/*
 * This file is part of the coreboot project.
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

#include <console/console.h>
#include <device/device.h>
#include <string.h>
#include <cpu/cpu.h>
#include <cpu/x86/lapic.h>
#include <cpu/x86/cache.h>

static void vsm_end_post_smi(void)
{
	__asm__ volatile (
			  "push %ax\n"
			  "mov $0x5000, %ax\n"
			  ".byte 0x0f, 0x38\n"
			  "pop %ax\n"
			  );
}

static void geode_gx2_init(device_t dev)
{
	printk(BIOS_DEBUG, "geode_gx2_init\n");

	/* Turn on caching if we haven't already */
	x86_enable_cache();

	/* Enable the local CPU APICs */
	//setup_lapic();

	vsm_end_post_smi();

	printk(BIOS_DEBUG, "geode_gx2_init DONE\n");
};

static struct device_operations cpu_dev_ops = {
	.init	= geode_gx2_init,
};

static const struct cpu_device_id cpu_table[] = {
	{ X86_VENDOR_NSC, 0x0552 },
	{ 0, 0 },
};

static const struct cpu_driver driver __cpu_driver = {
	.ops	  = &cpu_dev_ops,
	.id_table = cpu_table,
};
