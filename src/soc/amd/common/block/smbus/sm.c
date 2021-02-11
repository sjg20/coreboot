/* SPDX-License-Identifier: GPL-2.0-only */

#include <amdblocks/acpimmio.h>
#include <device/device.h>
#include <device/pci.h>
#include <device/pci_ids.h>
#include <device/smbus.h>
#include <device/smbus_host.h>
#include <arch/ioapic.h>
#include <soc/southbridge.h>

static void sm_init(struct device *dev)
{
	fch_enable_ioapic_decode();
	setup_ioapic(VIO_APIC_VADDR, CONFIG_MAX_CPUS);
}

static u32 get_sm_mmio(struct device *dev)
{
	/*
	 * Since SMBus and ASF controller are behind the same PCIe device, we don't know behind
	 * which controller a device is. We assume here that the devices are behind the SMBus
	 * controller. The proper solution would be to handle those as MMIO devices instead of
	 * PCI ones.
	 */
	return (uintptr_t)acpimmio_smbus;
}

static int lsmbus_recv_byte(struct device *dev)
{
	u8 device;

	device = dev->path.i2c.device;
	return do_smbus_recv_byte(get_sm_mmio(dev), device);
}

static int lsmbus_send_byte(struct device *dev, u8 val)
{
	u8 device;

	device = dev->path.i2c.device;
	return do_smbus_send_byte(get_sm_mmio(dev), device, val);
}

static int lsmbus_read_byte(struct device *dev, u8 address)
{
	u8 device;

	device = dev->path.i2c.device;
	return do_smbus_read_byte(get_sm_mmio(dev), device, address);
}

static int lsmbus_write_byte(struct device *dev, u8 address, u8 val)
{
	u8 device;

	device = dev->path.i2c.device;
	return do_smbus_write_byte(get_sm_mmio(dev), device, address, val);
}
static struct smbus_bus_operations lops_smbus_bus = {
	.recv_byte = lsmbus_recv_byte,
	.send_byte = lsmbus_send_byte,
	.read_byte = lsmbus_read_byte,
	.write_byte = lsmbus_write_byte,
};

static struct device_operations smbus_ops = {
	.read_resources = noop_read_resources,
	.set_resources = noop_set_resources,
	.enable_resources = pci_dev_enable_resources,
	.init = sm_init,
	.scan_bus = scan_smbus,
	.ops_pci = &pci_dev_ops_pci,
	.ops_smbus_bus = &lops_smbus_bus,
};
static const struct pci_driver smbus_driver __pci_driver = {
	.ops = &smbus_ops,
	.vendor = PCI_VENDOR_ID_AMD,
	.device = PCI_DEVICE_ID_AMD_CZ_SMBUS,
};
