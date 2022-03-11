/* SPDX-License-Identifier: GPL-2.0-or-later */

#include <baseboard/variants.h>
#include <device/device.h>
#include <ec/ec.h>
#include <soc/ramstage.h>
#include <fw_config.h>
#include <acpi/acpigen.h>
#include <drivers/wwan/fm/chip.h>

WEAK_DEV_PTR(rp6_wwan);

static void add_fw_config_oem_string(const struct fw_config *config, void *arg)
{
	struct smbios_type11 *t;
	char buffer[64];

	t = (struct smbios_type11 *)arg;

	snprintf(buffer, sizeof(buffer), "%s-%s", config->field_name, config->option_name);
	t->count = smbios_add_string(t->eos, buffer);
}

static void mainboard_smbios_strings(struct device *dev, struct smbios_type11 *t)
{
	fw_config_for_each_found(add_fw_config_oem_string, t);
}

void mainboard_update_soc_chip_config(struct soc_intel_alderlake_config *config)
{
	variant_update_soc_chip_config(config);
}

__weak void variant_update_soc_chip_config(struct soc_intel_alderlake_config *config)
{
	/* default implementation does nothing */
}

static void mainboard_init(void *chip_info)
{
	const struct pad_config *base_pads;
	const struct pad_config *override_pads;
	size_t base_num, override_num;

	base_pads = variant_gpio_table(&base_num);
	override_pads = variant_gpio_override_table(&override_num);
	gpio_configure_pads_with_override(base_pads, base_num, override_pads, override_num);

	variant_devtree_update();
}

void __weak variant_devtree_update(void)
{
	/* Override dev tree settings per board */
}

static void mainboard_dev_init(struct device *dev)
{
	mainboard_ec_init();
}

static void mainboard_generate_shutdown(const struct device *dev)
{
	const struct drivers_wwan_fm_config *config = config_of(dev);
	const struct device *parent = dev->bus->dev;

	if (!config)
		return;
	if (config->rtd3dev) {
		acpigen_write_store();
		acpigen_emit_namestring(acpi_device_path_join(parent, "RTD3._STA"));
		acpigen_emit_byte(LOCAL0_OP);
		acpigen_write_if_lequal_op_int(LOCAL0_OP, ONE_OP);
		{
			acpigen_emit_namestring(acpi_device_path_join(dev, "DPTS"));
			acpigen_emit_byte(ARG0_OP);
		}
		acpigen_write_if_end();
	} else {
		acpigen_emit_namestring(acpi_device_path_join(dev, "DPTS"));
		acpigen_emit_byte(ARG0_OP);
	}
}

static void mainboard_fill_ssdt(const struct device *dev)
{
	const struct device *wwan = DEV_PTR(rp6_wwan);

	if (wwan) {
		acpigen_write_scope("\\_SB");
		acpigen_write_method_serialized("MPTS", 1);
		mainboard_generate_shutdown(wwan);
		acpigen_write_method_end(); /* Method */
		acpigen_write_scope_end(); /* Scope */
	}
	/* for variant to fill additional SSDT */
	variant_fill_ssdt(dev);
}

void __weak variant_fill_ssdt(const struct device *dev)
{
	/* Add board-specific SSDT entries */
}

static void mainboard_enable(struct device *dev)
{
	dev->ops->init = mainboard_dev_init;
	dev->ops->get_smbios_strings = mainboard_smbios_strings;
	dev->ops->acpi_fill_ssdt = mainboard_fill_ssdt;
}

struct chip_operations mainboard_ops = {
	.init = mainboard_init,
	.enable_dev = mainboard_enable,
};
