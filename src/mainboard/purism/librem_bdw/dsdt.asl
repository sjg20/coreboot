/* SPDX-License-Identifier: GPL-2.0-only */
/* This file is part of the coreboot project. */

#include <arch/acpi.h>
DefinitionBlock(
	"dsdt.aml",
	"DSDT",
	0x02,		/* DSDT revision: ACPI v2.0 and up */
	OEM_ID,
	ACPI_TABLE_CREATOR,
	0x20160115	/* OEM revision */
)
{
	#include <soc/intel/broadwell/acpi/platform.asl>

	/* Global NVS and variables */
	#include <soc/intel/broadwell/acpi/globalnvs.asl>

	/* CPU */
	#include <cpu/intel/common/acpi/cpu.asl>

	Scope (\_SB) {
		Device (PCI0)
		{
			#include <soc/intel/broadwell/acpi/systemagent.asl>
			#include <soc/intel/broadwell/acpi/pch.asl>
		}
	}

	#include <southbridge/intel/common/acpi/sleepstates.asl>

	/* Mainboard specific */
	#include "acpi/mainboard.asl"
}
