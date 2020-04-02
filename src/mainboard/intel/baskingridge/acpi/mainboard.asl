/* SPDX-License-Identifier: GPL-2.0-only */
/* This file is part of the coreboot project. */

Device (PWRB)
{
	Name(_HID, EisaId("PNP0C0C"))

	// Wake
	Name(_PRW, Package(){0x1d, 0x05})
}
