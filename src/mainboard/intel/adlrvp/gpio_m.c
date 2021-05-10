/* SPDX-License-Identifier: GPL-2.0-only */

#include <baseboard/gpio.h>
#include <baseboard/variants.h>
#include <commonlib/helpers.h>

/* Pad configuration in ramstage */
static const struct pad_config gpio_table[] = {
	/* A12 : BT_RF_KILL_N */
	PAD_CFG_GPO(GPP_A12, 1, PLTRST),

	/* H2 : WLAN_RST_N */
	PAD_CFG_GPO(GPP_H2, 1, PLTRST),
	/* 8 : M.2_BTWIFI_SUS_CLK */
	PAD_CFG_NF(GPD8, NONE, DEEP, NF1),
	/* 9 : GPD_9_SLP_WLAN_N */
	PAD_CFG_NF(GPD9, NONE, DEEP, NF1),
	/* 10 : GPD_10_SLP_S5_N */
	PAD_CFG_NF(GPD10, NONE, DEEP, NF1),

	/* D12 : WIFI_RF_KILL_N */
	PAD_CFG_GPO(GPP_D12, 1, PLTRST),
	/* D13 : WIFI_WAKE_N */
	PAD_CFG_NF(GPP_D13, NONE, DEEP, NF1),
	/* D14 :  x1 PCIE slot1 PWREN / SML0B_CLK */
	PAD_CFG_NF(GPP_D14, NONE, DEEP, NF1),
	/* D15 : WWAN_DISABLE_N */
	PAD_CFG_GPO(GPP_D15, 1, PLTRST),
	/* D18 : WWAN WAKE N*/
	PAD_CFG_GPI_IRQ_WAKE(GPP_D18, NONE, DEEP, LEVEL, INVERT),
	/* H23 : CLKREQ5_WWAN_N */
	PAD_CFG_NF(GPP_H23, NONE, DEEP, NF2),

	/* F0 : CNV_BRI_DT_BT_UART2_RTS_N */
	PAD_CFG_NF(GPP_F0, NONE, DEEP, NF1),
	/* F1 : CNV_BRI_RSP_BT_UART2_RXD */
	PAD_CFG_NF(GPP_F1, NONE, DEEP, NF1),
	/* F2 : CNV_RGI_DT_BT_UART2_TXD */
	PAD_CFG_NF(GPP_F2, NONE, DEEP, NF1),
	/* F3 : CNV_RGI_RSP_BT_UART2_CTS_N */
	PAD_CFG_NF(GPP_F3, NONE, DEEP, NF1),
	/* F4 : CNV_RF_RESET_R_N */
	PAD_CFG_NF(GPP_F4, NONE, DEEP, NF1),
	/* F5 : MODEM_CLKREQ_R */
	PAD_CFG_NF(GPP_F5, NONE, DEEP, NF2),
	/* F6 : GPPC_F6_CNV_PA_BLANKING */
	PAD_CFG_NF(GPP_F6, NONE, DEEP, NF1),
	/* H8 : CNV_MFUART2_RXD */
	PAD_CFG_NF(GPP_H8, NONE, DEEP, NF2),
	/* H9 : CNV_MFUART2_TXD */
	PAD_CFG_NF(GPP_H9, NONE, DEEP, NF2),

	/* A14 : TCPC01_TYPEA23_OC1_N */
	PAD_CFG_NF(GPP_A14, NONE, DEEP, NF1),
	/* A15 :  USB_TYPEA_OC2_N */
	PAD_CFG_NF(GPP_A15, NONE, DEEP, NF1),
	/* E18 : TBT_LSX0_TXD */
	PAD_CFG_NF(GPP_E18, NONE, DEEP, NF4),
	/* E19 : TBT_LSX0_RXD */
	PAD_CFG_NF(GPP_E19, NONE, DEEP, NF4),
	/* E20 : TBT_LSX1_TXD */
	PAD_CFG_NF(GPP_E20, NONE, DEEP, NF4),
	/* E21 : TBT_LSX1_RXD */
	PAD_CFG_NF(GPP_E21, NONE, DEEP, NF4),

	/* H4  : I2C0 SDA */
	PAD_CFG_NF(GPP_H4, NONE, DEEP, NF1),
	/* H6  : I2C1 SDA */
	PAD_CFG_NF(GPP_H6, NONE, DEEP, NF1),
	/* B16 : I2C5 SDA */
	PAD_CFG_NF(GPP_B16, NONE, DEEP, NF2),

	/* H5  : I2C0 SCL */
	PAD_CFG_NF(GPP_H5, NONE, DEEP, NF1),
	/* H7  : I2C1 SCL */
	PAD_CFG_NF(GPP_H7, NONE, DEEP, NF1),
	/* B17 : I2C5 SCL */
	PAD_CFG_NF(GPP_B17, NONE, DEEP, NF2),

	/* C5  : WWAN_PERST_N */
	PAD_CFG_GPO(GPP_C5, 1, PLTRST),
	/* E5  : WWAN_PERST# */
	PAD_CFG_GPO(GPP_E5, 1, PLTRST),
	/* D15 : WWAN_DISABLE_N */
	PAD_CFG_GPO(GPP_D15, 1, PLTRST),
	/* D9  : WWAN_FCP_POWER_OFF_N */
	PAD_CFG_GPO(GPP_D9, 1, PLTRST),

	/* D10 : PCH_SSD_PWR_EN */
	PAD_CFG_GPO(GPP_D10, 1, PLTRST),
	/* H0  : PCH_SSD_RST# */
	PAD_CFG_GPO(GPP_H0, 1, PLTRST),
	/* D16 : CPU_SSD_PWR_EN */
	PAD_CFG_GPO(GPP_D16, 1, PLTRST),
	/* H13 : CPU_SSD_RST# */
	PAD_CFG_GPO(GPP_H13, 1, PLTRST),

	/* DDP1/2/A/B  CTRLCLK and CTRLDATA pins */
	PAD_CFG_NF(GPP_E18, NONE, DEEP, NF4),
	PAD_CFG_NF(GPP_E19, NONE, DEEP, NF4),
	PAD_CFG_NF(GPP_E20, NONE, DEEP, NF4),
	PAD_CFG_NF(GPP_E21, NONE, DEEP, NF4),
	PAD_CFG_NF(GPP_E22, NONE, DEEP, NF2),
	PAD_CFG_NF(GPP_E23, NONE, DEEP, NF2),
	PAD_CFG_NF(GPP_A21, NONE, DEEP, NF2),
	PAD_CFG_NF(GPP_A22, NONE, DEEP, NF2),
	PAD_CFG_NF(GPP_H15, NONE, DEEP, NF1),
	PAD_CFG_NF(GPP_H17, NONE, DEEP, NF1),

	/* HPD_1 (E14) and HPD_2 (A18) pins */
	PAD_CFG_NF(GPP_E14, NONE, DEEP, NF1),
	PAD_CFG_NF(GPP_A18, NONE, DEEP, NF1),

	PAD_NC(GPP_A19, NONE),
	PAD_NC(GPP_A20, NONE),

	/* GPIO pin for PCIE SRCCLKREQB */
	PAD_CFG_NF(GPP_D5, NONE, DEEP, NF1),
	PAD_CFG_NF(GPP_D6, NONE, DEEP, NF1),
	PAD_CFG_NF(GPP_D7, NONE, DEEP, NF1),
	PAD_CFG_NF(GPP_D8, NONE, DEEP, NF1),
	PAD_CFG_NF(GPP_H19, NONE, DEEP, NF1),

	/* CAM1_RST */
	PAD_CFG_GPO(GPP_R5, 1, PLTRST),
	/* CAM2_RST */
	PAD_CFG_GPO(GPP_E15, 1, PLTRST),
	/* CAM1_PWR_EN */
	PAD_CFG_GPO(GPP_B23, 1, PLTRST),
	/* CAM2_PWR_EN */
	PAD_CFG_GPO(GPP_E16, 1, PLTRST),
	/* IMGCLKOUT0 */
	PAD_CFG_NF(GPP_D4, NONE, DEEP, NF1),
	/* IMGCLKOUT1 */
	PAD_CFG_NF(GPP_H20, NONE, DEEP, NF1),

	/* C16 : I2C0 SDA */
	PAD_CFG_NF(GPP_C16, NONE, DEEP, NF1),

	/* S0 : SNDW1_CLK */
	PAD_CFG_NF(GPP_S0, NONE, DEEP, NF1),

	/* S1 : SNDW1_DATA */
	PAD_CFG_NF(GPP_S1, NONE, DEEP, NF1),

	/* S2 : SNDW2_CLK */
	PAD_CFG_NF(GPP_S2, NONE, DEEP, NF2),

	/* S3 : SNDW2_DATA */
	PAD_CFG_NF(GPP_S3, NONE, DEEP, NF2),

	/* S4 : SNDW3_CLK */
	PAD_CFG_NF(GPP_S4, NONE, DEEP, NF2),

	/* S5 : SNDW3_DATA */
	PAD_CFG_NF(GPP_S5, NONE, DEEP, NF2),

	/* S6 : SNDW4_CLK */
	PAD_CFG_NF(GPP_S6, NONE, DEEP, NF2),

	/* S7 : SNDW4_DATA */
	PAD_CFG_NF(GPP_S7, NONE, DEEP, NF2),
};

void variant_configure_gpio_pads(void)
{
	gpio_configure_pads(gpio_table, ARRAY_SIZE(gpio_table));
}

static const struct cros_gpio cros_gpios[] = {
	CROS_GPIO_REC_AL(CROS_GPIO_VIRTUAL, CROS_GPIO_DEVICE_NAME),
};

const struct cros_gpio *variant_cros_gpios(size_t *num)
{
	*num = ARRAY_SIZE(cros_gpios);
	return cros_gpios;
}
