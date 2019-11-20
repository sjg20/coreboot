/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2008-2009 coresystems GmbH
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; version 2 of
 * the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <arch/io.h>
#include <device/pci_ops.h>
#include <console/console.h>
#include <cpu/x86/smm.h>
#include <southbridge/intel/i82801gx/nvs.h>
#include <southbridge/intel/common/pmutil.h>
#include <ec/acpi/ec.h>
#include <pc80/mc146818rtc.h>
#include <ec/lenovo/h8/h8.h>
#include <delay.h>
#include "dock.h"
#include "smi.h"

#define GPE_EC_SCI	12

static void mainboard_smi_save_cmos(void)
{
	u8 val;
	u8 tmp70, tmp72;

	tmp70 = inb(0x70);
	tmp72 = inb(0x72);

	val = pci_read_config8(PCI_DEV(0, 2, 1), 0xf4);
	set_option("tft_brightness", &val);
	val = ec_read(H8_VOLUME_CONTROL);
	set_option("volume", &val);

	outb(tmp70, 0x70);
	outb(tmp72, 0x72);
}

int mainboard_io_trap_handler(int smif)
{
	switch (smif) {
	case SMI_DOCK_CONNECT:
		ec_clr_bit(0x03, 2);
		mdelay(250);
		if (!dock_connect()) {
			ec_set_bit(0x03, 2);
			/* set dock LED to indicate status */
			ec_write(0x0c, 0x09);
			ec_write(0x0c, 0x88);
		} else {
			/* blink dock LED to indicate failure */
			ec_write(0x0c, 0x08);
			ec_write(0x0c, 0xc9);
		}
		break;

	case SMI_DOCK_DISCONNECT:
		ec_clr_bit(0x03, 2);
		dock_disconnect();
		break;

	case SMI_SAVE_CMOS:
		mainboard_smi_save_cmos();
		break;
	default:
		return 0;
	}

	/* On success, the IO Trap Handler returns 1
	 * On failure, the IO Trap Handler returns a value != 1 */
	return 1;
}

static void mainboard_smi_brightness_up(void)
{
	u8 value;

	if ((value = pci_read_config8(PCI_DEV(0, 2, 1), 0xf4)) < 0xf0)
		pci_write_config8(PCI_DEV(0, 2, 1), 0xf4, (value + 0x10) | 0xf);
}

static void mainboard_smi_brightness_down(void)
{
	u8 value;

	if ((value = pci_read_config8(PCI_DEV(0, 2, 1), 0xf4)) > 0x10)
		pci_write_config8(PCI_DEV(0, 2, 1), 0xf4, (value - 0x10) & 0xf0);
}

static void mainboard_smi_handle_ec_sci(void)
{
	u8 status = inb(EC_SC);
	u8 event;

	if (!(status & EC_SCI_EVT))
		return;

	event = ec_query();
	printk(BIOS_DEBUG, "EC event %02x\n", event);

	switch (event) {
		/* brightness up */
		case 0x14:
			mainboard_smi_brightness_up();
			mainboard_smi_save_cmos();
			break;
		/* brightness down */
		case 0x15:
			mainboard_smi_brightness_down();
			mainboard_smi_save_cmos();
			break;
			/* Fn-F9 key */
		case 0x18:
			/* Power loss */
		case 0x27:
			/* Undock Key */
		case 0x50:
			mainboard_io_trap_handler(SMI_DOCK_DISCONNECT);
			break;
			/* Dock Event */
		case 0x37:
		case 0x58:
			mainboard_io_trap_handler(SMI_DOCK_CONNECT);
			break;
		default:
			break;
	}
}

void mainboard_smi_gpi(u32 gpi)
{
	if (gpi & (1 << GPE_EC_SCI))
		mainboard_smi_handle_ec_sci();
}

int mainboard_smi_apmc(u8 data)
{
	switch (data) {
		case APM_CNT_ACPI_ENABLE:
			/* use 0x1600/0x1604 to prevent races with userspace */
			ec_set_ports(0x1604, 0x1600);
			/* route H8SCI to SCI */
			gpi_route_interrupt(GPE_EC_SCI, GPI_IS_SCI);
			/* discard all events, and enable attention */
			ec_write(0x80, 0x01);
			break;
		case APM_CNT_ACPI_DISABLE:
			/* we have to use port 0x62/0x66, as 0x1600/0x1604 doesn't
			   provide a EC query function */
			ec_set_ports(0x66, 0x62);
			/* route H8SCI# to SMI */
			gpi_route_interrupt(GPE_EC_SCI, GPI_IS_SMI);
			/* discard all events, and enable attention */
			ec_write(0x80, 0x01);
			break;
		default:
			break;
	}
	return 0;
}
