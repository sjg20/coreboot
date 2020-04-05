/* SPDX-License-Identifier: GPL-2.0-only */
/* This file is part of the coreboot project. */

#include <baseboard/gpio.h>
#include <baseboard/variants.h>
#include <commonlib/helpers.h>

/* Pad configuration in ramstage */
/* Leave eSPI pins untouched from default settings */
static const struct pad_config gpio_table[] = {
/* RCIN# */		PAD_CFG_NC(GPP_A0), /* TP308 */
/* ESPI_IO0 */
/* ESPI_IO1 */
/* ESPI_IO2 */
/* ESPI_IO3 */
/* ESPI_CS# */
/* SERIRQ */		PAD_CFG_NC(GPP_A6), /* TP331 */
/* PIRQA# */		PAD_CFG_NC(GPP_A7), /* TP104 */
/* CLKRUN# */		PAD_CFG_NC(GPP_A8), /* TP329 */
/* ESPI_CLK */
/* CLKOUT_LPC1 */	PAD_CFG_NC(GPP_A10), /* TP188 */
/* PME# */		PAD_CFG_NC(GPP_A11), /* TP149 */
/* BM_BUSY# */		PAD_CFG_NC(GPP_A12),
/* SUSWARN# */		PAD_CFG_GPI_GPIO_DRIVER(GPP_A13, NONE,
						DEEP), /* eSPI mode */
/* ESPI_RESET# */
/* SUSACK# */		PAD_CFG_NC(GPP_A15), /* TP150 */
/* SD_1P8_SEL */	PAD_CFG_NC(GPP_A16),
/* SD_PWR_EN# */	PAD_CFG_NC(GPP_A17),
/* ISH_GP0 */		PAD_CFG_GPO(GPP_A18, 0, DEEP), /* 7322_OE */
/* ISH_GP1 */		PAD_CFG_GPI_GPIO_DRIVER(GPP_A19, NONE, DEEP), /* HDPO */
/* ISH_GP2 */		PAD_CFG_NC(GPP_A20),
/* ISH_GP3 */		PAD_CFG_NC(GPP_A21),
/* ISH_GP4 */		PAD_CFG_NC(GPP_A22),
/* ISH_GP5 */		PAD_CFG_GPO(GPP_A23, 1, DEEP), /* PCH_SPK_EN */

/* CORE_VID0 */		PAD_CFG_NC(GPP_B0), /* TP156 */
/* CORE_VID1 */		PAD_CFG_NC(GPP_B1),
/* VRALERT# */		PAD_CFG_NC(GPP_B2), /* TP152 */
/* CPU_GP2 */		PAD_CFG_GPO(GPP_B3, 0, DEEP), /* TOUCHSCREEN_RST# */
/* CPU_GP3 */		PAD_CFG_GPO(GPP_B4, 1, DEEP), /* PCH_TS_EN */
/* SRCCLKREQ0# */	PAD_CFG_NF(GPP_B5, NONE, DEEP,
				   NF1), /* CLK_PCIE_LAN_REQ# */
/* SRCCLKREQ1# */	PAD_CFG_NF(GPP_B6, NONE, DEEP,
				   NF1), /* PCIE_CLKREQ_SSD# */
/* SRCCLKREQ2# */	PAD_CFG_NF(GPP_B7, NONE, DEEP,
				   NF1), /* PCIE_CLKREQ_NGFF1# */
/* SRCCLKREQ3# */	PAD_CFG_NC(GPP_B8), /* TP333 */
/* SRCCLKREQ4# */	PAD_CFG_NC(GPP_B9), /* TP139 */
/* SRCCLKREQ5# */	PAD_CFG_NF(GPP_B10, NONE, DEEP,
				   NF1), /* PCIE_CLKREQ_WLAN# */
/* EXT_PWR_GATE# */	PAD_CFG_NF(GPP_B11, NONE, DEEP, NF1), /* MPHY_EXT_PWR */
/* SLP_S0# */		PAD_CFG_NF(GPP_B12, NONE, DEEP, NF1), /* PM_SLP_S0# */
/* PLTRST# */		PAD_CFG_NF(GPP_B13, NONE, DEEP, NF1), /* PCI_PLTRST# */
/* SPKR */		PAD_CFG_NF(GPP_B14, NONE, DEEP, NF1), /* SPKR */
/* GSPI0_CS# */		PAD_CFG_NF(GPP_B15, NONE, DEEP,
				   NF1), /* PCH_SPI_H1_3V3_CS_L */
/* GSPI0_CLK */		PAD_CFG_NF(GPP_B16, NONE, DEEP,
				   NF1), /* PCH_SPI_H1_3V3_CLK */
/* GSPI0_MISO */	PAD_CFG_NF(GPP_B17, NONE, DEEP,
				   NF1), /* PCH_SPI_H1_3V3_MISO */
/* GSPI0_MOSI */	PAD_CFG_NF(GPP_B18, NONE, DEEP,
				   NF1), /* PCH_SPI_H1_3V3_MOSI */
/* GSPI1_CS# */		PAD_CFG_NC(GPP_B19), /* TP111 */
/* GSPI1_CLK */		PAD_CFG_GPI_GPIO_DRIVER(GPP_B20, 20K_PU,
						DEEP), /* VR_DISABLE_L */
/* GSPI1_MISO */	PAD_CFG_GPI_GPIO_DRIVER(GPP_B21, 20K_PU,
						DEEP), /* HWA_TRST_N */
/* GSPI1_MOSI */	PAD_CFG_NC(GPP_B22), /* GSPI1_MOSI */
/* SML1ALERT# */		PAD_CFG_NC(GPP_B23), /* TP141 */

/* SMBCLK */		PAD_CFG_NF(GPP_C0, NONE, DEEP, NF1), /* PCH_MBCLK0_R */
/* SMBDATA */		PAD_CFG_NF(GPP_C1, NONE, DEEP, NF1), /* PCH_MBDAT0_R */
/* SMBALERT# */		PAD_CFG_NC(GPP_C2),
/* SML0CLK */		PAD_CFG_NC(GPP_C3),
/* SML0DATA */		PAD_CFG_NC(GPP_C4),
/* SML0ALERT# */	PAD_CFG_NF(GPP_C5, NONE, DEEP, NF1),
/* SM1CLK */		PAD_CFG_GPI_GPIO_DRIVER(GPP_C6, 20K_PU,
						DEEP), /* EC_IN_RW */
/* SM1DATA */		PAD_CFG_NC(GPP_C7), /* TP310 */
/* UART0_RXD */		PAD_CFG_GPI_GPIO_DRIVER(GPP_C8, 20K_PU,
							DEEP), /* GPIO1 */
/* UART0_TXD */		PAD_CFG_GPI_GPIO_DRIVER(GPP_C9, 20K_PU,
							DEEP), /* GPIO2 */
/* UART0_RTS# */	PAD_CFG_GPO(GPP_C10, 1, DEEP), /* V3P3_CCD_EN */
/* UART0_CTS# */	PAD_CFG_GPI_GPIO_DRIVER(GPP_C11, 20K_PU,
						DEEP), /* GPIO4 */
/* UART1_RXD */		PAD_CFG_GPI_GPIO_DRIVER(GPP_C12, NONE,
							DEEP), /* SKU_ID0 */
/* UART1_TXD */		PAD_CFG_GPI_GPIO_DRIVER(GPP_C13, NONE,
							DEEP), /* SKU_ID1 */
/* UART1_RTS# */	PAD_CFG_GPI_GPIO_DRIVER(GPP_C14, NONE,
						DEEP), /* SKU_ID2 */
/* UART1_CTS# */	PAD_CFG_GPI_GPIO_DRIVER(GPP_C15, NONE,
						DEEP), /* SKU_ID3 */
/* I2C0_SDA */		PAD_CFG_NF(GPP_C16, NONE, DEEP, NF1),
/* I2C0_SCL */		PAD_CFG_NF(GPP_C17, NONE, DEEP, NF1),
/* I2C1_SDA */		PAD_CFG_NC(GPP_C18),
/* I2C1_SCL */		PAD_CFG_NC(GPP_C19),
/* UART2_RXD */		PAD_CFG_NF(GPP_C20, NONE, DEEP, NF1), /* SERVO */
/* UART2_TXD */		PAD_CFG_NF(GPP_C21, NONE, DEEP, NF1), /* SERVO */
/* UART2_RTS# */	PAD_CFG_NC(GPP_C22), /* TP309 */
/* UART2_CTS# */	PAD_CFG_GPI_GPIO_DRIVER(GPP_C23, NONE,
				    DEEP), /* SCREW_SPI_WP_STATUS */

/* SPI1_CS# */		PAD_CFG_NC(GPP_D0), /* TP259 */
/* SPI1_CLK */		PAD_CFG_NC(GPP_D1), /* TP260 */
/* SPI1_MISO */		PAD_CFG_NC(GPP_D2), /* TP261 */
/* SPI1_MOSI */		PAD_CFG_NC(GPP_D3), /* TP262 */
/* FASHTRIG */		PAD_CFG_NC(GPP_D4), /* TP153 */
/* ISH_I2C0_SDA */	PAD_CFG_NF(GPP_D5, NONE, DEEP,
						NF1), /* PCH_I2C0_8625_SDA */
/* ISH_I2C0_SCL */	PAD_CFG_NF(GPP_D6, NONE, DEEP,
						NF1), /* PCH_I2C0_8625_SCL */
/* ISH_I2C1_SDA */	PAD_CFG_NC(GPP_D7),
/* ISH_I2C1_SCL */	PAD_CFG_NC(GPP_D8),
/* ISH_SPI_CS# */	PAD_CFG_GPI_APIC(GPP_D9, NONE,
						PLTRST), /* HP_IRQ_GPIO */
/* ISH_SPI_CLK */	PAD_CFG_GPI_GPIO_DRIVER(GPP_D10, NONE,
						DEEP), /* OEM_ID1 */
/* ISH_SPI_MISO */	PAD_CFG_GPI_GPIO_DRIVER(GPP_D11, NONE,
						DEEP), /* OEM_ID2 */
/* ISH_SPI_MOSI */	PAD_CFG_GPI_GPIO_DRIVER(GPP_D12, NONE,
						DEEP), /* OEM_ID3 */
/* ISH_UART0_RXD */	PAD_CFG_NC(GPP_D13),
/* ISH_UART0_TXD */	PAD_CFG_NC(GPP_D14),
/* ISH_UART0_RTS# */	PAD_CFG_NC(GPP_D15),
/* ISH_UART0_CTS# */	PAD_CFG_NC(GPP_D16),
/* DMIC_CLK1 */		PAD_CFG_NC(GPP_D17),
/* DMIC_DATA1 */	PAD_CFG_NC(GPP_D18),
/* DMIC_CLK0 */		PAD_CFG_NF(GPP_D19, NONE, DEEP,
						NF1), /* PCH_DMIC_CLK0 */
/* DMIC_DATA0 */	PAD_CFG_NF(GPP_D20, NONE, DEEP,
						NF1), /* PCH_DMIC_DATA0 */
/* SPI1_IO2 */		PAD_CFG_NC(GPP_D21), /* TP257 */
/* SPI1_IO3 */		PAD_CFG_GPO(GPP_D22, 1, DEEP), /* BOOT_BEEP_OVERRIDE */
/* I2S_MCLK */		PAD_CFG_NF(GPP_D23, NONE, DEEP, NF1), /* I2S_MCLK */

/* SATAXPCI0 */		PAD_CFG_GPI_APIC_INVERT(GPP_E0, NONE,
						PLTRST), /* H1_PCH_INT_ODL */
/* SATAXPCIE1 */	PAD_CFG_NF(GPP_E1, NONE, DEEP,
				   NF1), /* MB_PCIE_SATA#_DET */
/* SATAXPCIE2 */	PAD_CFG_NF(GPP_E2, 20K_PU, DEEP,
				   NF1), /* DB_PCIE_SATA#_DET */
/* CPU_GP0 */		PAD_CFG_NC(GPP_E3),
/* SATA_DEVSLP0 */	PAD_CFG_NC(GPP_E4), /* TP103 */
/* SATA_DEVSLP1 */	PAD_CFG_NF(GPP_E5, NONE, DEEP, NF1), /* DEVSLP1_MB */
/* SATA_DEVSLP2 */	PAD_CFG_NC(GPP_E6), /* DEVSLP2_DB */
/* CPU_GP1 */		PAD_CFG_GPI_APIC(GPP_E7, NONE,
					PLTRST), /* TOUCHSCREEN_INT# */
/* SATALED# */		PAD_CFG_NC(GPP_E8), /* TP314 */
/* USB2_OCO# */		PAD_CFG_NF(GPP_E9, NONE, DEEP, NF1), /* USB-C */
/* USB2_OC1# */		PAD_CFG_NF(GPP_E10, NONE, DEEP,
					NF1), /* Rear Dual-Stack USB Ports */
/* USB2_OC2# */		PAD_CFG_NF(GPP_E11, NONE, DEEP,
					   NF1), /* Front USB Ports */
/* USB2_OC3# */		PAD_CFG_NF(GPP_E12, NONE, DEEP,
					   NF1), /* Rear Single USB Port */
/* DDPB_HPD0 */		PAD_CFG_NF(GPP_E13, NONE, DEEP,
					   NF1), /* INT_HDMI_HPD */
/* DDPC_HPD1 */		PAD_CFG_NF(GPP_E14, NONE, DEEP,
					   NF1), /* DDI2_HPD */
/* DDPD_HPD2 */		PAD_CFG_NC(GPP_E15), /* TP325 */
/* DDPE_HPD3 */		PAD_CFG_NC(GPP_E16), /* TP326 */
/* EDP_HPD */		PAD_CFG_NF(GPP_E17, NONE, DEEP, NF1),
/* DDPB_CTRLCLK */	PAD_CFG_NF(GPP_E18, NONE, DEEP,
				   NF1), /* HDMI_DDCCLK_SW */
/* DDPB_CTRLDATA */	PAD_CFG_NF(GPP_E19, 20K_PD, DEEP,
				   NF1), /* HDMI_DDCCLK_DATA */
/* DDPC_CTRLCLK */	PAD_CFG_NF(GPP_E20, NONE, DEEP, NF1), /* CRT CLK */
/* DDPC_CTRLDATA */	PAD_CFG_NF(GPP_E21, NONE, DEEP, NF1), /* CRT DATA */
/* DDPD_CTRLCLK */	PAD_CFG_GPO(GPP_E22, 1, DEEP), /* DP_RST_L */
/* DDPD_CTRLDATA */	PAD_CFG_GPO(GPP_E23, 1, DEEP), /* DP_PD_L */

/* I2S2_SCLK */		PAD_CFG_GPI_GPIO_DRIVER(GPP_F0, NONE,
						DEEP), /* I2S_2_BCLK */
/* I2S2_SFRM */		PAD_CFG_GPI_GPIO_DRIVER(GPP_F1, NONE,
						DEEP), /* I2S_2_FS_LRC */
/* I2S2_TXD */		PAD_CFG_GPI_GPIO_DRIVER(GPP_F2, NONE,
						DEEP), /* I2S_2_TX_DAC */
/* I2S2_RXD */		PAD_CFG_NC(GPP_F3), /* TP189 */
/* I2C2_SDA */		PAD_CFG_NF(GPP_F4, NONE, DEEP,
				   NF1), /* PCH_I2C2_H1_3V3_SDA */
/* I2C2_SCL */		PAD_CFG_NF(GPP_F5, NONE, DEEP,
				   NF1), /* PCH_I2C2_H1_3V3_SCL */
/* I2C3_SDA */		PAD_CFG_NC(GPP_F6),
/* I2C3_SCL */		PAD_CFG_NC(GPP_F7),
/* I2C4_SDA */		PAD_CFG_NC(GPP_F8),
/* I2C4_SCL */		PAD_CFG_NC(GPP_F9),
/* I2C5_SDA */		PAD_CFG_NF_1V8(GPP_F10, NONE, DEEP,
				       NF1), /* PCH_I2C2_AUDIO_1V8_SDA */
/* I2C5_SCL */		PAD_CFG_NF_1V8(GPP_F11, NONE, DEEP,
				       NF1), /* PCH_I2C2_AUDIO_1V8_SCL */
/* EMMC_CMD */		PAD_CFG_NC(GPP_F12),
/* EMMC_DATA0 */	PAD_CFG_NC(GPP_F13),
/* EMMC_DATA1 */	PAD_CFG_NC(GPP_F14),
/* EMMC_DATA2 */	PAD_CFG_NC(GPP_F15),
/* EMMC_DATA3 */	PAD_CFG_NC(GPP_F16),
/* EMMC_DATA4 */	PAD_CFG_NC(GPP_F17),
/* EMMC_DATA5 */	PAD_CFG_NC(GPP_F18),
/* EMMC_DATA6 */	PAD_CFG_NC(GPP_F19),
/* EMMC_DATA7 */	PAD_CFG_NC(GPP_F20),
/* EMMC_RCLK */		PAD_CFG_NC(GPP_F21),
/* EMMC_CLK */		PAD_CFG_NC(GPP_F22),
/* RSVD */		PAD_CFG_NC(GPP_F23),

/* SD_CMD */		PAD_CFG_NC(GPP_G0),
/* SD_DATA0 */		PAD_CFG_NC(GPP_G1),
/* SD_DATA1 */		PAD_CFG_NC(GPP_G2),
/* SD_DATA2 */		PAD_CFG_NC(GPP_G3),
/* SD_DATA3 */		PAD_CFG_NC(GPP_G4),
/* SD_CD# */		PAD_CFG_NC(GPP_G5),
/* SD_CLK */		PAD_CFG_NC(GPP_G6),
/* SD_WP */		PAD_CFG_NC(GPP_G7), /* TP292 */

/* BATLOW# */		PAD_CFG_NC(GPD0), /* TP148 */
/* ACPRESENT */		PAD_CFG_NF(GPD1, NONE, DEEP, NF1), /* PCH_ACPRESENT */
/* LAN_WAKE# */		PAD_CFG_NF(GPD2, NONE, DEEP, NF1), /* EC_PCH_WAKE# */
/* PWRBTN# */		PAD_CFG_NF(GPD3, 20K_PU, DEEP, NF1), /* PCH_PWRBTN# */
/* SLP_S3# */		PAD_CFG_NF(GPD4, NONE, DEEP, NF1), /* PM_SLP_S3# */
/* SLP_S4# */		PAD_CFG_NF(GPD5, NONE, DEEP, NF1), /* PM_SLP_S4# */
/* SLP_A# */		PAD_CFG_NC(GPD6), /* TP147 */
/* RSVD */		PAD_CFG_NC(GPD7),
/* SUSCLK */		PAD_CFG_NF(GPD8, NONE, DEEP, NF1), /* SUS_CLK */
/* SLP_WLAN# */		PAD_CFG_NC(GPD9), /* TP146 */
/* SLP_S5# */		PAD_CFG_NC(GPD10), /* TP143 */
/* LANPHYC */		PAD_CFG_NC(GPD11),
};

/* Early pad configuration in bootblock */
static const struct pad_config early_gpio_table[] = {
/* GSPI0_CS# */		PAD_CFG_NF(GPP_B15, NONE, DEEP,
				   NF1), /* PCH_SPI_H1_3V3_CS_L */
/* GSPI0_CLK */		PAD_CFG_NF(GPP_B16, NONE, DEEP,
				   NF1), /* PCH_SPI_H1_3V3_CLK */
/* GSPI0_MISO */	PAD_CFG_NF(GPP_B17, NONE, DEEP,
				   NF1), /* PCH_SPI_H1_3V3_MISO */
/* GSPI0_MOSI */	PAD_CFG_NF(GPP_B18, NONE, DEEP,
				   NF1), /* PCH_SPI_H1_3V3_MOSI */
/* SATAXPCI0 */		PAD_CFG_GPI_APIC_INVERT(GPP_E0, NONE,
						PLTRST), /* H1_PCH_INT_ODL */
/* Ensure UART pins are in native mode for H1. */
/* UART2_RXD */		PAD_CFG_NF(GPP_C20, NONE, DEEP, NF1), /* SERVO */
/* UART2_TXD */		PAD_CFG_NF(GPP_C21, NONE, DEEP, NF1), /* SERVO */
/* UART2_CTS# */	PAD_CFG_GPI_GPIO_DRIVER(GPP_C23, NONE,
				    DEEP), /* SCREW_SPI_WP_STATUS */
/* SATAXPCIE1 */       PAD_CFG_NF(GPP_E1, NONE, DEEP,
				  NF1), /* MB_PCIE_SATA#_DET */
/* SATA_DEVSLP1 */     PAD_CFG_NF(GPP_E5, NONE, DEEP, NF1), /* DEVSLP1_MB */
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
