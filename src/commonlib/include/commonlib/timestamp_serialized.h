/* SPDX-License-Identifier: GPL-2.0-only */

#ifndef __TIMESTAMP_SERIALIZED_H__
#define __TIMESTAMP_SERIALIZED_H__

#include <stdint.h>
#include <commonlib/bsd/helpers.h>

struct timestamp_entry {
	uint32_t	entry_id;
	int64_t		entry_stamp;
} __packed;

struct timestamp_table {
	uint64_t	base_time;
	uint16_t	max_entries;
	uint16_t	tick_freq_mhz;
	uint32_t	num_entries;
	struct timestamp_entry entries[0]; /* Variable number of entries */
} __packed;

enum timestamp_id {
	TS_ROMSTAGE_START = 1,
	TS_INITRAM_START = 2,
	TS_INITRAM_END = 3,
	TS_ROMSTAGE_END = 4,
	TS_VBOOT_START = 5,
	TS_VBOOT_END = 6,
	TS_COPYRAM_START = 8,
	TS_COPYRAM_END = 9,
	TS_RAMSTAGE_START = 10,
	TS_BOOTBLOCK_START = 11,
	TS_BOOTBLOCK_END = 12,
	TS_COPYROM_START = 13,
	TS_COPYROM_END = 14,
	TS_ULZMA_START = 15,
	TS_ULZMA_END = 16,
	TS_ULZ4F_START = 17,
	TS_ULZ4F_END = 18,
	TS_DEVICE_ENUMERATE = 30,
	TS_DEVICE_CONFIGURE = 40,
	TS_DEVICE_ENABLE = 50,
	TS_DEVICE_INITIALIZE = 60,
	TS_OPROM_INITIALIZE = 65,
	TS_OPROM_COPY_END = 66,
	TS_OPROM_END = 67,
	TS_DEVICE_DONE = 70,
	TS_CBMEM_POST = 75,
	TS_WRITE_TABLES = 80,
	TS_FINALIZE_CHIPS = 85,
	TS_LOAD_PAYLOAD = 90,
	TS_ACPI_WAKE_JUMP = 98,
	TS_SELFBOOT_JUMP = 99,
	TS_POSTCAR_START = 100,
	TS_POSTCAR_END = 101,
	TS_DELAY_START = 110,
	TS_DELAY_END = 111,
	TS_READ_UCODE_START = 112,
	TS_READ_UCODE_END = 113,
	TS_ELOG_INIT_START = 114,
	TS_ELOG_INIT_END = 115,

	/* 500+ reserved for vendorcode extensions (500-600: google/chromeos) */
	TS_COPYVER_START = 501,
	TS_COPYVER_END = 502,
	TS_TPMINIT_START = 503,
	TS_TPMINIT_END = 504,
	TS_VERIFY_SLOT_START = 505,
	TS_VERIFY_SLOT_END = 506,
	TS_HASH_BODY_START = 507,
	TS_LOADING_END = 508,
	TS_HASHING_END = 509,
	TS_HASH_BODY_END = 510,
	TS_TPMPCR_START = 511,
	TS_TPMPCR_END = 512,
	TS_TPMLOCK_START = 513,
	TS_TPMLOCK_END = 514,
	TS_EC_SYNC_START = 515,
	TS_EC_HASH_READY = 516,
	TS_EC_POWER_LIMIT_WAIT = 517,
	TS_EC_SYNC_END = 518,
	TS_COPYVPD_START = 550,
	TS_COPYVPD_RO_END = 551,
	TS_COPYVPD_RW_END = 552,
	TS_TPM_ENABLE_UPDATE_START = 553,
	TS_TPM_ENABLE_UPDATE_END = 554,

	/* 900-940 reserved for vendorcode extensions (900-940: AMD) */
	TS_AGESA_INIT_RESET_START = 900,
	TS_AGESA_INIT_RESET_END = 901,
	TS_AGESA_INIT_EARLY_START = 902,
	TS_AGESA_INIT_EARLY_END = 903,
	TS_AGESA_INIT_POST_START = 904,
	TS_AGESA_INIT_POST_END = 905,
	TS_AGESA_INIT_ENV_START = 906,
	TS_AGESA_INIT_ENV_END = 907,
	TS_AGESA_INIT_MID_START = 908,
	TS_AGESA_INIT_MID_END = 909,
	TS_AGESA_INIT_LATE_START = 910,
	TS_AGESA_INIT_LATE_END = 911,
	TS_AGESA_INIT_RTB_START = 912,
	TS_AGESA_INIT_RTB_END = 913,
	TS_AGESA_INIT_RESUME_START = 914,
	TS_AGESA_INIT_RESUME_END = 915,
	TS_AGESA_S3_LATE_START = 916,
	TS_AGESA_S3_LATE_END = 917,
	TS_AGESA_S3_FINAL_START = 918,
	TS_AGESA_S3_FINAL_END = 919,
	TS_AMD_APOB_READ_START = 920,
	TS_AMD_APOB_ERASE_START = 921,
	TS_AMD_APOB_WRITE_START = 922,
	TS_AMD_APOB_END = 923,

	/* 940-950 reserved for vendorcode extensions (940-950: Intel ME) */
	TS_ME_INFORM_DRAM_START = 940,
	TS_ME_INFORM_DRAM_END = 941,
	TS_ME_END_OF_POST_START = 942,
	TS_ME_END_OF_POST_END = 943,
	TS_ME_BOOT_STALL_END = 944,
	TS_ME_ICC_CONFIG_START = 945,
	TS_ME_HOST_BOOT_PREP_END = 946,
	TS_ME_RECEIVED_CRDA_FROM_PMC = 947,
	TS_CSE_FW_SYNC_START = 948,
	TS_CSE_FW_SYNC_END = 949,

	/* 950+ reserved for vendorcode extensions (950-989: intel/fsp) */
	TS_FSP_MEMORY_INIT_START = 950,
	TS_FSP_MEMORY_INIT_END = 951,
	TS_FSP_TEMP_RAM_EXIT_START = 952,
	TS_FSP_TEMP_RAM_EXIT_END = 953,
	TS_FSP_SILICON_INIT_START = 954,
	TS_FSP_SILICON_INIT_END = 955,
	TS_FSP_ENUMERATE_START = 956,
	TS_FSP_ENUMERATE_END = 957,
	TS_FSP_FINALIZE_START = 958,
	TS_FSP_FINALIZE_END = 959,
	TS_FSP_END_OF_FIRMWARE_START = 960,
	TS_FSP_END_OF_FIRMWARE_END = 961,
	TS_FSP_MULTI_PHASE_SI_INIT_START = 962,
	TS_FSP_MULTI_PHASE_SI_INIT_END = 963,
	TS_FSP_MEMORY_INIT_LOAD = 970,
	TS_FSP_SILICON_INIT_LOAD = 971,

	/* 990+ reserved for vendorcode extensions (990-999: Intel ME continued) */
	TS_ME_ROM_START = 990,

	/* 1000+ reserved for payloads (1000-1200: ChromeOS depthcharge) */

	/* Depthcharge entry IDs start at 1000 */
	TS_DC_START = 1000,

	TS_RO_PARAMS_INIT = 1001,
	TS_RO_VB_INIT = 1002,
	TS_RO_VB_SELECT_FIRMWARE = 1003,
	TS_RO_VB_SELECT_AND_LOAD_KERNEL = 1004,

	TS_RW_VB_SELECT_AND_LOAD_KERNEL = 1010,

	TS_VB_SELECT_AND_LOAD_KERNEL = 1020,
	TS_VB_EC_VBOOT_DONE = 1030,
	TS_VB_STORAGE_INIT_DONE = 1040,
	TS_VB_READ_KERNEL_DONE = 1050,
	TS_VB_VBOOT_DONE = 1100,

	TS_KERNEL_START = 1101,
	TS_KERNEL_DECOMPRESSION = 1102,
};

#define TS_NAME_DEF(id, desc) {(id), STRINGIFY(id), (desc)}

static const struct timestamp_id_to_name {
	uint32_t id;
	const char *enum_name;
	const char *name;
} timestamp_ids[] = {
	/* Marker to report base_time. */
	{0, "TS_START", "1st timestamp"},
	TS_NAME_DEF(TS_ROMSTAGE_START, "start of romstage"),
	TS_NAME_DEF(TS_INITRAM_START, "before RAM initialization"),
	TS_NAME_DEF(TS_INITRAM_END, "after RAM initialization"),
	TS_NAME_DEF(TS_ROMSTAGE_END, "end of romstage"),
	TS_NAME_DEF(TS_VBOOT_START, "start of verified boot"),
	TS_NAME_DEF(TS_VBOOT_END, "end of verified boot"),
	TS_NAME_DEF(TS_COPYRAM_START, "starting to load ramstage"),
	TS_NAME_DEF(TS_COPYRAM_END, "finished loading ramstage"),
	TS_NAME_DEF(TS_RAMSTAGE_START, "start of ramstage"),
	TS_NAME_DEF(TS_BOOTBLOCK_START, "start of bootblock"),
	TS_NAME_DEF(TS_BOOTBLOCK_END, "end of bootblock"),
	TS_NAME_DEF(TS_COPYROM_START, "starting to load romstage"),
	TS_NAME_DEF(TS_COPYROM_END, "finished loading romstage"),
	TS_NAME_DEF(TS_ULZMA_START, "starting LZMA decompress (ignore for x86)"),
	TS_NAME_DEF(TS_ULZMA_END, "finished LZMA decompress (ignore for x86)"),
	TS_NAME_DEF(TS_ULZ4F_START, "starting LZ4 decompress (ignore for x86)"),
	TS_NAME_DEF(TS_ULZ4F_END, "finished LZ4 decompress (ignore for x86)"),
	TS_NAME_DEF(TS_DEVICE_ENUMERATE, "device enumeration"),
	TS_NAME_DEF(TS_DEVICE_CONFIGURE, "device configuration"),
	TS_NAME_DEF(TS_DEVICE_ENABLE, "device enable"),
	TS_NAME_DEF(TS_DEVICE_INITIALIZE, "device initialization"),
	TS_NAME_DEF(TS_OPROM_INITIALIZE, "Option ROM initialization"),
	TS_NAME_DEF(TS_OPROM_COPY_END, "Option ROM copy done"),
	TS_NAME_DEF(TS_OPROM_END, "Option ROM run done"),
	TS_NAME_DEF(TS_DEVICE_DONE, "device setup done"),
	TS_NAME_DEF(TS_CBMEM_POST, "cbmem post"),
	TS_NAME_DEF(TS_WRITE_TABLES, "write tables"),
	TS_NAME_DEF(TS_FINALIZE_CHIPS, "finalize chips"),
	TS_NAME_DEF(TS_LOAD_PAYLOAD, "starting to load payload"),
	TS_NAME_DEF(TS_ACPI_WAKE_JUMP, "ACPI wake jump"),
	TS_NAME_DEF(TS_SELFBOOT_JUMP, "selfboot jump"),
	TS_NAME_DEF(TS_POSTCAR_START, "start of postcar"),
	TS_NAME_DEF(TS_POSTCAR_END, "end of postcar"),
	TS_NAME_DEF(TS_DELAY_START, "Forced delay start"),
	TS_NAME_DEF(TS_DELAY_END, "Forced delay end"),
	TS_NAME_DEF(TS_READ_UCODE_START, "started reading uCode"),
	TS_NAME_DEF(TS_READ_UCODE_END, "finished reading uCode"),
	TS_NAME_DEF(TS_ELOG_INIT_START, "started elog init"),
	TS_NAME_DEF(TS_ELOG_INIT_END, "finished elog init"),

	/* Google related timestamps */
	TS_NAME_DEF(TS_COPYVER_START, "starting to load verstage"),
	TS_NAME_DEF(TS_COPYVER_END, "finished loading verstage"),
	TS_NAME_DEF(TS_TPMINIT_START, "starting to initialize TPM"),
	TS_NAME_DEF(TS_TPMINIT_END, "finished TPM initialization"),
	TS_NAME_DEF(TS_VERIFY_SLOT_START, "starting to verify keyblock/preamble (RSA)"),
	TS_NAME_DEF(TS_VERIFY_SLOT_END, "finished verifying keyblock/preamble (RSA)"),
	TS_NAME_DEF(TS_HASH_BODY_START, "starting to verify body (load+SHA2+RSA) "),
	TS_NAME_DEF(TS_LOADING_END, "finished loading body"),
	TS_NAME_DEF(TS_HASHING_END, "finished calculating body hash (SHA2)"),
	TS_NAME_DEF(TS_HASH_BODY_END, "finished verifying body signature (RSA)"),
	TS_NAME_DEF(TS_TPMPCR_START, "starting TPM PCR extend"),
	TS_NAME_DEF(TS_TPMPCR_END, "finished TPM PCR extend"),
	TS_NAME_DEF(TS_TPMLOCK_START, "starting locking TPM"),
	TS_NAME_DEF(TS_TPMLOCK_END, "finished locking TPM"),
	TS_NAME_DEF(TS_EC_SYNC_START, "starting EC software sync"),
	TS_NAME_DEF(TS_EC_HASH_READY, "EC vboot hash ready"),
	TS_NAME_DEF(TS_EC_POWER_LIMIT_WAIT, "waiting for EC to allow higher power draw"),
	TS_NAME_DEF(TS_EC_SYNC_END, "finished EC software sync"),
	TS_NAME_DEF(TS_COPYVPD_START, "starting to load Chrome OS VPD"),
	TS_NAME_DEF(TS_COPYVPD_RO_END, "finished loading Chrome OS VPD (RO)"),
	TS_NAME_DEF(TS_COPYVPD_RW_END, "finished loading Chrome OS VPD (RW)"),
	TS_NAME_DEF(TS_TPM_ENABLE_UPDATE_START, "started TPM enable update"),
	TS_NAME_DEF(TS_TPM_ENABLE_UPDATE_END, "finished TPM enable update"),

	/* AMD related timestamps */
	TS_NAME_DEF(TS_AGESA_INIT_RESET_START, "calling AmdInitReset"),
	TS_NAME_DEF(TS_AGESA_INIT_RESET_END, "back from AmdInitReset"),
	TS_NAME_DEF(TS_AGESA_INIT_EARLY_START, "calling AmdInitEarly"),
	TS_NAME_DEF(TS_AGESA_INIT_EARLY_END, "back from AmdInitEarly"),
	TS_NAME_DEF(TS_AGESA_INIT_POST_START, "calling AmdInitPost"),
	TS_NAME_DEF(TS_AGESA_INIT_POST_END, "back from AmdInitPost"),
	TS_NAME_DEF(TS_AGESA_INIT_ENV_START, "calling AmdInitEnv"),
	TS_NAME_DEF(TS_AGESA_INIT_ENV_END, "back from AmdInitEnv"),
	TS_NAME_DEF(TS_AGESA_INIT_MID_START, "calling AmdInitMid"),
	TS_NAME_DEF(TS_AGESA_INIT_MID_END, "back from AmdInitMid"),
	TS_NAME_DEF(TS_AGESA_INIT_LATE_START, "calling AmdInitLate"),
	TS_NAME_DEF(TS_AGESA_INIT_LATE_END, "back from AmdInitLate"),
	TS_NAME_DEF(TS_AGESA_INIT_RTB_START, "calling AmdInitRtb/AmdS3Save"),
	TS_NAME_DEF(TS_AGESA_INIT_RTB_END, "back from AmdInitRtb/AmdS3Save"),
	TS_NAME_DEF(TS_AGESA_INIT_RESUME_START, "calling AmdInitResume"),
	TS_NAME_DEF(TS_AGESA_INIT_RESUME_END, "back from AmdInitResume"),
	TS_NAME_DEF(TS_AGESA_S3_LATE_START, "calling AmdS3LateRestore"),
	TS_NAME_DEF(TS_AGESA_S3_LATE_END, "back from AmdS3LateRestore"),
	TS_NAME_DEF(TS_AGESA_S3_FINAL_START, "calling AmdS3FinalRestore"),
	TS_NAME_DEF(TS_AGESA_S3_FINAL_END, "back from AmdS3FinalRestore"),
	TS_NAME_DEF(TS_AMD_APOB_READ_START, "starting APOB read"),
	TS_NAME_DEF(TS_AMD_APOB_ERASE_START, "starting APOB erase"),
	TS_NAME_DEF(TS_AMD_APOB_WRITE_START, "starting APOB write"),
	TS_NAME_DEF(TS_AMD_APOB_END, "finished APOB"),

	/* Intel ME related timestamps */
	TS_NAME_DEF(TS_ME_INFORM_DRAM_START, "waiting for ME acknowledgement of raminit"),
	TS_NAME_DEF(TS_ME_INFORM_DRAM_END, "finished waiting for ME response"),
	TS_NAME_DEF(TS_ME_END_OF_POST_START, "before sending EOP to ME"),
	TS_NAME_DEF(TS_ME_END_OF_POST_END, "after sending EOP to ME"),
	TS_NAME_DEF(TS_ME_BOOT_STALL_END, "CSE sent 'Boot Stall Done' to PMC"),
	TS_NAME_DEF(TS_ME_ICC_CONFIG_START, "CSE started to handle ICC configuration"),
	TS_NAME_DEF(TS_ME_HOST_BOOT_PREP_END, "CSE sent 'Host BIOS Prep Done' to PMC"),
	TS_NAME_DEF(TS_ME_RECEIVED_CRDA_FROM_PMC,
		    "CSE received 'CPU Reset Done Ack sent' from PMC"),
	TS_NAME_DEF(TS_CSE_FW_SYNC_START, "starting CSE firmware sync"),
	TS_NAME_DEF(TS_CSE_FW_SYNC_END, "finished CSE firmware sync"),

	/* FSP related timestamps */
	TS_NAME_DEF(TS_FSP_MEMORY_INIT_START, "calling FspMemoryInit"),
	TS_NAME_DEF(TS_FSP_MEMORY_INIT_END, "returning from FspMemoryInit"),
	TS_NAME_DEF(TS_FSP_TEMP_RAM_EXIT_START, "calling FspTempRamExit"),
	TS_NAME_DEF(TS_FSP_TEMP_RAM_EXIT_END, "returning from FspTempRamExit"),
	TS_NAME_DEF(TS_FSP_SILICON_INIT_START, "calling FspSiliconInit"),
	TS_NAME_DEF(TS_FSP_SILICON_INIT_END, "returning from FspSiliconInit"),
	TS_NAME_DEF(TS_FSP_MULTI_PHASE_SI_INIT_START, "calling FspMultiPhaseSiInit"),
	TS_NAME_DEF(TS_FSP_MULTI_PHASE_SI_INIT_END, "returning from FspMultiPhaseSiInit"),
	TS_NAME_DEF(TS_FSP_ENUMERATE_START, "calling FspNotify(AfterPciEnumeration)"),
	TS_NAME_DEF(TS_FSP_ENUMERATE_END, "returning from FspNotify(AfterPciEnumeration)"),
	TS_NAME_DEF(TS_FSP_FINALIZE_START, "calling FspNotify(ReadyToBoot)"),
	TS_NAME_DEF(TS_FSP_FINALIZE_END, "returning from FspNotify(ReadyToBoot)"),
	TS_NAME_DEF(TS_FSP_END_OF_FIRMWARE_START, "calling FspNotify(EndOfFirmware)"),
	TS_NAME_DEF(TS_FSP_END_OF_FIRMWARE_END, "returning from FspNotify(EndOfFirmware)"),
	TS_NAME_DEF(TS_FSP_MEMORY_INIT_LOAD, "loading FSP-M"),
	TS_NAME_DEF(TS_FSP_SILICON_INIT_LOAD, "loading FSP-S"),

	/* Intel ME continued */
	TS_NAME_DEF(TS_ME_ROM_START, "CSME ROM started execution"),

	/* Depthcharge entry timestamp */
	TS_NAME_DEF(TS_DC_START, "depthcharge start"),

	TS_NAME_DEF(TS_RO_PARAMS_INIT, "RO parameter init"),
	TS_NAME_DEF(TS_RO_VB_INIT, "RO vboot init"),
	TS_NAME_DEF(TS_RO_VB_SELECT_FIRMWARE, "RO vboot select firmware"),
	TS_NAME_DEF(TS_RO_VB_SELECT_AND_LOAD_KERNEL, "RO vboot select&load kernel"),

	TS_NAME_DEF(TS_RW_VB_SELECT_AND_LOAD_KERNEL, "RW vboot select&load kernel"),

	TS_NAME_DEF(TS_VB_SELECT_AND_LOAD_KERNEL, "vboot select&load kernel"),
	TS_NAME_DEF(TS_VB_EC_VBOOT_DONE, "finished EC verification"),
	TS_NAME_DEF(TS_VB_STORAGE_INIT_DONE, "finished storage device initialization"),
	TS_NAME_DEF(TS_VB_READ_KERNEL_DONE, "finished reading kernel from disk"),
	TS_NAME_DEF(TS_VB_VBOOT_DONE, "finished vboot kernel verification"),

	TS_NAME_DEF(TS_KERNEL_START, "jumping to kernel"),
	TS_NAME_DEF(TS_KERNEL_DECOMPRESSION, "starting kernel decompression/relocation"),
};

#endif
