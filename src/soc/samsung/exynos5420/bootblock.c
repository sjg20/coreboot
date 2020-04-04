/* SPDX-License-Identifier: GPL-2.0-only */
/* This file is part of the coreboot project. */

#include <arch/cache.h>
#include <bootblock_common.h>
#include <soc/clk.h>
#include <soc/wakeup.h>
#include <soc/cpu.h>

/* convenient shorthand (in MB) */
#define SRAM_START	(EXYNOS5_SRAM_BASE >> 20)
#define SRAM_SIZE	1
#define SRAM_END	(SRAM_START + SRAM_SIZE)	/* plus one... */

void bootblock_soc_init(void)
{
	if (get_wakeup_state() == WAKEUP_DIRECT) {
		wakeup();
		/* Never returns. */
	}

	/* set up dcache and MMU */
	mmu_init();
	mmu_disable_range(0, SRAM_START);
	mmu_config_range(SRAM_START, SRAM_SIZE, DCACHE_WRITEBACK);
	mmu_config_range(SRAM_END, 4096 - SRAM_END, DCACHE_OFF);
	dcache_mmu_enable();

	/* For most ARM systems, we have to initialize firmware media source
	 * (ex, SPI, SD/MMC, or eMMC) now; but for Exynos platform, that is
	 * already handled by iROM so there's no need to setup again.
	 */
}
