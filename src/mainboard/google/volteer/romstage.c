/*
 * This file is part of the coreboot project.
 *
 * Copyright 2020 The coreboot project Authors.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include <baseboard/variants.h>
#include <gpio.h>
#include <soc/gpio.h>
#include <soc/meminit_tgl.h>
#include <soc/romstage.h>
#include <variant/gpio.h>

#include <fsp/soc_binding.h>

void mainboard_memory_init_params(FSPM_UPD *mupd)
{
	FSP_M_CONFIG *mem_cfg = &mupd->FspmConfig;
	const struct mb_lpddr4x_cfg *board_cfg = variant_memory_params();
	const struct spd_info spd_info = {
		.read_type = READ_SPD_CBFS,
		.spd_spec.spd_index = variant_memory_sku(),
	};
	bool half_populated = gpio_get(GPIO_MEM_CH_SEL);

	meminit_lpddr4x_dimm0(mem_cfg, board_cfg, &spd_info, half_populated);
}
