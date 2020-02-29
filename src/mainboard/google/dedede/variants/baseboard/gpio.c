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
#include <vendorcode/google/chromeos/chromeos.h>

/* Pad configuration in ramstage*/
static const struct pad_config gpio_table[] = {
	/* GPP_A0 thru GPP_A6 come configured out of reset, do not touch */
	/* A0  : ESPI_IO0 */
	/* A1  : ESPI_IO1 */
	/* A2  : ESPI_IO2 */
	/* A3  : ESPI_IO3 */
	/* A4  : ESPI_CS# */
	/* A5  : ESPI_CLK */
	/* A6  : ESPI_RESET_L */
	/* A7  : SMB_CLK */
	PAD_NC(GPP_A7, NONE),
	/* A8  : SMB_DATA */
	PAD_NC(GPP_A8, NONE),
	/* A9  : SMB_ALERT_N */
	PAD_NC(GPP_A9, NONE),
	/* A10 : WWAN_EN */
	PAD_NC(GPP_A10, NONE),
	/* A11 : TOUCH_RPT_EN */
	PAD_NC(GPP_A11, NONE),
	/* A12 : USB_OC1_N */
	PAD_NC(GPP_A12, NONE),
	/* A13 : USB_OC2_N */
	PAD_NC(GPP_A13, NONE),
	/* A14 : USB_OC3_N */
	PAD_NC(GPP_A14, NONE),
	/* A15 : GPP_A15 */
	PAD_NC(GPP_A15, NONE),
	/* A16 : EC_AP_USB_C0_HPD */
	PAD_CFG_NF(GPP_A16, NONE, DEEP, NF1),
	/* A17 : EDP_HPD */
	PAD_CFG_NF(GPP_A17, NONE, DEEP, NF1),
	/* A18 : USB_OC0_N */
	PAD_NC(GPP_A18, NONE),
	/* A19 : PCHHOT_N */
	PAD_NC(GPP_A19, NONE),

	/* B0  : VCCIN_AUX_VID0 */
	PAD_CFG_NF(GPP_B0, NONE, DEEP, NF1),
	/* B1  : VCCIN_AUX_VID1 */
	PAD_CFG_NF(GPP_B1, NONE, DEEP, NF1),
	/* B2  : PROCHOT_ODL */
	PAD_NC(GPP_B2, NONE),
	/* B3  : TRACKPAD_INT_ODL */
	PAD_CFG_GPI_IRQ_WAKE(GPP_B3, NONE, PLTRST, LEVEL, INVERT),
	/* B4  : H1_PCH_INT_ODL */
	PAD_CFG_GPI_APIC(GPP_B4, NONE, PLTRST, LEVEL, INVERT),
	/* B5  : PCIE_CLKREQ0_N */
	PAD_NC(GPP_B5, NONE),
	/* B6  : PCIE_CLKREQ1_N */
	PAD_NC(GPP_B6, NONE),
	/* B7  : PCIE_CLKREQ2_N */
	PAD_NC(GPP_B7, NONE),
	/* B8  : WLAN_CLKREQ_ODL */
	PAD_CFG_NF(GPP_B8, NONE, DEEP, NF1),
	/* B9  : PCIE_CLKREQ4_N */
	PAD_NC(GPP_B9, NONE),
	/* B10 : PCIE_CLKREQ5_N */
	PAD_NC(GPP_B10, NONE),
	/* B11 : PMCALERT_N */
	PAD_NC(GPP_B11, NONE),
	/* B12 : AP_SLP_S0_L */
	PAD_CFG_NF(GPP_B12, NONE, DEEP, NF1),
	/* B13 : PLT_RST_L */
	PAD_CFG_NF(GPP_B13, NONE, DEEP, NF1),
	/* B14 : SPKR/GSPI0_CS1_N */
	PAD_NC(GPP_B14, NONE),
	/* B15 : H1_SLAVE_SPI_CS_L */
	PAD_CFG_NF(GPP_B15, NONE, DEEP, NF1),
	/* B16 : H1_SLAVE_SPI_CLK */
	PAD_CFG_NF(GPP_B16, NONE, DEEP, NF1),
	/* B17 : H1_SLAVE_SPI_MISO_R */
	PAD_CFG_NF(GPP_B17, NONE, DEEP, NF1),
	/* B18 : H1_SLAVE_SPI_MOSI_R */
	PAD_CFG_NF(GPP_B18, NONE, DEEP, NF1),
	/* B19 : GSPI1_CS0_N */
	PAD_NC(GPP_B19, NONE),
	/* B20 : GSPI1_CLK */
	PAD_NC(GPP_B20, NONE),
	/* B21 : GSPI1_MISO */
	PAD_NC(GPP_B21, NONE),
	/* B22 : GSPI1_MOSI */
	PAD_NC(GPP_B22, NONE),
	/* B23 : EC_AP_USB_C1_HDMI_HPD */
	PAD_CFG_NF(GPP_B23, NONE, DEEP, NF1),

	/* C0  : RAM_STRAP_0 */
	PAD_CFG_GPI(GPP_C0, NONE, DEEP),
	/* C1  : GPP_C1 */
	PAD_NC(GPP_C1, NONE),
	/* C2  : GPP_C2 */
	PAD_NC(GPP_C2, NONE),
	/* C3  : RAM_STRAP_1 */
	PAD_CFG_GPI(GPP_C3, NONE, DEEP),
	/* C4  : RAM_STRAP_2 */
	PAD_CFG_GPI(GPP_C4, NONE, DEEP),
	/* C5  : RAM_STRAP_3 */
	PAD_CFG_GPI(GPP_C5, NONE, DEEP),
	/* C6  : PMC_SUSWARN_N */
	PAD_NC(GPP_C6, NONE),
	/* C7  : PMC_SUSACK_N */
	PAD_NC(GPP_C7, NONE),
	/* C8  : GPP_C8/UART0_RXD */
	PAD_NC(GPP_C8, NONE),
	/* C9  : GPP_C9/UART0_TXD */
	PAD_NC(GPP_C9, NONE),
	/* C10 : GPP_C10/UART0_RTSB */
	PAD_NC(GPP_C10, NONE),
	/* C11 : AP_WP_OD */
	PAD_NC(GPP_C11, NONE),
	/* C12 : AP_PEN_DET_ODL */
	PAD_NC(GPP_C12, NONE),
	/* C13 : GPP_C13/UART1_TXD */
	PAD_NC(GPP_C13, NONE),
	/* C14 : EC_IN_RW_OD */
	PAD_CFG_GPI(GPP_C14, NONE, DEEP),
	/* C15 : EC_AP_MKBP_INT_L */
	PAD_CFG_GPI_APIC(GPP_C15, NONE, PLTRST, LEVEL, INVERT),
	/* C16 : AP_I2C_TRACKPAD_SDA_3V3 */
	PAD_CFG_NF(GPP_C16, NONE, DEEP, NF1),
	/* C17 : AP_I2C_TRACKPAD_SCL_3V3 */
	PAD_CFG_NF(GPP_C17, NONE, DEEP, NF1),
	/* C18 : AP_I2C_EMR_SDA */
	PAD_CFG_NF(GPP_C18, NONE, DEEP, NF1),
	/* C19 : AP_I2C_EMR_SCL */
	PAD_CFG_NF(GPP_C19, NONE, DEEP, NF1),
	/* C20 : UART_DBG_TX_AP_RX */
	PAD_CFG_NF(GPP_C20, NONE, DEEP, NF1),
	/* C21 : UART_AP_TX_DBG_RX */
	PAD_CFG_NF(GPP_C21, NONE, DEEP, NF1),
	/* C22 : UART2_RTS_N */
	PAD_NC(GPP_C22, DN_20K),
	/* C23 : UART2_CTS_N */
	PAD_NC(GPP_C23, DN_20K),

	/* D0  : WWAN_HOST_WAKE */
	PAD_NC(GPP_D0, NONE),
	/* D1  : WLAN_PERST_L */
	PAD_CFG_GPO(GPP_D1, 1, DEEP),
	/* D2  : WLAN_INT_L */
	PAD_NC(GPP_D2, NONE),
	/* D3  : WLAN_PCIE_WAKE_ODL */
	PAD_CFG_GPI_SCI_LOW(GPP_D3, NONE, DEEP, EDGE_SINGLE),
	/* D4  : TOUCH_INT_ODL */
	PAD_NC(GPP_D4, NONE),
	/* D5  : TOUCH_RESET_L */
	PAD_NC(GPP_D5, NONE),
	/* D6  : EN_PP3300_TOUCH_S0 */
	PAD_NC(GPP_D6, NONE),
	/* D7  : EMR_INT_ODL */
	PAD_NC(GPP_D7, NONE),
	/* D8  : GPP_D8/GSPI2_CS0B/UART0A_RXD */
	PAD_NC(GPP_D8, NONE),
	/* D9  : GPP_D9/GSPI2_CLK/UART0A_TXD */
	PAD_NC(GPP_D9, NONE),
	/* D10 : GPP_D10/GSPI2_MISO/UART0A_RTSB */
	PAD_NC(GPP_D10, NONE),
	/* D11 : GPP_D11/GSPI2_MOSI/UART0A_CTSB */
	PAD_NC(GPP_D11, NONE),
	/* D12 : WCAM_RST_L */
	PAD_NC(GPP_D12, NONE),
	/* D13 : EN_PP2800_CAMERA */
	PAD_NC(GPP_D13, NONE),
	/* D14 : EN_PP1200_CAMERA */
	PAD_NC(GPP_D14, NONE),
	/* D15 : UCAM_RST_L */
	PAD_NC(GPP_D15, NONE),
	/* D16 : HP_INT_ODL */
	PAD_NC(GPP_D16, NONE),
	/* D17 : EN_SPK */
	PAD_NC(GPP_D17, NONE),
	/* D18 : I2S_MCLK */
	PAD_NC(GPP_D18, NONE),
	/* D19 : WWAN_WLAN_COEX1 */
	PAD_CFG_NF(GPP_D19, NONE, DEEP, NF1),
	/* D20 : WWAN_WLAN_COEX2 */
	PAD_CFG_NF(GPP_D20, NONE, DEEP, NF1),
	/* D21 : WWAN_WLAN_COEX3 */
	PAD_CFG_NF(GPP_D21, NONE, DEEP, NF1),
	/* D22 : AP_I2C_SUB_SDA*/
	PAD_NC(GPP_D22, NONE),
	/* D23 : AP_I2C_SUB_SCL */
	PAD_NC(GPP_D23, NONE),

	/* E0  : CLK_24M_UCAM */
	PAD_NC(GPP_E0, NONE),
	/* E1  : EMR_RESET_L */
	PAD_NC(GPP_E1, NONE),
	/* E2  : CLK_24M_WCAM */
	PAD_NC(GPP_E2, NONE),
	/* E3  : GPP_E3/SATA_0_DEVSLP */
	PAD_NC(GPP_E3, NONE),
	/* E4  : IMGCLKOUT_2 */
	PAD_NC(GPP_E4, NONE),
	/* E5  : AP_SUB_IO_2 */
	PAD_NC(GPP_E5, NONE),
	/* E6  : GPP_E6/IMGCLKOUT_3 */
	PAD_NC(GPP_E6, NONE),
	/* E7  : GPP_E7/SATA_1_DEVSLP */
	PAD_NC(GPP_E7, NONE),
	/* E8  : GPP_E8/SATA_0_GP */
	PAD_NC(GPP_E8, NONE),
	/* E9  : GPP_E9/SML_CLK0/SATA_1_GP */
	PAD_NC(GPP_E9, NONE),
	/* E10 : GPP_E10/SML_DATA0 */
	PAD_NC(GPP_E10, NONE),
	/* E11 : AP_I2C_SUB_INT_ODL */
	PAD_NC(GPP_E11, NONE),
	/* E12 : GPP_E12/IMGCLKOUT_4 */
	PAD_NC(GPP_E12, NONE),
	/* E13 : GPP_E13/DDI0_DDC_SCL */
	PAD_NC(GPP_E13, NONE),
	/* E14 : GPP_E14/DDI0_DDC_SDA */
	PAD_NC(GPP_E14, NONE),
	/* E15 : GPP_E15/DDI1_DDC_SCL */
	PAD_NC(GPP_E15, NONE),
	/* E16 : GPP_E16/DDI1_DDC_SDA */
	PAD_NC(GPP_E16, NONE),
	/* E17 : HDMI_DDC_SCL */
	PAD_NC(GPP_E17, NONE),
	/* E18 : HDMI_DDC_SDA */
	PAD_NC(GPP_E18, NONE),
	/* E19 : GPP_E19/IMGCLKOUT_5/PCIE_LNK_DOWN */
	PAD_NC(GPP_E19, NONE),
	/* E20 : CNV_BRI_DT_R */
	PAD_CFG_NF(GPP_E20, NONE, DEEP, NF1),
	/* E21 : CNV_BRI_RSP */
	PAD_CFG_NF(GPP_E21, NONE, DEEP, NF1),
	/* E22 : CNV_RGI_DT_R */
	PAD_CFG_NF(GPP_E22, NONE, DEEP, NF1),
	/* E23 : CNV_RGI_RSP */
	PAD_CFG_NF(GPP_E23, NONE, DEEP, NF1),


	/* F4  : CNV_RF_RST_L */
	PAD_CFG_NF(GPP_F4, NONE, DEEP, NF1),
	/* F7  : EMMC_CMD */
	PAD_CFG_NF(GPP_F7, NONE, DEEP, NF1),
	/* F8  : EMMC_DATA0 */
	PAD_CFG_NF(GPP_F8, NONE, DEEP, NF1),
	/* F9  : EMMC_DATA1 */
	PAD_CFG_NF(GPP_F9, NONE, DEEP, NF1),
	/* F10 : EMMC_DATA2 */
	PAD_CFG_NF(GPP_F10, NONE, DEEP, NF1),
	/* F11 : EMMC_DATA3 */
	PAD_CFG_NF(GPP_F11, NONE, DEEP, NF1),
	/* F12 : EMMC_DATA4 */
	PAD_CFG_NF(GPP_F12, NONE, DEEP, NF1),
	/* F13 : EMMC_DATA5 */
	PAD_CFG_NF(GPP_F13, NONE, DEEP, NF1),
	/* F14 : EMMC_DATA6 */
	PAD_CFG_NF(GPP_F14, NONE, DEEP, NF1),
	/* F15 : EMMC_DATA7 */
	PAD_CFG_NF(GPP_F15, NONE, DEEP, NF1),
	/* F16 : EMMC_RCLK */
	PAD_CFG_NF(GPP_F16, NONE, DEEP, NF1),
	/* F17 : EMMC_CLK */
	PAD_CFG_NF(GPP_F17, NONE, DEEP, NF1),
	/* F18 : EMMC_RESET_N */
	PAD_CFG_NF(GPP_F18, NONE, DEEP, NF1),

	/* G0  : SD_CMD */
	PAD_NC(GPP_G0, NONE),
	/* G1  : SD_DATA0 */
	PAD_NC(GPP_G1, NONE),
	/* G2  : SD_DATA1 */
	PAD_NC(GPP_G2, NONE),
	/* G3  : SD_DATA2 */
	PAD_NC(GPP_G3, NONE),
	/* G4  : SD_DATA3 */
	PAD_NC(GPP_G4, NONE),
	/* G5  : SD_CD_ODL */
	PAD_NC(GPP_G5, NONE),
	/* G6  : SD_CLK */
	PAD_NC(GPP_G6, NONE),
	/* G7  : SD_SDIO_WP */
	PAD_NC(GPP_G7, NONE),

	/* H0  : WWAN_PERST */
	PAD_NC(GPP_H0, NONE),
	/* H1  : EN_PP3300_SD_U */
	PAD_NC(GPP_H1, NONE),
	/* H2  : CNV_CLKREQ0 */
	PAD_CFG_NF(GPP_H2, NONE, DEEP, NF3),
	/* H3  : GPP_H03/SX_EXIT_HOLDOFF_N */
	PAD_NC(GPP_H3, NONE),
	/* H4  : AP_I2C_TS_SDA */
	PAD_CFG_NF(GPP_H4, NONE, DEEP, NF1),
	/* H5  : AP_I2C_TS_SCL */
	PAD_CFG_NF(GPP_H5, NONE, DEEP, NF1),
	/* H6  : AP_I2C_CAM_SDA */
	PAD_CFG_NF(GPP_H6, NONE, DEEP, NF1),
	/* H7  : AP_I2C_CAM_SCL */
	PAD_CFG_NF(GPP_H7, NONE, DEEP, NF1),
	/* H8  : AP_I2C_AUDIO_SDA */
	PAD_CFG_NF(GPP_H8, NONE, DEEP, NF1),
	/* H9  : AP_I2C_AUDIO_SCL */
	PAD_CFG_NF(GPP_H9, NONE, DEEP, NF1),
	/* H10 : CPU_C10_GATE_L */
	PAD_CFG_NF(GPP_H10, NONE, DEEP, NF1),
	/* H11 : GPP_H11/AV_I2S2_SCLK */
	PAD_NC(GPP_H11, NONE),
	/* H12 : GPP_H12/AVS_I2S2_SFRM/CNF_RF_RESET_N */
	PAD_NC(GPP_H12, NONE),
	/* H13 : GPP_H13/AVS_I2S2_TXD/MODEM_CLKREQ */
	PAD_NC(GPP_H13, NONE),
	/* H14 : GPP_H14/AVS_I2S2_RXD */
	PAD_NC(GPP_H14, NONE),
	/* H15 : I2S_SPK_BCLK */
	PAD_NC(GPP_H15, NONE),
	/* H16 : AP_SUB_IO_L */
	PAD_NC(GPP_H16, NONE),
	/* H17 : WWAN_RST_L */
	PAD_NC(GPP_H17, NONE),
	/* H18 : WLAN_DISABLE_L */
	PAD_CFG_GPO(GPP_H18, 1, DEEP),
	/* H19 : BT_DISABLE_L */
	PAD_CFG_GPO(GPP_H19, 1, DEEP),

	/* R0  : I2S_HP_BCLK */
	PAD_NC(GPP_R0, NONE),
	/* R1  : I2S_HP_LRCK */
	PAD_NC(GPP_R1, NONE),
	/* R2  : I2S_HP_AUDIO */
	PAD_NC(GPP_R2, NONE),
	/* R3  : I2S_HP_MIC */
	PAD_NC(GPP_R3, NONE),
	/* R4  : GPP_R04/HDA_RST_N */
	PAD_NC(GPP_R4, NONE),
	/* R5  : GPP_R05/HDA_SDI1/AVS_I2S1_RXD */
	PAD_NC(GPP_R5, NONE),
	/* R6  : I2S_SPK_LRCK */
	PAD_NC(GPP_R6, NONE),
	/* R7  : I2S_SPK_AUDIO */
	PAD_NC(GPP_R7, NONE),

	/* S0  : RAM_STRAP_4 */
	PAD_NC(GPP_S0, NONE),
	/* S1  : RSVD_STRAP */
	PAD_NC(GPP_S1, NONE),
	/* S2  : DMIC1_CLK */
	PAD_NC(GPP_S2, NONE),
	/* S3  : DMIC1_DATA */
	PAD_NC(GPP_S3, NONE),
	/* S4  : GPP_S04/SNDW1_CLK */
	PAD_NC(GPP_S4, NONE),
	/* S5  : GPP_S05/SNDW1_DATA */
	PAD_NC(GPP_S5, NONE),
	/* S6  : DMIC0_CLK */
	PAD_NC(GPP_S6, NONE),
	/* S7  : DMIC0_DATA */
	PAD_NC(GPP_S7, NONE),

	/* GPD0 : AP_BATLOW_L */
	PAD_CFG_NF(GPD0, NONE, DEEP, NF1),
	/* GPD1 : GPP_GPD1/ACPRESENT */
	PAD_CFG_NF(GPD1, NONE, DEEP, NF1),
	/* GPD2 : EC_AP_WAKE_ODL */
	PAD_CFG_NF(GPD2, NONE, DEEP, NF1),
	/* GPD3 : EC_AP_PWR_BTN_ODL */
	PAD_CFG_NF(GPD3, NONE, DEEP, NF1),
	/* GPD4 : AP_SLP_S3_L */
	PAD_CFG_NF(GPD4, NONE, DEEP, NF1),
	/* GPD5 : AP_SLP_S4_L */
	PAD_CFG_NF(GPD5, NONE, DEEP, NF1),
	/* GPD6 : AP_SLP_A_L */
	PAD_NC(GPD6, NONE),
	/* GPD7 : GPP_GPD7 */
	PAD_NC(GPD7, NONE),
	/* GPD8 : WLAN_SUSCLK */
	PAD_CFG_NF(GPD8, NONE, DEEP, NF1),
	/* GPD9 : AP_SLP_WLAN_L */
	PAD_NC(GPD9, NONE),
	/* GPD10 : AP_SLP_S5_L */
	PAD_NC(GPD10, NONE),
};

/* Early pad configuration in bootblock */
static const struct pad_config early_gpio_table[] = {
	/* B4 : H1_PCH_INT_ODL */
	PAD_CFG_GPI_APIC(GPP_B4, NONE, PLTRST, LEVEL, INVERT),
	/* B15 : H1_SLAVE_SPI_CS_L */
	PAD_CFG_NF(GPP_B15, NONE, DEEP, NF1),
	/* B16 : H1_SLAVE_SPI_CLK */
	PAD_CFG_NF(GPP_B16, NONE, DEEP, NF1),
	/* B17 : H1_SLAVE_SPI_MISO_R */
	PAD_CFG_NF(GPP_B17, NONE, DEEP, NF1),
	/* B18 : H1_SLAVE_SPI_MOSI_R */
	PAD_CFG_NF(GPP_B18, NONE, DEEP, NF1),

	/* C0  : RAM_STRAP_0 */
	PAD_CFG_GPI(GPP_C0, NONE, DEEP),
	/* C3  : RAM_STRAP_1 */
	PAD_CFG_GPI(GPP_C3, NONE, DEEP),
	/* C4  : RAM_STRAP_2 */
	PAD_CFG_GPI(GPP_C4, NONE, DEEP),
	/* C5  : RAM_STRAP_3 */
	PAD_CFG_GPI(GPP_C5, NONE, DEEP),

	/* D1  : WLAN_PERST_L */
	PAD_CFG_GPO(GPP_D1, 1, DEEP),

	/* H19 : BT_DISABLE_L */
	PAD_CFG_GPO(GPP_H19, 0, DEEP),
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

/* GPIO settings before entering sleep. */
static const struct pad_config sleep_gpio_table[] = {
};

const struct pad_config *__weak variant_sleep_gpio_table(size_t *num)
{
	*num = ARRAY_SIZE(sleep_gpio_table);
	return sleep_gpio_table;
}

static const struct cros_gpio cros_gpios[] = {
};

const struct cros_gpio *__weak variant_cros_gpios(size_t *num)
{
	*num = ARRAY_SIZE(cros_gpios);
	return cros_gpios;
}
