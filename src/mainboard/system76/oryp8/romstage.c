/* SPDX-License-Identifier: GPL-2.0-only */

#include <fsp/util.h>
#include <soc/meminit.h>
#include <soc/romstage.h>

static const struct mb_cfg board_cfg = {
	.type = MEM_TYPE_DDR4,
	.ddr4_config = {
		.dq_pins_interleaved = true,
	},
};

static const struct mem_spd spd_info = {
	.topo = MEM_TOPO_DIMM_MODULE,
	.smbus = {
		[0] = { .addr_dimm[0] = 0x50, },
		[1] = { .addr_dimm[0] = 0x52, },
	},
};

void mainboard_memory_init_params(FSPM_UPD *mupd)
{
	const bool half_populated = false;

	// Enable M.2 PCIE 4.0 and PEG1
	mupd->FspmConfig.CpuPcieRpEnableMask = 0x3;

	memcfg_init(mupd, &board_cfg, &spd_info, half_populated);
}
