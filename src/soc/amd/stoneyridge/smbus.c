/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2010 Advanced Micro Devices, Inc.
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
#include <stdint.h>
#include <console/console.h>
#include <amdblocks/acpimmio.h>
#include <soc/smbus.h>
#include <soc/southbridge.h>

static u8 controller_read8(u32 base, u8 reg)
{
	switch (base) {
	case ACPIMMIO_SMBUS_BASE:
		return smbus_read8(reg);
	case ACPIMMIO_ASF_BASE:
		return asf_read8(reg);
	default:
		printk(BIOS_ERR, "Error attempting to read SMBus at address 0x%x\n",
				base);
	}
	return 0xff;
}

static void controller_write8(u32 base, u8 reg, u8 val)
{
	switch (base) {
	case ACPIMMIO_SMBUS_BASE:
		smbus_write8(reg, val);
		break;
	case ACPIMMIO_ASF_BASE:
		asf_write8(reg, val);
		break;
	default:
		printk(BIOS_ERR, "Error attempting to write SMBus at address 0x%x\n",
				base);
	}
}

static int smbus_wait_until_ready(u32 mmio)
{
	u32 loops;
	loops = SMBUS_TIMEOUT;
	do {
		u8 val;
		val = controller_read8(mmio, SMBHSTSTAT);
		val &= SMBHST_STAT_VAL_BITS;
		if (val == 0) {	/* ready now */
			return 0;
		}
		controller_write8(mmio, SMBHSTSTAT, val);
	} while (--loops);
	return -2;		/* time out */
}

static int smbus_wait_until_done(u32 mmio)
{
	u32 loops;
	loops = SMBUS_TIMEOUT;
	do {
		u8 val;

		val = controller_read8(mmio, SMBHSTSTAT);
		val &= SMBHST_STAT_VAL_BITS;	/* mask off reserved bits */
		if (val & SMBHST_STAT_ERROR_BITS)
			return -5;	/* error */
		if (val == SMBHST_STAT_NOERROR) {
			controller_write8(mmio, SMBHSTSTAT, val); /* clr sts */
			return 0;
		}
	} while (--loops);
	return -3;		/* timeout */
}

int do_smbus_recv_byte(u32 mmio, u8 device)
{
	u8 byte;

	if (smbus_wait_until_ready(mmio) < 0)
		return -2;	/* not ready */

	/* set the device I'm talking to */
	controller_write8(mmio, SMBHSTADDR, ((device & 0x7f) << 1) | 1);

	byte = controller_read8(mmio, SMBHSTCTRL);
	byte &= ~SMBHST_CTRL_MODE_BITS;			/* Clear [4:2] */
	byte |= SMBHST_CTRL_STRT | SMBHST_CTRL_BTE_RW;	/* set mode, start */
	controller_write8(mmio, SMBHSTCTRL, byte);

	/* poll for transaction completion */
	if (smbus_wait_until_done(mmio) < 0)
		return -3;	/* timeout or error */

	/* read results of transaction */
	byte = controller_read8(mmio, SMBHSTDAT0);

	return byte;
}

int do_smbus_send_byte(u32 mmio, u8 device, u8 val)
{
	u8 byte;

	if (smbus_wait_until_ready(mmio) < 0)
		return -2;	/* not ready */

	/* set the command... */
	controller_write8(mmio, SMBHSTDAT0, val);

	/* set the device I'm talking to */
	controller_write8(mmio, SMBHSTADDR, ((device & 0x7f) << 1) | 0);

	byte = controller_read8(mmio, SMBHSTCTRL);
	byte &= ~SMBHST_CTRL_MODE_BITS;			/* Clear [4:2] */
	byte |= SMBHST_CTRL_STRT | SMBHST_CTRL_BTE_RW;	/* set mode, start */
	controller_write8(mmio, SMBHSTCTRL, byte);

	/* poll for transaction completion */
	if (smbus_wait_until_done(mmio) < 0)
		return -3;	/* timeout or error */

	return 0;
}

int do_smbus_read_byte(u32 mmio, u8 device, u8 address)
{
	u8 byte;

	if (smbus_wait_until_ready(mmio) < 0)
		return -2;	/* not ready */

	/* set the command/address... */
	controller_write8(mmio, SMBHSTCMD, address & 0xff);

	/* set the device I'm talking to */
	controller_write8(mmio, SMBHSTADDR, ((device & 0x7f) << 1) | 1);

	byte = controller_read8(mmio, SMBHSTCTRL);
	byte &= ~SMBHST_CTRL_MODE_BITS;			/* Clear [4:2] */
	byte |= SMBHST_CTRL_STRT | SMBHST_CTRL_BDT_RW;	/* set mode, start */
	controller_write8(mmio, SMBHSTCTRL, byte);

	/* poll for transaction completion */
	if (smbus_wait_until_done(mmio) < 0)
		return -3;	/* timeout or error */

	/* read results of transaction */
	byte = controller_read8(mmio, SMBHSTDAT0);

	return byte;
}

int do_smbus_write_byte(u32 mmio, u8 device, u8 address, u8 val)
{
	u8 byte;

	if (smbus_wait_until_ready(mmio) < 0)
		return -2;	/* not ready */

	/* set the command/address... */
	controller_write8(mmio, SMBHSTCMD, address & 0xff);

	/* set the device I'm talking to */
	controller_write8(mmio, SMBHSTADDR, ((device & 0x7f) << 1) | 0);

	/* output value */
	controller_write8(mmio, SMBHSTDAT0, val);

	byte = controller_read8(mmio, SMBHSTCTRL);
	byte &= ~SMBHST_CTRL_MODE_BITS;			/* Clear [4:2] */
	byte |= SMBHST_CTRL_STRT | SMBHST_CTRL_BDT_RW;	/* set mode, start */
	controller_write8(mmio, SMBHSTCTRL, byte);

	/* poll for transaction completion */
	if (smbus_wait_until_done(mmio) < 0)
		return -3;	/* timeout or error */

	return 0;
}

void alink_ab_indx(u32 reg_space, u32 reg_addr, u32 mask, u32 val)
{
	u32 tmp;

	outl((reg_space & 0x7) << 29 | reg_addr, AB_INDX);
	tmp = inl(AB_DATA);
	/* rpr 4.2
	 * For certain revisions of the chip, the ABCFG registers,
	 * with an address of 0x100NN (where 'N' is any hexadecimal
	 * number), require an extra programming step.*/
	outl(0, AB_INDX);

	tmp &= ~mask;
	tmp |= val;

	// printk(BIOS_DEBUG, "about write %x, index=%x", tmp,
	//				(reg_space&0x3)<<29 | reg_addr);

	/* probably we dont have to do it again. */
	outl((reg_space & 0x7) << 29 | reg_addr, AB_INDX);
	outl(tmp, AB_DATA);
	outl(0, AB_INDX);
}

void alink_rc_indx(u32 reg_space, u32 reg_addr, u32 port, u32 mask, u32 val)
{
	u32 tmp;

	outl((reg_space & 0x7) << 29 | (port & 3) << 24 | reg_addr, AB_INDX);
	tmp = inl(AB_DATA);
	/* rpr 4.2
	 * For certain revisions of the chip, the ABCFG registers,
	 * with an address of 0x100NN (where 'N' is any hexadecimal
	 * number), require an extra programming step.*/
	outl(0, AB_INDX);

	tmp &= ~mask;
	tmp |= val;

	//printk(BIOS_DEBUG, "about write %x, index=%x", tmp,
	//		(reg_space&0x3)<<29 | (port&3) << 24 | reg_addr);

	/* probably we dont have to do it again. */
	outl((reg_space & 0x7) << 29 | (port & 3) << 24 | reg_addr, AB_INDX);
	outl(tmp, AB_DATA);
	outl(0, AB_INDX);
}

/*
 * space = 0: AX_INDXC, AX_DATAC
 * space = 1: AX_INDXP, AX_DATAP
 */
void alink_ax_indx(u32 space /*c or p? */, u32 axindc, u32 mask, u32 val)
{
	u32 tmp;

	/* read axindc to tmp */
	outl(space << 29 | space << 3 | 0x30, AB_INDX);
	outl(axindc, AB_DATA);
	outl(0, AB_INDX);
	outl(space << 29 | space << 3 | 0x34, AB_INDX);
	tmp = inl(AB_DATA);
	outl(0, AB_INDX);

	tmp &= ~mask;
	tmp |= val;

	/* write tmp */
	outl(space << 29 | space << 3 | 0x30, AB_INDX);
	outl(axindc, AB_DATA);
	outl(0, AB_INDX);
	outl(space << 29 | space << 3 | 0x34, AB_INDX);
	outl(tmp, AB_DATA);
	outl(0, AB_INDX);
}
