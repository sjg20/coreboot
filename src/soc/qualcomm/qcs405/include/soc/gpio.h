/* This file is part of the coreboot project. */
/* SPDX-License-Identifier: GPL-2.0-only */

#ifndef _SOC_QUALCOMM_QCS405_GPIO_H_
#define _SOC_QUALCOMM_QCS405_GPIO_H_

#include <types.h>
#include <soc/addressmap.h>

typedef struct {
	u32 addr;
} gpio_t;

#define TLMM_TILE_SIZE		0x00400000
#define TLMM_GPIO_OFF_DELTA	0x00001000
#define TLMM_GPIO_TILE_NUM	3

#define TLMM_GPIO_IN_OUT_OFF	0x4
#define TLMM_GPIO_ID_STATUS_OFF	0x10


/* GPIO INTR CFG MASK */
#define GPIO_INTR_DECT_CTL_MASK		0x3
#define GPIO_INTR_RAW_STATUS_EN_MASK	0x1

/* GPIO INTR CFG SHIFT */
#define GPIO_INTR_DECT_CTL_SHIFT	2
#define GPIO_INTR_RAW_STATUS_EN_SHIFT	4

/* GPIO INTR STATUS MASK */
#define GPIO_INTR_STATUS_MASK		0x1

/* GPIO INTR RAW STATUS */
#define GPIO_INTR_RAW_STATUS_ENABLE	1
#define GPIO_INTR_RAW_STATUS_DISABLE	0

/* GPIO INTR STATUS */
#define GPIO_INTR_STATUS_ENABLE		1
#define GPIO_INTR_STATUS_DISABLE	0

/* GPIO TLMM: Direction */
#define GPIO_INPUT	0
#define GPIO_OUTPUT	1

/* GPIO TLMM: Pullup/Pulldown */
#define GPIO_NO_PULL	0
#define GPIO_PULL_DOWN	1
#define GPIO_KEEPER	2
#define GPIO_PULL_UP	3

/* GPIO TLMM: Drive Strength */
#define GPIO_2MA	0
#define GPIO_4MA	1
#define GPIO_6MA	2
#define GPIO_8MA	3
#define GPIO_10MA	4
#define GPIO_12MA	5
#define GPIO_14MA	6
#define GPIO_16MA	7

/* GPIO TLMM: Status */
#define GPIO_DISABLE	0
#define GPIO_ENABLE	1

/* GPIO TLMM: Mask */
#define GPIO_CFG_PULL_BMSK	0x3
#define GPIO_CFG_FUNC_BMSK	0xF
#define GPIO_CFG_DRV_BMSK	0x7
#define GPIO_CFG_OE_BMSK	0x1

/* GPIO TLMM: Shift */
#define GPIO_CFG_PULL_SHFT	0
#define GPIO_CFG_FUNC_SHFT	2
#define GPIO_CFG_DRV_SHFT	6
#define GPIO_CFG_OE_SHFT	9

/* GPIO IO: Mask */
#define GPIO_IO_IN_BMSK		0x1
#define GPIO_IO_OUT_BMSK	0x1

/* GPIO IO: Shift */
#define GPIO_IO_IN_SHFT		0
#define GPIO_IO_OUT_SHFT	1

/* GPIO ID STATUS: Mask */
#define GPIO_ID_STATUS_BMSK	0x1

/* GPIO MAX Valid # */
#define GPIO_NUM_MAX		149

#define GPIO_FUNC_GPIO		0

#define GPIO(num) ((gpio_t){.addr = GPIO##num##_ADDR})

#define PIN(index, tlmm, func1, func2, func3, func4, func5, func6, func7) \
GPIO##index##_ADDR = TLMM_##tlmm##_TILE_BASE + index * TLMM_GPIO_OFF_DELTA, \
GPIO##index##_FUNC_##func1 = 1,	\
GPIO##index##_FUNC_##func2 = 2, \
GPIO##index##_FUNC_##func3 = 3, \
GPIO##index##_FUNC_##func4 = 4, \
GPIO##index##_FUNC_##func5 = 5, \
GPIO##index##_FUNC_##func6 = 6, \
GPIO##index##_FUNC_##func7 = 7

enum {
	PIN(0, SOUTH,	RES_1, RES_2, RES_3, RES_4, RES_5, RES_6, RES_7),
	PIN(1, SOUTH,	RES_1, RES_2, RES_3, RES_4, RES_5, RES_6, RES_7),
	PIN(2, SOUTH,	RES_1, RES_2, RES_3, RES_4, RES_5, RES_6, RES_7),
	PIN(3, SOUTH,	RES_1, RES_2, RES_3, RES_4, RES_5, RES_6, RES_7),
	PIN(4, SOUTH,	RES_1, RES_2, RES_3, RES_4, RES_5, RES_6, RES_7),
	PIN(5, SOUTH,	RES_1, RES_2, RES_3, RES_4, RES_5, RES_6, RES_7),
	PIN(6, SOUTH,	RES_1, RES_2, RES_3, RES_4, RES_5, RES_6, RES_7),
	PIN(7, SOUTH,	RES_1, RES_2, RES_3, RES_4, RES_5, RES_6, RES_7),
	PIN(8, SOUTH,	RES_1, RES_2, RES_3, RES_4, RES_5, RES_6, RES_7),
	PIN(9, SOUTH,	RES_1, RES_2, RES_3, RES_4, RES_5, RES_6, RES_7),
	PIN(10, SOUTH,	RES_1, RES_2, RES_3, RES_4, RES_5, RES_6, RES_7),
	PIN(11, SOUTH,	RES_1, RES_2, RES_3, RES_4, RES_5, RES_6, RES_7),
	PIN(12, SOUTH,	RES_1, RES_2, RES_3, RES_4, RES_5, RES_6, RES_7),
	PIN(13, SOUTH,	RES_1, RES_2, RES_3, RES_4, RES_5, RES_6, RES_7),
	PIN(14, SOUTH,	RES_1, RES_2, RES_3, RES_4, RES_5, RES_6, RES_7),
	PIN(15, SOUTH,	RES_1, RES_2, RES_3, RES_4, RES_5, RES_6, RES_7),
	PIN(16, SOUTH,	RES_1, RES_2, RES_3, RES_4, RES_5, RES_6, RES_7),
	PIN(17, NORTH,	BLSP_UART_TX_A, BLSP_SPI_MOSI, RES_3, RES_4, RES_5,
		RES_6, RES_7),
	PIN(18, NORTH,	BLSP_UART_RX_A, BLSP_SPI_MISO, RES_3, RES_4, RES_5,
		RES_6, RES_7),
	PIN(19, NORTH,	BLSP_UART_CTS_N, AUD_CDC_INT2, RES_3, BLSP_SPI_CS_N,
		RES_5, RES_6, RES_7),
	PIN(20, NORTH,	BLSP_UART_RFR_N, RES_2, RES_3, BLSP_SPI_CLK, RES_5,
		RES_6, RES_7),
	PIN(21, SOUTH,	M_VOC_EXT_VFR_REF_IRQ_2, RES_2, RES_3, RES_4,
		RES_5, RES_6, RES_7),
	PIN(22, NORTH,	BLSP_UART_TX, BLSP_SPI_MOSI_A, ASDIV1, RES_4,
		RES_5, RES_6, RES_7),
	PIN(23, NORTH,	BLSP_UART_RX, BLSP_SPI_MISO_A, ASDIV2, RES_4,
		RES_5, RES_6, RES_7),
	PIN(24, NORTH,	BLSP_UART_CTS_N, BLSP_I2C_SDA, BLSP_SPI_CS_N_A,
		RES_4, RES_5, RES_6, RES_7),
	PIN(25, NORTH,	BLSP_UART_RFR_N, BLSP_I2C_SCL, BLSP_SPI_CLK_A,
		RES_4, RES_5, RES_6, RES_7),
	PIN(26, EAST,	RES_1, BLSP_UART_TX, BLSP_SPI_MOSI, RES_4, RES_5,
		RES_6, RES_7),
	PIN(27, EAST,	RES_1, BLSP_UART_RX, BLSP_SPI_MISO, RES_4, RES_5,
		RES_6, RES_7),
	PIN(28, EAST,	RES_1, BLSP_UART_CTS_N, RES_3, BLSP_SPI_CS_N, RES_5,
		RES_6, RES_7),
	PIN(29, EAST,	RES_1, BLSP_UART_RFR_N, RES_3, BLSP_SPI_CLK, RES_5,
		RES_6, RES_7),
	PIN(30, NORTH,	RES_1, BLSP_UART_TX, RES_3, RES_4, RES_5, RES_6,
		RES_7),
	PIN(31, NORTH,	RES_1, BLSP_UART_RX, RES_3, RES_4, RES_5, RES_6,
		RES_7),
	PIN(32, NORTH,	RES_1, BLSP_UART_CTS_N, BLSP_I2C_SDA, RES_4, RES_5,
		RES_6, RES_7),
	PIN(33, NORTH,	RES_1, BLSP_UART_RFR_N, BLSP_I2C_SCL, RES_4, RES_5,
		RES_6, RES_7),
	PIN(34, SOUTH,	RES_1, RES_2, RES_3, RES_4, RES_5, RES_6, RES_7),
	PIN(35, SOUTH,	PCIE_CLK_REQ, RES_2, RES_3, RES_4, RES_5, RES_6,
		RES_7),
	PIN(36, NORTH,	RES_1, RES_2, RES_3, RES_4, RES_5, RES_6, RES_7),
	PIN(37, NORTH,	NFC_IRQ, BLSP_SPI_MOSI, RES_3, RES_4, RES_5, RES_6,
		RES_7),
	PIN(38, NORTH,	RES_1, BLSP_SPI_MISO, AUDIO_TS_IN, RES_4, RES_5,
		RES_6, RES_7),
	PIN(39, EAST,	RES_1, RES_2, BLSP_UART_TX_B, RES_4, RES_5, RES_6,
		RES_7),
	PIN(40, EAST,	RES_1, RES_2, BLSP_UART_RX_B, RES_4, RES_5, RES_6,
		RES_7),
	PIN(41, EAST,	RES_1, BLSP_I2C_SDA_B, RES_3, RES_4, RES_5, RES_6,
		RES_7),
	PIN(42, EAST,	RES_1, BLSP_I2C_SCL_B, RES_3, RES_4, RES_5, RES_6,
		RES_7),
	PIN(43, EAST,	RES_1, PWM_LED11, RES_3, RES_4, RES_5, RES_6, RES_7),
	PIN(44, EAST,	RES_1, PWM_LED12, BLSP_SPI_CS1_N, RES_4, RES_5,
		RES_6, RES_7),
	PIN(45, EAST,	RES_1, PWM_LED13, BLSP_SPI_CS2_N, RES_4, RES_5,
		RES_6, RES_7),
	PIN(46, EAST,	RES_1, PWM_LED14, BLSP_SPI_CS3_N, RES_4, RES_5,
		RES_6, RES_7),
	PIN(47, EAST,	RES_1, PWM_LED15, BLSP_SPI_MOSI_B, RES_4, RES_5,
		RES_6, RES_7),
	PIN(48, EAST,	RES_1, PWM_LED16, BLSP_SPI_MISO_B, RES_4, RES_5,
		RES_6, RES_7),
	PIN(49, EAST,	RES_1, PWM_LED17, BLSP_SPI_CS_N_B, RES_4, RES_5,
		RES_6, RES_7),
	PIN(50, EAST,	RES_1, PWM_LED18, BLSP_SPI_CLK_B, RES_4, RES_5,
		RES_6, RES_7),
	PIN(51, EAST,	RES_1, PWM_LED19, EXT_MCLK1_B, RES_4, RES_5, RES_6,
		RES_7),
	PIN(52, EAST,	RES_1, PWM_LED20, RES_3, I2S_3_SCK_B, RES_5, RES_6,
		RES_7),
	PIN(53, EAST,	RES_1, PWM_LED21, I2S_3_WS_B, RES_4, RES_5, RES_6,
		RES_7),
	PIN(54, EAST,	RES_1, I2S_3_DATA0_B, RES_3, RES_4, RES_5, RES_6,
		RES_7),
	PIN(55, EAST,	RES_1, I2S_3_DATA1_B, RES_3, RES_4, RES_5, RES_6,
		RES_7),
	PIN(56, EAST,	RES_1, RES_2, I2S_3_DATA2_B, RES_4, RES_5, RES_6,
		RES_7),
	PIN(57, EAST,	RES_1, RES_2, I2S_3_DATA3_B, RES_4, RES_5, RES_6,
		RES_7),
	PIN(58, EAST,	RGB_DATA_B, RES_2, RES_3, RES_4, RES_5, RES_6,
		RES_7),
	PIN(59, EAST,	RGB_DATA_B, RES_2, RES_3, RES_4, RES_5, RES_6,
		RES_7),
	PIN(60, NORTH,	RES_1, RES_2, RES_3, RES_4, RES_5, RES_6, RES_7),
	PIN(61, NORTH,	RGMII_INT, RES_2, RES_3, RES_4, RES_5, RES_6,
		RES_7),
	PIN(62, NORTH,	RES_1, RES_2, RES_3, RES_4, RES_5, RES_6, RES_7),
	PIN(63, NORTH,	RGMII_CK_TX, RES_2, RES_3, RES_4, RES_5, RES_6,
		RES_7),
	PIN(64, NORTH,	RGMII_TX_3, RES_2, RES_3, RES_4, RES_5, RES_6,
		RES_7),
	PIN(65, NORTH,	RGMII_TX_2, RES_2, RES_3, RES_4, RES_5, RES_6,
		RES_7),
	PIN(66, NORTH,	RGMII_TX_1, RES_2, RES_3, RES_4, RES_5, RES_6,
		RES_7),
	PIN(67, NORTH,	RGMII_TX_0, RES_2, RES_3, RES_4, RES_5, RES_6,
		RES_7),
	PIN(68, NORTH,	RGMII_CTL_TX, RES_2, RES_3, RES_4, RES_5, RES_6,
		RES_7),
	PIN(69, NORTH,	RGMII_CK_RX, RES_2, RES_3, RES_4, RES_5, RES_6,
		RES_7),
	PIN(70, NORTH,	RGMII_RX_3, RES_2, RES_3, RES_4, RES_5, RES_6,
		RES_7),
	PIN(71, NORTH,	RGMII_RX_2, RES_2, RES_3, RES_4, RES_5, RES_6,
		RES_7),
	PIN(72, NORTH,	RGMII_RX_1, RES_2, RES_3, RES_4, RES_5, RES_6,
		RES_7),
	PIN(73, NORTH,	RGMII_RX_0, RES_2, RES_3, RES_4, RES_5, RES_6,
		RES_7),
	PIN(74, NORTH,	RGMII_CTL_RX, RES_2, RES_3, RES_4, RES_5, RES_6,
		RES_7),
	PIN(75, NORTH,	RGMII_MDIO, RES_2, RES_3, RES_4, RES_5, RES_6,
		RES_7),
	PIN(76, NORTH,	RGMII_MDC, RES_2, RES_3, RES_4, RES_5, RES_6,
		RES_7),
	PIN(77, NORTH,	IR_IN, RES_2, RES_3, RES_4, RES_5, RES_6, RES_7),
	PIN(78, EAST,	RGB_DATA_G, RES_2, RES_3, RES_4, RES_5, RES_6,
		RES_7),
	PIN(79, EAST,	RGB_DATA_G, RES_2, RES_3, RES_4, RES_5, RES_6,
		RES_7),
	PIN(80, EAST,	RGB_DATA_R, RES_2, RES_3, RES_4, RES_5, RES_6,
		RES_7),
	PIN(81, EAST,	RGB_DATA_R, RES_2, RES_3, RES_4, RES_5, RES_6,
		RES_7),
	PIN(82, NORTH,	BLSP_UART_TX, BLSP_SPI_MOSI, SD_WRITE_PROTECT,
		RES_4, RES_5, RES_6, RES_7),
	PIN(83, NORTH,	BLSP_UART_RX, BLSP_SPI_MISO, RES_3, RES_4, RES_5,
		RES_6, RES_7),
	PIN(84, NORTH,	BLSP_UART_CTS_N, BLSP_I2C_SDA, BLSP_SPI_CS_N,
		RES_4, RES_5, RES_6, RES_7),
	PIN(85, NORTH,	BLSP_UART_RFR_N, BLSP_I2C_SCL, BLSP_SPI_CLK, RES_4,
		RES_5, RES_6, RES_7),
	PIN(86, EAST,	RES_1, MCLK_IN1, RES_3, RES_4, RES_5, RES_6, RES_7),
	PIN(87, EAST,	I2S_1_SCK, DSD_CLK_A, RES_3, RES_4, RES_5, RES_6,
		RES_7),
	PIN(88, EAST,	I2S_1_WS, I2S_1_DATA0_DSD0, RES_3, RES_4, RES_5,
		RES_6, RES_7),
	PIN(89, EAST,	I2S_1_DATA0, I2S_1_DATA1_DSD1, RES_3, RES_4, RES_5,
		RES_6, RES_7),
	PIN(90, EAST,	I2S_1_DATA1, I2S_1_DATA2_DSD2, RES_3, RES_4, RES_5,
		RES_6, RES_7),
	PIN(91, EAST,	I2S_1_DATA2, I2S_1_DATA3_DSD3, RES_3, RES_4, RES_5,
		RES_6, RES_7),
	PIN(92, EAST,	I2S_1_DATA3, I2S_1_DATA4_DSD4, RES_3, RES_4, RES_5,
		RES_6, RES_7),
	PIN(93, EAST,	I2S_1_DATA4, PWM_LED22, I2S_1_DATA5_DSD5, RES_4,
		RES_5, RES_6, RES_7),
	PIN(94, EAST,	I2S_1_DATA5, PWM_LED23, I2S_1_DATA6_MIR, RES_4,
		RES_5, RES_6, RES_7),
	PIN(95, EAST,	RES_1, PWM_LED1, I2S_1_DATA7_MIR, RES_4, RES_5,
		RES_6, RES_7),
	PIN(96, EAST,	RES_1, PWM_LED2, RES_3, RES_4, RES_5, RES_6, RES_7),
	PIN(97, EAST,	RES_1, RES_2, RES_3, RES_4, RES_5, RES_6, RES_7),
	PIN(98, EAST,	RES_1, RES_2, RES_3, RES_4, RES_5, RES_6, RES_7),
	PIN(99, EAST,	RES_1, RES_2, RES_3, RES_4, RES_5, RES_6, RES_7),
	PIN(100, EAST,	RES_1, RES_2, RES_3, RES_4, RES_5, RES_6, RES_7),
	PIN(101, EAST,	RES_1, RES_2, RES_3, RES_4, RES_5, RES_6, RES_7),
	PIN(102, EAST,	RES_1, RES_2, RES_3, RES_4, RES_5, RES_6, RES_7),
	PIN(103, EAST,	RES_1, MCLK_IN2, RES_3, RES_4, RES_5, RES_6, RES_7),
	PIN(104, EAST,	I2S_3_SCK_A, RES_2, RES_3, RES_4, RES_5, RES_6,
		RES_7),
	PIN(105, EAST,	I2S_3_WS_A, RES_2, RES_3, RES_4, RES_5, RES_6,
		RES_7),
	PIN(106, EAST,	I2S_3_DATA0_A, RES_2, HDMI_HOT_PLUG_MIR, RES_4,
		RES_5, RES_6, RES_7),
	PIN(107, EAST,	I2S_3_DATA1_A, RES_2, RES_3, RES_4, RES_5, RES_6,
		RES_7),
	PIN(108, EAST,	I2S_3_DATA2_A, RES_2, RES_3, PWM_LED3, RES_5,
		RES_6, RES_7),
	PIN(109, EAST,	I2S_3_DATA3_A, RES_2, PWM_LED4, RES_4, RES_5,
		RES_6, RES_7),
	PIN(110, EAST,	RES_1, RES_2, DSD_CLK_B, PWM_LED5, RES_5, RES_6,
		RES_7),
	PIN(111, EAST,	RES_1, I2S_4_DATA0_DSD0, PWM_LED6, RES_4, RES_5,
		RES_6, RES_7),
	PIN(112, EAST,	RES_1, I2S_4_DATA1_DSD1, PWM_LED7, RES_4, RES_5,
		RES_6, RES_7),
	PIN(113, EAST,	RES_1, I2S_4_DATA2_DSD2, PWM_LED8, RES_4, RES_5,
		RES_6, RES_7),
	PIN(114, EAST,	RES_1, I2S_4_DATA3_DSD3, PWM_LED24, RES_4, RES_5,
		RES_6, RES_7),
	PIN(115, EAST,	RES_1, I2S_4_DATA4_DSD4, RES_3, RES_4, RES_5,
		RES_6, RES_7),
	PIN(116, EAST,	I2S_4_DATA5_DSD5, SPKR_DAC0, RES_3, RES_4, RES_5,
		RES_6, RES_7),
	PIN(117, NORTH,	BLSP_I2C_SDA, BLSP_SPI_CS_N, PWM_LED9, RES_4,
		RES_5, RES_6, RES_7),
	PIN(118, NORTH,	BLSP_I2C_SCL, BLSP_SPI_CLK, PWM_LED10, RES_4,
		RES_5, RES_6, RES_7),
	PIN(119, EAST,	RES_1, RES_2, RES_3, RES_4, RES_5, RES_6, RES_7),
};

enum gpio_irq_type {
	IRQ_TYPE_LEVEL = 0,
	IRQ_TYPE_RISING_EDGE = 1,
	IRQ_TYPE_FALLING_EDGE = 2,
	IRQ_TYPE_DUAL_EDGE = 3,
};

struct tlmm_gpio {
	uint32_t cfg;
	uint32_t in_out;
	uint32_t intr_cfg;
	uint32_t intr_status;
};

void gpio_configure(gpio_t gpio, uint32_t func, uint32_t pull,
				uint32_t drive_str, uint32_t enable);
void gpio_input_irq(gpio_t gpio, enum gpio_irq_type type, uint32_t pull);
int gpio_irq_status(gpio_t gpio);

#endif // _SOC_QUALCOMM_QCS405_GPIO_H_
