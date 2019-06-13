/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2013 Google, Inc.
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

#define NEED_VB20_INTERNALS  /* Peeking into vb2_shared_data */

#include <stddef.h>
#include <stdint.h>
#include <vb2_api.h>

#include <arch/stages.h>
#include <assert.h>
#include <bootmode.h>
#include <string.h>
#include <cbmem.h>
#include <console/console.h>
#include <console/vtxprintf.h>
#include <fmap.h>
#include <stdlib.h>
#include <vboot_struct.h>
#include <security/vboot/vbnv.h>
#include <security/vboot/misc.h>

/**
 * Sets vboot_handoff based on the information in vb2_shared_data
 */
static void fill_vboot_handoff(struct vboot_handoff *vboot_handoff,
			       struct vb2_shared_data *vb2_sd)
{
	VbSharedDataHeader *vb_sd =
		(VbSharedDataHeader *)vboot_handoff->shared_data;
	uint32_t *oflags = &vboot_handoff->out_flags;

	vb_sd->flags |= VBSD_BOOT_FIRMWARE_VBOOT2;

	vboot_handoff->selected_firmware = vb2_sd->fw_slot;

	vb_sd->firmware_index = vb2_sd->fw_slot;

	vb_sd->magic = VB_SHARED_DATA_MAGIC;
	vb_sd->struct_version = VB_SHARED_DATA_VERSION;
	vb_sd->struct_size = sizeof(VbSharedDataHeader);
	vb_sd->data_size = VB_SHARED_DATA_MIN_SIZE;
	vb_sd->data_used = sizeof(VbSharedDataHeader);
	vb_sd->fw_version_tpm = vb2_sd->fw_version_secdata;

	if (vb2_sd->recovery_reason) {
		vb_sd->firmware_index = 0xFF;
		if (vb2_sd->flags & VB2_SD_FLAG_MANUAL_RECOVERY)
			vb_sd->flags |= VBSD_BOOT_REC_SWITCH_ON;
		*oflags |= VB_INIT_OUT_ENABLE_RECOVERY;
		*oflags |= VB_INIT_OUT_CLEAR_RAM;
	}
	if (vb2_sd->flags & VB2_SD_FLAG_DEV_MODE_ENABLED) {
		*oflags |= VB_INIT_OUT_ENABLE_DEVELOPER;
		*oflags |= VB_INIT_OUT_CLEAR_RAM;
		vb_sd->flags |= VBSD_BOOT_DEV_SWITCH_ON;
		vb_sd->flags |= VBSD_LF_DEV_SWITCH_ON;
	}

	/* In vboot1, VBSD_FWB_TRIED is
	 * set only if B is booted as explicitly requested. Therefore, if B is
	 * booted because A was found bad, the flag should not be set. It's
	 * better not to touch it if we can only ambiguously control it. */
	/* if (vb2_sd->fw_slot)
		vb_sd->flags |= VBSD_FWB_TRIED; */

	/* copy kernel subkey if it's found */
	if (vb2_sd->workbuf_preamble_size) {
		struct vb2_fw_preamble *fp;
		uintptr_t dst, src;
		printk(BIOS_INFO, "Copying FW preamble\n");
		fp = (struct vb2_fw_preamble *)((uintptr_t)vb2_sd +
				vb2_sd->workbuf_preamble_offset);
		src = (uintptr_t)&fp->kernel_subkey +
				fp->kernel_subkey.key_offset;
		dst = (uintptr_t)vb_sd + sizeof(VbSharedDataHeader);
		assert(dst + fp->kernel_subkey.key_size <=
		       (uintptr_t)vboot_handoff + sizeof(*vboot_handoff));
		memcpy((void *)dst, (void *)src,
		       fp->kernel_subkey.key_size);
		vb_sd->data_used += fp->kernel_subkey.key_size;
		vb_sd->kernel_subkey.key_offset =
				dst - (uintptr_t)&vb_sd->kernel_subkey;
		vb_sd->kernel_subkey.key_size = fp->kernel_subkey.key_size;
		vb_sd->kernel_subkey.algorithm = fp->kernel_subkey.algorithm;
		vb_sd->kernel_subkey.key_version =
				fp->kernel_subkey.key_version;
	}

	vb_sd->recovery_reason = vb2_sd->recovery_reason;
}

void vboot_fill_handoff(void)
{
	struct vboot_handoff *vh;
	struct vb2_shared_data *sd;

	sd = vboot_get_shared_data();
	sd->workbuf_hash_offset = 0;
	sd->workbuf_hash_size = 0;

	printk(BIOS_INFO, "creating vboot_handoff structure\n");
	vh = cbmem_add(CBMEM_ID_VBOOT_HANDOFF, sizeof(*vh));
	if (vh == NULL)
		/* we don't need to failover gracefully here because this
		 * shouldn't happen with the image that has passed QA. */
		die("failed to allocate vboot_handoff structure\n");

	memset(vh, 0, sizeof(*vh));

	/* needed until we finish transtion to vboot2 for kernel verification */
	fill_vboot_handoff(vh, sd);


	/* Log the recovery mode switches if required, before clearing them. */
	log_recovery_mode_switch();

	/*
	 * The recovery mode switch is cleared (typically backed by EC) here
	 * to allow multiple queries to get_recovery_mode_switch() and have
	 * them return consistent results during the verified boot path as well
	 * as dram initialization. x86 systems ignore the saved dram settings
	 * in the recovery path in order to start from a clean slate. Therefore
	 * clear the state here since this function is called when memory
	 * is known to be up.
	 */
	clear_recovery_mode_switch();
}

/*
 * For platforms that employ VBOOT_STARTS_IN_ROMSTAGE, the vboot
 * verification doesn't happen until after cbmem is brought online.
 * Therefore, the vboot results would not be initialized so don't
 * automatically add results when cbmem comes online.
 */
#if !CONFIG(VBOOT_STARTS_IN_ROMSTAGE)
static void vb2_fill_handoff_cbmem(int unused)
{
	vboot_fill_handoff();
}
ROMSTAGE_CBMEM_INIT_HOOK(vb2_fill_handoff_cbmem)
#endif
