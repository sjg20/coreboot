/* SPDX-License-Identifier: GPL-2.0-only */

#ifndef MAINBOARD_EC_H
#define MAINBOARD_EC_H

#include <ec/ec.h>
#include <ec/google/chromeec/ec_commands.h>

/* GPIO_S0_000 is EC_SCI#, but it is bit 24 in GPE_STS */
#define EC_SCI_GPI   24
/* GPIO_S5_07 is EC_SMI#, but it is bit 23 in GPE_STS and ALT_GPIO_SMI. */
#define EC_SMI_GPI   23

#define MAINBOARD_EC_SCI_EVENTS \
	(EC_HOST_EVENT_MASK(EC_HOST_EVENT_LID_CLOSED)        |\
	 EC_HOST_EVENT_MASK(EC_HOST_EVENT_LID_OPEN)          |\
	 EC_HOST_EVENT_MASK(EC_HOST_EVENT_AC_CONNECTED)      |\
	 EC_HOST_EVENT_MASK(EC_HOST_EVENT_AC_DISCONNECTED)   |\
	 EC_HOST_EVENT_MASK(EC_HOST_EVENT_BATTERY_LOW)       |\
	 EC_HOST_EVENT_MASK(EC_HOST_EVENT_BATTERY_CRITICAL)  |\
	 EC_HOST_EVENT_MASK(EC_HOST_EVENT_BATTERY)           |\
	 EC_HOST_EVENT_MASK(EC_HOST_EVENT_THERMAL_THRESHOLD) |\
	 EC_HOST_EVENT_MASK(EC_HOST_EVENT_THROTTLE_START)    |\
	 EC_HOST_EVENT_MASK(EC_HOST_EVENT_THROTTLE_STOP)     |\
	 EC_HOST_EVENT_MASK(EC_HOST_EVENT_MKBP))

#define MAINBOARD_EC_SMI_EVENTS \
	(EC_HOST_EVENT_MASK(EC_HOST_EVENT_LID_CLOSED))

/* EC can wake from S5 with lid or power button */
#define MAINBOARD_EC_S5_WAKE_EVENTS \
	(EC_HOST_EVENT_MASK(EC_HOST_EVENT_LID_OPEN)     |\
	 EC_HOST_EVENT_MASK(EC_HOST_EVENT_POWER_BUTTON))

/* EC can wake from S3 with lid or power button or key press */
#define MAINBOARD_EC_S3_WAKE_EVENTS \
	(MAINBOARD_EC_S5_WAKE_EVENTS |\
	 EC_HOST_EVENT_MASK(EC_HOST_EVENT_KEY_PRESSED))

/* Log EC wake events plus EC shutdown events */
#define MAINBOARD_EC_LOG_EVENTS \
	(EC_HOST_EVENT_MASK(EC_HOST_EVENT_THERMAL_SHUTDOWN) |\
	 EC_HOST_EVENT_MASK(EC_HOST_EVENT_BATTERY_SHUTDOWN))

#endif
