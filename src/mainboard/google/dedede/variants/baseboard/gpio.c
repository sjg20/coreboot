/*
 * This file is part of the coreboot project.
 *
 * Copyright 2020 The coreboot project Authors.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include <baseboard/gpio.h>
#include <baseboard/variants.h>
#include <commonlib/helpers.h>

/* Pad configuration in ramstage*/
static const struct pad_config gpio_table[] = {
	/* ToDo: Fill gpio configuration */
};

/* Early pad configuration in bootblock */
static const struct pad_config early_gpio_table[] = {
	/* ToDo: Fill early gpio configuration */
};

const struct pad_config *__weak variant_gpio_table(size_t *num)
{
	*num = ARRAY_SIZE(gpio_table);
	return gpio_table;
}

const struct pad_config *__weak variant_early_gpio_table(size_t *num)
{
	*num = ARRAY_SIZE(early_gpio_table);
	return early_gpio_table;
}
