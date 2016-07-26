/*
 * This file is part of the coreboot project.
 *
 * Copyright 2016 Google Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <arch/acpi.h>
#include <boardid.h>
#include <console/console.h>
#include <device/device.h>
#include <nhlt.h>
#include <soc/gpio.h>
#include <soc/nhlt.h>
#include <vendorcode/google/chromeos/chromeos.h>
#include "ec.h"
#include "gpio.h"

static void mainboard_init(void *chip_info)
{
	int boardid;

	boardid = board_id();
	printk(BIOS_INFO, "Board ID: %d\n", boardid);

	gpio_configure_pads(gpio_table, ARRAY_SIZE(gpio_table));

	/* Apply proto board settings if board matches. */
	if (boardid == 0)
		gpio_configure_pads(proto_diff_table,
					ARRAY_SIZE(proto_diff_table));
	else
		gpio_configure_pads(nonproto_diff_table,
					ARRAY_SIZE(nonproto_diff_table));

	mainboard_ec_init();
}

static unsigned long mainboard_write_acpi_tables(
	device_t device, unsigned long current, acpi_rsdp_t *rsdp)
{
	uintptr_t start_addr;
	uintptr_t end_addr;
	struct nhlt *nhlt;

	start_addr = current;

	nhlt = nhlt_init();

	if (nhlt == NULL)
		return start_addr;

	/* 2 Channel DMIC array. */
	if (!nhlt_soc_add_dmic_array(nhlt, 2))
		printk(BIOS_ERR, "Added 2CH DMIC array.\n");

	/* Dialog for Headset codec.
	 * Headset codec is bi-directional but uses the same configuration
	 * settings for render and capture endpoints.
	 */
	if (!nhlt_soc_add_da7219(nhlt, AUDIO_LINK_SSP1))
		printk(BIOS_ERR, "Added Dialog_7219 codec.\n");

	/* MAXIM Smart Amps for left and right speakers. */
	if (!nhlt_soc_add_max98357(nhlt, AUDIO_LINK_SSP5))
		printk(BIOS_ERR, "Added Maxim_98357 codec.\n");

	end_addr = nhlt_soc_serialize(nhlt, start_addr);

	if (end_addr != start_addr)
		acpi_add_table(rsdp, (void *)start_addr);

	return end_addr;
}

static void mainboard_enable(device_t dev)
{
	dev->ops->write_acpi_tables = mainboard_write_acpi_tables;
	dev->ops->acpi_inject_dsdt_generator = chromeos_dsdt_generator;
}

struct chip_operations mainboard_ops = {
	.init = mainboard_init,
	.enable_dev = mainboard_enable,
};
