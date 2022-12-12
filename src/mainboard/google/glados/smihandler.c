/* SPDX-License-Identifier: GPL-2.0-only */

#include <baseboard/variant.h>
#include <console/console.h>
#include <cpu/x86/smm.h>
#include <ec/google/chromeec/smm.h>
#include <gpio.h>
#include <soc/iomap.h>
#include <soc/pm.h>
#include <intelblocks/smihandler.h>
#include "ec.h"
#include <variant/gpio.h>

void mainboard_smi_gpi_handler(const struct gpi_status *sts)
{
	if (gpi_status_get(sts, EC_SMI_GPI))
		chromeec_smi_process_events();
}

__weak void mainboard_gpio_smi_sleep(void)
{
}

void mainboard_smi_sleep(u8 slp_typ)
{
	if (CONFIG(EC_GOOGLE_CHROMEEC))
		chromeec_smi_sleep(slp_typ, MAINBOARD_EC_S3_WAKE_EVENTS,
					MAINBOARD_EC_S5_WAKE_EVENTS);

	mainboard_gpio_smi_sleep();
}

int mainboard_smi_apmc(u8 apmc)
{
	if (CONFIG(EC_GOOGLE_CHROMEEC))
		chromeec_smi_apmc(apmc, MAINBOARD_EC_SCI_EVENTS,
					MAINBOARD_EC_SMI_EVENTS);
	return 0;
}
