/* This file is part of the superiotool project */
/* SPDX-License-Identifier: GPL-2.0-or-later */

#include "superiotool.h"

#define DEVICE_ID_REG		0x20
#define DEVICE_REV_REG		0x21

static const struct superio_registers reg_table[] = {
	{0xb7, "SB7xx", {
		{NOLDN, NULL,
			{0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x28,0x29,0x2a,
			 0x2b,0x2c,0x2e, 0x2f, EOT},
			 {NANA,NANA,NANA,NANA,NANA,NANA,NANA,NANA,NANA,NANA,NANA,NANA,NANA,NANA,EOT}},
		{0x3, "EC channel 0",
			{0x30,0x60,0x61, EOT},
			 {NANA,NANA,NANA,EOT}},
		{0x5, "Irda",
			{0x30,0x60,0x61,0x70, EOT},
			 {NANA,NANA,NANA,NANA,EOT}},
		{0x7, "Keyboard Controller",
			{0x30, EOT},
			 {NANA,EOT}},
		{0x9, "Mailbox",
			{0x30,0x60,0x61, EOT},
			{NANA,NANA,NANA,EOT}},
		{EOT}}},
	{0xb8, "SB8xx", {
		{NOLDN, NULL,
			{0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x28,0x29,0x2a,
			 0x2b,0x2c,0x2e, 0x2f, EOT},
			 {NANA,NANA,NANA,NANA,NANA,NANA,NANA,NANA,NANA,NANA,NANA,NANA,NANA,NANA,EOT}},
		{0x3, "EC channel 0",
			{0x30,0x60,0x61, EOT},
			 {NANA,NANA,NANA,EOT}},
		{0x5, "Irda",
			{0x30,0x60,0x61,0x70, EOT},
			 {NANA,NANA,NANA,NANA,EOT}},
		{0x7, "Keyboard Controller",
			{0x30, EOT},
			 {NANA,EOT}},
		{0x9, "Mailbox",
			{0x30,0x60,0x61, EOT},
			{NANA,NANA,NANA,EOT}},
		{EOT}}},
	{EOT}
};

/* same as serverengines */
static void enter_conf_mode_ec(uint16_t port)
{
	OUTB(0x5a, port);
}

static void exit_conf_mode_ec(uint16_t port)
{
	OUTB(0xa5, port);
}

uint16_t detect_ec(void)
{
	uint16_t ec_port;
	struct pci_dev *dev;

	dev = pci_dev_find(0x1002, 0x439d);

	if (!dev) {
		return 0;
	}

	/* is EC disabled ? */
	if (!(pci_read_byte(dev, 0x40) & (1 << 7)))
		return 0;

	ec_port = pci_read_word(dev, 0xa4);

	if (!(ec_port & 0x1))
		return 0;

	ec_port &= ~0x1;

	return ec_port;
}

void probe_idregs_amd(uint16_t port)
{
	uint8_t rev, devid;

	probing_for("AMD EC", "", port);

	if (!(port = detect_ec()))
		return;

	enter_conf_mode_ec(port);

	devid = regval(port, DEVICE_ID_REG);
	rev = regval(port, DEVICE_REV_REG);

	if (superio_unknown(reg_table, devid)) {
		if (verbose)
			printf(NOTFOUND "id=0x%02x, rev=0x%02x\n", devid, rev);
		exit_conf_mode_ec(port);
		return;
	}

	printf("Found AMD EC %s (id=0x%02x, rev=0x%02x) at 0x%x\n",
	       get_superio_name(reg_table, devid), devid, rev, port);
	chip_found = 1;

	dump_superio("AMD EC", reg_table, port, devid, LDN_SEL);

	exit_conf_mode_ec(port);
}

void print_amd_chips(void)
{
	print_vendor_chips("AMD EC", reg_table);
}
