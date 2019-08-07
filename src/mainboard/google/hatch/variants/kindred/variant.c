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

#include <baseboard/variants.h>
#include <chip.h>
#include <soc/pci_devs.h>
#include <ec/google/chromeec/ec.h>

void variant_devtree_update(void)
{
	uint32_t sku_id;
	struct device *emmc_host;
	config_t *cfg = config_of_path(SA_DEVFN_ROOT);
	emmc_host = pcidev_path_on_root(PCH_DEVFN_EMMC);

	if (emmc_host == NULL)
		return;

	/* SKU ID 1/3/23/24 doesn't have a eMMC device, hence disable it. */
	sku_id = get_board_sku();
	if (sku_id == 1 || sku_id == 3 || sku_id == 23 || sku_id == 24) {
		emmc_host->enabled = 0;
		cfg->ScsEmmcHs400Enabled = 0;
	}
}
