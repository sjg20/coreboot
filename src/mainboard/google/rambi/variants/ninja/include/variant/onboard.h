/* SPDX-License-Identifier: GPL-2.0-only */
/* This file is part of the coreboot project. */

#ifndef ONBOARD_H
#define ONBOARD_H

#include <mainboard/google/rambi/irqroute.h>

#ifndef __ACPI__
void lan_init(void);
#endif

/* defines for programming the MAC address */
#define NINJA_NIC_VENDOR_ID			0x10EC
#define NINJA_NIC_DEVICE_ID			0x8168

/* 0x00: White LINK LED and Amber ACTIVE LED */
#define NINJA_NIC_LED_MODE			0x00

/* PCH wake signal from EC. */
#define BOARD_PCH_WAKE_GPIO             ACPI_ENABLE_WAKE_SUS_GPIO(0)

#define BOARD_CODEC_IRQ                 GPIO_S5_DED_IRQ(CODEC_IRQ_OFFSET)

#endif
