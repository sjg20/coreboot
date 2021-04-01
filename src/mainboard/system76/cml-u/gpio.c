/* SPDX-License-Identifier: GPL-2.0-only */

#include <mainboard/gpio.h>
#include <soc/gpe.h>
#include <soc/gpio.h>

static const struct pad_config gpio_table[] = {
	/* ------- GPIO Group GPD ------- */
	PAD_NC(GPD0, NONE), // PM_BATLOW#
	PAD_CFG_NF(GPD1, NATIVE, DEEP, NF1), // AC_PRESENT
	PAD_NC(GPD2, NONE),
	PAD_CFG_NF(GPD3, UP_20K, DEEP, NF1), // PWR_BTN#
	PAD_CFG_NF(GPD4, NONE, DEEP, NF1), // SUSB#_PCH
	PAD_CFG_NF(GPD5, NONE, DEEP, NF1), // SUSC#_PCH
	PAD_NC(GPD6, NONE),
	PAD_CFG_GPI(GPD7, NONE, DEEP), // 100k pull up
	PAD_CFG_NF(GPD8, NONE, DEEP, NF1), // SUS_CLK
	PAD_NC(GPD9, NONE), // GPD9_RTD3
	PAD_NC(GPD10, NONE),
	PAD_NC(GPD11, NONE),

	/* ------- GPIO Group A ------- */
	PAD_CFG_NF(GPP_A0, NONE, DEEP, NF1), // SB_KBCRST#
	PAD_CFG_NF(GPP_A1, NATIVE, DEEP, NF1), // LPC_AD0
	PAD_CFG_NF(GPP_A2, NATIVE, DEEP, NF1), // LPC_AD1
	PAD_CFG_NF(GPP_A3, NATIVE, DEEP, NF1), // LPC_AD2
	PAD_CFG_NF(GPP_A4, NATIVE, DEEP, NF1), // LPC_AD3
	PAD_CFG_NF(GPP_A5, NONE, DEEP, NF1), // LPC_FRAME#
	PAD_CFG_NF(GPP_A6, NONE, DEEP, NF1), // SERIRQ with 10k pull up
	PAD_CFG_GPI(GPP_A7, NONE, DEEP), // TPM_PIRQ#
	PAD_CFG_NF(GPP_A8, NONE, DEEP, NF1), // PM_CLKRUN# with 8.2k pull-up
	PAD_CFG_NF(GPP_A9, DN_20K, DEEP, NF1), // PCLK_KBC
	PAD_NC(GPP_A10, NONE),
	PAD_NC(GPP_A11, NONE),
	PAD_NC(GPP_A12, NONE), // PCH_GPP_A12
	PAD_CFG_NF(GPP_A13, NONE, DEEP, NF1), // SUSWARN#
	PAD_NC(GPP_A14, NONE),
	PAD_CFG_NF(GPP_A15, UP_20K, DEEP, NF1), // SUS_PWR_ACK
	PAD_NC(GPP_A16, NONE),
	PAD_CFG_GPI(GPP_A17, NONE, DEEP), // LIGHT_KB_DET#
	PAD_NC(GPP_A18, NONE),
	PAD_CFG_GPO(GPP_A19, 1, DEEP), // SATA_PWR_EN
	PAD_NC(GPP_A20, NONE),
	PAD_NC(GPP_A21, NONE),
	PAD_CFG_GPO(GPP_A22, 0, DEEP), // PS8338B_SW
	PAD_CFG_GPO(GPP_A23, 0, DEEP), // PS8338B_PCH

	/* ------- GPIO Group B ------- */
	PAD_NC(GPP_B0, NONE), // CORE_VID0
	PAD_NC(GPP_B1, NONE), // CORE_VID1
	PAD_CFG_GPO(GPP_B2, 0, DEEP), // CNVI_WAKE#
	PAD_NC(GPP_B3, NONE),
	PAD_NC(GPP_B4, NONE),
	PAD_NC(GPP_B5, NONE),
	PAD_NC(GPP_B6, NONE),
	PAD_CFG_NF(GPP_B7, NONE, DEEP, NF1), // WLAN_CLKREQ#
	PAD_CFG_NF(GPP_B8, NONE, DEEP, NF1), // LAN_CLKREQ#
	PAD_CFG_NF(GPP_B9, NONE, DEEP, NF1), // TBT_CLKREQ#
	PAD_CFG_NF(GPP_B10, NONE, DEEP, NF1), // SSD_CLKREQ#
	PAD_NC(GPP_B11, NONE), // EXT_PWR_GATE#
	PAD_CFG_NF(GPP_B12, NONE, DEEP, NF1), // SLP_S0# with 100k pull down
	PAD_CFG_NF(GPP_B13, NONE, DEEP, NF1), // PLT_RST#
	PAD_CFG_NF(GPP_B14, NONE, DEEP, NF1), // PCH_SPKR
	PAD_NC(GPP_B15, NONE),
	PAD_NC(GPP_B16, NONE), // PCH_GPP_B16
	PAD_NC(GPP_B17, NONE), // PCH_GPP_B17
	PAD_NC(GPP_B18, NONE), // PCH_GPP_B18 - strap for disabling no reboot mode
	PAD_NC(GPP_B19, NONE),
	PAD_NC(GPP_B20, NONE),
	PAD_NC(GPP_B21, NONE),
	PAD_NC(GPP_B22, NONE), // PCH_GPP_B22
	PAD_NC(GPP_B23, NONE),

	/* ------- GPIO Group C ------- */
	PAD_CFG_NF(GPP_C0, NONE, DEEP, NF1), // SMB_CLK_DDR
	PAD_CFG_NF(GPP_C1, NONE, DEEP, NF1), // SMB_DAT_DDR
	PAD_NC(GPP_C2, NONE), // PCH_GPP_C2 with 4.7k pull-up
	PAD_NC(GPP_C3, NONE),
	PAD_NC(GPP_C4, NONE),
	PAD_NC(GPP_C5, NONE), // PCH_GPP_C5 with 4.7k pull down
	PAD_CFG_GPI(GPP_C6, NONE, DEEP), // LAN_WAKEUP#
	PAD_NC(GPP_C7, NONE),
	PAD_NC(GPP_C8, NONE),
	_PAD_CFG_STRUCT(GPP_C9, 0x82880100, 0x3000), // TBCIO_PLUG_EVENT
	PAD_CFG_TERM_GPO(GPP_C10, 0, NONE, PLTRST), // TBT_FRC_PWR
	PAD_NC(GPP_C11, NONE),
	PAD_CFG_GPO(GPP_C12, 1, PLTRST), // GPP_C12_RTD3
	PAD_CFG_GPO(GPP_C13, 1, PLTRST), // SSD_PWR_DN#
	PAD_CFG_GPO(GPP_C14, 0, PLTRST), // TBTA_HRESET
	PAD_CFG_GPO(GPP_C15, 1, PLTRST), // TBT_PERST_N
	PAD_CFG_NF(GPP_C16, NONE, DEEP, NF1), // T_SDA
	PAD_CFG_NF(GPP_C17, NONE, DEEP, NF1), // T_SCL
	PAD_NC(GPP_C18, NONE),
	PAD_NC(GPP_C19, NONE), // SWI# on galp4, NC on darp6
	PAD_CFG_NF(GPP_C20, NONE, DEEP, NF1), // UART2_RXD
	PAD_CFG_NF(GPP_C21, NONE, DEEP, NF1), // UART2_TXD
	PAD_NC(GPP_C22, NONE),
	PAD_CFG_GPI_APIC_EDGE_LOW(GPP_C23, NONE, PLTRST), // NC on galp4, TP_ATTN# on darp6

	/* ------- GPIO Group D ------- */
	PAD_NC(GPP_D0, NONE),
	PAD_NC(GPP_D1, NONE),
	PAD_NC(GPP_D2, NONE),
	PAD_NC(GPP_D3, NONE),
	PAD_NC(GPP_D4, NONE),
	PAD_NC(GPP_D5, NONE),
	PAD_NC(GPP_D6, NONE),
	PAD_NC(GPP_D7, NONE),
	PAD_CFG_GPO(GPP_D8, 1, DEEP), // SB_BLON
	_PAD_CFG_STRUCT(GPP_D9, 0x40880100, 0x0000), // SWI#
	PAD_NC(GPP_D10, NONE),
	_PAD_CFG_STRUCT(GPP_D11, 0x40880100, 0x3000), // RTD3_PCIE_WAKE#
	PAD_NC(GPP_D12, NONE), // PCH_GPP_D12
	PAD_NC(GPP_D13, NONE),
	PAD_NC(GPP_D14, NONE),
	PAD_CFG_GPO(GPP_D15, 1, DEEP), // TBT_RTD3_PWR_EN_D15 on galp4, NC on darp6
	PAD_CFG_GPO(GPP_D16, 1, PWROK), // RTD3_3G_PW R_EN on galp4, NC on darp6
	PAD_NC(GPP_D17, NONE),
	PAD_NC(GPP_D18, NONE),
	PAD_CFG_NF(GPP_D19, NONE, DEEP, NF1), // GPPC_DMIC_CLK
	PAD_CFG_NF(GPP_D20, NONE, DEEP, NF1), // GPPC_DMIC_DATA
	PAD_CFG_GPI(GPP_D21, NONE, DEEP), // TPM_DET#
	PAD_CFG_GPI(GPP_D22, NONE, DEEP), // TPM_TCM_Detect
	PAD_NC(GPP_D23, NONE),

	/* ------- GPIO Group E ------- */
	PAD_NC(GPP_E0, NONE), // PCH_GPP_E0 with 10k pull-up
	PAD_NC(GPP_E1, NONE), // SATA_ODD_PRSNT#
	PAD_CFG_NF(GPP_E2, UP_20K, DEEP, NF1), // SATAGP2
	PAD_NC(GPP_E3, NONE),
	PAD_NC(GPP_E4, NONE),
	PAD_NC(GPP_E5, NONE),
	PAD_CFG_NF(GPP_E6, NONE, DEEP, NF1), // DEVSLP2
	PAD_NC(GPP_E7, NONE),
	PAD_CFG_NF(GPP_E8, NONE, DEEP, NF1), // PCH_SATAHDD_LED#
	PAD_NC(GPP_E9, NONE), // GP_BSSB_CLK
	PAD_NC(GPP_E10, NONE), // GPP_E10
	PAD_NC(GPP_E11, NONE), // GPP_E11
	PAD_NC(GPP_E12, NONE), // USB_OC#78
	PAD_CFG_NF(GPP_E13, NONE, DEEP, NF1), // MUX_HPD
	PAD_CFG_NF(GPP_E14, NONE, DEEP, NF1), // HDMI_HPD
	_PAD_CFG_STRUCT(GPP_E15, 0x42840100, 0x0), // SMI#
	_PAD_CFG_STRUCT(GPP_E16, 0x80880100, 0x0000), // SCI#
	PAD_CFG_NF(GPP_E17, NONE, DEEP, NF1), // EDP_HPD
	PAD_CFG_NF(GPP_E18, NONE, DEEP, NF1), // MDP_CTRLCLK
	PAD_CFG_NF(GPP_E19, NONE, DEEP, NF1), // MDP_CTRLDATA
	PAD_CFG_NF(GPP_E20, NONE, DEEP, NF1), // HDMI_CTRLCLK
	PAD_CFG_NF(GPP_E21, NONE, DEEP, NF1), // HDMI_CTRLDATA
	PAD_NC(GPP_E22, NONE),
	PAD_NC(GPP_E23, NONE),

	/* ------- GPIO Group F ------- */
	PAD_CFG_NF(GPP_F0, NONE, DEEP, NF1), // CNVI_GNSS_PA_BLANKING
	PAD_NC(GPP_F1, NONE),
	PAD_NC(GPP_F2, NONE),
	PAD_NC(GPP_F3, NONE),
	PAD_CFG_NF(GPP_F4, NONE, DEEP, NF1), // CNVI_BRI_DT
	PAD_CFG_NF(GPP_F5, UP_20K, DEEP, NF1), // CNVI_BRI_RSP
	PAD_CFG_NF(GPP_F6, NONE, DEEP, NF1), // CNVI_RGI_DT
	PAD_CFG_NF(GPP_F7, UP_20K, DEEP, NF1), // CNVI_RGI_RSP
	PAD_CFG_NF(GPP_F8, NONE, DEEP, NF1), // CNVI_MFUART2_RXD
	PAD_CFG_NF(GPP_F9, NONE, DEEP, NF1), // CNVI_MFUART2_TXD
	PAD_NC(GPP_F10, NONE),
	PAD_NC(GPP_F11, NONE),
	PAD_NC(GPP_F12, NONE),
	PAD_NC(GPP_F13, NONE),
	PAD_NC(GPP_F14, NONE),
	PAD_NC(GPP_F15, NONE),
	PAD_NC(GPP_F16, NONE),
	PAD_NC(GPP_F17, NONE),
	PAD_NC(GPP_F18, NONE),
	PAD_NC(GPP_F19, NONE),
	PAD_NC(GPP_F20, NONE),
	PAD_NC(GPP_F21, NONE),
	PAD_NC(GPP_F22, NONE),
	PAD_CFG_GPI(GPP_F23, NONE, DEEP), // A4WP_PRESENT

	/* ------- GPIO Group G ------- */
	PAD_CFG_GPI(GPP_G0, NONE, DEEP), // EDP_DET
	PAD_NC(GPP_G1, NONE),
	PAD_NC(GPP_G2, NONE),
	PAD_CFG_GPO(GPP_G3, 0, DEEP), // ASM1543_I_SEL0
	PAD_CFG_GPO(GPP_G4, 0, DEEP), // ASM1543_I_SEL1
	PAD_NC(GPP_G5, NONE), // BOARD_ID
	PAD_NC(GPP_G6, NONE),
	PAD_NC(GPP_G7, NONE), // TBT_Detect

	/* ------- GPIO Group H ------- */
	PAD_NC(GPP_H0, NONE),
	PAD_CFG_NF(GPP_H1, NONE, DEEP, NF3), // CNVI_RST#
	PAD_CFG_NF(GPP_H2, NONE, DEEP, NF3), // CNVI_CLKREQ
	PAD_NC(GPP_H3, NONE),
	PAD_NC(GPP_H4, NONE),
	PAD_NC(GPP_H5, NONE),
	PAD_NC(GPP_H6, NONE),
	PAD_NC(GPP_H7, NONE),
	PAD_NC(GPP_H8, NONE),
	PAD_NC(GPP_H9, NONE),
	PAD_NC(GPP_H10, NONE),
	PAD_NC(GPP_H11, NONE),
	PAD_NC(GPP_H12, NONE),
	PAD_NC(GPP_H13, NONE),
	PAD_NC(GPP_H14, NONE), // G_INT1
	PAD_NC(GPP_H15, NONE),
	PAD_NC(GPP_H16, NONE),
	PAD_NC(GPP_H17, NONE),
	PAD_CFG_NF(GPP_H18, NONE, DEEP, NF1), // CPU_C10_GATE#
	PAD_NC(GPP_H19, NONE),
	PAD_NC(GPP_H20, NONE),
	PAD_NC(GPP_H21, NONE), // GPPC_H21
	PAD_CFG_GPO(GPP_H22, 1, DEEP), // TBT_RTD3_PWR_EN_H22
	PAD_NC(GPP_H23, NONE), // WIGIG_PEWAKE on galp4, NC on darp6
};

void mainboard_configure_gpios(void)
{
	gpio_configure_pads(gpio_table, ARRAY_SIZE(gpio_table));
}
