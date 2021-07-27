/* SPDX-License-Identifier: GPL-2.0-or-later */

#include <baseboard/gpio.h>
#include <baseboard/variants.h>
#include <boardid.h>
#include <gpio.h>
#include <soc/gpio.h>
#include <baseboard/variants.h>

/* This table is used by guybrush variant with board version < 2. */
static const struct soc_amd_gpio bid1_gpio_table[] = {
	/* Unused TP183 */
	PAD_NC(GPIO_31),
	/* EN_SPKR */
	PAD_GPO(GPIO_69, HIGH),
	/* SD_AUX_RESET_L */
	PAD_GPO(GPIO_70, HIGH),
	/* RAM_ID_CHAN_SEL */
	PAD_GPI(GPIO_74, PULL_NONE),
};

/* This table is used by guybrush variant with board version < 2. */
/* Use AUX Reset lines instead of PCIE_RST for Board Version 1 */
static const struct soc_amd_gpio bid1_early_gpio_table[] = {
	/* SD_AUX_RESET_L */
	PAD_GPO(GPIO_70, LOW),
};

/* This table is used by guybrush variant with board version < 2. */
static const struct soc_amd_gpio bid1_pcie_gpio_table[] = {
	/* EN_PWR_WWAN_X */
	PAD_GPO(GPIO_8, LOW),
	/* WWAN_RST_L */
	PAD_GPO(GPIO_24, LOW),
	/* WWAN_DISABLE */
	PAD_GPO(GPIO_85, HIGH),
	/* SD_AUX_RESET_L */
	PAD_GPO(GPIO_70, HIGH),
};

/* This table is used by guybrush variant with board version >= 2. */
static const struct soc_amd_gpio bid2_pcie_gpio_table[] = {
	/* EN_PWR_WWAN_X */
	PAD_GPO(GPIO_8, LOW),
	/* WWAN_RST_L */
	PAD_GPO(GPIO_24, LOW),
	/* WWAN_DISABLE */
	PAD_GPO(GPIO_85, HIGH),
};

const struct soc_amd_gpio *variant_override_gpio_table(size_t *size)
{
	uint32_t board_version = board_id();
	*size = 0;

	if (board_version < 2) {
		*size = ARRAY_SIZE(bid1_gpio_table);
		return bid1_gpio_table;
	}

	return NULL;
}

const struct soc_amd_gpio *variant_early_override_gpio_table(size_t *size)
{
	uint32_t board_version = board_id();
	*size = 0;

	if (board_version < 2) {
		*size = ARRAY_SIZE(bid1_early_gpio_table);
		return bid1_early_gpio_table;
	}

	return NULL;
}

const struct soc_amd_gpio *variant_pcie_override_gpio_table(size_t *size)
{
	uint32_t board_version = board_id();
	*size = 0;

	if (board_version < 2) {
		*size = ARRAY_SIZE(bid1_pcie_gpio_table);
		return bid1_pcie_gpio_table;
	}

	*size = ARRAY_SIZE(bid2_pcie_gpio_table);
	return bid2_pcie_gpio_table;
}
