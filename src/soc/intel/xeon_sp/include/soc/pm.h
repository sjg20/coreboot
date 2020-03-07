/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2014 Google Inc.
 * Copyright (C) 2019 - 2020 Intel Corporation.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef _SOC_PM_H_
#define _SOC_PM_H_

#include <soc/iomap.h>
#include <soc/pmc.h>

#define PM1_CNT                   0x04
#define PM1_STS                   0x00
#define PM1_TMR                   0x08
#define PM2_CNT                   0x50

#define GPE0_REG_MAX              4
#define GPE0_STS(x)              (0x80 + (x * 4))

#endif
