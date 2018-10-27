/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2015-2018 Intel Corp.
 * (Written by Alexandru Gagniuc <alexandrux.gagniuc@intel.com> for Intel Corp.)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include <arch/early_variables.h>
#include <arch/io.h>
#include <cbmem.h>
#include <commonlib/helpers.h>
#include <console/console.h>
#include <fsp/api.h>
#include <fsp/util.h>
#include <inttypes.h>
#include <string.h>

#define HOB_HEADER_LEN		8

/* GUIDs in little-endian, so they can be used with memcmp() */
const uint8_t fsp_bootloader_tolum_guid[16] = {
	0x56, 0x4f, 0xff, 0x73, 0x8e, 0xaa, 0x51, 0x44,
	0xb3, 0x16, 0x36, 0x35, 0x36, 0x67, 0xad, 0x44,
};

const uint8_t fsp_reserved_memory_guid[16] = {
	0x59, 0x97, 0xa7, 0x69, 0x73, 0x13, 0x67, 0x43,
	0xa6, 0xc4, 0xc7, 0xf5, 0x9e, 0xfd, 0x98, 0x6e,
};

const uint8_t fsp_nv_storage_guid[16] = {
	0x02, 0xcf, 0x1a, 0x72, 0x77, 0x4d, 0x2a, 0x4c,
	0xb3, 0xdc, 0x27, 0x0b, 0x7b, 0xa9, 0xe4, 0xb0
};

static const uint8_t uuid_fv_info[16] = {
	0x2e, 0x72, 0x8e, 0x79, 0xb2, 0x15, 0x13, 0x4e,
	0x8a, 0xe9, 0x6b, 0xa3, 0x0f, 0xf7, 0xf1, 0x67
};

/*
 * Utilities for walking HOBs
 */

bool fsp_guid_compare(const uint8_t guid1[16], const uint8_t guid2[16])
{
	return !memcmp(guid1, guid2, 16);
}

const struct hob_header *fsp_next_hob(const struct hob_header *parent)
{
	union {
		const struct hob_header *hob;
		uintptr_t addr;
	} hob_walker;

	hob_walker.hob = parent;
	hob_walker.addr += parent->length;
	return hob_walker.hob;
}

static const void *hob_header_to_struct(const struct hob_header *hob)
{
	union {
		const struct hob_header *hob_hdr;
		const void *hob_descr;
		uintptr_t addr;
	} hob_walker;

	hob_walker.hob_hdr = hob;
	hob_walker.addr += HOB_HEADER_LEN;
	return hob_walker.hob_descr;
}

static const void *hob_header_to_extension_hob(const struct hob_header *hob)
{
	union {
		const struct hob_header *hob_hdr;
		const void *hob_descr;
		uintptr_t addr;
	} hob_walker;

	hob_walker.hob_hdr = hob;
	hob_walker.addr += HOB_HEADER_LEN + 16; /* header and 16-byte GUID */
	return hob_walker.hob_descr;
}

const
struct hob_resource *fsp_hob_header_to_resource(const struct hob_header *hob)
{
	return hob_header_to_struct(hob);
}

/*
 * Utilities for locating and identifying HOBs
 */

static void *fsp_hob_list_ptr CAR_GLOBAL;

static void save_hob_list(int is_recovery)
{
	uint32_t *cbmem_loc;
	const void *hob_list;
	cbmem_loc = cbmem_add(CBMEM_ID_FSP_RUNTIME, sizeof(*cbmem_loc));
	if (cbmem_loc == NULL)
		die("Error: Could not add cbmem area for hob list.\n");
	hob_list = fsp_get_hob_list();
	if (!hob_list)
		die("Error: Could not locate hob list pointer.\n");
	*cbmem_loc = (uintptr_t)hob_list;
}

ROMSTAGE_CBMEM_INIT_HOOK(save_hob_list);

const void *fsp_get_hob_list(void)
{
	uint32_t *list_loc;

	if (ENV_ROMSTAGE)
		return (void *)car_get_var(fsp_hob_list_ptr);
	list_loc = cbmem_find(CBMEM_ID_FSP_RUNTIME);
	return (list_loc) ? (void *)(uintptr_t)(*list_loc) : NULL;
}

void *fsp_get_hob_list_ptr(void)
{
	return car_get_var_ptr(&fsp_hob_list_ptr);
}

static const
struct hob_resource *find_resource_hob_by_guid(const struct hob_header *hob,
					       const uint8_t guid[16])
{
	const struct hob_resource *res;

	for (; hob->type != HOB_TYPE_END_OF_HOB_LIST;
		hob = fsp_next_hob(hob)) {

		if (hob->type != HOB_TYPE_RESOURCE_DESCRIPTOR)
			continue;

		res = fsp_hob_header_to_resource(hob);
		if (fsp_guid_compare(res->owner_guid, guid))
			return res;
	}
	return NULL;
}

void fsp_print_guid(const void *base)
{
	uint32_t big;
	uint16_t mid[2];

	const uint8_t *id = base;
	big = read32(id + 0);
	mid[0] = read16(id + 4);
	mid[1] = read16(id + 6);

	printk(BIOS_SPEW, "%08x-%04x-%04x-%02x%02x%02x%02x%02x%02x%02x%02x",
	       big, mid[0], mid[1],
	       id[8], id[9], id[10], id[11], id[12], id[13], id[14], id[15]);
}

int fsp_find_range_hob(struct range_entry *re, const uint8_t guid[16])
{
	const struct hob_resource *fsp_mem;
	const void *hob_list = fsp_get_hob_list();

	if (!hob_list)
		return -1;

	range_entry_init(re, 0, 0, 0);

	fsp_mem = find_resource_hob_by_guid(hob_list, guid);

	if (!fsp_mem) {
		fsp_print_guid(guid);
		printk(BIOS_SPEW, " not found!\n");
		return -1;
	}

	range_entry_init(re, fsp_mem->addr, fsp_mem->addr + fsp_mem->length, 0);
	return 0;
}

int fsp_find_reserved_memory(struct range_entry *re)
{
	return fsp_find_range_hob(re, fsp_reserved_memory_guid);
}

const void *fsp_find_extension_hob_by_guid(const uint8_t *guid, size_t *size)
{
	const uint8_t *hob_guid;
	const struct hob_header *hob = fsp_get_hob_list();

	if (!hob)
		return NULL;

	for (; hob->type != HOB_TYPE_END_OF_HOB_LIST;
		hob = fsp_next_hob(hob)) {

		if (hob->type != HOB_TYPE_GUID_EXTENSION)
			continue;

		hob_guid = hob_header_to_struct(hob);
		if (fsp_guid_compare(hob_guid, guid)) {
			*size = hob->length - (HOB_HEADER_LEN + 16);
			return hob_header_to_extension_hob(hob);
		}
	}

	return NULL;
}

static void display_fsp_version_info_hob(const void *hob, size_t size)
{
#if IS_ENABLED(CONFIG_DISPLAY_FSP_VERSION_INFO)
	const FIRMWARE_VERSION_INFO *fvi;
	const FIRMWARE_VERSION_INFO_HOB *fvih =
			(FIRMWARE_VERSION_INFO_HOB *)hob;
	int index, cnt;
	char *str_ptr;

	fvi = (void *)&fvih[1];
	str_ptr = (char *)((uintptr_t)fvi +
			 (fvih->Count * sizeof (FIRMWARE_VERSION_INFO)));
	size -= sizeof(SMBIOS_STRUCTURE);

	printk(BIOS_DEBUG, "Display FSP Version Info HOB\n");
	for (index = 0; index < fvih->Count; index++) {
		cnt = strlen(str_ptr);

		/*  Don't show ingredient name and version if its all 0xFF */
		if (fvi[index].Version.MajorVersion == 0xFF &&
			fvi[index].Version.MajorVersion == 0xFF &&
			fvi[index].Version.MajorVersion == 0xFF &&
			fvi[index].Version.MajorVersion == 0xFF &&
			fvi[index].VersionStringIndex == 0) {
			str_ptr = (char *)((uintptr_t)str_ptr + cnt +
					sizeof(uint8_t));
			continue;
		}
		/*
		 * Firmware Version String consist of 2 pieces of information
		 * 1. Component Name: string type data holds FW type name.
		 * 2. Version Information : Either a string type data or
		 * numeric field holds FW version information.
		 */
		printk(BIOS_DEBUG, "%s = ", str_ptr);

		if (!fvi[index].VersionStringIndex)
			printk(BIOS_DEBUG, "%x.%x.%x.%x\n",
					fvi[index].Version.MajorVersion,
					fvi[index].Version.MinorVersion,
					fvi[index].Version.Revision,
					fvi[index].Version.BuildNumber);
		else {
			str_ptr = (char *)((uintptr_t)str_ptr + cnt +
					sizeof(uint8_t));
			cnt = strlen(str_ptr);
			printk(BIOS_DEBUG, "%s\n", str_ptr);
		}
		str_ptr = (char *)((uintptr_t)str_ptr + cnt +
				sizeof(uint8_t));
	}
#endif
}

void fsp_display_fvi_version_hob(void)
{
	const uint8_t *hob_uuid;
	const struct hob_header *hob = fsp_get_hob_list();
	size_t size;

	if (!hob)
		return;

	for (; hob->type != HOB_TYPE_END_OF_HOB_LIST;
			hob = fsp_next_hob(hob)) {
		if (hob->type != HOB_TYPE_GUID_EXTENSION)
			continue;

		hob_uuid = hob_header_to_struct(hob);

		if (fsp_guid_compare(hob_uuid, uuid_fv_info)) {
			size = hob->length - (HOB_HEADER_LEN + 16);
			display_fsp_version_info_hob(hob, size);
		}
	}
}

const void *fsp_find_nv_storage_data(size_t *size)
{
	return fsp_find_extension_hob_by_guid(fsp_nv_storage_guid, size);
}
