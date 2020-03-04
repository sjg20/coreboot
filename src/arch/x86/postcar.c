/* SPDX-License-Identifier: GPL-2.0-only */
/* This file is part of the coreboot project. */

#include <arch/romstage.h>
#include <cbmem.h>
#include <console/console.h>
#include <cpu/x86/mtrr.h>
#include <main_decl.h>
#include <program_loading.h>
#include <timestamp.h>

/*
 * Systems without a native coreboot cache-as-ram teardown may implement
 * this to use an alternate method.
 */
__weak void late_car_teardown(void) { /* do nothing */ }

void main(void)
{
	late_car_teardown();

	console_init();

	/*
	 * CBMEM needs to be recovered because timestamps rely on
	 * the cbmem infrastructure being around. Explicitly recover it.
	 */
	cbmem_initialize();

	timestamp_add_now(TS_START_POSTCAR);

	display_mtrrs();

	/* Load and run ramstage. */
	run_ramstage();
}
