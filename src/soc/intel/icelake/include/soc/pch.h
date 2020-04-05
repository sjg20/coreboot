/* SPDX-License-Identifier: GPL-2.0-only */
/* This file is part of the coreboot project. */

#ifndef _SOC_ICELAKE_PCH_H_
#define _SOC_ICELAKE_PCH_H_

#include <stdint.h>

#define PCH_H				1
#define PCH_LP				2
#define PCH_UNKNOWN_SERIES		0xFF

#define PCIE_CLK_NOTUSED		0xFF
#define PCIE_CLK_LAN			0x70
#define PCIE_CLK_FREE			0x80

#endif
