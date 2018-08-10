/*
 * This file is part of the coreboot project.
 *
 * Copyright 2018-present Facebook, Inc.
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

#include <arch/io.h>
#include <soc/addressmap.h>
#include <reset.h>

void do_soft_reset(void)
{
	write64((void *)RST_SOFT_RESET, 1);
}
