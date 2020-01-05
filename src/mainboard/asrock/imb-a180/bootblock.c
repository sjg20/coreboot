/*
 * This file is part of the coreboot project.
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

#include <amdblocks/acpimmio.h>
#include <bootblock_common.h>
#include <device/pnp_type.h>
#include <superio/winbond/common/winbond.h>
#include <superio/winbond/w83627uhg/w83627uhg.h>

#define SERIAL_DEV PNP_DEV(0x2e, W83627UHG_SP1)

void bootblock_mainboard_early_init(void)
{
	u32 reg32;

	/* Disable PCI-PCI bridge and release GPIO32/33 for other uses. */
	pm_write8(0xea, 0x1);

	/* Set auxiliary output clock frequency on OSCOUT1 pin to be 48MHz */
	reg32 = misc_read32(0x28);
	reg32 &= 0xfff8ffff;
	misc_write32(0x28, reg32);

	/* Enable Auxiliary Clock1, disable FCH 14 MHz OscClk */
	reg32 = misc_read32(0x40);
	reg32 &= 0xffffbffb;
	misc_write32(0x40, reg32);

	/* w83627uhg has a default clk of 48MHz, p.9 of data-sheet */
	winbond_enable_serial(SERIAL_DEV, CONFIG_TTYS0_BASE);
}
