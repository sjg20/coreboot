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

#ifndef DRIVERS_INTEL_GMA_LIBGFXINIT_H
#define DRIVERS_INTEL_GMA_LIBGFXINIT_H

void gma_gfxinit(u64 mmio_base, u64 linear_fb, u32 phys_fb, int *success);

#endif
