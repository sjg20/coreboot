/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2019-2020 Intel Corporation.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef _SOC_CHIP_H_
#define _SOC_CHIP_H_

#include <intelblocks/cfg.h>
#include <drivers/i2c/designware/dw_i2c.h>
#include <intelblocks/gpio.h>
#include <intelblocks/gspi.h>
#include <stdint.h>
#include <soc/gpe.h>
#include <soc/gpio.h>
#include <soc/pch.h>
#include <soc/gpio_defs.h>
#include <soc/pci_devs.h>
#include <soc/pmc.h>
#include <soc/serialio.h>
#include <soc/usb.h>

struct soc_intel_tigerlake_config {

	/* Common struct containing soc config data required by common code */
	struct soc_intel_common_config common_soc_config;

	/* Gpio group routed to each dword of the GPE0 block. Values are
	 * of the form PMC_GPP_[A:U] or GPD. */
	uint8_t pmc_gpe0_dw0; /* GPE0_31_0 STS/EN */
	uint8_t pmc_gpe0_dw1; /* GPE0_63_32 STS/EN */
	uint8_t pmc_gpe0_dw2; /* GPE0_95_64 STS/EN */

	/* Generic IO decode ranges */
	uint32_t gen1_dec;
	uint32_t gen2_dec;
	uint32_t gen3_dec;
	uint32_t gen4_dec;

	/* Enable S0iX support */
	int s0ix_enable;
	/* Enable DPTF support */
	int dptf_enable;

	/* Deep SX enable for both AC and DC */
	int deep_s3_enable_ac;
	int deep_s3_enable_dc;
	int deep_s5_enable_ac;
	int deep_s5_enable_dc;

	/* Deep Sx Configuration
	 *  DSX_EN_WAKE_PIN       - Enable WAKE# pin
	 *  DSX_EN_LAN_WAKE_PIN   - Enable LAN_WAKE# pin
	 *  DSX_DIS_AC_PRESENT_PD - Disable pull-down on AC_PRESENT pin */
	uint32_t deep_sx_config;

	/* TCC activation offset */
	uint32_t tcc_offset;

	/* System Agent dynamic frequency support. Only effects ULX/ULT CPUs.
	 * When enabled memory will be training at two different frequencies.
	 * 0:Disabled, 1:FixedPoint0, 2:FixedPoint1, 3:FixedPoint2,
	 * 4:FixedPoint3, 5:Enabled */
	enum {
		SaGv_Disabled,
		SaGv_FixedPoint0,
		SaGv_FixedPoint1,
		SaGv_FixedPoint2,
		SaGv_FixedPoint3,
		SaGv_Enabled,
	} SaGv;

	/* Rank Margin Tool. 1:Enable, 0:Disable */
	uint8_t RMT;

	/* USB related */
	struct usb2_port_config usb2_ports[16];
	struct usb3_port_config usb3_ports[10];
	/* Wake Enable Bitmap for USB2 ports */
	uint16_t usb2_wake_enable_bitmap;
	/* Wake Enable Bitmap for USB3 ports */
	uint16_t usb3_wake_enable_bitmap;

	/* SATA related */
	uint8_t SataEnable;
	uint8_t SataMode;
	uint8_t SataSalpSupport;
	uint8_t SataPortsEnable[8];
	uint8_t SataPortsDevSlp[8];

	/* Audio related */
	uint8_t PchHdaEnable;
	uint8_t PchHdaDspEnable;

	/* Enable/Disable HD Audio Link. Muxed with SSP0/SSP1/SNDW1 */
	uint8_t PchHdaAudioLinkHda;
	uint8_t PchHdaAudioLinkDmic0;
	uint8_t PchHdaAudioLinkDmic1;
	uint8_t PchHdaAudioLinkSsp0;
	uint8_t PchHdaAudioLinkSsp1;
	uint8_t PchHdaAudioLinkSsp2;
	uint8_t PchHdaAudioLinkSndw1;
	uint8_t PchHdaAudioLinkSndw2;
	uint8_t PchHdaAudioLinkSndw3;
	uint8_t PchHdaAudioLinkSndw4;

	/* PCIe Root Ports */
	uint8_t PcieRpEnable[CONFIG_MAX_ROOT_PORTS];
	/* PCIe output clocks type to Pcie devices.
	 * 0-23: PCH rootport, 0x70: LAN, 0x80: unspecified but in use,
	 * 0xFF: not used */
	uint8_t PcieClkSrcUsage[CONFIG_MAX_PCIE_CLOCKS];
	/* PCIe ClkReq-to-ClkSrc mapping, number of clkreq signal assigned to
	 * clksrc. */
	uint8_t PcieClkSrcClkReq[CONFIG_MAX_PCIE_CLOCKS];

	/* SMBus */
	uint8_t SmbusEnable;

	/* eMMC and SD */
	uint8_t ScsEmmcHs400Enabled;

	/* Enable if SD Card Power Enable Signal is Active High */
	uint8_t SdCardPowerEnableActiveHigh;

	/* Integrated Sensor */
	uint8_t PchIshEnable;

	/* Heci related */
	uint8_t Heci3Enabled;

	/* Gfx related */
	uint8_t IgdDvmt50PreAlloc;
	uint8_t InternalGfx;
	uint8_t SkipExtGfxScan;

	uint32_t GraphicsConfigPtr;
	uint8_t Device4Enable;

	/* HeciEnabled decides the state of Heci1 at end of boot
	 * Setting to 0 (default) disables Heci1 and hides the device from OS */
	uint8_t HeciEnabled;
	/* PL2 Override value in Watts */
	uint32_t tdp_pl2_override;
	/* Intel Speed Shift Technology */
	uint8_t speed_shift_enable;

	/* Enable/Disable EIST. 1b:Enabled, 0b:Disabled */
	uint8_t eist_enable;

	/* Enable C6 DRAM */
	uint8_t enable_c6dram;
	/*
	 * PRMRR size setting with below options
	 * Disable: 0x0
	 * 32MB: 0x2000000
	 * 64MB: 0x4000000
	 * 128 MB: 0x8000000
	 * 256 MB: 0x10000000
	 * 512 MB: 0x20000000
	 */
	uint32_t PrmrrSize;
	uint8_t PmTimerDisabled;
	/* Desired platform debug type. */
	enum {
		DebugConsent_Disabled,
		DebugConsent_DCI_DBC,
		DebugConsent_DCI,
		DebugConsent_USB3_DBC,
		DebugConsent_XDP, /* XDP/Mipi60 */
		DebugConsent_USB2_DBC,
		DebugConsent_2WIRE_DCI,
		DebugConsent_Manual,
	} DebugConsent;
	/*
	 * SerialIO device mode selection:
	 * PchSerialIoDisabled,
	 * PchSerialIoPci,
	 * PchSerialIoHidden,
	 * PchSerialIoLegacyUart,
	 * PchSerialIoSkipInit
	 */
	uint8_t SerialIoI2cMode[CONFIG_SOC_INTEL_I2C_DEV_MAX];
	uint8_t SerialIoGSpiMode[CONFIG_SOC_INTEL_COMMON_BLOCK_GSPI_MAX];
	uint8_t SerialIoUartMode[CONFIG_SOC_INTEL_UART_DEV_MAX];
	/*
	 * GSPIn Default Chip Select Mode:
	 * 0:Hardware Mode,
	 * 1:Software Mode
	 */
	uint8_t SerialIoGSpiCsMode[CONFIG_SOC_INTEL_COMMON_BLOCK_GSPI_MAX];
	/*
	 * GSPIn Default Chip Select State:
	 * 0: Low,
	 * 1: High
	 */
	uint8_t SerialIoGSpiCsState[CONFIG_SOC_INTEL_COMMON_BLOCK_GSPI_MAX];

	/* GPIO SD card detect pin */
	unsigned int sdcard_cd_gpio;

	/* Enable Pch iSCLK */
	uint8_t pch_isclk;

	/* CNVi BT Audio Offload: Enable/Disable BT Audio Offload. */
	enum {
		FORCE_DISABLE,
		FORCE_ENABLE,
	} CnviBtAudioOffload;

	/* Tcss */
	uint8_t TcssXhciEn;
	uint8_t TcssXdciEn;

	/*
	 * Override GPIO PM configuration:
	 * 0: Use FSP default GPIO PM program,
	 * 1: coreboot to override GPIO PM program
	 */
	uint8_t gpio_override_pm;

	/*
	 * GPIO PM configuration: 0 to disable, 1 to enable power gating
	 * Bit 6-7: Reserved
	 * Bit 5: MISCCFG_GPSIDEDPCGEN
	 * Bit 4: MISCCFG_GPRCOMPCDLCGEN
	 * Bit 3: MISCCFG_GPRTCDLCGEN
	 * Bit 2: MISCCFG_GSXLCGEN
	 * Bit 1: MISCCFG_GPDPCGEN
	 * Bit 0: MISCCFG_GPDLCGEN
	 */
	uint8_t gpio_pm[TOTAL_GPIO_COMM];

	/* DP config */
	/*
	 * Port config
	 * 0:Disabled, 1:eDP, 2:MIPI DSI
	 */
	uint8_t DdiPortAConfig;
	uint8_t DdiPortBConfig;

	/* Enable(1)/Disable(0) HPD */
	uint8_t DdiPortAHpd;
	uint8_t DdiPortBHpd;
	uint8_t DdiPortCHpd;
	uint8_t DdiPort1Hpd;
	uint8_t DdiPort2Hpd;
	uint8_t DdiPort3Hpd;
	uint8_t DdiPort4Hpd;

	/* Enable(1)/Disable(0) DDC */
	uint8_t DdiPortADdc;
	uint8_t DdiPortBDdc;
	uint8_t DdiPortCDdc;
	uint8_t DdiPort1Ddc;
	uint8_t DdiPort2Ddc;
	uint8_t DdiPort3Ddc;
	uint8_t DdiPort4Ddc;
};

typedef struct soc_intel_tigerlake_config config_t;

#endif
