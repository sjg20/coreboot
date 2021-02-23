/* SPDX-License-Identifier: GPL-2.0-or-later */

#ifndef __MAINBOARD_EC_H__
#define __MAINBOARD_EC_H__

#include <ec/ec.h>
#include <ec/google/chromeec/ec_commands.h>
#include <baseboard/gpio.h>

#define MAINBOARD_EC_SCI_EVENTS                                                                \
	(EC_HOST_EVENT_MASK(EC_HOST_EVENT_LID_CLOSED)                                          \
	 | EC_HOST_EVENT_MASK(EC_HOST_EVENT_LID_OPEN)                                          \
	 | EC_HOST_EVENT_MASK(EC_HOST_EVENT_AC_CONNECTED)                                      \
	 | EC_HOST_EVENT_MASK(EC_HOST_EVENT_AC_DISCONNECTED)                                   \
	 | EC_HOST_EVENT_MASK(EC_HOST_EVENT_BATTERY_LOW)                                       \
	 | EC_HOST_EVENT_MASK(EC_HOST_EVENT_BATTERY_CRITICAL)                                  \
	 | EC_HOST_EVENT_MASK(EC_HOST_EVENT_BATTERY)                                           \
	 | EC_HOST_EVENT_MASK(EC_HOST_EVENT_BATTERY_STATUS)                                    \
	 | EC_HOST_EVENT_MASK(EC_HOST_EVENT_THERMAL_THRESHOLD)                                 \
	 | EC_HOST_EVENT_MASK(EC_HOST_EVENT_THROTTLE_START)                                    \
	 | EC_HOST_EVENT_MASK(EC_HOST_EVENT_THROTTLE_STOP)                                     \
	 | EC_HOST_EVENT_MASK(EC_HOST_EVENT_PD_MCU)                                            \
	 | EC_HOST_EVENT_MASK(EC_HOST_EVENT_MODE_CHANGE)                                       \
	 | EC_HOST_EVENT_MASK(EC_HOST_EVENT_USB_MUX))

#define MAINBOARD_EC_SMI_EVENTS (EC_HOST_EVENT_MASK(EC_HOST_EVENT_LID_CLOSED))

/* EC can wake from S5 with lid or power button */
#define MAINBOARD_EC_S5_WAKE_EVENTS                                                            \
	(EC_HOST_EVENT_MASK(EC_HOST_EVENT_LID_OPEN)                                            \
	 | EC_HOST_EVENT_MASK(EC_HOST_EVENT_POWER_BUTTON))

/* EC can wake from S3 with lid, power button or mode change event */
#define MAINBOARD_EC_S3_WAKE_EVENTS                                                            \
	(MAINBOARD_EC_S5_WAKE_EVENTS | EC_HOST_EVENT_MASK(EC_HOST_EVENT_AC_CONNECTED)          \
	 | EC_HOST_EVENT_MASK(EC_HOST_EVENT_AC_DISCONNECTED)                                   \
	 | EC_HOST_EVENT_MASK(EC_HOST_EVENT_KEY_PRESSED)                                       \
	 | EC_HOST_EVENT_MASK(EC_HOST_EVENT_MODE_CHANGE))

#define MAINBOARD_EC_S0IX_WAKE_EVENTS (MAINBOARD_EC_S3_WAKE_EVENTS)

/* Log EC wake events plus EC shutdown events */
#define MAINBOARD_EC_LOG_EVENTS                                                                \
	(EC_HOST_EVENT_MASK(EC_HOST_EVENT_THERMAL_SHUTDOWN)                                    \
	 | EC_HOST_EVENT_MASK(EC_HOST_EVENT_BATTERY_SHUTDOWN)                                  \
	 | EC_HOST_EVENT_MASK(EC_HOST_EVENT_PANIC))

#endif /* __MAINBOARD_EC_H__ */
