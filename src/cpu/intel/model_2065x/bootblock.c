/*
 * This file is part of the coreboot project.
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
#include <arch/cpu.h>
#include <cpu/x86/cache.h>
#include <cpu/x86/msr.h>
#include <cpu/x86/mtrr.h>
#include <arch/io.h>
#include <halt.h>

#include <cpu/intel/microcode/microcode.c>

#if CONFIG(SOUTHBRIDGE_INTEL_IBEXPEAK)
#include <southbridge/intel/ibexpeak/pch.h>
#include "model_2065x.h"
#else
#error "CPU must be paired with Intel Ibex Peak southbridge"
#endif

static void set_var_mtrr(unsigned int reg, unsigned int base, unsigned int size,
	unsigned int type)

{
	/* Bit Bit 32-35 of MTRRphysMask should be set to 1 */
	/* FIXME: It only support 4G less range */
	msr_t basem, maskm;
	basem.lo = base | type;
	basem.hi = 0;
	wrmsr(MTRR_PHYS_BASE(reg), basem);
	maskm.lo = ~(size - 1) | MTRR_PHYS_MASK_VALID;
	maskm.hi = (1 << (CONFIG_CPU_ADDR_BITS - 32)) - 1;
	wrmsr(MTRR_PHYS_MASK(reg), maskm);
}

static void enable_rom_caching(void)
{
	msr_t msr;

	disable_cache();
	set_var_mtrr(1, CACHE_ROM_BASE, CACHE_ROM_SIZE, MTRR_TYPE_WRPROT);
	enable_cache();

	/* Enable Variable MTRRs */
	msr.hi = 0x00000000;
	msr.lo = 0x00000800;
	wrmsr(MTRR_DEF_TYPE_MSR, msr);
}

static void bootblock_cpu_init(void)
{
	enable_rom_caching();
	intel_update_microcode_from_cbfs();
}
