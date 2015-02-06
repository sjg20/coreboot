/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2007-2008 Advanced Micro Devices, Inc.
 * Copyright (C) 2009 Rudolf Marek <r.marek@assembler.cz>
 * Copyright (C) 2015 Timothy Pearson <tpearson@raptorengineeringinc.com>, Raptor Engineering
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 */

#include <console/console.h>
#include <stdint.h>
#include <cpu/x86/msr.h>
#include <arch/acpigen.h>
#include <cpu/amd/powernow.h>
#include <device/pci.h>
#include <device/pci_ids.h>
#include <cpu/x86/msr.h>
#include <cpu/amd/mtrr.h>
#include <cpu/amd/amdfam10_sysconf.h>
#include <arch/cpu.h>
#include <northbridge/amd/amdht/AsPsDefs.h>

static void write_pstates_for_core(u8 pstate_num, u16 *pstate_feq, u32 *pstate_power,
				u32 *pstate_latency, u32 *pstate_control,
				u32 *pstate_status, int coreID,
				u32 pcontrol_blk, u8 plen, u8 onlyBSP)
{
	int i;

	if ((onlyBSP) && (coreID != 0)) {
	    plen = 0;
	    pcontrol_blk = 0;
	}

	acpigen_write_processor(coreID, pcontrol_blk, plen);
	acpigen_write_empty_PCT();
	acpigen_write_name("_PSS");

	/* add later to total sum */
	acpigen_write_package(pstate_num);

	for (i = 0;i < pstate_num; i++)
		acpigen_write_PSS_package(pstate_feq[i],
					  pstate_power[i],
					  pstate_latency[i],
					  pstate_latency[i],
					  pstate_control[i],
					  pstate_status[i]);

	/* update the package size */
	acpigen_pop_len();

	acpigen_write_PPC(pstate_num);
	/* patch the whole Processor token length */
	acpigen_pop_len();
}

/*
* For details of this algorithm, please refer to the BDKG 3.62 page 69
*/
static void pstates_algorithm(u32 pcontrol_blk, u8 plen, u8 onlyBSP)
{
	u8 processor_brand[49];
	u32 *v;
	struct cpuid_result cpuid1;

	u16 Pstate_feq[10];
	u32 Pstate_power[10];
	u32 Pstate_latency[10];
	u32 Pstate_control[10];
	u32 Pstate_status[10];
	u8 Pstate_num;
	u8 cmp_cap;
	u8 index;
	msr_t msr;

	/* Get the Processor Brand String using cpuid(0x8000000x) command x=2,3,4 */
	cpuid1 = cpuid(0x80000002);
	v = (u32 *) processor_brand;
	v[0] = cpuid1.eax;
	v[1] = cpuid1.ebx;
	v[2] = cpuid1.ecx;
	v[3] = cpuid1.edx;
	cpuid1 = cpuid(0x80000003);
	v[4] = cpuid1.eax;
	v[5] = cpuid1.ebx;
	v[6] = cpuid1.ecx;
	v[7] = cpuid1.edx;
	cpuid1 = cpuid(0x80000004);
	v[8] = cpuid1.eax;
	v[9] = cpuid1.ebx;
	v[10] = cpuid1.ecx;
	v[11] = cpuid1.edx;
	processor_brand[48] = 0;
	printk(BIOS_INFO, "processor_brand=%s\n", processor_brand);

	/*
	 * Based on the CPU socket type,cmp_cap and pwr_lmt , get the power limit.
	 * socket_type : 0x10 SocketF; 0x11 AM2/ASB1 ; 0x12 S1G1
	 * cmp_cap : 0x0 SingleCore ; 0x1 DualCore ; 0x2 TripleCore ; 0x3 QuadCore ; 0x5 QuintupleCore ; 0x6 HexCore
	 */
	printk(BIOS_INFO, "Pstates Algorithm ...\n");
	cmp_cap =
	    (pci_read_config16(dev_find_slot(0, PCI_DEVFN(0x18, 3)), 0xE8) &
	     0x7000) >> 12;

	Pstate_num = 0;

	/* See if the CPUID(0x80000007) returned EDX[7]==1b */
	cpuid1 = cpuid(0x80000007);
	if ((cpuid1.edx & 0x80) != 0x80) {
		printk(BIOS_INFO, "No valid set of P-states\n");
		goto write_pstates;
	}

	uint32_t dtemp;
	uint8_t pviModeFlag;
	uint8_t Pstate_max;
	uint8_t cpufid;
	uint8_t cpudid;
	uint8_t cpuvid;
	uint8_t cpuidd;
	uint8_t cpuidv;
	uint8_t power_step_up;
	uint8_t power_step_down;
	uint8_t pll_lock_time;
	uint32_t expanded_cpuidv;
	uint32_t core_frequency;
	uint32_t core_power;
	uint32_t core_latency;
	uint32_t core_voltage;	/* multiplied by 10000 */

	/* Determine if this is a PVI or SVI system */
	dtemp = pci_read_config32(dev_find_slot(0, PCI_DEVFN(0x18, 3)), 0xA0);

	if (dtemp & PVI_MODE)
		pviModeFlag = 1;
	else
		pviModeFlag = 0;

	/* Get PSmax's index */
	msr = rdmsr(0xC0010061);
	Pstate_max = (uint8_t) ((msr.lo >> PS_MAX_VAL_SHFT) & BIT_MASK_3);

	/* Determine if all enabled Pstates have the same fidvid */
	uint8_t i;
	uint8_t cpufid_prev = (rdmsr(0xC0010064).lo & 0x3f);
	uint8_t all_enabled_cores_have_same_cpufid = 1;
	for (i = 1; i < Pstate_max; i++) {
		cpufid = rdmsr(0xC0010064 + i).lo & 0x3f;
		if (cpufid != cpufid_prev) {
			all_enabled_cores_have_same_cpufid = 0;
			break;
		}
	}

	/* Populate tables with all Pstate information */
	for (Pstate_num = 0; Pstate_num < Pstate_max; Pstate_num++) {
		/* Get power state information */
		msr = rdmsr(0xC0010064 + Pstate_num);
		cpufid = (msr.lo & 0x3f);
		cpudid = (msr.lo & 0x1c0) >> 6;
		cpuvid = (msr.lo & 0xfe00) >> 9;
		cpuidd = (msr.hi & 0xff);
		cpuidv = (msr.hi & 0x300) >> 8;
		core_frequency = (100 * (cpufid + 0x10)) / (0x01 << cpudid);
		if (pviModeFlag) {
			if (cpuvid >= 0x20) {
				core_voltage = 7625 - (((cpuvid - 0x20) * 10000) / 80);
			}
			else {
				core_voltage = 15500 - ((cpuvid * 10000) / 40);
			}
		}
		else {
			cpuvid = cpuvid & 0x7f;
			if (cpuvid >= 0x7c)
				core_voltage = 0;
			else
				core_voltage = 15500 - ((cpuvid * 10000) / 80);
		}
		switch (cpuidv) {
			case 0x0:
				expanded_cpuidv = 1;
				break;
			case 0x1:
				expanded_cpuidv = 10;
				break;
			case 0x2:
				expanded_cpuidv = 100;
				break;
			case 0x3:
				expanded_cpuidv = 1000;
				break;
		}
		core_power = (core_voltage * cpuidd) / (expanded_cpuidv * 10);

		/* Calculate transition latency */
		dtemp = pci_read_config32(dev_find_slot(0, PCI_DEVFN(0x18, 3)), 0xD4);
		power_step_up = (dtemp & 0xf000000) >> 24;
		power_step_down = (dtemp & 0xf00000) >> 20;
		dtemp = pci_read_config32(dev_find_slot(0, PCI_DEVFN(0x18, 3)), 0xA0);
		pll_lock_time = (dtemp & 0x3800) >> 11;
		if (all_enabled_cores_have_same_cpufid)
			core_latency = ((12 * power_step_down) + power_step_up) / 1000;
		else
			core_latency = (12 * (power_step_down + power_step_up) / 1000)
						 + pll_lock_time;

		Pstate_feq[Pstate_num] = core_frequency;
		Pstate_power[Pstate_num] = core_power;
		Pstate_latency[Pstate_num] = core_latency;
		Pstate_control[Pstate_num] = Pstate_num;
		Pstate_status[Pstate_num] = Pstate_num;
	}

	/* Print Pstate frequency, power, and latency */
	for (index = 0; index < Pstate_num; index++) {
		printk(BIOS_INFO, "Pstate_freq[%d] = %dMHz\t", index,
			    Pstate_feq[index]);
		printk(BIOS_INFO, "Pstate_power[%d] = %dmw\n", index,
			    Pstate_power[index]);
		printk(BIOS_INFO, "Pstate_latency[%d] = %dus\n", index,
			    Pstate_latency[index]);
	}

write_pstates:
	for (index = 0; index < (cmp_cap + 1); index++)
		write_pstates_for_core(Pstate_num, Pstate_feq, Pstate_power,
				Pstate_latency, Pstate_control, Pstate_status,
				index, pcontrol_blk, plen, onlyBSP);
}

void amd_generate_powernow(u32 pcontrol_blk, u8 plen, u8 onlyBSP)
{
	char pscope[] = "\\_PR";

	acpigen_write_scope(pscope);
	pstates_algorithm(pcontrol_blk, plen, onlyBSP);
	acpigen_pop_len();
}
