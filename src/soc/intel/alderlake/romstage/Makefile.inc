# SPDX-License-Identifier: GPL-2.0-only

romstage-y += fsp_params.c
romstage-y += ../../../../cpu/intel/car/romstage.c
romstage-y += romstage.c
romstage-y += systemagent.c
romstage-$(CONFIG_EARLY_GFX_GMA) += graphics.c
romstage-y += ux.c
