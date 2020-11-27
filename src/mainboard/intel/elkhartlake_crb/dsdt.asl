/* SPDX-License-Identifier: GPL-2.0-only */

#include <acpi/acpi.h>
#include <baseboard/ec.h>
#include <baseboard/gpio.h>

DefinitionBlock(
	"dsdt.aml",
	"DSDT",
	ACPI_DSDT_REV_2,
	OEM_ID,
	ACPI_TABLE_CREATOR,
	0x20110725	/* OEM revision */
)
{
	#include <soc/intel/common/block/acpi/acpi/platform.asl>

	/* global NVS and variables */
	#include <soc/intel/common/block/acpi/acpi/globalnvs.asl>

	/* CPU */
	#include <cpu/intel/common/acpi/cpu.asl>

	Scope (\_SB) {
		Device (PCI0)
		{
			#include <soc/intel/common/block/acpi/acpi/northbridge.asl>
			#include <soc/intel/elkhartlake/acpi/southbridge.asl>
		}
	}

	#include <southbridge/intel/common/acpi/sleepstates.asl>
}
