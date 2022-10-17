/* SPDX-License-Identifier: GPL-2.0-only */

#ifndef AMD_STONEYRIDGE_I2C_H
#define AMD_STONEYRIDGE_I2C_H

#include <types.h>
#include <soc/gpio.h>

#define GPIO_I2C0_SCL			BIT(0)
#define GPIO_I2C1_SCL			BIT(1)
#define GPIO_I2C2_SCL			BIT(2)
#define GPIO_I2C3_SCL			BIT(3)
#define GPIO_I2C_MASK			(BIT(0) | BIT(1) | BIT(2) | BIT(3))

#define I2C0_SCL_PIN			GPIO_145
#define I2C1_SCL_PIN			GPIO_147
#define I2C2_SCL_PIN			GPIO_113
#define I2C3_SCL_PIN			GPIO_19

#define I2C0_SCL_PIN_IOMUX_GPIOxx	GPIO_145_IOMUX_GPIOxx
#define I2C1_SCL_PIN_IOMUX_GPIOxx	GPIO_147_IOMUX_GPIOxx
#define I2C2_SCL_PIN_IOMUX_GPIOxx	GPIO_113_IOMUX_GPIOxx
#define I2C3_SCL_PIN_IOMUX_GPIOxx	GPIO_19_IOMUX_GPIOxx

void reset_i2c_peripherals(void);

#endif /* AMD_STONEYRIDGE_I2C_H */
