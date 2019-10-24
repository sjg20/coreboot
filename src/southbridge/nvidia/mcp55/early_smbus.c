/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2004 Tyan Computer
 * Written by Yinghai Lu <yhlu@tyan.com> for Tyan Computer.
 * Copyright (C) 2006,2007 AMD
 * Written by Yinghai Lu <yinghai.lu@amd.com> for AMD.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <arch/io.h>
#include <device/pci_ops.h>
#include <console/console.h>
#include <device/pci.h>
#include "smbus.h"
#include "mcp55.h"

#define SMBUS0_IO_BASE	0x1000
#define SMBUS1_IO_BASE	(0x1000 + (1 << 8))
/* Size: 0x40 */

void enable_smbus(void)
{
	pci_devfn_t dev;
	dev = pci_locate_device(PCI_ID(0x10de, 0x0368), 0);

	if (dev == PCI_DEV_INVALID)
		die("SMBus controller not found\n");

	/* Set SMBus I/O base. */
	pci_write_config32(dev, 0x20, SMBUS0_IO_BASE | 1);
	pci_write_config32(dev, 0x24, SMBUS1_IO_BASE | 1);

	/* Set SMBus I/O space enable. */
	pci_write_config16(dev, 0x4, 0x01);

	/* Clear any lingering errors, so the transaction will run. */
	outb(inb(SMBUS0_IO_BASE + SMBHSTSTAT), SMBUS0_IO_BASE + SMBHSTSTAT);
	outb(inb(SMBUS1_IO_BASE + SMBHSTSTAT), SMBUS1_IO_BASE + SMBHSTSTAT);
}

int smbus_recv_byte(unsigned int device)
{
	return do_smbus_recv_byte(SMBUS0_IO_BASE, device);
}

int smbus_send_byte(unsigned int device, unsigned char val)
{
	return do_smbus_send_byte(SMBUS0_IO_BASE, device, val);
}

int smbus_read_byte(unsigned int device, unsigned int address)
{
	return do_smbus_read_byte(SMBUS0_IO_BASE, device, address);
}

int smbus_write_byte(unsigned int device, unsigned int address,
				   unsigned char val)
{
	return do_smbus_write_byte(SMBUS0_IO_BASE, device, address, val);
}

int smbusx_recv_byte(unsigned int smb_index, unsigned int device)
{
	return do_smbus_recv_byte(SMBUS0_IO_BASE + (smb_index << 8), device);
}

int smbusx_send_byte(unsigned int smb_index, unsigned int device,
				   unsigned char val)
{
	return do_smbus_send_byte(SMBUS0_IO_BASE + (smb_index << 8),
				  device, val);
}

int smbusx_read_byte(unsigned int smb_index, unsigned int device,
				   unsigned int address)
{
	return do_smbus_read_byte(SMBUS0_IO_BASE + (smb_index << 8),
				  device, address);
}

int smbusx_write_byte(unsigned int smb_index, unsigned int device,
				    unsigned int address, unsigned char val)
{
	return do_smbus_write_byte(SMBUS0_IO_BASE + (smb_index << 8),
				   device, address, val);
}
