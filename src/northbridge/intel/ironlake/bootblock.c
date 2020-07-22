/* SPDX-License-Identifier: GPL-2.0-only */

#include <arch/bootblock.h>
#include <device/pci_ops.h>
#include "ironlake.h"

void bootblock_early_northbridge_init(void)
{
	pci_io_write_config32(QPI_SAD, 0x50, CONFIG_MMCONF_BASE_ADDRESS | 1);
	pci_io_write_config32(QPI_SAD, 0x54, 0);
}
