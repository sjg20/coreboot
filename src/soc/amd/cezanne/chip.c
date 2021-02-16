/* SPDX-License-Identifier: GPL-2.0-only */

#include <device/device.h>
#include <fsp/api.h>
#include <soc/data_fabric.h>
#include <soc/southbridge.h>
#include <types.h>
#include "chip.h"

/* Supplied by uart.c */
extern struct device_operations cezanne_uart_mmio_ops;

struct device_operations cpu_bus_ops = {
	.read_resources	= noop_read_resources,
	.set_resources	= noop_set_resources,
	.init		= mp_cpu_bus_init,
};

static struct device_operations pci_domain_ops = {
	.read_resources	= pci_domain_read_resources,
	.set_resources	= pci_domain_set_resources,
	.scan_bus	= pci_domain_scan_bus,
};

static void set_mmio_dev_ops(struct device *dev)
{
	switch (dev->path.mmio.addr) {
	case APU_UART0_BASE:
	case APU_UART1_BASE:
		dev->ops = &cezanne_uart_mmio_ops;
		break;
	}
}

static void enable_dev(struct device *dev)
{
	/* Set the operations if it is a special bus type */
	switch (dev->path.type) {
	case DEVICE_PATH_DOMAIN:
		dev->ops = &pci_domain_ops;
		break;
	case DEVICE_PATH_CPU_CLUSTER:
		dev->ops = &cpu_bus_ops;
		break;
	case DEVICE_PATH_MMIO:
		set_mmio_dev_ops(dev);
		break;
	default:
		break;
	}
}

static void soc_init(void *chip_info)
{
	fsp_silicon_init();

	data_fabric_set_mmio_np();

	fch_init(chip_info);
}

static void soc_final(void *chip_info)
{
	fch_final(chip_info);
}

struct chip_operations soc_amd_cezanne_ops = {
	CHIP_NAME("AMD Cezanne SoC")
	.enable_dev = enable_dev,
	.init = soc_init,
	.final = soc_final
};
