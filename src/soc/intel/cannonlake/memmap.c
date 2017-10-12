/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2014 Google Inc.
 * Copyright (C) 2015-2017 Intel Corporation.
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
#include <arch/io.h>
#include <cbmem.h>
#include <chip.h>
#include <console/console.h>
#include <device/device.h>
#include <device/pci.h>
#include <fsp/util.h>
#include <intelblocks/systemagent.h>
#include <soc/bootblock.h>
#include <soc/pci_devs.h>
#include <soc/smm.h>
#include <soc/systemagent.h>
#include <stdlib.h>

void smm_region(void **start, size_t *size)
{
	*start = (void *)sa_get_tseg_base();
	*size = sa_get_tseg_size();
}

/*
 *        Subregions within SMM
 *     +-------------------------+ BGSM
 *     |          IED            | IED_REGION_SIZE
 *     +-------------------------+
 *     |  External Stage Cache   | SMM_RESERVED_SIZE
 *     +-------------------------+
 *     |      code and data      |
 *     |         (TSEG)          |
 *     +-------------------------+ TSEG
 */
int smm_subregion(int sub, void **start, size_t *size)
{
	uintptr_t sub_base;
	size_t sub_size;
	void *smm_base;
	const size_t ied_size = CONFIG_IED_REGION_SIZE;
	const size_t cache_size = CONFIG_SMM_RESERVED_SIZE;

	smm_region(&smm_base, &sub_size);
	sub_base = (uintptr_t)smm_base;

	switch (sub) {
	case SMM_SUBREGION_HANDLER:
		/* Handler starts at the base of TSEG. */
		sub_size -= ied_size;
		sub_size -= cache_size;
		break;
	case SMM_SUBREGION_CACHE:
		/* External cache is in the middle of TSEG. */
		sub_base += sub_size - (ied_size + cache_size);
		sub_size = cache_size;
		break;
	case SMM_SUBREGION_CHIPSET:
		/* IED is at the top. */
		sub_base += sub_size - ied_size;
		sub_size = ied_size;
		break;
	default:
		return -1;
	}

	*start = (void *)sub_base;
	*size = sub_size;

	return 0;
}

static void *top_of_ram_register(void)
{
	int num;
	int offset;
	num = (read32((uintptr_t *)HPET_BASE_ADDRESS) >> 8) & 0x1f;
	offset = 0x100 + (0x20 * num) + 0x08;
	return (void *)(uintptr_t)(HPET_BASE_ADDRESS + offset);
}

void clear_cbmem_top(void)
{
	write32(top_of_ram_register(), 0);
}

static bool is_ptt_enable(void)
{
	if ((read32((void *)PTT_TXT_BASE_ADDRESS) & PTT_PRESENT) ==
			PTT_PRESENT)
		return true;

	return false;
}

/* Calculate PTT size */
static size_t get_ptt_size(void)
{
	/* Allocate 4KB for PTT if enabled */
	return is_ptt_enable() ? 4*KiB : 0;
}

/* Calculate ME Stolen size */
static size_t get_imr_size(void)
{
	size_t imr_size;

	/* ME stolen memory */
	imr_size = MCHBAR32(IMRLIMIT) - MCHBAR32(IMRBASE);

	return imr_size;
}

/* Calculate PRMRR size based on user input PRMRR size and alignment */
static size_t get_prmrr_size(uintptr_t dram_base,
		const struct soc_intel_cannonlake_config *config)
{
	uintptr_t prmrr_base = dram_base;
	size_t prmrr_size;

	prmrr_size = config->PrmrrSize;

	/* Allocate PRMRR memory for C6DRAM */
	if (!prmrr_size) {
		if (config->enable_c6dram)
			prmrr_size = 1*MiB;
		else
			return 0;
	}

	/*
	 * PRMRR Sizes that are > 1MB and < 32MB are
	 * not supported and will fail out.
	 */
	if ((prmrr_size > 1*MiB) && (prmrr_size < 32*MiB))
		die("PRMRR Sizes that are > 1MB and < 32MB are not"
				"supported!\n");

	prmrr_base -= prmrr_size;
	if (prmrr_size >= 32*MiB)
		prmrr_base = ALIGN_DOWN(prmrr_base, 128*MiB);
	else
		prmrr_base = ALIGN_DOWN(prmrr_base, 16*MiB);
	/* PRMRR Area Size */
	prmrr_size = dram_base - prmrr_base;

	return prmrr_size;
}

/* Calculate Intel Traditional Memory size based on GSM, DSM, TSEG and DPR. */
static size_t calculate_traditional_mem_size(uintptr_t dram_base,
		const struct device *dev)
{
	uintptr_t traditional_mem_base = dram_base;
	size_t traditional_mem_size;

	if (dev->enabled) {
		/* Read BDSM from Host Bridge */
		traditional_mem_base -= sa_get_dsm_size();

		/* Read BGSM from Host Bridge */
		traditional_mem_base -= sa_get_gsm_size();
	}
	/* Get TSEG size */
	traditional_mem_base -= sa_get_tseg_size();

	/* Get DPR size */
	if (IS_ENABLED(CONFIG_SA_ENABLE_DPR))
		traditional_mem_base -= sa_get_dpr_size();

	/* Traditional Area Size */
	traditional_mem_size = dram_base - traditional_mem_base;

	return traditional_mem_size;
}

/*
 * Calculate Intel Reserved Memory size based on
 * PRMRR size, Me stolen memory and PTT selection.
 */
static size_t calculate_reserved_mem_size(uintptr_t dram_base,
		const struct device *dev)
{
	uintptr_t reserve_mem_base = dram_base;
	size_t reserve_mem_size;
	const struct soc_intel_cannonlake_config *config;

	config = dev->chip_info;

	/* Get PRMRR size */
	reserve_mem_base -= get_prmrr_size(reserve_mem_base, config);

	/* Get Tracehub size */
	reserve_mem_base -= get_imr_size();

	/* Get PTT size */
	reserve_mem_base -= get_ptt_size();

	/* Traditional Area Size */
	reserve_mem_size = dram_base - reserve_mem_base;

	return reserve_mem_size;
}

/*
 * Host Memory Map:
 *
 * +--------------------------+ TOUUD
 * |                          |
 * +--------------------------+ 4GiB
 * |     PCI Address Space    |
 * +--------------------------+ TOLUD (also maps into MC address space)
 * |     iGD                  |
 * +--------------------------+ BDSM
 * |     GTT                  |
 * +--------------------------+ BGSM
 * |     TSEG                 |
 * +--------------------------+ TSEGMB
 * |   DMA Protected Region   |
 * +--------------------------+ DPR
 * |    PRM (C6DRAM/SGX)      |
 * +--------------------------+ PRMRR
 * |     ME Stolen Memory     |
 * +--------------------------+ ME Stolen
 * |     PTT                  |
 * +--------------------------+ top_of_ram
 * |     Reserved - FSP/CBMEM |
 * +--------------------------+ TOLUM
 * |     Usage DRAM           |
 * +--------------------------+ 0
 *
 * Some of the base registers above can be equal making the size of those
 * regions 0. The reason is because the memory controller internally subtracts
 * the base registers from each other to determine sizes of the regions. In
 * other words, the memory map is in a fixed order no matter what.
 */
static uintptr_t calculate_dram_base(size_t *reserved_mem_size)
{
	uintptr_t dram_base;
	const struct device *dev;

	dev = dev_find_slot(0, PCI_DEVFN(SA_DEV_SLOT_IGD, 0));
	if (!dev)
		die("ERROR - IGD device not found!");

	/* Read TOLUD from Host Bridge offset */
	dram_base = sa_get_tolud_base();

	/* Get Intel Traditional Memory Range Size */
	dram_base -= calculate_traditional_mem_size(dram_base, dev);

	/* Get Intel Reserved Memory Range Size */
	*reserved_mem_size = calculate_reserved_mem_size(dram_base, dev);

	dram_base -= *reserved_mem_size;

	return dram_base;
}

void cbmem_top_init(void)
{
	uintptr_t top;
	size_t chipset_mem_size;

	top = calculate_dram_base(&chipset_mem_size);

	write32(top_of_ram_register(), top);
}

void *cbmem_top(void)
{
	/*
	 *     +-------------------------+  Top of RAM (aligned)
	 *     | System Management Mode  |
	 *     |      code and data      |  Length: CONFIG_TSEG_SIZE
	 *     |         (TSEG)          |
	 *     +-------------------------+  SMM base (aligned)
	 *     |                         |
	 *     | Chipset Reserved Memory |
	 *     |                         |
	 *     +-------------------------+  top_of_ram (aligned)
	 *     |                         |
	 *     |       CBMEM Root        |
	 *     |                         |
	 *     +-------------------------+
	 *     |                         |
	 *     |   FSP Reserved Memory   |
	 *     |                         |
	 *     +-------------------------+
	 *     |                         |
	 *     |  Various CBMEM Entries  |
	 *     |                         |
	 *     +-------------------------+  top_of_stack (8 byte aligned)
	 *     |                         |
	 *     |   stack (CBMEM Entry)   |
	 *     |                         |
	 *     +-------------------------+
	 */
	return (void *)(uintptr_t)read32(top_of_ram_register());
}
