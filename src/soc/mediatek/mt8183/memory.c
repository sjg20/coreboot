/*
 * This file is part of the coreboot project.
 *
 * Copyright 2018 MediaTek Inc.
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

#include <assert.h>
#include <cbfs.h>
#include <console/console.h>
#include <soc/dramc_param.h>
#include <soc/dramc_pi_api.h>
#include <soc/emi.h>
#include <string.h>
#include <symbols.h>

static void mt_mem_test(void)
{
	u64 rank_size[RANK_MAX];

	if (CONFIG(MEMORY_TEST)) {
		size_t r;
		u8 *addr = _dram;

		dramc_get_rank_size(rank_size);

		for (r = RANK_0; r < RANK_MAX; r++) {
			int i;

			if (rank_size[r] == 0)
				break;

			i = complex_mem_test(addr, 0x2000);

			printk(BIOS_DEBUG, "[MEM] complex R/W mem test %s : %d\n",
			       (i == 0) ? "pass" : "fail", i);

			ASSERT(i == 0);

			addr += rank_size[r];
		}
	}
}

static void dump_param_header(const struct dramc_param *dparam)
{
	const struct dramc_param_header *header = &dparam->header;

	printk(BIOS_DEBUG, "header.status = %#x\n", header->status);
	printk(BIOS_DEBUG, "header.magic = %#x (expected: %#x)\n",
	       header->magic, DRAMC_PARAM_HEADER_MAGIC);
	printk(BIOS_DEBUG, "header.version = %#x (expected: %#x)\n",
	       header->version, DRAMC_PARAM_HEADER_VERSION);
	printk(BIOS_DEBUG, "header.size = %#x (expected: %#lx)\n",
	       header->size, sizeof(*dparam));
	printk(BIOS_DEBUG, "header.config = %#x\n", header->config);
	printk(BIOS_DEBUG, "header.flags = %#x\n", header->flags);
	printk(BIOS_DEBUG, "header.checksum = %#x\n", header->checksum);
}

static int dram_run_fast_calibration(const struct dramc_param *dparam,
				     u16 config)
{
	if (!is_valid_dramc_param(dparam)) {
		printk(BIOS_WARNING,
		       "Invalid DRAM calibration data from flash\n");
		dump_param_header(dparam);
		return -1;
	}

	if (dparam->header.config != config)  {
		printk(BIOS_WARNING,
		       "Incompatible config for calibration data from flash "
		       "(expected: %#x, saved: %#x)\n",
		       config, dparam->header.config);
		return -1;
	}

	return 0;
}

static int dram_run_full_calibration(struct dramc_param *dparam, u16 config)
{
	initialize_dramc_param(dparam, config);

	/* Load and run the provided blob for full-calibration if available */
	struct prog dram = PROG_INIT(PROG_REFCODE, CONFIG_CBFS_PREFIX "/dram");

	if (prog_locate(&dram))
		return -1;

	if (cbfs_prog_stage_load(&dram))
		return -2;

	prog_set_entry(&dram, prog_entry(&dram), dparam);
	prog_run(&dram);

	if (dparam->header.status != DRAMC_SUCCESS) {
		printk(BIOS_ERR, "Full calibration failed: status = %d\n",
		       dparam->header.status);
		return -3;
	}

	if (!(dparam->header.flags & DRAMC_FLAG_HAS_SAVED_DATA)) {
		printk(BIOS_ERR,
		       "Full calibration executed without saving parameters. "
		       "Please ensure the blob is built properly.\n");
		return -4;
	}

	return 0;
}

static void set_source_to_flash(struct sdram_params *freq_params)
{
	for (u8 shuffle = DRAM_DFS_SHUFFLE_1; shuffle < DRAM_DFS_SHUFFLE_MAX;
	     shuffle++)
		freq_params[shuffle].source = DRAMC_PARAM_SOURCE_FLASH;
}

static void init_sdram_params(struct sdram_params *dst,
			      const struct sdram_params *src)
{
	for (u8 shuffle = DRAM_DFS_SHUFFLE_1; shuffle < DRAM_DFS_SHUFFLE_MAX;
	     shuffle++)
		memcpy(&dst[shuffle], src, sizeof(*dst));
}

void mt_mem_init(struct dramc_param_ops *dparam_ops)
{
	struct dramc_param *dparam = dparam_ops->param;

	u16 config = 0;
	if (CONFIG(MT8183_DRAM_EMCP))
		config |= DRAMC_CONFIG_EMCP;

	/* Load calibration params from flash and run fast calibration */
	if (dparam_ops->read_from_flash(dparam)) {
		if (dram_run_fast_calibration(dparam, config) == 0) {
			printk(BIOS_INFO,
			       "DRAM calibraion params loaded from flash\n");
			mt_set_emi(dparam);
			mt_mem_test();
			return;
		}
	} else {
		printk(BIOS_WARNING,
		       "Failed to read calibration data from flash\n");
	}

	/* Run full calibration */
	int err = dram_run_full_calibration(dparam, config);
	if (err == 0) {
		printk(BIOS_INFO, "Successfully loaded DRAM blobs and "
		       "ran DRAM calibration\n");
		set_source_to_flash(dparam->freq_params);
		dparam_ops->write_to_flash(dparam);
		printk(BIOS_DEBUG, "Calibration params saved to flash: "
		       "version=%#x, size=#%x\n",
		       dparam->header.version, dparam->header.size);
		return;
	}

	printk(BIOS_ERR, "Failed to do full calibration (%d), "
	       "falling back to load default sdram param\n", err);

	/* Init params from sdram configs and run partial calibration */
	init_sdram_params(dparam->freq_params, get_sdram_config());
	mt_set_emi(dparam);
	mt_mem_test();
}
