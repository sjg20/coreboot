/* SPDX-License-Identifier: GPL-2.0-only */
/* This file is part of the coreboot project. */

#ifndef __ARCH_MEMLAYOUT_H
#define __ARCH_MEMLAYOUT_H

#if (CONFIG_RAMTOP == 0)
# error "CONFIG_RAMTOP not configured"
#endif

/* Intel386 psABI requires a 16 byte aligned stack. */
#define ARCH_STACK_ALIGN_SIZE 16

#endif /* __ARCH_MEMLAYOUT_H */
