/* SPDX-License-Identifier: GPL-2.0-only */

#ifndef _MCALL_H
#define _MCALL_H

// NOTE: this is the size of hls_t below. A static_assert would be
// nice to have.
#if __riscv_xlen == 64
#define HLS_SIZE 88
#endif

#if __riscv_xlen == 32
#define HLS_SIZE 52
#endif

/* We save 37 registers, currently. */
#define MENTRY_FRAME_SIZE (HLS_SIZE + 37 * __SIZEOF_POINTER__)

#ifndef __ASSEMBLER__

#include <arch/encoding.h>
#include <arch/smp/atomic.h>
#include <stdint.h>

typedef struct {
	unsigned long dev;
	unsigned long cmd;
	unsigned long data;
	unsigned long sbi_private_data;
} sbi_device_message;

struct blocker {
	void *arg;
	void (*fn)(void *arg);
	atomic_t sync_a;
	atomic_t sync_b;
};

typedef struct {
	sbi_device_message *device_request_queue_head;
	unsigned long device_request_queue_size;
	sbi_device_message *device_response_queue_head;
	sbi_device_message *device_response_queue_tail;

	int hart_id;
	int ipi_pending;
	uint64_t *timecmp;
	uint64_t *time;
	void *fdt;
	struct blocker entry;
} hls_t;

_Static_assert(
	sizeof(hls_t) == HLS_SIZE,
	"HLS_SIZE must equal to sizeof(hls_t)");

#define MACHINE_STACK_TOP() ({ \
	/* coverity[uninit_use] : FALSE */ \
	register uintptr_t sp asm ("sp"); \
	(void*)((sp + RISCV_PGSIZE) & -RISCV_PGSIZE); })

// hart-local storage, at top of stack
#define HLS() ((hls_t*)(MACHINE_STACK_TOP() - HLS_SIZE))
#define OTHER_HLS(id) ((hls_t*)((void*)HLS() + RISCV_PGSIZE * ((id) - HLS()->hart_id)))

#define MACHINE_STACK_SIZE RISCV_PGSIZE

// need to call this before launching linux
void hls_init(uint32_t hart_id, void *fdt);

/* This function is used to initialize HLS()->time/HLS()->timecmp  */
void mtime_init(void);

/*
 * This function needs be implement by SoC code.
 * Although the privileged instruction set defines that MSIP will be
 * memory-mapped, but does not define how to map. SoC can be implemented as
 * a bit, a byte, a word, and so on.
 * So we can't provide code that is related to implementation.
 */
void set_msip(int hartid, int val);

#endif // __ASSEMBLER__

#endif
