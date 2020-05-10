/* SPDX-License-Identifier: GPL-2.0-only */

#ifndef MAINBOARD_GPIO_H
#define MAINBOARD_GPIO_H

#include <soc/gpe.h>
#include <soc/gpio.h>

#ifndef __ACPI__

#define PAD_CFG_NC(pad) PAD_NC(pad, NONE)

/* Early pad configuration in romstage. */
static const struct pad_config early_gpio_table[] = {
	// UART2
		// UART2_RXD
		PAD_CFG_NF(GPP_C20, NONE, DEEP, NF1),
		// UART2_TXD
		PAD_CFG_NF(GPP_C21, NONE, DEEP, NF1),
		// NC
		PAD_CFG_NC(GPP_C22),
		// NC
		PAD_CFG_NC(GPP_C23),
};

/* Pad configuration in ramstage. */
static const struct pad_config gpio_table[] = {
// GPD
	// Power Management
		// PM_BATLOW#
		PAD_CFG_NC(GPD0),
		// AC_PRESENT
		PAD_CFG_NF(GPD1, NATIVE, DEEP, NF1),
		// NC
		PAD_CFG_NC(GPD2),
		// PWR_BTN#
		PAD_CFG_NF(GPD3, UP_20K, DEEP, NF1),
		// SUSB#_PCH
		PAD_CFG_NF(GPD4, NONE, DEEP, NF1),
		// SUSC#_PCH
		PAD_CFG_NF(GPD5, NONE, DEEP, NF1),
		// SLP_A#
		PAD_CFG_NF(GPD6, NONE, DEEP, NF1),

	// GPIO
		// NC
		PAD_CFG_NC(GPD7),

	// Clock Signals
		// SUS_CLK
		PAD_CFG_NF(GPD8, NONE, DEEP, NF1),

	// Power Management
		// GPD9_RTD3
		PAD_CFG_NC(GPD9),
		// NC
		PAD_CFG_NF(GPD10, NONE, DEEP, NF1),
		// NC
		PAD_CFG_NC(GPD11),

// GPP_A
	// LPC
		// SB_KBCRST#
		PAD_CFG_NF(GPP_A0, NONE, DEEP, NF1),
		// LPC_AD0
		PAD_CFG_NF(GPP_A1, NATIVE, DEEP, NF1),
		// LPC_AD1
		PAD_CFG_NF(GPP_A2, NATIVE, DEEP, NF1),
		// LPC_AD2
		PAD_CFG_NF(GPP_A3, NATIVE, DEEP, NF1),
		// LPC_AD3
		PAD_CFG_NF(GPP_A4, NATIVE, DEEP, NF1),
		// LPC_FRAME#
		PAD_CFG_NF(GPP_A5, NONE, DEEP, NF1),
		// SERIRQ with pull up
		PAD_CFG_NF(GPP_A6, NONE, DEEP, NF1),

	// GSPI0
		// TODO - TPM_PIRQ#
		PAD_CFG_NC(GPP_A7),

	// LPC
		// PM_CLKRUN# with pull-up
		PAD_CFG_NF(GPP_A8, NONE, DEEP, NF1),
		// PCLK_KBC
		PAD_CFG_NF(GPP_A9, DN_20K, DEEP, NF1),
		// NC
		PAD_CFG_NF(GPP_A10, DN_20K, DEEP, NF1),

	// GSPI1
		// INTP_OUT
		_PAD_CFG_STRUCT(GPP_A11, 0x80100100, 0x0000),

	// ISH_GP
		// PCH_GPP_A12
		PAD_CFG_NC(GPP_A12),

	// Power Management
		// SUSWARN#
		PAD_CFG_NF(GPP_A13, NONE, DEEP, NF1),

	// LPC
		// NC
		PAD_CFG_NF(GPP_A14, NONE, DEEP, NF1),

	// Power Management
		// SUS_PWR_ACK
		PAD_CFG_NF(GPP_A15, UP_20K, DEEP, NF1),

	// SD
		// NC
		PAD_CFG_NC(GPP_A16),
		// LIGHT_KB_DET#
		PAD_CFG_NC(GPP_A17),

	// ISH_GP
		// NC
		PAD_CFG_NC(GPP_A18),
		// SATA_PWR_EN
		PAD_CFG_GPO(GPP_A19, 1, DEEP),
		// TEST_R
		PAD_CFG_TERM_GPO(GPP_A20, 0, NONE, DEEP),
		// NC
		PAD_CFG_NC(GPP_A21),
		// NC
		PAD_CFG_NC(GPP_A22),
		// NC
		PAD_CFG_NC(GPP_A23),

// GPP_B
	// Power
		// CORE_VID0
		PAD_CFG_NC(GPP_B0),
		// CORE_VID1
		PAD_CFG_NC(GPP_B1),

	// Power Management
		// CNVI_WAKE#
		PAD_CFG_NC(GPP_B2),

	// CPU Misc
		// GPP_B3
		_PAD_CFG_STRUCT(GPP_B3, 0x80100100, 0x0000),
		// NC
		PAD_CFG_NC(GPP_B4),

	// Clock Signals
		// NC
		PAD_CFG_NC(GPP_B5),
		// NC
		PAD_CFG_NC(GPP_B6),
		// WLAN_CLKREQ#
		PAD_CFG_NF(GPP_B7, NONE, DEEP, NF1),
		// LAN_CLKREQ#
		PAD_CFG_NF(GPP_B8, NONE, DEEP, NF1),
		// TBT_CLKREQ#
		PAD_CFG_NF(GPP_B9, NONE, DEEP, NF1),
		// SSD_CLKREQ#
		PAD_CFG_NF(GPP_B10, NONE, DEEP, NF1),

	// Power Management
		// EXT_PWR_GATE#
		PAD_CFG_NC(GPP_B11),
		// SLP_S0#
		PAD_CFG_NF(GPP_B12, NONE, DEEP, NF1),
		// PLT_RST#
		PAD_CFG_NF(GPP_B13, NONE, DEEP, NF1),

	// SPKR
		// PCH_SPKR
		PAD_CFG_NF(GPP_B14, NONE, DEEP, NF1),

	// GSPI0
		// NC
		PAD_CFG_NC(GPP_B15),
		// PCH_GPP_B16
		PAD_CFG_NC(GPP_B16),
		// PCH_GPP_B17
		PAD_CFG_NC(GPP_B17),
		// PCH_GPP_B18 - strap for disabling no reboot mode
		PAD_CFG_NC(GPP_B18),

	// GSPI1
		// NC
		PAD_CFG_NC(GPP_B19),
		// NC
		PAD_CFG_NC(GPP_B20),
		// NC
		PAD_CFG_NC(GPP_B21),
		// PCH_GPP_B22
		PAD_CFG_NC(GPP_B22),

	// SMBUS
		// NC
		PAD_CFG_NC(GPP_B23),

// GPP_C
	// SMBUS
		// SMB_CLK_DDR
		PAD_CFG_NF(GPP_C0, NONE, DEEP, NF1),
		// SMB_DAT_DDR
		PAD_CFG_NF(GPP_C1, NONE, DEEP, NF1),
		// PCH_GPP_C2 with pull-up
		PAD_CFG_NC(GPP_C2),
		// NC
		PAD_CFG_NC(GPP_C3),
		// NC
		PAD_CFG_NC(GPP_C4),
		// NC
		PAD_CFG_NC(GPP_C5),
		// LAN_WAKEUP#
		PAD_CFG_NC(GPP_C6),
		// NC
		PAD_CFG_NC(GPP_C7),

	// UART0
		// NC
		PAD_CFG_NC(GPP_C8),
		// NC
		PAD_CFG_NC(GPP_C9),
		// TBT_FRC_PWR
		PAD_CFG_TERM_GPO(GPP_C10, 0, NONE, PLTRST),
		// NC
		PAD_CFG_NC(GPP_C11),

	// UART1
		// GPP_C12_RTD3
		PAD_CFG_TERM_GPO(GPP_C12, 1, NONE, PLTRST),
		// SSD_PWR_DN#
		PAD_CFG_TERM_GPO(GPP_C13, 1, NONE, PLTRST),
		// TBTA_HRESET
		PAD_CFG_TERM_GPO(GPP_C14, 0, NONE, PLTRST),
		// NC
		PAD_CFG_NC(GPP_C15),

	// I2C
		// T_SDA
		PAD_CFG_NF(GPP_C16, NONE, DEEP, NF1),
		// T_SCL
		PAD_CFG_NF(GPP_C17, NONE, DEEP, NF1),
		// NC
		PAD_CFG_NC(GPP_C18),
		// SWI
		PAD_CFG_NC(GPP_C19),

	// UART2
		// UART2_RXD
		PAD_CFG_NF(GPP_C20, NONE, DEEP, NF1),
		// UART2_TXD
		PAD_CFG_NF(GPP_C21, NONE, DEEP, NF1),
		// NC
		PAD_CFG_NC(GPP_C22),
		// NC
		PAD_CFG_NC(GPP_C23),

// GPP_D
	// SPI1
		// NC
		PAD_CFG_NC(GPP_D0),
		// NC
		PAD_CFG_NC(GPP_D1),
		// NC
		PAD_CFG_NC(GPP_D2),
		// NC
		PAD_CFG_NC(GPP_D3),

	// IMGCLKOUT
		// NC
		PAD_CFG_NC(GPP_D4),

	// I2C
		// NC
		PAD_CFG_NC(GPP_D5),
		// NC
		PAD_CFG_NC(GPP_D6),
		// NC
		PAD_CFG_NC(GPP_D7),
		// SB_BLON
		PAD_CFG_TERM_GPO(GPP_D8, 1, NONE, DEEP),

	// GSPI2
		// SWI#
		_PAD_CFG_STRUCT(GPP_D9, 0x40880100, 0x0000),
		// NC
		PAD_CFG_NC(GPP_D10),
		// BOARD_ID
		PAD_CFG_NC(GPP_D11),
		// PCH_GPP_D12
		PAD_CFG_NC(GPP_D12),

	// UART0
		// GPP_D13_RTD3
		PAD_CFG_TERM_GPO(GPP_D13, 1, NONE, PLTRST),
		// SSD2_PWR_DN#
		PAD_CFG_TERM_GPO(GPP_D14, 1, NONE, PLTRST),
		// NC
		PAD_CFG_NC(GPP_D15),
		// RTD3_3G_PW R_EN
		PAD_CFG_TERM_GPO(GPP_D16, 1, NONE, PWROK),

	// DMIC
		// NC
		PAD_CFG_NC(GPP_D17),
		// NC
		PAD_CFG_NC(GPP_D18),
		// GPPC_DMIC_CLK
		PAD_CFG_NF(GPP_D19, NONE, DEEP, NF1),
		// GPPC_DMIC_DATA
		PAD_CFG_NF(GPP_D20, NONE, DEEP, NF1),

	// SPI1
		// TPM_DET#
		PAD_CFG_NC(GPP_D21),
		// TPM_TCM_Detect
		PAD_CFG_NC(GPP_D22),

	// I2S
		// NC
		PAD_CFG_NC(GPP_D23),

// GPP_E
	// SATA
		// PCH_GPP_E0 with pull-up
		PAD_CFG_NC(GPP_E0),
		// SATAGP1
		PAD_CFG_NF(GPP_E1, UP_20K, DEEP, NF1),
		// SATAGP2
		PAD_CFG_NF(GPP_E2, UP_20K, DEEP, NF1),

	// CPU Misc
		// NC
		PAD_CFG_NC(GPP_E3),

	// DEVSLP
		// NC
		PAD_CFG_NC(GPP_E4),
		// DEVSLP1
		PAD_CFG_NF(GPP_E5, NONE, DEEP, NF1),
		// DEVSLP2
		PAD_CFG_NF(GPP_E6, NONE, DEEP, NF1),

	// CPU Misc
		// NC
		PAD_CFG_NC(GPP_E7),

	// SATA
		// PCH_SATAHDD_LED#
		PAD_CFG_NF(GPP_E8, NONE, DEEP, NF1),

	// USB2
		// GP_BSSB_CLK
		PAD_CFG_NC(GPP_E9),
		// GPP_E10
		PAD_CFG_NC(GPP_E10),
		// GPP_E11
		PAD_CFG_NC(GPP_E11),
		// USB_OC#78
		PAD_CFG_NC(GPP_E12),

	// Display Signals
		// MUX_HPD
		PAD_CFG_NF(GPP_E13, NONE, DEEP, NF1),
		// HDMI_HPD
		PAD_CFG_NF(GPP_E14, NONE, DEEP, NF1),
		// SMI#
		_PAD_CFG_STRUCT(GPP_E15, 0x42840100, 0x0),
		// SCI#
		_PAD_CFG_STRUCT(GPP_E16, 0x80880100, 0x0000),
		// EDP_HPD
		PAD_CFG_NF(GPP_E17, NONE, DEEP, NF1),
		// MDP_CTRLCLK
		PAD_CFG_NF(GPP_E18, NONE, DEEP, NF1),
		// MDP_CTRLDATA
		PAD_CFG_NF(GPP_E19, NONE, DEEP, NF1),
		// HDMI_CTRLCLK
		PAD_CFG_NF(GPP_E20, NONE, DEEP, NF1),
		// HDMI_CTRLDATA
		PAD_CFG_NF(GPP_E21, NONE, DEEP, NF1),
		// NC
		PAD_CFG_NC(GPP_E22),
		// NC
		PAD_CFG_NC(GPP_E23),

// GPP_F
	// CNVI
		// CNVI_GNSS_PA_BLANKING
		PAD_CFG_NF(GPP_F0, NONE, DEEP, NF1),

	// GPIO
		// NC
		PAD_CFG_NC(GPP_F1),
		// NC
		PAD_CFG_NC(GPP_F2),
		// NC
		PAD_CFG_NC(GPP_F3),

	// CNVI
		// CNVI_BRI_DT
		PAD_CFG_NF(GPP_F4, NONE, DEEP, NF1),
		// CNVI_BRI_RSP
		PAD_CFG_NF(GPP_F5, UP_20K, DEEP, NF1),
		// CNVI_RGI_DT
		PAD_CFG_NF(GPP_F6, NONE, DEEP, NF1),
		// CNVI_RGI_RSP
		PAD_CFG_NF(GPP_F7, UP_20K, DEEP, NF1),
		// CNVI_MFUART2_RXD
		PAD_CFG_NF(GPP_F8, NONE, DEEP, NF1),
		// CNVI_MFUART2_TXD
		PAD_CFG_NF(GPP_F9, NONE, DEEP, NF1),

	// GPIO
		// NC
		PAD_CFG_NC(GPP_F10),

	// EMMC
		// NC
		PAD_CFG_NC(GPP_F11),
		// NC
		PAD_CFG_NC(GPP_F12),
		// NC
		PAD_CFG_NC(GPP_F13),
		// NC
		PAD_CFG_NC(GPP_F14),
		// NC
		PAD_CFG_NC(GPP_F15),
		// NC
		PAD_CFG_NC(GPP_F16),
		// NC
		PAD_CFG_NC(GPP_F17),
		// NC
		PAD_CFG_NC(GPP_F18),
		// NC
		PAD_CFG_NC(GPP_F19),
		// NC
		PAD_CFG_NC(GPP_F20),
		// NC
		PAD_CFG_NC(GPP_F21),
		// NC
		PAD_CFG_NC(GPP_F22),

	// A4WP
		// A4WP_PRESENT
		PAD_CFG_GPI(GPP_F23, DN_20K, DEEP),

// GPP_G
	// SD
		// EDP_DET
		PAD_CFG_NC(GPP_G0),
		// NC
		PAD_CFG_NC(GPP_G1),
		// NC
		PAD_CFG_NC(GPP_G2),
		// ASM1543_I_SEL0
		PAD_CFG_NC(GPP_G3),
		// ASM1543_I_SEL1
		PAD_CFG_NC(GPP_G4),
		// BOARD_ID
		PAD_CFG_NC(GPP_G5),
		// NC
		PAD_CFG_NC(GPP_G6),
		// TBT_Detect
		PAD_CFG_NC(GPP_G7),

// GPP_H
	// CNVI
		// NC
		PAD_CFG_NC(GPP_H0),
		// CNVI_RST#
		PAD_CFG_NF(GPP_H1, NONE, DEEP, NF3),
		// CNVI_CLKREQ
		PAD_CFG_NF(GPP_H2, NONE, DEEP, NF3),
		// NC
		PAD_CFG_NC(GPP_H3),

	// I2C
		// SMD_7411
		PAD_CFG_NF(GPP_H4, NONE, DEEP, NF1),
		// SMC_7411
		PAD_CFG_NF(GPP_H5, NONE, DEEP, NF1),
		// NC
		PAD_CFG_NC(GPP_H6),
		// NC
		PAD_CFG_NC(GPP_H7),
		// NC
		PAD_CFG_NC(GPP_H8),
		// NC
		PAD_CFG_NC(GPP_H9),

	// I2C
		// NC
		PAD_CFG_NC(GPP_H10),
		// NC
		PAD_CFG_NC(GPP_H11),

	// PCIE
		// NC
		PAD_CFG_NC(GPP_H12),
		// NC
		PAD_CFG_NC(GPP_H13),
		// G_INT1
		PAD_CFG_NC(GPP_H14),
		// NC
		PAD_CFG_NC(GPP_H15),

	// Display Signals
		// NC
		PAD_CFG_NC(GPP_H16),
		// NC
		PAD_CFG_NC(GPP_H17),

	// CPU Power
		// CPU_C10_GATE#
		PAD_CFG_NF(GPP_H18, NONE, DEEP, NF1),

	// TIMESYNC
		// NC
		PAD_CFG_NC(GPP_H19),

	// IMGCLKOUT
		// NC
		PAD_CFG_NC(GPP_H20),

	// GPIO
		// GPPC_H21
		PAD_CFG_NC(GPP_H21),
		// TBT_RTD3_PWR_EN_R
		PAD_NC(GPP_H22, NONE),
		// NC, WIGIG_PEWAKE
		PAD_CFG_NC(GPP_H23),
};

#endif

#endif
