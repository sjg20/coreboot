/* SPDX-License-Identifier: GPL-2.0-only */

#ifndef _AMDBLOCKS_SMM_H_
#define _AMDBLOCKS_SMM_H_

#include <cpu/x86/msr.h>
#include <types.h>

void get_smm_info(uintptr_t *perm_smbase, size_t *perm_smsize, size_t *smm_save_state_size);
void smm_relocation_handler(int cpu, uintptr_t curr_smbase, uintptr_t staggered_smbase);
void *get_smi_source_handler(int source);
void handle_smi_gsmi(void);
void handle_smi_store(void);
void clear_tvalid(void);
void tseg_valid(void);
bool is_smm_locked(void);
void lock_smm(void);
/* See SMITYPE_* for list possible of events. GEVENTS are handled with mainboard_smi_gpi. */
void mainboard_handle_smi(int event);

#endif
