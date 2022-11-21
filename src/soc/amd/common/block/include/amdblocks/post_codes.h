/* SPDX-License-Identifier: GPL-2.0-only */

#ifndef AMD_BLOCK_POST_CODES_H
#define AMD_BLOCK_POST_CODES_H

#define POST_AGESA_AMDINITRESET			0x37
#define POST_AGESA_AMDINITEARLY			0x38

#define POST_ROMSTAGE_MAIN			0x40

#define POST_AGESA_AMDINITPOST			0x40
#define POST_AGESA_AMDINITPOST_DONE		0x41

#define POST_PSP_NOTIFY_DRAM			0x42
#define POST_PSP_NOTIFY_DRAM_DONE		0x43

#define POST_ROMSTAGE_RUN_POSTCAR		0x44

#define POST_PSP_LOAD_SMU			0x46
#define POST_AGESA_AMDINITENV			0x47
#define POST_AGESA_AMDS3LATERESTORE		0x48

#define POST_AGESA_AMDINITRESUME		0x60
#define POST_AGESA_AMDINITRESUME_DONE		0x61

#define POST_BOOTBLOCK_SOC_EARLY_INIT		0x90


#define POST_BOOTBLOCK_RESUME_ENTRY		0xb0
#define POST_BOOTBLOCK_PRE_C_ENTRY		0xa0
#define POST_BOOTBLOCK_PRE_C_DONE		0xa2

#endif
