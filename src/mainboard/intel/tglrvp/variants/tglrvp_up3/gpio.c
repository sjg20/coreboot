/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2020 Intel Corporation.
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

#include <baseboard/gpio.h>
#include <baseboard/variants.h>
#include <commonlib/helpers.h>

/* Pad configuration in ramstage*/
static const struct pad_config gpio_table[] = {
	/* PCH M.2 SSD */
	PAD_CFG_GPO(GPP_B16, 1, PLTRST),
	PAD_CFG_GPO(GPP_H0, 1, PLTRST),

	/* Camera */
	PAD_CFG_GPO(GPP_B23, 0, PLTRST),
	PAD_CFG_GPO(GPP_C15, 0, PLTRST),
	PAD_CFG_GPO(GPP_R6, 0, PLTRST),
	PAD_CFG_GPO(GPP_H12, 0, PLTRST),

	/* Image clock: IMGCLKOUT_0, IMGCLKOUT_1 */
	PAD_CFG_NF(GPP_D4, NONE, PLTRST, NF1),
	PAD_CFG_NF(GPP_H20, NONE, PLTRST, NF1),

	/* ISH UART0 RX/TX */
	PAD_CFG_NF(GPP_D13, NONE, PLTRST, NF1),
	PAD_CFG_NF(GPP_D14, NONE, PLTRST, NF1),

	/* ISH I2C0 */
	PAD_CFG_NF(GPP_B5, NONE, PLTRST, NF1),
	PAD_CFG_NF(GPP_B6, NONE, PLTRST, NF1),

	/* ISH GPI 0-6 */
	PAD_CFG_NF(GPP_D0, NONE, PLTRST, NF1),
	PAD_CFG_NF(GPP_D1, NONE, PLTRST, NF1),
	PAD_CFG_NF(GPP_D2, NONE, PLTRST, NF1),
	PAD_CFG_NF(GPP_D3, NONE, PLTRST, NF1),
	PAD_CFG_NF(GPP_D17, NONE, PLTRST, NF1),
	PAD_CFG_NF(GPP_D18, NONE, PLTRST, NF1),
	PAD_CFG_NF(GPP_E15, NONE, PLTRST, NF1),
	PAD_CFG_NF(GPP_E16, NONE, PLTRST, NF1),

	/*Audio */
	PAD_CFG_NF(GPP_C16, NONE, DEEP, NF1), /* I2C0_SDA */
	PAD_CFG_NF(GPP_C17, NONE, DEEP, NF1), /* I2C0_SCL */
	PAD_CFG_GPO(GPP_C5, 1, PLTRST),
	PAD_CFG_GPI_APIC(GPP_C12, NONE, PLTRST, EDGE_BOTH, INVERT), /* AUDIO JACK IRQ */

};

/* Early pad configuration in bootblock */
static const struct pad_config early_gpio_table[] = {
	/*Audio */
	PAD_CFG_NF(GPP_R0, NONE, DEEP, NF2),   /* I2S0_HP_SCLK */
	PAD_CFG_NF(GPP_R1, NONE, DEEP, NF2),   /* I2S0_HP_SFRM */
	PAD_CFG_NF(GPP_R2, DN_20K, DEEP, NF2), /* I2S0_HP_TX */
	PAD_CFG_NF(GPP_R3, NONE, DEEP, NF2),   /* I2S0_HP_RX */

	PAD_CFG_NF(GPP_A23, NONE, DEEP, NF1),  /* I2S1_SPKR_SCLK */
	PAD_CFG_NF(GPP_R5, NONE, DEEP, NF2),   /* I2S1_SPKR_TX */
	PAD_CFG_NF(GPP_R6, NONE, DEEP, NF2),   /* I2S1_SPKR_RX */
	PAD_CFG_NF(GPP_R7, NONE, DEEP, NF2),   /* I2S1_SPKR_SFRM */

	PAD_CFG_NF(GPP_S0, NONE, DEEP, NF1),   /* SNDW0_HP_CLK */
	PAD_CFG_NF(GPP_S1, NONE, DEEP, NF1),   /* SNDW0_HP_DATA */
	PAD_CFG_NF(GPP_S2, NONE, DEEP, NF1),   /* SNDW1_SPKR_CLK */
	PAD_CFG_NF(GPP_S3, NONE, DEEP, NF1),   /* SNDW1_SPKR_DATA */

	PAD_CFG_NF(GPP_S4, NONE, DEEP, NF2),   /* DMIC1_CLK */
	PAD_CFG_NF(GPP_S5, NONE, DEEP, NF2),   /* DMIC1_DATA */
	PAD_CFG_NF(GPP_S6, NONE, DEEP, NF2),   /* DMIC0_CLK */
	PAD_CFG_NF(GPP_S7, NONE, DEEP, NF2),   /* DMIC0_DATA */

	/* DP */
	PAD_CFG_NF(GPP_L_BKLTEN, NONE, PLTRST, NF1), /* L_BKLTEN */
	PAD_CFG_NF(GPP_L_BKLTCTL, NONE, PLTRST, NF1), /* L_BKLTCTL */
	PAD_CFG_NF(GPP_L_VDDEN, NONE, PLTRST, NF1), /* L_VDDEN */
	PAD_CFG_NF(GPP_E14, NONE, PLTRST, NF1), /* HPD_A */
	PAD_CFG_NF(GPP_A18, NONE, PLTRST, NF1), /* HPD_B */
	PAD_CFG_NF(GPP_A19, NONE, PLTRST, NF1), /* HPD_1 */
	PAD_CFG_NF(GPP_E18, NONE, PLTRST, NF1), /* DDP_1_CTRCLK */
	PAD_CFG_NF(GPP_E19, NONE, PLTRST, NF1), /* DDP_1_CTRDATA */
};

const struct pad_config *variant_gpio_table(size_t *num)
{
	*num = ARRAY_SIZE(gpio_table);
	return gpio_table;
}

const struct pad_config *variant_early_gpio_table(size_t *num)
{
	*num = ARRAY_SIZE(early_gpio_table);
	return early_gpio_table;
}

static const struct cros_gpio cros_gpios[] = {
	CROS_GPIO_REC_AL(CROS_GPIO_VIRTUAL, CROS_GPIO_COMM0_NAME),
};

const struct cros_gpio *variant_cros_gpios(size_t *num)
{
	*num = ARRAY_SIZE(cros_gpios);
	return cros_gpios;
}
