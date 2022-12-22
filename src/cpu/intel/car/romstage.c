/* SPDX-License-Identifier: GPL-2.0-only */

#include <adainit.h>
#include <arch/romstage.h>
#include <arch/symbols.h>
#include <commonlib/helpers.h>
#include <console/console.h>
#include <cpu/x86/smm.h>
#include <program_loading.h>
#include <romstage_common.h>
#include <security/vboot/vboot_common.h>
#include <types.h>

/* If we do not have a constrained _car_stack region size, use the
   following as a guideline for acceptable stack usage. */
#define DCACHE_RAM_ROMSTAGE_STACK_SIZE 0x2000

void __noreturn romstage_main(void)
{
	int i;
	const int num_guards = 64;
	const u32 stack_guard = 0xdeadbeef;
	u32 *stack_base;
	u32 size;
	const size_t stack_size = MAX(CONFIG_DCACHE_BSP_STACK_SIZE,
				      DCACHE_RAM_ROMSTAGE_STACK_SIZE);

	/* Size of unallocated CAR. */
	size = ALIGN_DOWN(_car_stack_size, 16);

	size = MIN(size, stack_size);
	if (size < stack_size)
		printk(BIOS_DEBUG, "Romstage stack size limited to 0x%x!\n",
			size);

	stack_base = (u32 *)(_ecar_stack - size);

	for (i = 0; i < num_guards; i++)
		stack_base[i] = stack_guard;

	if (CONFIG(VBOOT_EARLY_EC_SYNC))
		vboot_sync_ec();

	/*
	 * We can generally jump between C and Ada code back and forth
	 * without trouble. But since we don't have an Ada main() we
	 * have to do some Ada package initializations that GNAT would
	 * do there. This has to be done before calling any Ada code.
	 *
	 * The package initializations should not have any dependen-
	 * cies on C code. So we can call them here early, and don't
	 * have to worry at which point we can start to use Ada.
	 */
	romstage_adainit();

	mainboard_romstage_entry();

	/* Check the stack. */
	for (i = 0; i < num_guards; i++) {
		if (stack_base[i] == stack_guard)
			continue;
		printk(BIOS_DEBUG, "Smashed stack detected in romstage!\n");
	}

	if (CONFIG(SMM_TSEG))
		smm_list_regions();

	prepare_and_run_postcar();
	/* We do not return here. */
}
