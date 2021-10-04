/* SPDX-License-Identifier: GPL-2.0-only */

#include <baseboard/gpio.h>
#include <baseboard/variants.h>
#include <commonlib/helpers.h>
#include <soc/gpio.h>

/* Early pad configuration in bootblock */
static const struct pad_config early_gpio_table[] = {
	/* WWAN_RST# */
	PAD_CFG_GPO(GPP_E5, 0, PLTRST),
	/* WWAN_PWR_EN */
	PAD_CFG_GPO(GPP_A8, 1, DEEP),

	/* H0  : PCH_SSD_RST# */
	PAD_CFG_GPO(GPP_H0, 0, PLTRST),
	/* H13 : CPU_SSD_RST# */
	PAD_CFG_GPO(GPP_H13, 0, PLTRST),

	/* EC_IN_RW */
	PAD_CFG_GPI(GPP_E7, NONE, DEEP),

	/* CPU PCIe VGPIO for RP0 */
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_0, NONE, DEEP, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_1, NONE, DEEP, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_3, NONE, DEEP, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_2, NONE, DEEP, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_4, NONE, DEEP, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_5, NONE, DEEP, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_6, NONE, DEEP, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_7, NONE, DEEP, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_8, NONE, DEEP, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_9, NONE, DEEP, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_10, NONE, DEEP, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_11, NONE, DEEP, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_12, NONE, DEEP, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_13, NONE, DEEP, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_14, NONE, DEEP, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_15, NONE, DEEP, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_64, NONE, DEEP, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_65, NONE, DEEP, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_66, NONE, DEEP, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_67, NONE, DEEP, NF1),

	/* CPU PCIe vGPIO for RP1 */
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_16, NONE, DEEP, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_17, NONE, DEEP, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_18, NONE, DEEP, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_19, NONE, DEEP, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_20, NONE, DEEP, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_21, NONE, DEEP, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_22, NONE, DEEP, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_23, NONE, DEEP, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_24, NONE, DEEP, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_25, NONE, DEEP, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_26, NONE, DEEP, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_27, NONE, DEEP, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_28, NONE, DEEP, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_29, NONE, DEEP, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_30, NONE, DEEP, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_31, NONE, DEEP, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_68, NONE, DEEP, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_69, NONE, DEEP, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_70, NONE, DEEP, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_71, NONE, DEEP, NF1),

	/* CPU PCIe vGPIO for RP2 */
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_32, NONE, DEEP, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_33, NONE, DEEP, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_34, NONE, DEEP, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_35, NONE, DEEP, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_36, NONE, DEEP, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_37, NONE, DEEP, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_38, NONE, DEEP, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_39, NONE, DEEP, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_40, NONE, DEEP, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_41, NONE, DEEP, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_42, NONE, DEEP, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_43, NONE, DEEP, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_44, NONE, DEEP, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_45, NONE, DEEP, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_46, NONE, DEEP, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_47, NONE, DEEP, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_72, NONE, DEEP, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_73, NONE, DEEP, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_74, NONE, DEEP, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_75, NONE, DEEP, NF1),

	/* CPU PCIe vGPIO for RP3 */
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_48, NONE, DEEP, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_49, NONE, DEEP, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_50, NONE, DEEP, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_51, NONE, DEEP, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_52, NONE, DEEP, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_53, NONE, DEEP, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_54, NONE, DEEP, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_55, NONE, DEEP, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_56, NONE, DEEP, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_57, NONE, DEEP, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_58, NONE, DEEP, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_59, NONE, DEEP, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_60, NONE, DEEP, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_61, NONE, DEEP, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_62, NONE, DEEP, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_63, NONE, DEEP, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_76, NONE, DEEP, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_77, NONE, DEEP, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_78, NONE, DEEP, NF1),
	PAD_CFG_NF_VWEN(GPP_vGPIO_PCIE_79, NONE, DEEP, NF1),

	/* H1_PCH_INT_ODL */
	PAD_CFG_GPI_APIC(GPP_E3, NONE, PLTRST, LEVEL, INVERT),
	/* TPM */
	/* F16 : GSPI1_CS0N */
	PAD_CFG_NF(GPP_F16, NONE, DEEP, NF4),
	/* F11 : GSPI1_CLK */
	PAD_CFG_NF(GPP_F11, NONE, DEEP, NF4),
	/* F13 : GSPI1_MISO */
	PAD_CFG_NF(GPP_F13, NONE, DEEP, NF4),
	/* F12 : GSPI1_MOSI */
	PAD_CFG_NF(GPP_F12, NONE, DEEP, NF4),

	 /* D10 : PCH_SSD_PWR_EN */
	PAD_CFG_GPO(GPP_D10, 1, PLTRST),
	/* D16 : CPU_SSD_PWR_EN */
	PAD_CFG_GPO(GPP_D16, 1, PLTRST),

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
