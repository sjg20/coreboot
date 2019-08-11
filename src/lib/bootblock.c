/*
 * This file is part of the coreboot project.
 *
 * Copyright 2010 Google Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; version 2 of
 * the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <arch/exception.h>
#include <bootblock_common.h>
#include <console/console.h>
#include <delay.h>
#include <pc80/mc146818rtc.h>
#include <program_loading.h>
#include <symbols.h>
#include <timestamp.h>
#include <soc/cpu.h>

#include <cbfs.h>

DECLARE_OPTIONAL_REGION(timestamp);

__weak void bootblock_mainboard_early_init(void) { /* no-op */ }
__weak void bootblock_soc_early_init(void) { /* do nothing */ }
__weak void bootblock_soc_init(void) { /* do nothing */ }
__weak void bootblock_mainboard_init(void) { /* do nothing */ }

void jump_to_u_boot(const char *whence)
{
	uint8_t *buf = (uint8_t *)0xfef10000;
	int buf_size = 0x10000;
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
	ret = cbfs_locate_file_in_region(&fh, "COREBOOT", "fallback/payload",
					 &type);
	printk(BIOS_INFO, "ret=%d\n", ret);
// 	fsize = cbfs_boot_load_file("u-boot", buf, buf_size, CBFS_TYPE_SELF);
// 	printk(BIOS_INFO, "ret = %d\n", ret);
	if (cbfsf_decompression_info(&fh, &compression_algo,
				     &decompressed_size) < 0 ||
	    decompressed_size > buf_size) {
		printk(BIOS_INFO, "decomp fail\n");
		return;
	}

	fsize = cbfs_load_and_decompress(&fh.data, 0,
					 region_device_sz(&fh.data),
					 buf, buf_size, compression_algo);

// // 	size = cbfs_boot_load_file("u-boot", buf, buf_size, CBFS_TYPE_RAW);
	printk(BIOS_INFO, "Loaded %zx %zx bytes to %p\n\n", fsize,
	       decompressed_size, buf);
	print_buffer((unsigned long)buf, buf, 4, 0x20, 0);
	printk(BIOS_INFO, "Check CONFIG_DEBUG_UART_BASE=%#x\n",
	       CONFIG_CONSOLE_UART_BASE_ADDRESS);
	flush_l1d_to_l2();
	func = (h_func)buf;
	printk(BIOS_INFO, "Jumping to U-Boot\n");
	func();
}

/*
 * This is a the same as the bootblock main(), with the difference that it does
 * not collect a timestamp. Instead it accepts the initial timestamp and
 * possibly additional timestamp entries as arguments. This can be used in cases
 * where earlier stamps are available. Note that this function is designed to be
 * entered from C code. This function assumes that the timer has already been
 * initialized, so it does not call init_timer().
 */
static void bootblock_main_with_timestamp(uint64_t base_timestamp,
	struct timestamp_entry *timestamps, size_t num_timestamps)
{
	/* Initialize timestamps if we have TIMESTAMP region in memlayout.ld. */
	if (CONFIG(COLLECT_TIMESTAMPS) &&
	    REGION_SIZE(timestamp) > 0) {
		int i;
		timestamp_init(base_timestamp);
		for (i = 0; i < num_timestamps; i++)
			timestamp_add(timestamps[i].entry_id,
				      timestamps[i].entry_stamp);
	}

	timestamp_add_now(TS_START_BOOTBLOCK);

	bootblock_soc_early_init();
	//console_init();
// 	jump_to_u_boot("bootblock before bootblock_mainboard_early_init()");
	bootblock_mainboard_early_init();

	sanitize_cmos();
	cmos_post_init();

	if (CONFIG(BOOTBLOCK_CONSOLE)) {
		console_init();
// 		jump_to_u_boot("bootblock after console");
		exception_init();
	}

// 	jump_to_u_boot("bootblock before bootblock_soc_init()");
	bootblock_soc_init();
	bootblock_mainboard_init();
//	jump_to_u_boot("bootblock before run_romstage()");

	timestamp_add_now(TS_END_BOOTBLOCK);

	run_romstage();
}

void bootblock_main_with_basetime(uint64_t base_timestamp)
{
	bootblock_main_with_timestamp(base_timestamp, NULL, 0);
}

void main(void)
{
	uint64_t base_timestamp = 0;

	init_timer();

	if (CONFIG(COLLECT_TIMESTAMPS))
		base_timestamp = timestamp_get();

	bootblock_main_with_timestamp(base_timestamp, NULL, 0);
}

#if CONFIG(COMPRESS_BOOTBLOCK)
/*
 * This is the bootblock entry point when it is run after a decompressor stage.
 * For non-decompressor builds, _start is generally defined in architecture-
 * specific assembly code. In decompressor builds that architecture
 * initialization code already ran in the decompressor, so the bootblock can
 * start straight into common code with a C environment.
 */
void _start(struct bootblock_arg *arg);
void _start(struct bootblock_arg *arg)
{
	bootblock_main_with_timestamp(arg->base_timestamp, arg->timestamps,
				      arg->num_timestamps);
}

#endif
