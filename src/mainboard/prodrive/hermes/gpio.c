/* SPDX-License-Identifier: GPL-2.0-only */

#include <commonlib/helpers.h>
#include <intelblocks/gpio.h>
#include <soc/gpio.h>

#include "gpio.h"

/* Pad configuration in ramstage */
static const struct pad_config gpio_table[] = {
	/* ------- GPIO Group GPP_A ------- */

	/* ISH */
	PAD_NC(GPP_A17, NONE),
	PAD_NC(GPP_A18, NONE),
	PAD_NC(GPP_A19, NONE),
	PAD_NC(GPP_A20, NONE),
	PAD_NC(GPP_A21, NONE),
	PAD_NC(GPP_A22, NONE),
	PAD_NC(GPP_A23, NONE),

	/* ------- GPIO Group GPP_B ------- */
	PAD_NC(GPP_B0, NONE),
	PAD_NC(GPP_B1, NONE),

	/* GPP_B2 - M2_E_BT_UART_WAKE_n */
	PAD_CFG_GPI_INT(GPP_B2, NONE, DEEP, OFF),

	/* GPP_B3 - PCH_M2_E_BT_KILL_n   : handled at runtime */
	/* GPP_B4 - PCH_M2_E_WLAN_KILL_n : handled at runtime */

	/* SRCCLKREQ0# - SRCCLKREQ5# */
	PAD_NC(GPP_B5, NONE),
	PAD_NC(GPP_B6, NONE),
	PAD_NC(GPP_B7, NONE),
	PAD_NC(GPP_B8, NONE),
	PAD_CFG_NF(GPP_B9, NONE, DEEP, NF1),		/* M2_M_CLK_REQ_n */
	PAD_CFG_NF(GPP_B10, NONE, DEEP, NF1),		/* M2_E_CLK_REQ_n */

	PAD_NC(GPP_B11, NONE),

	/* GPP_B12 - SLP_S0_n */
	PAD_CFG_NF(GPP_B12, NONE, DEEP, NF1),
	/* GPP_B13 - PLTRST_n */
	PAD_CFG_NF(GPP_B13, NONE, DEEP, NF1),

	/* GPP_B14 - SPKR */
	PAD_CFG_NF(GPP_B14, NONE, DEEP, NF1),

	/* GSPI0 */
	PAD_CFG_NF(GPP_B15, NONE, DEEP, NF1),		/* SPI0_CS */
	PAD_CFG_NF(GPP_B16, NONE, DEEP, NF1),		/* SPI0_CLK */
	PAD_CFG_NF(GPP_B17, NONE, DEEP, NF1),		/* SPI0_MISO */
	PAD_CFG_NF(GPP_B18, NONE, DEEP, NF1),		/* SPI0_MOSI */

	/* GSPI1 */
	PAD_NC(GPP_B19, NONE),
	PAD_NC(GPP_B20, NONE),
	PAD_NC(GPP_B21, NONE),
	PAD_NC(GPP_B22, NONE),

	PAD_CFG_NF(GPP_B23, NONE, DEEP, NF1),		/* PCH_SML1_ALERT_n */

	/* ------- GPIO Group GPP_C ------- */
	/* SML0 - Used by CSME */
	PAD_CFG_NF(GPP_C3, NONE, DEEP, NF1),		/* PCH_SML0_CLK */
	PAD_CFG_NF(GPP_C4, NONE, DEEP, NF1),		/* PCH_SML0_DATA */
	PAD_CFG_NF(GPP_C5, NONE, DEEP, NF1),		/* PCH_SML0_ALERT_N */

	/* SML1 - Used by CSME */
	PAD_CFG_NF(GPP_C6, NONE, DEEP, NF1),		/* PCH_SML1_CLK */
	PAD_CFG_NF(GPP_C7, NONE, DEEP, NF1),		/* PCH_SML1_DATA */

	/* UART0 */
	PAD_CFG_NF(GPP_C8, NONE, DEEP, NF1),		/* UART0_RXD */
	PAD_CFG_NF(GPP_C9, NONE, DEEP, NF1),		/* UART0_TXD */
	PAD_CFG_NF(GPP_C10, NONE, DEEP, NF1),		/* UART0_RTS_N */
	PAD_CFG_NF(GPP_C11, NONE, DEEP, NF1),		/* UART0_CTS_N */

	/* UART1 */
	PAD_CFG_NF(GPP_C12, NONE, DEEP, NF1),		/* UART1_RXD */
	PAD_CFG_NF(GPP_C13, NONE, DEEP, NF1),		/* UART1_TXD */
	PAD_CFG_NF(GPP_C14, NONE, DEEP, NF1),		/* UART1_RTS_N */
	PAD_CFG_NF(GPP_C15, NONE, DEEP, NF1),		/* UART1_CTS_N */

	PAD_NC(GPP_C17, NONE),

	PAD_CFG_GPI_INT(GPP_C18, NONE, PLTRST, OFF),	/* AUD_FPA_PRSNT_n */
	/* GPP_C19 - AUD_AMP_EN : configured at runtime */

	/* UART2 */
	PAD_CFG_NF(GPP_C20, NONE, DEEP, NF1),		/* UART2_RXD */
	PAD_CFG_NF(GPP_C21, NONE, DEEP, NF1),		/* UART2_TXD */
	PAD_CFG_NF(GPP_C22, NONE, DEEP, NF1),		/* UART2_RTS_N */
	PAD_CFG_NF(GPP_C23, NONE, DEEP, NF1),		/* UART2_CTS_N */

	/* ------- GPIO Group GPP_D ------- */
	/* SPI1 */
	PAD_NC(GPP_D0, NONE),
	PAD_NC(GPP_D1, NONE),
	PAD_NC(GPP_D2, NONE),
	PAD_NC(GPP_D3, NONE),

	PAD_NC(GPP_D4, NONE),

	/* CNVi */
	PAD_CFG_NF(GPP_D5, NONE, DEEP, NF3),		/* M2_E_BT_PCMFRM_CRF_RST_n */
	PAD_CFG_NF(GPP_D6, NONE, DEEP, NF3),		/* M2_E_BT_PCMOUT_CLKREQ0 */
	PAD_NC(GPP_D7, NONE),				/* M2_E_BT_PCMIN */
	PAD_NC(GPP_D8, NONE),				/* M2_E_BT_PCMCLK */

	/* ISH SPI */
	PAD_NC(GPP_D9, NONE),
	PAD_NC(GPP_D10, NONE),
	PAD_NC(GPP_D11, NONE),
	PAD_NC(GPP_D12, NONE),

	/* ISH UART */
	PAD_NC(GPP_D13, NONE),
	PAD_NC(GPP_D14, NONE),
	PAD_NC(GPP_D15, NONE),
	PAD_NC(GPP_D16, NONE),

	/* DMIC */
	PAD_NC(GPP_D17, NONE),
	PAD_NC(GPP_D18, NONE),
	PAD_NC(GPP_D19, NONE),
	PAD_NC(GPP_D20, NONE),

	PAD_NC(GPP_D21, NONE),
	PAD_NC(GPP_D22, NONE),
	PAD_NC(GPP_D23, NONE),

	/* ------- GPIO Group GPP_G ------- */
	/* GPP_G0 - USB31_RP1_PWR_EN : configured at runtime */
	/* GPP_G1 - USB31_RP2_PWR_EN : configured at runtime */
	/* GPP_G2 - USB31_FP_PWR_EN  : configured at runtime */
	/* GPP_G3 - USB2_FP1_PWR_EN  : configured at runtime */
	/* GPP_G4 - USB2_FP2_PWR_EN  : configured at runtime */

	PAD_NC(GPP_G5, NONE),
	PAD_NC(GPP_G6, NONE),
	PAD_NC(GPP_G7, NONE),

	/* ------- GPIO Group GPD ------- */
	/* GPD0 - BATLOW */
	PAD_CFG_NF(GPD0, NONE, DEEP, NF1),
	/* GPD1 - ACPRESENT */
	PAD_CFG_NF(GPD1, NONE, DEEP, NF1),
	/* GPD2 - LAN_WAKE# */
	PAD_CFG_NF(GPD2, NONE, DEEP, NF1),
	/* GPD3 - PRWBTN# */
	PAD_CFG_NF(GPD3, NONE, DEEP, NF1),
	/* GPD4 - SLP_S3# */
	PAD_CFG_NF(GPD4, NONE, DEEP, NF1),
	/* GPD5 - SLP_S4# */
	PAD_CFG_NF(GPD5, NONE, DEEP, NF1),
	/* GPD6 - SLP_A# */
	PAD_CFG_NF(GPD6, NONE, DEEP, NF1),
	/* GPD7 - GPIO */
	PAD_NC(GPD7, NONE),
	/* GPD8 - SUSCLK */
	PAD_CFG_NF(GPD8, NONE, DEEP, NF1),
	/* GPD9 - SLP_WLAN */
	PAD_CFG_NF(GPD9, NONE, DEEP, NF1),
	/* GPD10 - SLP_S5# */
	PAD_CFG_NF(GPD10, NONE, DEEP, NF1),
	/* GPD11 - LAN_DISABLE_n */
	PAD_CFG_NF(GPD11, NONE, DEEP, NF1),

	/* ------- GPIO Group GPP_K ------- */
	/* GPP_K0 - PERST_PCH_SLOTS_n   : configured at runtime */
	/* GPP_K1 - PERST_CPU_SLOTS_n   : configured at runtime */
	/* GPP_K2 - PERST_CNVI_SLOTS_n  : configured at runtime */
	/* GPP_K3 - DP1_PWR_EN          : configured at runtime */
	/* GPP_K4 - DP2_PWR_EN          : configured at runtime */
	/* GPP_K5 - DP3_PWR_EN          : configured at runtime */

	PAD_NC(GPP_K6, NONE),

	/* GPP_K7 - EN_3V3_KEYM_PCH     : configured at runtime  */

	PAD_NC(GPP_K8, NONE),
	PAD_NC(GPP_K9, NONE),
	PAD_NC(GPP_K10, NONE),
	PAD_NC(GPP_K11, NONE),

	/* K12 - K16 in early GPIO config */

	PAD_NC(GPP_K17, NONE),

	/* GPP_K18/!NMI - NC */
	PAD_NC(GPP_K18, NONE),
	/* GPP_K19/!SMI - NC */
	PAD_NC(GPP_K19, NONE),

	/* GPP_K20 - CPU_CATERR_PCH_n */
	PAD_CFG_GPI(GPP_K20, NONE, DEEP),
	/* GPP_K21 - TPM_INT_n */
	PAD_CFG_GPI_INT(GPP_K21, NONE, DEEP, OFF), /* Trigger? */
	/* GPP_K22 - NC */
	PAD_NC(GPP_K22, NONE),
	/* GPP_K23 - NC */
	PAD_NC(GPP_K23, NONE),

	/* ------- GPIO Group GPP_H ------- */

	/* SRCCLKREQ6# - SRCCLKREQ10# not used as CLKREQ, external 10K pullup */
	PAD_CFG_GPI(GPP_H0, NONE, DEEP),		/* PCIE_SLOT1_PRSNT_PCH_n */
	PAD_CFG_GPI(GPP_H1, NONE, DEEP),		/* PCIE_SLOT2_PRSNT_PCH_n */
	PAD_CFG_GPI(GPP_H2, NONE, DEEP),		/* PCIE_SLOT3_PRSNT_PCH_n */
	PAD_CFG_GPI(GPP_H3, NONE, DEEP),		/* PCIE_SLOT4_PRSNT_PCH_n */
	PAD_CFG_GPI(GPP_H4, NONE, DEEP),		/* PCIE_SLOT6_PRSNT_PCH_n */

	PAD_CFG_GPI(GPP_H4, NONE, DEEP),		/* PCIE_SLOT6_PRSNT_PCH_n */

	/* GPP_H5 - PCH_HBLED_n configured in early init */

	/* SRCCLKREQ13# - SRCCLKREQ15# */
	PAD_NC(GPP_H7, NONE),
	PAD_NC(GPP_H8, NONE),
	PAD_NC(GPP_H9, NONE),

	/* SML2 - Used by CSME */
	PAD_NC(GPP_H10, NONE),
	PAD_NC(GPP_H11, NONE),
	PAD_NC(GPP_H12, NONE),

	/* SML3 - Used by CSME */
	PAD_NC(GPP_H13, NONE),
	PAD_NC(GPP_H14, NONE),
	PAD_NC(GPP_H15, NONE),

	/* SML4 - Used by CSME */
	PAD_CFG_NF(GPP_H16, NONE, DEEP, NF1),		/* PCIE_SMB_CLK */
	PAD_CFG_NF(GPP_H17, NONE, DEEP, NF1),		/* PCIE_SMB_DATA */
	PAD_NC(GPP_H18, NONE),

	/* ISH I2C0 */
	PAD_NC(GPP_H19, NONE),
	PAD_NC(GPP_H20, NONE),

	/* ISH I2C1 */
	PAD_NC(GPP_H21, NONE),
	PAD_NC(GPP_H22, NONE),

	PAD_NC(GPP_H23, NONE),

	/* ------- GPIO Group GPP_E ------- */
	/* GPP_E0 - NC */
	PAD_NC(GPP_E0, NONE),
	/* GPP_E1 - M2_SATA_PCIE_SEL */
	PAD_CFG_NF(GPP_E1, NONE, DEEP, NF1),
	/* GPP_E2 - NC */
	PAD_NC(GPP_E2, NONE),
	/* GPP_E3 - NC */
	PAD_NC(GPP_E3, NONE),
	/* GPP_E4 - NC */
	PAD_NC(GPP_E4, NONE),

	/* GPP_E5 - PCH_M2_SATA_DEVSLP1 */
	PAD_CFG_NF(GPP_E5, NONE, DEEP, NF1),
	/* GPP_E6 - NC */
	PAD_NC(GPP_E6, NONE),
	/* GPP_E8 - SATALED# */
	PAD_CFG_NF(GPP_E8, NONE, DEEP, NF1),

	/* GPP_E9 - USB31_RP1_OC_N */
	PAD_CFG_NF(GPP_E9, NONE, DEEP, NF1),
	/* GPP_E10 - USB31_RP2_OC_N */
	PAD_CFG_NF(GPP_E10, NONE, DEEP, NF1),
	/* GPP_E11 - USB31_FP_OC_N */
	PAD_CFG_NF(GPP_E11, NONE, DEEP, NF1),
	/* GPP_E12 - USB2_FP1_OC_N */
	PAD_CFG_NF(GPP_E12, NONE, DEEP, NF1),

	/* ------- GPIO Group GPP_F ------- */
	/* SATAGP3-7 */
	PAD_NC(GPP_F0, NONE),
	PAD_NC(GPP_F1, NONE),
	PAD_NC(GPP_F2, NONE),
	PAD_NC(GPP_F3, NONE),
	PAD_NC(GPP_F4, NONE),

	/* SATA DEVSLP3-7 */
	PAD_NC(GPP_F5, NONE),
	PAD_NC(GPP_F6, NONE),
	PAD_NC(GPP_F7, NONE),
	PAD_NC(GPP_F8, NONE),
	PAD_NC(GPP_F9, NONE),

	/* SGPIO has external 2K pullups */
	/* GPP_F10 - SATA_SCLOCK */
	PAD_CFG_NF(GPP_F10, NONE, DEEP, NF1),
	/* GPP_F11 - SATA_SLOAD */
	PAD_CFG_NF(GPP_F11, NONE, DEEP, NF1),
	/* GPP_F12 - SATA_SDATAOUT1 */
	PAD_CFG_NF(GPP_F12, NONE, DEEP, NF1),
	/* GPP_F13 - SATA_BMC_SDATAOUT0 */
	PAD_CFG_NF(GPP_F13, NONE, DEEP, NF1),

	/* GPP_F14 - PS_ON_PCH_n */
	PAD_CFG_NF(GPP_F14, NONE, DEEP, NF2),
	/* GPP_F15 - USB2_FP2_OC_N */
	PAD_CFG_NF(GPP_F15, NONE, DEEP, NF1),

	/* GPP_F16 - NC/PU */
	PAD_NC(GPP_F16, NONE),
	/* GPP_F17 - GPIO */
	PAD_NC(GPP_F17, NONE),
	/* GPP_F18 - GPIO */
	PAD_NC(GPP_F18, NONE),
	/* GPP_F19 - GPIO */
	PAD_NC(GPP_F19, NONE),
	/* GPP_F20 - GPIO */
	PAD_NC(GPP_F20, NONE),
	/* GPP_F21 - GPIO */
	PAD_NC(GPP_F21, NONE),
	/* GPP_F22 - GPIO */
	PAD_NC(GPP_F22, NONE),
	/* GPP_F23 - NC */
	PAD_NC(GPP_F23, NONE),
	/* GPP_J0 - CNV_GNSS_PA_BLANKING */
	PAD_CFG_NF(GPP_J0, NONE, DEEP, NF1),
	/* GPP_J1 - NC */
	PAD_NC(GPP_J1, NONE),
	/* GPP_J2 - NC */
	PAD_NC(GPP_J2, NONE),
	/* GPP_J3 - NC */
	PAD_NC(GPP_J3, NONE),

	/* CNVi */
	/* GPP_J4 - CNV_BRI_DT*/
	PAD_CFG_NF(GPP_J4, NONE, DEEP, NF1),
	/* GPP_J5 - CNV_BRI_RSP */
	PAD_CFG_NF(GPP_J5, UP_20K, DEEP, NF1),
	/* GPP_J6 - CNV_RGI_DT */
	PAD_CFG_NF(GPP_J6, NONE, DEEP, NF1),
	/* GPP_J7 - CNV_RGI_RSP */
	PAD_CFG_NF(GPP_J7, UP_20K, DEEP, NF1),
	/* GPP_J8 - CNV_MFUART2_RXD */
	PAD_CFG_NF(GPP_J8, NONE, DEEP, NF1),
	/* GPP_J9 - CNV_MFUART2_TXD */
	PAD_CFG_NF(GPP_J9, NONE, DEEP, NF1),

	PAD_NC(GPP_J10, NONE),
	PAD_NC(GPP_J11, NONE),

	/* Display Port */
	PAD_CFG_NF(GPP_I0, NONE, DEEP, NF1),		/* DP1_HPD */
	PAD_CFG_NF(GPP_I1, NONE, DEEP, NF1),		/* DP2_HPD */
	PAD_CFG_NF(GPP_I2, NONE, DEEP, NF1),		/* DP3_HPD */
	PAD_NC(GPP_I3, NONE),
	PAD_NC(GPP_I4, NONE),

	PAD_CFG_NF(GPP_I5, NONE, DEEP, NF1),		/* DP1_DDC_SCL */
	PAD_CFG_NF(GPP_I6, NONE, DEEP, NF1),		/* DP1_DDC_SDA */

	PAD_CFG_NF(GPP_I7, NONE, DEEP, NF1),		/* DP2_DDC_SCL */
	PAD_CFG_NF(GPP_I8, NONE, DEEP, NF1),		/* DP2_DDC_SDA */

	PAD_CFG_NF(GPP_I9, NONE, DEEP, NF1),		/* DP3_DDC_SCL */
	PAD_CFG_NF(GPP_I10, NONE, DEEP, NF1),		/* DP3_DDC_SDA */

	PAD_NC(GPP_I11, NONE),
	PAD_NC(GPP_I12, NONE),
	PAD_NC(GPP_I13, NONE),
	PAD_NC(GPP_I14, NONE),

};

/* Early pad configuration in bootblock */
const struct pad_config early_gpio_table[] = {
	/* Get PCIe out of reset */
	PAD_CFG_GPO(GPP_K0, 1, DEEP),			/* PERST_PCH_SLOTS_n */
	PAD_CFG_GPO(GPP_K1, 1, DEEP),			/* PERST_CPU_SLOTS_n */
	PAD_CFG_GPO(GPP_K2, 1, DEEP),			/* PERST_CNVI_SLOTS_n */

	/* SMB */
	PAD_CFG_NF(GPP_C0, NONE, DEEP, NF1),		/* PCH_SMB_CLK */
	PAD_CFG_NF(GPP_C1, NONE, DEEP, NF1),		/* PCH_SMB_DATA */
	PAD_NC(GPP_C2, NONE),

	/* BMC HSI */
	PAD_CFG_GPI(GPP_K12, NONE, DEEP),		/* PCH_IO_2 */
	PAD_CFG_GPI(GPP_K13, NONE, DEEP),		/* PCH_IO_3 */
	PAD_CFG_GPI(GPP_K14, NONE, DEEP),		/* PCH_IO_1 */
	PAD_NC(GPP_K15, NONE),
	PAD_CFG_GPI(GPP_K16, NONE, DEEP),		/* PCH_IO_0 */

	/* LED */
	PAD_CFG_GPO(GPP_H5, 0, DEEP),			/* PCH_HBLED_n */

	/* UART0 */
	PAD_CFG_NF(GPP_C8, NONE, DEEP, NF1),		/* UART0_RXD */
	PAD_CFG_NF(GPP_C9, NONE, DEEP, NF1),		/* UART0_TXD */

	/* UART1 */
	PAD_CFG_NF(GPP_C12, NONE, DEEP, NF1),		/* UART1_RXD */
	PAD_CFG_NF(GPP_C13, NONE, DEEP, NF1),		/* UART1_TXD */

	/* UART2 */
	PAD_CFG_NF(GPP_C20, NONE, DEEP, NF1),		/* UART2_RXD */
	PAD_CFG_NF(GPP_C21, NONE, DEEP, NF1),		/* UART2_TXD */
};

void program_gpio_pads(void)
{
	gpio_configure_pads(gpio_table, ARRAY_SIZE(gpio_table));
}

void program_early_gpio_pads(void)
{
	gpio_configure_pads(early_gpio_table, ARRAY_SIZE(early_gpio_table));
}
