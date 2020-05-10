/* SPDX-License-Identifier: GPL-2.0-only */

#include <acpi/acpi.h>
#include "variant/ec.h"
#include "variant/gpio.h"

DefinitionBlock(
	"dsdt.aml",
	"DSDT",
	0x02,		// DSDT revision
	OEM_ID,
	ACPI_TABLE_CREATOR,
	0x20110725	// OEM revision
)
{
	#include <soc/intel/icelake/acpi/platform.asl>

	// global NVS and variables
	#include <soc/intel/common/block/acpi/acpi/globalnvs.asl>

	// CPU
	#include <cpu/intel/common/acpi/cpu.asl>

	Scope (\_SB) {
		Device (PCI0)
		{
			#include <soc/intel/common/block/acpi/acpi/northbridge.asl>
			#include <soc/intel/icelake/acpi/southbridge.asl>
		}
	}

#if CONFIG(CHROMEOS)
	// Chrome OS specific
	#include <vendorcode/google/chromeos/acpi/chromeos.asl>
#endif

	#include <southbridge/intel/common/acpi/sleepstates.asl>

	/* Chrome OS Embedded Controller */
	Scope (\_SB.PCI0.LPCB)
	{
		/* ACPI code for EC SuperIO functions */
		#include <ec/google/chromeec/acpi/superio.asl>
		/* ACPI code for EC functions */
		#include <ec/google/chromeec/acpi/ec.asl>
	}
}
