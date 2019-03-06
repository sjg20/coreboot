/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2008-2009 coresystems GmbH
 * Copyright (C) 2014 Vladimir Serbinenko
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; version 2 of
 * the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <southbridge/intel/common/gpio.h>

static const struct pch_gpio_set1 pch_gpio_set1_mode = {
	.gpio0 = GPIO_MODE_GPIO,
	.gpio1 = GPIO_MODE_GPIO,
	.gpio2 = GPIO_MODE_GPIO,
	.gpio3 = GPIO_MODE_GPIO,
	.gpio4 = GPIO_MODE_GPIO,
	.gpio5 = GPIO_MODE_GPIO,
	.gpio6 = GPIO_MODE_GPIO,
	.gpio7 = GPIO_MODE_GPIO,
	.gpio8 = GPIO_MODE_GPIO,
	.gpio9 = GPIO_MODE_NATIVE,
	.gpio10 = GPIO_MODE_NATIVE,
	.gpio11 = GPIO_MODE_GPIO,
	.gpio12 = GPIO_MODE_NATIVE,
	.gpio13 = GPIO_MODE_NATIVE,
	.gpio14 = GPIO_MODE_GPIO,
	.gpio15 = GPIO_MODE_GPIO,
	.gpio16 = GPIO_MODE_NATIVE,
	.gpio17 = GPIO_MODE_GPIO,
	.gpio18 = GPIO_MODE_NATIVE,
	.gpio19 = GPIO_MODE_NATIVE,
	.gpio20 = GPIO_MODE_NATIVE,
	.gpio21 = GPIO_MODE_NATIVE,
	.gpio22 = GPIO_MODE_NATIVE,
	.gpio23 = GPIO_MODE_NATIVE,
	.gpio24 = GPIO_MODE_GPIO,
	.gpio25 = GPIO_MODE_NATIVE,
	.gpio26 = GPIO_MODE_NATIVE,
	.gpio27 = GPIO_MODE_GPIO,
	.gpio28 = GPIO_MODE_GPIO,
	.gpio29 = GPIO_MODE_GPIO,
	.gpio30 = GPIO_MODE_NATIVE,
	.gpio31 = GPIO_MODE_GPIO,
};

static const struct pch_gpio_set1 pch_gpio_set1_direction = {
	.gpio0 = GPIO_DIR_INPUT,
	.gpio1 = GPIO_DIR_INPUT,
	.gpio2 = GPIO_DIR_INPUT,
	.gpio3 = GPIO_DIR_INPUT,
	.gpio4 = GPIO_DIR_INPUT,
	.gpio5 = GPIO_DIR_INPUT,
	.gpio6 = GPIO_DIR_INPUT,
	.gpio7 = GPIO_DIR_INPUT,
	.gpio8 = GPIO_DIR_OUTPUT,
	.gpio11 = GPIO_DIR_INPUT,
	.gpio14 = GPIO_DIR_INPUT,
	.gpio15 = GPIO_DIR_INPUT,
	.gpio17 = GPIO_DIR_INPUT,
	.gpio24 = GPIO_DIR_OUTPUT,
	.gpio27 = GPIO_DIR_OUTPUT,
	.gpio28 = GPIO_DIR_OUTPUT,
	.gpio29 = GPIO_DIR_OUTPUT,
	.gpio31 = GPIO_DIR_INPUT,
};

static const struct pch_gpio_set1 pch_gpio_set1_level = {
	#if CONFIG(ENABLE_MSATA)
		.gpio8 = GPIO_LEVEL_LOW,
	#else
		.gpio8 = GPIO_LEVEL_HIGH,
	#endif
	.gpio24 = GPIO_LEVEL_LOW,
	.gpio27 = GPIO_LEVEL_LOW,
	.gpio28 = GPIO_LEVEL_LOW,
	.gpio29 = GPIO_LEVEL_HIGH,
};

static const struct pch_gpio_set1 pch_gpio_set1_reset = {
	.gpio24 = GPIO_RESET_RSMRST,
};

static const struct pch_gpio_set1 pch_gpio_set1_invert = {
	.gpio1 = GPIO_INVERT,
	.gpio7 = GPIO_INVERT,
	.gpio14 = GPIO_INVERT,
	.gpio15 = GPIO_INVERT,
};

static const struct pch_gpio_set1 pch_gpio_set1_blink = {
};

static const struct pch_gpio_set2 pch_gpio_set2_mode = {
	.gpio32 = GPIO_MODE_NATIVE,
	.gpio33 = GPIO_MODE_NATIVE,
	.gpio34 = GPIO_MODE_GPIO,
	.gpio35 = GPIO_MODE_NATIVE,
	.gpio36 = GPIO_MODE_NATIVE,
	.gpio37 = GPIO_MODE_GPIO,
	.gpio38 = GPIO_MODE_NATIVE,
	.gpio39 = GPIO_MODE_NATIVE,
	.gpio40 = GPIO_MODE_NATIVE,
	.gpio41 = GPIO_MODE_NATIVE,
	.gpio42 = GPIO_MODE_NATIVE,
	.gpio43 = GPIO_MODE_NATIVE,
	.gpio44 = GPIO_MODE_NATIVE,
	.gpio45 = GPIO_MODE_NATIVE,
	.gpio46 = GPIO_MODE_GPIO,
	.gpio47 = GPIO_MODE_NATIVE,
	.gpio48 = GPIO_MODE_NATIVE,
	.gpio49 = GPIO_MODE_GPIO,
	.gpio50 = GPIO_MODE_GPIO,
	.gpio51 = GPIO_MODE_GPIO,
	.gpio52 = GPIO_MODE_GPIO,
	.gpio53 = GPIO_MODE_GPIO,
	.gpio54 = GPIO_MODE_GPIO,
	.gpio55 = GPIO_MODE_GPIO,
	.gpio56 = GPIO_MODE_NATIVE,
	.gpio57 = GPIO_MODE_GPIO,
	.gpio58 = GPIO_MODE_NATIVE,
	.gpio59 = GPIO_MODE_NATIVE,
	.gpio60 = GPIO_MODE_GPIO,
	.gpio61 = GPIO_MODE_NATIVE,
	.gpio62 = GPIO_MODE_NATIVE,
	.gpio63 = GPIO_MODE_NATIVE,
};

static const struct pch_gpio_set2 pch_gpio_set2_direction = {
	.gpio34 = GPIO_DIR_OUTPUT,
	.gpio37 = GPIO_DIR_OUTPUT,
	.gpio46 = GPIO_DIR_OUTPUT,
	.gpio49 = GPIO_DIR_INPUT,
	.gpio50 = GPIO_DIR_OUTPUT,
	.gpio51 = GPIO_DIR_OUTPUT,
	.gpio52 = GPIO_DIR_OUTPUT,
	.gpio53 = GPIO_DIR_OUTPUT,
	.gpio54 = GPIO_DIR_OUTPUT,
	.gpio55 = GPIO_DIR_OUTPUT,
	.gpio57 = GPIO_DIR_INPUT,
	.gpio60 = GPIO_DIR_OUTPUT,
};

static const struct pch_gpio_set2 pch_gpio_set2_level = {
	.gpio34 = GPIO_LEVEL_HIGH,
	.gpio37 = GPIO_LEVEL_LOW,
	.gpio46 = GPIO_LEVEL_HIGH,
	.gpio50 = GPIO_LEVEL_HIGH,
	.gpio51 = GPIO_LEVEL_LOW,
	.gpio52 = GPIO_LEVEL_HIGH,
	.gpio53 = GPIO_LEVEL_HIGH,
	.gpio54 = GPIO_LEVEL_HIGH,
	.gpio55 = GPIO_LEVEL_LOW,
	.gpio60 = GPIO_LEVEL_HIGH,
};

static const struct pch_gpio_set2 pch_gpio_set2_reset = {
};

static const struct pch_gpio_set3 pch_gpio_set3_mode = {
	.gpio64 = GPIO_MODE_NATIVE,
	.gpio65 = GPIO_MODE_NATIVE,
	.gpio66 = GPIO_MODE_GPIO,
	.gpio67 = GPIO_MODE_GPIO,
	.gpio68 = GPIO_MODE_GPIO,
	.gpio69 = GPIO_MODE_GPIO,
	.gpio70 = GPIO_MODE_NATIVE,
	.gpio71 = GPIO_MODE_NATIVE,
	.gpio72 = GPIO_MODE_NATIVE,
	.gpio73 = GPIO_MODE_NATIVE,
	.gpio74 = GPIO_MODE_NATIVE,
	.gpio75 = GPIO_MODE_NATIVE,
};

static const struct pch_gpio_set3 pch_gpio_set3_direction = {
	.gpio66 = GPIO_DIR_OUTPUT,
	.gpio67 = GPIO_DIR_INPUT,
	.gpio68 = GPIO_DIR_OUTPUT,
	.gpio69 = GPIO_DIR_INPUT,
};

static const struct pch_gpio_set3 pch_gpio_set3_level = {
	.gpio66 = GPIO_LEVEL_LOW,
	.gpio68 = GPIO_LEVEL_HIGH,
};

static const struct pch_gpio_set3 pch_gpio_set3_reset = {
};

const struct pch_gpio_map mainboard_gpio_map = {
	.set1 = {
		.mode		= &pch_gpio_set1_mode,
		.direction	= &pch_gpio_set1_direction,
		.level		= &pch_gpio_set1_level,
		.blink		= &pch_gpio_set1_blink,
		.invert		= &pch_gpio_set1_invert,
		.reset		= &pch_gpio_set1_reset,
	},
	.set2 = {
		.mode		= &pch_gpio_set2_mode,
		.direction	= &pch_gpio_set2_direction,
		.level		= &pch_gpio_set2_level,
		.reset		= &pch_gpio_set2_reset,
	},
	.set3 = {
		.mode		= &pch_gpio_set3_mode,
		.direction	= &pch_gpio_set3_direction,
		.level		= &pch_gpio_set3_level,
		.reset		= &pch_gpio_set3_reset,
	},
};
