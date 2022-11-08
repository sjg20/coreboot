/* SPDX-License-Identifier: GPL-2.0-or-later */

#ifndef __VARIANT_EC_H__
#define __VARIANT_EC_H__

#include <baseboard/ec.h>

#undef MAINBOARD_EC_SCI_EVENTS
#define MAINBOARD_EC_SCI_EVENTS \
	(EC_HOST_EVENT_MASK(EC_HOST_EVENT_LID_CLOSED)        |\
	 EC_HOST_EVENT_MASK(EC_HOST_EVENT_LID_OPEN)          |\
	 EC_HOST_EVENT_MASK(EC_HOST_EVENT_AC_CONNECTED)      |\
	 EC_HOST_EVENT_MASK(EC_HOST_EVENT_AC_DISCONNECTED)   |\
	 EC_HOST_EVENT_MASK(EC_HOST_EVENT_BATTERY_LOW)       |\
	 EC_HOST_EVENT_MASK(EC_HOST_EVENT_BATTERY_CRITICAL)  |\
	 EC_HOST_EVENT_MASK(EC_HOST_EVENT_BATTERY)           |\
	 EC_HOST_EVENT_MASK(EC_HOST_EVENT_BATTERY_STATUS)    |\
	 EC_HOST_EVENT_MASK(EC_HOST_EVENT_THERMAL_THRESHOLD) |\
	 EC_HOST_EVENT_MASK(EC_HOST_EVENT_THROTTLE_START)    |\
	 EC_HOST_EVENT_MASK(EC_HOST_EVENT_THROTTLE_STOP)     |\
	 EC_HOST_EVENT_MASK(EC_HOST_EVENT_MKBP)              |\
	 EC_HOST_EVENT_MASK(EC_HOST_EVENT_PD_MCU)            |\
	 EC_HOST_EVENT_MASK(EC_HOST_EVENT_MODE_CHANGE)       |\
	 EC_HOST_EVENT_MASK(EC_HOST_EVENT_USB_MUX)           |\
	 EC_HOST_EVENT_MASK(EC_HOST_EVENT_DEVICE))
/*
 * EC can wake from S3/S0ix with:
 * 1. Lid open
 * 2. AC Connect/Disconnect
 * 3. Power button
 * 4. Key press
 * 5. Mode change
 * 6. Host Device
 */
#undef MAINBOARD_EC_S3_WAKE_EVENTS
#define MAINBOARD_EC_S3_WAKE_EVENTS \
	(MAINBOARD_EC_S5_WAKE_EVENTS |\
	 EC_HOST_EVENT_MASK(EC_HOST_EVENT_AC_CONNECTED)    |\
	 EC_HOST_EVENT_MASK(EC_HOST_EVENT_AC_DISCONNECTED) |\
	 EC_HOST_EVENT_MASK(EC_HOST_EVENT_KEY_PRESSED)     |\
	 EC_HOST_EVENT_MASK(EC_HOST_EVENT_MODE_CHANGE)     |\
	 EC_HOST_EVENT_MASK(EC_HOST_EVENT_DEVICE))

/* Enable EC backed Keyboard Backlight in ACPI */
#define EC_ENABLE_KEYBOARD_BACKLIGHT

#endif
