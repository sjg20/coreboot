/* SPDX-License-Identifier: GPL-2.0-only */

#include <arch/cache.h>
#include <assert.h>
#include <bl31.h>
#include <soc/addressmap.h>
#include <soc/console_uart.h>
#include <types.h>

typedef struct bl31_plat_params {
	/* TZ memory size */
	uint64_t tzdram_size;
	/* TZ memory base */
	uint64_t tzdram_base;
	/* UART port ID */
	int uart_id;
} bl31_plat_params_t;

static bl31_plat_params_t t210_plat_params;

void *soc_get_bl31_plat_params(void)
{
	uintptr_t tz_base_mib;
	size_t tz_size_mib;
	int uart_id = 0;

	carveout_range(CARVEOUT_TZ, &tz_base_mib, &tz_size_mib);

	assert(tz_size_mib < 4096);

	switch (console_uart_get_id()) {
	case UART_ID_NONE:
		break;
	case UART_ID_A:
		uart_id = 1;
		break;
	case UART_ID_B:
		uart_id = 2;
		break;
	case UART_ID_C:
		uart_id = 3;
		break;
	case UART_ID_D:
		uart_id = 4;
		break;
	case UART_ID_E:
		uart_id = 5;
		break;
	}

	t210_plat_params.tzdram_size = tz_size_mib * MiB;
	t210_plat_params.tzdram_base = tz_base_mib * MiB;
	t210_plat_params.uart_id = uart_id;

	dcache_clean_by_mva(&t210_plat_params, sizeof(t210_plat_params));

	return &t210_plat_params;
}
