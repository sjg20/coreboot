/* SPDX-License-Identifier: GPL-2.0-only OR MIT */

/*
 * This file is created based on MT8188 Functional Specification
 * Chapter number: 5.8, 5.19
 */

#ifndef MTK_MT8188_SPI_H
#define MTK_MT8188_SPI_H

#include <soc/spi_common.h>
#include <spi-generic.h>

#define SPI_BUS_NUMBER 6

#define GET_SCK_REG(x) x->spi_cfg2_reg
#define GET_TICK_DLY_REG(x) x->spi_cmd_reg

DEFINE_BITFIELD(SPI_CFG_CS_HOLD, 15, 0)
DEFINE_BITFIELD(SPI_CFG_CS_SETUP, 31, 16)
DEFINE_BITFIELD(SPI_CFG_SCK_LOW, 15, 0)
DEFINE_BITFIELD(SPI_CFG_SCK_HIGH, 31, 16)
DEFINE_BITFIELD(SPI_CFG1_CS_IDLE, 7, 0)
DEFINE_BITFIELD(SPI_CFG1_PACKET_LOOP, 15, 8)
DEFINE_BITFIELD(SPI_CFG1_PACKET_LENGTH, 32, 16)
DEFINE_BITFIELD(SPI_TICK_DLY, 24, 22)

void mtk_snfc_init(void);

#endif
