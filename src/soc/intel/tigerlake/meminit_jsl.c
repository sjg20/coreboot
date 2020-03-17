/*
 * This file is part of the coreboot project.
 *
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
#include <console/console.h>
#include <fsp/util.h>
#include <soc/meminit_jsl.h>
#include <spd_bin.h>
#include <string.h>

static void spd_read_from_cbfs(const struct spd_info *spd_info, uintptr_t *spd_data_ptr,
				size_t *spd_data_len)
{
	struct region_device spd_rdev;
	size_t spd_index = spd_info->spd_spec.spd_index;

	printk(BIOS_DEBUG, "SPD INDEX = %lu\n", spd_index);
	if (get_spd_cbfs_rdev(&spd_rdev, spd_index) < 0)
		die("spd.bin not found or incorrect index\n");

	*spd_data_len = region_device_sz(&spd_rdev);

	/* Memory leak is ok since we have memory mapped boot media */
	assert(CONFIG(BOOT_DEVICE_MEMORY_MAPPED));

	*spd_data_ptr = (uintptr_t)rdev_mmap_full(&spd_rdev);
}

static void get_spd_data(const struct spd_info *spd_info, uintptr_t *spd_data_ptr,
				size_t *spd_data_len)
{
	if (spd_info->read_type == READ_SPD_MEMPTR) {
		*spd_data_ptr = spd_info->spd_spec.spd_data_ptr_info.spd_data_ptr;
		*spd_data_len = spd_info->spd_spec.spd_data_ptr_info.spd_data_len;
		return;
	}

	if (spd_info->read_type == READ_SPD_CBFS) {
		spd_read_from_cbfs(spd_info, spd_data_ptr, spd_data_len);
		return;
	}

	die("no valid way to read SPD info");
}

static void meminit_dq_dqs_map(FSP_M_CONFIG *mem_cfg, const struct mb_cfg *board_cfg,
				bool half_populated)
{
	memcpy(&mem_cfg->RcompResistor, &board_cfg->rcomp_resistor,
		sizeof(mem_cfg->RcompResistor));

	memcpy(&mem_cfg->RcompTarget, &board_cfg->rcomp_targets,
		sizeof(mem_cfg->RcompTarget));

	memcpy(&mem_cfg->DqByteMapCh0, &board_cfg->dq_map[DDR_CH0],
		sizeof(board_cfg->dq_map[DDR_CH0]));

	memcpy(&mem_cfg->DqsMapCpu2DramCh0, &board_cfg->dqs_map[DDR_CH0],
		sizeof(board_cfg->dqs_map[DDR_CH0]));

	if (half_populated)
		return;

	memcpy(&mem_cfg->DqByteMapCh1, &board_cfg->dq_map[DDR_CH1],
		sizeof(board_cfg->dq_map[DDR_CH1]));

	memcpy(&mem_cfg->DqsMapCpu2DramCh1, &board_cfg->dqs_map[DDR_CH1],
		sizeof(board_cfg->dqs_map[DDR_CH1]));
}

static void meminit_channels(FSP_M_CONFIG *mem_cfg, const struct mb_cfg *board_cfg,
				uintptr_t spd_data_ptr, bool half_populated)
{
	/* Channel 0 */
	mem_cfg->MemorySpdPtr00 = spd_data_ptr;
	mem_cfg->MemorySpdPtr01 = 0;

	if (half_populated) {
		printk(BIOS_INFO, "%s: DRAM half-populated\n", __func__);
		spd_data_ptr = 0;
	}

	/* Channel 1 */
	mem_cfg->MemorySpdPtr10 = spd_data_ptr;
	mem_cfg->MemorySpdPtr11 = 0;

	meminit_dq_dqs_map(mem_cfg, board_cfg, half_populated);
}

/* Initialize onboard memory configurations for lpddr4x */
void memcfg_init(FSP_M_CONFIG *mem_cfg, const struct mb_cfg *board_cfg,
			const struct spd_info *spd_info, bool half_populated)
{
	size_t spd_data_len;
	uintptr_t spd_data_ptr;

	memset(&mem_cfg->SpdAddressTable, 0, sizeof(mem_cfg->SpdAddressTable));
	get_spd_data(spd_info, &spd_data_ptr, &spd_data_len);
	print_spd_info((unsigned char *)spd_data_ptr);

	mem_cfg->MemorySpdDataLen = spd_data_len;
	meminit_channels(mem_cfg, board_cfg, spd_data_ptr, half_populated);

	/* Early Command Training Enabled */
	mem_cfg->ECT = board_cfg->ect;

	mem_cfg->UserBd = board_cfg->UserBd;
}
