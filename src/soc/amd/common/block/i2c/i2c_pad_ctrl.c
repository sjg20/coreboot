/* SPDX-License-Identifier: GPL-2.0-only */

#include <amdblocks/acpimmio.h>
#include <amdblocks/i2c.h>
#include <console/console.h>
#include <types.h>
#include "i2c_pad_def.h"

void fch_i2c_pad_init(unsigned int bus,
		      enum i2c_speed speed,
		      const struct i2c_pad_control *ctrl)
{
	uint32_t pad_ctrl;

	pad_ctrl = misc_read32(MISC_I2C_PAD_CTRL(bus));

	pad_ctrl &= ~I2C_PAD_CTRL_NG_MASK;
	pad_ctrl |= I2C_PAD_CTRL_NG_NORMAL;

	switch (ctrl->rx_level) {
	case I2C_PAD_RX_NO_CHANGE:
		break;
	case I2C_PAD_RX_OFF:
		pad_ctrl &= ~I2C_PAD_CTRL_RX_SEL_MASK;
		pad_ctrl |= I2C_PAD_CTRL_RX_SEL_OFF;
		break;
	case I2C_PAD_RX_3_3V:
		pad_ctrl &= ~I2C_PAD_CTRL_RX_SEL_MASK;
		pad_ctrl |= I2C_PAD_CTRL_RX_SEL_3_3V;
		break;
	case I2C_PAD_RX_1_8V:
		pad_ctrl &= ~I2C_PAD_CTRL_RX_SEL_MASK;
		pad_ctrl |= I2C_PAD_CTRL_RX_SEL_1_8V;
		break;
	default:
		printk(BIOS_WARNING, "Invalid I2C pad RX level for bus %u\n", bus);
		break;
	}

	pad_ctrl &= ~I2C_PAD_CTRL_FALLSLEW_MASK;
	pad_ctrl |= speed == I2C_SPEED_STANDARD ?
		I2C_PAD_CTRL_FALLSLEW_STD : I2C_PAD_CTRL_FALLSLEW_LOW;
	pad_ctrl |= I2C_PAD_CTRL_FALLSLEW_EN;
	misc_write32(MISC_I2C_PAD_CTRL(bus), pad_ctrl);
}
