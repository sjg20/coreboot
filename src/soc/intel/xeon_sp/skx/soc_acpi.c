/* SPDX-License-Identifier: GPL-2.0-only */

#include <acpi/acpi_gnvs.h>
#include <acpi/acpigen.h>
#include <arch/smp/mpspec.h>
#include <assert.h>
#include <cbmem.h>
#include <cpu/intel/turbo.h>
#include <device/mmio.h>
#include <device/pci.h>
#include <intelblocks/acpi.h>
#include <soc/acpi.h>
#include <soc/cpu.h>
#include <soc/iomap.h>
#include <device/mmio.h>
#include <soc/msr.h>
#include <soc/pci_devs.h>
#include <soc/pm.h>
#include <soc/soc_util.h>

#include "chip.h"

/* TODO: Check if the common/acpi weak function can be used */
unsigned long acpi_fill_mcfg(unsigned long current)
{
	current += acpi_create_mcfg_mmconfig((acpi_mcfg_mmconfig_t *)current,
		CONFIG_MMCONF_BASE_ADDRESS, 0, 0, 255);
	return current;
}

void acpi_init_gnvs(struct global_nvs *gnvs)
{
	/* CPU core count */
	gnvs->pcnt = dev_count_cpu();
	printk(BIOS_DEBUG, "%s gnvs->pcnt: %d\n", __func__, gnvs->pcnt);

	/* Update the mem console pointer. */
	if (CONFIG(CONSOLE_CBMEM))
		gnvs->cbmc = (uint32_t)cbmem_find(CBMEM_ID_CONSOLE);
}

int soc_madt_sci_irq_polarity(int sci)
{
	if (sci >= 20)
		return MP_IRQ_POLARITY_LOW;
	else
		return MP_IRQ_POLARITY_HIGH;
}

uint32_t soc_read_sci_irq_select(void)
{
	struct device *dev = PCH_DEV_PMC;

	if (!dev)
		return 0;

	return pci_read_config32(dev, PMC_ACPI_CNT);
}

/*
 * Currently called in southbridge_inject_dsdt(). Change to soc_southbridge_inject_dsdt()
 * with a call from the common/function or find another way to call this at the correct place
 */
void uncore_inject_dsdt(void)
{
	size_t hob_size;
	const uint8_t uds_guid[16] = FSP_HOB_IIO_UNIVERSAL_DATA_GUID;
	const IIO_UDS *hob = fsp_find_extension_hob_by_guid(uds_guid, &hob_size);
	assert(hob != NULL && hob_size != 0);

	acpigen_write_scope("\\_SB");
	for (int socket = 0; socket < hob->PlatformData.numofIIO; ++socket) {
		IIO_RESOURCE_INSTANCE iio_resource =
			hob->PlatformData.IIO_resource[socket];
		for (int stack = 0; stack <= PSTACK2; ++stack) {
			const STACK_RES *ri = &iio_resource.StackRes[stack];
			char rtname[16];
			snprintf(rtname, sizeof(rtname), "RT%02x",
				(socket*MAX_IIO_STACK)+stack);

			acpigen_write_name(rtname);
			printk(BIOS_DEBUG, "\tCreating ResourceTemplate %s for socket: %d, stack: %d\n",
				rtname, socket, stack);

			acpigen_write_resourcetemplate_header();

			/* bus resource */
			acpigen_resource_word(2, 0xc, 0, 0, ri->BusBase, ri->BusLimit,
				0x0, (ri->BusLimit - ri->BusBase + 1));

			// additional io resources on socket 0 bus 0
			if (socket == 0 && stack == 0) {
				/* ACPI 6.4.2.5 I/O Port Descriptor */
				acpigen_write_io16(0xCF8, 0xCFF, 0x1, 0x8, 1);

				/* IO decode  CF8-CFF */
				acpigen_resource_word(1, 0xc, 0x3, 0, 0x0000, 0x03AF,
					0, 0x03B0);
				acpigen_resource_word(1, 0xc, 0x3, 0, 0x03E0, 0x0CF7,
					0, 0x0918);
				acpigen_resource_word(1, 0xc, 0x3, 0, 0x03B0, 0x03BB,
					0, 0x000C);
				acpigen_resource_word(1, 0xc, 0x3, 0, 0x03C0, 0x03DF,
					0, 0x0020);
			}

			/* IO resource */
			acpigen_resource_word(1, 0xc, 0x3, 0, ri->PciResourceIoBase,
				ri->PciResourceIoLimit, 0x0,
				(ri->PciResourceIoLimit - ri->PciResourceIoBase + 1));

			// additional mem32 resources on socket 0 bus 0
			if (socket == 0 && stack == 0) {
				acpigen_resource_dword(0, 0xc, 3, 0, VGA_BASE_ADDRESS,
					(VGA_BASE_ADDRESS + VGA_BASE_SIZE - 1), 0x0,
					VGA_BASE_SIZE);
				acpigen_resource_dword(0, 0xc, 1, 0, SPI_BASE_ADDRESS,
					(SPI_BASE_ADDRESS + SPI_BASE_SIZE - 1), 0x0,
					SPI_BASE_SIZE);
			}

			/* Mem32 resource */
			acpigen_resource_dword(0, 0xc, 1, 0, ri->PciResourceMem32Base,
				ri->PciResourceMem32Limit, 0x0,
				(ri->PciResourceMem32Limit - ri->PciResourceMem32Base + 1));

			/* Mem64 resource */
			acpigen_resource_qword(0, 0xc, 1, 0, ri->PciResourceMem64Base,
				ri->PciResourceMem64Limit, 0x0,
				(ri->PciResourceMem64Limit - ri->PciResourceMem64Base + 1));

			acpigen_write_resourcetemplate_footer();
		}
	}
	acpigen_pop_len();
}

unsigned long xeonsp_acpi_create_madt_lapics(unsigned long current)
{
	struct device *cpu;
	int num_cpus = 0;

	for (cpu = all_devices; cpu; cpu = cpu->next) {
		if ((cpu->path.type != DEVICE_PATH_APIC) ||
			(cpu->bus->dev->path.type != DEVICE_PATH_CPU_CLUSTER)) {
			continue;
		}
		if (!cpu->enabled)
			continue;
		current += acpi_create_madt_lapic((acpi_madt_lapic_t *)current,
			num_cpus, cpu->path.apic.apic_id);
	}

	return current;
}
