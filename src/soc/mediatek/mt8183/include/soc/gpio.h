/* SPDX-License-Identifier: GPL-2.0-only */
/* This file is part of the coreboot project. */

#ifndef SOC_MEDIATEK_MT8183_GPIO_H
#define SOC_MEDIATEK_MT8183_GPIO_H

#include <soc/addressmap.h>
#include <soc/gpio_common.h>
#include <types.h>
#include <soc/spi_common.h>

enum {
	MAX_GPIO_REG_BITS = 32,
	MAX_GPIO_MODE_PER_REG = 8,
	GPIO_MODE_BITS = 4,
};

#define IOCFG_TO_GPIO_BASE(x) ((x >> 16) & 0xff)
#define GPIO_TO_IOCFG_BASE(x) ((void *)(IOCFG_RT_BASE & 0xff000000) + \
			       ((x) << 16))

#define PIN(id, name, flag, bit, base, offset, \
	    func1, func2, func3, func4, func5, func6, func7) \
	PAD_##name##_ID = id, \
	PAD_##name##_FLAG = flag, \
	PAD_##name##_BIT = bit, \
	PAD_##name##_BASE = IOCFG_TO_GPIO_BASE(base), \
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
	PIN(0, EINT0, 0, 6, IOCFG_RM_BASE, 0x00,
		MRG_SYNC, PCM0_SYNC, TP_GPIO0_AO,
		SRCLKENAI0, SCP_SPI2_CS, I2S3_MCK, SPI2_CSB),
	PIN(1, EINT1, 0, 7, IOCFG_RM_BASE, 0x00,
		MRG_CLK, PCM0_CLK, TP_GPIO1_AO,
		CLKM3, SCP_SPI2_MO, I2S3_BCK, SPI2_MO),
	PIN(2, EINT2, 0, 8, IOCFG_RM_BASE, 0x00,
		MRG_DO, PCM0_DO, TP_GPIO2_AO,
		SCL6, SCP_SPI2_CK, I2S3_LRCK, SPI2_CLK),
	PIN(3, EINT3, 0, 9, IOCFG_RM_BASE, 0x00,
		MRG_DI, PCM0_DI, TP_GPIO3_AO,
		DA6, TDM_MCK, I2S3_DO, SCP_VREQ_VAO),
	PIN(4, EINT4, 0, 11, IOCFG_RM_BASE, 0x00,
		PWM_B, I2S0_MCK, SSPM_UTXD_AO,
		MD_URXD1, TDM_BCK, TP_GPIO4_AO, DAP_MD32_SWD),
	PIN(5, EINT5, 0, 12, IOCFG_RM_BASE, 0x00,
		PWM_C, I2S0_BCK, SSPM_URXD_AO,
		MD_UTXD1, TDM_LRCK, TP_GPIO5_AO, DAP_MD32_SWCK),
	PIN(6, EINT6, 0, 13, IOCFG_RM_BASE, 0x00,
		PWM_A, I2S0_LRCK, IDDIG,
		MD_URXD0, TDM_DATA0, TP_GPIO6_AO, CMFLASH),
	PIN(7, EINT7, 0, 14, IOCFG_RM_BASE, 0x00,
		SPI1_B_MI, I2S0_DI, USB_DRVVBUS,
		MD_UTXD0, TDM_DATA1, TP_GPIO7_AO, DVFSRC_EXT_REQ),
	PIN(8, EINT8, 0, 0, IOCFG_RM_BASE, 0x00,
		SPI1_B_CSB, ANT_SEL3, SCL7,
		CONN_MCU_TRST_B, TDM_DATA2, MD_INT0, JTRSTN_SEL1),
	PIN(9, EINT9, 0, 26, IOCFG_RM_BASE, 0x00,
		SPI1_B_MO, ANT_SEL4, CMMCLK2,
		CONN_MCU_DBGACK_N, SSPM_JTAG_TRSTN, IO_JTAG_TRSTN, DBG_MON_B10),
	PIN(10, EINT10, 0, 27, IOCFG_RM_BASE, 0x00,
		SPI1_B_CLK, ANT_SEL5, CMMCLK3,
		CONN_MCU_DBGI_N, TDM_DATA3, EXT_FRAME_SYNC, DBG_MON_B11),
	PIN(11, SCL6, 0, 10, IOCFG_LT_BASE, 0x00,
		TP_URXD1_AO, IDDIG, SCL6,
		UCTS1, UCTS0, SRCLKENAI1, I2S5_MCK),
	PIN(12, SDA6, 0, 17, IOCFG_LT_BASE, 0x00,
		TP_UTXD1_AO, USB_DRVVBUS, SDA6,
		URTS1, URTS0, I2S2_DI2, I2S5_BCK),
	PIN(13, DPI_D0, 0, 6, IOCFG_LM_BASE, 0x00,
		DBPI_D0, SPI5_MI, PCM0_SYNC,
		MD_URXD0, ANT_SEL3, I2S0_MCK, DBG_MON_B15),
	PIN(14, DPI_D1, 0, 7, IOCFG_LM_BASE, 0x00,
		DBPI_D1, SPI5_CSB, PCM0_CLK,
		MD_UTXD0, ANT_SEL4, I2S0_BCK, DBG_MON_B16),
	PIN(15, DPI_D2, 0, 8, IOCFG_LM_BASE, 0x00,
		DBPI_D2, SPI5_MO, PCM0_DO,
		MD_URXD1, ANT_SEL5, I2S0_LRCK, DBG_MON_B17),
	PIN(16, DPI_D3, 0, 9, IOCFG_LM_BASE, 0x00,
		DBPI_D3, SPI5_CLK, PCM0_DI,
		MD_UTXD1, ANT_SEL6, I2S0_DI, DBG_MON_B23),
	PIN(17, DPI_D4, 0, 10, IOCFG_LM_BASE, 0x00,
		DBPI_D4, SPI4_MI, CONN_MCU_TRST_B,
		MD_INT0, ANT_SEL7, I2S3_MCK, DBG_MON_A1),
	PIN(18, DPI_D5, 0, 11, IOCFG_LM_BASE, 0x00,
		DBPI_D5, SPI4_CSB, CONN_MCU_DBGI_N,
		MD_INT0, SCP_VREQ_VAO, I2S3_BCK, DBG_MON_A2),
	PIN(19, DPI_D6, 0, 12, IOCFG_LM_BASE, 0x00,
		DBPI_D6, SPI4_MO, CONN_MCU_TDO,
		MD_INT2_C2K_UIM1_HOT_PLUG, URXD1, I2S3_LRCK, DBG_MON_A3),
	PIN(20, DPI_D7, 0, 13, IOCFG_LM_BASE, 0x00,
		DBPI_D7, SPI4_CLK, CONN_MCU_DBGACK_N,
		MD_INT1_C2K_UIM0_HOT_PLUG, UTXD1, I2S3_DO, DBG_MON_A19),
	PIN(21, DPI_D8, 0, 14, IOCFG_LM_BASE, 0x00,
		DBPI_D8, SPI3_MI, CONN_MCU_TMS,
		DAP_MD32_SWD, CONN_MCU_AICE_TMSC, I2S2_MCK, DBG_MON_B5),
	PIN(22, DPI_D9, 0, 15, IOCFG_LM_BASE, 0x00,
		DBPI_D9, SPI3_CSB, CONN_MCU_TCK,
		DAP_MD32_SWCK, CONN_MCU_AICE_TCKC, I2S2_BCK, DBG_MON_B6),
	PIN(23, DPI_D10, 0, 16, IOCFG_LM_BASE, 0x00,
		DBPI_D10, SPI3_MO, CONN_MCU_TDI,
		UCTS1, EXT_FRAME_SYNC, I2S2_LRCK, DBG_MON_B7),
	PIN(24, DPI_D11, 0, 17, IOCFG_LM_BASE, 0x00,
		DBPI_D11, SPI3_CLK, SRCLKENAI0,
		URTS1, IO_JTAG_TCK, I2S2_DI, DBG_MON_B31),
	PIN(25, DPI_HSYNC, 0, 18, IOCFG_LM_BASE, 0x00,
		DBPI_HSYNC, ANT_SEL0, SCL6,
		KPCOL2, IO_JTAG_TMS, I2S1_MCK, DBG_MON_B0),
	PIN(26, DPI_VSYNC, 0, 19, IOCFG_LM_BASE, 0x00,
		DBPI_VSYNC, ANT_SEL1, SDA6,
		KPROW2, IO_JTAG_TDI, I2S1_BCK, DBG_MON_B1),
	PIN(27, DPI_DE, 0, 20, IOCFG_LM_BASE, 0x00,
		DBPI_DE, ANT_SEL2, SCL7,
		DMIC_CLK, IO_JTAG_TDO, I2S1_LRCK, DBG_MON_B9),
	PIN(28, DPI_CK, 0, 21, IOCFG_LM_BASE, 0x00,
		DBPI_CK, DVFSRC_EXT_REQ, SDA7,
		DMIC_DAT, IO_JTAG_TRSTN, I2S1_DO, DBG_MON_B32),
	PIN(29, MSDC1_CLK, 1, 0, IOCFG_LM_BASE, 0xc0,
		MSDC1_CLK, IO_JTAG_TCK, UDI_TCK,
		CONN_DSP_JCK, SSPM_JTAG_TCK, PCM1_CLK, DBG_MON_A6),
	PIN(30, MSDC1_DAT3, 1, 4, IOCFG_LM_BASE, 0xc0,
		MSDC1_DAT3, DAP_MD32_SWD, CONN_MCU_AICE_TMSC,
		CONN_DSP_JINTP, SSPM_JTAG_TRSTN, PCM1_DI, DBG_MON_A7),
	PIN(31, MSDC1_CMD, 1, 8, IOCFG_LM_BASE, 0xc0,
		MSDC1_CMD, IO_JTAG_TMS, UDI_TMS,
		CONN_DSP_JMS, SSPM_JTAG_TMS, PCM1_SYNC, DBG_MON_A8),
	PIN(32, MSDC1_DAT0, 1, 12, IOCFG_LM_BASE, 0xc0,
		MSDC1_DAT0, IO_JTAG_TDI, UDI_TDI,
		CONN_DSP_JDI, SSPM_JTAG_TDI, PCM1_DO0, DBG_MON_A9),
	PIN(33, MSDC1_DAT2, 1, 16, IOCFG_LM_BASE, 0xc0,
		MSDC1_DAT2, IO_JTAG_TRSTN, UDI_NTRST,
		DAP_MD32_SWCK, CONN_MCU_AICE_TCKC, PCM1_DO2, DBG_MON_A10),
	PIN(34, MSDC1_DAT1, 1, 20, IOCFG_LM_BASE, 0xc0,
		MSDC1_DAT1, IO_JTAG_TDO, UDI_TDO,
		CONN_DSP_JDO, SSPM_JTAG_TDO, PCM1_DO1, DBG_MON_A11),
	PIN(35, SIM2_SIO, 1, 0, IOCFG_LB_BASE, 0xc0,
		MD1_SIM2_SIO, CCU_JTAG_TDO, MD1_SIM1_SIO,
		RES4, SCP_JTAG_TDO, CONN_DSP_JMS, DBG_MON_A28),
	PIN(36, SIM2_SRST, 1, 4, IOCFG_LB_BASE, 0xc0,
		MD1_SIM2_SRST, CCU_JTAG_TMS, MD1_SIM1_SRST,
		CONN_MCU_AICE_TMSC, SCP_JTAG_TMS, CONN_DSP_JINTP, DBG_MON_A29),
	PIN(37, SIM2_SCLK, 1, 8, IOCFG_LB_BASE, 0xc0,
		MD1_SIM2_SCLK, CCU_JTAG_TDI, MD1_SIM1_SCLK,
		RES4, SCP_JTAG_TDI, CONN_DSP_JDO, DBG_MON_A30),
	PIN(38, SIM1_SCLK, 1, 12, IOCFG_LB_BASE, 0xc0,
		MD1_SIM1_SCLK, RES2, MD1_SIM2_SCLK,
		CONN_MCU_AICE_TCKC, RES5, RES6, DBG_MON_A20),
	PIN(39, SIM1_SRST, 1, 16, IOCFG_LB_BASE, 0xc0,
		MD1_SIM1_SRST, CCU_JTAG_TCK, MD1_SIM2_SRST,
		RES4, SCP_JTAG_TCK, CONN_DSP_JCK, DBG_MON_A31),
	PIN(40, SIM1_SIO, 1, 20, IOCFG_LB_BASE, 0xc0,
		MD1_SIM1_SIO, CCU_JTAG_TRST, MD1_SIM2_SIO,
		RES4, SCP_JTAG_TRSTN, CONN_DSP_JDI, DBG_MON_A32),
	PIN(41, IDDIG, 1, 24, IOCFG_LB_BASE, 0xc0,
		IDDIG, URXD1, UCTS0,
		SSPM_UTXD_AO, EXT_FRAME_SYNC, DMIC_CLK, RES7),
	PIN(42, DRVBUS, 1, 28, IOCFG_LB_BASE, 0xc0,
		USB_DRVVBUS, UTXD1, URTS0,
		SSPM_URXD_AO, EXT_FRAME_SYNC, DMIC_DAT, RES7),
	PIN(43, DISP_PWM, 0, 8, IOCFG_LB_BASE, 0x00,
		DISP_PWM, RES2, RES3,
		RES4, RES5, RES6, RES7),
	PIN(44, DSI_TE, 0, 9, IOCFG_LB_BASE, 0x00,
		DSI_TE, RES2, RES3,
		RES4, RES5, RES6, RES7),
	PIN(45, LCM_RST, 0, 10, IOCFG_LB_BASE, 0x00,
		LCM_RST, RES2, RES3,
		RES4, RES5, RES6, RES7),
	PIN(46, INT_SIM2, 0, 11, IOCFG_LB_BASE, 0x00,
		MD_INT2_C2K_UIM1_HOT_PLUG, URXD1, UCTS1,
		CCU_UTXD_AO, TP_UCTS1_AO, IDDIG, I2S5_LRCK),
	PIN(47, INT_SIM1, 0, 12, IOCFG_LB_BASE, 0x00,
		MD_INT1_C2K_UIM0_HOT_PLUG, UTXD1, URTS1,
		CCU_URXD_AO, TP_URTS1_AO, USB_DRVVBUS, I2S5_DO),
	PIN(48, SCL5, 0, 13, IOCFG_LB_BASE, 0x00,
		SCL5, RES2, RES3,
		RES4, RES5, RES6, RES7),
	PIN(49, SDA5, 0, 14, IOCFG_LB_BASE, 0x00,
		SDA5, RES2, RES3,
		RES4, RES5, RES6, RES7),
	PIN(50, SCL3, 0, 0, IOCFG_BL_BASE, 0x00,
		SCL3, RES2, RES3,
		RES4, RES5, RES6, RES7),
	PIN(51, SDA3, 0, 1, IOCFG_BL_BASE, 0x00,
		SDA3, RES2, RES3,
		RES4, RES5, RES6, RES7),
	PIN(52, BPI_ANT2, 0, 2, IOCFG_BL_BASE, 0x00,
		BPI_ANT2, RES2, RES3,
		RES4, RES5, RES6, RES7),
	PIN(53, BPI_ANT0, 0, 3, IOCFG_BL_BASE, 0x00,
		BPI_ANT0, RES2, RES3,
		RES4, RES5, RES6, RES7),
	PIN(54, BPI_OLAT1, 0, 4, IOCFG_BL_BASE, 0x00,
		BPI_OLAT1, RES2, RES3,
		RES4, RES5, RES6, RES7),
	PIN(55, BPI_BUS8, 0, 5, IOCFG_BL_BASE, 0x00,
		BPI_BUS8, RES2, RES3,
		RES4, RES5, RES6, RES7),
	PIN(56, BPI_BUS9, 0, 6, IOCFG_BL_BASE, 0x00,
		BPI_BUS9, SCL_6306, RES3,
		RES4, RES5, RES6, RES7),
	PIN(57, BPI_BUS10, 0, 7, IOCFG_BL_BASE, 0x00,
		BPI_BUS10, SDA_6306, RES3,
		RES4, RES5, RES6, RES7),
	PIN(58, RFIC0_BSI_D2, 0, 8, IOCFG_BL_BASE, 0x00,
		RFIC0_BSI_D2, SPM_BSI_D2, PWM_B,
		RES4, RES5, RES6, RES7),
	PIN(59, RFIC0_BSI_D1, 0, 9, IOCFG_BL_BASE, 0x00,
		RFIC0_BSI_D1, SPM_BSI_D1, RES3,
		RES4, RES5, RES6, RES7),
	PIN(60, RFIC0_BSI_D0, 0, 10, IOCFG_BL_BASE, 0x00,
		RFIC0_BSI_D0, SPM_BSI_D0, RES3,
		RES4, RES5, RES6, RES7),
	PIN(61, MISC_BSI_DO_1, 0, 0, IOCFG_RB_BASE, 0x00,
		MIPI1_SDATA, RES2, RES3,
		RES4, RES5, RES6, RES7),
	PIN(62, MISC_BSI_CK_1, 0, 1, IOCFG_RB_BASE, 0x00,
		MIPI1_SCLK, RES2, RES3,
		RES4, RES5, RES6, RES7),
	PIN(63, MISC_BSI_DO_0, 0, 2, IOCFG_RB_BASE, 0x00,
		MIPI0_SDATA, RES2, RES3,
		RES4, RES5, RES6, RES7),
	PIN(64, MISC_BSI_CK_0, 0, 3, IOCFG_RB_BASE, 0x00,
		MIPI0_SCLK, RES2, RES3,
		RES4, RES5, RES6, RES7),
	PIN(65, MISC_BSI_DO_3, 0, 4, IOCFG_RB_BASE, 0x00,
		MIPI3_SDATA, BPI_OLAT2, RES3,
		RES4, RES5, RES6, RES7),
	PIN(66, MISC_BSI_CK_3, 0, 5, IOCFG_RB_BASE, 0x00,
		MIPI3_SCLK, BPI_OLAT3, RES3,
		RES4, RES5, RES6, RES7),
	PIN(67, MISC_BSI_DO_2, 0, 6, IOCFG_RB_BASE, 0x00,
		MIPI2_SDATA, RES2, RES3,
		RES4, RES5, RES6, RES7),
	PIN(68, MISC_BSI_CK_2, 0, 7, IOCFG_RB_BASE, 0x00,
		MIPI2_SCLK, RES2, RES3,
		RES4, RES5, RES6, RES7),
	PIN(69, BPI_BUS7, 0, 8, IOCFG_RB_BASE, 0x00,
		BPI_BUS7, RES2, RES3,
		RES4, RES5, RES6, RES7),
	PIN(70, BPI_BUS6, 0, 9, IOCFG_RB_BASE, 0x00,
		BPI_BUS6, RES2, RES3,
		RES4, RES5, RES6, RES7),
	PIN(71, BPI_BUS5, 0, 10, IOCFG_RB_BASE, 0x00,
		BPI_BUS5, RES2, RES3,
		RES4, RES5, RES6, RES7),
	PIN(72, BPI_BUS4, 0, 11, IOCFG_RB_BASE, 0x00,
		BPI_BUS4, RES2, RES3,
		RES4, RES5, RES6, RES7),
	PIN(73, BPI_BUS3, 0, 12, IOCFG_RB_BASE, 0x00,
		BPI_BUS3, RES2, RES3,
		RES4, RES5, RES6, RES7),
	PIN(74, BPI_BUS2, 0, 13, IOCFG_RB_BASE, 0x00,
		BPI_BUS2, RES2, RES3,
		RES4, RES5, RES6, RES7),
	PIN(75, BPI_BUS1, 0, 14, IOCFG_RB_BASE, 0x00,
		BPI_BUS1, RES2, RES3,
		RES4, RES5, RES6, RES7),
	PIN(76, BPI_BUS0, 0, 15, IOCFG_RB_BASE, 0x00,
		BPI_BUS0, RES2, RES3,
		RES4, RES5, RES6, RES7),
	PIN(77, BPI_ANT1, 0, 16, IOCFG_RB_BASE, 0x00,
		BPI_ANT1, RES2, RES3,
		RES4, RES5, RES6, RES7),
	PIN(78, BPI_OLAT0, 0, 17, IOCFG_RB_BASE, 0x00,
		BPI_OLAT0, RES2, RES3,
		RES4, RES5, RES6, RES7),
	PIN(79, BPI_PA_VM1, 0, 18, IOCFG_RB_BASE, 0x00,
		BPI_PA_VM1, MIPI4_SDATA, RES3,
		RES4, RES5, RES6, RES7),
	PIN(80, BPI_PA_VM0, 0, 19, IOCFG_RB_BASE, 0x00,
		BPI_PA_VM0, MIPI4_SCLK, RES3,
		RES4, RES5, RES6, RES7),
	PIN(81, SDA1, 0, 20, IOCFG_RB_BASE, 0x00,
		SDA1, RES2, RES3,
		RES4, RES5, RES6, RES7),
	PIN(82, SDA0, 0, 21, IOCFG_RB_BASE, 0x00,
		SDA0, RES2, RES3,
		RES4, RES5, RES6, RES7),
	PIN(83, SCL0, 0, 22, IOCFG_RB_BASE, 0x00,
		SCL0, RES2, RES3,
		RES4, RES5, RES6, RES7),
	PIN(84, SCL1, 0, 23, IOCFG_RB_BASE, 0x00,
		SCL1, RES2, RES3,
		RES4, RES5, RES6, RES7),
	PIN(85, SPI_MI, 0, 24, IOCFG_RB_BASE, 0x00,
		SPI0_MI, SCP_SPI0_MI, CLKM3,
		I2S1_BCK, MFG_DFD_JTAG_TDO, DFD_TDO, JTDO_SEL1),
	PIN(86, SPI_CSB, 0, 25, IOCFG_RB_BASE, 0x00,
		SPI0_CSB, SCP_SPI0_CS, CLKM0,
		I2S1_LRCK, MFG_DFD_JTAG_TMS, DFD_TMS, JTMS_SEL1),
	PIN(87, SPI_MO, 0, 26, IOCFG_RB_BASE, 0x00,
		SPI0_MO, SCP_SPI0_MO, SDA1,
		I2S1_DO, MFG_DFD_JTAG_TDI, DFD_TDI, JTDI_SEL1),
	PIN(88, SPI_CLK, 0, 27, IOCFG_RB_BASE, 0x00,
		SPI0_CLK, SCP_SPI0_CK, SCL1,
		I2S1_MCK, MFG_DFD_JTAG_TCK, DFD_TCK_XI, JTCK_SEL1),
	PIN(89, SRCLKENAI, 0, 24, IOCFG_RM_BASE, 0x00,
		SRCLKENAI0, PWM_C, I2S5_BCK,
		ANT_SEL6, SDA8, CMVREF0, DBG_MON_A21),
	PIN(90, PWM_A, 0, 1, IOCFG_RM_BASE, 0x00,
		PWM_A, CMMCLK2, I2S5_LRCK,
		SCP_VREQ_VAO, SCL8, PTA_RXD, DBG_MON_A22),
	PIN(91, KPROW1, 1, 0, IOCFG_RM_BASE, 0xc0,
		KPROW1, PWM_B, I2S5_DO,
		ANT_SEL7, CMMCLK3, PTA_TXD, RES7),
	PIN(92, KPROW0, 1, 4, IOCFG_RM_BASE, 0xc0,
		KPROW0, RES2, RES3,
		RES4, RES5, RES6, RES7),
	PIN(93, KPCOL0, 1, 8, IOCFG_RM_BASE, 0xc0,
		KPCOL0, RES2, RES3,
		RES4, RES5, RES6, DBG_MON_B27),
	PIN(94, KPCOL1, 1, 12, IOCFG_RM_BASE, 0xc0,
		KPCOL1, I2S2_DI2, I2S5_MCK,
		CMMCLK2, SCP_SPI2_MI, SRCLKENAI1, SPI2_MI),
	PIN(95, URXD0, 0, 15, IOCFG_RM_BASE, 0x00,
		URXD0, UTXD0, MD_URXD0,
		MD_URXD1, SSPM_URXD_AO, CCU_URXD_AO, RES7),
	PIN(96, UTXD0, 0, 17, IOCFG_RM_BASE, 0x00,
		UTXD0, URXD0, MD_UTXD0,
		MD_UTXD1, SSPM_UTXD_AO, CCU_UTXD_AO, DBG_MON_B2),
	PIN(97, CAM_PDN0, 0, 18, IOCFG_RM_BASE, 0x00,
		UCTS0, I2S2_MCK, IDDIG,
		CONN_MCU_TDO, SSPM_JTAG_TDO, IO_JTAG_TDO, DBG_MON_B3),
	PIN(98, CAM_PDN1, 0, 19, IOCFG_RM_BASE, 0x00,
		URTS0, I2S2_BCK, USB_DRVVBUS,
		CONN_MCU_TMS, SSPM_JTAG_TMS, IO_JTAG_TMS, DBG_MON_B4),
	PIN(99, CAM_CLK0, 0, 20, IOCFG_RM_BASE, 0x00,
		CMMCLK0, RES2, RES3,
		CONN_MCU_AICE_TMSC, RES5, RES6, DBG_MON_B28),
	PIN(100, CAM_CLK1, 0, 21, IOCFG_RM_BASE, 0x00,
		CMMCLK1, PWM_C, MD_INT1_C2K_UIM0_HOT_PLUG,
		CONN_MCU_AICE_TCKC, RES5, RES6, DBG_MON_B29),
	PIN(101, CAM_RST0, 0, 22, IOCFG_RM_BASE, 0x00,
		CLKM2, I2S2_LRCK, CMVREF1,
		CONN_MCU_TCK, SSPM_JTAG_TCK, IO_JTAG_TCK, RES7),
	PIN(102, CAM_RST1, 0, 23, IOCFG_RM_BASE, 0x00,
		CLKM1, I2S2_DI, DVFSRC_EXT_REQ,
		CONN_MCU_TDI, SSPM_JTAG_TDI, IO_JTAG_TDI, DBG_MON_B8),
	PIN(103, SCL2, 0, 28, IOCFG_RM_BASE, 0x00,
		SCL2, RES2, RES3,
		RES4, RES5, RES6, RES7),
	PIN(104, SDA2, 0, 29, IOCFG_RM_BASE, 0x00,
		SDA2, RES2, RES3,
		RES4, RES5, RES6, RES7),
	PIN(105, SCL4, 0, 30, IOCFG_RM_BASE, 0x00,
		SCL4, RES2, RES3,
		RES4, RES5, RES6, RES7),
	PIN(106, SDA4, 0, 31, IOCFG_RM_BASE, 0x00,
		SDA4, RES2, RES3,
		RES4, RES5, RES6, RES7),
	PIN(107, CAM_PDN2, 0, 0, IOCFG_RT_BASE, 0x00,
		DMIC_CLK, ANT_SEL0, CLKM0,
		SDA7, EXT_FRAME_SYNC, PWM_A, DBG_MON_B12),
	PIN(108, CAM_CLK2, 0, 1, IOCFG_RT_BASE, 0x00,
		CMMCLK2, ANT_SEL1, CLKM1,
		SCL8, DAP_MD32_SWD, PWM_B, DBG_MON_B13),
	PIN(109, CAM_RST2, 0, 2, IOCFG_RT_BASE, 0x00,
		DMIC_DAT, ANT_SEL2, CLKM2,
		SDA8, DAP_MD32_SWCK, PWM_C, DBG_MON_B14),
	PIN(110, CAM_PDN3, 0, 3, IOCFG_RT_BASE, 0x00,
		SCL7, ANT_SEL0, TP_URXD1_AO,
		USB_DRVVBUS, SRCLKENAI1, KPCOL2, URXD1),
	PIN(111, CAM_CLK3, 0, 4, IOCFG_RT_BASE, 0x00,
		CMMCLK3, ANT_SEL1, SRCLKENAI0,
		SCP_VREQ_VAO, MD_INT2_C2K_UIM1_HOT_PLUG, RES6, DVFSRC_EXT_REQ),
	PIN(112, CAM_RST3, 0, 5, IOCFG_RT_BASE, 0x00,
		SDA7, ANT_SEL2, TP_UTXD1_AO,
		IDDIG, AGPS_SYNC, KPROW2, UTXD1),
	PIN(113, CONN_TOP_CLK, 0, 6, IOCFG_RT_BASE, 0x00,
		CONN_TOP_CLK, RES2, SCL6,
		AUXIF_CLK0, RES5, TP_UCTS1_AO, RES7),
	PIN(114, CONN_TOP_DATA, 0, 7, IOCFG_RT_BASE, 0x00,
		CONN_TOP_DATA, RES2, SDA6,
		AUXIF_ST0, RES5, TP_URTS1_AO, RES7),
	PIN(115, CONN_BT_CLK, 0, 8, IOCFG_RT_BASE, 0x00,
		CONN_BT_CLK, UTXD1, PTA_TXD,
		AUXIF_CLK1, DAP_MD32_SWD, TP_UTXD1_AO, RES7),
	PIN(116, CONN_BT_DATA, 0, 9, IOCFG_RT_BASE, 0x00,
		CONN_BT_DATA, IPU_JTAG_TRST, RES3,
		AUXIF_ST1, DAP_MD32_SWCK, TP_URXD2_AO, DBG_MON_A0),
	PIN(117, CONN_WF_CTRL0, 0, 10, IOCFG_RT_BASE, 0x00,
		CONN_WF_HB0, IPU_JTAG_TDO, RES3,
		RES4, RES5, TP_UTXD2_AO, DBG_MON_A4),
	PIN(118, CONN_WF_CTRL1, 0, 11, IOCFG_RT_BASE, 0x00,
		CONN_WF_HB1, IPU_JTAG_TDI, RES3,
		RES4, SSPM_URXD_AO, TP_UCTS2_AO, DBG_MON_A5),
	PIN(119, CONN_WF_CTRL2, 0, 12, IOCFG_RT_BASE, 0x00,
		CONN_WF_HB2, IPU_JTAG_TCK, RES3,
		RES4, SSPM_UTXD_AO, TP_URTS2_AO, RES7),
	PIN(120, CONN_WB_PTA, 0, 13, IOCFG_RT_BASE, 0x00,
		CONN_WB_PTA, IPU_JTAG_TMS, RES3,
		RES4, CCU_URXD_AO, RES6, RES7),
	PIN(121, CONN_HRST_B, 0, 14, IOCFG_RT_BASE, 0x00,
		CONN_HRST_B, URXD1, PTA_RXD,
		RES4, CCU_UTXD_AO, TP_URXD1_AO, RES7),
	PIN(122, MSDC0_CMD, 1, 0, IOCFG_TL_BASE, 0xc0,
		MSDC0_CMD, PWRMCU_URXD2_AO, ANT_SEL1,
		RES4, RES5, RES6, DBG_MON_A12),
	PIN(123, MSDC0_DAT0, 1, 4, IOCFG_TL_BASE, 0xc0,
		MSDC0_DAT0, RES2, ANT_SEL0,
		RES4, RES5, RES6, DBG_MON_A13),
	PIN(124, MSDC0_CLK, 1, 8, IOCFG_TL_BASE, 0xc0,
		MSDC0_CLK, RES2, RES3,
		RES4, RES5, RES6, DBG_MON_A14),
	PIN(125, MSDC0_DAT2, 1, 12, IOCFG_TL_BASE, 0xc0,
		MSDC0_DAT2, RES2, MRG_CLK,
		RES4, RES5, RES6, DBG_MON_A15),
	PIN(126, MSDC0_DAT4, 1, 16, IOCFG_TL_BASE, 0xc0,
		MSDC0_DAT4, RES2, ANT_SEL5,
		RES4, RES5, UFS_MPHY_SCL, DBG_MON_A16),
	PIN(127, MSDC0_DAT6, 1, 20, IOCFG_TL_BASE, 0xc0,
		MSDC0_DAT6, RES2, ANT_SEL4,
		RES4, RES5, UFS_MPHY_SDA, DBG_MON_A17),
	PIN(128, MSDC0_DAT1, 1, 24, IOCFG_TL_BASE, 0xc0,
		MSDC0_DAT1, RES2, ANT_SEL2,
		RES4, RES5, UFS_UNIPRO_SDA, DBG_MON_A18),
	PIN(129, MSDC0_DAT5, 1, 28, IOCFG_TL_BASE, 0xc0,
		MSDC0_DAT5, RES2, ANT_SEL3,
		RES4, RES5, UFS_UNIPRO_SCL, DBG_MON_A23),
	PIN(130, MSDC0_DAT7, 1, 0, IOCFG_TL_BASE, 0xd0,
		MSDC0_DAT7, RES2, MRG_DO,
		RES4, RES5, RES6, DBG_MON_A24),
	PIN(131, MSDC0_DSL, 1, 4, IOCFG_TL_BASE, 0xd0,
		MSDC0_DSL, RES2, MRG_SYNC,
		RES4, RES5, RES6, DBG_MON_A25),
	PIN(132, MSDC0_DAT3, 1, 8, IOCFG_TL_BASE, 0xd0,
		MSDC0_DAT3, RES2, MRG_DI,
		RES4, RES5, RES6, DBG_MON_A26),
	PIN(133, MSDC0_RSTB, 1, 12, IOCFG_TL_BASE, 0xd0,
		MSDC0_RSTB, RES2, AGPS_SYNC,
		RES4, RES5, RES6, DBG_MON_A27),
	PIN(134, RTC32K_CK, 0, 0, IOCFG_LT_BASE, 0x00,
		RTC32K_CK, RES2, RES3,
		RES4, RES5, RES6, RES7),
	PIN(135, WATCHDOG, 0, 1, IOCFG_LT_BASE, 0x00,
		WATCHDOG, RES2, RES3,
		RES4, RES5, RES6, RES7),
	PIN(136, AUD_CLK_MOSI, 0, 2, IOCFG_LT_BASE, 0x00,
		AUD_CLK_MOSI, AUD_CLK_MISO, I2S1_MCK,
		RES4, RES5, UFS_UNIPRO_SCL, RES7),
	PIN(137, AUD_SYNC_MOSI, 0, 3, IOCFG_LT_BASE, 0x00,
		AUD_SYNC_MOSI, AUD_SYNC_MISO, I2S1_BCK,
		RES4, RES5, RES6, RES7),
	PIN(138, AUD_DAT_MOSI0, 0, 4, IOCFG_LT_BASE, 0x00,
		AUD_DAT_MOSI0, AUD_DAT_MISO0, I2S1_LRCK,
		RES4, RES5, RES6, DBG_MON_B24),
	PIN(139, AUD_DAT_MOSI1, 0, 5, IOCFG_LT_BASE, 0x00,
		AUD_DAT_MOSI1, AUD_DAT_MISO1, I2S1_DO,
		RES4, RES5, UFS_MPHY_SDA, RES7),
	PIN(140, AUD_CLK_MISO, 0, 6, IOCFG_LT_BASE, 0x00,
		AUD_CLK_MISO, AUD_CLK_MOSI, I2S0_MCK,
		RES4, RES5, UFS_UNIPRO_SDA, RES7),
	PIN(141, AUD_SYNC_MISO, 0, 7, IOCFG_LT_BASE, 0x00,
		AUD_SYNC_MISO, AUD_SYNC_MOSI, I2S0_BCK,
		RES4, RES5, RES6, RES7),
	PIN(142, AUD_DAT_MISO0, 0, 8, IOCFG_LT_BASE, 0x00,
		AUD_DAT_MISO0, AUD_DAT_MOSI0, I2S0_LRCK,
		VOW_DAT_MISO, RES5, RES6, DBG_MON_B25),
	PIN(143, AUD_DAT_MISO1, 0, 9, IOCFG_LT_BASE, 0x00,
		AUD_DAT_MISO1, AUD_DAT_MOSI1, I2S0_DI,
		VOW_CLK_MISO, RES5, UFS_MPHY_SCL, DBG_MON_B26),
	PIN(144, PWRAP_SPI0_MI, 0, 11, IOCFG_LT_BASE, 0x00,
		PWRAP_SPI0_MI, PWRAP_SPI0_MO, RES3,
		RES4, RES5, RES6, RES7),
	PIN(145, PWRAP_SPI0_CSN, 0, 12, IOCFG_LT_BASE, 0x00,
		PWRAP_SPI0_CSN, RES2, RES3,
		RES4, RES5, RES6, RES7),
	PIN(146, PWRAP_SPI0_MO, 0, 13, IOCFG_LT_BASE, 0x00,
		PWRAP_SPI0_MO, PWRAP_SPI0_MI, RES3,
		RES4, RES5, RES6, RES7),
	PIN(147, PWRAP_SPI0_CK, 0, 14, IOCFG_LT_BASE, 0x00,
		PWRAP_SPI0_CK, RES2, RES3,
		RES4, RES5, RES6, RES7),
	PIN(148, SRCLKENA0, 0, 15, IOCFG_LT_BASE, 0x00,
		SRCLKENA0, RES2, RES3,
		RES4, RES5, RES6, RES7),
	PIN(149, SRCLKENA1, 0, 16, IOCFG_LT_BASE, 0x00,
		SRCLKENA1, RES2, RES3,
		RES4, RES5, RES6, RES7),
	PIN(150, PERIPHERAL_EN0, 0, 18, IOCFG_LT_BASE, 0x00,
		PWM_A, CMFLASH, CLKM0,
		RES4, RES5, RES6, DBG_MON_B30),
	PIN(151, PERIPHERAL_EN1, 0, 19, IOCFG_LT_BASE, 0x00,
		PWM_B, CMVREF0, CLKM1,
		RES4, RES5, RES6, DBG_MON_B20),
	PIN(152, PERIPHERAL_EN2, 0, 20, IOCFG_LT_BASE, 0x00,
		PWM_C, CMFLASH, CLKM2,
		RES4, RES5, RES6, DBG_MON_B21),
	PIN(153, PERIPHERAL_EN3, 0, 21, IOCFG_LT_BASE, 0x00,
		PWM_A, CMVREF0, CLKM3,
		RES4, RES5, RES6, DBG_MON_B22),
	PIN(154, SCP_VREQ_VAO, 0, 22, IOCFG_LT_BASE, 0x00,
		SCP_VREQ_VAO, DVFSRC_EXT_REQ, RES3,
		RES4, RES5, RES6, DBG_MON_B18),
	PIN(155, ANT_SEL0, 0, 23, IOCFG_LT_BASE, 0x00,
		ANT_SEL0, DVFSRC_EXT_REQ, CMVREF1,
		RES4, RES5, RES6, SCP_JTAG_TDI),
	PIN(156, ANT_SEL1, 0, 24, IOCFG_LT_BASE, 0x00,
		ANT_SEL1, SRCLKENAI0, SCL6,
		KPCOL2, IDDIG, RES6, SCP_JTAG_TCK),
	PIN(157, ANT_SEL2, 0, 25, IOCFG_LT_BASE, 0x00,
		ANT_SEL2, SRCLKENAI1, SDA6,
		KPROW2, USB_DRVVBUS, RES6, SCP_JTAG_TRSTN),
	PIN(158, PERIPHERAL_EN6, 0, 26, IOCFG_LT_BASE, 0x00,
		ANT_SEL3, RES2, RES3,
		RES4, RES5, RES6, RES7),
	PIN(159, PERIPHERAL_EN7, 0, 27, IOCFG_LT_BASE, 0x00,
		ANT_SEL4, RES2, RES3,
		RES4, RES5, RES6, RES7),
	PIN(160, PERIPHERAL_EN8, 0, 28, IOCFG_LT_BASE, 0x00,
		ANT_SEL5, RES2, RES3,
		RES4, RES5, RES6, RES7),
	PIN(161, SPI1_MI, 0, 0, IOCFG_LM_BASE, 0x00,
		SPI1_A_MI, SCP_SPI1_MI, IDDIG,
		ANT_SEL6, KPCOL2, PTA_RXD, DBG_MON_B19),
	PIN(162, SPI1_CSB, 0, 1, IOCFG_LM_BASE, 0x00,
		SPI1_A_CSB, SCP_SPI1_CS, USB_DRVVBUS,
		ANT_SEL5, KPROW2, PTA_TXD, RES7),
	PIN(163, SPI1_MO, 0, 2, IOCFG_LM_BASE, 0x00,
		SPI1_A_MO, SCP_SPI1_MO, SDA1,
		ANT_SEL4, CMMCLK2, DMIC_CLK, RES7),
	PIN(164, SPI1_CLK, 0, 3, IOCFG_LM_BASE, 0x00,
		SPI1_A_CLK, SCP_SPI1_CK, SCL1,
		ANT_SEL3, CMMCLK3, DMIC_DAT, RES7),
	PIN(165, PERIPHERAL_EN4, 0, 4, IOCFG_LM_BASE, 0x00,
		PWM_B, CMMCLK2, SCP_VREQ_VAO,
		RES4, RES5, TDM_MCK_2nd, SCP_JTAG_TDO),
	PIN(166, PERIPHERAL_EN9, 0, 5, IOCFG_LM_BASE, 0x00,
		ANT_SEL6, RES2, RES3,
		RES4, RES5, RES6, RES7),
	PIN(167, RFIC0_BSI_EN, 0, 11, IOCFG_BL_BASE, 0x00,
		RFIC0_BSI_EN, SPM_BSI_EN, RES3,
		RES4, RES5, RES6, RES7),
	PIN(168, RFIC0_BSI_CK, 0, 12, IOCFG_BL_BASE, 0x00,
		RFIC0_BSI_CK, SPM_BSI_CK, RES3,
		RES4, RES5, RES6, RES7),
	PIN(169, PERIPHERAL_EN5, 0, 13, IOCFG_BL_BASE, 0x00,
		PWM_C, CMMCLK3, CMVREF1,
		ANT_SEL7, AGPS_SYNC, TDM_BCK_2nd, SCP_JTAG_TMS),
	PIN(170, I2S1_BCK, 0, 14, IOCFG_BL_BASE, 0x00,
		I2S1_BCK, I2S3_BCK, SCL7,
		I2S5_BCK, EXT_FRAME_SYNC, TDM_LRCK_2nd, ANT_SEL3),
	PIN(171, I2S1_LRCK, 0, 15, IOCFG_BL_BASE, 0x00,
		I2S1_LRCK, I2S3_LRCK, SDA7,
		I2S5_LRCK, URXD1, TDM_DATA0_2nd, ANT_SEL4),
	PIN(172, I2S1_DO, 0, 16, IOCFG_BL_BASE, 0x00,
		I2S1_DO, I2S3_DO, SCL8,
		I2S5_DO, UTXD1, TDM_DATA1_2nd, ANT_SEL5),
	PIN(173, I2S1_MCK, 0, 17, IOCFG_BL_BASE, 0x00,
		I2S1_MCK, I2S3_MCK, SDA8,
		I2S5_MCK, UCTS0, TDM_DATA2_2nd, ANT_SEL6),
	PIN(174, I2S2_DI, 0, 18, IOCFG_BL_BASE, 0x00,
		I2S2_DI, I2S0_DI, DVFSRC_EXT_REQ,
		I2S2_DI2, URTS0, TDM_DATA3_2nd, ANT_SEL7),
	PIN(175, PERIPHERAL_EN12, 0, 19, IOCFG_BL_BASE, 0x00,
		ANT_SEL7, RES2, RES3,
		RES4, RES5, RES6, RES7),
	PIN(176, PERIPHERAL_EN13, 0, 20, IOCFG_BL_BASE, 0x00,
		RES1, RES2, RES3,
		RES4, RES5, RES6, RES7),
	PIN(177, PERIPHERAL_EN14, 0, 10, IOCFG_RM_BASE, 0x00,
		RES1, RES2, RES3,
		RES4, RES5, RES6, RES7),
	PIN(178, PERIPHERAL_EN10, 0, 16, IOCFG_RM_BASE, 0x00,
		RES1, RES2, RES3,
		RES4, RES5, RES6, RES7),
	PIN(179, PERIPHERAL_EN11, 0, 25, IOCFG_RM_BASE, 0x00,
		RES1, RES2, RES3,
		RES4, RES5, RES6, RES7),
};

struct val_regs {
	uint32_t val;
	uint32_t set;
	uint32_t rst;
	uint32_t align;
};

struct gpio_regs {
	struct val_regs dir[6];
	uint8_t rsv00[160];
	struct val_regs dout[6];
	uint8_t rsv01[160];
	struct val_regs din[6];
	uint8_t rsv02[160];
	struct val_regs mode[23];
};

check_member(gpio_regs, mode[22].val, 0x460);

static struct gpio_regs *const mtk_gpio = (void *)(GPIO_BASE);
void gpio_set_i2c_eh_rsel(void);
void gpio_set_spi_driving(unsigned int bus, enum spi_pad_mask pad_select,
			  unsigned int milliamps);

#endif
