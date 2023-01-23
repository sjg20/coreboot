/* SPDX-License-Identifier: GPL-2.0-or-later */

/*
 * NOTE: The layout of the global_nvs structure below must match the layout
 * in soc/soc/amd/picasso/acpi/globalnvs.asl !!!
 *
 */

#ifndef AMD_PICASSO_NVS_H
#define AMD_PICASSO_NVS_H

#include <stdint.h>
#include <soc/southbridge.h>

struct __packed global_nvs {
	/* Miscellaneous */
	uint8_t		lids; /* 0x00 - LID State */
	uint32_t	cbmc; /* 0x01 - 0x04 - coreboot Memory Console */
	uint64_t	pm1i; /* 0x05 - 0x0c - System Wake Source - PM1 Index */
	uint64_t	gpei; /* 0x0d - 0x14 - GPE Wake Source */
	uint8_t		tmps; /* 0x15 - Temperature Sensor ID */
	uint8_t		tcrt; /* 0x16 - Critical Threshold */
	uint8_t		tpsv; /* 0x17 - Passive Threshold */
};

#endif /* AMD_PICASSO_NVS_H */
