/*
 * This file is part of the coreboot project.
 *
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

#include <arch/pirq_routing.h>

static const struct irq_routing_table intel_irq_routing_table = {
	PIRQ_SIGNATURE,
	PIRQ_VERSION,
	32 + 16 * CONFIG_IRQ_SLOT_COUNT,/* Max. number of devices on the bus */
	0x00,			/* Interrupt router bus */
	(0x04 << 3) | 0x0,	/* Interrupt router device */
	0,			/* IRQs devoted exclusively to PCI usage */
	0x8086,			/* Vendor */
	0x122e,			/* Device */
	0,			/* Miniport data */
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* u8 rfu[11] */
	0xf9,			/* Checksum */
	{
		/* bus,       dev|fn,   {link, bitmap}, {link, bitmap}, {link, bitmap}, {link, bitmap},  slot, rfu */
		{0x00,(0x0c << 3)|0x0, {{0x60, 0x1eb8}, {0x61, 0x1eb8}, {0x62, 0x1eb8}, {0x63, 0x01eb8}}, 0x1, 0x0},
		{0x00,(0x0b << 3)|0x0, {{0x61, 0x1eb8}, {0x62, 0x1eb8}, {0x63, 0x1eb8}, {0x60, 0x01eb8}}, 0x2, 0x0},
		{0x00,(0x0a << 3)|0x0, {{0x62, 0x1eb8}, {0x63, 0x1eb8}, {0x60, 0x1eb8}, {0x61, 0x01eb8}}, 0x3, 0x0},
		{0x00,(0x09 << 3)|0x0, {{0x63, 0x1eb8}, {0x60, 0x1eb8}, {0x61, 0x1eb8}, {0x62, 0x01eb8}}, 0x4, 0x0},
		{0x00,(0x0d << 3)|0x0, {{0x63, 0x1eb8}, {0x60, 0x1eb8}, {0x61, 0x1eb8}, {0x62, 0x01eb8}}, 0x5, 0x0},
		{0x00,(0x04 << 3)|0x0, {{0x60, 0x1eb8}, {0x61, 0x1eb8}, {0x62, 0x1eb8}, {0x63, 0x01eb8}}, 0x0, 0x0},
		{0x00,(0x01 << 3)|0x0, {{0x60, 0x1eb8}, {0x61, 0x1eb8}, {0x62, 0x1eb8}, {0x63, 0x01eb8}}, 0x0, 0x0},
	}
};

unsigned long write_pirq_routing_table(unsigned long addr)
{
	return copy_pirq_routing_table(addr, &intel_irq_routing_table);
}
