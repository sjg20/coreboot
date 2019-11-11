/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2015 Damien Zammit <damien@zamaudio.com>
 * Copyright (C) 2017 Arthur Heymans <arthur@aheymans.xyz>
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

#include <device/pnp_ops.h>
#include <device/pci_ops.h>
#include <console/console.h>
#include <arch/romstage.h>
#include <northbridge/intel/x4x/x4x.h>
#include <southbridge/intel/common/pmclib.h>
#include <southbridge/intel/i82801gx/i82801gx.h>
#include <superio/winbond/common/winbond.h>
#include <superio/winbond/w83627dhg/w83627dhg.h>

#define SERIAL_DEV PNP_DEV(0x2e, W83627DHG_SP1)
#define LPC_DEV PCI_DEV(0, 0x1f, 0)

static void mb_lpc_setup(void)
{
	/* Set GPIOs on superio, enable UART */
	pnp_enter_ext_func_mode(SERIAL_DEV);
	pnp_set_logical_device(SERIAL_DEV);

	pnp_write_config(SERIAL_DEV, 0x2c, 0x13);

	pnp_exit_ext_func_mode(SERIAL_DEV);

	/* IRQ routing */
	RCBA16(D31IR) = 0x0132;
	RCBA16(D29IR) = 0x0237;
}

void mainboard_romstage_entry(void)
{
	//                          ch0      ch1
	const u8 spd_addrmap[4] = { 0x50, 0, 0x52, 0 };
	u8 boot_path = 0;
	u8 s3_resume;

	/* Set southbridge and Super I/O GPIOs. */
	i82801gx_lpc_setup();
	mb_lpc_setup();
	winbond_enable_serial(SERIAL_DEV, CONFIG_TTYS0_BASE);

	console_init();

	enable_smbus();

	i82801gx_early_init();
	x4x_early_init();

	s3_resume = southbridge_detect_s3_resume();
	if (s3_resume)
		boot_path = BOOT_PATH_RESUME;
	if (MCHBAR32(PMSTS_MCHBAR) & PMSTS_WARM_RESET)
		boot_path = BOOT_PATH_WARM_RESET;

	sdram_initialize(boot_path, spd_addrmap);

	x4x_late_init(s3_resume);

	printk(BIOS_DEBUG, "x4x late init complete\n");

}
