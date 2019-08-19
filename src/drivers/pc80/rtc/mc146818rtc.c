/*
 * This file is part of the coreboot project.
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

#include <arch/acpi.h>
#include <arch/io.h>
#include <bcd.h>
#include <fallback.h>
#include <version.h>
#include <console/console.h>
#include <pc80/mc146818rtc.h>
#include <rtc.h>
#include <string.h>
#include <cbfs.h>
#include <security/vboot/vbnv.h>
#include <security/vboot/vbnv_layout.h>
#include <types.h>

/* There's no way around this include guard. option_table.h is autogenerated */
#if CONFIG(USE_OPTION_TABLE)
#include "option_table.h"
#else
#define LB_CKS_RANGE_START	0
#define LB_CKS_RANGE_END	0
#define LB_CKS_LOC		0
#endif

/* Don't warn for checking >= LB_CKS_RANGE_START even though it may be 0. */
#pragma GCC diagnostic ignored "-Wtype-limits"

static void cmos_reset_date(void)
{
	/* Now setup a default date equals to the build date */
	struct rtc_time time = {
		.sec = 0,
		.min = 0,
		.hour = 1,
		.mday = bcd2bin(coreboot_build_date.day),
		.mon = bcd2bin(coreboot_build_date.month),
		.year = (bcd2bin(coreboot_build_date.century) * 100) +
			bcd2bin(coreboot_build_date.year),
		.wday = bcd2bin(coreboot_build_date.weekday)
	};
	rtc_set(&time);
}

static int cmos_checksum_valid(int range_start, int range_end, int cks_loc)
{
	int i;
	u16 sum, old_sum;

	if (CONFIG(STATIC_OPTION_TABLE))
		return 1;

	sum = 0;
	for (i = range_start; i <= range_end; i++)
		sum += cmos_read(i);
	old_sum = ((cmos_read(cks_loc) << 8) | cmos_read(cks_loc + 1)) &
		  0x0ffff;
	return sum == old_sum;
}

static void cmos_set_checksum(int range_start, int range_end, int cks_loc)
{
	int i;
	u16 sum;

	sum = 0;
	for (i = range_start; i <= range_end; i++)
		sum += cmos_read(i);
	cmos_write(((sum >> 8) & 0x0ff), cks_loc);
	cmos_write(((sum >> 0) & 0x0ff), cks_loc + 1);
}

#define RTC_CONTROL_DEFAULT (RTC_24H)
#define RTC_FREQ_SELECT_DEFAULT (RTC_REF_CLCK_32KHZ | RTC_RATE_1024HZ)

static bool __cmos_init(bool invalid)
{
	bool cmos_invalid;
	bool checksum_invalid = false;
	bool clear_cmos;
	size_t i;
	uint8_t x;

	/*
	 * Avoid clearing pending interrupts and resetting the RTC control
	 * register in the resume path because the Linux kernel relies on
	 * this to know if it should restart the RTC timer queue if the wake
	 * was due to the RTC alarm.
	 */
	if (ENV_RAMSTAGE && acpi_is_wakeup_s3())
		return false;

	printk(BIOS_DEBUG, "RTC Init\n");

	/* See if there has been a CMOS power problem. */
	x = cmos_read(RTC_VALID);
	cmos_invalid = !(x & RTC_VRT);

	if (CONFIG(USE_OPTION_TABLE)) {
		/* See if there is a CMOS checksum error */
		checksum_invalid = !cmos_checksum_valid(PC_CKS_RANGE_START,
						PC_CKS_RANGE_END, PC_CKS_LOC);

		clear_cmos = false;
	} else {
		clear_cmos = true;
	}

	if (cmos_invalid || invalid)
		cmos_write(cmos_read(RTC_CONTROL) | RTC_SET, RTC_CONTROL);

	if (invalid || cmos_invalid || checksum_invalid) {
		if (clear_cmos) {
			cmos_write(0, 0x01);
			cmos_write(0, 0x03);
			cmos_write(0, 0x05);
			for (i = 10; i < 128; i++)
				cmos_write(0, i);
		}

		if (cmos_invalid || invalid)
			cmos_reset_date();

		printk(BIOS_WARNING, "RTC:%s%s%s%s\n",
			invalid ? " Clear requested":"",
			cmos_invalid ? " Power Problem":"",
			checksum_invalid ? " Checksum invalid":"",
			clear_cmos ? " zeroing cmos":"");
	} else
		clear_cmos = false;

	/* Setup the real time clock */
	cmos_write(RTC_CONTROL_DEFAULT, RTC_CONTROL);
	/* Setup the frequency it operates at */
	cmos_write(RTC_FREQ_SELECT_DEFAULT, RTC_FREQ_SELECT);
	/* Ensure all reserved bits are 0 in register D */
	cmos_write(RTC_VRT, RTC_VALID);

	if (CONFIG(USE_OPTION_TABLE)) {
		/* See if there is a LB CMOS checksum error */
		checksum_invalid = !cmos_checksum_valid(LB_CKS_RANGE_START,
				LB_CKS_RANGE_END, LB_CKS_LOC);
		if (checksum_invalid)
			printk(BIOS_DEBUG, "RTC: coreboot checksum invalid\n");

		/* Make certain we have a valid checksum */
		cmos_set_checksum(PC_CKS_RANGE_START, PC_CKS_RANGE_END, PC_CKS_LOC);
	}

	/* Clear any pending interrupts */
	cmos_read(RTC_INTR_FLAGS);

	return clear_cmos;
}

static void cmos_init_vbnv(bool invalid)
{
	uint8_t vbnv[VBOOT_VBNV_BLOCK_SIZE];

	/* __cmos_init() will clear vbnv contents when a known rtc failure
	   occurred with !CONFIG_USE_OPTION_TABLE. However, __cmos_init() may
	   clear vbnv data for other internal reasons. For that, always back up
	   the vbnv contents and conditionally save them when __cmos_init()
	   indicates cmos was cleared. */
	read_vbnv_cmos(vbnv);

	if (__cmos_init(invalid))
		save_vbnv_cmos(vbnv);
}

void cmos_init(bool invalid)
{
	if (ENV_SMM)
		return;

	if (CONFIG(VBOOT_VBNV_CMOS))
		cmos_init_vbnv(invalid);
	else
		__cmos_init(invalid);
}

/*
 * This routine returns the value of the requested bits.
 * input bit = bit count from the beginning of the cmos image
 * length = number of bits to include in the value
 * ret = a character pointer to where the value is to be returned
 * returns CB_SUCCESS = successful, cb_err code if an error occurred
 */
static enum cb_err get_cmos_value(unsigned long bit, unsigned long length,
				  void *vret)
{
	unsigned char *ret;
	unsigned long byte, byte_bit;
	unsigned long i;
	unsigned char uchar;

	/*
	 * The table is checked when it is built to ensure all
	 * values are valid.
	 */
	ret = vret;
	byte = bit / 8;	/* find the byte where the data starts */
	byte_bit = bit % 8; /* find the bit in the byte where the data starts */
	if (length < 9) {	/* one byte or less */
		uchar = cmos_read(byte); /* load the byte */
		uchar >>= byte_bit;	/* shift the bits to byte align */
		/* clear unspecified bits */
		ret[0] = uchar & ((1 << length) - 1);
	} else {	/* more than one byte so transfer the whole bytes */
		for (i = 0; length; i++, length -= 8, byte++) {
			/* load the byte */
			ret[i] = cmos_read(byte);
		}
	}
	return CB_SUCCESS;
}

static enum cb_err locate_cmos_layout(struct region_device *rdev)
{
	uint32_t cbfs_type = CBFS_COMPONENT_CMOS_LAYOUT;
	MAYBE_STATIC_BSS struct cbfsf fh = {};

	/*
	 * In case VBOOT is enabled and this function is called from SMM,
	 * we have multiple CMOS layout files and to locate them we'd need to
	 * include VBOOT into SMM...
	 *
	 * Support only one CMOS layout in the 'COREBOOT' region for now.
	 */
	if (!region_device_sz(&(fh.data))) {
		if (cbfs_locate_file_in_region(&fh, "COREBOOT", "cmos_layout.bin",
					       &cbfs_type)) {
			printk(BIOS_ERR, "RTC: cmos_layout.bin could not be found. "
						"Options are disabled\n");
			return CB_CMOS_LAYOUT_NOT_FOUND;
		}
	}

	cbfs_file_data(rdev, &fh);

	return CB_SUCCESS;
}

enum cb_err get_option(void *dest, const char *name)
{
	struct cmos_option_table *ct;
	struct region_device rdev;
	struct cmos_entries *ce;
	size_t namelen;
	int found = 0;

	if (!CONFIG(USE_OPTION_TABLE))
		return CB_CMOS_OTABLE_DISABLED;

	/* Figure out how long name is */
	namelen = strnlen(name, CMOS_MAX_NAME_LENGTH);

	if (locate_cmos_layout(&rdev) != CB_SUCCESS) {
		return CB_CMOS_LAYOUT_NOT_FOUND;
	}
	ct = rdev_mmap_full(&rdev);
	if (!ct) {
		printk(BIOS_ERR, "RTC: cmos_layout.bin could not be mapped. "
		       "Options are disabled\n");

		return CB_CMOS_LAYOUT_NOT_FOUND;
	}

	/* find the requested entry record */
	ce = (struct cmos_entries *)((unsigned char *)ct + ct->header_length);
	for (; ce->tag == LB_TAG_OPTION;
		ce = (struct cmos_entries *)((unsigned char *)ce + ce->size)) {
		if (memcmp(ce->name, name, namelen) == 0) {
			found = 1;
			break;
		}
	}
	if (!found) {
		printk(BIOS_DEBUG, "No CMOS option '%s'.\n", name);
		rdev_munmap(&rdev, ct);
		return CB_CMOS_OPTION_NOT_FOUND;
	}

	if (!cmos_checksum_valid(LB_CKS_RANGE_START, LB_CKS_RANGE_END, LB_CKS_LOC)) {
		rdev_munmap(&rdev, ct);
		return CB_CMOS_CHECKSUM_INVALID;
	}
	if (get_cmos_value(ce->bit, ce->length, dest) != CB_SUCCESS) {
		rdev_munmap(&rdev, ct);
		return CB_CMOS_ACCESS_ERROR;
	}
	rdev_munmap(&rdev, ct);
	return CB_SUCCESS;
}

static enum cb_err set_cmos_value(unsigned long bit, unsigned long length,
				  void *vret)
{
	unsigned char *ret;
	unsigned long byte, byte_bit;
	unsigned long i;
	unsigned char uchar, mask;
	unsigned int chksum_update_needed = 0;

	ret = vret;
	byte = bit / 8;		/* find the byte where the data starts */
	byte_bit = bit % 8;	/* find the bit where the data starts */
	if (length <= 8) {	/* one byte or less */
		mask = (1 << length) - 1;
		mask <<= byte_bit;

		uchar = cmos_read(byte);
		uchar &= ~mask;
		uchar |= (ret[0] << byte_bit);
		cmos_write(uchar, byte);
		if (byte >= LB_CKS_RANGE_START && byte <= LB_CKS_RANGE_END)
			chksum_update_needed = 1;
	} else { /* more that one byte so transfer the whole bytes */
		if (byte_bit || length % 8)
			return CB_ERR_ARG;

		for (i = 0; length; i++, length -= 8, byte++) {
			cmos_write(ret[i], byte);
			if (byte >= LB_CKS_RANGE_START &&
			    byte <= LB_CKS_RANGE_END)
				chksum_update_needed = 1;
		}
	}

	if (chksum_update_needed) {
		cmos_set_checksum(LB_CKS_RANGE_START, LB_CKS_RANGE_END,
				  LB_CKS_LOC);
	}
	return CB_SUCCESS;
}

unsigned int read_option_lowlevel(unsigned int start, unsigned int size,
				  unsigned int def)
{
	printk(BIOS_NOTICE, "NOTICE: read_option() used to access CMOS "
		"from non-ROMCC code, please use get_option() instead.\n");
	if (CONFIG(USE_OPTION_TABLE)) {
		const unsigned char byte = cmos_read(start / 8);
		return (byte >> (start & 7U)) & ((1U << size) - 1U);
	}
	return def;
}

enum cb_err set_option(const char *name, void *value)
{
	struct cmos_option_table *ct;
	struct region_device rdev;
	struct cmos_entries *ce;
	unsigned long length;
	size_t namelen;
	int found = 0;

	if (!CONFIG(USE_OPTION_TABLE))
		return CB_CMOS_OTABLE_DISABLED;

	/* Figure out how long name is */
	namelen = strnlen(name, CMOS_MAX_NAME_LENGTH);

	if (locate_cmos_layout(&rdev) != CB_SUCCESS) {
		return CB_CMOS_LAYOUT_NOT_FOUND;
	}
	ct = rdev_mmap_full(&rdev);
	if (!ct) {
		printk(BIOS_ERR, "RTC: cmos_layout.bin could not be mapped. "
		       "Options are disabled\n");

		return CB_CMOS_LAYOUT_NOT_FOUND;
	}

	/* find the requested entry record */
	ce = (struct cmos_entries *)((unsigned char *)ct + ct->header_length);
	for (; ce->tag == LB_TAG_OPTION;
		ce = (struct cmos_entries *)((unsigned char *)ce + ce->size)) {
		if (memcmp(ce->name, name, namelen) == 0) {
			found = 1;
			break;
		}
	}
	if (!found) {
		printk(BIOS_DEBUG, "WARNING: No CMOS option '%s'.\n", name);
		rdev_munmap(&rdev, ct);
		return CB_CMOS_OPTION_NOT_FOUND;
	}

	length = ce->length;
	if (ce->config == 's') {
		length = MAX(strlen((const char *)value) * 8, ce->length - 8);
		/* make sure the string is null terminated */
		if (set_cmos_value(ce->bit + ce->length - 8, 8, &(u8[]){0})
		    != CB_SUCCESS) {
			rdev_munmap(&rdev, ct);
			return CB_CMOS_ACCESS_ERROR;
		}
	}

	if (set_cmos_value(ce->bit, length, value) != CB_SUCCESS) {
		rdev_munmap(&rdev, ct);
		return CB_CMOS_ACCESS_ERROR;
	}

	rdev_munmap(&rdev, ct);
	return CB_SUCCESS;
}

/*
 * If the CMOS is cleared, the rtc_reg has the invalid date. That
 * hurts some OSes. Even if we don't set USE_OPTION_TABLE, we need
 * to make sure the date is valid.
 */
void cmos_check_update_date(void)
{
	u8 year, century;

	/* Assume hardware always supports RTC_CLK_ALTCENTURY. */
	wait_uip();
	century = cmos_read(RTC_CLK_ALTCENTURY);
	year = cmos_read(RTC_CLK_YEAR);

	/*
	 * TODO: If century is 0xFF, 100% that the cmos is cleared.
	 * Other than that, so far rtc_year is the only entry to check
	 * if the date is valid.
	 */
	if (century > 0x99 || year > 0x99) /* Invalid date */
		cmos_reset_date();
}

int rtc_set(const struct rtc_time *time)
{
	cmos_write(bin2bcd(time->sec), RTC_CLK_SECOND);
	cmos_write(bin2bcd(time->min), RTC_CLK_MINUTE);
	cmos_write(bin2bcd(time->hour), RTC_CLK_HOUR);
	cmos_write(bin2bcd(time->mday), RTC_CLK_DAYOFMONTH);
	cmos_write(bin2bcd(time->mon), RTC_CLK_MONTH);
	cmos_write(bin2bcd(time->year % 100), RTC_CLK_YEAR);
	/* Same assumption as above: We always have RTC_CLK_ALTCENTURY */
	cmos_write(bin2bcd(time->year / 100), RTC_CLK_ALTCENTURY);
	cmos_write(bin2bcd(time->wday + 1), RTC_CLK_DAYOFWEEK);
	return 0;
}

int rtc_get(struct rtc_time *time)
{
	wait_uip();
	time->sec = bcd2bin(cmos_read(RTC_CLK_SECOND));
	time->min = bcd2bin(cmos_read(RTC_CLK_MINUTE));
	time->hour = bcd2bin(cmos_read(RTC_CLK_HOUR));
	time->mday = bcd2bin(cmos_read(RTC_CLK_DAYOFMONTH));
	time->mon = bcd2bin(cmos_read(RTC_CLK_MONTH));
	time->year = bcd2bin(cmos_read(RTC_CLK_YEAR));
	/* Same assumption as above: We always have RTC_CLK_ALTCENTURY */
	time->year += bcd2bin(cmos_read(RTC_CLK_ALTCENTURY)) * 100;
	time->wday = bcd2bin(cmos_read(RTC_CLK_DAYOFWEEK)) - 1;
	return 0;
}

/*
 * Signal coreboot proper completed -- just before running payload
 * or jumping to ACPI S3 wakeup vector.
 */
void set_boot_successful(void)
{
	uint8_t index, byte;

	index = inb(RTC_PORT(0)) & 0x80;
	index |= RTC_BOOT_BYTE;
	outb(index, RTC_PORT(0));

	byte = inb(RTC_PORT(1));

	if (CONFIG(SKIP_MAX_REBOOT_CNT_CLEAR)) {
		/*
		 * Set the fallback boot bit to allow for recovery if
		 * the payload fails to boot.
		 * It is the responsibility of the payload to reset
		 * the normal boot bit to 1 if desired
		 */
		byte &= ~RTC_BOOT_NORMAL;
	} else {
		/* If we are in normal mode set the boot count to 0 */
		if (byte & RTC_BOOT_NORMAL)
			byte &= 0x0f;

	}

	outb(byte, RTC_PORT(1));
}
