/*
 * This file is part of the coreboot project.
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

/*
 * Driver for Adesto Technologies SPI flash
 * based on winbond.c
 */

#include <console/console.h>
#include <commonlib/helpers.h>
#include <string.h>
#include <spi_flash.h>
#include <spi-generic.h>

#include "spi_flash_internal.h"

/* at25dfxx-specific commands */
#define CMD_AT25DF_WREN		0x06	/* Write Enable */
#define CMD_AT25DF_WRDI		0x04	/* Write Disable */
#define CMD_AT25DF_RDSR		0x05	/* Read Status Register */
#define CMD_AT25DF_WRSR		0x01	/* Write Status Register */
#define CMD_AT25DF_READ		0x03	/* Read Data Bytes */
#define CMD_AT25DF_FAST_READ	0x0b	/* Read Data Bytes at Higher Speed */
#define CMD_AT25DF_PP		0x02	/* Page Program */
#define CMD_AT25DF_SE		0x20	/* Sector (4K) Erase */
#define CMD_AT25DF_BE		0xd8	/* Block (64K) Erase */
#define CMD_AT25DF_CE		0xc7	/* Chip Erase */
#define CMD_AT25DF_DP		0xb9	/* Deep Power-down */
#define CMD_AT25DF_RES		0xab	/* Release from DP, and Read Signature */

static const struct spi_flash_part_id flash_table[] = {
	{
		.id			= 0x4218,
		.name			= "AT25SL128A",
		.nr_sectors_shift	= 12,
		.sector_size_kib_shift	= 2,
	},
	{
		.id			= 0x4501,
		.name			= "AT25DF081A", /* Yes, 81A id < 81 */
		.nr_sectors_shift	= 8,
		.sector_size_kib_shift	= 2,
	},
	{
		.id			= 0x4502,
		.name			= "AT25DF081",
		.nr_sectors_shift	= 8,
		.sector_size_kib_shift	= 2,
	},
	{
		.id			= 0x4602,
		.name			= "AT25DF161",
		.nr_sectors_shift	= 9,
		.sector_size_kib_shift	= 2,
	},
	{
		.id			= 0x4603,
		.name			= "AT25DL161",
		.nr_sectors_shift	= 9,
		.sector_size_kib_shift	= 2,
	},
	{
		.id			= 0x4700,
		.name			= "AT25DF321",
		.nr_sectors_shift	= 10,
		.sector_size_kib_shift	= 2,
	},
	{
		.id			= 0x4701,
		.name			= "AT25DF321A",
		.nr_sectors_shift	= 10,
		.sector_size_kib_shift	= 2,
	},
	{
		.id			= 0x4800,
		.name			= "AT25DF641",
		.nr_sectors_shift	= 11,
		.sector_size_kib_shift	= 2,
	},
	{
		.id			= 0x8501,
		.name			= "AT25SF081",
		.nr_sectors_shift	= 8,
		.sector_size_kib_shift	= 2,
	},
	{
		.id			= 0x8600,
		.name			= "AT25DQ161",
		.nr_sectors_shift	= 9,
		.sector_size_kib_shift	= 2,
	},
	{
		.id			= 0x8601,
		.name			= "AT25SF161",
		.nr_sectors_shift	= 9,
		.sector_size_kib_shift	= 2,
	},
	{
		.id			= 0x8700,
		.name			= "AT25DQ321",
		.nr_sectors_shift	= 10,
		.sector_size_kib_shift	= 2,
	},
};

static const struct spi_flash_ops spi_flash_ops = {
	.read = spi_flash_cmd_read,
	.write = spi_flash_cmd_write_page_program,
	.erase = spi_flash_cmd_erase,
	.status = spi_flash_cmd_status,
};

int spi_flash_probe_adesto(const struct spi_slave *spi, u8 *idcode,
			   struct spi_flash *flash)
{
	const struct spi_flash_part_id *params;
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(flash_table); i++) {
		params = &flash_table[i];
		if (params->id == ((idcode[1] << 8) | idcode[2]))
			break;
	}

	if (i == ARRAY_SIZE(flash_table)) {
		printk(BIOS_WARNING, "SF: Unsupported adesto ID %02x%02x\n",
				idcode[1], idcode[2]);
		return -1;
	}

	memcpy(&flash->spi, spi, sizeof(*spi));
	flash->name = params->name;
	/* Assuming power-of-two page size initially. */
	flash->page_size = 256;
	flash->sector_size = (1U << params->sector_size_kib_shift) * KiB;
	flash->size = flash->sector_size * (1U << params->nr_sectors_shift);
	flash->erase_cmd = CMD_AT25DF_SE;
	flash->status_cmd = CMD_AT25DF_RDSR;
	flash->pp_cmd = CMD_AT25DF_PP;
	flash->wren_cmd = CMD_AT25DF_WREN;

	flash->ops = &spi_flash_ops;

	return 0;
}
