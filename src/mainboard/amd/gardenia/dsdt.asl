/* SPDX-License-Identifier: GPL-2.0-only */

#define MAINBOARD_HAS_SPEAKER 1

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
	/* #include <arch/x86/acpi/debug.asl> */	/* as needed */

	/* global NVS and variables */
	#include <globalnvs.asl>

	/* Globals for the platform */
	#include "acpi/mainboard.asl"

	/* Describe the USB Overcurrent pins */
	#include "acpi/usb_oc.asl"

	/* PCI IRQ mapping for the Southbridge */
	#include <pcie.asl>

	/* Describe the processor tree (\_SB) */
	#include <cpu.asl>

	/* Contains the supported sleep states for this chipset */
	#include <sleepstates.asl>

	/* Contains the Sleep methods (WAK, PTS, GTS, etc.) */
	#include "acpi/sleep.asl"

	/* System Bus */
	Scope(\_SB) { /* Start \_SB scope */
		/* global utility methods expected within the \_SB scope */
		#include <arch/x86/acpi/globutil.asl>

		/* IRQ Routing mapping for this platform (in \_SB scope) */
		#include "acpi/routing.asl"

		Device(PWRB) {
			Name(_HID, EISAID("PNP0C0C"))
			Name(_UID, 0xAA)
			Name(_PRW, Package () {3, 0x04})
			Name(_STA, 0x0B)
		}

		/* Describe the SOC */
		#include <soc.asl>

	} /* End \_SB scope */

	/* Define the General Purpose Events for the platform */
	#include "acpi/gpe.asl"
}
/* End of ASL file */
