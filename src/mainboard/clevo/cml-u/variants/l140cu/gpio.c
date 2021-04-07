/* SPDX-License-Identifier: GPL-2.0-only */

#include <soc/gpe.h>
#include <soc/gpio.h>
#include <variant/gpio.h>

/* Name format: <pad name> / <net/pin name in schematics> */
static const struct pad_config gpio_table[] = {
	/* ------- GPIO Group GPD ------- */
	PAD_NC(GPD0, NONE),
	PAD_CFG_NF(GPD1, NATIVE, DEEP, NF1),		/* ACPRESENT / AC_PRESENT */
	PAD_NC(GPD2, UP_20K),
	PAD_CFG_NF(GPD3, UP_20K, DEEP, NF1),		/* PWRBTN# / PWR_BTN# */
	PAD_CFG_NF(GPD4, NONE, DEEP, NF1),		/* SLP_S3# / SUSB#_PCH */
	PAD_CFG_NF(GPD5, NONE, DEEP, NF1),		/* SLP_S4# / SUSC#_PCH */
	PAD_NC(GPD6, UP_20K),
	PAD_NC(GPD7, NONE),
	PAD_CFG_NF(GPD8, NONE, DEEP, NF1),		/* SUSCLK / SUS_CLK */
	PAD_NC(GPD9, UP_20K),
	PAD_NC(GPD10, UP_20K),
	PAD_NC(GPD11, UP_20K),

	/* ------- GPIO Group GPP_A ------- */
	PAD_CFG_NF(GPP_A0, NONE, DEEP, NF1),		/* RCIN# / SB_KBCRST# */
	PAD_CFG_NF(GPP_A1, NATIVE, DEEP, NF1),		/* LAD0 / LPC_AD0 */
	PAD_CFG_NF(GPP_A2, NATIVE, DEEP, NF1),		/* LAD1 / LPC_AD1 */
	PAD_CFG_NF(GPP_A3, NATIVE, DEEP, NF1),		/* LAD2 / LPC_AD2 */
	PAD_CFG_NF(GPP_A4, NATIVE, DEEP, NF1),		/* LAD3 / LPC_AD3 */
	PAD_CFG_NF(GPP_A5, NONE, DEEP, NF1),		/* LFRAME# / LPC_FRAME# */
	PAD_CFG_NF(GPP_A6, NONE, DEEP, NF1),		/* SERIRQ */
	PAD_CFG_NF(GPP_A7, NONE, DEEP, NF1),		/* PIRQA# / TPM_PIRQ# */
	PAD_CFG_NF(GPP_A8, NONE, DEEP, NF1),		/* CLKRUN# / PM_CLKRUN#
							   Note: R209 is populated despite being
							   marked no-stuff in schematic
							 */
	PAD_CFG_NF(GPP_A9, DN_20K, DEEP, NF1),		/* CLKOUT_LPC0 / PCLK_KBC */
	PAD_NC(GPP_A10, UP_20K),
	PAD_NC(GPP_A11, NONE),				/* INTP_OUT (unknown and unused) */
	PAD_NC(GPP_A12, UP_20K),
	PAD_NC(GPP_A13, UP_20K),			/* SUSWARN#
							   (unused due to missing DeepSx support)
							 */
	PAD_NC(GPP_A14, UP_20K),
	PAD_NC(GPP_A15, UP_20K),
	PAD_NC(GPP_A16, UP_20K),
	PAD_NC(GPP_A17, NONE),				/* LEDKB_DET#
							   (unused in cb; all devices of that
							   model have KB LED)
							 */
	PAD_NC(GPP_A18, UP_20K),
	PAD_NC(GPP_A19, UP_20K),
	PAD_CFG_GPO(GPP_A20, 0, DEEP),			/* GPP_A20 / TEST_R */
	PAD_NC(GPP_A21, UP_20K),
	PAD_NC(GPP_A22, UP_20K),
	PAD_NC(GPP_A23, UP_20K),

	/* ------- GPIO Group GPP_B ------- */
	PAD_NC(GPP_B0, UP_20K),
	PAD_NC(GPP_B1, UP_20K),
	PAD_NC(GPP_B2, UP_20K),				/* CNVI_WAKE#
							   (UART_WAKE# in M.2 spec; unused)
							 */
	PAD_CFG_GPI_APIC_LOW(GPP_B3, NONE, PLTRST),	/* GPP_B3 (touchpad interrupt) */
	PAD_NC(GPP_B4, UP_20K),
	PAD_NC(GPP_B5, UP_20K),
	PAD_NC(GPP_B6, UP_20K),
	PAD_CFG_NF(GPP_B7, NONE, DEEP, NF1),		/* SRCCLKREQ2# / WLAN_CLKREQ# */
	PAD_CFG_NF(GPP_B8, NONE, DEEP, NF1),		/* SRCCLKREQ3# / CARD_CLKREQ# */
	PAD_CFG_NF(GPP_B9, NONE, DEEP, NF1),		/* SRCCLKREQ4# / SSD2_CLKREQ# */
	PAD_CFG_NF(GPP_B10, NONE, DEEP, NF1),		/* SRCCLKREQ5# / SSD1_CLKREQ# */
	PAD_NC(GPP_B11, NONE),
	PAD_CFG_NF(GPP_B12, NONE, DEEP, NF1),		/* SLP_S0# */
	PAD_CFG_NF(GPP_B13, NONE, DEEP, NF1),		/* PLT_RST# */
	PAD_CFG_NF(GPP_B14, NONE, DEEP, NF1),		/* SPKR / PCH_SPKR */
	PAD_NC(GPP_B15, UP_20K),
	PAD_NC(GPP_B16, UP_20K),
	PAD_NC(GPP_B17, NONE),
	PAD_NC(GPP_B18, UP_20K),
	PAD_NC(GPP_B19, UP_20K),
	PAD_NC(GPP_B20, UP_20K),
	PAD_NC(GPP_B21, UP_20K),
	PAD_NC(GPP_B22, UP_20K),
	PAD_NC(GPP_B23, UP_20K),

	/* ------- GPIO Group GPP_C ------- */
	PAD_CFG_NF(GPP_C0, NONE, DEEP, NF1),		/* SMBCLK / SMB_CLK_DDR */
	PAD_CFG_NF(GPP_C1, NONE, DEEP, NF1),		/* SMBDATA / SMB_DAT_DDR */
	PAD_NC(GPP_C2, UP_20K),
	PAD_NC(GPP_C3, UP_20K),
	PAD_NC(GPP_C4, UP_20K),
	PAD_NC(GPP_C5, UP_20K),
	PAD_NC(GPP_C6, UP_20K),
	PAD_NC(GPP_C7, UP_20K),
	PAD_NC(GPP_C8, UP_20K),
	PAD_NC(GPP_C9, UP_20K),
	PAD_NC(GPP_C10, UP_20K),
	PAD_NC(GPP_C11, UP_20K),
	PAD_NC(GPP_C12, UP_20K),
	PAD_CFG_GPO(GPP_C13, 1, PLTRST),		/* GPP_C13 / SSD1_PWR_DN# */
	PAD_NC(GPP_C14, UP_20K),
	PAD_NC(GPP_C15, UP_20K),
	PAD_CFG_NF(GPP_C16, NONE, DEEP, NF1),		/* I2C0_SDA / T_SDA */
	PAD_CFG_NF(GPP_C17, NONE, DEEP, NF1),		/* I2C0_SCL / T_SCL */
	PAD_NC(GPP_C18, UP_20K),
	PAD_NC(GPP_C19, UP_20K),
	PAD_CFG_NF(GPP_C20, NONE, DEEP, NF1),		/* UART2_RXD */
	PAD_CFG_NF(GPP_C21, NONE, DEEP, NF1),		/* UART2_TXD */
	PAD_NC(GPP_C22, UP_20K),
	PAD_NC(GPP_C23, UP_20K),

	/* ------- GPIO Group GPP_D ------- */
	PAD_NC(GPP_D0, UP_20K),
	PAD_NC(GPP_D1, UP_20K),
	PAD_NC(GPP_D2, UP_20K),
	PAD_NC(GPP_D3, UP_20K),
	PAD_NC(GPP_D4, UP_20K),
	PAD_NC(GPP_D5, UP_20K),
	PAD_NC(GPP_D6, UP_20K),
	PAD_NC(GPP_D7, UP_20K),
	PAD_CFG_GPO(GPP_D8, 1, DEEP),			/* SB_BLON */
	PAD_CFG_GPI_SCI_LOW(GPP_D9, NONE, DEEP, LEVEL),	/* EC SWI# */
	PAD_NC(GPP_D10, NONE),				/* DDR_TYPE_D10
							   (unused; there is only one on-board
							   ram type/model)
							 */
	PAD_NC(GPP_D11, NONE),				/* BOARD_ID
							   (unused in cb; we already know the
							   device model)
							 */
	PAD_NC(GPP_D12, UP_20K),
	PAD_NC(GPP_D13, UP_20K),
	PAD_CFG_GPO(GPP_D14, 1, PLTRST),		/* SSD2_PWR_DN# */
	PAD_NC(GPP_D15, UP_20K),
	PAD_NC(GPP_D16, UP_20K),
	PAD_NC(GPP_D17, UP_20K),
	PAD_NC(GPP_D18, UP_20K),
	PAD_NC(GPP_D19, UP_20K),
	PAD_NC(GPP_D20, UP_20K),
	PAD_NC(GPP_D21, NONE),				/* TPM_DET#
							   (currently unused in cb; there seem
							   to be no devices without TPM)
							 */
	PAD_NC(GPP_D22, NONE),				/* DDR_TYPE_D22
							   (unused in cb; there is only one
							   on-board ram type)
							 */
	PAD_NC(GPP_D23, UP_20K),

	/* ------- GPIO Group GPP_E ------- */
	PAD_NC(GPP_E0, UP_20K),
	PAD_CFG_NF(GPP_E1, NONE, DEEP, NF1),		/* SATAXPCIE1 / SATAGP1 */
	PAD_CFG_NF(GPP_E2, NONE, DEEP, NF1),		/* SATAXPCIE2 / SATAGP2 */
	PAD_NC(GPP_E3, UP_20K),
	PAD_NC(GPP_E4, UP_20K),
	PAD_CFG_NF(GPP_E5, NONE, DEEP, NF1),		/* DEVSLP1 */
	PAD_CFG_NF(GPP_E6, NONE, DEEP, NF1),		/* DEVSLP2 */
	PAD_NC(GPP_E7, UP_20K),
	PAD_NC(GPP_E8, NONE),
	PAD_NC(GPP_E9, NONE),
	PAD_NC(GPP_E10, NONE),
	PAD_NC(GPP_E11, NONE),
	PAD_NC(GPP_E12, NONE),
	PAD_CFG_NF(GPP_E13, NONE, DEEP, NF1),		/* DDPB_HPD0 / MUX_HPD */
	PAD_CFG_NF(GPP_E14, NONE, DEEP, NF1),		/* DDPC_HPD1 / HDMI_HPD */
	PAD_CFG_GPI_SMI_LOW(GPP_E15, NONE, DEEP, EDGE_SINGLE),	/* EC SMI# */
	PAD_CFG_GPI_SCI_LOW(GPP_E16, NONE, PLTRST, LEVEL),	/* EC SCI# */
	PAD_CFG_NF(GPP_E17, NONE, DEEP, NF1),		/* EDP_HPD */
	PAD_NC(GPP_E18, UP_20K),
	PAD_NC(GPP_E19, NONE),
	PAD_CFG_NF(GPP_E20, NONE, DEEP, NF1),		/* DPPC_CTRLCLK / HDMI_CTRLCLK */
	PAD_CFG_NF(GPP_E21, NONE, DEEP, NF1),		/* DPPC_CTRLDATA / HDMI_CTRLDATA */
	PAD_NC(GPP_E22, UP_20K),
	PAD_NC(GPP_E23, UP_20K),

	/* ------- GPIO Group GPP_F ------- */
	PAD_NC(GPP_F0, UP_20K),
	PAD_NC(GPP_F1, UP_20K),
	PAD_NC(GPP_F2, UP_20K),
	PAD_NC(GPP_F3, UP_20K),
	PAD_CFG_NF(GPP_F4, NONE, DEEP, NF1),		/* CNV_BRI_DT / CNVI_BRI_DT */
	PAD_CFG_NF(GPP_F5, UP_20K, DEEP, NF1),		/* CNV_BRI_RSP / CNVI_BRI_RSP */
	PAD_CFG_NF(GPP_F6, NONE, DEEP, NF1),		/* CNV_RGI_DT / CNVI_RGI_DT */
	PAD_CFG_NF(GPP_F7, UP_20K, DEEP, NF1),		/* CNV_RGI_RSP / CNVI_RGI_RSP */
	PAD_NC(GPP_F8, UP_20K),
	PAD_NC(GPP_F9, UP_20K),
	PAD_NC(GPP_F10, UP_20K),
	PAD_NC(GPP_F11, UP_20K),
	PAD_NC(GPP_F12, UP_20K),
	PAD_NC(GPP_F13, UP_20K),
	PAD_NC(GPP_F14, UP_20K),
	PAD_NC(GPP_F15, UP_20K),
	PAD_NC(GPP_F16, UP_20K),
	PAD_NC(GPP_F17, UP_20K),
	PAD_NC(GPP_F18, UP_20K),
	PAD_NC(GPP_F19, UP_20K),
	PAD_NC(GPP_F20, UP_20K),
	PAD_NC(GPP_F21, UP_20K),
	PAD_NC(GPP_F22, UP_20K),
	PAD_NC(GPP_F23, NONE),

	/* ------- GPIO Group GPP_G ------- */
	PAD_NC(GPP_G0, UP_20K),
	PAD_NC(GPP_G1, UP_20K),
	PAD_NC(GPP_G2, UP_20K),
	PAD_NC(GPP_G3, UP_20K),
	PAD_NC(GPP_G4, UP_20K),
	PAD_NC(GPP_G5, UP_20K),
	PAD_NC(GPP_G6, UP_20K),
	PAD_NC(GPP_G7, UP_20K),

	/* ------- GPIO Group GPP_H ------- */
	PAD_NC(GPP_H0, UP_20K),
	PAD_CFG_NF(GPP_H1, NONE, DEEP, NF3),		/* CNV_RF_RESET# / CNVI_RST# */
	PAD_CFG_NF(GPP_H2, DN_20K, DEEP, NF3),		/* MODEM_CLKREQ / CNVI_CLKREQ */
	PAD_NC(GPP_H3, UP_20K),
	PAD_CFG_NF(GPP_H4, NONE, DEEP, NF1),		/* I2C2_SDA / SMD_7411 */
	PAD_CFG_NF(GPP_H5, NONE, DEEP, NF1),		/* I2C2_SCL / SMC_7411 */
	PAD_NC(GPP_H6, UP_20K),
	PAD_NC(GPP_H7, UP_20K),
	PAD_NC(GPP_H8, UP_20K),
	PAD_NC(GPP_H9, UP_20K),
	PAD_NC(GPP_H10, UP_20K),
	PAD_NC(GPP_H11, UP_20K),
	PAD_NC(GPP_H12, UP_20K),
	PAD_NC(GPP_H13, UP_20K),
	PAD_NC(GPP_H14, UP_20K),
	PAD_NC(GPP_H15, UP_20K),
	PAD_NC(GPP_H16, UP_20K),
	PAD_NC(GPP_H17, UP_20K),
	PAD_CFG_NF(GPP_H18, NONE, DEEP, NF1),		/* CPU_C10_GATE# */
	PAD_NC(GPP_H19, UP_20K),
	PAD_NC(GPP_H20, UP_20K),
	PAD_NC(GPP_H21, NONE),
	PAD_NC(GPP_H22, UP_20K),
	PAD_NC(GPP_H23, UP_20K),
};

void variant_configure_gpios(void)
{
	gpio_configure_pads(gpio_table, ARRAY_SIZE(gpio_table));
}
