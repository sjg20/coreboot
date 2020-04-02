/* SPDX-License-Identifier: GPL-2.0-only */
/* This file is part of the coreboot project. */

/* File taken from the Linux xgifb driver (v3.18.5) */

#include "xgi_coreboot.h"
#include "vgatypes.h"
#include "vb_util.h"

void xgifb_reg_set(unsigned long port, u8 index, u8 data)
{
	outb(index, port);
	outb(data, port + 1);
}

u8 xgifb_reg_get(unsigned long port, u8 index)
{
	u8 data;

	outb(index, port);
	data = inb(port + 1);
	return data;
}

void xgifb_reg_and_or(unsigned long port, u8 index,
		unsigned int data_and, unsigned int data_or)
{
	u8 temp;

	temp = xgifb_reg_get(port, index); /* XGINew_Part1Port index 02 */
	temp = (temp & data_and) | data_or;
	xgifb_reg_set(port, index, temp);
}

void xgifb_reg_and(unsigned long port, u8 index, unsigned int data_and)
{
	u8 temp;

	temp = xgifb_reg_get(port, index); /* XGINew_Part1Port index 02 */
	temp &= data_and;
	xgifb_reg_set(port, index, temp);
}

void xgifb_reg_or(unsigned long port, u8 index, unsigned int data_or)
{
	u8 temp;

	temp = xgifb_reg_get(port, index); /* XGINew_Part1Port index 02 */
	temp |= data_or;
	xgifb_reg_set(port, index, temp);
}
