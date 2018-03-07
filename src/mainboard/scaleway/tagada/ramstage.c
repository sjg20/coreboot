/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2014 - 2017 Intel Corporation
 * Copyright (C) 2017 - 2018 Online SAS.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include <console/console.h>
#include <fsp/api.h>
#include <soc/ramstage.h>

#include "bmcinfo.h"

void mainboard_silicon_init_params(FSPS_UPD *params)
{
	/* Disable eMMC */
	params->FspsConfig.PcdEnableEmmc = 0;

	if (bmcinfo_disable_nic1())
		params->FspsConfig.PcdEnableGbE = 2; // disable lan 1 only
}
