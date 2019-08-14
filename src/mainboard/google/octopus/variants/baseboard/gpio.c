/*
 * This file is part of the coreboot project.
 *
 * Copyright 2018 Intel Corp.
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

#include <arch/acpi.h>
#include <baseboard/gpio.h>
#include <baseboard/variants.h>
#include <commonlib/helpers.h>

/*
 * Pad configuration in ramstage. The order largely follows the 'GPIO Muxing'
 * table found in EDS vol 1, but some pins aren't grouped functionally in
 * the table so those were moved for more logical grouping.
 */
static const struct pad_config gpio_table[] = {
	/* NORTHWEST COMMUNITY GPIOS */
	PAD_NC(GPIO_0, DN_20K), /* TCK -- debug header NC */
	PAD_NC(GPIO_1, DN_20K), /* TRST_B -- debug header NC */
	PAD_NC(GPIO_2, UP_20K), /* TMS -- debug header NC */
	PAD_NC(GPIO_3, UP_20K), /* TDI -- debug header NC */
	PAD_NC(GPIO_4, UP_20K), /* TDO -- debug header NC */
	PAD_NC(GPIO_5, UP_20K), /* JTAGX -- unused */
	PAD_NC(GPIO_6, UP_20K), /* CX_PREQ_B -- debug header NC */
	PAD_NC(GPIO_7, UP_20K), /* CX_PRDY_B -- debug header NC */
	PAD_NC(GPIO_8, DN_20K), /* TRACE_0_CLK_VNN -- debug header NC */
	PAD_NC(GPIO_9, DN_20K), /* TRACE_0_DATA0_VNN -- debug header NC */
	PAD_NC(GPIO_10, DN_20K), /* TRACE_0_DATA1_VNN -- debug header NC */
	PAD_NC(GPIO_11, DN_20K), /* TRACE_0_DATA2_VNN -- debug header NC */
	PAD_NC(GPIO_12, DN_20K), /* TRACE_0_DATA3_VNN -- debug header NC */
	PAD_NC(GPIO_13, DN_20K), /* TRACE_0_DATA4_VNN -- debug header NC */
	PAD_NC(GPIO_14, DN_20K), /* TRACE_0_DATA5_VNN -- debug header NC */
	PAD_NC(GPIO_15, DN_20K), /* TRACE_0_DATA6_VNN -- debug header NC */
	PAD_NC(GPIO_16, DN_20K), /* TRACE_0_DATA7_VNN -- debug header NC */
	PAD_NC(GPIO_17, UP_20K), /* DBG_PTI_CLK_1 -- debug header NC */
	PAD_NC(GPIO_18, UP_20K), /* DBG_PTI_DATA_8 -- debug header NC */
	PAD_NC(GPIO_19, UP_20K), /* DBG_PTI_DATA_9 -- debug header NC */
	PAD_NC(GPIO_20, UP_20K), /* DBG_PTI_DATA_10 -- debug header NC */
	PAD_CFG_NF(GPIO_21, UP_20K, DEEP, NF2), /* CNV_MFUART2_RXD */
	PAD_CFG_NF_IOSSTATE(GPIO_22, UP_20K, DEEP, NF2, TxDRxE), /* CNV_MFUART2_TXD */
	PAD_CFG_NF(GPIO_23, UP_20K, DEEP, NF2), /* CNV_GNSS_PABLANKIt */
	PAD_NC(GPIO_24, UP_20K), /* TRACE_1_DATA6_VNN -- debug header NC */
	PAD_NC(GPIO_25, UP_20K), /* TRACE_1_DATA7_VNN -- debug header NC */
	PAD_NC(GPIO_26, DN_20K), /* TRACE_2_CLK_VNN -- debug header NC */
	PAD_NC(GPIO_27, DN_20K), /* TRACE_2_DATA0_VNN -- debug header NC */
	PAD_NC(GPIO_28, DN_20K), /* TRACE_2_DATA1_VNN 0-- debug header NC */
	PAD_NC(GPIO_29, DN_20K), /* TRACE_2_DATA2_VNN -- debug header NC */
	PAD_NC(GPIO_30, DN_20K), /* TRACE_2_DATA3_VNN -- debug header NC */
	PAD_NC(GPIO_31, DN_20K), /* TRACE_2_DATA4_VNN -- debug header NC */
	PAD_NC(GPIO_32, DN_20K), /* TRACE_2_DATA5_VNN -- debug header NC */
	PAD_NC(GPIO_33, DN_20K), /* TRACE_2_DATA6_VNN -- debug header NC */
	PAD_NC(GPIO_34, DN_20K), /* TRACE_2_DATA7_VNN -- debug header NC */
	PAD_NC(GPIO_35, UP_20K), /* TRACE_3_CLK_VNN -- debug header NC */
	PAD_NC(GPIO_36, UP_20K), /* TRACE_3_DATA0_VNN -- debug header NC */
	PAD_NC(GPIO_37, UP_20K), /* TRACE_3_DATA1_VNN -- debug header NC */
	PAD_NC(GPIO_38, UP_20K), /* TRACE_3_DATA2_VNN -- debug header NC */
	PAD_NC(GPIO_39, UP_20K), /* TRACE_3_DATA3_VNN -- unused */
	PAD_NC(GPIO_40, UP_20K), /* TRACE_3_DATA4_VNN -- unused */
	PAD_NC(GPIO_41, DN_20K), /* TRACE_3_DATA5_VNN -- unused */
	PAD_NC(GPIO_42, DN_20K), /* GP_INTD_DSI_TE1 -- unused */
	PAD_NC(GPIO_43, DN_20K), /* GP_INTD_DSI_TE2 -- debug header NC */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_44, UP_20K, DEEP, NF1, TxDRxE, ENPU), /* USB_OC0_B */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_45, UP_20K, DEEP, NF1, TxDRxE, ENPU), /* USB_OC1_B */
	PAD_NC(GPIO_46, DN_20K), /* DSI_I2C_SDA -- unused */
	PAD_NC(GPIO_47, DN_20K), /* DSI_I2C_SCL -- unused */

	/* PMC stays active in suspend so disable standby for these pins */
	PAD_CFG_NF_IOSTANDBY_IGNORE(GPIO_48, NONE, DEEP, NF1), /* PMC_I2C_SDA */
	PAD_CFG_NF_IOSTANDBY_IGNORE(GPIO_49, NONE, DEEP, NF1), /* PMC_I2C_SCL */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_50, NONE, DEEP, NF1, HIZCRx1, DISPUPD), /* PCH_I2C_PEN_SDA */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_51, NONE, DEEP, NF1, HIZCRx1, DISPUPD), /* PCH_I2C_PEN_SCL */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_52, NONE, DEEP, NF1, HIZCRx1, DISPUPD), /* LPSS_I2C1_SDA */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_53, NONE, DEEP, NF1, HIZCRx1, DISPUPD), /* LPSS_I2C1_SCL */
	PAD_NC(GPIO_54, UP_20K), /* LPSS_I2C2_SDA -- unused */
	PAD_NC(GPIO_55, UP_20K), /* LPSS_I2C2_SCL -- unused */
	PAD_NC(GPIO_56, UP_20K), /* LPSS_I2C3_SDA -- debug header NC */
	PAD_NC(GPIO_57, UP_20K), /* LPSS_I2C2_SCL -- debug header NC */
	PAD_NC(GPIO_58, UP_20K), /* LPSS_I2C4_SDA -- unused */
	PAD_NC(GPIO_59, UP_20K), /* LPSS_I2C4_SCL -- unused */
	PAD_NC(GPIO_60, UP_20K), /* LPSS_UART0_RXD -- debug header NC */
	PAD_NC(GPIO_61, UP_20K), /* LPSS_UART0_TXD -- debug header NC */
	PAD_NC(GPIO_62, UP_20K), /* UART0-RTS_B -- unused */
	PAD_CFG_GPI_APIC_IOS(GPIO_63, NONE, DEEP, LEVEL, INVERT, TxDRxE, DISPUPD), /* H1_PCH_INT_ODL */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_64, UP_20K, DEEP, NF1, HIZCRx1, DISPUPD), /* LPSS_UART2_RXD */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_65, UP_20K, DEEP, NF1, TxLASTRxE, DISPUPD), /* LPSS_UART2_TXD */
	PAD_NC(GPIO_66, UP_20K), /* UART2-RTS_B -- unused */
	PAD_CFG_GPO_IOSSTATE_IOSTERM(GPIO_67, 0, DEEP, NONE, TxLASTRxE, DISPUPD), /* UART2-CTS_B -- EN_PP3300_DX_LTE_SOC */
	PAD_CFG_GPI(GPIO_68, NONE, DEEP), /* DRAM_ID0 */
	PAD_CFG_GPI(GPIO_69, NONE, DEEP), /* DRAM_ID1 */
	PAD_CFG_GPI(GPIO_70, NONE, DEEP), /* DRAM_ID2 */
	PAD_CFG_GPI(GPIO_71, NONE, DEEP), /* DRAM_ID3 */
	PAD_NC(GPIO_72, DN_20K), /* PMC_SPI_TXD -- unused */
	PAD_NC(GPIO_73, DN_20K), /* PMC_SPI_CLK -- unused */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_74, UP_20K, DEEP, NF1, TxDRxE, ENPU), /* THERMTRIP_B */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_75, NONE, DEEP, NF1, TxDRxE, DISPUPD), /* PROCHOT_B */
	PAD_NC(GPIO_211, UP_20K), /* EMMC_RST_B -- unused */
	PAD_CFG_GPI_APIC_IOS(GPIO_212, NONE, DEEP, LEVEL, INVERT, HIZCRx1, DISPUPD), /* Touch Panel Int */
	PAD_CFG_GPO_IOSSTATE_IOSTERM(GPIO_213, 0, DEEP, NONE, Tx0RxDCRx0, DISPUPD), /* EN_PP3300_TOUCHSCREEN */
	PAD_CFG_GPI_APIC_IOS(GPIO_214, NONE, DEEP, LEVEL, INVERT, HIZCRx1, DISPUPD), /* P_SENSOR_INT_L */

	/* NORTH COMMUNITY GPIOS */

	/* svid - unused */
	PAD_NC(GPIO_76, UP_20K),/* SVID Alert - unused */
	PAD_NC(GPIO_77, UP_20K),/* SVID Data - unused */
	PAD_NC(GPIO_78, UP_20K),/* SVID Clk - unused */

	/* LPSS */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_79, NONE, DEEP, NF1, HIZCRx0, DISPUPD), /* H1_SLAVE_SPI_CLK_R */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_80, NONE, DEEP, NF1, HIZCRx1, DISPUPD), /* H1_SLAVE_SPI_CS_L_R */
	PAD_NC(GPIO_81, DN_20K), /* GPIO_81_DEBUG -- debug header NC */
	PAD_CFG_NF(GPIO_82, NONE, DEEP, NF1), /* H1_SLAVE_SPI_MISO */
	PAD_CFG_NF(GPIO_83, NONE, DEEP, NF1), /* H1_SLAVE_SPI_MOSI_R */
	PAD_NC(GPIO_84, DN_20K), /* LPSS_SPI_2_CLK - unused */
	PAD_NC(GPIO_85, DN_20K), /* LPSS_SPI_2_FS0 - unused */
	PAD_NC(GPIO_86, DN_20K), /* LPSS_SPI_2_FS1 - unused */
	PAD_NC(GPIO_87, DN_20K), /* LPSS_SPI_2_FS2 - unused */
	PAD_NC(GPIO_88, DN_20K), /* LPSS_SPI_2_RXD - unused */
	PAD_NC(GPIO_89, DN_20K), /* LPSS_SPI_2_TXD - unused */

	/* Fast SPI */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_90, NATIVE, DEEP, NF1, HIZCRx1, SAME),/* FST_SPI_CS0_B */
	PAD_CFG_GPO_IOSSTATE_IOSTERM(GPIO_91, 0, DEEP, NONE, Tx0RxDCRx0, DISPUPD),/* FST_SPI_CS1_B -- SPK_PA_EN_R */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_92, NATIVE, DEEP, NF1, HIZCRx1, SAME),/* FST_SPI_MOSI_IO0 */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_93, NATIVE, DEEP, NF1, HIZCRx1, SAME),/* FST_SPI_MISO_IO1 */
	PAD_NC(GPIO_94, NATIVE),/* FST_SPI_IO2 - unused */
	PAD_NC(GPIO_95, NATIVE),/* FST_SPI_IO3 - unused */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_96, NATIVE, DEEP, NF1, HIZCRx0, SAME),/* FST_SPI_CLK */

	/* PMU Signals */
	PAD_CFG_NF_IOSTANDBY_IGNORE(GPIO_98, NONE, DEEP, NF1),/* PMU_PLTRST_B */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_99, NONE, DEEP, NF1, TxDRxE, DISPUPD),/* PMU_PWRBTN_B */
	PAD_CFG_NF_IOSTANDBY_IGNORE(GPIO_100, NONE, DEEP, NF1),/* PMU_SLP_S0_B */
	PAD_CFG_NF_IOSTANDBY_IGNORE(GPIO_101, NONE, DEEP, NF1),/* PMU_SLP_S3_B */
	PAD_CFG_NF_IOSTANDBY_IGNORE(GPIO_102, NONE, DEEP, NF1),/* PMU_SLP_S4_B */
	PAD_CFG_NF_IOSTANDBY_IGNORE(GPIO_103, NONE, DEEP, NF1),/* SUSPWRDNACK */
	PAD_NC(GPIO_104, UP_20K),/* EMMC_DNX_PWR_EN_B - unused */
	PAD_CFG_GPO_IOSSTATE_IOSTERM(GPIO_105, 1, DEEP, NONE, Tx1RxDCRx0, DISPUPD),/* GPIO_105 -- TOUCHSCREEN_RST */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_106, NONE, DEEP, NF1, HIZCRx1, DISPUPD),/* PMU_BATLOW_B */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_107, NONE, DEEP, NF1, TxDRxE, DISPUPD),/* PMU_RESETBUTTON_B */
	PAD_NC(GPIO_108, NONE),/* PMU_SUSCLK -- unused */
	PAD_CFG_GPO_IOSSTATE_IOSTERM(GPIO_109, 1, DEEP, NONE, Tx1RxDCRx1, DISPUPD),/* SUS_STAT_B -- BT_DISABLE_L */

	/* I2C5 - Audio */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_110, NONE, DEEP, NF1, HIZCRx1, DISPUPD),/* LPSS_I2C5_SDA */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_111, NONE, DEEP, NF1, HIZCRx1, DISPUPD),/* LPSS_I2C5_SCL */

	/* I2C6 - Trackpad */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_112, NONE, DEEP, NF1, HIZCRx1, DISPUPD),/* LPSS_I2C6_SDA */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_113, NONE, DEEP, NF1, HIZCRx1, DISPUPD),/* LPSS_I2C6_SCL */

	/* I2C7 - Touchscreen */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_114, NONE, DEEP, NF1, HIZCRx1, DISPUPD),/* LPSS_I2C7_SDA */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_115, NONE, DEEP, NF1, HIZCRx1, DISPUPD),/* LPSS_I2C7_SCL */

	/* PCIE_WAKE[0:3]_B */
	PAD_CFG_GPO_IOSSTATE_IOSTERM(GPIO_116, 1, DEEP, NONE, Tx1RxDCRx1, DISPUPD), /* PCIE_WAKE0_B -- WIFI_DISABLE_L */
	PAD_CFG_GPI_SCI_LOW(GPIO_117, NONE, DEEP, EDGE_SINGLE),/* PCIE_WAKE1_B -- LTE_WAKE_L */
	PAD_NC(GPIO_118, UP_20K),/* PCIE_WAKE2_B -- unused */
	PAD_CFG_GPI_SCI_LOW(GPIO_119, NONE, DEEP, EDGE_SINGLE),/* PCIE_WAKE3_B */

	/*
	 * PCIE_CLKREQ[0:3]_B. For unused pins, follow the termination
	 * guideline for unused PCIE ports as described in PDG i.e. keep
	 * the pins in native mode and deploy the internal pull up.
	 */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_120, UP_20K, DEEP, NF1, HIZCRx1, ENPU),/* PCIE_CLKREQ0_B -- unused*/
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_121, UP_20K, DEEP, NF1, HIZCRx1, ENPU),/* PCIE_CLKREQ1_B -- unused */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_122, UP_20K, DEEP, NF1, HIZCRx1, ENPU),/* PCIE_CLKREQ2_B -- unused */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_123, NONE, DEEP, NF1, TxDRxE, DISPUPD), /* PCIE_CLKREQ3_B */

	/* DDI[0:1] SDA and SCL -- unused */
	PAD_NC(GPIO_124, UP_20K),/* HV_DDI0_DDC_SDA -- unused */
	PAD_NC(GPIO_125, UP_20K),/* HV_DDI0_DDC_SCL -- unused */
	PAD_NC(GPIO_126, UP_20K),/* HV_DDI1_DDC_SDA -- unused */
	PAD_NC(GPIO_127, UP_20K),/* HV_DDI1_DDC_SCL -- unused */

	/* Panel 0 control */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_128, NONE, DEEP, NF1, Tx0RxDCRx0, DISPUPD),/* PANEL0_VDDEN*/
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_129, NONE, DEEP, NF1, Tx0RxDCRx0, DISPUPD),/* PANEL0_BKLTEN */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_130, NONE, DEEP, NF1, Tx0RxDCRx0, DISPUPD),/* PANEL0_BKLTCTL */

	/* Hot plug detect. */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_131, NONE, DEEP, NF1, HIZCRx1, DISPUPD),/* HV_DDI0_HPD */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_132, NONE, DEEP, NF1, HIZCRx1, DISPUPD),/* HV_DDI1_HPD */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_133, NONE, DEEP, NF1, HIZCRx1, DISPUPD),/* HV_EDP_HPD */

	/* EC_AP_INT_ODL */
	PAD_CFG_GPI_APIC_LOW(GPIO_134, NONE, DEEP),

	PAD_CFG_GPI_IRQ_WAKE(GPIO_135, NONE, DEEP, LEVEL, INVERT),/* GPIO_135 -- TRACKPAD_INT1_1V8_ODL */
	PAD_CFG_GPI_APIC_IOS(GPIO_136, NONE, DEEP, LEVEL, INVERT, TxDRxE, DISPUPD),/* GPIO_136 -- PMIC_PCH_INT_ODL */
	PAD_CFG_GPI_APIC_IOS(GPIO_137, NONE, DEEP, LEVEL, INVERT, HIZCRx1, DISPUPD),/* GPIO_137 -- HP_INT_ODL */
	PAD_CFG_GPI_APIC_IOS(GPIO_138, NONE, DEEP, LEVEL, INVERT, HIZCRx1, DISPUPD),/* GPIO_138 -- PEN_PDCT_ODL */
	PAD_CFG_GPI_APIC_IOS(GPIO_139, NONE, DEEP, LEVEL, INVERT, HIZCRx1, DISPUPD),/* GPIO_139 -- PEN_INT_ODL */
	PAD_CFG_GPO_IOSSTATE_IOSTERM(GPIO_140, 1, DEEP, NONE, Tx1RxDCRx0, DISPUPD),/* GPIO_140 -- PEN_RESET */
	// Also we may be able to use eSPI WAKE# Virtual Wire instead
	PAD_CFG_GPI_SCI_IOS(GPIO_141, NONE, DEEP, EDGE_SINGLE, INVERT, IGNORE, DISPUPD),/* GPIO_141 -- EC_PCH_WAKE_ODL */
	PAD_NC(GPIO_142, UP_20K),/* GPIO_142 -- TRACKPAD_INT2_1V8_ODL(unused) */
	PAD_CFG_GPO_IOSSTATE_IOSTERM(GPIO_143, 1, DEEP, UP_20K, HIZCRx1, ENPU),/* GPIO_143 -- LTE_SAR_ODL */

	/* GPIO_144 -- PEN_EJECT(wake) */
	PAD_CFG_GPI_SCI_HIGH_DEBEN(GPIO_144, UP_20K, DEEP, EDGE_SINGLE,
							DEBOUNCE_256_RTC),
	/* GPIO_145 -- PEN_EJECT(notifications) */
	PAD_CFG_GPI_GPIO_DRIVER(GPIO_145, UP_20K, DEEP),
	PAD_NC(GPIO_146, UP_20K),/* GPIO_146 -- unused */

	/*
	 * GPIO_154 - LPC_CLKRUN# has a native function for LPC but not for
	 * eSPI. Nonetheless if we use eSPI, it should be configured as a GPIO
	 * and kept unconnected to allow S0ix entry.
	 */

	/* AUDIO COMMUNITY GPIOS*/
	PAD_NC(GPIO_156, DN_20K), /* AVS_I2S0_MCLK -- unused */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_157, NONE, DEEP, NF1, HIZCRx0, DISPUPD), /* AVS_I2S0_BCLK */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_158, NONE, DEEP, NF1, HIZCRx0, DISPUPD), /* AVS_I2S0_WS_SYNC */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_159, NONE, DEEP, NF1, HIZCRx0, DISPUPD), /* AVS_I2S0_SDI */
	PAD_NC(GPIO_160, DN_20K), /* AVS_I2S0_SDO -- unused */
	PAD_CFG_GPO_IOSSTATE_IOSTERM(GPIO_161, 1, DEEP, UP_20K, Tx1RxDCRx0, DISPUPD), /* AVS_I2S1_MCLK -- LTE_OFF_ODL */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_162, NONE, DEEP, NF1, HIZCRx0, DISPUPD), /* AVS_I2S1_BCLK */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_163, NONE, DEEP, NF1, HIZCRx0, DISPUPD), /* AVS_I2S1_WS_SYNC */
	PAD_CFG_GPO(GPIO_164, 0, DEEP), /* WLAN_PE_RST */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_165, NONE, DEEP, NF1, HIZCRx0, DISPUPD), /* AVS_I2S1_SDO */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_166, NONE, DEEP, NF2, HIZCRx0, DISPUPD), /* AVS_I2S2_BCLK */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_167, NONE, DEEP, NF2, HIZCRx0, DISPUPD), /* AVS_I2S2_WS_SYNC */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_168, NONE, DEEP, NF2, HIZCRx0, DISPUPD), /* AVS_I2S2_SDI */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_169, NONE, DEEP, NF2, HIZCRx0, DISPUPD), /* AVS_I2S2_SD0 */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_170, DN_20K, DEEP, NF2, HIZCRx0, DISPUPD), /* AVS_I2S1_MCLK */

	/* Disable standby for GPIO_171 and GPIO_173 to support Wake on Voice */
	PAD_CFG_NF_IOSTANDBY_IGNORE(GPIO_171, DN_20K, DEEP, NF1), /* AVS_M_CLK_A1 -- DMIC_CLK1 */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_172, DN_20K, DEEP, NF1, HIZCRx0, DISPUPD), /* AVS_M_CLK_B1 */
	PAD_CFG_NF_IOSTANDBY_IGNORE(GPIO_173, DN_20K, DEEP, NF1), /* AVS_M_DATA_1 -- DMIC_DATA */
	PAD_NC(GPIO_174, DN_20K), /* AVS_M_CLK_AB2 -- unused */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_175, NONE, DEEP, NF1, HIZCRx0, DISPUPD), /* AVS_M_DATA_2 */

	/* SCC COMMUNITY GPIOS */
	PAD_NC(GPIO_176, UP_20K), /* SMB_ALERTB -- unused */
	PAD_NC(GPIO_177, UP_20K), /* SMB_CLK -- unused */
	PAD_CFG_GPO_IOSSTATE_IOSTERM(GPIO_178, 0, DEEP, NONE, Tx0RxDCRx0, DISPUPD), /* EN_PP3300_WLAN_L */

	PAD_NC(GPIO_179, NONE), /* SDCARD_CLK -- unused */
	PAD_NC(GPIO_180, NONE), /* SDCARD_CMD -- unused */
	PAD_NC(GPIO_181, UP_20K), /* SDCARD_D0 -- unused */
	PAD_NC(GPIO_182, UP_20K), /* SDCARD_D1 -- unused */
	PAD_NC(GPIO_183, UP_20K), /* SDCARD_D2 -- unused */
	PAD_NC(GPIO_184, UP_20K), /* SDCARD_D3 -- unused */
	PAD_NC(GPIO_185, UP_20K), /* SDCARD_CMD -- unused */
	PAD_NC(GPIO_186, UP_20K), /* SDCARD_CD_N -- unused */
	PAD_NC(GPIO_187, NONE), /* SDCARD_LVL_WP -- unused */
	PAD_NC(GPIO_188, UP_20K), /* SDCARD_PWR_DWN_N -- unused */
	PAD_CFG_GPI(GPIO_189, NONE, DEEP), /* EC_IN_RW */
	PAD_CFG_GPI(GPIO_190, NONE, DEEP), /* PCH_WP_OD */

	/*
	 * Disable standby state for these CNVI pins to allow wake on
	 * WiFI & Bluetooth.
	 */
	PAD_CFG_NF_IOSTANDBY_IGNORE(GPIO_191, NONE, DEEP, NF1), /* CNV_BRI_DT */
	PAD_CFG_NF_IOSTANDBY_IGNORE(GPIO_192, UP_20K, DEEP, NF1), /* CNV_BRI_RSP */
	PAD_CFG_NF_IOSTANDBY_IGNORE(GPIO_193, NONE, DEEP, NF1), /* CNV_RGI_DT */
	PAD_CFG_NF_IOSTANDBY_IGNORE(GPIO_194, UP_20K, DEEP, NF1), /* CNV_RGI_RSP */
	PAD_CFG_NF_IOSTANDBY_IGNORE(GPIO_195, NONE, DEEP, NF1), /* CNV_RF_RESET_B */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_198, DN_20K, DEEP, NF1, HIZCRx0, ENPD), /* EMMC0_CLK */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_200, UP_20K, DEEP, NF1, HIZCRx1, ENPU), /* EMMC0_D0 */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_201, UP_20K, DEEP, NF1, HIZCRx1, ENPU), /* EMMC0_D1 */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_202, UP_20K, DEEP, NF1, HIZCRx1, ENPU), /* EMMC0_D2 */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_203, UP_20K, DEEP, NF1, HIZCRx1, ENPU), /* EMMC0_D3 */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_204, UP_20K, DEEP, NF1, HIZCRx1, ENPU), /* EMMC0_D4 */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_205, UP_20K, DEEP, NF1, HIZCRx1, ENPU), /* EMMC0_D5 */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_206, UP_20K, DEEP, NF1, HIZCRx1, ENPU), /* EMMC0_D6 */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_207, UP_20K, DEEP, NF1, HIZCRx1, ENPU), /* EMMC0_D7 */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_208, UP_20K, DEEP, NF1, HIZCRx1, ENPU), /* EMMC0_CMD */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_209, NONE, DEEP, NF1, HIZCRx0, DISPUPD), /* EMMC0_STROBE */
	PAD_NC(GPIO_210, DN_20K),
};

const struct pad_config *__weak variant_base_gpio_table(size_t *num)
{
	*num = ARRAY_SIZE(gpio_table);
	return gpio_table;
}

const struct pad_config *__weak variant_override_gpio_table(size_t *num)
{
	*num = 0;
	return NULL;
}

const struct pad_config *__weak variant_early_override_gpio_table(size_t *num)
{
	*num = 0;
	return NULL;
}

/* GPIOs needed prior to ramstage. */
static const struct pad_config early_gpio_table[] = {
	PAD_CFG_GPI(GPIO_190, NONE, DEEP), /* PCH_WP_OD */
	/* GSPI0_INT */
	PAD_CFG_GPI_APIC_IOS(GPIO_63, NONE, DEEP, LEVEL, INVERT, TxDRxE,
		DISPUPD), /* H1_PCH_INT_ODL */
	/* GSPI0_CLK */
	PAD_CFG_NF(GPIO_79, NONE, DEEP, NF1), /* H1_SLAVE_SPI_CLK_R */
	/* GSPI0_CS# */
	PAD_CFG_NF(GPIO_80, NONE, DEEP, NF1), /* H1_SLAVE_SPI_CS_L_R */
	/* GSPI0_MISO */
	PAD_CFG_NF(GPIO_82, NONE, DEEP, NF1), /* H1_SLAVE_SPI_MISO */
	/* GSPI0_MOSI */
	PAD_CFG_NF(GPIO_83, NONE, DEEP, NF1), /* H1_SLAVE_SPI_MOSI_R */

	/* Enable power to wifi early in bootblock and de-assert PERST#. */
	PAD_CFG_GPO(GPIO_178, 0, DEEP), /* EN_PP3300_WLAN_L */
	PAD_CFG_GPO(GPIO_164, 0, DEEP), /* WLAN_PE_RST */

	/*
	 * ESPI_IO1 acts as ALERT# (which is open-drain) and requies a weak
	 * pull-up for proper operation. Since there is no external pull present
	 * on this platform, configure an internal weak pull-up.
	 */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_151, UP_20K, DEEP, NF2, HIZCRx1,
				    ENPU), /* ESPI_IO1 */

	/* GPIO_67 and GPIO_117 are in early_gpio_table and gpio_table. For variants
	 * having LTE SKUs, these two GPIOs would be overridden to output high first
	 * in the bootblock then be set to default state in gpio_table for non-LTE
	 * SKUs and keep to output high for LTE SKUs in ramstage.
	 */
	PAD_CFG_GPO_IOSSTATE_IOSTERM(GPIO_67, 0, DEEP, NONE, TxLASTRxE, DISPUPD), /* UART2-CTS_B -- EN_PP3300_DX_LTE_SOC */
	PAD_CFG_GPI_SCI_LOW(GPIO_117, NONE, DEEP, EDGE_SINGLE),/* PCIE_WAKE1_B -- LTE_WAKE_L */
	/* GPIO_161 is in early_gpio_table and gpio_table because LTE SKU needs
	 * to override this pin to output low then high respectively in two
	 * stages.
	 */
	PAD_CFG_GPO_IOSSTATE_IOSTERM(GPIO_161, 1, DEEP, UP_20K, Tx1RxDCRx0, DISPUPD), /* AVS_I2S1_MCLK -- LTE_OFF_ODL */
};

const struct pad_config *__weak
variant_early_gpio_table(size_t *num)
{
	*num = ARRAY_SIZE(early_gpio_table);
	return early_gpio_table;
}

/* GPIO settings before entering sleep. */
static const struct pad_config sleep_gpio_table[] = {
};

/* GPIO settings before entering slp_s5. */
static const struct pad_config sleep_s5_gpio_table[] = {
	/* BT_DISABLE_L */
	PAD_CFG_GPO_IOSSTATE_IOSTERM(GPIO_109, 0, DEEP, NONE, Tx0RxDCRx1, SAME),
};

const struct pad_config *__weak
variant_sleep_gpio_table(size_t *num, int slp_typ)
{
	if (slp_typ == ACPI_S5) {
		*num = ARRAY_SIZE(sleep_s5_gpio_table);
		return sleep_s5_gpio_table;
	}

	*num = ARRAY_SIZE(sleep_gpio_table);
	return sleep_gpio_table;
}

static const struct cros_gpio cros_gpios[] = {
	CROS_GPIO_REC_AL(CROS_GPIO_VIRTUAL, CROS_GPIO_DEVICE_NAME),
	CROS_GPIO_WP_AH(PAD_SCC(GPIO_PCH_WP), GPIO_COMM_SCC_NAME),
};

const struct cros_gpio *__weak variant_cros_gpios(size_t *num)
{
	*num = ARRAY_SIZE(cros_gpios);
	return cros_gpios;
}
