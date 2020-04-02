/* SPDX-License-Identifier: GPL-2.0-only */
/* This file is part of the coreboot project. */

#ifndef _PCI_EHCI_H_
#define _PCI_EHCI_H_

#include <device/device.h>
#include <device/pci_type.h>

#define EHCI_BAR_INDEX		0x10
#define PCI_EHCI_CLASSCODE	0x0c0320  /* USB2.0 with EHCI controller */

/* Return PCI BDF for an EHCI controller by a given index. PCI function
 * must already be powered to respond to configuration requests.
 */
pci_devfn_t pci_ehci_dbg_dev(unsigned int hcd_idx);

u8 *pci_ehci_base_regs(pci_devfn_t dev);
void pci_ehci_dbg_set_port(pci_devfn_t dev, unsigned int port);

#if !CONFIG(USBDEBUG)
#define pci_ehci_read_resources pci_dev_read_resources
#else
/* Relocation of EHCI Debug Port BAR
 *
 * PCI EHCI controller with Debug Port capability shall replace
 * pci_dev_read_resources() with pci_ehci_read_resources() in its
 * declaration of device_operations for .read_resources.
 * This installs a hook to reconfigure usbdebug when resource allocator
 * assigns a new BAR for the device.
 */
struct device;
void pci_ehci_read_resources(struct device *dev);
#endif

#endif /* _PCI_EHCI_H_ */
