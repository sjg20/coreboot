/* This file is part of the coreboot project. */
/* SPDX-License-Identifier: GPL-2.0-or-later */

#include <device/mmio.h>
#include <device/pci_ops.h>
#include "pch.h"
#include "cpu/intel/model_2065x/model_2065x.h"
#include <cpu/x86/msr.h>

/* Early thermal init, must be done prior to giving ME its memory
   which is done at the end of raminit.  */
void early_thermal_init(void)
{
	pci_devfn_t dev;
	msr_t msr;

	dev = PCI_DEV(0x0, 0x1f, 0x6);

	/* Program address for temporary BAR.  */
	pci_write_config32(dev, 0x40, 0x40000000);
	pci_write_config32(dev, 0x44, 0x0);

	/* Activate temporary BAR.  */
	pci_write_config32(dev, 0x40,
			   pci_read_config32(dev, 0x40) | 5);

	/* Perform init.  */
	/* Configure TJmax.  */
	msr = rdmsr(MSR_TEMPERATURE_TARGET);
	write16((u16 *)0x40000012, ((msr.lo >> 16) & 0xff) << 6);
	/* Northbridge temperature slope and offset.  */
	write16((u16 *)0x40000016, 0x7746);
	/* Enable thermal data reporting, processor, PCH and northbridge.  */
	write16((u16 *)0x4000001a,
		(read16((u16 *)0x4000001a) & ~0xf) | 0x10f0);

	/* Disable temporary BAR.  */
	pci_write_config32(dev, 0x40,
			   pci_read_config32(dev, 0x40) & ~1);
	pci_write_config32(dev, 0x40, 0);
}
