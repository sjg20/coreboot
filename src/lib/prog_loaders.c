/*
 * This file is part of the coreboot project.
 *
 * Copyright 2015 Google Inc.
 * Copyright (C) 2018-2019 Eltan B.V.
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


#include <stdlib.h>
#include <cbfs.h>
#include <cbmem.h>
#include <console/console.h>
#include <fallback.h>
#include <halt.h>
#include <lib.h>
#include <program_loading.h>
#include <reset.h>
#include <romstage_handoff.h>
#include <rmodule.h>
#include <stage_cache.h>
#include <symbols.h>
#include <timestamp.h>
#include <fit_payload.h>
#include <security/vboot/vboot_common.h>
#include <soc/cpu.h>

/* Only can represent up to 1 byte less than size_t. */
const struct mem_region_device addrspace_32bit =
	MEM_REGION_DEV_RO_INIT(0, ~0UL);

int prog_locate(struct prog *prog)
{
	struct cbfsf file;

	if (prog_locate_hook(prog))
		return -1;

	cbfs_prepare_program_locate();

	if (cbfs_boot_locate(&file, prog_name(prog), NULL))
		return -1;

	cbfsf_file_type(&file, &prog->cbfs_type);

	cbfs_file_data(prog_rdev(prog), &file);

	return 0;
}

void run_romstage(void)
{
	struct prog romstage =
		PROG_INIT(PROG_ROMSTAGE, CONFIG_CBFS_PREFIX "/romstage");

	vboot_run_logic();

	if (prog_locate(&romstage))
		goto fail;

	timestamp_add_now(TS_START_COPYROM);

	if (cbfs_prog_stage_load(&romstage))
		goto fail;

	timestamp_add_now(TS_END_COPYROM);

	console_time_report();

	prog_run(&romstage);

fail:
	if (CONFIG(BOOTBLOCK_CONSOLE))
		die_with_post_code(POST_INVALID_ROM,
				   "Couldn't load romstage.\n");
	halt();
}

int __weak prog_locate_hook(struct prog *prog) { return 0; }

static void ramstage_cache_invalid(void)
{
	printk(BIOS_ERR, "ramstage cache invalid.\n");
	if (CONFIG(RESET_ON_INVALID_RAMSTAGE_CACHE)) {
		board_reset();
	}
}

static void run_ramstage_from_resume(struct prog *ramstage)
{
	if (!romstage_handoff_is_resume())
		return;

	/* Load the cached ramstage to runtime location. */
	stage_cache_load_stage(STAGE_RAMSTAGE, ramstage);

	prog_set_arg(ramstage, cbmem_top());

	if (prog_entry(ramstage) != NULL) {
		printk(BIOS_DEBUG, "Jumping to image.\n");
		prog_run(ramstage);
	}
	ramstage_cache_invalid();
}

static int load_relocatable_ramstage(struct prog *ramstage)
{
	struct rmod_stage_load rmod_ram = {
		.cbmem_id = CBMEM_ID_RAMSTAGE,
		.prog = ramstage,
	};

	return rmodule_stage_load(&rmod_ram);
}

void run_ramstage(void)
{
	struct prog ramstage =
		PROG_INIT(PROG_RAMSTAGE, CONFIG_CBFS_PREFIX "/ramstage");

	if (ENV_POSTCAR)
		timestamp_add_now(TS_END_POSTCAR);

	/* Call "end of romstage" here if postcar stage doesn't exist */
	if (ENV_ROMSTAGE)
		timestamp_add_now(TS_END_ROMSTAGE);

	/*
	 * Only x86 systems using ramstage stage cache currently take the same
	 * firmware path on resume.
	 */
	if (CONFIG(ARCH_X86) &&
	    !CONFIG(NO_STAGE_CACHE))
		run_ramstage_from_resume(&ramstage);

	vboot_run_logic();

	if (prog_locate(&ramstage))
		goto fail;

	timestamp_add_now(TS_START_COPYRAM);

	if (CONFIG(RELOCATABLE_RAMSTAGE)) {
		if (load_relocatable_ramstage(&ramstage))
			goto fail;
	} else if (cbfs_prog_stage_load(&ramstage))
		goto fail;

	stage_cache_add(STAGE_RAMSTAGE, &ramstage);

	timestamp_add_now(TS_END_COPYRAM);

	console_time_report();

	/* This overrides the arg fetched from the relocatable module */
	prog_set_arg(&ramstage, cbmem_top());

	prog_run(&ramstage);

fail:
	die_with_post_code(POST_INVALID_ROM, "Ramstage was not loaded!\n");
}

#if ENV_PAYLOAD_LOADER // gc-sections should take care of this

static struct prog global_payload =
	PROG_INIT(PROG_PAYLOAD, CONFIG_CBFS_PREFIX "/payload");

void __weak mirror_payload(struct prog *payload)
{
}

void jump_to_u_boot(const char *whence)
{
	uint8_t *buf = (uint8_t *)0x01110000;
	int buf_size = 0x100000;
	struct cbfsf fh;
	size_t fsize;
	int ret;
	uint32_t compression_algo;
	size_t decompressed_size;
	uint32_t type;
	typedef void (*h_func)(void);
	h_func func;

	printk(BIOS_INFO, "\n\nLoading U-Boot from '%s'\n", whence);

// 	if (cbfs_boot_locate(&fh, name, &type))
// 		return NULL;
	type = CBFS_TYPE_RAW;
	ret = cbfs_locate_file_in_region(&fh, "RW_LEGACY", "altfw/u-boot",
					 &type);
	printk(BIOS_INFO, "ret=%d\n", ret);
	if (ret < 0) {
		printk(BIOS_INFO, "Could not find U-Boot\n");
		die("lookup fail");
	}
// 	fsize = cbfs_boot_load_file("u-boot", buf, buf_size, CBFS_TYPE_SELF);
// 	printk(BIOS_INFO, "ret = %d\n", ret);
	if (cbfsf_decompression_info(&fh, &compression_algo,
				     &decompressed_size) < 0 ||
	    decompressed_size > buf_size) {
		printk(BIOS_INFO, "decomp fail\n");
		die("decomp fail");
	}

	fsize = cbfs_load_and_decompress(&fh.data, 0,
					 region_device_sz(&fh.data),
					 buf, buf_size, compression_algo);

// // 	size = cbfs_boot_load_file("u-boot", buf, buf_size, CBFS_TYPE_RAW);
	printk(BIOS_INFO, "Loaded %zx %zx bytes to %p\n\n", fsize,
	       decompressed_size, buf);
	print_buffer((unsigned long)buf, buf, 4, 0x20, 0);
	flush_l1d_to_l2();
	func = (h_func)buf;
	func();
}

#if 0
/* hack version goes straight to an address */
void jump_to_u_boot(const char *whence)
{
	uint8_t *buf = (uint8_t *)(0xe70000 + 0xff081000);
	typedef void (*h_func)(void);
	h_func func;

	printk(BIOS_INFO, "\nLoading U-Boot from '%s'\n", whence);
	printk(BIOS_INFO, "Jumping to %p\n\n", buf);

	print_buffer((unsigned long)buf, buf, 4, 0x20, 0);

	func = (h_func)buf;
	func();
}
#endif

void payload_load(void)
{
	struct prog *payload = &global_payload;

	timestamp_add_now(TS_LOAD_PAYLOAD);

	if (prog_locate(payload))
		goto out;

	printk(BIOS_INFO, "loaded\n");
	jump_to_u_boot("payload");

	mirror_payload(payload);

	switch (prog_cbfs_type(payload)) {
	case CBFS_TYPE_SELF: /* Simple ELF */
		selfload_check(payload, BM_MEM_RAM);
		break;
	case CBFS_TYPE_FIT: /* Flattened image tree */
		if (CONFIG(PAYLOAD_FIT_SUPPORT)) {
			fit_payload(payload);
			break;
		} /* else fall-through */
	default:
		die_with_post_code(POST_INVALID_ROM,
				   "Unsupported payload type.\n");
		break;
	}

out:
	if (prog_entry(payload) == NULL)
		die_with_post_code(POST_INVALID_ROM, "Payload not loaded.\n");
}

void payload_run(void)
{
	struct prog *payload = &global_payload;

	/* Reset to booting from this image as late as possible */
	boot_successful();

	printk(BIOS_DEBUG, "Jumping to boot code at %p(%p)\n",
		prog_entry(payload), prog_entry_arg(payload));

	post_code(POST_ENTER_ELF_BOOT);

	timestamp_add_now(TS_SELFBOOT_JUMP);

	/* Before we go off to run the payload, see if
	 * we stayed within our bounds.
	 */
	checkstack(_estack, 0);

	prog_run(payload);
}

#endif
