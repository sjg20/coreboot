/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2005 Yinghai Lu <yinghailu@gmail.com>
 * Copyright (C) 2009 coresystems GmbH
 * Copyright (C) 2013 Vladimir Serbinenko
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <arch/io.h>
#include <console/console.h>
#include <device/smbus_def.h>
#include <stdlib.h>
#include "smbus.h"


#if IS_ENABLED(CONFIG_DEBUG_SMBUS)
#define dprintk(args...) printk(BIOS_DEBUG, ##args)
#else
#define dprintk(args...) do {} while (0)
#endif

/* I801 command constants */
#define I801_QUICK		(0 << 2)
#define I801_BYTE		(1 << 2)
#define I801_BYTE_DATA		(2 << 2)
#define I801_WORD_DATA		(3 << 2)
#define I801_BLOCK_DATA		(5 << 2)
#define I801_I2C_BLOCK_DATA	(6 << 2) /* ICH5 and later */

/* I801 Host Control register bits */
#define SMBHSTCNT_INTREN	(1 << 0)
#define SMBHSTCNT_KILL		(1 << 1)
#define SMBHSTCNT_LAST_BYTE	(1 << 5)
#define SMBHSTCNT_START		(1 << 6)
#define SMBHSTCNT_PEC_EN	(1 << 7) /* ICH3 and later */

/* I801 Hosts Status register bits */
#define SMBHSTSTS_BYTE_DONE	(1 << 7)
#define SMBHSTSTS_INUSE_STS	(1 << 6)
#define SMBHSTSTS_SMBALERT_STS	(1 << 5)
#define SMBHSTSTS_FAILED	(1 << 4)
#define SMBHSTSTS_BUS_ERR	(1 << 3)
#define SMBHSTSTS_DEV_ERR	(1 << 2)
#define SMBHSTSTS_INTR		(1 << 1)
#define SMBHSTSTS_HOST_BUSY	(1 << 0)

/* For SMBXMITADD register. */
#define XMIT_WRITE(dev)		(((dev) << 1) | 0)
#define XMIT_READ(dev)		(((dev) << 1) | 1)

#define SMBUS_TIMEOUT		(10 * 1000 * 100)
#define SMBUS_BLOCK_MAXLEN	32

static void smbus_delay(void)
{
	inb(0x80);
}

static int host_completed(u8 status)
{
	if (status & SMBHSTSTS_HOST_BUSY)
		return 0;
	status &= ~(SMBHSTSTS_SMBALERT_STS | SMBHSTSTS_INUSE_STS);
	return status != 0;
}

static int recover_master(int smbus_base, int ret)
{
	/* TODO: Depending of the failure, drive KILL transaction
	 * or force soft reset on SMBus master controller.
	 */
	printk(BIOS_ERR, "SMBus: Fatal master timeout (%d)\n", ret);
	return ret;
}

static int cb_err_from_stat(u8 status)
{
	/* Ignore the "In Use" status... */
	status &= ~(SMBHSTSTS_SMBALERT_STS | SMBHSTSTS_INUSE_STS);

	if (status == SMBHSTSTS_INTR)
		return 0;

	return SMBUS_ERROR;
}

static int setup_command(unsigned int smbus_base, u8 ctrl, u8 xmitadd)
{
	unsigned int loops = SMBUS_TIMEOUT;
	u8 host_busy;

	do {
		smbus_delay();
		host_busy = inb(smbus_base + SMBHSTSTAT) & SMBHSTSTS_HOST_BUSY;
	} while (--loops && host_busy);

	if (loops == 0)
		return recover_master(smbus_base,
				      SMBUS_WAIT_UNTIL_READY_TIMEOUT);

	/* Clear any lingering errors, so the transaction will run. */
	outb(inb(smbus_base + SMBHSTSTAT), smbus_base + SMBHSTSTAT);

	/* Set up transaction */
	/* Disable interrupts */
	outb(ctrl, (smbus_base + SMBHSTCTL));

	/* Set the device I'm talking to. */
	outb(xmitadd, smbus_base + SMBXMITADD);

	return 0;
}

static int execute_command(unsigned int smbus_base)
{
	unsigned int loops = SMBUS_TIMEOUT;
	u8 status;

	/* Start the command. */
	outb((inb(smbus_base + SMBHSTCTL) | SMBHSTCNT_START),
	     smbus_base + SMBHSTCTL);

	/* Poll for it to start. */
	do {
		smbus_delay();

		/* If we poll too slow, we could miss HOST_BUSY flag
		 * set and detect INTR or x_ERR flags instead here.
		 */
		status = inb(smbus_base + SMBHSTSTAT);
		status &= ~(SMBHSTSTS_SMBALERT_STS | SMBHSTSTS_INUSE_STS);
	} while (--loops && status == 0);

	if (loops == 0)
		return recover_master(smbus_base,
				      SMBUS_WAIT_UNTIL_ACTIVE_TIMEOUT);

	return 0;
}

static int complete_command(unsigned int smbus_base)
{
	unsigned int loops = SMBUS_TIMEOUT;
	u8 status;

	do {
		smbus_delay();
		status = inb(smbus_base + SMBHSTSTAT);
	} while (--loops && !host_completed(status));

	if (loops == 0)
		return recover_master(smbus_base,
				      SMBUS_WAIT_UNTIL_DONE_TIMEOUT);

	return cb_err_from_stat(status);
}

int do_smbus_read_byte(unsigned int smbus_base, u8 device,
		unsigned int address)
{
	int ret;
	u8 byte;

	/* Set up for a byte data read. */
	ret = setup_command(smbus_base, I801_BYTE_DATA, XMIT_READ(device));
	if (ret < 0)
		return ret;

	/* Set the command/address... */
	outb(address, smbus_base + SMBHSTCMD);

	/* Clear the data byte... */
	outb(0, smbus_base + SMBHSTDAT0);

	/* Start the command */
	ret = execute_command(smbus_base);
	if (ret < 0)
		return ret;

	/* Poll for transaction completion */
	ret = complete_command(smbus_base);
	if (ret < 0)
		return ret;

	/* Read results of transaction */
	byte = inb(smbus_base + SMBHSTDAT0);
	return byte;
}

int do_smbus_write_byte(unsigned int smbus_base, u8 device,
			unsigned int address, unsigned int data)
{
	int ret;

	/* Set up for a byte data write. */
	ret = setup_command(smbus_base, I801_BYTE_DATA, XMIT_WRITE(device));
	if (ret < 0)
		return ret;

	/* Set the command/address... */
	outb(address, smbus_base + SMBHSTCMD);

	/* Set the data byte... */
	outb(data, smbus_base + SMBHSTDAT0);

	/* Start the command */
	ret = execute_command(smbus_base);
	if (ret < 0)
		return ret;

	/* Poll for transaction completion */
	return complete_command(smbus_base);
}

int do_smbus_block_read(unsigned int smbus_base, u8 device, u8 cmd,
			unsigned int max_bytes, u8 *buf)
{
	u8 status;
	int ret, slave_bytes;
	int bytes_read = 0;
	unsigned int loops = SMBUS_TIMEOUT;

	max_bytes = MIN(SMBUS_BLOCK_MAXLEN, max_bytes);

	/* Set up for a block data read. */
	ret = setup_command(smbus_base, I801_BLOCK_DATA, XMIT_READ(device));
	if (ret < 0)
		return ret;

	/* Set the command/address... */
	outb(cmd, smbus_base + SMBHSTCMD);

	/* Reset number of bytes to transfer so we notice later it
	 * was really updated with the transaction. */
	outb(0, smbus_base + SMBHSTDAT0);

	/* Start the command */
	ret = execute_command(smbus_base);
	if (ret < 0)
		return ret;

	/* Poll for transaction completion */
	do {
		status = inb(smbus_base + SMBHSTSTAT);

		if (status & SMBHSTSTS_BYTE_DONE) { /* Byte done */

			if (bytes_read < max_bytes) {
				*buf++ = inb(smbus_base + SMBBLKDAT);
				bytes_read++;
			}

			/* Engine internally completes the transaction
			 * and clears HOST_BUSY flag once the byte count
			 * from slave is reached.
			 */
			outb(SMBHSTSTS_BYTE_DONE, smbus_base + SMBHSTSTAT);
		}
	} while (--loops && !host_completed(status));

	/* Post-check we received complete message. */
	slave_bytes = inb(smbus_base + SMBHSTDAT0);

	dprintk("%s: status = %02x, len = %d / %d, loops = %d\n",
		__func__, status, bytes_read, slave_bytes, loops);

	if (loops == 0)
		return recover_master(smbus_base,
				      SMBUS_WAIT_UNTIL_DONE_TIMEOUT);

	ret = cb_err_from_stat(status);
	if (ret < 0)
		return ret;

	if (bytes_read < slave_bytes)
		return SMBUS_ERROR;

	return bytes_read;
}

int do_smbus_block_write(unsigned int smbus_base, u8 device, u8 cmd,
			const unsigned int bytes, const u8 *buf)
{
	u8 status;
	int ret, bytes_sent = 0;
	unsigned int loops = SMBUS_TIMEOUT;

	if (bytes > SMBUS_BLOCK_MAXLEN)
		return SMBUS_ERROR;

	/* Set up for a block data write. */
	ret = setup_command(smbus_base, I801_BLOCK_DATA, XMIT_WRITE(device));
	if (ret < 0)
		return ret;

	/* Set the command/address... */
	outb(cmd, smbus_base + SMBHSTCMD);

	/* Set number of bytes to transfer. */
	outb(bytes, smbus_base + SMBHSTDAT0);

	/* Send first byte from buffer, bytes_sent increments after
	 * hardware acknowledges it.
	 */
	outb(*buf++, smbus_base + SMBBLKDAT);

	/* Start the command */
	ret = execute_command(smbus_base);
	if (ret < 0)
		return ret;

	/* Poll for transaction completion */
	do {
		status = inb(smbus_base + SMBHSTSTAT);

		if (status & SMBHSTSTS_BYTE_DONE) {
			bytes_sent++;
			if (bytes_sent < bytes)
				outb(*buf++, smbus_base + SMBBLKDAT);

			/* Engine internally completes the transaction
			 * and clears HOST_BUSY flag once the byte count
			 * has been reached.
			 */
			outb(SMBHSTSTS_BYTE_DONE, smbus_base + SMBHSTSTAT);
		}
	} while (--loops && !host_completed(status));

	dprintk("%s: status = %02x, len = %d / %d, loops = %d\n",
		__func__, status, bytes_sent, bytes, loops);

	if (loops == 0)
		return recover_master(smbus_base,
				      SMBUS_WAIT_UNTIL_DONE_TIMEOUT);

	ret = cb_err_from_stat(status);
	if (ret < 0)
		return ret;

	if (bytes_sent < bytes)
		return SMBUS_ERROR;

	return bytes_sent;
}

/* Only since ICH5 */
int do_i2c_block_read(unsigned int smbus_base, u8 device,
		unsigned int offset, const unsigned int bytes, u8 *buf)
{
	u8 status;
	int ret, bytes_read = 0;
	unsigned int loops = SMBUS_TIMEOUT;

	/* Set up for a i2c block data read.
	 *
	 * FIXME: Address parameter changes to XMIT_READ(device) with
	 * some revision of PCH. Presumably hardware revisions that
	 * do not have i2c block write support internally set LSB.
	 */
	ret = setup_command(smbus_base, I801_I2C_BLOCK_DATA,
			    XMIT_WRITE(device));
	if (ret < 0)
		return ret;

	/* device offset */
	outb(offset, smbus_base + SMBHSTDAT1);

	/* Start the command */
	ret = execute_command(smbus_base);
	if (ret < 0)
		return ret;

	/* Poll for transaction completion */
	do {
		status = inb(smbus_base + SMBHSTSTAT);

		if (status & SMBHSTSTS_BYTE_DONE) {

			if (bytes_read < bytes) {
				*buf++ = inb(smbus_base + SMBBLKDAT);
				bytes_read++;
			}

			if (bytes_read + 1 >= bytes) {
				/* indicate that next byte is the last one */
				outb(inb(smbus_base + SMBHSTCTL)
					| SMBHSTCNT_LAST_BYTE,
					smbus_base + SMBHSTCTL);
			}

			outb(SMBHSTSTS_BYTE_DONE, smbus_base + SMBHSTSTAT);
		}
	} while (--loops && !host_completed(status));

	dprintk("%s: status = %02x, len = %d / %d, loops = %d\n",
		__func__, status, bytes_read, bytes, loops);

	if (loops == 0)
		return recover_master(smbus_base,
				      SMBUS_WAIT_UNTIL_DONE_TIMEOUT);

	ret = cb_err_from_stat(status);
	if (ret < 0)
		return ret;

	if (bytes_read < bytes)
		return SMBUS_ERROR;

	return bytes_read;
}
