/*
 * This file is part of the coreboot project.
 *
 * Copyright 2018 Google LLC
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
 * GNU General Public License for more details.
 */

#include <baseboard/gpio.h>
#include <baseboard/variants.h>
#include <boardid.h>
#include <gpio.h>
#include <soc/gpio.h>

static const struct pad_config default_override_table[] = {

	PAD_NC(GPIO_50, UP_20K),
	PAD_NC(GPIO_51, UP_20K),
	PAD_NC(GPIO_52, UP_20K),
	PAD_NC(GPIO_53, UP_20K),
	PAD_NC(GPIO_67, UP_20K),
	PAD_NC(GPIO_117, UP_20K),

	/* CAM_SOC_EC_SYNC */
	PAD_CFG_GPI_APIC_IOS(GPIO_134, NONE, DEEP, EDGE_SINGLE, INVERT, TxDRxE,
			     DISPUPD),

	PAD_NC(GPIO_138, DN_20K),
	PAD_NC(GPIO_139, DN_20K),
	PAD_NC(GPIO_140, UP_20K),
	PAD_NC(GPIO_143, UP_20K),
	PAD_NC(GPIO_144, UP_20K),
	PAD_NC(GPIO_145, UP_20K),

	/* EN_PP3300_TOUCHSCREEN */
	PAD_CFG_GPO_IOSSTATE_IOSTERM(GPIO_146, 0, DEEP, NONE, Tx0RxDCRx0,
					DISPUPD),

	PAD_NC(GPIO_161, UP_20K),

	/* EN_PP3300_WLAN_L */
	PAD_CFG_GPO_IOSSTATE_IOSTERM(GPIO_178, 0, DEEP, NONE, Tx0RxDCRx0, DISPUPD),

	PAD_NC(GPIO_213, DN_20K),
	PAD_NC(GPIO_214, DN_20K),
};

static const struct pad_config bid0_override_table[] = {
	PAD_NC(GPIO_50, UP_20K),
	PAD_NC(GPIO_51, UP_20K),
	PAD_NC(GPIO_52, UP_20K),
	PAD_NC(GPIO_53, UP_20K),
	PAD_NC(GPIO_67, UP_20K),
	PAD_NC(GPIO_117, UP_20K),
	PAD_NC(GPIO_138, DN_20K),
	PAD_NC(GPIO_139, DN_20K),
	PAD_NC(GPIO_140, UP_20K),
	PAD_NC(GPIO_143, UP_20K),
	PAD_NC(GPIO_144, UP_20K),
	PAD_NC(GPIO_145, UP_20K),
	PAD_NC(GPIO_161, UP_20K),
	PAD_NC(GPIO_214, DN_20K),
};

const struct pad_config *variant_override_gpio_table(size_t *num)
{
	const struct pad_config *c;

	switch (board_id()) {
	case 0:
	case UNDEFINED_STRAPPING_ID:
		c = bid0_override_table;
		*num = ARRAY_SIZE(bid0_override_table);
		break;
	default:
		c = default_override_table;
		*num = ARRAY_SIZE(default_override_table);
	}

	return c;
}
