/* SPDX-License-Identifier: GPL-2.0-only */

#include <console/console.h>
#include <device/device.h>
#include <acpi/acpi.h>
#include <amdblocks/amd_pci_util.h>
#include <FspsUpd.h>
#include <soc/cpu.h>
#include <soc/southbridge.h>
#include <soc/pci_devs.h>
#include <types.h>
#include <commonlib/helpers.h>
#include <chip.h>
#include "gpio.h"

/* TODO: recheck IRQ tables */

/*
 * These arrays set up the FCH PCI_INTR registers 0xC00/0xC01.
 * This table is responsible for physically routing the PIC and
 * IOAPIC IRQs to the different PCI devices on the system.  It
 * is read and written via registers 0xC00/0xC01 as an
 * Index/Data pair.  These values are chipset and mainboard
 * dependent and should be updated accordingly.
 */
static uint8_t fch_pic_routing[0x80];
static uint8_t fch_apic_routing[0x80];

_Static_assert(sizeof(fch_pic_routing) == sizeof(fch_apic_routing),
	"PIC and APIC FCH interrupt tables must be the same size");

/*
 * This table doesn't actually perform any routing. It only populates the
 * PCI_INTERRUPT_LINE register on the PCI device with the PIC value specified
 * in fch_apic_routing. The linux kernel only looks at this field as a backup
 * if ACPI routing fails to describe the PCI routing correctly. The linux kernel
 * also uses the APIC by default, so the value coded into the registers will be
 * wrong.
 *
 * This table is also confusing because PCI Interrupt routing happens at the
 * device/slot level, not the function level.
 */
static const struct pirq_struct mainboard_pirq_data[] = {
	{ PCIE_GPP_0_DEVFN,	{ PIRQ_A, PIRQ_B, PIRQ_C, PIRQ_D } },
	{ PCIE_GPP_1_DEVFN,	{ PIRQ_A, PIRQ_B, PIRQ_C, PIRQ_D } },
	{ PCIE_GPP_2_DEVFN,	{ PIRQ_A, PIRQ_B, PIRQ_C, PIRQ_D } },
	{ PCIE_GPP_3_DEVFN,	{ PIRQ_A, PIRQ_B, PIRQ_C, PIRQ_D } },
	{ PCIE_GPP_4_DEVFN,	{ PIRQ_A, PIRQ_B, PIRQ_C, PIRQ_D } },
	{ PCIE_GPP_5_DEVFN,	{ PIRQ_A, PIRQ_B, PIRQ_C, PIRQ_D } },
	{ PCIE_GPP_6_DEVFN,	{ PIRQ_A, PIRQ_B, PIRQ_C, PIRQ_D } },
	{ PCIE_GPP_A_DEVFN,	{ PIRQ_A, PIRQ_B, PIRQ_C, PIRQ_D } },
	{ PCIE_GPP_B_DEVFN,	{ PIRQ_A, PIRQ_B, PIRQ_C, PIRQ_D } },
	{ SMBUS_DEVFN,	{ PIRQ_SMBUS, PIRQ_NC, PIRQ_NC, PIRQ_NC } },
};

static const struct fch_irq_routing {
	uint8_t intr_index;
	uint8_t pic_irq_num;
	uint8_t apic_irq_num;
} mandolin_fch[] = {
	{ PIRQ_A,	8,		16 },
	{ PIRQ_B,	10,		17 },
	{ PIRQ_C,	11,		18 },
	{ PIRQ_D,	12,		19 },
	{ PIRQ_SCI,	9,		 9 },
	{ PIRQ_SD,	PIRQ_NC,	16 },
	{ PIRQ_SDIO,	PIRQ_NC,	16 },
	{ PIRQ_SATA,	PIRQ_NC,	19 },
	{ PIRQ_EMMC,	PIRQ_NC,	17 },
	{ PIRQ_GPIO,	 7,		 7 },
	{ PIRQ_I2C2,	 6,		 6 },
	{ PIRQ_I2C3,	14,		14 },
	{ PIRQ_UART0,	 4,		 4 },
	{ PIRQ_UART1,	 3,		 3 },
	{ PIRQ_UART2,	 4,		 4 },
	{ PIRQ_UART3,	 3,		 3 },

	/* The MISC registers are not interrupt numbers */
	{ PIRQ_MISC,	0xfa,		0x00 },
	{ PIRQ_MISC0,	0x91,		0x00 },
	{ PIRQ_MISC1,	0x00,		0x00 },
	{ PIRQ_MISC2,	0x00,		0x00 },
};

static void init_tables(void)
{
	const struct fch_irq_routing *entry;
	int i;

	memset(fch_pic_routing, PIRQ_NC, sizeof(fch_pic_routing));
	memset(fch_apic_routing, PIRQ_NC, sizeof(fch_apic_routing));

	for (i = 0; i < ARRAY_SIZE(mandolin_fch); i++) {
		entry = mandolin_fch + i;
		fch_pic_routing[entry->intr_index] = entry->pic_irq_num;
		fch_apic_routing[entry->intr_index] = entry->apic_irq_num;
	}
}

static void pirq_setup(void)
{
	init_tables();

	pirq_data_ptr = mainboard_pirq_data;
	pirq_data_size = ARRAY_SIZE(mainboard_pirq_data);
	intr_data_ptr = fch_apic_routing;
	picr_data_ptr = fch_pic_routing;
}

static void mainboard_init(void *chip_info)
{
	struct soc_amd_picasso_config *cfg = config_of_soc();

	if (!CONFIG(MANDOLIN_LPC))
		cfg->emmc_config.timing = SD_EMMC_EMMC_HS400;

	mainboard_program_gpios();

	/* Re-muxing LPCCLK0 can hang the system if LPC is in use. */
	if (CONFIG(MANDOLIN_LPC))
		printk(BIOS_INFO, "eMMC not available due to LPC requirement\n");
	else
		mainboard_program_emmc_gpios();
}

static void mandolin_enable(struct device *dev)
{
	printk(BIOS_INFO, "Mainboard " CONFIG_MAINBOARD_PART_NUMBER " Enable.\n");

	/* Initialize the PIRQ data structures for consumption */
	pirq_setup();
}

struct chip_operations mainboard_ops = {
	.init = mainboard_init,
	.enable_dev = mandolin_enable,
};
