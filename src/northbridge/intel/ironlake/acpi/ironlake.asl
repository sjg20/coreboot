/* SPDX-License-Identifier: GPL-2.0-only */
/* This file is part of the coreboot project. */

#include "../ironlake.h"
#include "hostbridge.asl"
#include <southbridge/intel/common/rcba.h>

/* PCI Device Resource Consumption */
Device (PDRC)
{
	Name (_HID, EISAID("PNP0C02"))
	Name (_UID, 1)

	Name (PDRS, ResourceTemplate() {
		Memory32Fixed(ReadWrite, DEFAULT_RCBA, 0x00004000)
		Memory32Fixed(ReadWrite, DEFAULT_MCHBAR,   0x00008000)
		Memory32Fixed(ReadWrite, DEFAULT_DMIBAR,   0x00001000)
		Memory32Fixed(ReadWrite, DEFAULT_EPBAR,    0x00001000)
		Memory32Fixed(ReadWrite, CONFIG_MMCONF_BASE_ADDRESS, 0x04000000)
		Memory32Fixed(ReadWrite, 0xfed20000, 0x00020000) // Misc ICH
		Memory32Fixed(ReadWrite, 0xfed40000, 0x00005000) // Misc ICH
		Memory32Fixed(ReadWrite, 0xfed45000, 0x0004b000) // Misc ICH

#if CONFIG(CHROMEOS_RAMOOPS)
		Memory32Fixed(ReadWrite, CONFIG_CHROMEOS_RAMOOPS_RAM_START,
					 CONFIG_CHROMEOS_RAMOOPS_RAM_SIZE)
#endif

		/* Required for SandyBridge sighting 3715511 */
		Memory32Fixed(ReadWrite, 0x20000000, 0x00200000)
		Memory32Fixed(ReadWrite, 0x40000000, 0x00200000)
	})

	// Current Resource Settings
	Method (_CRS, 0, Serialized)
	{
		Return(PDRS)
	}
}
