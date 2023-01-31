/* SPDX-License-Identifier: GPL-2.0-only */

#include <gpio.h>
#include "gpio.h"

/* GPIO pins used by coreboot should be initialized in bootblock */

static const struct soc_amd_gpio gpio_set_stage_reset[] = {
	/* TPM CS */
	PAD_NF(GPIO_29, SPI_TPM_CS_L, PULL_NONE),
	/* ESPI_CS_L */
	PAD_NF(GPIO_30, ESPI_CS_L, PULL_NONE),
	/* ESPI_SOC_CLK */
	PAD_NF(GPIO_77, SPI1_CLK, PULL_NONE),
	/* ESPI_DATA0 */
	PAD_NF(GPIO_81, SPI1_DAT0, PULL_NONE),
	/* ESPI_DATA1 */
	PAD_NF(GPIO_80, SPI1_DAT1, PULL_NONE),
	/* ESPI_DATA2 */
	PAD_NF(GPIO_68, SPI1_DAT2, PULL_NONE),
	/* ESPI_DATA3 */
	PAD_NF(GPIO_69, SPI1_DAT3, PULL_NONE),
	/* ESPI_ALERT_L */
	PAD_NF(GPIO_22, ESPI_ALERT_D1, PULL_NONE),
	/* TPM IRQ */
	PAD_SCI(GPIO_130, PULL_UP, EDGE_LOW),
	/* SPI_ROM_REQ */
	PAD_NF(GPIO_67, SPI_ROM_REQ, PULL_NONE),
	/* SPI_ROM_GNT */
	PAD_NF(GPIO_76, SPI_ROM_GNT, PULL_NONE),
	/* KBRST_L */
	PAD_NF(GPIO_21, KBRST_L, PULL_NONE),

	/* Deassert PCIe Reset lines */
	/* PCIE_RST0_L */
	PAD_NFO(GPIO_26, PCIE_RST0_L, HIGH),
	/* PCIE_RST1_L */
	PAD_NFO(GPIO_27, PCIE_RST1_L, HIGH),

	/* PC beep to codec */
	PAD_NF(GPIO_91, SPKR, PULL_NONE),
	/* Enable UART 2 */
	/* UART2_RXD */
	PAD_NF(GPIO_136, UART2_RXD, PULL_NONE),
	/* UART2_TXD */
	PAD_NF(GPIO_138, UART2_TXD, PULL_NONE),
	/* Enable UART 0 */
	/* UART0_RXD */
	PAD_NF(GPIO_141, UART0_RXD, PULL_NONE),
	/* UART0_TXD */
	PAD_NF(GPIO_143, UART0_TXD, PULL_NONE),
	/* FANOUT0 */
	PAD_NF(GPIO_85, FANOUT0, PULL_NONE),

	/* I2C0 SCL */
	PAD_NF(GPIO_145, I2C0_SCL, PULL_NONE),
	/* I2C0 SDA */
	PAD_NF(GPIO_146, I2C0_SDA, PULL_NONE),
	/* I2C1 SCL */
	PAD_NF(GPIO_147, I2C1_SCL, PULL_NONE),
	/* I2C1 SDA */
	PAD_NF(GPIO_148, I2C1_SDA, PULL_NONE),
	/* I2C2_SCL */
	PAD_NF(GPIO_113, I2C2_SCL, PULL_NONE),
	/* I2C2_SDA */
	PAD_NF(GPIO_114, I2C2_SDA, PULL_NONE),
	/* I2C3_SCL */
	PAD_NF(GPIO_19, I2C3_SCL, PULL_NONE),
	/* I2C3_SDA */
	PAD_NF(GPIO_20, I2C3_SDA, PULL_NONE),
};

void mainboard_program_early_gpios(void)
{
	gpio_configure_pads(gpio_set_stage_reset, ARRAY_SIZE(gpio_set_stage_reset));
}
