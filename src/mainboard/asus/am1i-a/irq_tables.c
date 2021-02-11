/* SPDX-License-Identifier: GPL-2.0-only */

#include <arch/pirq_routing.h>

const struct irq_routing_table intel_irq_routing_table = {
	PIRQ_SIGNATURE,				/* u32 signature */
	PIRQ_VERSION,				/* u16 version */
	32 + 16 * CONFIG_IRQ_SLOT_COUNT,	/* Max. number of devices on the bus */
	0x00,					/* Interrupt router bus */
	(0x14 << 3) | 0x3,			/* Interrupt router dev */
	0,					/* IRQs devoted exclusively to PCI usage */
	0x1002,					/* Vendor */
	0x439d,					/* Device */
	0,					/* Miniport */
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },	/* u8 rfu[11] */
	0x3b,					/* Checksum (has to be set to some value that
						* would give 0 after the sum of all bytes
						* for this structure (including checksum).
						*/
	/* clang-format off */
	{
		/* bus,        dev | fn,   {link, bitmap}, {link, bitmap}, {link, bitmap}, {link, bitmap}, slot, rfu */
		{0x00, (0x01 << 3) | 0x0, {{0x01, 0x9cb8}, {0x02, 0x9cb8}, {0x00, 0x0000}, {0x00, 0x0000}}, 0x0, 0x0},
		{0x00, (0x02 << 3) | 0x0, {{0x01, 0x9cb8}, {0x02, 0x9cb8}, {0x03, 0x9cb8}, {0x04, 0x9cb8}}, 0x0, 0x0},
		{0x00, (0x10 << 3) | 0x0, {{0x03, 0x9cb8}, {0x00, 0x0000}, {0x00, 0x0000}, {0x00, 0x0000}}, 0x0, 0x0},
		{0x00, (0x11 << 3) | 0x0, {{0x04, 0x9cb8}, {0x00, 0x0000}, {0x00, 0x0000}, {0x00, 0x0000}}, 0x0, 0x0},
		{0x00, (0x12 << 3) | 0x0, {{0x03, 0x9cb8}, {0x02, 0x9cb8}, {0x00, 0x0000}, {0x00, 0x0000}}, 0x0, 0x0},
		{0x00, (0x13 << 3) | 0x0, {{0x03, 0x9cb8}, {0x02, 0x9cb8}, {0x00, 0x0000}, {0x00, 0x0000}}, 0x0, 0x0},
		{0x00, (0x14 << 3) | 0x0, {{0x01, 0x9cb8}, {0x02, 0x9cb8}, {0x03, 0x9cb8}, {0x04, 0x9cb8}}, 0x0, 0x0},
		{0x00, (0x16 << 3) | 0x0, {{0x03, 0x9cb8}, {0x02, 0x9cb8}, {0x00, 0x0000}, {0x00, 0x0000}}, 0x0, 0x0},
		{0x01, (0x00 << 3) | 0x0, {{0x01, 0x9cb8}, {0x02, 0x9cb8}, {0x03, 0x9cb8}, {0x04, 0x9cb8}}, 0x0, 0x0},
		{0x02, (0x00 << 3) | 0x0, {{0x02, 0x9cb8}, {0x00, 0x0000}, {0x00, 0x0000}, {0x00, 0x0000}}, 0x0, 0x0},
	}
	/* clang-format on */
};

unsigned long write_pirq_routing_table(unsigned long addr)
{
	return copy_pirq_routing_table(addr, &intel_irq_routing_table);
}
