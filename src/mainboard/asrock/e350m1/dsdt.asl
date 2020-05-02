/* SPDX-License-Identifier: GPL-2.0-only */
/* This file is part of the coreboot project. */

/* DefinitionBlock Statement */
#include <acpi/acpi.h>
DefinitionBlock (
	"DSDT.AML",	/* Output filename */
	"DSDT",		/* Signature */
	0x02,		/* DSDT Revision, needs to be 2 for 64bit */
	OEM_ID,
	ACPI_TABLE_CREATOR,
	0x00010001	/* OEM Revision */
	)
{	/* Start of ASL file */
	/* #include <arch/x86/acpi/debug.asl> */	/* Include global debug methods if needed */

	#include "acpi/mainboard.asl"

	#include <cpu/amd/agesa/family14/acpi/cpu.asl>

	#include "acpi/routing.asl"

	Scope(\_SB) {
		/* global utility methods expected within the \_SB scope */
		#include <arch/x86/acpi/globutil.asl>

		Device(PCI0) {

			/* Describe the AMD Northbridge */
			#include <northbridge/amd/agesa/family14/acpi/northbridge.asl>

			/* Describe the AMD Fusion Controller Hub Southbridge */
			#include <southbridge/amd/cimx/sb800/acpi/fch.asl>

		}
	}   /* End Scope(_SB)  */

	#include "acpi/superio.asl"

	/* Contains the supported sleep states for this chipset */
	#include <southbridge/amd/common/acpi/sleepstates.asl>

	/* Contains the Sleep methods (WAK, PTS, GTS, etc.) */
	#include "acpi/sleep.asl"

	#include "acpi/gpe.asl"
}
/* End of ASL file */
