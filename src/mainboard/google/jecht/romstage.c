/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2007-2010 coresystems GmbH
 * Copyright (C) 2014 Google Inc.
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

#include <bootmode.h>
#include <console/console.h>
#include <string.h>
#include <ec/google/chromeec/ec.h>
#include <soc/pei_data.h>
#include <soc/pei_wrapper.h>
#include <soc/romstage.h>
#include <superio/ite/common/ite.h>
#include <superio/ite/it8772f/it8772f.h>
#include <mainboard/google/jecht/spd/spd.h>
#include "onboard.h"


void mainboard_romstage_entry(struct romstage_params *rp)
{
	post_code(0x32);

	/* Fill out PEI DATA */
	mainboard_fill_pei_data(&rp->pei_data);
	mainboard_fill_spd_data(&rp->pei_data);

	/* Call into the real romstage main with this board's attributes. */
	romstage_common(rp);

	if (CONFIG(CHROMEOS))
		init_bootmode_straps();
}

void mainboard_pre_console_init(void)
{
	/* Early SuperIO setup */
	it8772f_ac_resume_southbridge(IT8772F_SUPERIO_DEV);
	ite_kill_watchdog(IT8772F_GPIO_DEV);
	ite_enable_serial(IT8772F_SERIAL_DEV, CONFIG_TTYS0_BASE);

	/* Turn On Power LED */
	set_power_led(LED_ON);

}
