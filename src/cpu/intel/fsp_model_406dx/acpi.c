/*
 * This file is part of the coreboot project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; version 2 of
 * the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <types.h>
#include <commonlib/helpers.h>
#include <console/console.h>
#include <arch/acpi.h>
#include <arch/acpigen.h>
#include <arch/cpu.h>
#include <cpu/x86/msr.h>
#include <cpu/intel/speedstep.h>
#include <cpu/intel/turbo.h>
#include <delay.h>
#include <device/device.h>
#include <device/pci.h>
#include "model_406dx.h"
#include "chip.h"

static int get_cores_per_package(void)
{
	struct cpuinfo_x86 c;
	struct cpuid_result result;
	int cores = 1;

	get_fms(&c, cpuid_eax(1));
	if (c.x86 != 6)
		return 1;

	result = cpuid_ext(0xb, 1);
	cores = result.ebx & 0xff;

	return cores;
}

static void generate_C_state_entries(void)
{
	struct cpu_info *info;
	struct cpu_driver *cpu;
	struct device *lapic;
	struct cpu_intel_model_406dx_config *conf = NULL;

	/* Find the SpeedStep CPU in the device tree using magic APIC ID */
	lapic = dev_find_lapic(SPEEDSTEP_APIC_MAGIC);
	if (!lapic)
		return;
	conf = lapic->chip_info;
	if (!conf)
		return;

	/* Find CPU map of supported C-states */
	info = cpu_info();
	if (!info)
		return;
	cpu = find_cpu_driver(info->cpu);
	if (!cpu || !cpu->cstates)
		return;

	acpigen_emit_byte(0x14);		/* MethodOp */
	acpigen_write_len_f();		/* PkgLength */
	acpigen_emit_namestring("_CST");
	acpigen_emit_byte(0x00);		/* No Arguments */

	/* If running on AC power */
	acpigen_emit_byte(0xa0);		/* IfOp */
	acpigen_write_len_f();		/* PkgLength */
	acpigen_emit_namestring("PWRS");
	acpigen_emit_byte(0xa4);	/* ReturnOp */
	acpigen_pop_len();

	/* Else on battery power */
	acpigen_emit_byte(0xa4);	/* ReturnOp */
	acpigen_pop_len();
}

static acpi_tstate_t tss_table_fine[] = {
	{ 100, 1000, 0, 0x00, 0 },
	{ 94, 940, 0, 0x1f, 0 },
	{ 88, 880, 0, 0x1e, 0 },
	{ 82, 820, 0, 0x1d, 0 },
	{ 75, 760, 0, 0x1c, 0 },
	{ 69, 700, 0, 0x1b, 0 },
	{ 63, 640, 0, 0x1a, 0 },
	{ 57, 580, 0, 0x19, 0 },
	{ 50, 520, 0, 0x18, 0 },
	{ 44, 460, 0, 0x17, 0 },
	{ 38, 400, 0, 0x16, 0 },
	{ 32, 340, 0, 0x15, 0 },
	{ 25, 280, 0, 0x14, 0 },
	{ 19, 220, 0, 0x13, 0 },
	{ 13, 160, 0, 0x12, 0 },
};

static acpi_tstate_t tss_table_coarse[] = {
	{ 100, 1000, 0, 0x00, 0 },
	{ 88, 875, 0, 0x1f, 0 },
	{ 75, 750, 0, 0x1e, 0 },
	{ 63, 625, 0, 0x1d, 0 },
	{ 50, 500, 0, 0x1c, 0 },
	{ 38, 375, 0, 0x1b, 0 },
	{ 25, 250, 0, 0x1a, 0 },
	{ 13, 125, 0, 0x19, 0 },
};

static void generate_T_state_entries(int core, int cores_per_package)
{
	/* Indicate SW_ALL coordination for T-states */
	acpigen_write_TSD_package(core, cores_per_package, SW_ALL);

	/* Indicate FFixedHW so OS will use MSR */
	acpigen_write_empty_PTC();

	/* Set a T-state limit that can be modified in NVS */
	acpigen_write_TPC("\\TLVL");

	/*
	 * CPUID.(EAX=6):EAX[5] indicates support
	 * for extended throttle levels.
	 */
	if (cpuid_eax(6) & (1 << 5))
		acpigen_write_TSS_package(
			ARRAY_SIZE(tss_table_fine), tss_table_fine);
	else
		acpigen_write_TSS_package(
			ARRAY_SIZE(tss_table_coarse), tss_table_coarse);
}

static int calculate_power(int tdp, int p1_ratio, int ratio)
{
	u32 m;
	u32 power;

	/*
	 * M = ((1.1 - ((p1_ratio - ratio) * 0.00625)) / 1.1) ^ 2
	 *
	 * Power = (ratio / p1_ratio) * m * tdp
	 */

	m = (110000 - ((p1_ratio - ratio) * 625)) / 11;
	m = (m * m) / 1000;

	power = ((ratio * 100000 / p1_ratio) / 100);
	power *= (m / 100) * (tdp / 1000);
	power /= 1000;

	return (int)power;
}

static int get_core_frequency_mhz(int ratio)
{
	int fsb, core_freq;

	/* Get BCLK - different SKUs can have different BCLK */
	fsb = get_timer_fsb();

	printk(BIOS_DEBUG, "BCLK:%d MHz ratio:%d\n", fsb, ratio);

	core_freq = DIV_ROUND_CLOSEST(fsb * ratio, 100) * 100;
	printk(BIOS_DEBUG, "core frequency for ratio(%d) %dMHz\n", ratio, core_freq);
	return core_freq;
}

static void generate_P_state_entries(int core, int cores_per_package)
{
	int ratio_min, ratio_max, ratio_turbo, ratio_step;
	int coord_type, power_max, num_entries;
	int ratio, power, clock, clock_max;
	msr_t msr;

	/* Rangeley uses hardware only control */
	coord_type = HW_ALL;

	/* Get bus ratio limits and calculate clock speeds */
	msr = rdmsr(MSR_PLATFORM_INFO);
	ratio_min = (msr.hi >> (40-32)) & 0xff; /* Max Efficiency Ratio */

	/* Determine if this CPU has configurable TDP */
	if (cpu_config_tdp_levels()) {
		/* Set max ratio to nominal TDP ratio */
		msr = rdmsr(MSR_CONFIG_TDP_NOMINAL);
		ratio_max = msr.lo & 0xff;
	} else {
		/* Max Non-Turbo Ratio */
		ratio_max = (msr.lo >> 8) & 0xff;
	}
	clock_max = get_core_frequency_mhz(ratio_max);

	/* Calculate CPU TDP in mW */
	msr = rdmsr(MSR_PKG_POWER_SKU_UNIT);
	power_max = 2 << ((msr.lo & 0xf) - 1);


	/* Write _PCT indicating use of FFixedHW */
	acpigen_write_empty_PCT();

	/* Write _PPC with no limit on supported P-state */
	acpigen_write_PPC_NVS();

	/* Write PSD indicating configured coordination type */
	acpigen_write_PSD_package(core, cores_per_package, coord_type);

	/* Add P-state entries in _PSS table */
	acpigen_write_name("_PSS");

	/* Determine ratio points */
	ratio_step = PSS_RATIO_STEP;
	num_entries = (ratio_max - ratio_min) / ratio_step;
	while (num_entries > PSS_MAX_ENTRIES-1) {
		ratio_step <<= 1;
		num_entries >>= 1;
	}

	/* P[T] is Turbo state if enabled */
	if (get_turbo_state() == TURBO_ENABLED) {
		/* _PSS package count including Turbo */
		acpigen_write_package(num_entries + 2);

		msr = rdmsr(MSR_TURBO_RATIO_LIMIT);
		ratio_turbo = msr.lo & 0xff;

		/* Add entry for Turbo ratio */
		acpigen_write_PSS_package(
			clock_max + 1,		/*MHz*/
			power_max,		/*mW*/
			PSS_LATENCY_TRANSITION,	/*lat1*/
			PSS_LATENCY_BUSMASTER,	/*lat2*/
			ratio_turbo << 8,	/*control*/
			ratio_turbo << 8);	/*status*/
	} else {
		/* _PSS package count without Turbo */
		acpigen_write_package(num_entries + 1);
	}

	/* First regular entry is max non-turbo ratio */
	acpigen_write_PSS_package(
		clock_max,		/*MHz*/
		power_max,		/*mW*/
		PSS_LATENCY_TRANSITION,	/*lat1*/
		PSS_LATENCY_BUSMASTER,	/*lat2*/
		ratio_max << 8,		/*control*/
		ratio_max << 8);	/*status*/

	/* Generate the remaining entries */
	for (ratio = ratio_min + ((num_entries - 1) * ratio_step);
	     ratio >= ratio_min; ratio -= ratio_step) {

		/* Calculate power at this ratio */
		power = calculate_power(power_max, ratio_max, ratio);
		clock = get_core_frequency_mhz(ratio);

		acpigen_write_PSS_package(
			clock,			/*MHz*/
			power,			/*mW*/
			PSS_LATENCY_TRANSITION,	/*lat1*/
			PSS_LATENCY_BUSMASTER,	/*lat2*/
			ratio << 8,		/*control*/
			ratio << 8);		/*status*/
	}

	/* Fix package length */
	acpigen_pop_len();
}

void generate_cpu_entries(struct device *device)
{
	int coreID, cpuID, pcontrol_blk = PMB0_BASE, plen = 6;
	int totalcores = dev_count_cpu();
	int cores_per_package = get_cores_per_package();
	int numcpus = totalcores/cores_per_package;

	printk(BIOS_DEBUG, "Found %d CPU(s) with %d core(s) each.\n",
	       numcpus, cores_per_package);

	for (cpuID = 1; cpuID <= numcpus; cpuID++) {
		for (coreID = 1; coreID <= cores_per_package; coreID++) {
			if (coreID > 1) {
				pcontrol_blk = 0;
				plen = 0;
			}

			/* Generate processor \_PR.CPUx */
			acpigen_write_processor(
				(cpuID-1)*cores_per_package+coreID-1,
				pcontrol_blk, plen);

			/* Generate P-state tables */
			generate_P_state_entries(
				cpuID-1, cores_per_package);

			/* Generate C-state tables */
			generate_C_state_entries();

			/* Generate T-state tables */
			generate_T_state_entries(
				cpuID-1, cores_per_package);

			acpigen_pop_len();
		}
	}

	/* PPKG is usually used for thermal management
	   of the first and only package. */
	acpigen_write_processor_package("PPKG", 0, cores_per_package);

	/* Add a method to notify processor nodes */
	acpigen_write_processor_cnot(cores_per_package);
}

struct chip_operations cpu_intel_model_406dx_ops = {
	CHIP_NAME("Intel Rangeley CPU")
};
