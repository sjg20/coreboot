/* SPDX-License-Identifier: GPL-2.0-only */

#include <acpi/acpi.h>
#include <amdblocks/cpu.h>
#include <amdblocks/iomap.h>
#include <amdblocks/mca.h>
#include <console/console.h>
#include <cpu/amd/microcode.h>
#include <cpu/cpu.h>
#include <cpu/x86/mp.h>
#include <cpu/x86/mtrr.h>
#include <device/device.h>
#include <soc/cpu.h>
#include <soc/iomap.h>

_Static_assert(CONFIG_MAX_CPUS == 8, "Do not override MAX_CPUS. To reduce the number of "
	"available cores, use the downcore_mode and disable_smt devicetree settings instead.");

/* MP and SMM loading initialization. */

void mp_init_cpus(struct bus *cpu_bus)
{
	extern const struct mp_ops amd_mp_ops_with_smm;
	if (mp_init_with_smm(cpu_bus, &amd_mp_ops_with_smm) != CB_SUCCESS)
		die_with_post_code(POST_HW_INIT_FAILURE,
				"mp_init_with_smm failed. Halting.\n");

	/* pre_mp_init made the flash not cacheable. Reset to WP for performance. */
	mtrr_use_temp_range(FLASH_BELOW_4GB_MAPPING_REGION_BASE,
			    FLASH_BELOW_4GB_MAPPING_REGION_SIZE, MTRR_TYPE_WRPROT);

	/* SMMINFO only needs to be set up when booting from S5 */
	if (!acpi_is_wakeup_s3())
		apm_control(APM_CNT_SMMINFO);

}

static void model_17_init(struct device *dev)
{
	check_mca();
	set_cstate_io_addr();

	amd_update_microcode_from_cbfs();
}

static struct device_operations cpu_dev_ops = {
	.init = model_17_init,
};

static struct cpu_device_id cpu_table[] = {
	{ X86_VENDOR_AMD, RAVEN1_B0_CPUID, CPUID_EXACT_MATCH_MASK },
	{ X86_VENDOR_AMD, PICASSO_B0_CPUID, CPUID_EXACT_MATCH_MASK },
	{ X86_VENDOR_AMD, PICASSO_B1_CPUID, CPUID_EXACT_MATCH_MASK },
	{ X86_VENDOR_AMD, RAVEN2_A0_CPUID, CPUID_EXACT_MATCH_MASK },
	{ X86_VENDOR_AMD, RAVEN2_A1_CPUID, CPUID_EXACT_MATCH_MASK },
	{ 0, 0, 0 },
};

static const struct cpu_driver model_17 __cpu_driver = {
	.ops      = &cpu_dev_ops,
	.id_table = cpu_table,
};
