/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2012 Advanced Micro Devices, Inc.
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

#include <amdblocks/acpimmio.h>
#include <arch/io.h>
#include <device/pci_ops.h>
#include <northbridge/amd/agesa/state_machine.h>
#include <southbridge/amd/agesa/hudson/hudson.h>

void board_BeforeAgesa(struct sysinfo *cb)
{
	/* For serial port option, plug-in card on LPC. */
	pci_devfn_t dev = PCI_DEV(0, 0x14, 3);
	pci_write_config32(dev, 0x44, 0xff03ffd5);

	/* In Hudson RRG, PMIOxD2[5:4] is "Drive strength control for
	 *  LpcClk[1:0]".  To be consistent with Parmer, setting to 4mA
	 *  even though the register is not documented in the Kabini BKDG.
	 *  Otherwise the serial output is bad code.
	 */
	pm_io_write8(0xd2, 0);
}
