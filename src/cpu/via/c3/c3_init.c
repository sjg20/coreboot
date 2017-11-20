/*
 * This file is part of the coreboot project.
 *
 * (C) 2007-2008 coresystems GmbH
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <device/device.h>
#include <cpu/cpu.h>
#include <cpu/x86/mtrr.h>
#include <cpu/x86/msr.h>
#include <cpu/x86/lapic.h>
#include <cpu/x86/cache.h>

static void c3_init(struct device *dev)
{
	x86_enable_cache();
	x86_setup_mtrrs();
	x86_mtrr_check();

	/* Enable the local CPU APICs */
	setup_lapic();
};

static struct device_operations cpu_dev_ops = {
	.init     = c3_init,
};

static const struct cpu_device_id cpu_table[] = {
	{ X86_VENDOR_CENTAUR, 0x0670 },		// VIA C3 Samual 2 + Ezra
	{ X86_VENDOR_CENTAUR, 0x0680 },		// VIA C3 Ezra-T
	{ X86_VENDOR_CENTAUR, 0x0690 },		// VIA C3 Nehemiah
	{ 0, 0 },
};

static const struct cpu_driver driver __cpu_driver = {
	.ops      = &cpu_dev_ops,
	.id_table = cpu_table,
};
