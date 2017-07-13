/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2007 AMD
 * Written by Yinghai Lu <yinghailu@amd.com> for AMD.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <stdint.h>
#include <string.h>
#include <device/pci_def.h>
#include <device/pci_ids.h>
#include <arch/io.h>
#include <device/pnp_def.h>
#include <cpu/x86/lapic.h>
#include <pc80/mc146818rtc.h>
#include <console/console.h>
#include <lib.h>
#include <spd.h>
#include <cpu/amd/model_fxx_rev.h>
#include <southbridge/nvidia/mcp55/mcp55.h>
#include <northbridge/amd/amdk8/raminit.h>
#include <delay.h>
#include <cpu/x86/lapic.h>
#include <superio/smsc/dme1737/dme1737.h>
#include <cpu/amd/car.h>
#include <cpu/x86/bist.h>

#include "northbridge/amd/amdk8/setup_resource_map.c"

#define SERIAL_DEV PNP_DEV(0x2e, DME1737_SP1)

unsigned get_sbdn(unsigned bus);

unsigned get_sbdn(unsigned bus)
{
	pci_devfn_t dev;

	/* Find the device. */
	dev = pci_locate_device_on_bus(PCI_ID(PCI_VENDOR_ID_NVIDIA,
				       PCI_DEVICE_ID_NVIDIA_MCP55_HT), bus);

	return (dev >> 15) & 0x1f;
}

void memreset(int controllers, const struct mem_controller *ctrl) { }
void activate_spd_rom(const struct mem_controller *ctrl) { }

int spd_read_byte(unsigned device, unsigned address)
{
	return smbus_read_byte(device, address);
}

#include <northbridge/amd/amdk8/f.h>
#include "northbridge/amd/amdk8/incoherent_ht.c"
#include "lib/generic_sdram.c"
#include "resourcemap.c"
#include "cpu/amd/dualcore/dualcore.c"

#define NMI_SC 0x0061
#define PCI_SERR_EN 0x04

#define MCP55_MB_SETUP \
	RES_PORT_IO_8, SYSCTRL_IO_BASE + 0xc0+61, 0x00, 0x05,/* GPIO62: enable/not-disable on-board TSB43AB22A Firewire */

#include <southbridge/nvidia/mcp55/early_setup_ss.h>
#include "southbridge/nvidia/mcp55/early_setup_car.c"
#include "cpu/amd/model_fxx/init_cpus.c"
#include "cpu/amd/model_fxx/fidvid.c"
#include "northbridge/amd/amdk8/early_ht.c"

static void sio_setup(void)
{
	uint32_t dword;
	uint8_t byte;

	byte = pci_read_config8(PCI_DEV(0, MCP55_DEVN_BASE+1 , 0), 0x7b);
	byte |= 0x20;
	pci_write_config8(PCI_DEV(0, MCP55_DEVN_BASE+1 , 0), 0x7b, byte);

	dword = pci_read_config32(PCI_DEV(0, MCP55_DEVN_BASE+1 , 0), 0xa0);
	dword |= (1 << 0);
	pci_write_config32(PCI_DEV(0, MCP55_DEVN_BASE+1 , 0), 0xa0, dword);

	dword = pci_read_config32(PCI_DEV(0, MCP55_DEVN_BASE+1 , 0), 0xa4);
	dword |= (1 << 16);
	pci_write_config32(PCI_DEV(0, MCP55_DEVN_BASE+1 , 0), 0xa4, dword);
}

void cache_as_ram_main(unsigned long bist, unsigned long cpu_init_detectedx)
{
	static const uint16_t spd_addr [] = {
		// Node 0
		DIMM0, DIMM2, 0, 0,
		DIMM1, DIMM3, 0, 0,
		// Node 1
		DIMM4, DIMM6, 0, 0,
		DIMM5, DIMM7, 0, 0,
	};

	struct sys_info *sysinfo = &sysinfo_car;
	int needs_reset = 0;
	unsigned bsp_apicid = 0;

	if (!cpu_init_detectedx && boot_cpu()) {
		/* Nothing special needs to be done to find bus 0 */
		/* Allow the HT devices to be found */
		enumerate_ht_chain();
		sio_setup();
	}

	if (bist == 0)
		bsp_apicid = init_cpus(cpu_init_detectedx, sysinfo);

	setup_mb_resource_map();

	dme1737_enable_serial(SERIAL_DEV, CONFIG_TTYS0_BASE);
	console_init();

	/* Halt if there was a built in self test failure */
	report_bist_failure(bist);
	printk(BIOS_DEBUG, "*sysinfo range: [%p,%p]\n",sysinfo,sysinfo+1);

	printk(BIOS_DEBUG, "bsp_apicid=%02x\n", bsp_apicid);

	set_sysinfo_in_ram(0); // in BSP so could hold all ap until sysinfo is in ram
	setup_coherent_ht_domain(); // routing table and start other core0

	wait_all_core0_started();
#if IS_ENABLED(CONFIG_LOGICAL_CPUS)
	// It is said that we should start core1 after all core0 launched
	/* becase optimize_link_coherent_ht is moved out from setup_coherent_ht_domain,
	 * So here need to make sure last core0 is started, esp for two way system,
	 * (there may be apic id conflicts in that case)
	 */
	start_other_cores();
	wait_all_other_cores_started(bsp_apicid);
#endif

	/* it will set up chains and store link pair for optimization later */
	ht_setup_chains_x(sysinfo); // it will init sblnk and sbbusn, nodes, sbdn

#if IS_ENABLED(CONFIG_SET_FIDVID)
	{
		msr_t msr;
		msr = rdmsr(0xc0010042);
		printk(BIOS_DEBUG, "begin msr fid, vid %08x%08x\n", msr.hi, msr.lo);
	}
	enable_fid_change();
	enable_fid_change_on_sb(sysinfo->sbbusn, sysinfo->sbdn);
	init_fidvid_bsp(bsp_apicid);
	// show final fid and vid
	{
		msr_t msr;
		msr = rdmsr(0xc0010042);
		printk(BIOS_DEBUG, "end   msr fid, vid %08x%08x\n", msr.hi, msr.lo);
	}
#endif

	init_timer(); /* Need to use TMICT to synchronize FID/VID. */

	needs_reset |= optimize_link_coherent_ht();
	needs_reset |= optimize_link_incoherent_ht(sysinfo);
	needs_reset |= mcp55_early_setup_x();

	/* mask NMI from constantly-asserted-on-this-board SERR# */
	outb((inb(NMI_SC) & 0x0f) | PCI_SERR_EN, NMI_SC);

	// fidvid change will issue one LDTSTOP and the HT change will be effective too
	if (needs_reset) {
		printk(BIOS_INFO, "ht reset -\n");
		soft_reset();
	}
	allow_all_aps_stop(bsp_apicid);

	//It's the time to set ctrl in sysinfo now;
	fill_mem_ctrl(sysinfo->nodes, sysinfo->ctrl, spd_addr);

	enable_smbus();

	/* all ap stopped? */

	sdram_initialize(sysinfo->nodes, sysinfo->ctrl, sysinfo);

	post_cache_as_ram(); // bsp swtich stack to RAM and copy sysinfo RAM now
}
