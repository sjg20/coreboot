/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2007-2009 coresystems GmbH
 * Copyright (C) 2015 Google Inc.
 * Copyright (C) 2015 Intel Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <arch/acpi.h>

DefinitionBlock(
	"dsdt.aml",
	"DSDT",
	0x05,		// DSDT revision: ACPI v5.0
	"COREv4",	// OEM id
	"COREBOOT",	// OEM table id
	0x20110725	// OEM revision
){
	//Platform
	#include <soc/intel/skylake/acpi/platform.asl>

	// global NVS and variables
	#include <soc/intel/skylake/acpi/globalnvs.asl>

	// CPU
	#include <cpu/intel/common/acpi/cpu.asl>

	Scope (\_SB) {
		Device (PCI0)
		{
			#include <soc/intel/skylake/acpi/systemagent.asl>
			#include <soc/intel/skylake/acpi/pch.asl>
		}

	}
	// Chipset specific sleep states
	#include <southbridge/intel/common/acpi/sleepstates.asl>

	#include "acpi/mainboard.asl"
}
