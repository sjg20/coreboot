/*
 * This file is part of the coreboot project.
 *
 * Copyright 2017 Google Inc.
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

/* Pad configuration in ramstage */
static const struct pad_config gpio_table[] = {
/* RCIN# */		PAD_NC(GPP_A0, NONE), /* PCH_CSI_GPIO1 */
/* ESPI_IO0 */		PAD_CFG_NF(GPP_A1, NONE, DEEP, NF2), /* ESPI_IO0_R */
/* ESPI_IO1 */		PAD_CFG_NF(GPP_A2, NONE, DEEP, NF2), /* ESPI_IO0_R */
/* ESPI_IO2 */		PAD_CFG_NF(GPP_A3, NONE, DEEP, NF2), /* ESPI_IO2_R */
/* ESPI_IO3 */		PAD_CFG_NF(GPP_A4, NONE, DEEP, NF2), /* ESPI_IO3_R */
/* ESPI_CS# */		PAD_CFG_NF(GPP_A5, NONE, DEEP, NF2), /* ESPI_CS_L */
/* SERIRQ */		PAD_NC(GPP_A6, NONE),
/* PIRQA# */		PAD_NC(GPP_A7, NONE),
/* CLKRUN# */		PAD_CFG_GPI(GPP_A8, NONE, DEEP), /* EC_IN_RW_OD */
/* ESPI_CLK */		PAD_CFG_NF(GPP_A9, NONE, DEEP, NF2), /* ESPI_CLK_R */
/* CLKOUT_LPC1 */	PAD_NC(GPP_A10, NONE),
/* PME# */		PAD_CFG_GPO(GPP_A11, 0, DEEP), /* PCH_FP_PWR_EN */
/* BM_BUSY# */		PAD_CFG_GPI(GPP_A12, NONE, DEEP), /* FPMCU_INT */
/* SUSWARN# */		PAD_CFG_NF(GPP_A13, NONE, DEEP, NF1), /* SUSWARN_L */
/* ESPI_RESET# */	PAD_CFG_NF(GPP_A14, NONE, DEEP, NF2), /* ESPI_RESET_L */
/* SUSACK# */		PAD_CFG_NF(GPP_A15, NONE, DEEP, NF1), /* SUSACK_L */
/* SD_1P8_SEL */	PAD_NC(GPP_A16, NONE),
/* SD_PWR_EN# */	PAD_CFG_NF(GPP_A17, NONE, DEEP, NF1),
/* ISH_GP0 */		PAD_NC(GPP_A18, NONE),
/* ISH_GP1 */		PAD_NC(GPP_A19, NONE),
/* ISH_GP2 */		PAD_NC(GPP_A20, NONE),
/* ISH_GP3 */		PAD_CFG_GPO(GPP_A21, 0, DEEP), /* PCH_FPMCU_BOOT0 */
/* ISH_GP4 */		PAD_CFG_GPI(GPP_A22, NONE, DEEP), /* FPMCU_INT */
/* ISH_GP5 */		PAD_CFG_GPO(GPP_A23, 1, DEEP), /* PCH_FPMCU_RST_ODL */
/* CORE_VID0 */		PAD_CFG_NF(GPP_B0, NONE, DEEP, NF1), /* CORE_VID0 */
/* CORE_VID1 */		PAD_CFG_NF(GPP_B1, NONE, DEEP, NF1), /* CORE_VID1 */
/* VRALERT# */		PAD_NC(GPP_B2, NONE),
/* CPU_GP2 */		PAD_NC(GPP_B3, NONE),
/* CPU_GP3 */		PAD_NC(GPP_B4, NONE),
/* SRCCLKREQ0# */	PAD_NC(GPP_B5, NONE),
/* SRCCLKREQ1# */	PAD_NC(GPP_B6, NONE),
/* SRCCLKREQ2# */	PAD_CFG_NF(GPP_B7, NONE, DEEP,
				   NF1), /* PCIE_8_WLAN_CLKREQ_ODL */
/* SRCCLKREQ3# */	PAD_CFG_NF(GPP_B8, NONE, DEEP,
				   NF1), /* PCIE_NVME_CLKREQ_ODL */
/* SRCCLKREQ4# */	PAD_NC(GPP_B9, NONE),
/* SRCCLKREQ5# */	PAD_NC(GPP_B10, NONE),
/* EXT_PWR_GATE# */
/* SLP_S0# */		PAD_CFG_NF(GPP_B12, NONE, DEEP, NF1), /* SLP_SO_L */
/* PLTRST# */		PAD_CFG_NF(GPP_B13, NONE, DEEP, NF1), /* PLT_RST_L */
/* SPKR */		PAD_CFG_GPI(GPP_B14, NONE, DEEP), /* GPP_B14_STRAP */
#if IS_ENABLED(CONFIG_ZOOMBINI_USE_SPI_TPM)
/* GSPI0_CS# */		PAD_CFG_NF(GPP_B15, NONE, DEEP,
				   NF1), /* H1_SLAVE_SPI_CS_L */
/* GSPI0_CLK */		PAD_CFG_NF(GPP_B16, NONE, DEEP,
				   NF1), /* H1_SLAVE_SPI_CLK */
/* GSPI0_MISO */	PAD_CFG_NF(GPP_B17, NONE, DEEP,
				   NF1), /* H1_SLAVE_SPI_MISO_R */
/* GSPI0_MOSI */	PAD_CFG_NF(GPP_B18, NONE, DEEP,
				   NF1), /* H1_SLAVE_SPI_MOSI_R */
#else
/* GSPI0_CS# */		PAD_NC(GPP_B15, NONE),
/* GSPI0_CLK */		PAD_NC(GPP_B16, NONE),
/* GSPI0_MISO */	PAD_NC(GPP_B17, NONE),
/* GSPI0_MOSI */	PAD_NC(GPP_B18, NONE),
#endif
/* GSPI1_CS# */		PAD_CFG_NF(GPP_B19, NONE, DEEP,
				   NF1), /* PCH_FPMCU_SPI_CS_L */
/* GSPI1_CLK */		PAD_CFG_NF(GPP_B20, NONE, DEEP,
				   NF1), /* PCH_FPMCU_SPI_CLK */
/* GSPI1_MISO */	PAD_CFG_NF(GPP_B21, NONE, DEEP,
				   NF1), /* PCH_FPMCU_SPI_MISO_R */
/* GSPI1_MOSI */	PAD_CFG_NF(GPP_B22, NONE, DEEP,
				   NF1), /* PCH_FPMCU_SPI_MOSI_R */
/* SML1ALERT# */	PAD_CFG_GPI(GPP_B23, NONE, DEEP), /* GPP_B23_STRAP */
/* SMBCLK */		PAD_NC(GPP_C0, NONE),
/* SMBDATA */		PAD_CFG_GPI(GPP_C1, NONE,
				    DEEP), /* PCIE_8_WLAN_WAKE_ODL */
/* SMBALERT# */		PAD_CFG_GPI(GPP_C2, NONE, DEEP), /* GPP_C2_STRAP */
/* SML0CLK */		PAD_CFG_GPI(GPP_C3, NONE, DEEP), /* PCH_SAR1_INT_L */
/* SML0DATA */		PAD_CFG_GPI(GPP_C4, NONE, DEEP), /* PCH_SAR0_INT_L */
/* SML0ALERT# */	PAD_CFG_GPI(GPP_C5, NONE, DEEP), /* GPP_C5_STRAP */
/* SM1CLK */		PAD_CFG_GPO(GPP_C6, 0, DEEP), /* PCH_SAR_PWR_EN */
/* SM1DATA */		PAD_NC(GPP_C7, NONE),
/* UART0_RXD */		PAD_CFG_NF(GPP_C8, NONE, DEEP,
				   NF1), /* UART_PCH_RX_DEBUG_TX */
/* UART0_TXD */		PAD_CFG_NF(GPP_C9, NONE, DEEP,
				   NF1), /* UART_PCH_TX_DEBUG_RX */
/* UART0_RTS# */	PAD_CFG_GPO(GPP_C10, 0, DEEP), /* PP3300_TOUCH_EN */
/* UART0_CTS# */	PAD_NC(GPP_C11, NONE),
/* UART1_RXD */         PAD_CFG_GPI_SCI_LOW(GPP_C12, NONE, DEEP,
					    LEVEL), /* H1_PCH_INT_ODL */
/* UART1_TXD */		PAD_NC(GPP_C13, NONE),
/* UART1_RTS# */	PAD_CFG_GPI_SCI(GPP_C14, NONE, DEEP, EDGE_SINGLE,
					NONE), /* TOUCHSCREEN_INT_ODL */
/* UART1_CTS# */	PAD_NC(GPP_C15, NONE),
/* I2C0_SDA */		PAD_CFG_NF(GPP_C16, NONE, DEEP,
				   NF1), /* PCH_TOUCHSCREEN_I2C0_SDA */
/* I2C0_SCL */		PAD_CFG_NF(GPP_C17, NONE, DEEP,
				   NF1), /* PCH_TOUCHSCREEN_I2C0_SCL */
/* I2C1_SDA */		PAD_CFG_NF(GPP_C18, NONE, DEEP,
				   NF1), /* PCH_DISPLAY_SAR1_I2C1_SDA */
/* I2C1_SCL */		PAD_CFG_NF(GPP_C19, NONE, DEEP,
				   NF1), /* PCH_DISPLAY_SAR1_I2C1_SCL */
/* UART2_RXD */		PAD_NC(GPP_C20, NONE),
/* UART2_TXD */		PAD_NC(GPP_C21, NONE),
/* UART2_RTS# */	PAD_NC(GPP_C22, NONE),
/* UART2_CTS# */	PAD_NC(GPP_C23, NONE),
/* SPI1_CS# */		PAD_CFG_GPI(GPP_D0, NONE, DEEP), /* PCH_MEM_STRAP3 */
/* SPI1_CLK */		PAD_NC(GPP_D1, NONE),
/* SPI1_MISO */		PAD_NC(GPP_D2, NONE),
/* SPI1_MOSI */		PAD_CFG_GPI(GPP_D3, NONE, DEEP), /* PCH_MEM_STRAP0 */
/* FASHTRIG */		PAD_CFG_NF(GPP_D4, NONE, DEEP, NF1), /* FCAM_MCLK */
/* ISH_I2C0_SDA */	PAD_NC(GPP_D5, NONE),
/* ISH_I2C0_SCL */	PAD_NC(GPP_D6, NONE),
/* ISH_I2C1_SDA */	PAD_CFG_GPO(GPP_D7, 1, DEEP), /* FCAM_RST_L */
/* ISH_I2C1_SCL */	PAD_CFG_GPO(GPP_D8, 0, DEEP), /* DMIC_PWR_EN */
/* ISH_SPI_CS# */	PAD_NC(GPP_D9, NONE),
/* ISH_SPI_CLK */	PAD_CFG_GPO(GPP_D10, 0, DEEP), /* FCAM_PWR_EN */
/* ISH_SPI_MISO */	PAD_NC(GPP_D11, NONE),
/* ISH_SPI_MOSI */	PAD_CFG_GPI(GPP_D12, NONE, DEEP), /* GPP_D12_STRAP */
/* ISH_UART0_RXD */	PAD_NC(GPP_D13, NONE), /* ISH_UART_RX */
/* ISH_UART0_TXD */	PAD_NC(GPP_D14, NONE), /* ISH_UART_TX */
/* ISH_UART0_RTS# */	PAD_CFG_GPO(GPP_D15, 1, DEEP), /* TOUCHSCREEN_RST_ODL */
/* ISH_UART0_CTS# */	PAD_CFG_GPO(GPP_D16, 0, DEEP), /* SPKR_HWRST_L */
/* DMIC_CLK1 */		PAD_CFG_NF(GPP_D17, NONE, DEEP,
				   NF1), /* DB0_PCH_DMIC_CLK_R */
/* DMIC_DATA1 */	PAD_CFG_NF(GPP_D18, NONE, DEEP,
				   NF1), /* DB0TX_PCHRX_DMIC_DATA */
/* DMIC_CLK0 */		PAD_NC(GPP_D19, NONE),
/* DMIC_DATA0 */	PAD_NC(GPP_D20, NONE),
/* SPI1_IO2 */		PAD_CFG_GPI(GPP_D21, NONE, DEEP), /* PCH_MEM_STRAP1 */
/* SPI1_IO3 */		PAD_CFG_GPI(GPP_D22, NONE, DEEP), /* PCH_MEM_STRAP2 */
/* I2S_MCLK */
/* SATAXPCI0 */		PAD_CFG_GPO(GPP_E0, 0, DEEP), /* RCAM_PWR_EN */
/* SATAXPCIE1 */	PAD_CFG_GPO(GPP_E1, 1, DEEP), /* RCAM_RST_L */
/* SATAXPCIE2 */	PAD_NC(GPP_E2, NONE),
/* CPU_GP0 */		PAD_NC(GPP_E3, NONE),
/* SATA_DEVSLP0 */	PAD_NC(GPP_E4, NONE),
/* SATA_DEVSLP1 */	PAD_NC(GPP_E5, NONE),
/* SATA_DEVSLP2 */	PAD_NC(GPP_E6, NONE),
/* CPU_GP1 */		PAD_NC(GPP_E7, NONE),
/* SATALED# */		PAD_NC(GPP_E8, NONE),
/* USB2_OCO# */		PAD_CFG_NF(GPP_E9, NONE, DEEP, NF2), /* DCI_CLK */
/* USB2_OC1# */		PAD_CFG_NF(GPP_E10, NONE, DEEP, NF2), /* DCI_DATA */
/* USB2_OC2# */		PAD_CFG_NF(GPP_E11, NONE, DEEP,
				   NF1), /* USB_C0_OC_ODL */
/* USB2_OC3# */		PAD_CFG_NF(GPP_E12, NONE, DEEP,
				   NF1), /* USB_C1_OC_ODL */
/* DDPB_HPD0 */		PAD_CFG_NF(GPP_E13, NONE, DEEP,
				   NF1), /* EC_USB_C0_HPD */
/* DDPC_HPD1 */		PAD_CFG_NF(GPP_E14, NONE, DEEP,
				   NF1), /* EC_USB_C1_HPD */
/* DDPD_HPD2 */		PAD_CFG_NF(GPP_E15, NONE, DEEP,
				   NF1), /* EC_USB_C2_HPD */
/* DDPE_HPD3 */		PAD_NC(GPP_E16, NONE),
/* EDP_HPD */
/* DDPB_CTRLCLK */	PAD_NC(GPP_E18, NONE),
/* DDPB_CTRLDATA */	PAD_CFG_GPI(GPP_E19, NONE, DEEP), /* GPP_E19_STRAP */
/* DDPC_CTRLCLK */	PAD_NC(GPP_E20, NONE),
/* DDPC_CTRLDATA */	PAD_CFG_GPI(GPP_E21, NONE, DEEP), /* GPP_E21_STRAP */
/* DDPD_CTRLCLK */	PAD_NC(GPP_E22, NONE),
/* DDPD_CTRLDATA */	PAD_CFG_GPI(GPP_E23, NONE, DEEP), /* GPP_E23_STRAP */
/* I2S2_SFRM */		PAD_CFG_GPO(GPP_F1, 0, DEEP),
					/* WWAN_RESET_1V8_ODL */
/* I2S2_TXD */		PAD_NC(GPP_F2, NONE),
/* I2S2_RXD */		PAD_NC(GPP_F3, NONE),
/* I2C2_SDA */		PAD_CFG_NF(GPP_F4, NONE, DEEP, NF1), /* CNV_BRI_DT_R */
/* I2C2_SCL */		PAD_CFG_NF(GPP_F5, NONE, DEEP, NF1), /* CNV_BRI_RSP */
/* I2C3_SDA */		PAD_CFG_NF(GPP_F6, NONE, DEEP, NF1), /* CNV_RGI_DT_R */
/* I2C3_SCL */		PAD_CFG_NF(GPP_F7, NONE, DEEP, NF1), /* CNV_RGI_RSP */
/* I2C4_SDA */		PAD_NC(GPP_F8, NONE),
/* I2C4_SCL */		PAD_NC(GPP_F9, NONE),
/* I2C5_SDA */		PAD_CFG_GPI(GPP_F10, NONE,
				    DEEP), /* OPVR_MCIVR_BREAK_L */
/* I2C5_SCL */		PAD_CFG_NF(GPP_F11, NONE, DEEP, NF1), /* EMMC_CMD */
/* EMMC_CMD */		PAD_CFG_NF(GPP_F12, NONE, DEEP, NF1), /* EMMC_DAT0 */
/* EMMC_DATA0 */	PAD_CFG_NF(GPP_F13, NONE, DEEP, NF1), /* EMMC_DAT1 */
/* EMMC_DATA1 */	PAD_CFG_NF(GPP_F14, NONE, DEEP, NF1), /* EMMC_DAT2 */
/* EMMC_DATA2 */	PAD_CFG_NF(GPP_F15, NONE, DEEP, NF1), /* EMMC_DAT3 */
/* EMMC_DATA3 */	PAD_CFG_NF(GPP_F16, NONE, DEEP, NF1), /* EMMC_DAT4 */
/* EMMC_DATA4 */	PAD_CFG_NF(GPP_F17, NONE, DEEP, NF1), /* EMMC_DAT5 */
/* EMMC_DATA5 */	PAD_CFG_NF(GPP_F18, NONE, DEEP, NF1), /* EMMC_DAT6 */
/* EMMC_DATA6 */	PAD_CFG_NF(GPP_F19, NONE, DEEP, NF1), /* EMMC_DAT7 */
/* EMMC_DATA7 */	PAD_CFG_NF(GPP_F20, NONE, DEEP, NF1), /* EMMC_RCLK */
/* EMMC_RCLK */		PAD_CFG_NF(GPP_F21, NONE, DEEP, NF1), /* EMMC_CLK */
/* EMMC_CLK */		PAD_CFG_NF(GPP_F22, NONE, DEEP, NF1), /* EMMC_RST_ODL */
/* RSVD */
/* SD_CMD */		PAD_NC(GPP_G0, NONE),
/* SD_DATA0 */		PAD_NC(GPP_G1, NONE),
/* SD_DATA1 */		PAD_NC(GPP_G2, NONE),
/* SD_DATA2 */		PAD_NC(GPP_G3, NONE),
/* SD_DATA3 */		PAD_NC(GPP_G4, NONE),
/* SD_CD# */		PAD_NC(GPP_G5, NONE),
/* SD_CLK */		PAD_NC(GPP_G6, NONE),
/* SD_WP */		PAD_NC(GPP_G7, NONE),
/* I2S2_SCLK */		PAD_NC(GPP_H0, NONE),
/* I2S2_SFRM */		PAD_CFG_NF(GPP_H1, NONE, DEEP,
				   NF3), /* CNV_RF_RESET_L */
/* I2S2_TXD */		PAD_CFG_NF(GPP_H2, NONE, DEEP, NF3), /* WLAN_CLKREQ0 */
/* I2S2_RXD */		PAD_NC(GPP_H3, NONE),
/* I2C2_SDA */		PAD_CFG_NF(GPP_H4, NONE, DEEP,
				   NF1), /* PCH_BL_I2C2_SDA */
/* I2C2_SCL */		PAD_CFG_NF(GPP_H5, NONE, DEEP,
				   NF1), /* PCH_BL_I2C2_SCL */
/* I2C3_SDA */		PAD_CFG_NF(GPP_H6, NONE, DEEP,
				   NF1), /* PCH_AUDIO_I2C3_SDA */
/* I2C3_SCL */		PAD_CFG_NF(GPP_H7, NONE, DEEP,
				   NF1), /* PCH_AUDIO_I2C3_SCL */
/* I2C4_SDA */		PAD_CFG_NF(GPP_H8, NONE, DEEP,
				   NF1), /* PCH_FCAM_I2C4_SDA */
/* I2C4_SCL */		PAD_CFG_NF(GPP_H9, NONE, DEEP,
				   NF1), /* PCH_FCAM_I2C4_SCL */
/* I2C5_SDA */		PAD_CFG_NF(GPP_H10, NONE, DEEP,
				   NF1), /* PCH_RCAM_SAR0_I2C5_SDA */
/* I2C5_SCL */		PAD_CFG_NF(GPP_H11, NONE, DEEP,
				   NF1), /* PCH_RCAM_SAR0_I2C5_SCL */
/* M2_SKT2_CFG0 */	PAD_NC(GPP_H12, NONE),
/* M2_SKT2_CFG1 */	PAD_NC(GPP_H13, NONE),
/* M2_SKT2_CFG2 */	PAD_NC(GPP_H14, NONE),
/* M2_SKT2_CFG3 */	PAD_NC(GPP_H15, NONE),
/* DDPF_CTRLCLK */
/* DPPF_CTRLDATA */
/* CPU_C10_GATE# */	PAD_CFG_NF(GPP_H18, NONE, DEEP,
				   NF1), /* CPU_C10_GATE_PCH_L */
/* TIMESYNC0 */		PAD_NC(GPP_H19, NONE),
/* IMGCLKOUT1 */	PAD_CFG_NF(GPP_H20, NONE, DEEP, NF1), /* RCAM_MCLK */
/* GPP_H21 */		PAD_CFG_GPI(GPP_H21, NONE, DEEP), /* H21_STRAP */
/* GPP_H22 */		PAD_NC(GPP_H22, NONE),
/* GPP_H23 */		PAD_CFG_GPI(GPP_H23, NONE, DEEP), /* GPP_H23 */

/* BATLOW# */		PAD_CFG_NF(GPD0, NONE, DEEP, NF1), /* BATLOW_L */
/* ACPRESENT */		PAD_NC(GPD1, NONE),
/* LAN_WAKE# */		PAD_CFG_GPI(GPD2, NONE, DEEP), /* EC_PCH_WAKE_ODL */
/* PWRBTN# */		PAD_CFG_NF(GPD3, NONE, DEEP,
				   NF1), /* EC_PCH_PWR_BTN_ODL */
/* SLP_S3# */		PAD_CFG_NF(GPD4, NONE, DEEP, NF1), /* SLP_S3_L */
/* SLP_S4# */		PAD_CFG_NF(GPD5, NONE, DEEP, NF1), /* SLP_S4_L */
/* SLP_A# */		PAD_NC(GPD6, NONE),
/* RSVD */		PAD_CFG_GPI(GPD7, NONE, DEEP), /* DPD7_Strap */
/* SUSCLK */		PAD_CFG_NF(GPD8, NONE, DEEP, NF1), /* PCH_SUSCLK */
/* SLP_WLAN# */		PAD_NC(GPD9, NONE),
/* SLP_S5# */		PAD_NC(GPD10, NONE),
/* LANPHYC */		PAD_NC(GPD11, NONE),
};

/* Early pad configuration in bootblock */
static const struct pad_config early_gpio_table[] = {
#if IS_ENABLED(CONFIG_ZOOMBINI_USE_SPI_TPM)
/* GSPI0_CS# */		PAD_CFG_NF(GPP_B15, NONE, DEEP,
				   NF1), /* PCH_SPI_H1_3V3_CS_L */
/* GSPI0_CLK */		PAD_CFG_NF(GPP_B16, NONE, DEEP,
				   NF1), /* PCH_SPI_H1_3V3_CLK */
/* GSPI0_MISO */	PAD_CFG_NF(GPP_B17, NONE, DEEP,
				   NF1), /* PCH_SPI_H1_3V3_MISO */
/* GSPI0_MOSI */	PAD_CFG_NF(GPP_B18, NONE, DEEP,
				   NF1), /* PCH_SPI_H1_3V3_MOSI */
#else
/* GSPI0_CS# */		PAD_NC(GPP_B15, NONE),
/* GSPI0_CLK */		PAD_NC(GPP_B16, NONE),
/* GSPI0_MISO */	PAD_NC(GPP_B17, NONE),
/* GSPI0_MOSI */	PAD_NC(GPP_B18, NONE),
#endif
/* UART1_RXD */         PAD_CFG_GPI_SCI_LOW(GPP_C12, NONE, DEEP, LEVEL),
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
