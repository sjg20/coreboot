/* SPDX-License-Identifier: GPL-2.0-only */
/* This file is part of the coreboot project. */

#undef SUPERIO_DEV
#undef SUPERIO_PNP_BASE
#undef IT8783EF_SHOW_UARTA
#undef IT8783EF_SHOW_UARTB
#undef IT8783EF_SHOW_UARTC
#undef IT8783EF_SHOW_UARTD
#undef IT8783EF_SHOW_KBC
#undef IT8783EF_SHOW_PS2M
#define SUPERIO_DEV		SIO0
#define SUPERIO_PNP_BASE	0x2e
#define IT8783EF_SHOW_UARTA	1
#define IT8783EF_SHOW_UARTB	1
#define IT8783EF_SHOW_UARTC	1
#define IT8783EF_SHOW_UARTD	1
#include <superio/ite/it8783ef/acpi/superio.asl>
