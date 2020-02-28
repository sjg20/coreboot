/*
 * This file is part of the coreboot project.
 *
 * Copyright 2020 The coreboot project Authors.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include <stddef.h>
#include <boardid.h>
#include <ec/google/chromeec/ec.h>
#include <console/console.h>
#include <string.h>

#define SKU_UNKNOWN		0xFFFFFFFF

uint32_t google_chromeec_get_board_sku(void)
{
	MAYBE_STATIC_NONZERO uint32_t sku_id = SKU_UNKNOWN;

	if (sku_id != SKU_UNKNOWN)
		return sku_id;

	if (google_chromeec_cbi_get_sku_id(&sku_id))
		sku_id = SKU_UNKNOWN;

	return sku_id;
}

const char *google_chromeec_smbios_system_sku(void)
{
	static char sku_str[14]; /* sku{0..2147483647} */
	uint32_t sku_id = google_chromeec_get_board_sku();
	snprintf(sku_str, sizeof(sku_str), "sku%u", sku_id);
	return sku_str;
}
