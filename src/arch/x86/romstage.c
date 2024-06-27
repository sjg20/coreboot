/* SPDX-License-Identifier: GPL-2.0-only */

#include <arch/cpu.h>
#include <commonlib/ccb_api.h>
#include <console/console.h>
#include <timestamp.h>
#include <romstage_common.h>

asmlinkage void car_stage_entry(void)
{
	timestamp_add_now(TS_ROMSTAGE_START);

	ccb_init();

	/* Assumes the hardware was set up during the bootblock */
	console_init();

	ccb_check();

	romstage_main();
}
