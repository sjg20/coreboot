/* This file is part of uio_usbdebug */
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <stdio.h>
#include <stdarg.h>
#include <console/console.h>

int do_printk(int msg_level, const char *const fmt, ...)
{
	va_list args;
	int i;

	va_start(args, fmt);
	i = vfprintf(stderr, fmt, args);
	va_end(args);

	return i;
}
