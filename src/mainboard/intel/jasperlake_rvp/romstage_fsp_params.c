/*
 * This file is part of the coreboot project.
 *
 * Copyright 2020 The coreboot project Authors
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
#include <baseboard/variants.h>
#include <console/console.h>
#include <soc/meminit_jsl.h>
#include <soc/romstage.h>
#include "board_id.h"

void mainboard_memory_init_params(FSPM_UPD *memupd)
{
	static struct spd_info jslrvp_spd_info;
	uint8_t board_id = get_board_id();
	const struct mb_cfg *board_cfg = variant_memcfg_config(board_id);

	/* TODO: Read the resistor strap to get number of memory segments */
	bool half_populated = false;

	/* Check board id and fill correct parameters to upd */
	if (board_id == jsl_ddr4) {
		/* Initialize spd information for DDR4 board */
		jslrvp_spd_info.read_type = READ_SMBUS;
		jslrvp_spd_info.spd_spec.spd_smbus_address[0] = 0xA0;
		jslrvp_spd_info.spd_spec.spd_smbus_address[1] = 0xA2;
		jslrvp_spd_info.spd_spec.spd_smbus_address[2] = 0xA4;
		jslrvp_spd_info.spd_spec.spd_smbus_address[3] = 0xA6;

	} else if (board_id == jsl_lpddr4) {
		/* Initialize spd information for LPDDR4 board */
		jslrvp_spd_info.read_type = READ_SPD_CBFS;
		jslrvp_spd_info.spd_spec.spd_index = 0x00;
	}

	/* Initialize variant specific configurations */
	memcfg_init(&memupd->FspmConfig, board_cfg, &jslrvp_spd_info, half_populated);
}
