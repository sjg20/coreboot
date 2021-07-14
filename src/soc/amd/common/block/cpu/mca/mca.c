/* SPDX-License-Identifier: GPL-2.0-only */

#include <amdblocks/mca.h>
#include <amdblocks/reset.h>
#include <cpu/amd/msr.h>
#include <cpu/x86/lapic.h>
#include <cpu/x86/msr.h>
#include <console/console.h>
#include <types.h>
#include "mca_common_defs.h"

static bool mca_skip_check(void)
{
	return !is_warm_reset();
}

static void mca_print_error(unsigned int bank)
{
	msr_t msr;

	printk(BIOS_WARNING, "#MC Error: core %u, bank %u %s\n", initial_lapicid(), bank,
		mca_get_bank_name(bank));

	msr = rdmsr(IA32_MC_STATUS(bank));
	printk(BIOS_WARNING, "   MC%u_STATUS =   %08x_%08x\n", bank, msr.hi, msr.lo);
	msr = rdmsr(IA32_MC_ADDR(bank));
	printk(BIOS_WARNING, "   MC%u_ADDR =     %08x_%08x\n", bank, msr.hi, msr.lo);
	msr = rdmsr(IA32_MC_MISC(bank));
	printk(BIOS_WARNING, "   MC%u_MISC =     %08x_%08x\n", bank, msr.hi, msr.lo);
	msr = rdmsr(IA32_MC_CTL(bank));
	printk(BIOS_WARNING, "   MC%u_CTL =      %08x_%08x\n", bank, msr.hi, msr.lo);
	msr = rdmsr(MC_CTL_MASK(bank));
	printk(BIOS_WARNING, "   MC%u_CTL_MASK = %08x_%08x\n", bank, msr.hi, msr.lo);
}

void mca_check_all_banks(void)
{
	struct mca_bank_status mci;
	const unsigned int num_banks = mca_get_bank_count();

	if (!mca_has_expected_bank_count())
		printk(BIOS_WARNING, "CPU has an unexpected number of MCA banks!\n");

	if (mca_skip_check())
		return;

	for (unsigned int i = 0 ; i < num_banks ; i++) {
		if (!mca_is_valid_bank(i))
			continue;

		mci.bank = i;
		mci.sts = rdmsr(IA32_MC_STATUS(i));
		if (mci.sts.hi || mci.sts.lo) {
			mca_print_error(i);

			if (CONFIG(ACPI_BERT) && mca_valid(mci.sts))
				build_bert_mca_error(&mci);
		}
	}
}
