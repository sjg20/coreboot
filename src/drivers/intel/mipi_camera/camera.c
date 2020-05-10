/* SPDX-License-Identifier: GPL-2.0-only */

#include <acpi/acpi.h>
#include <acpi/acpi_device.h>
#include <acpi/acpigen.h>
#include <console/console.h>
#include <device/i2c_simple.h>
#include <device/device.h>
#include <device/path.h>
#include "chip.h"

static void camera_fill_ssdt(const struct device *dev)
{
	struct drivers_intel_mipi_camera_config *config = dev->chip_info;
	const char *scope = acpi_device_scope(dev);
	struct acpi_i2c i2c = {
		.address = dev->path.i2c.device,
		.mode_10bit = dev->path.i2c.mode_10bit,
		.speed = I2C_SPEED_FAST,
		.resource = scope,
	};

	if (!dev->enabled || !scope)
		return;

	/* Device */
	acpigen_write_scope(scope);
	acpigen_write_device(acpi_device_name(dev));
	acpigen_write_name_string("_HID", config->acpi_hid);
	acpigen_write_name_integer("_UID", config->acpi_uid);
	acpigen_write_name_string("_DDN", config->chip_name);
	acpigen_write_STA(acpi_device_status(dev));

	/* Resources */
	acpigen_write_name("_CRS");
	acpigen_write_resourcetemplate_header();
	acpi_device_write_i2c(&i2c);
	acpigen_write_resourcetemplate_footer();

	/* Mark it as Camera related device */
	acpigen_write_name_integer("CAMD", config->device_type);

	/* Create Device specific data */
	if (config->device_type == INTEL_ACPI_CAMERA_SENSOR) {
		acpigen_write_method_serialized("SSDB", 0);
		acpigen_write_return_byte_buffer((uint8_t *)&config->ssdb,
						sizeof(config->ssdb));
		acpigen_pop_len(); /* Method */
	}

	/* Fill Power Sequencing Data */
	acpigen_write_method_serialized("PWDB", 0);
	acpigen_write_return_byte_buffer((uint8_t *)&config->pwdb,
			(sizeof(struct intel_pwdb) * config->num_pwdb_entries));
	acpigen_pop_len(); /* Method */

	acpigen_pop_len(); /* Device */
	acpigen_pop_len(); /* Scope */
	printk(BIOS_INFO, "%s: %s address 0%xh\n", acpi_device_path(dev),
			dev->chip_ops->name, dev->path.i2c.device);
}

static const char *camera_acpi_name(const struct device *dev)
{
	struct drivers_intel_mipi_camera_config *config = dev->chip_info;
	return config->acpi_name;
}

static struct device_operations camera_ops = {
	.read_resources		= noop_read_resources,
	.set_resources		= noop_set_resources,
	.acpi_name		= camera_acpi_name,
	.acpi_fill_ssdt		= camera_fill_ssdt,
};

static void camera_enable(struct device *dev)
{
	dev->ops = &camera_ops;
}

struct chip_operations drivers_intel_mipi_camera_ops = {
	CHIP_NAME("Intel MIPI Camera Device")
	.enable_dev = camera_enable
};
