/* SPDX-License-Identifier: GPL-2.0-only */

#include <baseboard/gpio.h>
#include <baseboard/variants.h>
#include <device/device.h>
#include <soc/gpio.h>
#include <vendorcode/google/chromeos/chromeos.h>
#include <smbios.h>
#include <string.h>

const char *smbios_system_sku(void)
{
	static char sku_str[7] = ""; /* sku{0..255} */
	uint32_t sku_id = 255;

	snprintf(sku_str, sizeof(sku_str), "sku%u", sku_id);
	return sku_str;
}

static void mainboard_init(void *chip_info)
{
	const struct pad_config *pads;
	size_t num;

	pads = variant_gpio_table(&num);
	gpio_configure_pads(pads, num);
}

static void mainboard_enable(struct device *dev)
{
	dev->ops->acpi_inject_dsdt = chromeos_dsdt_generator;
}

struct chip_operations mainboard_ops = {
	.init = mainboard_init,
	.enable_dev = mainboard_enable,
};
