/* SPDX-License-Identifier: GPL-2.0-only */
/* This file is part of the coreboot project. */

#include <baseboard/variants.h>
#include <bootblock_common.h>
#include <ec/ec.h>
#include <intelblocks/lpc_lib.h>
#include <soc/gpio.h>

void bootblock_mainboard_init(void)
{
	const struct pad_config *pads, *override_pads;
	size_t num, override_num;

	lpc_configure_pads();

	/*
	 * Perform EC init before configuring GPIOs. This is because variant
	 * might talk to the EC to get board id and hence it will require EC
	 * init to have already performed.
	 */
	mainboard_ec_init();

	pads = variant_early_gpio_table(&num);
	override_pads = variant_early_override_gpio_table(&override_num);
	gpio_configure_pads_with_override(pads, num,
			override_pads, override_num);
}
