/* SPDX-License-Identifier: GPL-2.0-only */
#include <assert.h>
#include <console/console.h>
#include <fsp/api.h>
#include <soc/romstage.h>
#include <spd_bin.h>
#include <string.h>
#include <soc/meminit.h>
#include <baseboard/variants.h>
#include <cbfs.h>

void mainboard_memory_init_params(FSPM_UPD *mupd)
{
	const struct mb_cfg *mem_config = variant_memory_params();
	const bool half_populated = false;

	const struct mem_spd lp5_spd_info = {
		.topo = MEM_TOPO_MEMORY_DOWN,
		.cbfs_index = variant_memory_sku(),
	};

	memcfg_init(&mupd->FspmConfig, mem_config, &lp5_spd_info, half_populated);
}
