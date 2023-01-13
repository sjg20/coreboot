/* SPDX-License-Identifier: GPL-2.0-or-later */

#include <acpi/acpigen.h>

#include "chip.h"

static const char *conn_acpi_name(const struct device *dev)
{
	static char name[5];
	snprintf(name, sizeof(name), "CON%1X", dev->path.generic.id);
	return name;
}

static void conn_fill_ssdt(const struct device *dev)
{
	const struct ec_google_chromeec_mux_conn_config *config = dev->chip_info;
	const char *name;
	name = acpi_device_name(dev);
	if (!name)
		return;

	acpigen_write_scope(acpi_device_scope(dev));
	acpigen_write_device(name);

	acpigen_write_name_integer("_ADR", dev->path.generic.id);

	if (config) {
		struct acpi_dp *dsd = acpi_dp_new_table("_DSD");

		if (config->mode_switch)
			acpi_dp_add_integer(dsd, "mode-switch", 1);
		if (config->retimer_switch)
			acpi_dp_add_integer(dsd, "retimer-switch", 1);

		acpi_dp_write(dsd);
	}

	acpigen_write_device_end();
	acpigen_write_scope_end();
}

static struct device_operations conn_dev_ops = {
	.read_resources	= noop_read_resources,
	.set_resources	= noop_set_resources,
	.acpi_name	= conn_acpi_name,
	.acpi_fill_ssdt	= conn_fill_ssdt,
};

static void conn_enable(struct device *dev)
{
	dev->ops = &conn_dev_ops;
}

struct chip_operations ec_google_chromeec_mux_conn_ops = {
	CHIP_NAME("CrosEC Type C Mux device")
	.enable_dev	= conn_enable,
};
