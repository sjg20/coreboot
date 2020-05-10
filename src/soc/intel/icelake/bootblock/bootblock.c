/* SPDX-License-Identifier: GPL-2.0-only */

#include <bootblock_common.h>
#include <intelblocks/gspi.h>
#include <intelblocks/systemagent.h>
#include <intelblocks/uart.h>
#include <soc/bootblock.h>
#include <soc/iomap.h>
#include <soc/pch.h>

asmlinkage void bootblock_c_entry(uint64_t base_timestamp)
{
	/* Call lib/bootblock.c main */
	bootblock_main_with_basetime(base_timestamp);
}

void bootblock_soc_early_init(void)
{
	bootblock_systemagent_early_init();
	bootblock_pch_early_init();
	bootblock_cpu_init();
	pch_early_iorange_init();
	if (CONFIG(INTEL_LPSS_UART_FOR_CONSOLE))
		uart_bootblock_init();
}

void bootblock_soc_init(void)
{
	report_platform_info();
	pch_init();
}
