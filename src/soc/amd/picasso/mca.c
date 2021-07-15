/* SPDX-License-Identifier: GPL-2.0-only */

#include <amdblocks/msr_zen.h>
#include <amdblocks/reset.h>
#include <cpu/x86/lapic.h>
#include <cpu/x86/msr.h>
#include <acpi/acpi.h>
#include <soc/cpu.h>
#include <console/console.h>
#include <arch/bert_storage.h>
#include <cper.h>

/* MISC4 is the last used register in the MCAX banks of Picasso */
#define MCAX_USED_REGISTERS_PER_BANK	(MCAX_MISC4_OFFSET + 1)

struct mca_bank_status {
	unsigned int bank;
	msr_t sts;
};

static inline size_t mca_report_size_reqd(void)
{
	size_t size;

	size = sizeof(acpi_generic_error_status_t);

	size += sizeof(acpi_hest_generic_data_v300_t);
	size += sizeof(cper_proc_generic_error_section_t);

	size += sizeof(acpi_hest_generic_data_v300_t);
	size += sizeof(cper_ia32x64_proc_error_section_t);

	/* Check Error */
	size += cper_ia32x64_check_sz();

	/* Context of MCG_CAP, MCG_STAT, MCG_CTL */
	size += cper_ia32x64_ctx_sz_bytype(CPER_IA32X64_CTX_MSR, 3);

	/* Context of CTL, STATUS, ADDR, MISC0, CONFIG, IPID, SYND, RESERVED, DESTAT, DEADDR,
	   MISC1, MISC2, MISC3, MISC4 */
	size += cper_ia32x64_ctx_sz_bytype(CPER_IA32X64_CTX_MSR, MCAX_USED_REGISTERS_PER_BANK);

	/* Context of CTL_MASK */
	size += cper_ia32x64_ctx_sz_bytype(CPER_IA32X64_CTX_MSR, 1);

	return size;
}

static enum cper_x86_check_type error_to_chktype(struct mca_bank_status *mci)
{
	int error = mca_err_type(mci->sts);

	if (error == MCA_ERRTYPE_BUS)
		return X86_PROCESSOR_BUS_CHK;
	if (error == MCA_ERRTYPE_INT)
		return X86_PROCESSOR_MS_CHK;
	if (error == MCA_ERRTYPE_MEM)
		return X86_PROCESSOR_CACHE_CHK;
	if (error == MCA_ERRTYPE_TLB)
		return X86_PROCESSOR_TLB_CHK;

	return X86_PROCESSOR_MS_CHK; /* unrecognized */
}

/* Fill additional information in the Generic Processor Error Section. */
static void fill_generic_section(cper_proc_generic_error_section_t *sec,
		struct mca_bank_status *mci)
{
	int type = mca_err_type(mci->sts);

	if (type == MCA_ERRTYPE_BUS) /* try to map MCA errors to CPER types */
		sec->error_type = GENPROC_ERRTYPE_BUS;
	else if (type == MCA_ERRTYPE_INT)
		sec->error_type = GENPROC_ERRTYPE_UARCH;
	else if (type == MCA_ERRTYPE_MEM)
		sec->error_type = GENPROC_ERRTYPE_CACHE;
	else if (type == MCA_ERRTYPE_TLB)
		sec->error_type = GENPROC_ERRTYPE_TLB;
	else
		sec->error_type = GENPROC_ERRTYPE_UNKNOWN;
	sec->validation |= GENPROC_VALID_PROC_ERR_TYPE;
}

/* Convert an error reported by an MCA bank into BERT information to be reported
 * by the OS.  The ACPI driver doesn't recognize/parse the IA32/X64 structure,
 * which is the best method to report MSR context.  As a result, add two
 * structures:  A "processor generic error" that is parsed, and an IA32/X64 one
 * to capture complete information.
 */
static void build_bert_mca_error(struct mca_bank_status *mci)
{
	acpi_generic_error_status_t *status;
	acpi_hest_generic_data_v300_t *gen_entry;
	acpi_hest_generic_data_v300_t *x86_entry;
	cper_proc_generic_error_section_t *gen_sec;
	cper_ia32x64_proc_error_section_t *x86_sec;
	cper_ia32x64_proc_error_info_t *chk;
	cper_ia32x64_context_t *ctx;

	if (mca_report_size_reqd() > bert_storage_remaining())
		goto failed;

	status = bert_new_event(&CPER_SEC_PROC_GENERIC_GUID);
	if (!status)
		goto failed;

	gen_entry = acpi_hest_generic_data3(status);
	gen_sec = section_of_acpientry(gen_sec, gen_entry);

	fill_generic_section(gen_sec, mci);

	x86_entry = bert_append_ia32x64(status);
	x86_sec = section_of_acpientry(x86_sec, x86_entry);

	chk = new_cper_ia32x64_check(status, x86_sec, error_to_chktype(mci));
	if (!chk)
		goto failed;

	ctx = cper_new_ia32x64_context_msr(status, x86_sec, IA32_MCG_CAP, 3);
	if (!ctx)
		goto failed;
	ctx = cper_new_ia32x64_context_msr(status, x86_sec, MCAX_CTL_MSR(mci->bank),
					   MCAX_USED_REGISTERS_PER_BANK);
	if (!ctx)
		goto failed;
	ctx = cper_new_ia32x64_context_msr(status, x86_sec, MCA_CTL_MASK_MSR(mci->bank), 1);
	if (!ctx)
		goto failed;

	return;

failed:
	/* We're here because of a hardware error, don't break something else */
	printk(BIOS_ERR, "Error: Not enough room in BERT region for Machine Check error\n");
}

static const char *const mca_bank_name[] = {
	"Load-store unit",
	"Instruction fetch unit",
	"L2 cache unit",
	"Decode unit",
	"",
	"Execution unit",
	"Floating point unit",
	"L3 cache unit"
};

static void mca_print_error(unsigned int bank)
{
	msr_t msr;

	printk(BIOS_WARNING, "#MC Error: core %u, bank %u %s\n", initial_lapicid(), bank,
		bank < ARRAY_SIZE(mca_bank_name) ? mca_bank_name[bank] : "");

	msr = rdmsr(MCAX_STATUS_MSR(bank));
	printk(BIOS_WARNING, "   MC%u_STATUS =   %08x_%08x\n", bank, msr.hi, msr.lo);
	msr = rdmsr(MCAX_ADDR_MSR(bank));
	printk(BIOS_WARNING, "   MC%u_ADDR =     %08x_%08x\n", bank, msr.hi, msr.lo);
	msr = rdmsr(MCAX_MISC0_MSR(bank));
	printk(BIOS_WARNING, "   MC%u_MISC =     %08x_%08x\n", bank, msr.hi, msr.lo);
	msr = rdmsr(MCAX_CTL_MSR(bank));
	printk(BIOS_WARNING, "   MC%u_CTL =      %08x_%08x\n", bank, msr.hi, msr.lo);
	msr = rdmsr(MCA_CTL_MASK_MSR(bank));
	printk(BIOS_WARNING, "   MC%u_CTL_MASK = %08x_%08x\n", bank, msr.hi, msr.lo);
}

static void mca_check_all_banks(void)
{
	struct mca_bank_status mci;
	const unsigned int num_banks = mca_get_bank_count();

	for (unsigned int i = 0 ; i < num_banks ; i++) {
		mci.bank = i;
		mci.sts = rdmsr(MCAX_STATUS_MSR(i));
		if (mci.sts.hi || mci.sts.lo) {
			mca_print_error(i);

			if (CONFIG(ACPI_BERT) && mca_valid(mci.sts))
				build_bert_mca_error(&mci);
		}
	}
}

/* Check the Machine Check Architecture Extension registers */
void check_mca(void)
{
	mca_check_all_banks();
	/* mca_clear_status uses the MCA registers and not the MCAX ones. Since they are
	   aliases, we can use either set of registers. */
	mca_clear_status();
}
