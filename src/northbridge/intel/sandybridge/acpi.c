/* SPDX-License-Identifier: GPL-2.0-only */
/* This file is part of the coreboot project. */

#include <types.h>
#include <console/console.h>
#include <commonlib/helpers.h>
#include <acpi/acpi.h>
#include <device/device.h>
#include <device/pci_ops.h>
#include "sandybridge.h"
#include <southbridge/intel/bd82x6x/pch.h>

unsigned long acpi_fill_mcfg(unsigned long current)
{
	u32 pciexbar = 0;
	u32 pciexbar_reg;
	int max_buses;

	struct device *const dev = pcidev_on_root(0, 0);

	if (!dev)
		return current;

	pciexbar_reg = pci_read_config32(dev, PCIEXBAR);

	/* MMCFG not supported or not enabled */
	if (!(pciexbar_reg & (1 << 0)))
		return current;

	switch ((pciexbar_reg >> 1) & 3) {
	case 0: /* 256MB */
		pciexbar = pciexbar_reg & (0xffffffffULL << 28);
		max_buses = 256;
		break;
	case 1: /* 128M */
		pciexbar = pciexbar_reg & (0xffffffffULL << 27);
		max_buses = 128;
		break;
	case 2: /* 64M */
		pciexbar = pciexbar_reg & (0xffffffffULL << 26);
		max_buses = 64;
		break;
	default: /* RSVD */
		return current;
	}

	if (!pciexbar)
		return current;

	current += acpi_create_mcfg_mmconfig((acpi_mcfg_mmconfig_t *) current, pciexbar, 0, 0,
			max_buses - 1);

	return current;
}


static unsigned long acpi_create_igfx_rmrr(const unsigned long current)
{
	const u32 base_mask = ~(u32)(MiB - 1);

	struct device *const host = pcidev_on_root(0, 0);
	if (!host)
		return 0;

	const u32 bgsm  = pci_read_config32(host,  BGSM) & base_mask;
	const u32 tolud = pci_read_config32(host, TOLUD) & base_mask;
	if (!bgsm || !tolud)
		return 0;

	return acpi_create_dmar_rmrr(current, 0, bgsm, tolud - 1);
}

static unsigned long acpi_fill_dmar(unsigned long current)
{
	const struct device *const igfx = pcidev_on_root(2, 0);

	if (igfx && igfx->enabled) {
		unsigned long tmp;

		tmp = current;
		current += acpi_create_dmar_drhd(current, 0, 0, GFXVT_BASE);
		current += acpi_create_dmar_ds_pci(current, 0, 2, 0);
		current += acpi_create_dmar_ds_pci(current, 0, 2, 1);
		acpi_dmar_drhd_fixup(tmp, current);

		tmp = current;
		current += acpi_create_igfx_rmrr(current);
		if (current != tmp) {
			current += acpi_create_dmar_ds_pci(current, 0, 2, 0);
			current += acpi_create_dmar_ds_pci(current, 0, 2, 1);
			acpi_dmar_rmrr_fixup(tmp, current);
		}
	}

	const unsigned long tmp = current;
	current += acpi_create_dmar_drhd(current, DRHD_INCLUDE_PCI_ALL, 0, VTVC0_BASE);

	current += acpi_create_dmar_ds_ioapic(current, 2, PCH_IOAPIC_PCI_BUS,
			PCH_IOAPIC_PCI_SLOT, 0);

	size_t i;
	for (i = 0; i < 8; ++i)
		current += acpi_create_dmar_ds_msi_hpet(current, 0, PCH_HPET_PCI_BUS,
				PCH_HPET_PCI_SLOT, i);

	acpi_dmar_drhd_fixup(tmp, current);

	return current;
}

unsigned long northbridge_write_acpi_tables(const struct device *const dev,
					    unsigned long current,
					    struct acpi_rsdp *const rsdp)
{
	const u32 capid0_a = pci_read_config32(dev, CAPID0_A);
	if (capid0_a & (1 << 23))
		return current;

	printk(BIOS_DEBUG, "ACPI:     * DMAR\n");

	acpi_dmar_t *const dmar = (acpi_dmar_t *)current;

	acpi_create_dmar(dmar, DMAR_INTR_REMAP, acpi_fill_dmar);
	current += dmar->header.length;
	current = acpi_align_current(current);

	acpi_add_table(rsdp, dmar);
	current = acpi_align_current(current);

	printk(BIOS_DEBUG, "current = %lx\n", current);

	return current;
}
