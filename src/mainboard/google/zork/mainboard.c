/* SPDX-License-Identifier: GPL-2.0-or-later */

#include <string.h>
#include <console/console.h>
#include <cbfs.h>
#include <device/device.h>
#include <device/mmio.h>
#include <acpi/acpi.h>
#include <amdblocks/amd_pci_util.h>
#include <amdblocks/gpio_banks.h>
#include <cbmem.h>
#include <baseboard/variants.h>
#include <boardid.h>
#include <gpio.h>
#include <smbios.h>
#include <soc/cpu.h>
#include <soc/gpio.h>
#include <soc/nvs.h>
#include <soc/pci_devs.h>
#include <soc/platform_descriptors.h>
#include <soc/southbridge.h>
#include <soc/smi.h>
#include <soc/soc_util.h>
#include <amdblocks/acpimmio.h>
#include <variant/ec.h>
#include <variant/thermal.h>
#include <vendorcode/google/chromeos/chromeos.h>
#include <commonlib/helpers.h>
#include <bootstate.h>

/***********************************************************
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
	{ PCIE_GPP_1_DEVFN,	{ PIRQ_A, PIRQ_B, PIRQ_C, PIRQ_D } }, // Bridge 1 - Wifi
	{ PCIE_GPP_2_DEVFN,	{ PIRQ_A, PIRQ_B, PIRQ_C, PIRQ_D } }, // Bridge 2 - SD
	{ PCIE_GPP_3_DEVFN,	{ PIRQ_A, PIRQ_B, PIRQ_C, PIRQ_D } },
	{ PCIE_GPP_4_DEVFN,	{ PIRQ_A, PIRQ_B, PIRQ_C, PIRQ_D } },
	{ PCIE_GPP_5_DEVFN,	{ PIRQ_A, PIRQ_B, PIRQ_C, PIRQ_D } },
	{ PCIE_GPP_6_DEVFN,	{ PIRQ_A, PIRQ_B, PIRQ_C, PIRQ_D } }, // Bridge 6 - NVME
	{ PCIE_GPP_A_DEVFN,	{ PIRQ_A, PIRQ_B, PIRQ_C, PIRQ_D } },
	{ PCIE_GPP_B_DEVFN,	{ PIRQ_A, PIRQ_B, PIRQ_C, PIRQ_D } },
	{ SMBUS_DEVFN,	{ PIRQ_SMBUS, PIRQ_NC, PIRQ_NC, PIRQ_NC } },
};

/*
 * This controls the device -> IRQ routing.
 * The PIC values are limited to 0,1, 3 - 12, 14, 15.
 */
static const struct fch_apic_routing {
	uint8_t intr_index;
	uint8_t pic_irq_num;
	uint8_t apic_irq_num;
} fch_pirq[] = {
	{ PIRQ_A,	6,		16 },
	{ PIRQ_B,	6,		17 },
	{ PIRQ_C,	14,		18 },
	{ PIRQ_D,	15,		19 },
	{ PIRQ_E,	PIRQ_NC,	PIRQ_NC },
	{ PIRQ_F,	PIRQ_NC,	PIRQ_NC },
	{ PIRQ_G,	PIRQ_NC,	PIRQ_NC },
	{ PIRQ_H,	PIRQ_NC,	PIRQ_NC },
	{ PIRQ_SIRQA,	PIRQ_NC,	PIRQ_NC },
	{ PIRQ_SIRQB,	PIRQ_NC,	PIRQ_NC },
	{ PIRQ_SIRQC,	PIRQ_NC,	PIRQ_NC },
	{ PIRQ_SIRQD,	PIRQ_NC,	PIRQ_NC },
	{ PIRQ_SCI,	9,		9 },
	{ PIRQ_SMBUS,	PIRQ_NC,	PIRQ_NC },
	{ PIRQ_ASF,	PIRQ_NC,	PIRQ_NC },
	{ PIRQ_PMON,	PIRQ_NC,	PIRQ_NC },
	{ PIRQ_SD,	PIRQ_NC,	PIRQ_NC },
	{ PIRQ_SDIO,	PIRQ_NC,	PIRQ_NC },
	{ PIRQ_CIR,	PIRQ_NC,	PIRQ_NC },
	{ PIRQ_GPIOA,	PIRQ_NC,	PIRQ_NC },
	{ PIRQ_GPIOB,	PIRQ_NC,	PIRQ_NC },
	{ PIRQ_GPIOC,	PIRQ_NC,	PIRQ_NC },
	{ PIRQ_SATA,	PIRQ_NC,	PIRQ_NC },
	{ PIRQ_EMMC,	5,		5 },
	{ PIRQ_GPP0,	PIRQ_NC,	PIRQ_NC },
	{ PIRQ_GPP1,	PIRQ_NC,	PIRQ_NC },
	{ PIRQ_GPP2,	PIRQ_NC,	PIRQ_NC },
	{ PIRQ_GPP3,	PIRQ_NC,	PIRQ_NC },
	{ PIRQ_GPIO,	7,		7 },
	{ PIRQ_I2C0,	PIRQ_NC,	PIRQ_NC },
	{ PIRQ_I2C1,	PIRQ_NC,	PIRQ_NC },
	{ PIRQ_I2C2,	10,		10 },
	{ PIRQ_I2C3,	11,		11 },
	{ PIRQ_UART0,	4,		4 },
	{ PIRQ_UART1,	3,		3 },
	{ PIRQ_I2C4,	PIRQ_NC,	PIRQ_NC },
	{ PIRQ_I2C5,	PIRQ_NC,	PIRQ_NC },
	{ PIRQ_UART2,	PIRQ_NC,	PIRQ_NC },
	{ PIRQ_UART3,	PIRQ_NC,	PIRQ_NC },

	/* The MISC registers are not interrupt numbers */
	{ PIRQ_MISC,	0xfa,		0x00 },
	{ PIRQ_MISC0,	0xf1,		0x00 },
	{ PIRQ_MISC1,	0x00,		0x00 },
	{ PIRQ_MISC2,	0x00,		0x00 },
};

static void init_tables(void)
{
	const struct fch_apic_routing *entry;
	int i;

	memset(fch_pic_routing, PIRQ_NC, sizeof(fch_pic_routing));
	memset(fch_apic_routing, PIRQ_NC, sizeof(fch_apic_routing));

	for (i = 0; i < ARRAY_SIZE(fch_pirq); i++) {
		entry = fch_pirq + i;
		fch_pic_routing[entry->intr_index] = entry->pic_irq_num;
		fch_apic_routing[entry->intr_index] = entry->apic_irq_num;
	}
}

/* PIRQ Setup */
static void pirq_setup(void)
{
	init_tables();

	pirq_data_ptr = mainboard_pirq_data;
	pirq_data_size = ARRAY_SIZE(mainboard_pirq_data);
	intr_data_ptr = fch_apic_routing;
	picr_data_ptr = fch_pic_routing;
}

static void mainboard_configure_gpios(void)
{
	size_t base_num_gpios, override_num_gpios;
	const struct soc_amd_gpio *base_gpios, *override_gpios;

	base_gpios = variant_base_gpio_table(&base_num_gpios);
	override_gpios = variant_override_gpio_table(&override_num_gpios);

	gpio_configure_pads_with_override(base_gpios, base_num_gpios, override_gpios,
					  override_num_gpios);
}

static void mainboard_init(void *chip_info)
{
	const struct sci_source *gpes;
	size_t num;
	int boardid;

	mainboard_ec_init();
	boardid = board_id();
	printk(BIOS_INFO, "Board ID: %d\n", boardid);

	mainboard_configure_gpios();

	/* Update DUT configuration */
	variant_devtree_update();

	/*
	 * Some platforms use SCI not generated by a GPIO pin (event above 23).
	 * For these boards, gpe_configure_sci() is still needed, but all GPIO
	 * generated events (23-0) must be removed from gpe_table[].
	 * For boards that only have GPIO generated events, table gpe_table[]
	 * must be removed, and get_gpe_table() should return NULL.
	 */
	gpes = get_gpe_table(&num);
	if (gpes != NULL)
		gpe_configure_sci(gpes, num);
}

void mainboard_get_pcie_ddi_descriptors(const picasso_fsp_pcie_descriptor **pcie_descs,
					size_t *pcie_num,
					const picasso_fsp_ddi_descriptor **ddi_descs,
					size_t *ddi_num)
{
	variant_get_pcie_ddi_descriptors(pcie_descs, pcie_num, ddi_descs, ddi_num);
}

/*************************************************
 * Dedicated mainboard function
 *************************************************/
static void zork_enable(struct device *dev)
{
	printk(BIOS_INFO, "Mainboard " CONFIG_MAINBOARD_PART_NUMBER " Enable.\n");

	/* Initialize the PIRQ data structures for consumption */
	pirq_setup();

	dev->ops->acpi_inject_dsdt = chromeos_dsdt_generator;
}

static const struct soc_amd_gpio gpio_set_bl[] = {
	PAD_GPO(GPIO_85, LOW),
};

static void reset_backlight_gpio(void *unused)
{
	printk(BIOS_DEBUG, "Reset backlight GPIO\n");
	/* Re-Enable backlight - GPIO 85 active low */
	/* TODO: Remove this after AGESA stops enabling the fan - b/155667589 */
	program_gpios(gpio_set_bl, ARRAY_SIZE(gpio_set_bl)); /*  APU_EDP_BL_DISABLE */
}

static void mainboard_final(void *chip_info)
{
	struct global_nvs_t *gnvs;

	gnvs = cbmem_find(CBMEM_ID_ACPI_GNVS);

	reset_backlight_gpio(NULL);

	if (gnvs) {
		gnvs->tmps = CTL_TDP_SENSOR_ID;
		gnvs->tcrt = CRITICAL_TEMPERATURE;
		gnvs->tpsv = PASSIVE_TEMPERATURE;
	}
}

struct chip_operations mainboard_ops = {
	.init = mainboard_init,
	.enable_dev = zork_enable,
	.final = mainboard_final,
};

void __weak variant_devtree_update(void)
{
}

__weak const struct soc_amd_gpio *variant_override_gpio_table(size_t *size)
{
	/* Default weak implementation - No overrides. */
	*size = 0;
	return NULL;
}

BOOT_STATE_INIT_ENTRY(BS_OS_RESUME, BS_ON_ENTRY, reset_backlight_gpio, NULL);
