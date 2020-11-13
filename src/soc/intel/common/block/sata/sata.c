/* SPDX-License-Identifier: GPL-2.0-only */

#include <device/device.h>
#include <device/pci.h>
#include <device/pci_ids.h>

static struct device_operations sata_ops = {
	.read_resources		= pci_dev_read_resources,
	.set_resources		= pci_dev_set_resources,
	.enable_resources	= pci_dev_enable_resources,
	.final			= pci_dev_request_bus_master,
	.ops_pci		= &pci_dev_ops_pci,
};

static const unsigned short pci_device_ids[] = {
	PCI_DID_INTEL_MTL_SATA,
	PCI_DID_INTEL_SPT_U_SATA,
	PCI_DID_INTEL_SPT_U_Y_PREMIUM_SATA,
	PCI_DID_INTEL_SPT_KBL_SATA,
	PCI_DID_INTEL_LWB_SATA_AHCI,
	PCI_DID_INTEL_LWB_SSATA_AHCI,
	PCI_DID_INTEL_LWB_SATA_RAID,
	PCI_DID_INTEL_LWB_SSATA_RAID,
	PCI_DID_INTEL_LWB_SATA_AHCI_SUPER,
	PCI_DID_INTEL_LWB_SSATA_AHCI_SUPER,
	PCI_DID_INTEL_LWB_SATA_RAID_SUPER,
	PCI_DID_INTEL_LWB_SSATA_RAID_SUPER,
	PCI_DID_INTEL_LWB_SATA_ALT,
	PCI_DID_INTEL_LWB_SATA_ALT_RST,
	PCI_DID_INTEL_LWB_SSATA_ALT,
	PCI_DID_INTEL_LWB_SSATA_ALT_RST,
	PCI_DID_INTEL_CNL_SATA,
	PCI_DID_INTEL_CNL_PREMIUM_SATA,
	PCI_DID_INTEL_CNP_CMP_COMPAT_SATA,
	PCI_DID_INTEL_CNP_H_SATA,
	PCI_DID_INTEL_CNP_H_HALO_SATA,
	PCI_DID_INTEL_CNP_LP_SATA,
	PCI_DID_INTEL_ICP_U_SATA,
	PCI_DID_INTEL_CMP_SATA,
	PCI_DID_INTEL_CMP_PREMIUM_SATA,
	PCI_DID_INTEL_CMP_LP_SATA,
	PCI_DID_INTEL_CMP_H_SATA,
	PCI_DID_INTEL_CMP_H_HALO_SATA,
	PCI_DID_INTEL_CMP_H_PREMIUM_SATA,
	PCI_DID_INTEL_TGP_LP_SATA,
	PCI_DID_INTEL_TGP_SATA,
	PCI_DID_INTEL_TGP_PREMIUM_SATA,
	PCI_DID_INTEL_TGP_COMPAT_SATA,
	PCI_DID_INTEL_TGP_H_SATA,
	PCI_DID_INTEL_MCC_AHCI_SATA,
	PCI_DID_INTEL_JSP_SATA_1,
	PCI_DID_INTEL_JSP_SATA_2,
	PCI_DID_INTEL_ADP_P_SATA_1,
	PCI_DID_INTEL_ADP_P_SATA_2,
	PCI_DID_INTEL_ADP_P_SATA_3,
	PCI_DID_INTEL_ADP_P_SATA_4,
	PCI_DID_INTEL_ADP_P_SATA_5,
	PCI_DID_INTEL_ADP_P_SATA_6,
	PCI_DID_INTEL_ADP_S_SATA_1,
	PCI_DID_INTEL_ADP_S_SATA_2,
	PCI_DID_INTEL_ADP_S_SATA_3,
	PCI_DID_INTEL_ADP_S_SATA_4,
	PCI_DID_INTEL_ADP_S_SATA_5,
	PCI_DID_INTEL_ADP_S_SATA_6,
	PCI_DID_INTEL_ADP_M_SATA_1,
	PCI_DID_INTEL_ADP_M_SATA_2,
	PCI_DID_INTEL_ADP_M_SATA_3,
	0
};

static const struct pci_driver pch_sata __pci_driver = {
	.ops     = &sata_ops,
	.vendor  = PCI_VID_INTEL,
	.devices = pci_device_ids,
};
