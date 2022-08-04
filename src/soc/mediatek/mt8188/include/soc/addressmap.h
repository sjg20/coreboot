/* SPDX-License-Identifier: GPL-2.0-only OR MIT */

#ifndef __SOC_MEDIATEK_MT8188_INCLUDE_SOC_ADDRESSMAP_H__
#define __SOC_MEDIATEK_MT8188_INCLUDE_SOC_ADDRESSMAP_H__

/*
 * This file is created based on MT8188 Application Processor Registers
 */

enum {
	MCUSYS_BASE		= 0x0C530000,
	MCUPM_SRAM_BASE		= 0x0C540000,
	MCUPM_CFG_BASE		= 0x0C560000,
	BUS_TRACE_MONITOR_BASE  = 0x0D040000,
	IO_PHYS			= 0x10000000,
	MCUCFG_BASE		= MCUSYS_BASE + 0x00008000,
};

enum {
	CKSYS_BASE		= IO_PHYS + 0x00000000,
	INFRACFG_AO_BASE	= IO_PHYS + 0x00001000,
	GPIO_BASE		= IO_PHYS + 0x00005000,
	SPM_BASE		= IO_PHYS + 0x00006000,
	RGU_BASE		= IO_PHYS + 0x00007000,
	GPT_BASE		= IO_PHYS + 0x00008000,
	EINT_BASE		= IO_PHYS + 0x0000B000,
	APMIXED_BASE		= IO_PHYS + 0x0000C000,
	SYSTIMER_BASE		= IO_PHYS + 0x00017000,
	INFRACFG_AO_BCRM_BASE	= IO_PHYS + 0x00022000,
	PMIF_SPI_BASE		= IO_PHYS + 0x00024000,
	PMICSPI_MST_BASE	= IO_PHYS + 0x00025000,
	PMIF_SPMI_BASE		= IO_PHYS + 0x00027000,
	SPMI_MST_BASE		= IO_PHYS + 0x00029000,
	DBG_TRACKER_BASE	= IO_PHYS + 0x00208000,
	PERI_TRACKER_BASE	= IO_PHYS + 0x00218000,
	EMI0_BASE		= IO_PHYS + 0x00219000,
	EMI1_BASE		= IO_PHYS + 0x0021D000,
	I2C0_DMA_BASE		= IO_PHYS + 0x00220080,
	I2C1_DMA_BASE		= IO_PHYS + 0x00220100,
	I2C2_DMA_BASE		= IO_PHYS + 0x00220180,
	I2C3_DMA_BASE		= IO_PHYS + 0x00220280,
	I2C4_DMA_BASE		= IO_PHYS + 0x00220380,
	I2C5_DMA_BASE		= IO_PHYS + 0x00220480,
	I2C6_DMA_BASE		= IO_PHYS + 0x00220600,
	SCP_ADSP_CFG_BASE	= IO_PHYS + 0x00720000,
	DRAMC_CHA_AO_BASE	= IO_PHYS + 0x00230000,
	INFRA_TRACKER_BASE	= IO_PHYS + 0x00314000,
	SSPM_SRAM_BASE          = IO_PHYS + 0x00400000,
	SSPM_CFG_BASE		= IO_PHYS + 0x00440000,
	DPM_PM_SRAM_BASE	= IO_PHYS + 0x00900000,
	DPM_DM_SRAM_BASE	= IO_PHYS + 0x00920000,
	DPM_CFG_BASE		= IO_PHYS + 0x00940000,
	DPM_PM_SRAM_BASE2	= IO_PHYS + 0x00A00000,
	DPM_DM_SRAM_BASE2	= IO_PHYS + 0x00A20000,
	DPM_CFG_BASE2		= IO_PHYS + 0x00A40000,
	UART0_BASE		= IO_PHYS + 0x01001100,
	UART1_BASE		= IO_PHYS + 0x01001200,
	UART2_BASE		= IO_PHYS + 0x01001300,
	UART3_BASE		= IO_PHYS + 0x01001400,
	AUXADC_BASE		= IO_PHYS + 0x01002000,
	PERICFG_AO_BASE		= IO_PHYS + 0x01003000,
	SPI0_BASE		= IO_PHYS + 0x0100A000,
	SPI1_BASE		= IO_PHYS + 0x01010000,
	SPI2_BASE		= IO_PHYS + 0x01012000,
	SPI3_BASE		= IO_PHYS + 0x01013000,
	SPI4_BASE		= IO_PHYS + 0x01018000,
	SPI5_BASE		= IO_PHYS + 0x01019000,
	SSUSB_IPPC_BASE		= IO_PHYS + 0x01203E00,
	MSDC0_BASE		= IO_PHYS + 0x01230000,
	MSDC1_BASE		= IO_PHYS + 0x01240000,
	I2C0_BASE		= IO_PHYS + 0x01280000,
	I2C2_BASE		= IO_PHYS + 0x01281000,
	I2C3_BASE		= IO_PHYS + 0x01282000,
	SFLASH_REG_BASE		= IO_PHYS + 0x0132C000,
	IOCFG_RM_BASE		= IO_PHYS + 0x01C00000,
	I2C1_BASE		= IO_PHYS + 0x01E00000,
	I2C4_BASE		= IO_PHYS + 0x01E01000,
	IOCFG_LT_BASE		= IO_PHYS + 0x01E10000,
	IOCFG_LM_BASE		= IO_PHYS + 0x01E20000,
	SSUSB_SIF_BASE		= IO_PHYS + 0x01E40300,
	IOCFG_RT_BASE		= IO_PHYS + 0x01EA0000,
	MSDC1_TOP_BASE		= IO_PHYS + 0x01EB0000,
	I2C5_BASE		= IO_PHYS + 0x01EC0000,
	I2C6_BASE		= IO_PHYS + 0x01EC1000,
	EFUSE_BASE		= IO_PHYS + 0x01F20000,
	MSDC0_TOP_BASE		= IO_PHYS + 0x01F50000,
};
#endif
