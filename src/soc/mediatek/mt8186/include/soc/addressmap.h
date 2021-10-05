/* SPDX-License-Identifier: GPL-2.0-only */

#ifndef __SOC_MEDIATEK_MT8186_INCLUDE_SOC_ADDRESSMAP_H__
#define __SOC_MEDIATEK_MT8186_INCLUDE_SOC_ADDRESSMAP_H__

enum {
	MCUSYS_BASE	= 0x0C530000,
	IO_PHYS		= 0x10000000,
};

enum {
	MCUCFG_BASE		= MCUSYS_BASE + 0x00008000,
};

enum {
	CKSYS_BASE			= IO_PHYS + 0x00000000,
	INFRACFG_AO_BASE		= IO_PHYS + 0x00001000,
	IOCFG_LT_BASE			= IO_PHYS + 0x00002000,
	IOCFG_LM_BASE			= IO_PHYS + 0x00002200,
	IOCFG_LB_BASE			= IO_PHYS + 0x00002400,
	IOCFG_BL_BASE			= IO_PHYS + 0x00002600,
	IOCFG_RB_BASE			= IO_PHYS + 0x00002A00,
	IOCFG_RT_BASE			= IO_PHYS + 0x00002C00,
	GPIO_BASE			= IO_PHYS + 0x00005000,
	SPM_BASE			= IO_PHYS + 0x00006000,
	RGU_BASE			= IO_PHYS + 0x00007000,
	GPT_BASE			= IO_PHYS + 0x00008000,
	EINT_BASE			= IO_PHYS + 0x0000B000,
	APMIXED_BASE			= IO_PHYS + 0x0000C000,
	PWRAP_BASE			= IO_PHYS + 0x0000D000,
	DEVAPC_AO_INFRA_PERI_BASE	= IO_PHYS + 0x0000E000,
	DEVAPC_AO_MM_BASE		= IO_PHYS + 0x0000F000,
	SYSTIMER_BASE			= IO_PHYS + 0x00017000,
	I2C0_DMA_BASE			= IO_PHYS + 0x00200100,
	I2C1_DMA_BASE			= IO_PHYS + 0x00200200,
	I2C2_DMA_BASE			= IO_PHYS + 0x00200300,
	I2C3_DMA_BASE			= IO_PHYS + 0x00200480,
	I2C4_DMA_BASE			= IO_PHYS + 0x00200580,
	I2C5_DMA_BASE			= IO_PHYS + 0x00200700,
	I2C6_DMA_BASE			= IO_PHYS + 0x00200800,
	I2C7_DMA_BASE			= IO_PHYS + 0x00200900,
	I2C8_DMA_BASE			= IO_PHYS + 0x00200A80,
	I2C9_DMA_BASE			= IO_PHYS + 0x00200C00,
	DEVAPC_BASE			= IO_PHYS + 0x00207000,
	EMI0_BASE			= IO_PHYS + 0x00219000,
	EMI0_MPU_BASE			= IO_PHYS + 0x0021B000,
	DRAMC_CHA_AO_BASE		= IO_PHYS + 0x00220000,
	SFLASH_REG_BASE			= IO_PHYS + 0x01000000,
	AUXADC_BASE			= IO_PHYS + 0x01001000,
	UART0_BASE			= IO_PHYS + 0x01002000,
	I2C7_BASE			= IO_PHYS + 0x01004000,
	I2C8_BASE			= IO_PHYS + 0x01005000,
	I2C0_BASE			= IO_PHYS + 0x01007000,
	I2C1_BASE			= IO_PHYS + 0x01008000,
	I2C2_BASE			= IO_PHYS + 0x01009000,
	SPI0_BASE			= IO_PHYS + 0x0100A000,
	I2C6_BASE			= IO_PHYS + 0x0100D000,
	I2C3_BASE			= IO_PHYS + 0x0100F000,
	SPI1_BASE			= IO_PHYS + 0x01010000,
	I2C4_BASE			= IO_PHYS + 0x01011000,
	SPI2_BASE			= IO_PHYS + 0x01012000,
	SPI3_BASE			= IO_PHYS + 0x01013000,
	SPI4_BASE			= IO_PHYS + 0x01014000,
	SPI5_BASE			= IO_PHYS + 0x01015000,
	I2C5_BASE			= IO_PHYS + 0x01016000,
	I2C9_BASE			= IO_PHYS + 0x01019000,
	SSUSB_IPPC_BASE			= IO_PHYS + 0x01203E00,
	MSDC0_BASE			= IO_PHYS + 0x01230000,
	SSUSB_SIF_BASE			= IO_PHYS + 0x01CA0000,
	EFUSEC_BASE			= IO_PHYS + 0x01CB0000,
	MIPITX_BASE			= IO_PHYS + 0x01CC0000,
	MSDC0_TOP_BASE			= IO_PHYS + 0x01CD0000,
	SMI_BASE			= IO_PHYS + 0x04002000,
	SMI_LARB0			= IO_PHYS + 0x04003000,
	DSI0_BASE			= IO_PHYS + 0x04013000,
};
#endif
