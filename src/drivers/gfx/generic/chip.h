/*
 * This file is part of the coreboot project.
 *
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

#ifndef __DRIVERS_GFX_GENERIC_CHIP_H__
#define __DRIVERS_GFX_GENERIC_CHIP_H__

#include <arch/acpi_device.h>

/* Config for electronic privacy screen */
struct drivers_gfx_generic_privacy_screen_config {
	/* Is privacy screen available on this graphics device */
	int enabled;
	/* ACPI namespace path to privacy screen detection function */
	const char *detect_function;
	/* ACPI namespace path to privacy screen status function */
	const char *status_function;
	/* ACPI namespace path to privacy screen enable function */
	const char *enable_function;
	/* ACPI namespace path to privacy screen disable function */
	const char *disable_function;
	/*
	 * GPIO used for controlling the privacy screen. If provided,
	 * the gpio mechanism takes preference over the functions ptrs
	 * above, if any (GPIO functions override the function ptrs).
	 */
	struct acpi_gpio gpio;
};

/* Config for an output device as defined in section A.5 of the ACPI spec */
struct drivers_gfx_generic_device_config {
	/* ACPI device name of the output device */
	const char *name;
	/* The address of the output device. See section A.3.2 */
	unsigned int addr;
	/* Electronic privacy screen specific config */
	struct drivers_gfx_generic_privacy_screen_config privacy;
};

/* Config for an ACPI video device defined in Appendix A of the ACPI spec */
struct drivers_gfx_generic_config {
	/*
	 * ACPI device name of the graphics card, "GFX0" will be used if name is
	 * not set
	 */
	const char *name;
	/* The number of output devices defined */
	int device_count;
	/* Config for output devices */
	struct drivers_gfx_generic_device_config device[5];
};

extern struct device *find_gfx_dev(void);

#endif /* __DRIVERS_GFX_GENERIC_CHIP_H__ */
