/* This file is part of the coreboot project. */
/* SPDX-License-Identifier: GPL-2.0-only */

#include <device/device.h>
#include <device/mmio.h>
#include <gpio.h>
#include <timestamp.h>
#include <soc/usb.h>

static struct usb_board_data usb0_board_data = {
	.pll_bias_control_2 = 0x22,
	.imp_ctrl1 = 0x08,
	.port_tune1 = 0xc5,
};

static void setup_usb(void)
{
	setup_usb_host0(&usb0_board_data);
}

static void mainboard_init(struct device *dev)
{
	setup_usb();
}

static void mainboard_enable(struct device *dev)
{
	dev->ops->init = &mainboard_init;
}

struct chip_operations mainboard_ops = {
	.name = CONFIG_MAINBOARD_PART_NUMBER,
	.enable_dev = mainboard_enable,
};
