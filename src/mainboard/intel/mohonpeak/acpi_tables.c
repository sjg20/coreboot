/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2012 The Chromium OS Authors. All rights reserved.
 * Copyright (C) 2013 Sage Electronic Engineering, LLC.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 */

#include <types.h>
#include <string.h>
#include <cbmem.h>
#include <console/console.h>
#include <arch/acpi.h>
#include <arch/ioapic.h>
#include <arch/acpigen.h>
#include <arch/smp/mpspec.h>
#include <device/device.h>
#include <device/pci.h>
#include <device/pci_ids.h>
#include <cpu/x86/msr.h>
#include <southbridge/intel/fsp_rangeley/nvs.h>
#include <northbridge/intel/fsp_rangeley/northbridge.h>

extern const unsigned char AmlCode[];
#if CONFIG_HAVE_ACPI_SLIC
unsigned long acpi_create_slic(unsigned long current);
#endif

static global_nvs_t *gnvs_;

static void acpi_create_gnvs(global_nvs_t *gnvs)
{
	gnvs_ = gnvs;
	memset((void *)gnvs, 0, sizeof(*gnvs));
	gnvs->apic = 1;
	gnvs->mpen = 1; /* Enable Multi Processing */
	gnvs->pcnt = dev_count_cpu();

	/* Enable USB ports in S3 */
	gnvs->s3u0 = 1;
	gnvs->s3u1 = 1;

	/*
	 * Enable Front USB ports in S5 by default
	 * to be consistent with back port behavior
	 */
	gnvs->s5u0 = 1;
	gnvs->s5u1 = 1;

	/* CBMEM TOC */
	gnvs->cmem = (u32)get_cbmem_toc();

	/* IGD Displays */
	gnvs->ndid = 3;
	gnvs->did[0] = 0x80000100;
	gnvs->did[1] = 0x80000240;
	gnvs->did[2] = 0x80000410;
	gnvs->did[3] = 0x80000410;
	gnvs->did[4] = 0x00000005;

}

unsigned long acpi_fill_madt(unsigned long current)
{
	/* Local APICs */
	current = acpi_create_madt_lapics(current);

	/* IOAPIC */
	current += acpi_create_madt_ioapic((acpi_madt_ioapic_t *) current,
				2, IO_APIC_ADDR, 0);

	/* INT_SRC_OVR */
	current += acpi_create_madt_irqoverride((acpi_madt_irqoverride_t *)
		 current, 0, 0, 2, 0);
	current += acpi_create_madt_irqoverride((acpi_madt_irqoverride_t *)
		 current, 0, 9, 9, MP_IRQ_TRIGGER_LEVEL | MP_IRQ_POLARITY_HIGH);

	return current;
}

unsigned long acpi_fill_ssdt_generator(unsigned long current,
					const char *oem_table_id)
{
	u32 lens, bmbound;
	char pscope[] = "\\_SB.PCI0";

	bmbound = sideband_read(B_UNIT, BMBOUND);
	lens = acpigen_write_scope(pscope);
	lens += acpigen_write_name_dword("BMBD", bmbound);
	generate_cpu_entries();
	acpigen_patch_len(lens - 1);
	return (unsigned long) (acpigen_get_current());
}

unsigned long acpi_fill_slit(unsigned long current)
{
	// Not implemented
	return current;
}

unsigned long acpi_fill_srat(unsigned long current)
{
	/* No NUMA, no SRAT */
	return current;
}

void smm_setup_structures(void *gnvs, void *tcg, void *smi1);

#define ALIGN_CURRENT current = (ALIGN(current, 16))
unsigned long write_acpi_tables(unsigned long start)
{
	unsigned long current;
	int i;
	acpi_rsdp_t *rsdp;
	acpi_rsdt_t *rsdt;
	acpi_xsdt_t *xsdt;
	acpi_hpet_t *hpet;
	acpi_madt_t *madt;
	acpi_mcfg_t *mcfg;
	acpi_fadt_t *fadt;
	acpi_facs_t *facs;
#if CONFIG_HAVE_ACPI_SLIC
	acpi_header_t *slic;
#endif
	acpi_header_t *ssdt;
	acpi_header_t *dsdt;

	current = start;

	/* Align ACPI tables to 16byte */
	ALIGN_CURRENT;

	printk(BIOS_INFO, "ACPI: Writing ACPI tables at %lx.\n", start);

	/* We need at least an RSDP and an RSDT Table */
	rsdp = (acpi_rsdp_t *) current;
	current += sizeof(acpi_rsdp_t);
	ALIGN_CURRENT;
	rsdt = (acpi_rsdt_t *) current;
	current += sizeof(acpi_rsdt_t);
	ALIGN_CURRENT;
	xsdt = (acpi_xsdt_t *) current;
	current += sizeof(acpi_xsdt_t);
	ALIGN_CURRENT;

	/* clear all table memory */
	memset((void *) start, 0, current - start);

	acpi_write_rsdp(rsdp, rsdt, xsdt);
	acpi_write_rsdt(rsdt);
	acpi_write_xsdt(xsdt);

	printk(BIOS_DEBUG, "ACPI:    * FACS\n");
	facs = (acpi_facs_t *) current;
	current += sizeof(acpi_facs_t);
	ALIGN_CURRENT;
	acpi_create_facs(facs);

	printk(BIOS_DEBUG, "ACPI:    * DSDT\n");
	dsdt = (acpi_header_t *) current;
	memcpy(dsdt, &AmlCode, sizeof(acpi_header_t));
	current += dsdt->length;
	memcpy(dsdt, &AmlCode, dsdt->length);

	ALIGN_CURRENT;

	printk(BIOS_DEBUG, "ACPI:    * FADT\n");
	fadt = (acpi_fadt_t *) current;
	current += sizeof(acpi_fadt_t);
	ALIGN_CURRENT;

	acpi_create_fadt(fadt, facs, dsdt);
	acpi_add_table(rsdp, fadt);

	/*
	 * We explicitly add these tables later on:
	 */
	printk(BIOS_DEBUG, "ACPI:    * HPET\n");

	hpet = (acpi_hpet_t *) current;
	current += sizeof(acpi_hpet_t);
	ALIGN_CURRENT;
	acpi_create_hpet(hpet);
	acpi_add_table(rsdp, hpet);

	/* If we want to use HPET Timers Linux wants an MADT */
	printk(BIOS_DEBUG, "ACPI:    * MADT\n");

	madt = (acpi_madt_t *) current;
	acpi_create_madt(madt);
	current += madt->header.length;
	ALIGN_CURRENT;
	acpi_add_table(rsdp, madt);

	printk(BIOS_DEBUG, "ACPI:    * MCFG\n");
	mcfg = (acpi_mcfg_t *) current;
	acpi_create_mcfg(mcfg);
	current += mcfg->header.length;
	ALIGN_CURRENT;
	acpi_add_table(rsdp, mcfg);

	/* Pack GNVS into the ACPI table area */
	for (i=0; i < dsdt->length; i++) {
		if (*(u32*)(((u32)dsdt) + i) == 0xC0DEBABE) {
			printk(BIOS_DEBUG, "ACPI: Patching up global NVS in "
			     "DSDT at offset 0x%04x -> 0x%08lx\n", i, current);
			*(u32*)(((u32)dsdt) + i) = current; // 0x92 bytes
			acpi_save_gnvs(current);
			break;
		}
	}

	/* And fill it */
	acpi_create_gnvs((global_nvs_t *)current);

	/* And tell SMI about it */
#if CONFIG_HAVE_SMI_HANDLER
	smm_setup_structures((void *)current, NULL, NULL);
#endif

	current += sizeof(global_nvs_t);
	ALIGN_CURRENT;

	/* We patched up the DSDT, so we need to recalculate the checksum */
	dsdt->checksum = 0;
	dsdt->checksum = acpi_checksum((void *)dsdt, dsdt->length);

	printk(BIOS_DEBUG, "ACPI:     * DSDT @ %p Length %x\n", dsdt,
		     dsdt->length);

#if CONFIG_HAVE_ACPI_SLIC
	printk(BIOS_DEBUG, "ACPI:     * SLIC\n");
	slic = (acpi_header_t *)current;
	current += acpi_create_slic(current);
	ALIGN_CURRENT;
	acpi_add_table(rsdp, slic);
#endif

	printk(BIOS_DEBUG, "ACPI:     * SSDT\n");
	ssdt = (acpi_header_t *)current;
	acpi_create_ssdt_generator(ssdt, ACPI_TABLE_CREATOR);
	current += ssdt->length;
	acpi_add_table(rsdp, ssdt);
	ALIGN_CURRENT;

	printk(BIOS_DEBUG, "current = %lx\n", current);
	printk(BIOS_INFO, "ACPI: done.\n");
	return current;
}
