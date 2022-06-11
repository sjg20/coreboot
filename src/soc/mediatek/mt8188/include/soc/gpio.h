/* SPDX-License-Identifier: GPL-2.0-only */

/*
 * This file is created based on MT8188 Functional Specification
 * Chapter number: 5.2
 */

#ifndef SOC_MEDIATEK_MT8188_GPIO_H
#define SOC_MEDIATEK_MT8188_GPIO_H

#include <soc/addressmap.h>
#include <soc/gpio_common.h>
#include <types.h>

#define GPIO_NUM 177

enum {
	MAX_GPIO_REG_BITS = 32,
	MAX_GPIO_MODE_PER_REG = 8,
	GPIO_MODE_BITS = 4,
};
enum gpio_drv {
	GPIO_DRV_2_MA = 0,
	GPIO_DRV_4_MA = 1,
	GPIO_DRV_6_MA = 2,
	GPIO_DRV_8_MA = 3,
	GPIO_DRV_10_MA = 4,
	GPIO_DRV_12_MA = 5,
	GPIO_DRV_14_MA = 6,
	GPIO_DRV_16_MA = 7,
};

#define PIN(id, name, flag, bit, base, offset, \
		func1, func2, func3, func4, func5, func6, func7) \
	PAD_##name##_ID = id, \
	PAD_##name##_FLAG = flag, \
	PAD_##name##_BIT = bit, \
	PAD_##name##_BASE = base, \
	PAD_##name##_OFFSET = offset, \
	PAD_##name##_FUNC_##func1 = 1, \
	PAD_##name##_FUNC_##func2 = 2, \
	PAD_##name##_FUNC_##func3 = 3, \
	PAD_##name##_FUNC_##func4 = 4, \
	PAD_##name##_FUNC_##func5 = 5, \
	PAD_##name##_FUNC_##func6 = 6, \
	PAD_##name##_FUNC_##func7 = 7

#define GPIO(name) ((gpio_t){ \
		.id = PAD_##name##_ID, \
		.flag = PAD_##name##_FLAG, \
		.bit = PAD_##name##_BIT, \
		.base = PAD_##name##_BASE, \
		.offset = PAD_##name##_OFFSET \
	})

enum {

	PIN(0, GPIO00, 0, 6, 0x31, 0xe0,
	    TP_GPIO0_AO, SPIM5_CSB, UTXD1, DMIC3_CLK,
	    I2SIN_MCK, I2SO2_MCK, DBG_MON_A0),
	PIN(1, GPIO01, 0, 7, 0x31, 0xe0,
	    TP_GPIO1_AO, SPIM5_CLK, URXD1, DMIC3_DAT,
	    I2SIN_BCK, I2SO2_BCK, DBG_MON_A1),
	PIN(2, GPIO02, 0, 8, 0x31, 0xe0,
	    TP_GPIO2_AO, SPIM5_MOSI, URTS1, DMIC3_DAT_R,
	    I2SIN_WS, I2SO2_WS, DBG_MON_A2),
	PIN(3, GPIO03, 0, 9, 0x31, 0xe0,
	    TP_GPIO3_AO, SPIM5_MISO, UCTS1, DMIC4_CLK,
	    I2SIN_D0, I2SO2_D0, DBG_MON_A3),
	PIN(4, GPIO04, 0, 10, 0x31, 0xe0,
	    TP_GPIO4_AO, SPDIF_IN2, I2SO1_MCK, DMIC4_DAT,
	    I2SIN_D1, I2SO2_D1, DBG_MON_A4),
	PIN(5, GPIO05, 0, 11, 0x31, 0xe0,
	    TP_GPIO5_AO, SPDIF_IN1, I2SO1_BCK, DMIC4_DAT_R,
	    I2SIN_D2, I2SO2_D2, DBG_MON_A5),
	PIN(6, GPIO06, 0, 12, 0x31, 0xe0,
	    TP_GPIO6_AO, SPDIF_IN0, I2SO1_WS, DMIC1_CLK,
	    I2SIN_D3, I2SO2_D3, MD32_0_GPIO0),
	PIN(7, GPIO07, 0, 13, 0x31, 0xe0,
	    TP_GPIO7_AO, SPIM3_CSB, TDMIN_MCK, DMIC1_DAT,
	    CMVREF0, CLKM0, DBG_MON_A6),
	PIN(8, GPIO08, 0, 14, 0x31, 0xe0,
	    TP_GPIO0_AO, SPIM3_CLK, TDMIN_BCK, DMIC1_DAT_R,
	    CMVREF1, CLKM1, DBG_MON_A7),
	PIN(9, GPIO09, 0, 15, 0x31, 0xe0,
	    TP_GPIO1_AO, SPIM3_MOSI, TDMIN_LRCK, DMIC2_CLK,
	    CMFLASH0, PWM_0, DBG_MON_A8),
	PIN(10, GPIO10, 0, 16, 0x31, 0xe0,
	    TP_GPIO2_AO, SPIM3_MISO, TDMIN_DI, DMIC2_DAT,
	    CMFLASH1, PWM_1, DBG_MON_A9),
	PIN(11, GPIO11, 0, 17, 0x31, 0xe0,
	    TP_GPIO3_AO, SPDIF_OUT, I2SO1_D0, DMIC2_DAT_R,
	    DVFSRC_EXT_REQ, CMVREF6, DBG_MON_A10),
	PIN(12, GPIO12, 0, 12, 0x32, 0xd0,
	    TP_GPIO4_AO, SPIM4_CSB, JTMS_SEL3, APU_JTAG_TMS,
	    VPU_UDI_TMS, IPU_JTAG_TMS, HDMITX20_HTPLG),
	PIN(13, GPIO13, 0, 13, 0x32, 0xd0,
	    TP_GPIO5_AO, SPIM4_CLK, JTCK_SEL3, APU_JTAG_TCK,
	    VPU_UDI_TCK, IPU_JTAG_TCK, HDMITX20_CEC),
	PIN(14, GPIO14, 0, 14, 0x32, 0xd0,
	    TP_GPIO6_AO, SPIM4_MOSI, JTDI_SEL3, APU_JTAG_TDI,
	    VPU_UDI_TDI, IPU_JTAG_TDI, HDMITX20_SCL),
	PIN(15, GPIO15, 0, 15, 0x32, 0xd0,
	    TP_GPIO7_AO, SPIM4_MISO, JTDO_SEL3, APU_JTAG_TDO,
	    VPU_UDI_TDO, IPU_JTAG_TDO, HDMITX20_SDA),
	PIN(16, GPIO16, 0, 1, 0x23, 0x70,
	    TP_GPIO0_AO, UTXD3, JTRSTn_SEL3, APU_JTAG_TRST,
	    VPU_UDI_NTRST, IPU_JTAG_TRST, HDMITX20_PWR5V),
	PIN(17, GPIO17, 0, 2, 0x23, 0x70,
	    TP_GPIO1_AO, URXD3, CMFLASH2, EDP_TX_HPD,
	    DVFSRC_EXT_REQ, CMVREF7, MD32_0_GPIO1),
	PIN(18, CMMPDN0, 0, 3, 0x24, 0x80,
	    TP_GPIO2_AO, CMFLASH0, CMVREF4, TDMIN_MCK,
	    UTXD1, TP_UTXD1_AO, DBG_MON_A11),
	PIN(19, CMMRST0, 0, 5, 0x24, 0x80,
	    TP_GPIO3_AO, CMFLASH1, CMVREF5, TDMIN_BCK,
	    URXD1, TP_URXD1_AO, DBG_MON_A12),
	PIN(20, CMMPDN1, 0, 4, 0x24, 0x80,
	    TP_GPIO4_AO, CMFLASH2, CLKM2, TDMIN_LRCK,
	    URTS1, TP_URTS1_AO, DBG_MON_A13),
	PIN(21, CMMRST1, 0, 6, 0x24, 0x80,
	    TP_GPIO5_AO, CMFLASH3, CLKM3, TDMIN_DI,
	    UCTS1, TP_UCTS1_AO, DBG_MON_A14),
	PIN(22, CMMCLK0, 0, 0, 0x24, 0x80,
	    CMMCLK0, RES2, RES3, RES4,
	    TP_GPIO6_AO, RES6, DBG_MON_A15),
	PIN(23, CMMCLK1, 0, 1, 0x24, 0x80,
	    CMMCLK1, RES2, PWM_2, PCIE_PHY_I2C_SCL,
	    TP_GPIO7_AO, DP_TX_HPD, DBG_MON_A16),
	PIN(24, CMMCLK2, 0, 2, 0x24, 0x80,
	    CMMCLK2, RES2, PWM_3, PCIE_PHY_I2C_SDA,
	    DVFSRC_EXT_REQ, EDP_TX_HPD, MD32_0_GPIO2),
	PIN(25, DSI0_LCM_RST, 0, 3, 0x31, 0xe0,
	    LCM_RST, LCM1_RST, DP_TX_HPD, RES4,
	    RES5, RES6, RES7),
	PIN(26, DSI0_DSI_TE, 0, 2, 0x31, 0xe0,
	    DSI_TE, DSI1_TE, EDP_TX_HPD, RES4,
	    RES5, RES6, RES7),
	PIN(27, DSI1_LCM_RST, 0, 5, 0x31, 0xe0,
	    LCM1_RST, LCM_RST, DP_TX_HPD, CMVREF2,
	    mbistwriteen_trigger, PWM_2, DBG_MON_A17),
	PIN(28, DSI1_DSI_TE, 0, 4, 0x31, 0xe0,
	    DSI1_TE, DSI_TE, EDP_TX_HPD, CMVREF3,
	    mbistreaden_trigger, PWM_3, DBG_MON_A18),
	PIN(29, DISP_PWM0, 0, 0, 0x31, 0xe0,
	    DISP_PWM0, DISP_PWM1, RES3, RES4,
	    RES5, RES6, RES7),
	PIN(30, DISP_PWM1, 0, 1, 0x31, 0xe0,
	    DISP_PWM1, DISP_PWM0, CMFLASH3, PWM_1,
	    RES5, RES6, DBG_MON_A19),
	PIN(31, UART0_TXD, 0, 11, 0x31, 0xf0,
	    UTXD0, TP_UTXD1_AO, ADSP_UTXD0, TP_UTXD2_AO,
	    MD32_0_TXD, MD32_1_TXD, SSPM_UTXD_AO),
	PIN(32, UART0_RXD, 0, 10, 0x31, 0xf0,
	    URXD0, TP_URXD1_AO, ADSP_URXD0, TP_URXD2_AO,
	    MD32_0_RXD, MD32_1_RXD, SSPM_URXD_AO),
	PIN(33, UART1_TXD, 0, 13, 0x31, 0xf0,
	    UTXD1, URTS2, ADSP_UTXD0, TP_UTXD1_AO,
	    mbistwriteen_trigger, MD32_0_TXD, SSPM_UTXD_AO),
	PIN(34, UART1_RXD, 0, 12, 0x31, 0xf0,
	    URXD1, UCTS2, ADSP_URXD0, TP_URXD1_AO,
	    mbistreaden_trigger, MD32_0_RXD, SSPM_URXD_AO),
	PIN(35, UART2_TXD, 0, 15, 0x31, 0xf0,
	    UTXD2, URTS1, ADSP_UTXD0, TP_URTS1_AO,
	    TP_UTXD2_AO, MD32_1_TXD, DBG_MON_A20),
	PIN(36, UART2_RXD, 0, 14, 0x31, 0xf0,
	    URXD2, UCTS1, ADSP_URXD0, TP_UCTS1_AO,
	    TP_URXD2_AO, MD32_1_RXD, DBG_MON_A21),
	PIN(37, JTMS, 0, 21, 0x31, 0xe0,
	    JTMS_SEL1, UDI_TMS, SPM_JTAG_TMS, ADSP_JTAG0_TMS,
	    SCP_JTAG0_TMS, CCU0_JTAG_TMS, MCUPM_JTAG_TMS),
	PIN(38, JTCK, 0, 18, 0x31, 0xe0,
	    JTCK_SEL1, UDI_TCK, SPM_JTAG_TCK, ADSP_JTAG0_TCK,
	    SCP_JTAG0_TCK, CCU0_JTAG_TCK, MCUPM_JTAG_TCK),
	PIN(39, JTDI, 0, 19, 0x31, 0xe0,
	    JTDI_SEL1, UDI_TDI, SPM_JTAG_TDI, ADSP_JTAG0_TDI,
	    SCP_JTAG0_TDI, CCU0_JTAG_TDI, MCUPM_JTAG_TDI),
	PIN(40, JTDO, 0, 20, 0x31, 0xe0,
	    JTDO_SEL1, UDI_TDO, SPM_JTAG_TDO, ADSP_JTAG0_TDO,
	    SCP_JTAG0_TDO, CCU0_JTAG_TDO, MCUPM_JTAG_TDO),
	PIN(41, JTRST, 0, 22, 0x31, 0xe0,
	    JTRSTn_SEL1, UDI_NTRST, SPM_JTAG_TRSTN, ADSP_JTAG0_TRSTN,
	    SCP_JTAG0_TRSTN, CCU0_JTAG_TRST, MCUPM_JTAG_TRSTN),
	PIN(42, KPCOL0, 1, 12, 0x32, 0xc0,
	    KPCOL0, RES2, RES3, RES4,
	    RES5, RES6, RES7),
	PIN(43, KPCOL1, 1, 13, 0x32, 0xc0,
	    KPCOL1, DP_TX_HPD, CMFLASH2, DVFSRC_EXT_REQ,
	    RES5, RES6, mbistwriteen_trigger),
	PIN(44, KPROW0, 1, 14, 0x32, 0xc0,
	    KPROW0, RES2, RES3, RES4,
	    RES5, RES6, RES7),
	PIN(45, KPROW1, 1, 15, 0x32, 0xc0,
	    KPROW1, EDP_TX_HPD, CMFLASH3, I2SIN_MCK,
	    RES5, RES6, mbistreaden_trigger),
	PIN(46, DPTX_HPD, 0, 0, 0x23, 0x70,
	    DP_TX_HPD, PWM_0, VBUSVALID_2P, RES4,
	    RES5, RES6, DBG_MON_A22),
	PIN(47, PCIE_WAKE_N, 0, 25, 0x31, 0xe0,
	    WAKEN, RES2, RES3, RES4,
	    RES5, GDU_TROOPS_DET0, RES7),
	PIN(48, PCIE_PERESET_N, 0, 24, 0x31, 0xe0,
	    PERSTN, RES2, RES3, RES4,
	    RES5, GDU_TROOPS_DET1, RES7),
	PIN(49, PCIE_CLKREQ_N, 0, 23, 0x31, 0xe0,
	    CLKREQN, RES2, RES3, RES4,
	    RES5, GDU_TROOPS_DET2, RES7),
	PIN(50, HDMITX_PWR5V, 0, 5, 0x23, 0x70,
	    HDMITX20_PWR5V, RES2, IDDIG_1P, SCP_JTAG1_TMS,
	    SSPM_JTAG_TMS, MD32_0_JTAG_TMS, MD32_1_JTAG_TMS),
	PIN(51, HDMITX_HTPLG, 0, 4, 0x23, 0x70,
	    HDMITX20_HTPLG, EDP_TX_HPD, USB_DRVVBUS_1P, SCP_JTAG1_TCK,
	    SSPM_JTAG_TCK, MD32_0_JTAG_TCK, MD32_1_JTAG_TCK),
	PIN(52, HDMITX_CEC, 0, 3, 0x23, 0x70,
	    HDMITX20_CEC, RES2, VBUSVALID_1P, SCP_JTAG1_TDI,
	    SSPM_JTAG_TDI, MD32_0_JTAG_TDI, MD32_1_JTAG_TDI),
	PIN(53, HDMITX_SCL, 0, 6, 0x23, 0x70,
	    HDMITX20_SCL, RES2, IDDIG_2P, SCP_JTAG1_TDO,
	    SSPM_JTAG_TDO, MD32_0_JTAG_TDO, MD32_1_JTAG_TDO),
	PIN(54, HDMITX_SDA, 0, 7, 0x23, 0x70,
	    HDMITX20_SDA, RES2, USB_DRVVBUS_2P, SCP_JTAG1_TRSTN,
	    SSPM_JTAG_TRSTN, MD32_0_JTAG_TRST, MD32_1_JTAG_TRST),
	PIN(55, SCL0, 0, 26, 0x31, 0xe0,
	    SCL0, SCP_SCL0, SCP_SCL1, PCIE_PHY_I2C_SCL,
	    RES5, RES6, RES7),
	PIN(56, SDA0, 0, 29, 0x31, 0xe0,
	    SDA0, SCP_SDA0, SCP_SDA1, PCIE_PHY_I2C_SDA,
	    RES5, RES6, RES7),
	PIN(57, SCL1, 0, 6, 0x32, 0xe0,
	    SCL1, RES2, RES3, RES4,
	    RES5, RES6, RES7),
	PIN(58, SDA1, 0, 9, 0x32, 0xe0,
	    SDA1, RES2, RES3, RES4,
	    RES5, RES6, RES7),
	PIN(59, SCL2, 0, 27, 0x31, 0xe0,
	    SCL2, SCP_SCL0, SCP_SCL1, RES4,
	    RES5, RES6, RES7),
	PIN(60, SDA2, 0, 30, 0x31, 0xe0,
	    SDA2, SCP_SDA0, SCP_SDA1, RES4,
	    RES5, RES6, RES7),
	PIN(61, SCL3, 0, 28, 0x31, 0xe0,
	    SCL3, SCP_SCL0, SCP_SCL1, PCIE_PHY_I2C_SCL,
	    RES5, RES6, RES7),
	PIN(62, SDA3, 0, 31, 0x31, 0xe0,
	    SDA3, SCP_SDA0, SCP_SDA1, PCIE_PHY_I2C_SDA,
	    RES5, RES6, RES7),
	PIN(63, SCL4, 0, 7, 0x32, 0xe0,
	    SCL4, RES2, RES3, RES4,
	    RES5, RES6, RES7),
	PIN(64, SDA4, 0, 10, 0x32, 0xe0,
	    SDA4, RES2, RES3, RES4,
	    RES5, RES6, RES7),
	PIN(65, SCL5, 0, 7, 0x24, 0x80,
	    SCL5, SCP_SCL0, SCP_SCL1, RES4,
	    RES5, RES6, RES7),
	PIN(66, SDA5, 0, 9, 0x24, 0x80,
	    SDA5, SCP_SDA0, SCP_SDA1, RES4,
	    RES5, RES6, RES7),
	PIN(67, SCL6, 0, 8, 0x24, 0x80,
	    SCL6, SCP_SCL0, SCP_SCL1, PCIE_PHY_I2C_SCL,
	    RES5, RES6, RES7),
	PIN(68, SDA6, 0, 10, 0x24, 0x80,
	    SDA6, SCP_SDA0, SCP_SDA1, PCIE_PHY_I2C_SDA,
	    RES5, RES6, RES7),
	PIN(69, SPIM0_CSB, 0, 1, 0x31, 0xf0,
	    SPIM0_CSB, SCP_SPI0_CS, DMIC3_CLK, MD32_1_GPIO0,
	    CMVREF0, GDU_SUM_TROOP0_0, DBG_MON_A23),
	PIN(70, SPIM0_CLK, 0, 0, 0x31, 0xf0,
	    SPIM0_CLK, SCP_SPI0_CK, DMIC3_DAT, MD32_1_GPIO1,
	    CMVREF1, GDU_SUM_TROOP0_1, DBG_MON_A24),
	PIN(71, SPIM0_MOSI, 0, 5, 0x31, 0xf0,
	    SPIM0_MOSI, SCP_SPI0_MO, DMIC3_DAT_R, MD32_1_GPIO2,
	    CMVREF2, GDU_SUM_TROOP0_2, DBG_MON_A25),
	PIN(72, SPIM0_MISO, 0, 4, 0x31, 0xf0,
	    SPIM0_MISO, SCP_SPI0_MI, DMIC4_CLK, RES4,
	    CMVREF3, GDU_SUM_TROOP1_0, DBG_MON_A26),
	PIN(73, SPIM0_MIO2, 0, 2, 0x31, 0xf0,
	    SPIM0_MIO2, UTXD3, DMIC4_DAT, CLKM0,
	    CMVREF4, GDU_SUM_TROOP1_1, DBG_MON_A27),
	PIN(74, SPIM0_MIO3, 0, 3, 0x31, 0xf0,
	    SPIM0_MIO3, URXD3, DMIC4_DAT_R, CLKM1,
	    CMVREF5, GDU_SUM_TROOP1_2, DBG_MON_A28),
	PIN(75, SPIM1_CSB, 0, 7, 0x31, 0xf0,
	    SPIM1_CSB, SCP_SPI1_A_CS, TDMIN_MCK, SCP_SCL0,
	    CMVREF6, GDU_SUM_TROOP2_0, DBG_MON_A29),
	PIN(76, SPIM1_CLK, 0, 6, 0x31, 0xf0,
	    SPIM1_CLK, SCP_SPI1_A_CK, TDMIN_BCK, SCP_SDA0,
	    CMVREF7, GDU_SUM_TROOP2_1, DBG_MON_A30),
	PIN(77, SPIM1_MOSI, 0, 9, 0x31, 0xf0,
	    SPIM1_MOSI, SCP_SPI1_A_MO, TDMIN_LRCK, SCP_SCL1,
	    RES5, GDU_SUM_TROOP2_2, DBG_MON_A31),
	PIN(78, SPIM1_MISO, 0, 8, 0x31, 0xf0,
	    SPIM1_MISO, SCP_SPI1_A_MI, TDMIN_DI, SCP_SDA1,
	    RES5, RES6, DBG_MON_A32),
	PIN(79, SPIM2_CSB, 0, 12, 0x24, 0x80,
	    SPIM2_CSB, SCP_SPI2_CS, I2SO1_MCK, UTXD2,
	    TP_UTXD2_AO, PCM_SYNC, DBG_MON_B0),
	PIN(80, SPIM2_CLK, 0, 11, 0x24, 0x80,
	    SPIM2_CLK, SCP_SPI2_CK, I2SO1_BCK, URXD2,
	    TP_URXD2_AO, PCM_CLK, DBG_MON_B1),
	PIN(81, SPIM2_MOSI, 0, 14, 0x24, 0x80,
	    SPIM2_MOSI, SCP_SPI2_MO, I2SO1_WS, URTS2,
	    TP_URTS2_AO, PCM_DO, DBG_MON_B2),
	PIN(82, SPIM2_MISO, 0, 13, 0x24, 0x80,
	    SPIM2_MISO, SCP_SPI2_MI, I2SO1_D0, UCTS2,
	    TP_UCTS2_AO, PCM_DI, DBG_MON_B3),
	PIN(83, USB0_IDDIG, 0, 16, 0x32, 0xe0,
	    IDDIG, RES2, RES3, RES4,
	    RES5, RES6, RES7),
	PIN(84, USB0_DRV_VBUS, 0, 15, 0x32, 0xe0,
	    USB_DRVVBUS, RES2, RES3, RES4,
	    RES5, RES6, RES7),
	PIN(85, USB0_VBUS_VALID, 0, 17, 0x32, 0xe0,
	    VBUSVALID, RES2, RES3, RES4,
	    RES5, RES6, RES7),
	PIN(86, USB1_IDDIG, 0, 19, 0x32, 0xe0,
	    IDDIG_1P, UTXD1, URTS2, PWM_2,
	    TP_GPIO4_AO, AUXIF_ST0, DBG_MON_B4),
	PIN(87, USB1_DRV_VBUS, 0, 18, 0x32, 0xe0,
	    USB_DRVVBUS_1P, URXD1, UCTS2, PWM_3,
	    TP_GPIO5_AO, AUXIF_CLK0, DBG_MON_B5),
	PIN(88, USB1_VBUS_VALID, 0, 20, 0x32, 0xe0,
	    VBUSVALID_1P, UTXD2, URTS1, CLKM2,
	    TP_GPIO6_AO, AUXIF_ST1, DBG_MON_B6),
	PIN(89, USB2_IDDIG, 0, 22, 0x32, 0xe0,
	    IDDIG_2P, URXD2, UCTS1, CLKM3,
	    TP_GPIO7_AO, AUXIF_CLK1, DBG_MON_B7),
	PIN(90, USB2_DRV_VBUS, 0, 21, 0x32, 0xe0,
	    USB_DRVVBUS_2P, UTXD3, ADSP_UTXD0, SSPM_UTXD_AO,
	    MD32_0_TXD, MD32_1_TXD, DBG_MON_B8),
	PIN(91, USB2_VBUS_VALID, 0, 23, 0x32, 0xe0,
	    VBUSVALID_2P, URXD3, ADSP_URXD0, SSPM_URXD_AO,
	    MD32_0_RXD, MD32_1_RXD, DBG_MON_B9),
	PIN(92, PWRAP_SPI_CSN, 0, 3, 0x32, 0xe0,
	    PWRAP_SPI0_CSN, RES2, RES3, RES4,
	    RES5, RES6, RES7),
	PIN(93, PWRAP_SPI_CK, 0, 2, 0x32, 0xe0,
	    PWRAP_SPI0_CK, RES2, RES3, RES4,
	    RES5, RES6, RES7),
	PIN(94, PWRAP_SPI_MO, 0, 5, 0x32, 0xe0,
	    PWRAP_SPI0_MO, PWRAP_SPI0_MI, RES3, RES4,
	    RES5, RES6, RES7),
	PIN(95, PWRAP_SPI_MI, 0, 4, 0x32, 0xe0,
	    PWRAP_SPI0_MI, PWRAP_SPI0_MO, RES3, RES4,
	    RES5, RES6, RES7),
	PIN(96, PMIC_SRCLKENA0, 0, 31, 0x32, 0xd0,
	    SRCLKENA0, RES2, RES3, RES4,
	    RES5, RES6, RES7),
	PIN(97, PMIC_SRCLKENA1, 0, 0, 0x32, 0xe0,
	    SRCLKENA1, RES2, RES3, RES4,
	    RES5, RES6, RES7),
	PIN(98, SCP_VREQ_VAO, 0, 8, 0x32, 0xe0,
	    SCP_VREQ_VAO, DVFSRC_EXT_REQ, RES3, RES4,
	    RES5, RES6, RES7),
	PIN(99, PMIC_RTC32K_CK, 0, 30, 0x32, 0xd0,
	    RTC32K_CK, RES2, RES3, RES4,
	    RES5, RES6, RES7),
	PIN(100, PMIC_WATCHDOG, 0, 1, 0x32, 0xe0,
	    WATCHDOG, RES2, RES3, RES4,
	    RES5, RES6, RES7),
	PIN(101, AUD_CLK_MOSI, 0, 0, 0x32, 0xd0,
	    AUD_CLK_MOSI, I2SO1_MCK, I2SIN_BCK, RES4,
	    RES5, RES6, RES7),
	PIN(102, AUD_SYNC_MOSI, 0, 5, 0x32, 0xd0,
	    AUD_SYNC_MOSI, I2SO1_BCK, I2SIN_WS, RES4,
	    RES5, RES6, RES7),
	PIN(103, AUD_DAT_MOSI0, 0, 3, 0x32, 0xd0,
	    AUD_DAT_MOSI0, I2SO1_WS, I2SIN_D0, RES4,
	    RES5, RES6, RES7),
	PIN(104, AUD_DAT_MOSI1, 0, 4, 0x32, 0xd0,
	    AUD_DAT_MOSI1, I2SO1_D0, I2SIN_D1, RES4,
	    RES5, RES6, RES7),
	PIN(105, AUD_DAT_MISO0, 0, 1, 0x32, 0xd0,
	    AUD_DAT_MISO0, VOW_DAT_MISO, I2SIN_D2, RES4,
	    RES5, RES6, RES7),
	PIN(106, AUD_DAT_MISO1, 0, 2, 0x32, 0xd0,
	    AUD_DAT_MISO1, VOW_CLK_MISO, I2SIN_D3, RES4,
	    RES5, RES6, RES7),
	PIN(107, I2SIN_MCK, 0, 21, 0x32, 0xd0,
	    I2SIN_MCK, SPLIN_MCK, SPDIF_IN0, CMVREF4,
	    AUXIF_ST0, PGD_LV_LSC_PWR0, RES7),
	PIN(108, I2SIN_BCK, 0, 16, 0x32, 0xd0,
	    I2SIN_BCK, SPLIN_LRCK, DMIC4_CLK, CMVREF5,
	    AUXIF_CLK0, PGD_LV_LSC_PWR1, DBG_MON_B10),
	PIN(109, I2SIN_WS, 0, 22, 0x32, 0xd0,
	    I2SIN_WS, SPLIN_BCK, DMIC4_DAT, CMVREF6,
	    AUXIF_ST1, PGD_LV_LSC_PWR2, DBG_MON_B11),
	PIN(110, I2SIN_D0, 0, 17, 0x32, 0xd0,
	    I2SIN_D0, SPLIN_D0, DMIC4_DAT_R, CMVREF7,
	    AUXIF_CLK1, PGD_LV_LSC_PWR3, DBG_MON_B12),
	PIN(111, I2SIN_D1, 0, 18, 0x32, 0xd0,
	    I2SIN_D1, SPLIN_D1, DMIC3_CLK, SPDIF_OUT,
	    RES5, PGD_LV_LSC_PWR4, DBG_MON_B13),
	PIN(112, I2SIN_D2, 0, 19, 0x32, 0xd0,
	    I2SIN_D2, SPLIN_D2, DMIC3_DAT, TDMIN_MCK,
	    I2SO1_WS, PGD_LV_LSC_PWR5, DBG_MON_B14),
	PIN(113, I2SIN_D3, 0, 20, 0x32, 0xd0,
	    I2SIN_D3, SPLIN_D3, DMIC3_DAT_R, TDMIN_BCK,
	    I2SO1_D0, RES6, DBG_MON_B15),
	PIN(114, I2SO2_MCK, 0, 28, 0x32, 0xd0,
	    I2SO2_MCK, I2SIN_MCK, MCUPM_JTAG_TMS, APU_JTAG_TMS,
	    SCP_JTAG1_TMS, SPM_JTAG_TMS, DBG_MON_B16),
	PIN(115, I2SO2_BCK, 0, 23, 0x32, 0xd0,
	    I2SO2_BCK, I2SIN_BCK, MCUPM_JTAG_TCK, APU_JTAG_TCK,
	    SCP_JTAG1_TCK, SPM_JTAG_TCK, DBG_MON_B17),
	PIN(116, I2SO2_WS, 0, 29, 0x32, 0xd0,
	    I2SO2_WS, I2SIN_WS, MCUPM_JTAG_TDI, APU_JTAG_TDI,
	    SCP_JTAG1_TDI, SPM_JTAG_TDI, DBG_MON_B18),
	PIN(117, I2SO2_D0, 0, 24, 0x32, 0xd0,
	    I2SO2_D0, I2SIN_D0, MCUPM_JTAG_TDO, APU_JTAG_TDO,
	    SCP_JTAG1_TDO, SPM_JTAG_TDO, DBG_MON_B19),
	PIN(118, I2SO2_D1, 0, 25, 0x32, 0xd0,
	    I2SO2_D1, I2SIN_D1, MCUPM_JTAG_TRSTN, APU_JTAG_TRST,
	    SCP_JTAG1_TRSTN, SPM_JTAG_TRSTN, DBG_MON_B20),
	PIN(119, I2SO2_D2, 0, 26, 0x32, 0xd0,
	    I2SO2_D2, I2SIN_D2, UTXD3, TDMIN_LRCK,
	    I2SO1_MCK, SSPM_UTXD_AO, DBG_MON_B21),
	PIN(120, I2SO2_D3, 0, 27, 0x32, 0xd0,
	    I2SO2_D3, I2SIN_D3, URXD3, TDMIN_DI,
	    I2SO1_BCK, SSPM_URXD_AO, DBG_MON_B22),
	PIN(121, PCM_CLK, 0, 8, 0x23, 0x70,
	    PCM_CLK, SPIM4_CSB, SCP_SPI1_B_CS, TP_UTXD2_AO,
	    AUXIF_ST0, PGD_DA_EFUSE_RDY, DBG_MON_B23),
	PIN(122, PCM_SYNC, 0, 11, 0x23, 0x70,
	    PCM_SYNC, SPIM4_CLK, SCP_SPI1_B_CK, TP_URXD2_AO,
	    AUXIF_CLK0, PGD_DA_EFUSE_RDY_PRE, DBG_MON_B24),
	PIN(123, PCM_DO, 0, 10, 0x23, 0x70,
	    PCM_DO, SPIM4_MOSI, SCP_SPI1_B_MO, TP_URTS2_AO,
	    AUXIF_ST1, PGD_DA_PWRGD_RESET, DBG_MON_B25),
	PIN(124, PCM_DI, 0, 9, 0x23, 0x70,
	    PCM_DI, SPIM4_MISO, SCP_SPI1_B_MI, TP_UCTS2_AO,
	    AUXIF_CLK1, PGD_DA_PWRGD_ENB, DBG_MON_B26),
	PIN(125, DMIC1_CLK, 0, 6, 0x32, 0xd0,
	    DMIC1_CLK, SPINOR_CK, TDMIN_MCK, RES4,
	    RES5, LVTS_FOUT, DBG_MON_B27),
	PIN(126, DMIC1_DAT, 0, 7, 0x32, 0xd0,
	    DMIC1_DAT, SPINOR_CS, TDMIN_BCK, RES4,
	    RES5, LVTS_SDO, DBG_MON_B28),
	PIN(127, DMIC1_DAT_R, 0, 8, 0x32, 0xd0,
	    DMIC1_DAT_R, SPINOR_IO0, TDMIN_LRCK, RES4,
	    RES5, LVTS_26M, DBG_MON_B29),
	PIN(128, DMIC2_CLK, 0, 9, 0x32, 0xd0,
	    DMIC2_CLK, SPINOR_IO1, TDMIN_DI, RES4,
	    RES5, LVTS_SCF, DBG_MON_B30),
	PIN(129, DMIC2_DAT, 0, 10, 0x32, 0xd0,
	    DMIC2_DAT, SPINOR_IO2, SPDIF_IN1, RES4,
	    RES5, LVTS_SCK, DBG_MON_B31),
	PIN(130, DMIC2_DAT_R, 0, 11, 0x32, 0xd0,
	    DMIC2_DAT_R, SPINOR_IO3, SPDIF_IN2, RES4,
	    RES5, LVTS_SDI, DBG_MON_B32),
	PIN(131, DPI_D0, 1, 1, 0x31, 0xd0,
	    DPI_D0, GBE_TXD3, DMIC1_CLK, I2SO2_MCK,
	    TP_GPIO0_AO, SPIM5_CSB, PGD_LV_HSC_PWR0),
	PIN(132, DPI_D1, 1, 2, 0x31, 0xd0,
	    DPI_D1, GBE_TXD2, DMIC1_DAT, I2SO2_BCK,
	    TP_GPIO1_AO, SPIM5_CLK, PGD_LV_HSC_PWR1),
	PIN(133, DPI_D2, 1, 9, 0x31, 0xd0,
	    DPI_D2, GBE_TXD1, DMIC1_DAT_R, I2SO2_WS,
	    TP_GPIO2_AO, SPIM5_MOSI, PGD_LV_HSC_PWR2),
	PIN(134, DPI_D3, 1, 10, 0x31, 0xd0,
	    DPI_D3, GBE_TXD0, DMIC2_CLK, I2SO2_D0,
	    TP_GPIO3_AO, SPIM5_MISO, PGD_LV_HSC_PWR3),
	PIN(135, DPI_D4, 1, 11, 0x31, 0xd0,
	    DPI_D4, GBE_RXD3, DMIC2_DAT, I2SO2_D1,
	    TP_GPIO4_AO, WAKEN, PGD_LV_HSC_PWR4),
	PIN(136, DPI_D5, 1, 12, 0x31, 0xd0,
	    DPI_D5, GBE_RXD2, DMIC2_DAT_R, I2SO2_D2,
	    TP_GPIO5_AO, PERSTN, PGD_LV_HSC_PWR5),
	PIN(137, DPI_D6, 1, 13, 0x31, 0xd0,
	    DPI_D6, GBE_RXD1, DMIC3_CLK, I2SO2_D3,
	    TP_GPIO6_AO, CLKREQN, PWM_0),
	PIN(138, DPI_D7, 1, 14, 0x31, 0xd0,
	    DPI_D7, GBE_RXD0, DMIC3_DAT, CLKM2,
	    TP_GPIO7_AO, RES6, MD32_0_GPIO0),
	PIN(139, DPI_D8, 1, 15, 0x31, 0xd0,
	    DPI_D8, GBE_TXC, DMIC3_DAT_R, CLKM3,
	    TP_UTXD2_AO, UTXD2, MD32_0_GPIO1),
	PIN(140, DPI_D9, 1, 16, 0x31, 0xd0,
	    DPI_D9, GBE_RXC, DMIC4_CLK, PWM_2,
	    TP_URXD2_AO, URXD2, MD32_0_GPIO2),
	PIN(141, DPI_D10, 1, 3, 0x31, 0xd0,
	    DPI_D10, GBE_RXDV, DMIC4_DAT, PWM_3,
	    TP_URTS2_AO, URTS2, MD32_1_GPIO0),
	PIN(142, DPI_D11, 1, 4, 0x31, 0xd0,
	    DPI_D11, GBE_TXEN, DMIC4_DAT_R, PWM_1,
	    TP_UCTS2_AO, UCTS2, MD32_1_GPIO1),
	PIN(143, DPI_D12, 1, 5, 0x31, 0xd0,
	    DPI_D12, GBE_MDC, MD32_0_GPIO0, CLKM0,
	    SPIM3_CSB, UTXD1, MD32_1_GPIO2),
	PIN(144, DPI_D13, 1, 6, 0x31, 0xd0,
	    DPI_D13, GBE_MDIO, MD32_0_GPIO1, CLKM1,
	    SPIM3_CLK, URXD1, PGD_HV_HSC_PWR0),
	PIN(145, DPI_D14, 1, 7, 0x31, 0xd0,
	    DPI_D14, GBE_TXER, MD32_1_GPIO0, CMFLASH0,
	    SPIM3_MOSI, GBE_AUX_PPS2, PGD_HV_HSC_PWR1),
	PIN(146, DPI_D15, 1, 8, 0x31, 0xd0,
	    DPI_D15, GBE_RXER, MD32_1_GPIO1, CMFLASH1,
	    SPIM3_MISO, GBE_AUX_PPS3, PGD_HV_HSC_PWR2),
	PIN(147, DPI_HSYNC, 1, 18, 0x31, 0xd0,
	    DPI_HSYNC, GBE_COL, I2SO1_MCK, CMVREF0,
	    SPDIF_OUT, URTS1, PGD_HV_HSC_PWR3),
	PIN(148, DPI_VSYNC, 1, 19, 0x31, 0xd0,
	    DPI_VSYNC, GBE_INTR, I2SO1_BCK, CMVREF1,
	    SPDIF_IN0, UCTS1, PGD_HV_HSC_PWR4),
	PIN(149, DPI_DE, 1, 17, 0x31, 0xd0,
	    DPI_DE, GBE_AUX_PPS0, I2SO1_WS, CMVREF2,
	    SPDIF_IN1, UTXD3, PGD_HV_HSC_PWR5),
	PIN(150, DPI_CK, 1, 0, 0x31, 0xd0,
	    DPI_CK, GBE_AUX_PPS1, I2SO1_D0, CMVREF3,
	    SPDIF_IN2, URXD3, RES7),
	PIN(151, EMMC_DAT7, 1, 9, 0x32, 0xc0,
	    MSDC0_DAT7, RES2, RES3, RES4,
	    RES5, RES6, RES7),
	PIN(152, EMMC_DAT6, 1, 8, 0x32, 0xc0,
	    MSDC0_DAT6, RES2, RES3, RES4,
	    RES5, RES6, RES7),
	PIN(153, EMMC_DAT5, 1, 7, 0x32, 0xc0,
	    MSDC0_DAT5, RES2, RES3, RES4,
	    RES5, RES6, RES7),
	PIN(154, EMMC_DAT4, 1, 6, 0x32, 0xc0,
	    MSDC0_DAT4, RES2, RES3, RES4,
	    RES5, RES6, RES7),
	PIN(155, EMMC_RSTB, 1, 11, 0x32, 0xc0,
	    MSDC0_RSTB, RES2, RES3, RES4,
	    RES5, RES6, RES7),
	PIN(156, EMMC_CMD, 1, 1, 0x32, 0xc0,
	    MSDC0_CMD, RES2, RES3, RES4,
	    RES5, RES6, RES7),
	PIN(157, EMMC_CLK, 1, 0, 0x32, 0xc0,
	    MSDC0_CLK, RES2, RES3, RES4,
	    RES5, RES6, RES7),
	PIN(158, EMMC_DAT3, 1, 5, 0x32, 0xc0,
	    MSDC0_DAT3, RES2, RES3, RES4,
	    RES5, RES6, RES7),
	PIN(159, EMMC_DAT2, 1, 4, 0x32, 0xc0,
	    MSDC0_DAT2, RES2, RES3, RES4,
	    RES5, RES6, RES7),
	PIN(160, EMMC_DAT1, 1, 3, 0x32, 0xc0,
	    MSDC0_DAT1, RES2, RES3, RES4,
	    RES5, RES6, RES7),
	PIN(161, EMMC_DAT0, 1, 2, 0x32, 0xc0,
	    MSDC0_DAT0, RES2, RES3, RES4,
	    RES5, RES6, RES7),
	PIN(162, EMMC_DSL, 1, 10, 0x32, 0xc0,
	    MSDC0_DSL, RES2, RES3, RES4,
	    RES5, RES6, RES7),
	PIN(163, MSDC1_CMD, 1, 1, 0x24, 0x70,
	    MSDC1_CMD, SPDIF_OUT, MD32_0_JTAG_TMS, ADSP_JTAG0_TMS,
	    SCP_JTAG0_TMS, CCU0_JTAG_TMS, IPU_JTAG_TMS),
	PIN(164, MSDC1_CLK, 1, 0, 0x24, 0x70,
	    MSDC1_CLK, SPDIF_IN0, MD32_0_JTAG_TCK, ADSP_JTAG0_TCK,
	    SCP_JTAG0_TCK, CCU0_JTAG_TCK, IPU_JTAG_TCK),
	PIN(165, MSDC1_DAT0, 1, 2, 0x24, 0x70,
	    MSDC1_DAT0, SPDIF_IN1, MD32_0_JTAG_TDI, ADSP_JTAG0_TDI,
	    SCP_JTAG0_TDI, CCU0_JTAG_TDI, IPU_JTAG_TDI),
	PIN(166, MSDC1_DAT1, 1, 3, 0x24, 0x70,
	    MSDC1_DAT1, SPDIF_IN2, MD32_0_JTAG_TDO, ADSP_JTAG0_TDO,
	    SCP_JTAG0_TDO, CCU0_JTAG_TDO, IPU_JTAG_TDO),
	PIN(167, MSDC1_DAT2, 1, 4, 0x24, 0x70,
	    MSDC1_DAT2, PWM_0, MD32_0_JTAG_TRST, ADSP_JTAG0_TRSTN,
	    SCP_JTAG0_TRSTN, CCU0_JTAG_TRST, IPU_JTAG_TRST),
	PIN(168, MSDC1_DAT3, 1, 5, 0x24, 0x70,
	    MSDC1_DAT3, PWM_1, CLKM0, RES4,
	    RES5, RES6, RES7),
	PIN(169, MSDC2_CMD, 1, 1, 0x23, 0x60,
	    MSDC2_CMD, LVTS_FOUT, MD32_1_JTAG_TMS, UDI_TMS,
	    VPU_UDI_TMS, TDMIN_MCK, SSPM_JTAG_TMS),
	PIN(170, MSDC2_CLK, 1, 0, 0x23, 0x60,
	    MSDC2_CLK, LVTS_SDO, MD32_1_JTAG_TCK, UDI_TCK,
	    VPU_UDI_TCK, TDMIN_BCK, SSPM_JTAG_TCK),
	PIN(171, MSDC2_DAT0, 1, 2, 0x23, 0x60,
	    MSDC2_DAT0, LVTS_26M, MD32_1_JTAG_TDI, UDI_TDI,
	    VPU_UDI_TDI, TDMIN_LRCK, SSPM_JTAG_TDI),
	PIN(172, MSDC2_DAT1, 1, 3, 0x23, 0x60,
	    MSDC2_DAT1, LVTS_SCF, MD32_1_JTAG_TDO, UDI_TDO,
	    VPU_UDI_TDO, TDMIN_DI, SSPM_JTAG_TDO),
	PIN(173, MSDC2_DAT2, 1, 4, 0x23, 0x60,
	    MSDC2_DAT2, LVTS_SCK, MD32_1_JTAG_TRST, UDI_NTRST,
	    VPU_UDI_NTRST, RES6, SSPM_JTAG_TRSTN),
	PIN(174, MSDC2_DAT3, 1, 5, 0x23, 0x60,
	    MSDC2_DAT3, LVTS_SDI, RES3, RES4,
	    RES5, RES6, RES7),
	PIN(175, SPMI_M_SCL, 0, 11, 0x32, 0xe0,
	    SPMI_M_SCL, RES2, RES3, RES4,
	    RES5, RES6, RES7),
	PIN(176, SPMI_M_SDA, 0, 12, 0x32, 0xe0,
	    SPMI_M_SDA, RES2, RES3, RES4,
	    RES5, RES6, RES7),
};

struct val_regs {
	uint32_t val;
	uint32_t set;
	uint32_t rst;
	uint32_t align;
};
struct gpio_regs {
	struct val_regs dir[7];
	uint8_t rsv00[144];
	struct val_regs dout[7];
	uint8_t rsv01[144];
	struct val_regs din[7];
	uint8_t rsv02[144];
	struct val_regs mode[28];
	uint8_t rsv03[560];
	uint32_t dram_pinmux_trapping;
};
check_member(gpio_regs, mode[27].val, 0x4b0);
check_member(gpio_regs, dram_pinmux_trapping, 0x6f0);
static struct gpio_regs *const mtk_gpio = (void *)(GPIO_BASE);
#endif /* MT_GPIO_H */
