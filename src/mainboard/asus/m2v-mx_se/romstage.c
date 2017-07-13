/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2006 AMD
 * (Written by Yinghai Lu <yinghailu@amd.com> for AMD)
 * Copyright (C) 2006 MSI
 * (Written by Bingxun Shi <bingxunshi@gmail.com> for MSI)
 * Copyright (C) 2008 Rudolf Marek <r.marek@assembler.cz>
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

unsigned int get_sbdn(unsigned bus);

#include <stdint.h>
#include <string.h>
#include <device/pci_def.h>
#include <arch/io.h>
#include <device/pnp_def.h>
#include <cpu/amd/mtrr.h>
#include <cpu/x86/lapic.h>
#include <pc80/mc146818rtc.h>
#include <console/console.h>
#include <cpu/amd/model_fxx_rev.h>
#include <halt.h>
#include <northbridge/amd/amdk8/raminit.h>
#include <delay.h>

#include <superio/ite/common/ite.h>
#include <superio/ite/it8712f/it8712f.h>
#include <southbridge/via/vt8237r/vt8237r.h>
#include <cpu/amd/car.h>
#include <cpu/x86/bist.h>
#include "northbridge/amd/amdk8/setup_resource_map.c"
#include <spd.h>
#include <northbridge/amd/amdk8/f.h>

#define SERIAL_DEV PNP_DEV(0x2e, IT8712F_SP1)
#define GPIO_DEV PNP_DEV(0x2e, IT8712F_GPIO)

void memreset(int controllers, const struct mem_controller *ctrl) { }
void activate_spd_rom(const struct mem_controller *ctrl) { }

int spd_read_byte(unsigned device, unsigned address)
{
	return smbus_read_byte(device, address);
}

#include "southbridge/via/k8t890/early_car.c"
#include <northbridge/amd/amdk8/amdk8.h>
#include "northbridge/amd/amdk8/incoherent_ht.c"
#include "lib/generic_sdram.c"
#include "cpu/amd/dualcore/dualcore.c"
#include "cpu/amd/model_fxx/init_cpus.c"

#define SB_VFSMAF 0

static void ldtstop_sb(void)
{
	printk(BIOS_DEBUG, "toggle LDTSTP#\n");

	/* fix errata #181, disable DRAM controller it will get enabled later */
	u8 tmp = pci_read_config8(PCI_DEV(0, 0x18, 2), 0x94);
	tmp |= (( 1 << 14) | (1 << 3));
	pci_write_config8(PCI_DEV(0, 0x18, 2), 0x94, tmp);

	u8 reg = inb (VT8237R_ACPI_IO_BASE + 0x5c);
	reg = reg ^ (1 << 0);
	outb(reg, VT8237R_ACPI_IO_BASE + 0x5c);
	reg = inb(VT8237R_ACPI_IO_BASE + 0x15);
	printk(BIOS_DEBUG, "done\n");
}

#include "cpu/amd/model_fxx/fidvid.c"
#include "northbridge/amd/amdk8/resourcemap.c"

void do_soft_reset(void)
{
	uint8_t tmp;

	set_bios_reset();
	printk(BIOS_DEBUG, "soft reset\n");

	/* PCI reset */
	tmp = pci_read_config8(PCI_DEV(0, 0x11, 0), 0x4f);
	tmp |= 0x01;
	/* FIXME from S3 set bit1 to disable USB reset VT8237A/S */
	pci_write_config8(PCI_DEV(0, 0x11, 0), 0x4f, tmp);

	halt();
}

unsigned int get_sbdn(unsigned bus)
{
	pci_devfn_t dev;

	dev = pci_locate_device_on_bus(PCI_ID(PCI_VENDOR_ID_VIA,
					PCI_DEVICE_ID_VIA_VT8237R_LPC), bus);
	return (dev >> 15) & 0x1f;
}

void cache_as_ram_main(unsigned long bist, unsigned long cpu_init_detectedx)
{
	static const uint16_t spd_addr[] = {
		// Node 0
		DIMM0, DIMM2, 0, 0,
		DIMM1, DIMM3, 0, 0,
		// Node 1
		DIMM4, DIMM6, 0, 0,
		DIMM5, DIMM7, 0, 0,
	};
	unsigned bsp_apicid = 0;
	int needs_reset = 0;
	struct sys_info *sysinfo = &sysinfo_car;

	ite_enable_serial(SERIAL_DEV, CONFIG_TTYS0_BASE);
	ite_kill_watchdog(GPIO_DEV);
	ite_enable_3vsbsw(GPIO_DEV);
	console_init();
	enable_rom_decode();

	printk(BIOS_INFO, "now booting...\n");

	if (bist == 0)
		bsp_apicid = init_cpus(cpu_init_detectedx, sysinfo);

	/* Halt if there was a built in self test failure. */
	report_bist_failure(bist);
	setup_default_resource_map();
	setup_coherent_ht_domain();
	wait_all_core0_started();

	printk(BIOS_INFO, "now booting... All core 0 started\n");

#if IS_ENABLED(CONFIG_LOGICAL_CPUS)
	/* It is said that we should start core1 after all core0 launched. */
	start_other_cores();
	wait_all_other_cores_started(bsp_apicid);
#endif
	init_timer();
	ht_setup_chains_x(sysinfo); /* Init sblnk and sbbusn, nodes, sbdn. */

	needs_reset = optimize_link_coherent_ht();
	printk(BIOS_DEBUG, "%02x", needs_reset);
	needs_reset |= optimize_link_incoherent_ht(sysinfo);
	printk(BIOS_DEBUG, "%02x", needs_reset);
	needs_reset |= k8t890_early_setup_ht();
	printk(BIOS_DEBUG, "%02x", needs_reset);

	vt8237_early_network_init(NULL);
	vt8237_early_spi_init();

	if (needs_reset) {
		printk(BIOS_DEBUG, "ht reset -\n");
		soft_reset();
		printk(BIOS_DEBUG, "FAILED!\n");
	}

	/* the HT settings needs to be OK, because link freq chnage may cause HT disconnect */
	/* allow LDT STOP asserts */
	vt8237_sb_enable_fid_vid();

	enable_fid_change();
	printk(BIOS_DEBUG, "after enable_fid_change\n");

	init_fidvid_bsp(bsp_apicid);

	/* Stop the APs so we can start them later in init. */
	allow_all_aps_stop(bsp_apicid);

	/* It's the time to set ctrl now. */
	fill_mem_ctrl(sysinfo->nodes, sysinfo->ctrl, spd_addr);
	enable_smbus();
	sdram_initialize(sysinfo->nodes, sysinfo->ctrl, sysinfo);
	post_cache_as_ram();
}
