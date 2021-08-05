/* SPDX-License-Identifier: GPL-2.0-or-later */

#include <acpi/acpi_device.h>
#include <acpi/acpigen.h>
#include <console/console.h>
#include <device/path.h>
#include <string.h>
#include "chip.h"

static bool uart_acpi_add_gpios_to_crs(struct drivers_uart_acpi_config *config)
{
	/*
	 * Return false if:
	 * 1. Request to explicitly disable export of GPIOs in CRS, or
	 * 2. Both reset and enable GPIOs are not provided.
	 */
	if (config->disable_gpio_export_in_crs ||
	    ((config->reset_gpio.pin_count == 0) &&
	     (config->enable_gpio.pin_count == 0)))
		return false;

	return true;
}

static int uart_acpi_write_gpio(struct acpi_gpio *gpio, int *curr_index)
{
	int ret = -1;

	if (gpio->pin_count == 0)
		return ret;

	acpi_device_write_gpio(gpio);
	ret = *curr_index;
	(*curr_index)++;

	return ret;
}

static void uart_acpi_fill_ssdt(const struct device *dev)
{
	const char *scope = acpi_device_scope(dev);
	const char *path = acpi_device_path(dev);
	struct drivers_uart_acpi_config *config = dev->chip_info;
	int curr_index = 0;
	int irq_gpio_index = -1;
	int reset_gpio_index = -1;
	int enable_gpio_index = -1;

	if (!scope)
		return;

	if (!config->hid) {
		printk(BIOS_ERR, "%s: ERROR: HID required\n", dev_path(dev));
		return;
	}

	acpigen_write_scope(scope);
	acpigen_write_device(acpi_device_name(dev));

	acpigen_write_name_string("_HID", config->hid);
	if (config->cid)
		acpigen_write_name_string("_CID", config->cid);
	acpigen_write_name_integer("_UID", config->uid);
	acpigen_write_name_string("_DDN", config->desc);
	acpigen_write_STA(acpi_device_status(dev));

	/* Resources */
	acpigen_write_name("_CRS");
	acpigen_write_resourcetemplate_header();

	/* Fix up resource pointer to this scope */
	config->uart.resource = scope;
	acpi_device_write_uart(&config->uart);

	/* Use either Interrupt() or GpioInt() */
	if (config->irq_gpio.pin_count)
		acpi_device_write_gpio(&config->irq_gpio);
	else
		acpi_device_write_interrupt(&config->irq);

	/* Add enable/reset GPIOs if needed */
	if (uart_acpi_add_gpios_to_crs(config)) {
		reset_gpio_index = uart_acpi_write_gpio(&config->reset_gpio,
							&curr_index);
		enable_gpio_index = uart_acpi_write_gpio(&config->enable_gpio,
							 &curr_index);
	}
	acpigen_write_resourcetemplate_footer();

	/* Wake capabilities */
	if (config->wake) {
		acpigen_write_name_integer("_S0W", ACPI_DEVICE_SLEEP_D3_HOT);
		acpigen_write_PRW(config->wake, SLP_TYP_S3);
	};

	/* Write device properties if needed */
	if (config->compat_string || irq_gpio_index >= 0 ||
	    reset_gpio_index >= 0 || enable_gpio_index >= 0) {
		struct acpi_dp *dsd = acpi_dp_new_table("_DSD");
		if (config->compat_string)
			acpi_dp_add_string(dsd, "compatible",
					   config->compat_string);
		if (irq_gpio_index >= 0)
			acpi_dp_add_gpio(dsd, "irq-gpios", path,
					 irq_gpio_index, 0,
					 config->irq_gpio.active_low);
		if (reset_gpio_index >= 0)
			acpi_dp_add_gpio(dsd, "reset-gpios", path,
					 reset_gpio_index, 0,
					 config->reset_gpio.active_low);
		if (enable_gpio_index >= 0)
			acpi_dp_add_gpio(dsd, "enable-gpios", path,
					 enable_gpio_index, 0,
					 config->enable_gpio.active_low);
		acpi_dp_write(dsd);
	}

	/* Power Resource */
	if (config->has_power_resource) {
		const struct acpi_power_res_params power_res_params = {
			&config->reset_gpio,
			config->reset_delay_ms,
			config->reset_off_delay_ms,
			&config->enable_gpio,
			config->enable_delay_ms,
			config->enable_off_delay_ms,
			&config->stop_gpio,
			config->stop_delay_ms,
			config->stop_off_delay_ms
		};
		acpi_device_add_power_res(&power_res_params);
	}

	acpigen_pop_len(); /* Device */
	acpigen_pop_len(); /* Scope */

	printk(BIOS_INFO, "%s: %s at %s\n", path, config->desc, dev_path(dev));
}

static const char *uart_acpi_name(const struct device *dev)
{
	struct drivers_uart_acpi_config *config = dev->chip_info;
	static char name[5];

	if (config->name)
		return config->name;

	snprintf(name, sizeof(name), "D%03.3X", dev->path.generic.id);
	return name;
}

static struct device_operations uart_acpi_dev_ops = {
	.read_resources	= noop_read_resources,
	.set_resources	= noop_set_resources,
	.acpi_fill_ssdt	= uart_acpi_fill_ssdt,
	.acpi_name	= uart_acpi_name,
};

static void uart_acpi_enable(struct device *dev)
{
	struct drivers_uart_acpi_config *config = dev->chip_info;

	if (config->desc)
		dev->name = config->desc;
	else
		config->desc = dev->chip_ops->name;

	dev->ops = &uart_acpi_dev_ops;
}

struct chip_operations drivers_uart_acpi_ops = {
	CHIP_NAME("ACPI UART Device")
	.enable_dev = uart_acpi_enable
};
