/* SPDX-License-Identifier: GPL-2.0-only */
/* This file is part of the coreboot project. */

#ifndef RAMINIT_TABLES_H
#define RAMINIT_TABLES_H

#include <types.h>

extern const u32 pattern[32][16];

extern const u8 use_base[63][32];

extern const u8 invert[63][32];

#endif /* RAMINIT_TABLES_H */
