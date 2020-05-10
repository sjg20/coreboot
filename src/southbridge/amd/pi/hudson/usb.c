/* SPDX-License-Identifier: GPL-2.0-only */

#include <device/device.h>
#include <device/pci.h>
#include <device/pci_ids.h>
#include <device/pci_ehci.h>
#include "hudson.h"

static struct pci_operations lops_pci = {
	.set_subsystem = pci_dev_set_subsystem,
};

static void usb_init(struct device *dev)
{
}

static struct device_operations usb_ops = {
	.read_resources = pci_ehci_read_resources,
	.set_resources = pci_dev_set_resources,
	.enable_resources = pci_dev_enable_resources,
	.init = usb_init,
	.ops_pci = &lops_pci,
};

static const unsigned short pci_device_ids[] = {
	PCI_DEVICE_ID_AMD_SB900_USB_18_0,
	PCI_DEVICE_ID_AMD_SB900_USB_18_2,
	PCI_DEVICE_ID_AMD_SB900_USB_20_5,
	PCI_DEVICE_ID_AMD_CZ_USB_0,
	PCI_DEVICE_ID_AMD_CZ_USB_1,
	PCI_DEVICE_ID_AMD_CZ_USB3_0,
	0
};

static const struct pci_driver usb_0_driver __pci_driver = {
	.ops = &usb_ops,
	.vendor = PCI_VENDOR_ID_AMD,
	.devices = pci_device_ids,
};
