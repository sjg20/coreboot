/* SPDX-License-Identifier: GPL-2.0-only */

/*
 * Declares assorted devices that falls under this southbridge.
 */
#include "southbridge/intel/i82371eb/i82371eb.h"

	OperationRegion (S1XX, PCI_Config, 0xB2, 0x01)
	Field (S1XX, ByteAcc, NoLock, Preserve)
	{
		FXS1,   8
	}

	/* 8259-compatible Programmable Interrupt Controller */
	Device (PIC)
	{
		Name (_HID, EisaId ("PNP0000"))
		Name (_CRS, ResourceTemplate ()
		{
			IO (Decode16, 0x0020, 0x0020, 0x01, 0x02,)
			IO (Decode16, 0x00A0, 0x00A0, 0x01, 0x02,)
			IRQNoFlags () {2}
		})
	}

	/* PC-class DMA Controller */
	Device (DMA1)
	{
		Name (_HID, EisaId ("PNP0200"))
		Name (_CRS, ResourceTemplate ()
		{
			DMA (Compatibility, BusMaster, Transfer8,) {4}
			IO (Decode16, 0x0000, 0x0000, 0x01, 0x10,)
			IO (Decode16, 0x0080, 0x0080, 0x01, 0x11,)
			IO (Decode16, 0x0094, 0x0094, 0x01, 0x0C,)
			IO (Decode16, 0x00C0, 0x00C0, 0x01, 0x20,)
		})
	}

	/* PC-class System Timer */
	Device (TMR)
	{
		Name (_HID, EisaId ("PNP0100"))
		Name (_CRS, ResourceTemplate ()
		{
			IO (Decode16,0x0040,0x0040,0x01,0x04,)
			IRQNoFlags () {0}
		})
	}

	/* AT Real-Time Clock */
	Device (RTC)
	{
		Name (_HID, EisaId ("PNP0B00"))
		Name (_CRS, ResourceTemplate ()
		{
			IO (Decode16,0x0070,0x0070,0x01,0x04,)
			IRQNoFlags () {8}
		})
	}

	Device (SPKR)
	{
		Name (_HID, EisaId ("PNP0800"))
		Name (_CRS, ResourceTemplate ()
		{
			IO (Decode16,0x0061,0x0061,0x01,0x01,)
		})
	}

	/* x87-compatible Floating Point Processing Unit */
	Device (COPR)
	{
		Name (_HID, EisaId ("PNP0C04"))
		Name (_CRS, ResourceTemplate ()
		{
			IO (Decode16,0x00F0,0x00F0,0x01,0x10,)
			IRQNoFlags () {13}
		})
	}
