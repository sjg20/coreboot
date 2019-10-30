/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2007-2009 coresystems GmbH
 * Copyright (C) 2014 Google Inc.
 * Copyright (C) 2015 Intel Corporation.
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

// Intel LPC Bus Device  - 0:1f.0
#include <soc/intel/common/block/acpi/acpi/lpc.asl>

Scope (\_SB.PCI0.LPCB)
{
	#include <acpi/ec.asl>
	#include <acpi/superio.asl>
}
