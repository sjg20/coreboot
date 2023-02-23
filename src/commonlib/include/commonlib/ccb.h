/* SPDX-License-Identifier: GPL-2.0-only */

/*
 * CCB - coreboot Control Block - simple post-build settings for coreboot
 *
 * This is a small block of settings, typically loaded as part of bootblock.
 * It can be updated using cbfstool without rebuilding coreboot. It is intended
 * to control simple things like the serial console and logging.
 *
 * See Documentation/technotes/ccb.md for details
 */

#ifndef CCB_H
#define CCB_H

#include <stdint.h>

/**
 * enum ccb_flags - flags for use in the CCB
 */
enum ccb_flags {
	CCB_CONSOLE_SILENT	= 1 << 0,
};

/* Magic number at the top of the CCB and used to detect it in the bootblock */
#define CCB_MAGIC	0xc043b001

/**
 * struct ccb - Data in the CCB
 *
 * @magic: Magic number, must be CCB_MAGIC
 * @flags: Flag values - see enum ccb_flags
 */
struct ccb {
	uint32_t magic;
	uint32_t flags;
};

#endif
