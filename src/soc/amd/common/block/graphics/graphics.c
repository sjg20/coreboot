/* SPDX-License-Identifier: GPL-2.0-or-later */

#include <acpi/acpi_device.h>
#include <acpi/acpigen.h>
#include <device/pci.h>
#include <device/pci_ids.h>

#define ATIF_FUNCTION_VERIFY_INTERFACE 0x0
struct atif_verify_interface_output {
	uint16_t size; /* Size of this object, including size field */
	uint16_t version;
	uint32_t supported_notifications;
	uint32_t supported_functions; /* Bit n set if function n+1 supported. */
};

#define ATIF_FUNCTION_QUERY_BRIGHTNESS_TRANSFER_CHARACTERISTICS    0x10
# define ATIF_QBTC_REQUEST_LCD1                              0
/* error codes */
# define ATIF_QBTC_ERROR_CODE_SUCCESS                        0
# define ATIF_QBTC_ERROR_CODE_FAILURE                        1
# define ATIF_QBTC_ERROR_CODE_DEVICE_NOT_SUPPORTED           2
struct atif_brightness_input {
	uint16_t size;
	/* ATIF doc indicates this field is a word, but the kernel drivers uses a byte. */
	uint8_t requested_display;
};
struct atif_brightness_output {
	uint16_t size; /* Size of this object, including size field. */
	uint16_t flags; /* Currently all reserved. */
	uint8_t error_code;
	/* default brightness fields currently ignored by Linux driver. */
	uint8_t default_brightness_ac; /* Percentage brightness when connected to AC. */
	uint8_t default_brightness_dc; /* Percentage brightness when connected to DC. */
	/* The following 2 fields are the only ones honored by Linux driver currently. */
	uint8_t min_input_signal_level; /* 0-255 corresponding to 0% */
	uint8_t max_input_signal_level; /* 0-255 corresponding to 100% */
	/* Array of data points consisting of:
	 *  { uint8_t luminance_level; (percent)
	 *    uint8_t input_signal_level; (0-255 in value) }
	 * Linux ignores these fields so no support currently. */
	uint8_t count_data_points; /* Count of data points. */
};

static void generate_atif(const struct device *dev)
{
	struct atif_verify_interface_output verify_output = {
		.size = sizeof(verify_output),
		.version = 1,
		.supported_functions =
			BIT(ATIF_FUNCTION_QUERY_BRIGHTNESS_TRANSFER_CHARACTERISTICS - 1),
	};
	struct atif_brightness_output brightness_error = {
		.size = sizeof(brightness_error),
		.error_code = ATIF_QBTC_ERROR_CODE_DEVICE_NOT_SUPPORTED,
	};
	struct atif_brightness_output brightness_out = {
		.size = sizeof(brightness_out),
		.error_code = ATIF_QBTC_ERROR_CODE_SUCCESS,
		.min_input_signal_level = 0,
		.max_input_signal_level = 255,
	};

	/* Scope (\_SB.PCI0.PBRA.IGFX) */
	acpigen_write_scope(acpi_device_path(dev));
	/* Method (ATIF, 2, NotSerialized) */
	acpigen_write_method("ATIF", 2);
	/* ToInteger (Arg0, Local0) */
	acpigen_write_to_integer(ARG0_OP, LOCAL0_OP);

	/* If ((Local0 == Zero)) */
	acpigen_write_if_lequal_op_int(LOCAL0_OP, ATIF_FUNCTION_VERIFY_INTERFACE);
	/* Return (Buffer (0x0C) { ... } */
	acpigen_write_return_byte_buffer((uint8_t *)(void *)&verify_output,
		sizeof(verify_output));
	acpigen_pop_len(); /* if (LEqual(Local0, 0) */

	/* ElseIf ((Local0 == 0x10)) */
	acpigen_write_else();
	acpigen_write_if_lequal_op_int(LOCAL0_OP,
		ATIF_FUNCTION_QUERY_BRIGHTNESS_TRANSFER_CHARACTERISTICS);
	/* CreateByteField (Arg1, 0x02, DISP) */
	acpigen_write_create_byte_field(ARG1_OP,
		offsetof(struct atif_brightness_input, requested_display), "DISP");
	/* ToInteger (DISP, Local1) */
	acpigen_write_to_integer_from_namestring("DISP", LOCAL1_OP);
	/* If ((Local1 == Zero)) */
	acpigen_write_if_lequal_op_int(LOCAL1_OP, ATIF_QBTC_REQUEST_LCD1);
	/* Return (Buffer (0x0A) { ... } */
	acpigen_write_return_byte_buffer((uint8_t *)(void *)&brightness_out,
		sizeof(brightness_out));
	acpigen_pop_len(); /* if (LEqual(Local2, ATIF_QBTC_REQUEST_LCD1) */
	/* Else */
	acpigen_write_else();
	/* Return (Buffer (0x0A) */
	acpigen_write_return_byte_buffer((uint8_t *)(void *)&brightness_error,
		sizeof(brightness_error));
	acpigen_pop_len(); /* else */

	acpigen_pop_len(); /* if (LEqual(Local0, 0x10) */
	acpigen_pop_len(); /* else */

	acpigen_pop_len(); /* Method */
	acpigen_pop_len(); /* Scope */
}

static void graphics_fill_ssdt(const struct device *dev)
{
	acpi_device_write_pci_dev(dev);
	pci_rom_ssdt(dev);
	if (CONFIG(SOC_AMD_COMMON_BLOCK_GRAPHICS_ATIF))
		generate_atif(dev);
}

static const char *graphics_acpi_name(const struct device *dev)
{
	return "IGFX";
}

static const struct device_operations graphics_ops = {
	.read_resources		= pci_dev_read_resources,
	.set_resources		= pci_dev_set_resources,
	.enable_resources	= pci_dev_enable_resources,
	.init			= pci_dev_init,
	.ops_pci		= &pci_dev_ops_pci,
	.write_acpi_tables	= pci_rom_write_acpi_tables,
	.acpi_fill_ssdt		= graphics_fill_ssdt,
	.acpi_name		= graphics_acpi_name,
};

static const unsigned short pci_device_ids[] = {
	PCI_DEVICE_ID_ATI_FAM17H_GPU,
	0,
};

static const struct pci_driver graphics_driver __pci_driver = {
	.ops		= &graphics_ops,
	.vendor		= PCI_VENDOR_ID_ATI,
	.devices	= pci_device_ids,
};
