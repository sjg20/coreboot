/* SPDX-License-Identifier: GPL-2.0-only */
/* This file is part of the coreboot project. */

#include <arch/acpi.h>
#include <baseboard/variants.h>
#include <boardid.h>
#include <console/console.h>
#include <device/device.h>
#include <ec/ec.h>
#include <nhlt.h>
#include <soc/gpio.h>
#include <soc/nhlt.h>
#include <vendorcode/google/chromeos/chromeos.h>
#include <variant/ec.h>
#include <variant/gpio.h>

static void mainboard_init(void *chip_info)
{
	int boardid;
	const struct pad_config *pads;
	size_t num;

	boardid = board_id();
	printk(BIOS_INFO, "Board ID: %d\n", boardid);

	pads = variant_gpio_table(&num);
	gpio_configure_pads(pads, num);

	mainboard_ec_init();
}

static unsigned long mainboard_write_acpi_tables(
	struct device *device, unsigned long current, acpi_rsdp_t *rsdp)
{
	uintptr_t start_addr;
	uintptr_t end_addr;
	struct nhlt *nhlt;

	start_addr = current;

	nhlt = nhlt_init();

	if (nhlt == NULL)
		return start_addr;

	variant_nhlt_init(nhlt);

	end_addr = nhlt_soc_serialize(nhlt, start_addr);

	if (end_addr != start_addr)
		acpi_add_table(rsdp, (void *)start_addr);

	return end_addr;
}

static void mainboard_enable(struct device *dev)
{
	dev->ops->write_acpi_tables = mainboard_write_acpi_tables;
	dev->ops->acpi_inject_dsdt = chromeos_dsdt_generator;
}

struct chip_operations mainboard_ops = {
	.init = mainboard_init,
	.enable_dev = mainboard_enable,
};
