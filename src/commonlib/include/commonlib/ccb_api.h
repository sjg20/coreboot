/* SPDX-License-Identifier: GPL-2.0-only */

#ifndef CCB_API_H
#define CCB_API_H

#include <commonlib/ccb.h>

#if CONFIG(CCB)

/**
 * ccb_get() - Get a pointer to the coreboot control block
 *
 * Return: pointer to CCB or NULL if there is none
 */
struct ccb *ccb_get(void);

/**
 * ccb_get_flags() - Get the CCB flags
 *
 * The default value of the flags is zero.
 *
 * Return: value of CCB flags or 0 if none
 */
int ccb_get_flags(void);

/**
 * ccb_init() - Set up the CCB for use
 *
 * This locates the CCB, either built into the stage (typically for bootblock)
 * or in cbmem (for later stages).
 *
 * After calling this, other API functions can be used
 */
void ccb_init(void);

#else

static inline struct ccb *ccb_get(void) { return NULL; }
static inline int ccb_get_flags(void) { return 0; }
static inline void ccb_init(void) {}

#endif /* CCB_API_H */

#endif
