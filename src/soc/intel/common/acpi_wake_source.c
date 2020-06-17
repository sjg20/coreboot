/* SPDX-License-Identifier: GPL-2.0-only */

#include <acpi/acpi.h>
#include <acpi/acpi_gnvs.h>
#include <bootstate.h>
#include <console/console.h>
#include <soc/nvs.h>
#include <stdint.h>
#include "acpi.h"

__weak int soc_fill_acpi_wake(uint32_t *pm1, uint32_t **gpe0)
{
	return -1;
}

/* Save wake source data for ACPI _SWS methods in NVS */
static void acpi_save_wake_source(void *unused)
{
	struct global_nvs *gnvs = acpi_get_gnvs();
	uint32_t pm1, *gpe0;
	int gpe_reg, gpe_reg_count;
	int reg_size = sizeof(uint32_t) * 8;

	if (!gnvs)
		return;

	gnvs->pm1i = -1;
	gnvs->gpei = -1;

	gpe_reg_count = soc_fill_acpi_wake(&pm1, &gpe0);
	if (gpe_reg_count < 0)
		return;

	/* Scan for first set bit in PM1 */
	for (gnvs->pm1i = 0; gnvs->pm1i < reg_size; gnvs->pm1i++) {
		if (pm1 & 1)
			break;
		pm1 >>= 1;
	}

	/* If unable to determine then return -1 */
	if (gnvs->pm1i >= 16)
		gnvs->pm1i = -1;

	/* Scan for first set bit in GPE registers */
	for (gpe_reg = 0; gpe_reg < gpe_reg_count; gpe_reg++) {
		uint32_t gpe = gpe0[gpe_reg];
		int start = gpe_reg * reg_size;
		int end = start + reg_size;

		if (gpe == 0) {
			if (!gnvs->gpei)
				gnvs->gpei = end;
			continue;
		}

		for (gnvs->gpei = start; gnvs->gpei < end; gnvs->gpei++) {
			if (gpe & 1)
				break;
			gpe >>= 1;
		}
	}

	/* If unable to determine then return -1 */
	if (gnvs->gpei >= gpe_reg_count * reg_size)
		gnvs->gpei = -1;

	printk(BIOS_DEBUG, "ACPI _SWS is PM1 Index %lld GPE Index %lld\n",
	       (long long)gnvs->pm1i, (long long)gnvs->gpei);
}

BOOT_STATE_INIT_ENTRY(BS_OS_RESUME, BS_ON_ENTRY, acpi_save_wake_source, NULL);
