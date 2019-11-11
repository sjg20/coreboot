/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2007-2008 coresystems GmbH
 * Copyright (C) 2016 Arthur Heymans arthur@aheymans.xyz
 * Copyright (C) 2016 Kyösti Mälkki <kyosti.malkki@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <stdint.h>
#include <cf9_reset.h>
#include <device/pnp_ops.h>
#include <device/pci_ops.h>
#include <device/pci_def.h>
#include <cpu/x86/lapic.h>
#include <superio/winbond/common/winbond.h>
#include <superio/winbond/w83627dhg/w83627dhg.h>
#include <console/console.h>
#include <arch/romstage.h>
#include <northbridge/intel/i945/i945.h>
#include <northbridge/intel/i945/raminit.h>
#include <southbridge/intel/i82801gx/i82801gx.h>
#include <southbridge/intel/common/pmclib.h>
#include <cpu/x86/msr.h>
#include <cpu/intel/speedstep.h>
#include <arch/cpu.h>

#define SERIAL_DEV PNP_DEV(0x2e, W83627DHG_SP1)
#define GPIO_DEV PNP_DEV(0x2e, W83627DHG_GPIO2345_V)

/*
 * BSEL0 is connected with GPIO32
 * BSEL1 is connected with GPIO33 with inversed logic
 * BSEL2 is connected with GPIO55
 */
static int setup_sio_gpio(u8 bsel)
{
	int need_reset = 0;
	u8 reg, old_reg;

	pnp_enter_ext_func_mode(GPIO_DEV);
	pnp_set_logical_device(GPIO_DEV);

	reg = 0x9a;
	old_reg = pnp_read_config(GPIO_DEV, 0x2c);
	pnp_write_config(GPIO_DEV, 0x2c, reg);
	need_reset = (reg != old_reg);

	pnp_write_config(GPIO_DEV, 0x30, 0x0e);
	pnp_write_config(GPIO_DEV, 0xe0, 0xde);
	pnp_write_config(GPIO_DEV, 0xf0, 0xf3);
	pnp_write_config(GPIO_DEV, 0xf4, 0x80);
	pnp_write_config(GPIO_DEV, 0xf5, 0x80);

	/* Invert GPIO33 */
	pnp_write_config(GPIO_DEV, 0xf2, 0x08);

	reg = (bsel & 3) << 2;
	old_reg = pnp_read_config(GPIO_DEV, 0xf1);
	pnp_write_config(GPIO_DEV, 0xf1, reg);
	need_reset += ((reg & 0xc) != (old_reg & 0xc));

	reg = (bsel >> 2) << 5;
	old_reg = pnp_read_config(GPIO_DEV, 0xe1);
	pnp_write_config(GPIO_DEV, 0xe1, reg);
	need_reset += ((reg & 0x20) != (old_reg & 0x20));

	pnp_exit_ext_func_mode(GPIO_DEV);

	return need_reset;
}

static u8 msr_get_fsb(void)
{
	u8 fsbcfg;
	msr_t msr;
	const u32 eax = cpuid_eax(1);

	/* Netburst */
	if (((eax >> 8) & 0xf) == 0xf) {
		msr = rdmsr(MSR_EBC_FREQUENCY_ID);
		fsbcfg = (msr.lo >> 16) & 0x7;
	} else { /* Intel Core 2 */
		msr = rdmsr(MSR_FSB_FREQ);
		fsbcfg = msr.lo & 0x7;
	}

	return fsbcfg;
}

static void rcba_config(void)
{
	/* Enable PCIe Root Port Clock Gate */
	RCBA32(CG) = 0x00000001;
}
void mainboard_romstage_entry(void)
{
	int s3resume = 0, boot_mode = 0;

	u8 c_bsel = msr_get_fsb();

	enable_lapic();

	i82801gx_lpc_setup();

	winbond_enable_serial(SERIAL_DEV, CONFIG_TTYS0_BASE);

	/* Set up the console */
	console_init();

	if (MCHBAR16(SSKPD) == 0xCAFE) {
		printk(BIOS_DEBUG, "soft reset detected.\n");
		boot_mode = 1;
	}

	/* Perform some early chipset initialization required
	 * before RAM initialization can work
	 */
	i82801gx_early_init();
	i945_early_initialization();

	s3resume = southbridge_detect_s3_resume();

	/*
	 * Result is that FSB is incorrect on s3 resume (fixed at 800MHz).
	 * Some CPU accept this others don't.
	 */
	if (!s3resume && setup_sio_gpio(c_bsel)) {
		printk(BIOS_DEBUG,
			"Needs reset to configure CPU BSEL straps\n");
		full_reset();
	}

	/* Enable SPD ROMs and DDR-II DRAM */
	enable_smbus();

	if (CONFIG(DEBUG_RAM_SETUP))
		dump_spd_registers();

	sdram_initialize(s3resume ? 2 : boot_mode, NULL);

	/* This should probably go away. Until now it is required
	 * and mainboard specific
	 */
	rcba_config();

	/* Chipset Errata! */
	fixup_i945_errata();

	/* Initialize the internal PCIe links before we go into stage2 */
	i945_late_initialization(s3resume);
}
