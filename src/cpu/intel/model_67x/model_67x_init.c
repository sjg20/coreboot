/* SPDX-License-Identifier: GPL-2.0-only */

#include <device/device.h>
#include <cpu/cpu.h>
#include <cpu/x86/mtrr.h>
#include <cpu/intel/microcode.h>
#include <cpu/x86/cache.h>
#include <cpu/intel/l2_cache.h>

static void model_67x_init(struct device *cpu)
{
	/* Update the microcode */
	intel_update_microcode_from_cbfs();

	/* Initialize L2 cache */
	p6_configure_l2_cache();

	/* Turn on caching if we haven't already */
	enable_cache();

	/* Setup MTRRs */
	x86_setup_mtrrs();
	x86_mtrr_check();
}

static struct device_operations cpu_dev_ops = {
	.init     = model_67x_init,
};

/*
 * Intel Pentium III Processor Identification and Package Information
 * http://www.intel.com/design/pentiumiii/qit/update.pdf
 *
 * Intel Pentium III Processor Specification Update
 * http://download.intel.com/design/intarch/specupdt/24445358.pdf
 */
static const struct cpu_device_id cpu_table[] = {
	{ X86_VENDOR_INTEL, 0x0671, CPUID_EXACT_MATCH_MASK },
	{ X86_VENDOR_INTEL, 0x0672, CPUID_EXACT_MATCH_MASK }, /* PIII, kB0 */
	{ X86_VENDOR_INTEL, 0x0673, CPUID_EXACT_MATCH_MASK }, /* PIII, kC0 */
	CPU_TABLE_END
};

static const struct cpu_driver driver __cpu_driver = {
	.ops      = &cpu_dev_ops,
	.id_table = cpu_table,
};
