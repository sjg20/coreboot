/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 1991, 1992  Linus Torvalds
 * Copyright (C) 2015 Timothy Pearson <tpearson@raptorengineeringinc.com>,
 *               Raptor Engineering
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * blatantly copied from linux/kernel/printk.c
 */

#include <console/console.h>
#include <console/streams.h>
#include <console/vtxprintf.h>
#include <smp/spinlock.h>
#include <smp/node.h>
#include <stddef.h>
#include <trace.h>

#if (!defined(__PRE_RAM__) && IS_ENABLED(CONFIG_HAVE_ROMSTAGE_CONSOLE_SPINLOCK)) || !IS_ENABLED(CONFIG_HAVE_ROMSTAGE_CONSOLE_SPINLOCK)
DECLARE_SPIN_LOCK(console_lock)
#endif

void do_putchar(unsigned char byte)
{
	console_tx_byte(byte);
}

static void wrap_putchar(unsigned char byte, void *data)
{
	do_putchar(byte);
}

int vprintk(int msg_level, const char *fmt, va_list args)
{
	int i;

	if (IS_ENABLED(CONFIG_SQUELCH_EARLY_SMP) && ENV_CACHE_AS_RAM &&
		!boot_cpu())
		return 0;

	if (!console_log_level(msg_level))
		return 0;

	DISABLE_TRACE;
#ifdef __PRE_RAM__
#if IS_ENABLED(CONFIG_HAVE_ROMSTAGE_CONSOLE_SPINLOCK)
	spin_lock(romstage_console_lock());
#endif
#else
	spin_lock(&console_lock);
#endif

	i = vtxprintf(wrap_putchar, fmt, args, NULL);

	console_tx_flush();

#ifdef __PRE_RAM__
#if IS_ENABLED(CONFIG_HAVE_ROMSTAGE_CONSOLE_SPINLOCK)
	spin_unlock(romstage_console_lock());
#endif
#else
	spin_unlock(&console_lock);
#endif
	ENABLE_TRACE;

	return i;
}

int do_printk(int msg_level, const char *fmt, ...)
{
	va_list args;
	int i;

	va_start(args, fmt);
	i = vprintk(msg_level, fmt, args);
	va_end(args);

	return i;
}
