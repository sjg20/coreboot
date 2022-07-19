/* SPDX-License-Identifier: GPL-2.0-only */

#include <baseboard/gpio.h>
#include <baseboard/variants.h>
#include <soc/gpio.h>

/* Early pad configuration in bootblock */
static const struct pad_config early_gpio_table[] = {
	/* WWAN_RST# (updated in ramstage) */
	PAD_CFG_GPO(GPP_F14, 0, DEEP),
	/* WWAN_PERST_L (updated in ramstage) */
	PAD_CFG_GPO(GPP_C5, 0, DEEP),
	/* WWAN_FCPO_L (updated in romstage) */
	PAD_CFG_GPO(GPP_F15, 0, DEEP),
	/* WWAN_PWR_EN */
	PAD_CFG_GPO(GPP_F21, 1, DEEP),
	/* SMB_CLK */
	PAD_CFG_NF(GPP_C0, NONE, DEEP, NF1),
	/* SMB_DATA */
	PAD_CFG_NF(GPP_C1, NONE, DEEP, NF1),

	/* EC_IN_RW */
	PAD_CFG_GPI(GPP_E7, NONE, DEEP),

	/* x4 PCIE slot 1 RESET */
	PAD_CFG_GPO(GPP_F10, 0, PLTRST),

	/* Support external source clock via OEB6 and OEB7 */
	/* SRCCLK_OEB6 for built-in LAN */
	PAD_CFG_NF(GPP_E5, NONE, PLTRST, NF2),
	/* SRCCLK_OEB7 for x4 slot */
	PAD_CFG_NF(GPP_A7, NONE, PLTRST, NF1),

	/* CPU PCIe VGPIO for RP0 */
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_0, NONE, PLTRST, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_1, NONE, PLTRST, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_3, NONE, PLTRST, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_2, NONE, PLTRST, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_4, NONE, PLTRST, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_5, NONE, PLTRST, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_6, NONE, PLTRST, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_7, NONE, PLTRST, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_8, NONE, PLTRST, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_9, NONE, PLTRST, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_10, NONE, PLTRST, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_11, NONE, PLTRST, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_12, NONE, PLTRST, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_13, NONE, PLTRST, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_14, NONE, PLTRST, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_15, NONE, PLTRST, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_64, NONE, PLTRST, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_65, NONE, PLTRST, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_66, NONE, PLTRST, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_67, NONE, PLTRST, NF1),

	/* CPU PCIe vGPIO for RP1 */
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_16, NONE, PLTRST, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_17, NONE, PLTRST, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_18, NONE, PLTRST, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_19, NONE, PLTRST, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_20, NONE, PLTRST, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_21, NONE, PLTRST, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_22, NONE, PLTRST, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_23, NONE, PLTRST, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_24, NONE, PLTRST, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_25, NONE, PLTRST, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_26, NONE, PLTRST, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_27, NONE, PLTRST, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_28, NONE, PLTRST, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_29, NONE, PLTRST, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_30, NONE, PLTRST, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_31, NONE, PLTRST, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_68, NONE, PLTRST, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_69, NONE, PLTRST, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_70, NONE, PLTRST, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_71, NONE, PLTRST, NF1),

	/* CPU PCIe vGPIO for RP2 */
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_32, NONE, PLTRST, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_33, NONE, PLTRST, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_34, NONE, PLTRST, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_35, NONE, PLTRST, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_36, NONE, PLTRST, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_37, NONE, PLTRST, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_38, NONE, PLTRST, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_39, NONE, PLTRST, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_40, NONE, PLTRST, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_41, NONE, PLTRST, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_42, NONE, PLTRST, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_43, NONE, PLTRST, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_44, NONE, PLTRST, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_45, NONE, PLTRST, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_46, NONE, PLTRST, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_47, NONE, PLTRST, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_72, NONE, PLTRST, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_73, NONE, PLTRST, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_74, NONE, PLTRST, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_75, NONE, PLTRST, NF1),

	/* CPU PCIe vGPIO for RP3 */
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_48, NONE, PLTRST, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_49, NONE, PLTRST, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_50, NONE, PLTRST, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_51, NONE, PLTRST, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_52, NONE, PLTRST, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_53, NONE, PLTRST, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_54, NONE, PLTRST, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_55, NONE, PLTRST, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_56, NONE, PLTRST, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_57, NONE, PLTRST, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_58, NONE, PLTRST, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_59, NONE, PLTRST, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_60, NONE, PLTRST, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_61, NONE, PLTRST, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_62, NONE, PLTRST, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_63, NONE, PLTRST, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_76, NONE, PLTRST, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_77, NONE, PLTRST, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_78, NONE, PLTRST, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_79, NONE, PLTRST, NF1),

	/*_TPM_*/
	/* H1_PCH_INT_ODL */
	PAD_CFG_GPI_APIC(GPP_E3, NONE, PLTRST, LEVEL, INVERT),
	/* F16 : GSPI1_CS0N */
	PAD_CFG_NF(GPP_F16, NONE, DEEP, NF4),
	/* F11 : GSPI1_CLK */
	PAD_CFG_NF(GPP_F11, NONE, DEEP, NF4),
	/* F13 : GSPI1_MISO */
	PAD_CFG_NF(GPP_F13, NONE, DEEP, NF4),
	/* F12 : GSPI1_MOSI */
	PAD_CFG_NF(GPP_F12, NONE, DEEP, NF4),
};

static const struct pad_config early_uart_gpio_table[] = {
	/* UART0 RX */
	PAD_CFG_NF(GPP_H10, NONE, DEEP, NF2),
	/* UART0 TX */
	PAD_CFG_NF(GPP_H11, NONE, DEEP, NF2),
};

void variant_configure_early_gpio_pads(void)
{
	if (CONFIG(INTEL_LPSS_UART_FOR_CONSOLE))
		gpio_configure_pads(early_uart_gpio_table, ARRAY_SIZE(early_uart_gpio_table));

	gpio_configure_pads(early_gpio_table, ARRAY_SIZE(early_gpio_table));
}
