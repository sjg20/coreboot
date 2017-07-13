/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2008 Advanced Micro Devices, Inc.
 * Copyright (C) 2010 Siemens AG, Inc.
 * (Written by Josef Kellermann <joseph.kellermann@heitec.de> for Siemens AG, Inc.)
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

#include <stdint.h>
#include <string.h>
#include <device/pci_def.h>
#include <arch/io.h>
#include <device/pnp_def.h>
#include <cpu/x86/lapic.h>
#include <pc80/mc146818rtc.h>
#include <console/console.h>
#include <spd.h>

#include <cpu/amd/model_fxx_rev.h>
#include <northbridge/amd/amdk8/raminit.h>
#include <delay.h>

#include <cpu/x86/lapic.h>
#include <superio/ite/common/ite.h>
#include <superio/ite/it8712f/it8712f.h>

#include <cpu/amd/car.h>
#include <cpu/x86/bist.h>

#include "northbridge/amd/amdk8/setup_resource_map.c"

#include "southbridge/amd/rs690/early_setup.c"
#include "southbridge/amd/sb600/early_setup.c"
#include <northbridge/amd/amdk8/f.h>

#define SERIAL_DEV PNP_DEV(0x2e, CONFIG_UART_FOR_CONSOLE == 1 ? IT8712F_SP2 : IT8712F_SP1)
#define GPIO_DEV PNP_DEV(0x2e, IT8712F_GPIO)

/* CAN'T BE REMOVED! crt0.S will use it. I don't know WHY!*/
void memreset(int controllers, const struct mem_controller *ctrl)
{
}

/* called in raminit_f.c */
void activate_spd_rom(const struct mem_controller *ctrl)
{
}

/*called in raminit_f.c */
int spd_read_byte(u32 device, u32 address)
{
	return smbus_read_byte(device, address);
}

#include <northbridge/amd/amdk8/amdk8.h>
#include "northbridge/amd/amdk8/incoherent_ht.c"
#include "lib/generic_sdram.c"
#include "resourcemap.c"
#include "cpu/amd/dualcore/dualcore.c"
#include "cpu/amd/model_fxx/init_cpus.c"
#include "cpu/amd/model_fxx/fidvid.c"
#include "northbridge/amd/amdk8/early_ht.c"

#define __WARNING__(fmt, arg...) do_printk(BIOS_WARNING ,fmt, ##arg)
#define __DEBUG__(fmt, arg...) do_printk(BIOS_DEBUG ,fmt, ##arg)
#define __INFO__(fmt, arg...) do_printk(BIOS_INFO ,fmt, ##arg)

void cache_as_ram_main(unsigned long bist, unsigned long cpu_init_detectedx)
{
	static const u16 spd_addr[] = { DIMM0, 0, 0, 0, DIMM1, 0, 0, 0, };
	int needs_reset = 0;
	u32 bsp_apicid = 0;
	msr_t msr;
	struct cpuid_result cpuid1;
	struct sys_info *sysinfo = &sysinfo_car;

	if (!cpu_init_detectedx && boot_cpu()) {
		/* Nothing special needs to be done to find bus 0 */
		/* Allow the HT devices to be found */
		enumerate_ht_chain();

		/* sb600_lpc_port80(); */
		sb600_pci_port80();
	}

	if (bist == 0) {
		bsp_apicid = init_cpus(cpu_init_detectedx, sysinfo);
	}

	enable_rs690_dev8(); // enable CFG access to Dev8, which is the SB P2P Bridge
	sb600_lpc_init();
#if defined(DUMP_CMOS_RAM) && (DUMP_CMOS_RAM == 0)
	check_cmos();  // rebooting in case of corrupted cmos !!!!!
#endif
	ite_enable_serial(SERIAL_DEV, CONFIG_TTYS0_BASE);
	ite_kill_watchdog(GPIO_DEV);

	console_init();
#if defined(DUMP_CMOS_RAM) && (DUMP_CMOS_RAM == 1)
	check_cmos();  // rebooting in case of corrupted cmos !!!!!
#endif
	post_code(0x03);

	/* Halt if there was a built in self test failure */
	report_bist_failure(bist);
	__DEBUG__("bsp_apicid=0x%x\n", bsp_apicid);

	setup_sitemp_resource_map();

	setup_coherent_ht_domain();

#if IS_ENABLED(CONFIG_LOGICAL_CPUS)
	/* It is said that we should start core1 after all core0 launched */
	wait_all_core0_started();
	start_other_cores();
#endif
	wait_all_aps_started(bsp_apicid);

	ht_setup_chains_x(sysinfo);

	/* run _early_setup before soft-reset. */
	rs690_early_setup();
	sb600_early_setup();

	post_code(0x04);

	/* Check to see if processor is capable of changing FIDVID  */
	/* otherwise it will throw a GP# when reading FIDVID_STATUS */
	cpuid1 = cpuid(0x80000007);
	if( (cpuid1.edx & 0x6) == 0x6 ) {

		/* Read FIDVID_STATUS */
		msr = rdmsr(0xc0010042);
		__DEBUG__("begin msr fid, vid: hi=0x%x, lo=0x%x\n", msr.hi, msr.lo);

		enable_fid_change();
		enable_fid_change_on_sb(sysinfo->sbbusn, sysinfo->sbdn);
		init_fidvid_bsp(bsp_apicid);

		/* show final fid and vid */
		msr = rdmsr(0xc0010042);
		__DEBUG__("end msr fid, vid: hi=0x%x, lo=0x%x\n", msr.hi, msr.lo);

	} else {
		__DEBUG__("Changing FIDVID not supported\n");
	}

	post_code(0x05);

	needs_reset = optimize_link_coherent_ht();
	needs_reset |= optimize_link_incoherent_ht(sysinfo);
	rs690_htinit();
	__DEBUG__("needs_reset=0x%x\n", needs_reset);

	post_code(0x06);

	if (needs_reset) {
		__INFO__("ht reset -\n");
		soft_reset();
	}

	allow_all_aps_stop(bsp_apicid);

	/* It's the time to set ctrl now; */
	__DEBUG__("sysinfo->nodes: %2x  sysinfo->ctrl: %p  spd_addr: %p\n",
		     sysinfo->nodes, sysinfo->ctrl, spd_addr);
	fill_mem_ctrl(sysinfo->nodes, sysinfo->ctrl, spd_addr);

	post_code(0x07);

	sdram_initialize(sysinfo->nodes, sysinfo->ctrl, sysinfo);

	post_code(0x08);

	rs690_before_pci_init(); // does nothing
	sb600_before_pci_init();

	post_cache_as_ram();
}
