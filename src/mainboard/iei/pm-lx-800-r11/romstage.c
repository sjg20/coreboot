/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2007 Advanced Micro Devices, Inc.
 * Copyright (C) 2012 Ricardo Martins <rasmartins@gmail.com>
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

#include <stdlib.h>
#include <spd.h>
#include <arch/io.h>
#include <device/pci_def.h>
#include <device/pnp_def.h>
#include <console/console.h>
#include <cpu/x86/bist.h>
#include <cpu/x86/msr.h>
#include <cpu/amd/lxdef.h>
#include <southbridge/amd/cs5536/cs5536.h>
#include <superio/winbond/common/winbond.h>
#include <superio/winbond/w83627ehg/w83627ehg.h>
#include <northbridge/amd/lx/raminit.h>

#define SERIAL_DEV PNP_DEV(0x2e, W83627EHG_SP1)

int spd_read_byte(unsigned int device, unsigned int address)
{
	/* Only DIMM0 is available. */
	if (device != DIMM0)
		return 0xff;

	return smbus_read_byte(device, address);
}

#include <northbridge/amd/lx/pll_reset.c>
#include <cpu/amd/geode_lx/cpureginit.c>
#include <cpu/amd/geode_lx/syspreinit.c>
#include <cpu/amd/geode_lx/msrinit.c>

void asmlinkage mainboard_romstage_entry(unsigned long bist)
{
	static const struct mem_controller memctrl[] = {
		{.channel0 = {DIMM0, DIMM1}}
	};

	SystemPreInit();
	msr_init();

	cs5536_early_setup();

	winbond_enable_serial(SERIAL_DEV, CONFIG_TTYS0_BASE);
	console_init();

	report_bist_failure(bist);

	pll_reset();

	cpuRegInit(0, DIMM0, DIMM1, DRAM_TERMINATED);

	sdram_initialize(1, memctrl);
}
