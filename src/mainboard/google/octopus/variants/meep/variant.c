/*
 * This file is part of the coreboot project.
 *
 * Copyright 2019 Google LLC
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

#include <ec/google/chromeec/ec.h>
#include <drivers/intel/gma/opregion.h>
#include <baseboard/variants.h>
#include <variant/sku.h>
#include <sar.h>

const char *get_wifi_sar_cbfs_filename(void)
{
	const char *filename = NULL;
	uint32_t sku_id = get_board_sku();

	switch (sku_id) {
	case SKU_4_VORTININJA:
	case SKU_5_VORTININJA:
	case SKU_6_VORTININJA:
	case SKU_7_VORTININJA:
		filename = "wifi_sar-vortininja.hex";
		break;
	}
	return filename;
}

const char *mainboard_vbt_filename(void)
{
	uint32_t sku_id;

	sku_id = get_board_sku();

	switch (sku_id) {
	case SKU_33_DORP:
	case SKU_34_DORP:
	case SKU_35_DORP:
	case SKU_36_DORP:
		return "vbt_dorp_hdmi.bin";
	default:
		return "vbt.bin";
	}
}
