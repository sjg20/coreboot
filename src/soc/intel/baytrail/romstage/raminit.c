/* SPDX-License-Identifier: GPL-2.0-only */

#include <stddef.h>
#include <acpi/acpi.h>
#include <assert.h>
#include <cbfs.h>
#include <cbmem.h>
#include <cf9_reset.h>
#include <console/console.h>
#include <device/dram/ddr3.h>
#include <device/pci_def.h>
#include <device/pci_ops.h>
#include <device/smbus_host.h>
#include <mrc_cache.h>
#include <soc/gpio.h>
#include <soc/iomap.h>
#include <soc/iosf.h>
#include <soc/pci_devs.h>
#include <soc/romstage.h>
#include <ec/google/chromeec/ec.h>
#include <ec/google/chromeec/ec_commands.h>
#include <security/vboot/vboot_common.h>

uintptr_t smbus_base(void)
{
	return SMBUS_BASE_ADDRESS;
}

int smbus_enable_iobar(uintptr_t base)
{
	uint32_t reg;
	const uint32_t smbus_dev = PCI_DEV(0, SMBUS_DEV, SMBUS_FUNC);

	/* SMBus I/O BAR */
	reg = base | 2;
	pci_write_config32(smbus_dev, PCI_BASE_ADDRESS_4, reg);
	/* Enable decode of I/O space. */
	reg = pci_read_config16(smbus_dev, PCI_COMMAND);
	reg |= 0x1;
	pci_write_config16(smbus_dev, PCI_COMMAND, reg);
	/* Enable Host Controller */
	reg = pci_read_config8(smbus_dev, 0x40);
	reg |= 1;
	pci_write_config8(smbus_dev, 0x40, reg);

	/* Configure pads to be used for SMBus */
	score_select_func(PCU_SMB_CLK_PAD, 1);
	score_select_func(PCU_SMB_DATA_PAD, 1);

	return 0;
}

static void ABI_X86 send_to_console(unsigned char b)
{
	do_putchar(b);
}

static void populate_smbios_tables(void *dram_data, int speed, int num_channels)
{
	dimm_attr dimm;
	enum spd_status status;

	/* Decode into dimm_attr struct */
	status = spd_decode_ddr3(&dimm, *(spd_raw_data *)dram_data);

	/* Some SPDs have bad CRCs, nothing we can do about it */
	if (status == SPD_STATUS_OK || status == SPD_STATUS_CRC_ERROR) {
		/* Add table 17 entry for each channel */
		for (int i = 0; i < num_channels; i++)
			spd_add_smbios17(i, 0, speed, &dimm);
	}
}

static void print_dram_info(void *dram_data)
{
	const int mrc_ver_reg = 0xf0;
	const uint32_t soc_dev = PCI_DEV(0, SOC_DEV, SOC_FUNC);
	uint32_t reg;
	int num_channels;
	int speed;
	uint32_t ch0;
	uint32_t ch1;

	reg = pci_read_config32(soc_dev, mrc_ver_reg);

	printk(BIOS_INFO, "MRC v%d.%02d\n", (reg >> 8) & 0xff, reg & 0xff);

	/* Number of channels enabled and DDR3 type. Determine number of
	 * channels by keying of the rank enable bits [3:0]. * */
	ch0 = iosf_dunit_ch0_read(DRP);
	ch1 = iosf_dunit_ch1_read(DRP);
	num_channels = 0;
	if (ch0 & DRP_RANK_MASK)
		num_channels++;
	if (ch1 & DRP_RANK_MASK)
		num_channels++;

	printk(BIOS_INFO, "%d channels of %sDDR3 @ ", num_channels,
	       (reg & (1 << 22)) ? "LP" : "");

	/* DRAM frequency -- all channels run at same frequency. */
	reg = iosf_dunit_read(DTR0);
	switch (reg & 0x3) {
	case 0:
		speed = 800; break;
	case 1:
		speed = 1066; break;
	case 2:
		speed = 1333; break;
	case 3:
		speed = 1600; break;
	}
	printk(BIOS_INFO, "%dMHz\n", speed);

	populate_smbios_tables(dram_data, speed, num_channels);
}

void raminit(struct mrc_params *mp, int prev_sleep_state)
{
	int ret;
	mrc_wrapper_entry_t mrc_entry;
	struct region_device rdev;

	/* Fill in default entries. */
	mp->version = MRC_PARAMS_VER;
	mp->console_out = &send_to_console;
	mp->prev_sleep_state = prev_sleep_state;
	mp->rmt_enabled = CONFIG(MRC_RMT);

	/* Default to 2GiB IO hole. */
	if (!mp->io_hole_mb)
		mp->io_hole_mb = 2048;

	if (!mrc_cache_get_current(MRC_TRAINING_DATA, 0, &rdev)) {
		mp->saved_data_size = region_device_sz(&rdev);
		mp->saved_data = rdev_mmap_full(&rdev);
		/* Assume boot device is memory mapped. */
		assert(CONFIG(BOOT_DEVICE_MEMORY_MAPPED));
	} else if (prev_sleep_state == ACPI_S3) {
		/* If waking from S3 and no cache then. */
		printk(BIOS_DEBUG, "No MRC cache found in S3 resume path.\n");
		post_code(POST_RESUME_FAILURE);
		system_reset();
	} else {
		printk(BIOS_DEBUG, "No MRC cache found.\n");
	}

	/* Determine if mrc.bin is in the cbfs. */
	if (cbfs_boot_map_with_leak("mrc.bin", CBFS_TYPE_MRC, NULL) == NULL) {
		printk(BIOS_DEBUG, "Couldn't find mrc.bin\n");
		return;
	}

	/*
	 * The entry point is currently the first instruction. Handle the
	 * case of an ELF file being put in the cbfs by setting the entry
	 * to the CONFIG_MRC_BIN_ADDRESS.
	 */
	mrc_entry = (void *)(uintptr_t)CONFIG_MRC_BIN_ADDRESS;

	if (mp->mainboard.dram_info_location == DRAM_INFO_SPD_SMBUS)
		enable_smbus();

	ret = mrc_entry(mp);

	if (prev_sleep_state != ACPI_S3) {
		cbmem_initialize_empty();
	} else if (cbmem_initialize()) {
		printk(BIOS_DEBUG, "Failed to recover CBMEM in S3 resume.\n");
		/* Failed S3 resume, reset to come up cleanly */
		system_reset();
	}

	print_dram_info(mp->mainboard.dram_data[0]);

	printk(BIOS_DEBUG, "MRC Wrapper returned %d\n", ret);
	printk(BIOS_DEBUG, "MRC data at %p %d bytes\n", mp->data_to_save,
	       mp->data_to_save_size);

	if (mp->data_to_save != NULL && mp->data_to_save_size > 0)
		mrc_cache_stash_data(MRC_TRAINING_DATA, 0, mp->data_to_save,
					mp->data_to_save_size);
}
