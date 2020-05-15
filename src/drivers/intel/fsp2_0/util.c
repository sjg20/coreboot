/* SPDX-License-Identifier: GPL-2.0-or-later */

#include <device/mmio.h>
#include <cbfs.h>
#include <cf9_reset.h>
#include <commonlib/bsd/compression.h>
#include <commonlib/fsp.h>
#include <console/console.h>
#include <fsp/util.h>
#include <lib.h>
#include <string.h>
#include <types.h>

static bool looks_like_fsp_header(const uint8_t *raw_hdr)
{
	if (memcmp(raw_hdr, FSP_HDR_SIGNATURE, 4)) {
		printk(BIOS_ALERT, "Did not find a valid FSP signature\n");
		return false;
	}

	if (read32(raw_hdr + 4) != FSP_HDR_LEN) {
		printk(BIOS_ALERT, "FSP header has invalid length\n");
		return false;
	}

	return true;
}

enum cb_err fsp_identify(struct fsp_header *hdr, const void *fsp_blob)
{
	const uint8_t *raw_hdr = fsp_blob;

	if (!looks_like_fsp_header(raw_hdr))
		return CB_ERR;

	hdr->spec_version = read8(raw_hdr + 10);
	hdr->revision = read8(raw_hdr + 11);
	hdr->fsp_revision = read32(raw_hdr + 12);
	memcpy(hdr->image_id, raw_hdr + 16, ARRAY_SIZE(hdr->image_id));
	hdr->image_id[ARRAY_SIZE(hdr->image_id) - 1] = '\0';
	hdr->image_size = read32(raw_hdr + 24);
	hdr->image_base = read32(raw_hdr + 28);
	hdr->image_attribute = read16(raw_hdr + 32);
	hdr->component_attribute = read16(raw_hdr + 34);
	hdr->cfg_region_offset = read32(raw_hdr + 36);
	hdr->cfg_region_size = read32(raw_hdr + 40);
	hdr->temp_ram_init_entry = read32(raw_hdr + 48);
	hdr->temp_ram_exit_entry = read32(raw_hdr + 64);
	hdr->notify_phase_entry_offset = read32(raw_hdr + 56);
	hdr->memory_init_entry_offset = read32(raw_hdr + 60);
	hdr->silicon_init_entry_offset = read32(raw_hdr + 68);

	return CB_SUCCESS;
}

enum cb_err fsp_validate_component(struct fsp_header *hdr,
					const struct region_device *rdev)
{
	void *membase;

	/* Map just enough of the file to be able to parse the header. */
	membase = rdev_mmap(rdev, FSP_HDR_OFFSET, FSP_HDR_LEN);

	if (membase == NULL) {
		printk(BIOS_CRIT, "Could not mmap() FSP header.\n");
		return CB_ERR;
	}

	if (fsp_identify(hdr, membase) != CB_SUCCESS) {
		rdev_munmap(rdev, membase);
		printk(BIOS_CRIT, "No valid FSP header\n");
		return CB_ERR;
	}

	rdev_munmap(rdev, membase);

	if (CONFIG(DISPLAY_FSP_HEADER))
		fsp_print_header_info(hdr);

	/* Check if size specified in the header matches the cbfs file size */
	if (region_device_sz(rdev) < hdr->image_size) {
		printk(BIOS_CRIT, "Component size bigger than cbfs file.\n");
		return CB_ERR;
	}

	return CB_SUCCESS;
}

static bool fsp_reset_requested(uint32_t status)
{
	return (status >= FSP_STATUS_RESET_REQUIRED_COLD &&
		status <= FSP_STATUS_RESET_REQUIRED_8);
}

void fsp_handle_reset(uint32_t status)
{
	if (!fsp_reset_requested(status))
		return;

	printk(BIOS_SPEW, "FSP: handling reset type %x\n", status);

	switch (status) {
	case FSP_STATUS_RESET_REQUIRED_COLD:
		full_reset();
		break;
	case FSP_STATUS_RESET_REQUIRED_WARM:
		system_reset();
		break;
	case FSP_STATUS_RESET_REQUIRED_3:
	case FSP_STATUS_RESET_REQUIRED_4:
	case FSP_STATUS_RESET_REQUIRED_5:
	case FSP_STATUS_RESET_REQUIRED_6:
	case FSP_STATUS_RESET_REQUIRED_7:
	case FSP_STATUS_RESET_REQUIRED_8:
		chipset_handle_reset(status);
		break;
	default:
		break;
	}
}

static void *fsp_get_dest_and_load(struct fsp_load_descriptor *fspld, size_t size,
				const struct region_device *source_rdev,
				uint32_t compression_algo)
{
	void *dest;

	if (fspld->get_destination(fspld, &dest, size, source_rdev) < 0) {
		printk(BIOS_ERR, "FSP Destination not obtained.\n");
		return NULL;
	}

	if (cbfs_load_and_decompress(source_rdev, 0, region_device_sz(source_rdev),
			dest, size, compression_algo) != size) {
		printk(BIOS_ERR, "Failed to load FSP component.\n");
		return NULL;
	}

	if (fsp_component_relocate((uintptr_t)dest, dest, size) < 0) {
		printk(BIOS_ERR, "Unable to relocate FSP component!\n");
		return NULL;
	}

	return dest;
}

/* Load the FSP component described by fsp_load_descriptor from cbfs. The FSP
 * header object will be validated and filled in on successful load. */
enum cb_err fsp_load_component(struct fsp_load_descriptor *fspld, struct fsp_header *hdr)
{
	struct cbfsf file_desc;
	uint32_t compression_algo;
	size_t output_size;
	void *dest;
	struct region_device source_rdev;
	struct prog *fsp_prog = &fspld->fsp_prog;

	if (fspld->get_destination == NULL)
		return CB_ERR;

	if (cbfs_boot_locate(&file_desc, prog_name(fsp_prog), &fsp_prog->cbfs_type) < 0)
		return CB_ERR;

	if (cbfsf_decompression_info(&file_desc, &compression_algo, &output_size) < 0)
		return CB_ERR;

	cbfs_file_data(&source_rdev, &file_desc);

	dest = fsp_get_dest_and_load(fspld, output_size, &source_rdev, compression_algo);

	if (dest == NULL)
		return CB_ERR;

	prog_set_area(fsp_prog, dest, output_size);

	if (fsp_validate_component(hdr, prog_rdev(fsp_prog)) != CB_SUCCESS) {
		printk(BIOS_ERR, "Invalid FSP header after load!\n");
		return CB_ERR;
	}

	/* Signal that FSP component has been loaded. */
	prog_segment_loaded(hdr->image_base, hdr->image_size, SEG_FINAL);

	return CB_SUCCESS;
}
