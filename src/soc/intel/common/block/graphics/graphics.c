/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2017-2018 Intel Corp.
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

#include <assert.h>
#include <console/console.h>
#include <device/mmio.h>
#include <device/pci.h>
#include <device/pci_ids.h>
#include <intelblocks/graphics.h>
#include <soc/pci_devs.h>

/* SoC Overrides */
__weak void graphics_soc_init(struct device *dev)
{
	/*
	 * User needs to implement SoC override in case wishes
	 * to perform certain specific graphics initialization
	 * along with pci_dev_init(dev)
	 */
	pci_dev_init(dev);
}

static uintptr_t graphics_get_bar(unsigned long index)
{
	struct device *dev = SA_DEV_IGD;
	struct resource *gm_res;
	assert(dev != NULL);

	/* Check if Graphics PCI device is disabled */
	if (!dev || !dev->enabled)
		return 0;

	gm_res = find_resource(dev, index);
	if (!gm_res)
		return 0;

	return gm_res->base;
}

uintptr_t graphics_get_memory_base(void)
{
	/*
	 * GFX PCI config space offset 0x18 know as Graphics
	 * Memory Range Address (GMADR)
	 */
	uintptr_t memory_base = graphics_get_bar(PCI_BASE_ADDRESS_2);
	if (!memory_base)
		die("GMADR is not programmed!");

	return memory_base;
}

static uintptr_t graphics_get_gtt_base(void)
{
	/*
	 * GFX PCI config space offset 0x10 know as Graphics
	 * Translation Table Memory Mapped Range Address
	 * (GTTMMADR)
	 */
	static uintptr_t gtt_base;
	if (!gtt_base) {
		gtt_base = graphics_get_bar(PCI_BASE_ADDRESS_0);
		if (!gtt_base)
			die("GTTMMADR is not programmed!");
	}
	return gtt_base;
}

uint32_t graphics_gtt_read(unsigned long reg)
{
	return read32((void *)(graphics_get_gtt_base() + reg));
}

void graphics_gtt_write(unsigned long reg, uint32_t data)
{
	write32((void *)(graphics_get_gtt_base() + reg), data);
}

void graphics_gtt_rmw(unsigned long reg, uint32_t andmask, uint32_t ormask)
{
	uint32_t val = graphics_gtt_read(reg);
	val &= andmask;
	val |= ormask;
	graphics_gtt_write(reg, val);
}

static const struct device_operations graphics_ops = {
	.read_resources		= pci_dev_read_resources,
	.set_resources		= pci_dev_set_resources,
	.enable_resources	= pci_dev_enable_resources,
	.init			= graphics_soc_init,
	.ops_pci		= &pci_dev_ops_pci,
	.write_acpi_tables	= graphics_soc_write_acpi_opregion,
};

static const unsigned short pci_device_ids[] = {
	PCI_DEVICE_ID_INTEL_APL_IGD_HD_505,
	PCI_DEVICE_ID_INTEL_APL_IGD_HD_500,
	PCI_DEVICE_ID_INTEL_CNL_GT2_ULX_1,
	PCI_DEVICE_ID_INTEL_CNL_GT2_ULX_2,
	PCI_DEVICE_ID_INTEL_CNL_GT2_ULX_3,
	PCI_DEVICE_ID_INTEL_CNL_GT2_ULX_4,
	PCI_DEVICE_ID_INTEL_CNL_GT2_ULT_1,
	PCI_DEVICE_ID_INTEL_CNL_GT2_ULT_2,
	PCI_DEVICE_ID_INTEL_CNL_GT2_ULT_3,
	PCI_DEVICE_ID_INTEL_CNL_GT2_ULT_4,
	PCI_DEVICE_ID_INTEL_GLK_IGD,
	PCI_DEVICE_ID_INTEL_GLK_IGD_EU12,
	PCI_DEVICE_ID_INTEL_WHL_GT1_ULT_1,
	PCI_DEVICE_ID_INTEL_WHL_GT2_ULT_1,
	PCI_DEVICE_ID_INTEL_KBL_GT1_SULTM,
	PCI_DEVICE_ID_INTEL_KBL_GT2_SULXM,
	PCI_DEVICE_ID_INTEL_KBL_GT2_SULTM,
	PCI_DEVICE_ID_INTEL_KBL_GT2_SULTMR,
	PCI_DEVICE_ID_INTEL_KBL_GT2_SHALM,
	PCI_DEVICE_ID_INTEL_KBL_GT2_DT2P2,
	PCI_DEVICE_ID_INTEL_AML_GT2_ULX,
	PCI_DEVICE_ID_INTEL_SKL_GT1_SULTM,
	PCI_DEVICE_ID_INTEL_SKL_GT2_DT2P1,
	PCI_DEVICE_ID_INTEL_SKL_GT2_SULXM,
	PCI_DEVICE_ID_INTEL_SKL_GT2_SULTM,
	PCI_DEVICE_ID_INTEL_SKL_GT2_SHALM,
	PCI_DEVICE_ID_INTEL_SKL_GT2_SWKSM,
	PCI_DEVICE_ID_INTEL_SKL_GT4_SHALM,
	PCI_DEVICE_ID_INTEL_CFL_H_GT2,
	PCI_DEVICE_ID_INTEL_CFL_S_GT2,
	PCI_DEVICE_ID_INTEL_ICL_GT0_ULT,
	PCI_DEVICE_ID_INTEL_ICL_GT0_5_ULT,
	PCI_DEVICE_ID_INTEL_ICL_GT1_ULT,
	PCI_DEVICE_ID_INTEL_ICL_GT2_ULX_0,
	PCI_DEVICE_ID_INTEL_ICL_GT2_ULX_1,
	PCI_DEVICE_ID_INTEL_ICL_GT2_ULT_1,
	PCI_DEVICE_ID_INTEL_ICL_GT2_ULX_2,
	PCI_DEVICE_ID_INTEL_ICL_GT2_ULT_2,
	PCI_DEVICE_ID_INTEL_ICL_GT2_ULX_3,
	PCI_DEVICE_ID_INTEL_ICL_GT2_ULT_3,
	PCI_DEVICE_ID_INTEL_ICL_GT2_ULX_4,
	PCI_DEVICE_ID_INTEL_ICL_GT2_ULT_4,
	PCI_DEVICE_ID_INTEL_ICL_GT2_ULX_5,
	PCI_DEVICE_ID_INTEL_ICL_GT2_ULT_5,
	PCI_DEVICE_ID_INTEL_ICL_GT2_ULX_6,
	PCI_DEVICE_ID_INTEL_ICL_GT3_ULT,
	PCI_DEVICE_ID_INTEL_CML_GT1_ULT_1,
	PCI_DEVICE_ID_INTEL_CML_GT1_ULT_2,
	PCI_DEVICE_ID_INTEL_CML_GT2_ULT_1,
	PCI_DEVICE_ID_INTEL_CML_GT2_ULT_2,
	PCI_DEVICE_ID_INTEL_CML_GT1_ULT_3,
	PCI_DEVICE_ID_INTEL_CML_GT1_ULT_4,
	PCI_DEVICE_ID_INTEL_CML_GT2_ULT_3,
	PCI_DEVICE_ID_INTEL_CML_GT2_ULT_4,
	PCI_DEVICE_ID_INTEL_CML_GT1_ULX_1,
	PCI_DEVICE_ID_INTEL_CML_GT2_ULX_1,
	PCI_DEVICE_ID_INTEL_CML_GT1_S_1,
	PCI_DEVICE_ID_INTEL_CML_GT1_S_2,
	PCI_DEVICE_ID_INTEL_CML_GT2_S_1,
	PCI_DEVICE_ID_INTEL_CML_GT2_S_2,
	PCI_DEVICE_ID_INTEL_CML_GT1_H_1,
	PCI_DEVICE_ID_INTEL_CML_GT1_H_2,
	PCI_DEVICE_ID_INTEL_CML_GT2_H_1,
	PCI_DEVICE_ID_INTEL_CML_GT2_H_2,
	0,
};

static const struct pci_driver graphics_driver __pci_driver = {
	.ops		= &graphics_ops,
	.vendor		= PCI_VENDOR_ID_INTEL,
	.devices	= pci_device_ids,
};
