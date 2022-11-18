/* SPDX-License-Identifier: GPL-2.0-only */

#include <device/device.h>
#include <amdblocks/agesawrapper.h>
#include <amdblocks/amd_pci_util.h>
#include <console/console.h>
#include <soc/gpio.h>
#include <soc/southbridge.h>
#include <string.h>

#include "gpio.h"

/*
 * These arrays set up the FCH PCI_INTR registers 0xC00/0xC01.
 * This table is responsible for physically routing the PIC and
 * IOAPIC IRQs to the different PCI devices on the system.  It
 * is read and written via registers 0xC00/0xC01 as an
 * Index/Data pair.  These values are chipset and mainboard
 * dependent and should be updated accordingly.
 */
static uint8_t fch_pic_routing[FCH_IRQ_ROUTING_ENTRIES];
static uint8_t fch_apic_routing[FCH_IRQ_ROUTING_ENTRIES];

static const struct fch_irq_routing fch_irq_map[] = {
	{ PIRQ_A,	 3,		16 },
	{ PIRQ_B,	 4,		17 },
	{ PIRQ_C,	 5,		18 },
	{ PIRQ_D,	 7,		19 },
	{ PIRQ_E,	11,		20 },
	{ PIRQ_F,	10,		21 },
	{ PIRQ_G,	PIRQ_NC,	22 },
	{ PIRQ_H,	PIRQ_NC,	23 },
	{ PIRQ_SCI,	PIRQ_NC,	 9 },
	{ PIRQ_SMBUS,	PIRQ_NC,	PIRQ_NC },
	{ PIRQ_HDA,	 3,		16 },
	{ PIRQ_SD,	PIRQ_NC,	16 },
	{ PIRQ_SDIO,	PIRQ_NC,	PIRQ_NC },
	{ PIRQ_EHCI,	 5,		18 },
	{ PIRQ_XHCI,	 4,		18 },
	{ PIRQ_SATA,	PIRQ_NC,	19 },
	{ PIRQ_GPIO,	 7,		 7 },
	{ PIRQ_I2C0,	 3,		 3 },
	{ PIRQ_I2C1,	15,		15 },
	{ PIRQ_I2C2,	 6,		 6 },
	{ PIRQ_I2C3,	14,		14 },
	{ PIRQ_UART0,	10,		10 },
	{ PIRQ_UART1,	11,		11 },

	/* The MISC registers are not interrupt numbers */
	{ PIRQ_MISC,	0xfa,	0x00 },
	{ PIRQ_MISC0,	0xf1,	0x00 },
	{ PIRQ_MISC1,	0x00,	0x00 },
	{ PIRQ_MISC2,	0x00,	0x00 },
};

static const struct fch_irq_routing *mb_get_fch_irq_mapping(size_t *length)
{
	*length = ARRAY_SIZE(fch_irq_map);
	return fch_irq_map;
}

static void init_tables(void)
{
	const struct fch_irq_routing *mb_irq_map;
	size_t mb_fch_irq_mapping_table_size;
	size_t i;

	mb_irq_map = mb_get_fch_irq_mapping(&mb_fch_irq_mapping_table_size);

	memset(fch_pic_routing, PIRQ_NC, sizeof(fch_pic_routing));
	memset(fch_apic_routing, PIRQ_NC, sizeof(fch_apic_routing));

	for (i = 0; i < mb_fch_irq_mapping_table_size; i++) {
		if (mb_irq_map[i].intr_index >= FCH_IRQ_ROUTING_ENTRIES) {
			printk(BIOS_WARNING,
			       "Invalid IRQ index %u in FCH IRQ routing table entry %zu\n",
			       mb_irq_map[i].intr_index, i);
			continue;
		}
		fch_pic_routing[mb_irq_map[i].intr_index] = mb_irq_map[i].pic_irq_num;
		fch_apic_routing[mb_irq_map[i].intr_index] = mb_irq_map[i].apic_irq_num;
	}
}

/* PIRQ Setup */
static void pirq_setup(void)
{
	intr_data_ptr = fch_apic_routing;
	picr_data_ptr = fch_pic_routing;
}

static void mainboard_init(void *chip_info)
{
	size_t num_gpios;
	const struct soc_amd_gpio *gpios;
	gpios = gpio_table(&num_gpios);
	gpio_configure_pads(gpios, num_gpios);
}

/*************************************************
 * enable the dedicated function in gardenia board.
 *************************************************/
static void mainboard_enable(struct device *dev)
{
	init_tables();
	/* Initialize the PIRQ data structures for consumption */
	pirq_setup();
}

struct chip_operations mainboard_ops = {
	.init = mainboard_init,
	.enable_dev = mainboard_enable,
};
