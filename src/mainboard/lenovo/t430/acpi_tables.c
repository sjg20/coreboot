/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2017 Patrick Rudolph <siro@das-labor.org>
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

#include <southbridge/intel/bd82x6x/nvs.h>

void acpi_create_gnvs(global_nvs_t *gnvs)
{
	/* The lid is open by default */
	gnvs->lids = 1;

	/* Config TDP Down */
	gnvs->f0of = 80;
	gnvs->f0on = 90;

	/* Temperature at which OS will shutdown */
	gnvs->tcrt = 100;
	/* Temperature at which OS will throttle CPU */
	gnvs->tpsv = 90;
	/* Tj_max value for calculating PECI CPU temperature */
	gnvs->tmax = 105;
}
