/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2014 Google Inc.
 * Copyright (C) 2015 Intel Corporation.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef _SOC_SMM_H_
#define _SOC_SMM_H_

#include <stdint.h>
#include <cpu/x86/msr.h>
#include <cpu/x86/smm.h>
#include <intelblocks/smihandler.h>
#include <soc/gpio.h>

struct ied_header {
	char signature[10];
	u32 size;
	u8 reserved[34];
} __packed;

struct smm_relocation_params {
	uintptr_t ied_base;
	size_t ied_size;
	msr_t smrr_base;
	msr_t smrr_mask;
	msr_t emrr_base;
	msr_t emrr_mask;
	msr_t uncore_emrr_base;
	msr_t uncore_emrr_mask;
	/*
	 * The smm_save_state_in_msrs field indicates if SMM save state
	 * locations live in MSRs. This indicates to the CPUs how to adjust
	 * the SMMBASE and IEDBASE
	 */
	int smm_save_state_in_msrs;
};

void smm_relocation_handler(int cpu, uintptr_t curr_smbase,
				uintptr_t staggered_smbase);
void smm_info(uintptr_t *perm_smbase, size_t *perm_smsize,
		size_t *smm_save_state_size);
void smm_initialize(void);
void smm_relocate(void);
void smm_lock(void);

#endif
