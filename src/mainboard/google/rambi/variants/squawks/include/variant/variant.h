/* SPDX-License-Identifier: GPL-2.0-only */
/* This file is part of the coreboot project. */

#ifndef VARIANT_H
#define VARIANT_H

#include <stdint.h>

/*
 * RAM_ID[2:0] are on GPIO_SSUS[39:37]
 * 0b000 - 4GiB total - 2 x 2GiB Elpida EDJ4216EFBG-GNL-F 1600MHz
 * 0b001 - 4GiB total - 2 x 2GiB Hynix  H5TC4G63AFR-PBA 1600MHz
 * 0b010 - 4GiB total - 2 x 2GiB Hynix  H5TC4G63CFR-PBR 1600MHz
 * 0b011 - 4GiB total - 2 x 2GiB Hynix  H5TC4G63AFR-PBR 1600MHz
 * 0b100 - 2GiB total - 1 x 2GiB Elpida EDJ4216EFBG-GNL-F 1600MHz
 * 0b101 - 2GiB total - 1 x 2GiB Hynix  H5TC4G63AFR-PBA 1600MHz
 * 0b110 - 2GiB total - 1 x 2GiB Hynix  H5TC4G63AFR-PBR 1600MHz
 * 0b111 - 2GiB total - 1 x 2GiB Hynix  H5TC4G63CFR-PBR 1600MHz
 */

static const uint32_t dual_channel_config =
	(1 << 0) | (1 << 1) | (1 << 2) | (1 << 3);

#define SPD_SIZE 256
#define GPIO_SSUS_37_PAD 57
#define GPIO_SSUS_38_PAD 50
#define GPIO_SSUS_39_PAD 58

#endif
