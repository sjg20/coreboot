/* SPDX-License-Identifier: GPL-2.0-only */
/* This file is part of the coreboot project. */

#include <device/device.h>
#include <device/pci.h>
#include <device/pci_ops.h>
#include <device/pci_ids.h>
#include "i82801jx.h"

static void pci_init(struct device *dev)
{
	u16 reg16;
	u8 reg8;

	/* This device has no interrupt */
	pci_write_config8(dev, PCI_INTERRUPT_LINE, 0xff);

	/* Master Latency Count must be set to 0x04! */
	reg8 = pci_read_config8(dev, D30F0_SMLT);
	reg8 &= 0x07;
	reg8 |= (0x04 << 3);
	pci_write_config8(dev, D30F0_SMLT, reg8);

	/* Clear errors in status registers */
	reg16 = pci_read_config16(dev, PCI_STATUS);
	//reg16 |= 0xf900;
	pci_write_config16(dev, PCI_STATUS, reg16);

	reg16 = pci_read_config16(dev, PCI_SEC_STATUS);
	// reg16 |= 0xf900;
	pci_write_config16(dev, PCI_SEC_STATUS, reg16);
}

static struct pci_operations pci_ops = {
	.set_subsystem = pci_dev_set_subsystem,
};

static struct device_operations device_ops = {
	.read_resources		= pci_bus_read_resources,
	.set_resources		= pci_dev_set_resources,
	.enable_resources	= pci_bus_enable_resources,
	.init			= pci_init,
	.scan_bus		= pci_scan_bridge,
	.reset_bus		= pci_bus_reset,
	.ops_pci		= &pci_ops,
};

static const unsigned short pci_device_ids[] = {
	0x244e,
	0
};

static const struct pci_driver ich10_pci __pci_driver = {
	.ops		= &device_ops,
	.vendor		= PCI_VENDOR_ID_INTEL,
	.devices	= pci_device_ids,
};
