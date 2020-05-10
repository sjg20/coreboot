/* SPDX-License-Identifier: GPL-2.0-only */

#ifndef __USB_ACPI_CHIP_H__
#define __USB_ACPI_CHIP_H__

#include <acpi/acpi_device.h>
#include <acpi/acpi.h>
#include <acpi/acpi_pld.h>

struct drivers_usb_acpi_config {
	const char *desc;

	/*
	 * Physical ports that are user visible
	 *
	 * UPC_TYPE_A
	 * UPC_TYPE_MINI_AB
	 * UPC_TYPE_EXPRESSCARD
	 * UPC_TYPE_USB3_A
	 * UPC_TYPE_USB3_B
	 * UPC_TYPE_USB3_MICRO_B
	 * UPC_TYPE_USB3_MICRO_AB
	 * UPC_TYPE_USB3_POWER_B
	 * UPC_TYPE_C_USB2_ONLY
	 * UPC_TYPE_C_USB2_SS_SWITCH
	 * UPC_TYPE_C_USB2_SS
	 *
	 * Non-visible ports or special devices
	 *
	 * UPC_TYPE_PROPRIETARY
	 * UPC_TYPE_INTERNAL
	 * UPC_TYPE_UNUSED
	 * UPC_TYPE_HUB
	 */
	enum acpi_upc_type type;

	/* Group peer ports */
	struct acpi_pld_group group;

	/*
	 * Define a custom physical location for the port.
	 * If enabled, this takes precedence over the 'group' field.
	 */
	bool use_custom_pld;
	struct acpi_pld custom_pld;

	struct acpi_gpio reset_gpio;
};

#endif /* __USB_ACPI_CHIP_H__ */
