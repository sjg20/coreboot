/* SPDX-License-Identifier: GPL-2.0-only */

#include <baseboard/gpio.h>
#include <baseboard/variants.h>
#include <commonlib/helpers.h>
#include <vendorcode/google/chromeos/chromeos.h>

/*
 * Pad configuration in ramstage. The order largely follows the 'GPIO Muxing'
 * table found in EDS vol 1, but some pins aren't grouped functionally in
 * the table so those were moved for more logical grouping.
 */
static const struct pad_config gpio_table[] = {
/* NORTHWEST COMMUNITY GPIOS */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_0, DN_20K, DEEP, NF1, IGNORE, ENPD), /* TCK */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_1, DN_20K, DEEP, NF1, IGNORE, ENPD), /* TRST_B */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_2, UP_20K, DEEP, NF1, IGNORE, ENPU), /* TMS */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_3, UP_20K, DEEP, NF1, IGNORE, ENPU), /* TDI */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_4, UP_20K, DEEP, NF1, IGNORE, ENPU), /* TDO */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_5, UP_20K, DEEP, NF1, IGNORE, ENPU), /* JTAGX */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_6, UP_20K, DEEP, NF1, IGNORE, ENPU), /* CX_PREQ_B */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_7, UP_20K, DEEP, NF1, IGNORE, ENPU), /* CX_PRDY_B */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_8, DN_20K, DEEP, NF5, HIZCRx0, DISPUPD), /* TRACE_0_CLK_VNN */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_9, DN_20K, DEEP, NF5, HIZCRx0, DISPUPD), /* TRACE_0_DATA0_VNN */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_10, DN_20K, DEEP, NF5, HIZCRx0, DISPUPD), /* TRACE_0_DATA1_VNN */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_11, DN_20K, DEEP, NF5, HIZCRx0, DISPUPD), /* TRACE_0_DATA2_VNN */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_12, DN_20K, DEEP, NF5, HIZCRx0, DISPUPD), /* TRACE_0_DATA3_VNN */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_13, DN_20K, DEEP, NF5, HIZCRx0, DISPUPD), /* TRACE_0_DATA4_VNN */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_14, DN_20K, DEEP, NF5, HIZCRx0, DISPUPD), /* TRACE_0_DATA5_VNN */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_15, DN_20K, DEEP, NF5, HIZCRx0, DISPUPD), /* TRACE_0_DATA6_VNN */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_16, DN_20K, DEEP, NF5, HIZCRx0, DISPUPD), /* TRACE_0_DATA7_VNN */
	PAD_CFG_GPO_IOSSTATE_IOSTERM(GPIO_17, 1, DEEP, UP_20K, TxDRxE, SAME),/*Ec-to-SOC CS Wake */
	PAD_CFG_GPI_APIC_IOS(GPIO_18, UP_20K, DEEP, LEVEL, NONE, IGNORE, SAME),/* Touch Pad Interrupt */
	PAD_CFG_GPI_APIC_IOS(GPIO_19, UP_20K, DEEP, EDGE_SINGLE, NONE, TxDRxE, SAME),/*PMIC Interrupt*/
	PAD_CFG_GPI_APIC_IOS(GPIO_20, UP_20K, DEEP, LEVEL, INVERT, IGNORE, SAME),/* Audio Codec Interrupt*/
	PAD_CFG_NF(GPIO_21, UP_20K, DEEP, NF2), /* CNV_MFUART2_RXD */
	PAD_CFG_NF_IOSSTATE(GPIO_22, UP_20K, DEEP, NF2, TxDRxE), /* CNV_MFUART2_TXD */
	PAD_CFG_NF(GPIO_23, UP_20K, DEEP, NF2), /* CNV_GNSS_PABLANKIt */
	PAD_CFG_GPO_GPIO_DRIVER(GPIO_24, 1, DEEP, DN_20K),
	PAD_CFG_GPO_IOSSTATE_IOSTERM(GPIO_25, 1, DEEP, UP_20K, TxLASTRxE, SAME),/*WWAN /RF_KILL_GPS*/
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_26, UP_20K, DEEP, NF2, HIZCRx1, DISPUPD),/* NFC Interrupt */
	PAD_CFG_GPO_IOSSTATE_IOSTERM(GPIO_27, 1, DEEP, NONE, IGNORE, DISPUPD),/* RF_KILL_WiFi/WiFi_Disable */
	PAD_CFG_GPO_IOSSTATE_IOSTERM(GPIO_28, 1, DEEP, UP_20K, TxLASTRxE, DISPUPD),/* RF_KILL_BT/BT_Disable */
	PAD_CFG_GPO_IOSSTATE_IOSTERM(GPIO_29, 1, DEEP, UP_20K, HIZCRx0, DISPUPD),/* Codec Power Down: Output/ISH_GPIO_3*/
	PAD_CFG_NF_IOSTANDBY_IGNORE(GPIO_30, DN_20K, DEEP, NF1), /* ISH_GPIO_4 */
	PAD_CFG_NF_IOSTANDBY_IGNORE(GPIO_31, DN_20K, DEEP, NF1), /* ISH_GPIO_5 */
	PAD_CFG_NF_IOSTANDBY_IGNORE(GPIO_32, DN_20K, DEEP, NF1), /* ISH_GPIO_6 */
	PAD_CFG_NF_IOSTANDBY_IGNORE(GPIO_33, DN_20K, DEEP, NF1), /* ISH_GPIO_7 */
	PAD_CFG_NF_IOSTANDBY_IGNORE(GPIO_34, DN_20K, DEEP, NF1), /* ISH_GPIO_8/SUSCLK2 (1.8V) */
	PAD_CFG_NF_IOSTANDBY_IGNORE(GPIO_35, UP_20K, DEEP, NF6), /* BSSB_CLK */
	PAD_CFG_NF_IOSTANDBY_IGNORE(GPIO_36, UP_20K, DEEP, NF6), /* BSSB_DI */
	PAD_CFG_GPI_SCI_IOS(GPIO_37, UP_20K, DEEP, EDGE_SINGLE, INVERT, IGNORE, SAME),/*Runtime SCI */
	PAD_CFG_GPI_SCI_IOS(GPIO_38, UP_20K, DEEP, EDGE_SINGLE, INVERT, IGNORE, SAME),/*Wake SCI */
	PAD_CFG_GPI_APIC_IOS(GPIO_39, DN_20K, DEEP, LEVEL, NONE, IGNORE, SAME),/* Finger Print Sensor Interrupt  (DRDY) */
	PAD_CFG_NF_IOSTANDBY_IGNORE(GPIO_40, UP_20K, DEEP, NF6),/*IERR (USB Camera Power Enable)*/
	PAD_CFG_GPI_SMI_IOS(GPIO_41, UP_20K, DEEP, EDGE_SINGLE, NONE, IGNORE, SAME),/*SOC_EXTSMI_N */
	PAD_CFG_NF(GPIO_42, DN_20K, DEEP, NF1), /* GP_INTD_DSI_TE1 */
	PAD_CFG_NF(GPIO_43, DN_20K, DEEP, NF1), /* GP_INTD_DSI_TE2 */
	PAD_CFG_NF(GPIO_44, UP_20K, DEEP, NF1), /* USB_OC0_B */
	PAD_CFG_NF(GPIO_45, UP_20K, DEEP, NF1), /* USB_OC1_B */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_46, UP_20K, DEEP, NF1, HIZCRx1, SAME), /* DSI_I2C_SDA */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_47, UP_20K, DEEP, NF1, HIZCRx1, ENPU), /* DSI_I2C_SCL */
	PAD_CFG_NF_IOSTANDBY_IGNORE(GPIO_48, UP_1K, DEEP, NF1), /* PMC_I2C_SDA */
	PAD_CFG_NF_IOSTANDBY_IGNORE(GPIO_49, UP_1K, DEEP, NF1), /* PMC_I2C_SCL */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_50, UP_2K, DEEP, NF1, HIZCRx1, ENPU), /* LPSS_I2C0_SDA  - Audio Codec*/
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_51, UP_2K, DEEP, NF1, HIZCRx1, ENPU), /* LPSS_I2C0_SCL - Audio Codec */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_52, UP_20K, DEEP, NF1, HIZCRx1, ENPU), /* LPSS_I2C1_SDA - NFC */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_53, UP_20K, DEEP, NF1, HIZCRx1, ENPU), /* LPSS_I2C1_SCL - NFC */
	PAD_CFG_GPIO_DRIVER_HI_Z(GPIO_54, UP_20K, DEEP, HIZCRx1, ENPU),/*LPSS_I2C2_SDA*/
	PAD_CFG_GPIO_DRIVER_HI_Z(GPIO_55, UP_20K, DEEP, HIZCRx1, ENPU),/*LPSS_I2C2_SCL*/
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_56, UP_20K, DEEP, NF1, HIZCRx1, ENPU),/* I2C3-SDA -  DBG (PSS, SINAI2, MIPI) */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_57, UP_20K, DEEP, NF1, HIZCRx1, ENPU),/*I2C3-SCL -  DBG (PSS, SINAI2, MIPI) */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_58, UP_20K, DEEP, NF1, HIZCRx1, ENPU),/*I2C4-SDA - Touch Pad*/
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_59, UP_20K, DEEP, NF1, HIZCRx1, ENPU),/*I2C4-SCL - Touch Pad*/
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_60, UP_20K, DEEP, NF1, HIZCRx1, DISPUPD),/* UART0-RXD - M.2dGNSS */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_61, UP_20K, DEEP, NF1, HIZCRx1, DISPUPD),/* UART0-TXD - M.2dGNSS */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_62, UP_20K, DEEP, NF1, HIZCRx1, DISPUPD),/* UART0-RTS_B - M.2 dGNSS */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_63, UP_20K, DEEP, NF1, HIZCRx1, DISPUPD),/* UART0-CTS_B - M.2 dGNSS */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_64, UP_20K, DEEP, NF1, HIZCRx1, DISPUPD),/*LPSS_UART2_RXD*/
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_65, UP_20K, DEEP, NF1, TxLASTRxE, DISPUPD),/*LPSS_UART2_TXD*/
	PAD_CFG_GPO_IOSSTATE_IOSTERM(GPIO_66, 1, DEEP, UP_20K, TxDRxE, DISPUPD),/*RF_KILL_WWAN */
#if CONFIG(TPM_ON_FAST_SPI)
	PAD_CFG_GPI_INT(GPIO_67, UP_20K, DEEP, LEVEL),/*SPI TPM Interrupt */
#endif
	PAD_CFG_NF(GPIO_68, UP_20K, DEEP, NF1),/*PMC_SPI_FS0*/
	PAD_CFG_GPI_APIC(GPIO_69, DN_20K, DEEP, EDGE_SINGLE, NONE),/*SIM Detect*/
	PAD_CFG_NF(GPIO_70, DN_20K, DEEP, NF1),/*PMC_SPI_FS2*/
	PAD_CFG_NF(GPIO_71, DN_20K, DEEP, NF1),/*PMC_SPI_RXD*/
	PAD_CFG_NF(GPIO_72, DN_20K, DEEP, NF1),/*PMC_SPI_TXD*/
	PAD_CFG_NF(GPIO_73, DN_20K, DEEP, NF1),/*PMC_SPI_CLK*/
	PAD_CFG_NF(GPIO_74, DN_20K, DEEP, NF1),/*THERMTRIP_B*/
	PAD_CFG_NF_IOSSTATE(GPIO_75, UP_20K, DEEP, NF1, HIZCRx1),/*PROCHOT_B*/
	PAD_CFG_NF_IOSSTATE(GPIO_211, UP_20K, DEEP, NF1, HIZCRx1),/*EMMC_RST_B*/
	PAD_CFG_GPI_GPIO_DRIVER(GPIO_212, UP_20K, DEEP),/*Touch Panel Int*/
	PAD_CFG_GPO_IOSSTATE_IOSTERM(GPIO_213, 1, DEEP, NONE, HIZCRx0, SAME),/*DNX LED - CSE owned*/
	PAD_CFG_GPO_IOSSTATE_IOSTERM(GPIO_214, 1, DEEP, NONE, HIZCRx0, SAME),/*LAN Isolate*/
/* NORTH COMMUNITY GPIOS */
	PAD_CFG_NF_IOSTANDBY_IGNORE(GPIO_76, UP_20K, DEEP, NF1),/*SVID Alert*/
	PAD_CFG_NF_IOSTANDBY_IGNORE(GPIO_77, UP_20K, DEEP, NF1),/* SVID Data */
	PAD_CFG_NF_IOSTANDBY_IGNORE(GPIO_78, UP_20K, DEEP, NF1),/* SVID Clk */
	PAD_CFG_NF_IOSTANDBY_IGNORE(GPIO_79, NATIVE, DEEP, NF1),/* Finger Print Sensor */
	PAD_CFG_NF_IOSTANDBY_IGNORE(GPIO_80, NATIVE, DEEP, NF1),/* Finger Print Sensor CS */
	PAD_CFG_NF_IOSTANDBY_IGNORE(GPIO_81, NONE, DEEP, NF3),/* FST_SPI_CS2_B - TPM */
	PAD_CFG_NF_IOSTANDBY_IGNORE(GPIO_82, NATIVE, DEEP, NF1),/* Finger Print Sensor */
	PAD_CFG_NF_IOSTANDBY_IGNORE(GPIO_83, NATIVE, DEEP, NF1),/* Finger Print Sensor */
	PAD_CFG_NF_IOSSTATE(GPIO_84, NONE, DEEP, NF3, HIZCRx1),/* SPI iTouch*/
	PAD_CFG_NF_IOSSTATE(GPIO_85, DN_20K, DEEP, NF3, HIZCRx1),/*Function 3: SPI iTouch CS*/
	PAD_CFG_NF_IOSSTATE(GPIO_86, DN_20K, DEEP, NF3, HIZCRx1),/*Function 3: SPI iTouch*/
	PAD_CFG_NF_IOSSTATE(GPIO_87, DN_20K, DEEP, NF3, HIZCRx1),/*Function 3: SPI iTouch*/
	PAD_CFG_NF_IOSSTATE(GPIO_88, DN_20K, DEEP, NF3, HIZCRx1),/*Function 3: SPI iTouch*/
	PAD_CFG_NF_IOSSTATE(GPIO_89, DN_20K, DEEP, NF3, HIZCRx1),/*Function 3: SPI iTouch*/
	PAD_CFG_NF_IOSTANDBY_IGNORE(GPIO_90, NATIVE, DEEP, NF1),/*Function 1: FST SPI Boot Flash CS*/
	PAD_CFG_GPIO_HI_Z(GPIO_91, NATIVE, DEEP, IGNORE, SAME),/*FST_SPI_CS1_B*/
	PAD_CFG_NF_IOSTANDBY_IGNORE(GPIO_92, DN_20K, DEEP, NF1),/*FST_SPI_MOSI_IO0*/
	PAD_CFG_NF_IOSTANDBY_IGNORE(GPIO_93, NATIVE, DEEP, NF1),/*FST_SPI_MISO_IO1*/
	PAD_CFG_NF_IOSTANDBY_IGNORE(GPIO_94, NATIVE, DEEP, NF1),/*FST_SPI_IO2*/
	PAD_CFG_NF_IOSTANDBY_IGNORE(GPIO_95, NATIVE, DEEP, NF1),/*FST_SPI_IO3*/
	PAD_CFG_NF_IOSTANDBY_IGNORE(GPIO_96, NATIVE, DEEP, NF1),/*FST_SPI_CLK*/
	PAD_CFG_NF(GPIO_97, NATIVE, DEEP, NF1),/*FST_SPI_CLK_FB*/
	PAD_CFG_NF_IOSTANDBY_IGNORE(GPIO_98, NONE, DEEP, NF1),/*PMU_PLTRST_B*/
	PAD_CFG_NF_IOSTANDBY_IGNORE(GPIO_99, UP_20K, DEEP, NF1),/*PMU_PWRBTN_B*/
	PAD_CFG_NF_IOSTANDBY_IGNORE(GPIO_100, NONE, DEEP, NF1),/*PMU_SLP_S0_B*/
	PAD_CFG_NF_IOSTANDBY_IGNORE(GPIO_101, NONE, DEEP, NF1),/*PMU_SLP_S3_B*/
	PAD_CFG_NF_IOSTANDBY_IGNORE(GPIO_102, NONE, DEEP, NF1),/*PMU_SLP_S4_B*/
	PAD_CFG_NF_IOSTANDBY_IGNORE(GPIO_103, NONE, DEEP, NF1),/*SUSPWRDNACK*/
	PAD_CFG_NF_IOSTANDBY_IGNORE(GPIO_104, UP_20K, DEEP, NF1),/*EMMC_DNX_PWR_EN_B*/
	PAD_CFG_GPO_IOSSTATE_IOSTERM(GPIO_105, 0, DEEP, NONE, Tx0RxDCRx0, SAME),/*x4 Slot-2 Reset*/
	PAD_CFG_NF_IOSTANDBY_IGNORE(GPIO_106, UP_20K, DEEP, NF1),/*PMU_BATLOW_B*/
	PAD_CFG_NF_IOSTANDBY_IGNORE(GPIO_107, UP_20K, DEEP, NF1),/*PMU_RESETBUTTON_B*/
	PAD_CFG_NF_IOSTANDBY_IGNORE(GPIO_108, NONE, DEEP, NF1),/*PMU_SUSCLK*/
	PAD_CFG_NF_IOSTANDBY_IGNORE(GPIO_109, NONE, DEEP, NF1),/*SUS_STAT_B*/
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_110, UP_20K, DEEP, NF2, HIZCRx1, ENPU),/*LPSS_I2C5_SDA*/
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_111, UP_20K, DEEP, NF2, HIZCRx1, ENPU),/*LPSS_I2C5_SCL*/
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_112, UP_20K, DEEP, NF2, HIZCRx1, ENPU),/*LPSS_I2C6_SDA*/
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_113, UP_20K, DEEP, NF2, HIZCRx1, ENPU),/*LPSS_I2C6_SCL*/
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_114, UP_20K, DEEP, NF1, HIZCRx1, ENPU),/*LPSS_I2C7_SDA*/
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_115, UP_20K, DEEP, NF1, HIZCRx1, ENPU),/*LPSS_I2C7_SCL*/
	PAD_CFG_NF_IOSTANDBY_IGNORE(GPIO_116, UP_20K, DEEP, NF1),/*PCIE_WAKE0_B*/
	PAD_CFG_NF_IOSTANDBY_IGNORE(GPIO_117, UP_20K, DEEP, NF1),/*PCIE_WAKE1_B*/
	PAD_CFG_NF_IOSTANDBY_IGNORE(GPIO_118, UP_20K, DEEP, NF1),/*PCIE_WAKE2_B*/
	PAD_CFG_NF_IOSTANDBY_IGNORE(GPIO_119, UP_20K, DEEP, NF1),/*PCIE_WAKE3_B*/
	PAD_CFG_GPI(GPIO_120, UP_20K, DEEP),     /* unused */
	PAD_CFG_GPI(GPIO_121, UP_20K, DEEP),     /* unused */
	PAD_CFG_GPI(GPIO_122, UP_20K, DEEP),     /* unused */
	PAD_CFG_NF_IOSSTATE(GPIO_123, UP_20K, DEEP, NF1, HIZCRx1),/*PCIE_CLKREQ3_B*/
	PAD_CFG_NF_IOSSTATE(GPIO_124, UP_20K, DEEP, NF1, HIZCRx0),/*HV_DDI0_DDC_SDA*/
	PAD_CFG_NF_IOSSTATE(GPIO_125, UP_20K, DEEP, NF1, HIZCRx0),/*HV_DDI0_DDC_SCL*/
	PAD_CFG_NF_IOSSTATE(GPIO_126, UP_20K, DEEP, NF1, HIZCRx0),/*HV_DDI1_DDC_SDA*/
	PAD_CFG_NF_IOSSTATE(GPIO_127, UP_20K, DEEP, NF1, HIZCRx0),/*HV_DDI1_DDC_SCL*/
	PAD_CFG_NF_IOSSTATE(GPIO_128, NONE, DEEP, NF1, Tx0RxDCRx0),/*PANEL0_VDDEN*/
	PAD_CFG_NF_IOSSTATE(GPIO_129, NONE, DEEP, NF1, Tx0RxDCRx0),/*PANEL0_BKLTEN*/
	PAD_CFG_NF_IOSSTATE(GPIO_130, NONE, DEEP, NF1, Tx0RxDCRx0),/*PANEL0_BKLTCTL*/
	PAD_CFG_NF_IOSSTATE(GPIO_131, UP_20K, DEEP, NF1, TxDRxE),/*HV_DDI0_HPD*/
	PAD_CFG_NF_IOSSTATE(GPIO_132, UP_20K, DEEP, NF1, TxDRxE),/*HV_DDI1_HPD*/
	PAD_CFG_NF_IOSSTATE(GPIO_133, UP_20K, DEEP, NF1, TxDRxE),/*HV_EDP_HPD*/
	PAD_CFG_GPO_IOSSTATE_IOSTERM(GPIO_134, 1, DEEP, UP_20K, IGNORE, SAME),/*Slot-1 Power Enable*/
	PAD_CFG_GPO_IOSSTATE_IOSTERM(GPIO_135, 1, DEEP, UP_20K, IGNORE, SAME),/*Slot-2 Power Enable*/
	PAD_CFG_GPO_IOSSTATE_IOSTERM(GPIO_136, 1, DEEP, NONE, Tx0RxDCRx0, SAME),/*DGPU Power Select*/
	PAD_CFG_GPO_IOSSTATE_IOSTERM(GPIO_137, 1, DEEP, UP_20K, IGNORE, SAME),/*slot-1 Reset*/
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_138, UP_20K, DEEP, NF2, HIZCRx1, DISPUPD),/*SATA_GP0 (DC RTD3 need)*/
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_139, UP_20K, DEEP, NF2, TxLASTRxE, DISPUPD),/*SATA_GP1 (ZPODD_DEV_DET)*/
	PAD_CFG_NF(GPIO_140, UP_20K, DEEP, NF5),/*SATA_DEVSLP0 (DC DEV SLP)*/
	PAD_CFG_NF_IOSSTATE(GPIO_141, UP_20K, DEEP, NF5, HIZCRx1),/*SATA_DEVSLP1 (ZPODD DEV ATN)*/
	PAD_CFG_NF_IOSSTATE(GPIO_142, UP_20K, DEEP, NF5, HIZCRx1),/*SATA_LED*/
	PAD_CFG_GPI_APIC_IOS(GPIO_143, NONE, DEEP, LEVEL, NONE, HIZCRx1, SAME),/*DGPU Power Ok*/
	PAD_CFG_NF_IOSSTATE(GPIO_144, UP_20K, DEEP, NF5, HIZCRx1),/*PANEL1_VDDEN*/
	PAD_CFG_NF_IOSSTATE(GPIO_145, UP_20K, DEEP, NF5, HIZCRx1),/*PANEL1_BKLTEN*/
	PAD_CFG_NF_IOSSTATE(GPIO_146, UP_20K, DEEP, NF5, HIZCRx1),/*PANEL1_BKLTCTL*/
	PAD_CFG_GPO_IOSSTATE_IOSTERM(GPIO_157, 1, DEEP, UP_20K, IGNORE, SAME),/*WWAN_Reset/dGPS Reset*/
	PAD_CFG_GPO_IOSSTATE_IOSTERM(GPIO_158, 0, DEEP, DN_20K, IGNORE, SAME),/*NFC_DFU*/
	PAD_CFG_GPO_IOSSTATE_IOSTERM(GPIO_159, 1, DEEP, NONE, Tx0RxDCRx0, SAME),/*NFC reset*/
	PAD_CFG_GPO_IOSSTATE_IOSTERM(GPIO_160, 0, DEEP, UP_20K, IGNORE, SAME),/*SD_MODE for spk*/
	PAD_CFG_GPO_IOSSTATE_IOSTERM(GPIO_161, 1, DEEP, UP_20K, IGNORE, SAME),/*Touch panel reset*/
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_162, DN_20K, DEEP, NF1, HIZCRx1, SAME),/*AVS_I2S1_BCLK*/
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_163, DN_20K, DEEP, NF1, HIZCRx1, SAME),/*AVS_I2S1_WS_SYNC*/
	PAD_CFG_GPO_IOSSTATE_IOSTERM(GPIO_164, 1, DEEP, NONE, Tx0RxDCRx0, SAME),/*Touch Panel Power Enable*/
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_165, DN_20K, DEEP, NF1, HIZCRx1, SAME),/*AVS_I2S1_SDO*/

/* AUDIO COMMUNITY GPIOS*/

	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_166, DN_20K, DEEP, NF2, HIZCRx1, SAME),/*AVS_I2S2_BCLK*/
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_167, DN_20K, DEEP, NF2, HIZCRx1, SAME),/*AVS_I2S2_WS_SYNC*/
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_168, DN_20K, DEEP, NF2, HIZCRx1, SAME),/* AVS_I2S2_SDI*/
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_169, DN_20K, DEEP, NF2, HIZCRx1, SAME),/*AVS_I2S2_SD0*/
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_170, DN_20K, DEEP, NF2, HIZCRx1, SAME),/*AVS_I2S1_MCLK*/
	PAD_CFG_NF_IOSTANDBY_IGNORE(GPIO_171, DN_20K, DEEP, NF1),/*AVS_M_CLK_A1*/
	PAD_CFG_NF_IOSSTATE(GPIO_172, DN_20K, DEEP, NF1, HIZCRx1),/*AVS_M_CLK_B1*/
	PAD_CFG_NF_IOSTANDBY_IGNORE(GPIO_173, DN_20K, DEEP, NF1),/*AVS_M_DATA_1*/
	PAD_CFG_NF_IOSSTATE(GPIO_174, DN_20K, DEEP, NF1, HIZCRx1),/*AVS_M_CLK_AB2*/
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_175, DN_20K, DEEP, NF1, HIZCRx1, ENPD),/*AVS_M_DATA_2*/

/* SCC COMMUNITY GPIOS */
	PAD_CFG_NF_IOSTANDBY_IGNORE(GPIO_176, UP_20K, DEEP, NF1),/*SMB_ALERTB*/
	PAD_CFG_NF_IOSTANDBY_IGNORE(GPIO_177, UP_20K, DEEP, NF1),/*SMB_CLK*/
	PAD_CFG_NF_IOSTANDBY_IGNORE(GPIO_178, UP_20K, DEEP, NF1),/*SMB_DATA*/
	PAD_CFG_NF_IOSTANDBY_IGNORE(GPIO_187, DN_20K, DEEP, NF1),/*SDCARD_LVL_WP*/
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_179, DN_20K, DEEP, NF1, HIZCRx0, DISPUPD),/*SDCARD_CLK*/
	PAD_CFG_NF(GPIO_180, DN_20K, DEEP, NF1),/*SDCARD_CLK_FB*/
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_181, UP_20K, DEEP, NF1, HIZCRx1, DISPUPD),/*SDCARD_D0*/
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_182, UP_20K, DEEP, NF1, HIZCRx1, DISPUPD),/*SDCARD_D1*/
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_183, UP_20K, DEEP, NF1, HIZCRx1, DISPUPD),/*SDCARD_D2*/
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_184, UP_20K, DEEP, NF1, HIZCRx1, DISPUPD),/*SDCARD_D3*/
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_185, UP_20K, DEEP, NF1, HIZCRx1, DISPUPD),/*SDCARD_CMD*/
	PAD_CFG_NF(GPIO_186, NONE, DEEP, NF1),/*SDCARD_CD_B*/
	PAD_CFG_GPO_IOSSTATE_IOSTERM(GPIO_188, 0, DEEP, NONE, TxDRxE, SAME),/*SD Card*/
	PAD_CFG_GPO_IOSSTATE_IOSTERM(GPIO_210, 1, DEEP, UP_20K, HIZCRx0, DISPUPD),
	PAD_CFG_NF_IOSSTATE(GPIO_189, DN_20K, DEEP, NF1, HIZCRx0),/*OSC_CLK_OUT_0*/
	PAD_CFG_NF_IOSSTATE(GPIO_190, DN_20K, DEEP, NF1, HIZCRx0),/*OSC_CLK_OUT_1*/
	PAD_CFG_NF_IOSTANDBY_IGNORE(GPIO_191, NONE, DEEP, NF1),/*CNV_BRI_DT*/
	PAD_CFG_NF_IOSTANDBY_IGNORE(GPIO_192, UP_20K, DEEP, NF1),/*CNV_BRI_RSP*/
	PAD_CFG_NF_IOSTANDBY_IGNORE(GPIO_193, NONE, DEEP, NF1),/*CNV_RGI_DT*/
	PAD_CFG_NF_IOSTANDBY_IGNORE(GPIO_194, UP_20K, DEEP, NF1),/*CNV_RGI_RSP*/
	PAD_CFG_NF_IOSTANDBY_IGNORE(GPIO_195, NONE, DEEP, NF1),/*CNV_RF_RESET_B*/
	PAD_CFG_NF_IOSTANDBY_IGNORE(GPIO_196, NONE, DEEP, NF1),/*XTAL_CLKREQ*/
	PAD_CFG_NF(GPIO_197, DN_20K, DEEP, NF1),/*SDIO_CLK_FB*/
	PAD_CFG_NF_IOSSTATE(GPIO_198, DN_20K, DEEP, NF1, HIZCRx0),/*EMMC0_CLK*/
	PAD_CFG_NF(GPIO_199, DN_20K, DEEP, NF1),/*EMMC0_CLK_FB*/
	PAD_CFG_NF_IOSSTATE(GPIO_200, UP_20K, DEEP, NF1, HIZCRx1),/*EMMC0_D0*/
	PAD_CFG_NF_IOSSTATE(GPIO_201, UP_20K, DEEP, NF1, HIZCRx1),/*EMMC0_D1*/
	PAD_CFG_NF_IOSSTATE(GPIO_202, UP_20K, DEEP, NF1, HIZCRx1),/*EMMC0_D2*/
	PAD_CFG_NF_IOSSTATE(GPIO_203, UP_20K, DEEP, NF1, HIZCRx1),/*EMMC0_D3*/
	PAD_CFG_NF_IOSSTATE(GPIO_204, UP_20K, DEEP, NF1, HIZCRx1),/*EMMC0_D4*/
	PAD_CFG_NF_IOSSTATE(GPIO_205, UP_20K, DEEP, NF1, HIZCRx1),/*EMMC0_D5*/
	PAD_CFG_NF_IOSSTATE(GPIO_206, UP_20K, DEEP, NF1, HIZCRx1),/*EMMC0_D6*/
	PAD_CFG_NF_IOSSTATE(GPIO_207, UP_20K, DEEP, NF1, HIZCRx1),/*EMMC0_D7*/
	PAD_CFG_NF_IOSSTATE(GPIO_208, UP_20K, DEEP, NF1, HIZCRx1),/*EMMC0_CMD*/
	PAD_CFG_NF_IOSSTATE(GPIO_209, DN_20K, DEEP, NF1, HIZCRx0),/*EMMC0_STROBE*/
};

const struct pad_config * __weak variant_gpio_table(size_t *num)
{
	*num = ARRAY_SIZE(gpio_table);
	return gpio_table;
}

/* GPIOs needed prior to ramstage. */
static const struct pad_config early_gpio_table[] = {
	PAD_CFG_NF_IOSTANDBY_IGNORE(GPIO_177, UP_20K, DEEP, NF1), /* SMB_CLK */
	PAD_CFG_NF_IOSTANDBY_IGNORE(GPIO_178, UP_20K, DEEP, NF1), /* SMB_DATA */
	PAD_NC(GPIO_154, NONE), /* LPC_CLKRUNB -- NC for eSPI */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_64, UP_20K, DEEP, NF1, HIZCRx1, DISPUPD),/* LPSS_UART2_RXD */
	PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_65, UP_20K, DEEP, NF1, TxLASTRxE, DISPUPD),/* LPSS_UART2_TXD */
};

const struct pad_config * __weak
variant_early_gpio_table(size_t *num)
{
	*num = ARRAY_SIZE(early_gpio_table);
	return early_gpio_table;
}

/* GPIO settings before entering sleep. */
static const struct pad_config sleep_gpio_table[] = {
};

const struct pad_config * __weak
variant_sleep_gpio_table(size_t *num)
{
	*num = ARRAY_SIZE(sleep_gpio_table);
	return sleep_gpio_table;
}

static const struct cros_gpio cros_gpios[] = {
};

const struct cros_gpio * __weak variant_cros_gpios(size_t *num)
{
	*num = ARRAY_SIZE(cros_gpios);
	return cros_gpios;
}
