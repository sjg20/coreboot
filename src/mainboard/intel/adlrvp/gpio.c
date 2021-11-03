/* SPDX-License-Identifier: GPL-2.0-only */

#include <baseboard/gpio.h>
#include <baseboard/variants.h>
#include <commonlib/helpers.h>
#include <vendorcode/google/chromeos/chromeos.h>

/* Pad configuration in ramstage*/
static const struct pad_config gpio_table[] = {
	/* SSD1_PWREN  CPU SSD1 */
	PAD_CFG_GPO(GPP_D14, 1, PLTRST),
	/* SSD1_RESET  CPU SSD1 */
	PAD_CFG_GPO(GPP_F20, 1, PLTRST),
	/* BT_RF_KILL_N */
	PAD_CFG_GPO(GPP_A13, 1, PLTRST),
	/* WLAN RST# */
	PAD_CFG_GPO(GPP_H2, 1, PLTRST),
	/* WIFI_WAKE_N */
	PAD_CFG_GPI_IRQ_WAKE(GPP_D13, NONE, DEEP, LEVEL, INVERT),
	/* x4 PCIE slot1 PWREN */
	PAD_CFG_GPO(GPP_H17, 0, PLTRST),
	/* x4 PCIE slot 1 RESET */
	PAD_CFG_GPO(GPP_F10, 1, PLTRST),
	/* Retimer Force Power */
	PAD_CFG_GPO(GPP_E4, 0, PLTRST),
	/* PEG Slot RST# */
	PAD_CFG_GPO(GPP_B2, 1, PLTRST),
	/* M.2 SSD_2 Reset */
	PAD_CFG_GPO(GPP_H0, 1, PLTRST),
	/* CAM_STROBE */
	PAD_CFG_GPO(GPP_B18, 0, PLTRST),
	/* Audio Codec INT N */
	PAD_CFG_GPI_APIC(GPP_H3, NONE, PLTRST, LEVEL, INVERT),
	/* TCH PAD Power EN */
	PAD_CFG_GPO(GPP_F7, 1, PLTRST),
	/* THC1 SPI2 RST# */
	PAD_CFG_GPO(GPP_F17, 1, PLTRST),
	/* THC1_SPI2_INTB */
	PAD_CFG_GPI_APIC(GPP_F18, NONE, PLTRST, EDGE_SINGLE, INVERT),
	/* THC1_SPI2_INTB */
	PAD_CFG_GPI(GPP_E17, NONE, PLTRST),
	/* EC_SLP_S0_CS_N */
	PAD_CFG_GPO(GPP_F9, 1, PLTRST),
	/* WIFI RF KILL */
	PAD_CFG_GPO(GPP_E3, 1, PLTRST),
	/* DISP_AUX_N_BIAS_GPIO */
	PAD_CFG_GPO(GPP_E23, 1, PLTRST),
	/* WWAN WAKE N*/
	PAD_CFG_GPI_IRQ_WAKE(GPP_D18, NONE, DEEP, LEVEL, INVERT),
	/* WWAN_DISABLE_N */
	PAD_CFG_GPO(GPP_D15, 1, PLTRST),
	/* WWAN_RST# */
	PAD_CFG_GPO(GPP_F14, 1, PLTRST),
	/* WWAN_PWR_EN */
	PAD_CFG_GPO(GPP_F21, 1, DEEP),
	/* WWAN_PERST# */
	PAD_CFG_GPO(GPP_C5, 1, PLTRST),
	/* PEG_SLOT_WAKE_N */
	PAD_CFG_GPI(GPP_A20, NONE, PLTRST),
	/* CAM CONN1 CLKEN */
	PAD_CFG_GPO(GPP_H15, 1, PLTRST),
	/* CPU SSD2 PWREN */
	PAD_CFG_GPO(GPP_C2, 1, PLTRST),
	/* CPU SSD2 RST# */
	PAD_CFG_GPO(GPP_H1, 1, PLTRST),
	/* Sata direct Power */
	PAD_CFG_GPO(GPP_B4, 1, PLTRST),
	/* M.2_PCH_SSD_PWREN */
	PAD_CFG_GPO(GPP_D16, 1, PLTRST),
	/* SRCCLK_OEB7 */
	PAD_CFG_GPO(GPP_A7, 0, PLTRST),
	/* SRCCLK_OEB6 */
	PAD_CFG_GPO(GPP_E5, 0, PLTRST),

	/* CAM1_RST */
	PAD_CFG_GPO(GPP_R5, 1, PLTRST),
	/* CAM2_RST */
	PAD_CFG_GPO(GPP_E15, 1, PLTRST),
	/* CAM1_PWR_EN */
	PAD_CFG_GPO(GPP_B23, 1, PLTRST),
	/* CAM2_PWR_EN */
	PAD_CFG_GPO(GPP_E16, 1, PLTRST),
	/* M.2_SSD_PDET_R */
	PAD_CFG_NF(GPP_A12, NONE, DEEP, NF1),
	/* THC0 SPI1 CLK */
	PAD_CFG_NF(GPP_E11, NONE, DEEP, NF2),
	/* THC0 SPI1 IO 1 */
	PAD_CFG_NF(GPP_E12, NONE, DEEP, NF2),
	/* THC0 SPI1 IO 2 */
	PAD_CFG_NF(GPP_E1, NONE, DEEP, NF2),
	/* THC0 SPI IO 3 */
	PAD_CFG_NF(GPP_E2, NONE, DEEP, NF2),
	/* THC1 SPI1 RSTB */
	PAD_CFG_NF(GPP_E6, NONE, DEEP, NF2),
	/* UART_RX(1) */
	PAD_CFG_NF(GPP_C12, NONE, DEEP, NF1),
	/* UART_RX(2) */
	PAD_CFG_NF(GPP_C20, NONE, DEEP, NF1),
	/* UART_RX(4) */
	PAD_CFG_NF(GPP_T4, NONE, DEEP, NF1),
	/* UART_RX(5) */
	PAD_CFG_NF(GPP_T8, NONE, DEEP, NF1),
	/* UART_RX(6) */
	PAD_CFG_NF(GPP_T12, NONE, DEEP, NF1),

	/* UART_TX(1) */
	PAD_CFG_NF(GPP_C13, NONE, DEEP, NF1),
	/* UART_TX(2) */
	PAD_CFG_NF(GPP_C21, NONE, DEEP, NF1),
	/* UART_TX(4) */
	PAD_CFG_NF(GPP_T5, NONE, DEEP, NF1),
	/* UART_TX(5) */
	PAD_CFG_NF(GPP_T9, NONE, DEEP, NF1),
	/* UART_TX(6) */
	PAD_CFG_NF(GPP_T13, NONE, DEEP, NF1),

	/* UART_RTS(1) */
	PAD_CFG_NF(GPP_C14, NONE, DEEP, NF1),
	/* UART_RTS(2) */
	PAD_CFG_NF(GPP_C22, NONE, DEEP, NF1),
	/* UART_RTS(4) */
	PAD_CFG_NF(GPP_T6, NONE, DEEP, NF1),
	/* UART_RTS(5) */
	PAD_CFG_NF(GPP_T10, NONE, DEEP, NF1),
	/* UART_RTS(6) */
	PAD_CFG_NF(GPP_T14, NONE, DEEP, NF1),

	/* UART_CTS(1) */
	PAD_CFG_NF(GPP_C15, NONE, DEEP, NF1),
	/* UART_CTS(2) */
	PAD_CFG_NF(GPP_C23, NONE, DEEP, NF1),
	/* UART_CTS(4) */
	PAD_CFG_NF(GPP_T7, NONE, DEEP, NF1),
	/* UART_CTS(5) */
	PAD_CFG_NF(GPP_T11, NONE, DEEP, NF1),
	/* UART_CTS(6) */
	PAD_CFG_NF(GPP_T15, NONE, DEEP, NF1),

	/* SPI_MOSI(1) */
	PAD_CFG_NF(GPP_B22, NONE, DEEP, NF1),
	/* SPI_MOSI(2) */
	PAD_CFG_NF(GPP_D12, NONE, DEEP, NF2),

	/* SPI_MIS0(1) */
	PAD_CFG_NF(GPP_B21, NONE, DEEP, NF1),
	/* SPI_MIS0(2) */
	PAD_CFG_NF(GPP_D11, NONE, DEEP, NF2),

	/* SPI_CLK(1) */
	PAD_CFG_NF(GPP_B20, NONE, DEEP, NF1),
	/* SPI_CLK(2) */
	PAD_CFG_NF(GPP_D10, NONE, DEEP, NF2),

	/* SPI_CS(0, 1) */
	PAD_CFG_NF(GPP_B14, NONE, DEEP, NF1),
	/* SPI_CS(1, 0) */
	PAD_CFG_NF(GPP_B19, NONE, DEEP, NF1),
	/* SPI_CS(2, 0) */
	PAD_CFG_NF(GPP_D9, NONE, DEEP, NF2),

	/* I2C_SCL(0) */
	PAD_CFG_NF(GPP_H5, NONE, DEEP, NF1),
	/* I2C_SCL(1) */
	PAD_CFG_NF(GPP_H7, NONE, DEEP, NF1),
	/* I2C_SCL(2) */
	PAD_CFG_NF(GPP_B6, NONE, DEEP, NF2),
	/* I2C_SCL(3) */
	PAD_CFG_NF(GPP_B8, NONE, DEEP, NF2),
	/* I2C_SCL(5) */
	PAD_CFG_NF(GPP_B17, NONE, DEEP, NF2),

	/* I2C_SDA(0) */
	PAD_CFG_NF(GPP_H4, NONE, DEEP, NF1),
	/* I2C_SDA(1) */
	PAD_CFG_NF(GPP_H6, NONE, DEEP, NF1),
	/* I2C_SDA(2) */
	PAD_CFG_NF(GPP_B5, NONE, DEEP, NF2),
	/* I2C_SDA(3) */
	PAD_CFG_NF(GPP_B7, NONE, DEEP, NF2),
	/* I2C_SDA(5) */
	PAD_CFG_NF(GPP_B16, NONE, DEEP, NF2),

	/* I2S0_SCLK */
	PAD_CFG_NF(GPP_R0, NONE, DEEP, NF2),
	/* I2S0_SFRM */
	PAD_CFG_NF(GPP_R1, NONE, DEEP, NF2),
	/* I2S0_TXD */
	PAD_CFG_NF(GPP_R2, NONE, DEEP, NF2),
	/* I2S0_RXD */
	PAD_CFG_NF(GPP_R3, NONE, DEEP, NF2),

	/* I2S2_SCLK */
	PAD_CFG_NF(GPP_A7, NONE, DEEP, NF1),
	/* I2S2_SFRM */
	PAD_CFG_NF(GPP_A8, NONE, DEEP, NF1),
	/* I2S2_TXD */
	PAD_CFG_NF(GPP_A9, NONE, DEEP, NF1),
	/* I2S2_RXD */
	PAD_CFG_NF(GPP_A10, NONE, DEEP, NF1),

	/* I2S_MCLK1_OUT */
	PAD_CFG_NF(GPP_D19, NONE, DEEP, NF1),
	/* I2S_MCLK2_INOUT */
	PAD_CFG_NF(GPP_F8, NONE, DEEP, NF1),

	/* SNDW1_CLK */
	PAD_CFG_NF(GPP_S0, NONE, DEEP, NF1),
	/* SNDW1_DATA */
	PAD_CFG_NF(GPP_S1, NONE, DEEP, NF1),
	/* SNDW2_CLK */
	PAD_CFG_NF(GPP_S2, NONE, DEEP, NF2),
	/* SNDW2_DATA */
	PAD_CFG_NF(GPP_S3, NONE, DEEP, NF2),
	/* SNDW3_CLK */
	PAD_CFG_NF(GPP_S4, NONE, DEEP, NF2),
	/* SNDW3_DATA */
	PAD_CFG_NF(GPP_S5, NONE, DEEP, NF2),
	/* SNDW4_CLK */
	PAD_CFG_NF(GPP_S6, NONE, DEEP, NF2),
	/* SNDW4_DATA */
	PAD_CFG_NF(GPP_S7, NONE, DEEP, NF2),

	/* SMB_CLK */
	PAD_CFG_NF(GPP_C0, NONE, DEEP, NF1),
	/* SMB_DATA */
	PAD_CFG_NF(GPP_C1, NONE, DEEP, NF1),

	/* SATA DEVSLP */
	PAD_CFG_NF(GPP_H12, NONE, DEEP, NF4),
	PAD_CFG_NF(GPP_H13, NONE, DEEP, NF5),

	/* SATA LED pin */
	PAD_CFG_NF(GPP_E8, NONE, DEEP, NF1),

	/* USB2 OC0 pins */
	PAD_CFG_NF(GPP_E9, NONE, DEEP, NF1),
	/* USB2 OC3 pins */
	PAD_CFG_NF(GPP_A16, NONE, DEEP, NF1),

	/* GPIO pin for PCIE SRCCLKREQB */
	PAD_CFG_NF(GPP_D5, NONE, DEEP, NF1),
	PAD_CFG_NF(GPP_D6, NONE, DEEP, NF1),
	PAD_CFG_NF(GPP_D7, NONE, DEEP, NF1),
	PAD_NC(GPP_D8, NONE),
	PAD_CFG_NF(GPP_H19, NONE, DEEP, NF1),
	PAD_CFG_NF(GPP_F19, NONE, DEEP, NF1),

	/* DDP1/2/3/4/A/B/C  CTRLCLK and CTRLDATA pins */
	PAD_CFG_NF(GPP_E18, NONE, DEEP, NF4),
	PAD_CFG_NF(GPP_E19, NONE, DEEP, NF4),
	PAD_CFG_NF(GPP_E20, NONE, DEEP, NF4),
	PAD_CFG_NF(GPP_E21, NONE, DEEP, NF4),
	PAD_CFG_NF(GPP_E22, NONE, DEEP, NF2),
	PAD_CFG_NF(GPP_A21, NONE, DEEP, NF2),
	PAD_CFG_NF(GPP_A22, NONE, DEEP, NF2),

	/* HPD_1 (E14) and HPD_2 (A18) pins */
	PAD_CFG_NF(GPP_E14, NONE, DEEP, NF1),
	PAD_CFG_NF(GPP_A18, NONE, DEEP, NF1),

	/* IMGCLKOUT */
	PAD_CFG_NF(GPP_D4, NONE, DEEP, NF1),
	PAD_CFG_NF(GPP_H20, NONE, DEEP, NF1),
	PAD_CFG_NF(GPP_H21, NONE, DEEP, NF1),
	PAD_CFG_NF(GPP_H22, NONE, DEEP, NF1),
	PAD_NC(GPP_H23, NONE),

	/* A21 : HDMI CRLS CTRLCLK */
	PAD_CFG_NF(GPP_A21, NONE, DEEP, NF1),
	/* A22 : HDMI CRLS CTRLDATA */
	PAD_CFG_NF(GPP_A22, NONE, DEEP, NF1),
};

void variant_configure_gpio_pads(void)
{
	gpio_configure_pads(gpio_table, ARRAY_SIZE(gpio_table));
}

static const struct cros_gpio cros_gpios[] = {
	CROS_GPIO_REC_AL(CROS_GPIO_VIRTUAL, CROS_GPIO_DEVICE_NAME),
};

const struct cros_gpio *variant_cros_gpios(size_t *num)
{
	*num = ARRAY_SIZE(cros_gpios);
	return cros_gpios;
}
