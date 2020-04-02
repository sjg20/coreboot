/* SPDX-License-Identifier: GPL-2.0-only */
/* This file is part of the coreboot project. */

#include <device/mmio.h>
#include <device/pci_ops.h>
#include <device/device.h>
#include <device/pci.h>
#include <device/pci_ids.h>

#include "i82801jx.h"

static void thermal_init(struct device *dev)
{
	if (LPC_IS_MOBILE(pcidev_on_root(0x1f, 0)))
		return;

	u8 reg8;
	u32 reg32;

	pci_write_config32(dev, 0x10, (uintptr_t)DEFAULT_TBAR);
	reg32 = pci_read_config32(dev, 0x04);
	pci_write_config32(dev, 0x04, reg32 | (1 << 1));

	write32(DEFAULT_TBAR + 0x04, 0); /* Clear thermal trip points. */
	write32(DEFAULT_TBAR + 0x44, 0);

	write8(DEFAULT_TBAR + 0x01, 0xba); /* Enable sensor 0 + 1. */
	write8(DEFAULT_TBAR + 0x41, 0xba);

	reg8 = read8(DEFAULT_TBAR + 0x08); /* Lock thermal registers. */
	write8(DEFAULT_TBAR + 0x08, reg8 | (1 << 7));
	reg8 = read8(DEFAULT_TBAR + 0x48);
	write8(DEFAULT_TBAR + 0x48, reg8 | (1 << 7));

	reg32 = pci_read_config32(dev, 0x04);
	pci_write_config32(dev, 0x04, reg32 & ~(1 << 1));
	pci_write_config32(dev, 0x10, 0);
}

static struct pci_operations thermal_pci_ops = {
	.set_subsystem = pci_dev_set_subsystem,
};

static struct device_operations device_ops = {
	.read_resources		= pci_dev_read_resources,
	.set_resources		= pci_dev_set_resources,
	.enable_resources	= pci_dev_enable_resources,
	.init			= thermal_init,
	.scan_bus		= 0,
	.ops_pci		= &thermal_pci_ops,
};

static const unsigned short pci_device_ids[] = {
	0x3a32,
	0x3a62,
	0
};

static const struct pci_driver ich10_thermal __pci_driver = {
	.ops	= &device_ops,
	.vendor	= PCI_VENDOR_ID_INTEL,
	.devices	= pci_device_ids,
};
