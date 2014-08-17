/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2007-2009 coresystems GmbH
 * Copyright (C) 2011 Sven Schnelle <svens@stackframe.org>
 * Copyright (C) 2013 Vladimir Serbinenko <phcoder@gmail.com>
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
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston,
 * MA 02110-1301 USA
 */

#include <console/console.h>
#include <device/device.h>
#include <arch/io.h>
#include <delay.h>
#include <device/pci_def.h>
#include <device/pci_ops.h>
#include <device/pci_ids.h>
#include <arch/io.h>
#include <northbridge/intel/nehalem/nehalem.h>
#include <southbridge/intel/bd82x6x/pch.h>
#include <ec/acpi/ec.h>

#include <pc80/mc146818rtc.h>
#include "hda_verb.h"
#include <arch/x86/include/arch/acpigen.h>
#if CONFIG_PCI_OPTION_ROM_RUN_YABEL || CONFIG_PCI_OPTION_ROM_RUN_REALMODE
#include <x86emu/regs.h>
#include <arch/interrupt.h>
#endif
#include <pc80/keyboard.h>
#include <cpu/x86/lapic.h>
#include <device/pci.h>
#include <smbios.h>
#include <device/azalia_device.h>

static acpi_cstate_t cst_entries[] = {
	{1, 1, 1000, {0x7f, 1, 2, {0}, 1, 0}},
	{2, 1, 500, {0x01, 8, 0, {0}, DEFAULT_PMBASE + LV2, 0}},
	{2, 17, 250, {0x01, 8, 0, {0}, DEFAULT_PMBASE + LV3, 0}},
};

int get_cst_entries(acpi_cstate_t ** entries)
{
	*entries = cst_entries;
	return ARRAY_SIZE(cst_entries);
}

#if CONFIG_PCI_OPTION_ROM_RUN_YABEL || CONFIG_PCI_OPTION_ROM_RUN_REALMODE

static int int15_handler(void)
{
	switch ((X86_EAX & 0xffff)) {
		/* Get boot display.  */
	case 0x5f35:
		X86_EAX = 0x5f;
		/* The flags are:
		   1 - VGA
		   4 - DisplayPort
		   8 - LCD
		 */
		X86_ECX = 0x8;

		return 1;
	case 0x5f40:
		X86_EAX = 0x5f;
		X86_ECX = 0x2;
		return 1;
	default:
		printk(BIOS_WARNING, "Unknown INT15 function %04x!\n",
		       X86_EAX & 0xffff);
		return 0;
	}
}
#endif

/* Audio Setup */

static void verb_setup(void)
{
	cim_verb_data = mainboard_cim_verb_data;
	cim_verb_data_size = sizeof(mainboard_cim_verb_data);
}

static void mainboard_enable(device_t dev)
{
	u16 pmbase;

	printk(BIOS_SPEW, "starting SPI configuration\n");

	/* Configure SPI.  */
	RCBA32(0x3800) = 0x07ff0500;
	RCBA32(0x3804) = 0x3f046008;
	RCBA32(0x3808) = 0x0058efc0;
	RCBA32(0x384c) = 0x92000000;
	RCBA32(0x3850) = 0x00000a0b;
	RCBA32(0x3858) = 0x07ff0500;
	RCBA32(0x385c) = 0x04ff0003;
	RCBA32(0x3860) = 0x00020001;
	RCBA32(0x3864) = 0x00000fff;
	RCBA32(0x3874) = 0;
	RCBA32(0x3890) = 0xf8400000;
	RCBA32(0x3894) = 0x143b5006;
	RCBA32(0x3898) = 0x05200302;
	RCBA32(0x389c) = 0x0601209f;
	RCBA32(0x38b0) = 0x00000004;
	RCBA32(0x38b4) = 0x03040002;
	RCBA32(0x38c0) = 0x00000007;
	RCBA32(0x38c8) = 0x00002005;
	RCBA32(0x38c4) = 0x00802005;
	RCBA32(0x3804) = 0x3f04e008;

	printk(BIOS_SPEW, "SPI configured\n");

	int i;
        const u8 dmp[256] = {
		0x00, 0x20, 0x00, 0x00, 0x00, 0x02, 0x89, 0xe4, 0x30, 0x00, 0x40, 0x14, 0x00, 0x00, 0x00, 0x11,
		0x03, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0a, 0x00, 0xf4, 0x01, 0x00, 0x00, 0x01,
		0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x19, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x62, 0x01, 0x04, 0x00, 0x08, 0x73, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
		0x42, 0x07, 0x09, 0x09, 0xf0, 0x00, 0x00, 0xf0, 0xa9, 0x00, 0x00, 0x06, 0x00, 0x00, 0xff, 0x00,
		0x00, 0x01, 0x00, 0x04, 0xff, 0xff, 0x00, 0x00, 0x00, 0xb1, 0x00, 0x00, 0x00, 0x00, 0x04, 0x0b,
		0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x28, 0x1b, 0x21, 0x00, 0x2c, 0x3b, 0x13, 0x00,
		0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x19, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x55, 0x5a, 0x57, 0x5c, 0x00, 0x00, 0x00, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x45, 0x00, 0x00, 0x00,
		0x52, 0x10, 0x52, 0x10, 0x64, 0x00, 0x00, 0x00, 0x74, 0x30, 0x00, 0x60, 0x00, 0x00, 0xaf, 0x0b,
		0x30, 0x45, 0x2e, 0x30, 0x38, 0x41, 0x43, 0x2e, 0x30, 0x31, 0x2e, 0x31, 0x36, 0x20, 0x00, 0x00,
        };

	for (i = 0; i < 256; i++)
		ec_write (i, dmp[i]);

	pmbase = pci_read_config32(dev_find_slot(0, PCI_DEVFN(0x1f, 0)),
				   PMBASE) & 0xff80;

	printk(BIOS_SPEW, " ... pmbase = 0x%04x\n", pmbase);

	outl(0, pmbase + SMI_EN);

	enable_lapic();
	pci_write_config32(dev_find_slot(0, PCI_DEVFN(0x1f, 0)), GPIO_BASE,
			   DEFAULT_GPIOBASE | 1);
	pci_write_config8(dev_find_slot(0, PCI_DEVFN(0x1f, 0)), GPIO_CNTL,
			  0x10);

#if CONFIG_PCI_OPTION_ROM_RUN_YABEL || CONFIG_PCI_OPTION_ROM_RUN_REALMODE
	/* Install custom int15 handler for VGA OPROM */
	mainboard_interrupt_handlers(0x15, &int15_handler);
#endif

	/* This sneaked in here, because EasyNote has no SuperIO chip.
	 */
	pc_keyboard_init();
	verb_setup();
}

struct chip_operations mainboard_ops = {
	.enable_dev = mainboard_enable,
};
