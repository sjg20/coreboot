/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2008-2009 coresystems GmbH
 * Copyright (C) 2014 Google Inc.
 * Copyright (C) 2015 Intel Corporation.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <chip.h>
#include <console/console.h>
#include <device/device.h>
#include <device/pci.h>
#include <device/pci_ids.h>
#include <arch/io.h>
#include <arch/ioapic.h>
#include <arch/acpi.h>
#include <cpu/cpu.h>
#include <intelblocks/pcr.h>
#include <intelblocks/pmclib.h>
#include <pc80/mc146818rtc.h>
#include <reg_script.h>
#include <string.h>
#include <soc/gpio.h>
#include <soc/iomap.h>
#include <soc/pci_devs.h>
#include <soc/pm.h>
#include <soc/pmc.h>
#include <cpu/x86/smm.h>
#include <soc/pcr_ids.h>
#include <soc/ramstage.h>

static const struct reg_script pch_pmc_misc_init_script[] = {
	/* SLP_S4=4s, SLP_S3=50ms, disable SLP_X stretching after SUS loss. */
	REG_PCI_RMW16(GEN_PMCON_B,
			~(S4MAW_MASK | SLP_S3_MIN_ASST_WDTH_MASK),
			S4MAW_4S | SLP_S3_MIN_ASST_WDTH_50MS |
			DIS_SLP_X_STRCH_SUS_UP),
	/* Enable SCI and clear SLP requests. */
	REG_IO_RMW32(ACPI_BASE_ADDRESS + PM1_CNT, ~SLP_TYP, SCI_EN),
	REG_SCRIPT_END
};

static const struct reg_script pmc_write1_to_clear_script[] = {
	REG_PCI_OR32(GEN_PMCON_A, 0),
	REG_PCI_OR32(GEN_PMCON_B, 0),
	REG_PCI_OR32(GEN_PMCON_B, 0),
	REG_RES_OR32(PWRMBASE, GBLRST_CAUSE0, 0),
	REG_RES_OR32(PWRMBASE, GBLRST_CAUSE1, 0),
	REG_SCRIPT_END
};

static void pch_pmc_add_mmio_resources(device_t dev)
{
	struct resource *res;

	/* Memory-mmapped I/O registers. */
	res = new_resource(dev, PWRMBASE);
	res->base = PCH_PWRM_BASE_ADDRESS;
	res->size = PCH_PWRM_BASE_SIZE;
	res->flags = IORESOURCE_MEM | IORESOURCE_ASSIGNED |
			IORESOURCE_FIXED | IORESOURCE_RESERVE;
}

static void pch_pmc_add_io_resource(device_t dev, u16 base, u16 size, int index)
{
	struct resource *res;
	res = new_resource(dev, index);
	res->base = base;
	res->size = size;
	res->flags = IORESOURCE_IO | IORESOURCE_ASSIGNED | IORESOURCE_FIXED;
}

static void pch_pmc_add_io_resources(device_t dev)
{
	/* PMBASE */
	pch_pmc_add_io_resource(dev, ACPI_BASE_ADDRESS, ACPI_BASE_SIZE, ABASE);
}

static void pch_pmc_read_resources(device_t dev)
{
	/* Get the normal PCI resources of this device. */
	pci_dev_read_resources(dev);

	/* Add non-standard MMIO resources. */
	pch_pmc_add_mmio_resources(dev);

	/* Add IO resources. */
	pch_pmc_add_io_resources(dev);
}

static void pch_set_acpi_mode(void)
{
	if (IS_ENABLED(CONFIG_HAVE_SMI_HANDLER) && !acpi_is_wakeup_s3()) {
		printk(BIOS_DEBUG, "Disabling ACPI via APMC:\n");
		outb(APM_CNT_ACPI_DISABLE, APM_CNT);
		printk(BIOS_DEBUG, "done.\n");
	}
}

static void pch_rtc_init(void)
{
	/* Ensure the date is set including century byte. */
	cmos_check_update_date();

	cmos_init(rtc_failure());
}

static void pch_power_options(void)
{
	u16 reg16;
	const char *state;
	/*PMC Controller Device 0x1F, Func 02*/
	device_t dev = PCH_DEV_PMC;
	/* Get the chip configuration */
	int pwr_on = CONFIG_MAINBOARD_POWER_ON_AFTER_POWER_FAIL;

	/*
	 * Which state do we want to goto after g3 (power restored)?
	 * 0 == S0 Full On
	 * 1 == S5 Soft Off
	 *
	 * If the option is not existent (Laptops), use Kconfig setting.
	 */
	/*TODO: cmos_layout.bin need to verify; cause wrong CMOS setup*/
	//get_option(&pwr_on, "power_on_after_fail");
	pwr_on = MAINBOARD_POWER_ON;
	reg16 = pci_read_config16(dev, GEN_PMCON_B);
	reg16 &= 0xfffe;
	switch (pwr_on) {
	case MAINBOARD_POWER_OFF:
		reg16 |= 1;
		state = "off";
		break;
	case MAINBOARD_POWER_ON:
		reg16 &= ~1;
		state = "on";
		break;
	case MAINBOARD_POWER_KEEP:
		reg16 &= ~1;
		state = "state keep";
		break;
	default:
		state = "undefined";
	}
	pci_write_config16(dev, GEN_PMCON_B, reg16);
	printk(BIOS_INFO, "Set power %s after power failure.\n", state);

	/* Set up GPE configuration. */
	pmc_gpe_init();
}

static void config_deep_sX(uint32_t offset, uint32_t mask, int sx, int enable)
{
	uint32_t reg;
	uint8_t *pmcbase = pmc_mmio_regs();

	printk(BIOS_DEBUG, "%sabling Deep S%c\n",
		enable ? "En" : "Dis", sx + '0');
	reg = read32(pmcbase + offset);
	if (enable)
		reg |= mask;
	else
		reg &= ~mask;
	write32(pmcbase + offset, reg);
}

static void config_deep_s5(int on_ac, int on_dc)
{
	/* Treat S4 the same as S5. */
	config_deep_sX(S4_PWRGATE_POL, S4AC_GATE_SUS, 4, on_ac);
	config_deep_sX(S4_PWRGATE_POL, S4DC_GATE_SUS, 4, on_dc);
	config_deep_sX(S5_PWRGATE_POL, S5AC_GATE_SUS, 5, on_ac);
	config_deep_sX(S5_PWRGATE_POL, S5DC_GATE_SUS, 5, on_dc);
}

static void config_deep_s3(int on_ac, int on_dc)
{
	config_deep_sX(S3_PWRGATE_POL, S3AC_GATE_SUS, 3, on_ac);
	config_deep_sX(S3_PWRGATE_POL, S3DC_GATE_SUS, 3, on_dc);
}

static void config_deep_sx(uint32_t deepsx_config)
{
	uint32_t reg;
	uint8_t *pmcbase = pmc_mmio_regs();

	reg = read32(pmcbase + DSX_CFG);
	reg &= ~DSX_CFG_MASK;
	reg |= deepsx_config;
	write32(pmcbase + DSX_CFG, reg);
}

static void pmc_init(struct device *dev)
{
	config_t *config = dev->chip_info;

	pch_rtc_init();

	/* Initialize power management */
	pch_power_options();

	/* Note that certain bits may be cleared from running script as
	 * certain bit fields are write 1 to clear. */
	reg_script_run_on_dev(dev, pch_pmc_misc_init_script);
	pch_set_acpi_mode();

	config_deep_s3(config->deep_s3_enable_ac, config->deep_s3_enable_dc);
	config_deep_s5(config->deep_s5_enable_ac, config->deep_s5_enable_dc);
	config_deep_sx(config->deep_sx_config);

	/* Clear registers that contain write-1-to-clear bits. */
	reg_script_run_on_dev(dev, pmc_write1_to_clear_script);
}

static struct device_operations device_ops = {
	.read_resources		= &pch_pmc_read_resources,
	.set_resources		= &pci_dev_set_resources,
	.enable_resources	= &pci_dev_enable_resources,
	.init			= &pmc_init,
	.scan_bus		= &scan_lpc_bus,
	.ops_pci		= &soc_pci_ops,
};

static const unsigned short pci_device_ids[] = {
	0x9d21,
	0xa121,
	0
};

static const struct pci_driver pch_lpc __pci_driver = {
	.ops	 = &device_ops,
	.vendor	 = PCI_VENDOR_ID_INTEL,
	.devices = pci_device_ids,
};
