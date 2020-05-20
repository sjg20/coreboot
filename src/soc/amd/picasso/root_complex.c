/* SPDX-License-Identifier: GPL-2.0-only */

#include <acpi/acpigen.h>
#include <cbmem.h>
#include <console/console.h>
#include <cpu/amd/msr.h>
#include <cpu/amd/mtrr.h>
#include <device/device.h>
#include <device/pci.h>
#include <device/pci_ids.h>
#include <fsp/util.h>
#include <stdint.h>

static void read_resources(struct device *dev)
{
	uint32_t mem_usable = (uintptr_t)cbmem_top();
	unsigned int idx = 0;
	const struct hob_header *hob = fsp_get_hob_list();
	const struct hob_resource *res;

	/* 0x0 - 0x9ffff */
	ram_resource(dev, idx++, 0, 0xa0000 / KiB);

	/* 0xa0000 - 0xbffff: legacy VGA */
	mmio_resource(dev, idx++, 0xa0000 / KiB, 0x20000 / KiB);

	/* 0xc0000 - 0xfffff: Option ROM */
	reserved_ram_resource(dev, idx++, 0xc0000 / KiB, 0x40000 / KiB);

	/* 1MB to top of low usable RAM */
	ram_resource(dev, idx++, 1 * MiB / KiB, (mem_usable - 1 * MiB) / KiB);

	mmconf_resource(dev, MMIO_CONF_BASE);

	if (!hob) {
		printk(BIOS_ERR, "Error: %s incomplete because no HOB list was found\n",
				__func__);
		return;
	}

	for (; hob->type != HOB_TYPE_END_OF_HOB_LIST; hob = fsp_next_hob(hob)) {

		if (hob->type != HOB_TYPE_RESOURCE_DESCRIPTOR)
			continue;

		res = fsp_hob_header_to_resource(hob);

		if (res->type == EFI_RESOURCE_SYSTEM_MEMORY && res->addr < mem_usable)
			continue; /* 0 through low usable was set above */
		if (res->type == EFI_RESOURCE_MEMORY_MAPPED_IO)
			continue; /* Done separately */

		if (res->type == EFI_RESOURCE_SYSTEM_MEMORY)
			ram_resource(dev, idx++, res->addr / KiB, res->length / KiB);
		else if (res->type == EFI_RESOURCE_MEMORY_RESERVED)
			reserved_ram_resource(dev, idx++, res->addr / KiB, res->length / KiB);
		else
			printk(BIOS_ERR, "Error: failed to set resources for type %d\n",
					res->type);
	}
}

/* Used by \_SB.PCI0._CRS */
static void root_complex_fill_ssdt(const struct device *device)
{
	msr_t msr;

	acpigen_write_scope(acpi_device_scope(device));

	msr = rdmsr(TOP_MEM);
	acpigen_write_name_dword("TOM1", msr.lo);
	msr = rdmsr(TOP_MEM2);
	/*
	 * Since XP only implements parts of ACPI 2.0, we can't use a qword
	 * here.
	 * See http://www.acpi.info/presentations/S01USMOBS169_OS%2520new.ppt
	 * slide 22ff.
	 * Shift value right by 20 bit to make it fit into 32bit,
	 * giving us 1MB granularity and a limit of almost 4Exabyte of memory.
	 */
	acpigen_write_name_dword("TOM2", (msr.hi << 12) | msr.lo >> 20);
	acpigen_pop_len();
}

static struct device_operations root_complex_operations = {
	.read_resources		= read_resources,
	.enable_resources	= pci_dev_enable_resources,
	.acpi_fill_ssdt		= root_complex_fill_ssdt,
};

static const struct pci_driver family17_root_complex __pci_driver = {
	.ops	= &root_complex_operations,
	.vendor	= PCI_VENDOR_ID_AMD,
	.device	= PCI_DEVICE_ID_AMD_17H_MODEL_101F_NB,
};
