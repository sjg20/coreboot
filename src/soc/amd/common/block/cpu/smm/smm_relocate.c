/* SPDX-License-Identifier: GPL-2.0-only */

#include <amdblocks/smm.h>
#include <console/console.h>
#include <cpu/amd/amd64_save_state.h>
#include <cpu/amd/msr.h>
#include <cpu/cpu.h>
#include <cpu/x86/msr.h>
#include <cpu/x86/smm.h>
#include <types.h>

void get_smm_info(uintptr_t *perm_smbase, size_t *perm_smsize, size_t *smm_save_state_size)
{
	printk(BIOS_DEBUG, "Setting up SMI for CPU\n");

	uintptr_t tseg_base;
	size_t tseg_size;

	smm_region(&tseg_base, &tseg_size);

	if (!IS_ALIGNED(tseg_base, tseg_size)) {
		printk(BIOS_ERR, "TSEG base not aligned to TSEG size\n");
		return;
	}
	/* Minimum granularity for TSEG MSRs */
	if (tseg_size < 128 * KiB) {
		printk(BIOS_ERR, "TSEG size (0x%zx) too small\n", tseg_size);
		return;
	}


	smm_subregion(SMM_SUBREGION_HANDLER, perm_smbase, perm_smsize);
	*smm_save_state_size = sizeof(amd64_smm_state_save_area_t);
}

void smm_relocation_handler(int cpu, uintptr_t curr_smbase, uintptr_t staggered_smbase)
{
	amd64_smm_state_save_area_t *smm_state;

	uintptr_t tseg_base;
	size_t tseg_size;

	smm_region(&tseg_base, &tseg_size);

	msr_t msr;
	msr.lo = tseg_base;
	msr.hi = 0;
	wrmsr(SMM_ADDR_MSR, msr);

	msr.lo = ~(tseg_size - 1);
	msr.lo |= SMM_TSEG_WB;
	msr.hi = (1 << (cpu_phys_address_size() - 32)) - 1;
	wrmsr(SMM_MASK_MSR, msr);

	smm_state = (void *)(SMM_AMD64_SAVE_STATE_OFFSET + curr_smbase);
	smm_state->smbase = staggered_smbase;
}
