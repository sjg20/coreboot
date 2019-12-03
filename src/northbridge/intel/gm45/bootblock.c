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

#include <arch/bootblock.h>
#include <device/pci_ops.h>

/* Just re-define these instead of including gm45.h. It blows up romcc. */
#define D0F0_PCIEXBAR_LO 0x60
#define D0F0_PCIEXBAR_HI 0x64

void bootblock_early_northbridge_init(void)
{
	uint32_t reg;

	/*
	 * The "io" variant of the config access is explicitly used to
	 * setup the PCIEXBAR because CONFIG_MMCONF_SUPPORT is set to
	 * to true. That way all subsequent non-explicit config accesses use
	 * MCFG. This code also assumes that bootblock_northbridge_init() is
	 * the first thing called in the non-asm boot block code. The final
	 * assumption is that no assembly code is using the
	 * CONFIG_MMCONF_SUPPORT option to do PCI config accesses.
	 *
	 * The PCIEXBAR is assumed to live in the memory mapped IO space under
	 * 4GiB.
	 */
	reg = 0;
	pci_io_write_config32(PCI_DEV(0,0,0), D0F0_PCIEXBAR_HI, reg);
	reg = CONFIG_MMCONF_BASE_ADDRESS | (2 << 1) | 1; /* 64MiB - 0-63 buses. */
	pci_io_write_config32(PCI_DEV(0,0,0), D0F0_PCIEXBAR_LO, reg);
}
