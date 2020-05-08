/* This file is part of the superiotool project */
/*
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

#include "superiotool.h"

#define DEVICE_SCRATCH_REG	0x21

static const struct superio_registers reg_table[] = {
	{0x00, "AST2400", {
		{NOLDN, NULL,
			{0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,
			 0x29,0x2a,0x2b,0x2c,0x2d,0x2e,0x2f,EOT},
			{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			 0x00,0x00,0x00,0x00,0x00,0x00,0x00,EOT}},
		{0x02, "SUART1",
			{0x30,0x60,0x61,0x70,0x71,0xf0,EOT},
			{0x00,0x03,0xf8,0x04,0x02,RSVD,EOT}},
		{0x03, "SUART2",
			{0x30,0x60,0x61,0x70,0x71,0xf0,EOT},
			{0x00,0x02,0xf8,0x03,0x02,0x00,EOT}},
		{0x04, "SWC",
			{0x30,0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67,
			 0x70,0x71,EOT},
			{0x00,0x08,0xe6,0x08,0xe0,0x08,0xe4,0x08,0xe8,
			 0x09,0x01,EOT}},
		{0x05, "Keyboard config (KBC)",
			{0x30,0x60,0x61,0x62,0x63,0x70,0x71,0x72,0x73,
			 0xf0,EOT},
			{0x00,0x00,0x60,0x00,0x64,0x01,0x02,0x0c,0x02,
			 0x83,EOT}},
		{0x07, "GPIO",
			{0x30,0x38,0x70,0x71,EOT},
			{0x00,0x00,0x0b,0x01,EOT}},
		{0x0b, "SUART3",
			{0x30,0x60,0x61,0x70,0x71,0xf0,EOT},
			{0x00,0x03,0xe8,0x06,0x02,0x00,EOT}},
		{0x0c, "SUART4",
			{0x30,0x60,0x61,0x70,0x71,0xf0,EOT},
			{0x00,0x02,0xe8,0x05,0x02,0x00,EOT}},
		{0x0d, "iLPC2AHB",
			{0x30,0x70,0x71,0xf0,0xf1,0xf2,0xf3,0xf4,0xf5,
			 0xf6,0xf7,0xf8,0xfe,EOT},
			{0x00,0x09,0x01,NANA,NANA,NANA,NANA,NANA,NANA,
			 NANA,NANA,0x00,0x00,EOT}},
		{0x0e, "Mailbox",
			{0x30,0x60,0x61,0x70,0x71,EOT},
			{0x00,0x08,0xc0,0x09,0x01,EOT}},
		{EOT}}},
	{EOT}
};

static void enter_conf_mode_ast(uint16_t port)
{
	OUTB(0xa5, port);
	OUTB(0xa5, port);
}

static void exit_conf_mode_ast(uint16_t port)
{
	OUTB(0xaa, port);
}

static int detect_ast_superio(uint16_t port)
{
	int i;
	enter_conf_mode_ast(port);

	/* Aspeed devices doesn't have a DEVICE_ID_REG.
	 * Host cycles that aren't decoded read as 0xff.
	 * Probe for the scratch register that are initialized to zero.
	 * The firmware might overwrite that, but it's the best we have.
	 */

	for (i = DEVICE_SCRATCH_REG; i < 0x30; i++) {
		if (regval(port, i) != 0xff)
			break;
	}
	if (i == 0x30) {
		if (verbose)
			printf(NOTFOUND
			       "scratch registers all read as 0xff\n");
	}
	exit_conf_mode_ast(port);

	return i < 0x30;
}

void probe_idregs_aspeed(uint16_t port)
{
	uint16_t chip_id = 0;

	probing_for("Aspeed", "", port);

	if (!detect_ast_superio(port))
		return;

	if (superio_unknown(reg_table, chip_id)) {
		if (verbose)
			printf(NOTFOUND "id=0x%02x\n", chip_id);
		return;
	}

	printf("Found Aspeed %s (id=0x%02x) at 0x%x\n",
	       get_superio_name(reg_table, chip_id), chip_id, port);
	chip_found = 1;

	enter_conf_mode_ast(port);
	dump_superio("Aspeed", reg_table, port, chip_id, LDN_SEL);
	exit_conf_mode_ast(port);
}

void print_aspeed_chips(void)
{
	print_vendor_chips("Aspeed", reg_table);
}
