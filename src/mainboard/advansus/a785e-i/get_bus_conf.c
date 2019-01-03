/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2011 Advanced Micro Devices, Inc.
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

#include <device/pci.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <cpu/amd/multicore.h>
#include <cpu/amd/amdfam10_sysconf.h>

/* Global variables for MB layouts and these will be shared by irqtable mptable
* and acpi_tables busnum is default.
*/
u8 bus_sb800[6];
u32 apicid_sb800;

/*
* Here you only need to set value in pci1234 for HT-IO that could be installed or not
* You may need to preset pci1234 for HTIO board,
* please refer to src/northbridge/amd/amdk8/get_sblk_pci1234.c for detail
*/
u32 pci1234x[] = {
	0x0000ff0,
};

/*
* HT Chain device num, actually it is unit id base of every ht device in chain,
* assume every chain only have 4 ht device at most
*/
u32 hcdnx[] = {
	0x20202020,
};



void get_bus_conf(void)
{
	u32 apicid_base;
	struct device *dev;
	int i;

	sysconf.hc_possible_num = ARRAY_SIZE(pci1234x);
	for (i = 0; i < sysconf.hc_possible_num; i++) {
		sysconf.pci1234[i] = pci1234x[i];
		sysconf.hcdn[i] = hcdnx[i];
	}

	get_pci1234();

	sysconf.sbdn = (sysconf.hcdn[0] & 0xff);

	memset(bus_sb800, 0, sizeof(bus_sb800));

	bus_sb800[0] = (sysconf.pci1234[0] >> 16) & 0xff;

	/* sb800 */
	dev = dev_find_slot(bus_sb800[0], PCI_DEVFN(0x14, 4));
	if (dev) {
		bus_sb800[1] = pci_read_config8(dev, PCI_SECONDARY_BUS);
	}

	for (i = 0; i < 4; i++) {
		dev = dev_find_slot(bus_sb800[0], PCI_DEVFN(0x15, i));
		if (dev) {
			bus_sb800[2 + i] = pci_read_config8(dev, PCI_SECONDARY_BUS);
		}
	}

	/* I/O APICs:   APIC ID Version State   Address */
	if (IS_ENABLED(CONFIG_LOGICAL_CPUS))
		apicid_base = get_apicid_base(1);
	else
		apicid_base = CONFIG_MAX_PHYSICAL_CPUS;
	apicid_sb800 = apicid_base + 0;
}
