/*
 * This file is part of the coreboot project.
 *
 * Copyright (c) 2011 Sven Schnelle <svens@stackframe.org>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; version 2 of
 * the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

Device (HKEY)
{
	/* Generated by ssdt.c */
	External (\HBDC, IntObj)
	External (\HWAN, IntObj)
	External (\HKBL, IntObj)
	External (\HUWB, IntObj)

	Name (_HID, EisaId ("IBM0068"))

	Name (BTN, 0)

	Name (BTAB, 0)

	/* MASK */
	Name (DHKN, 0x080C)

	/* Effective Mask */
	Name (EMSK, 0)

	/* Effective Mask for tablet */
	Name (ETAB, 0)

	/* Device enabled. */
	Name (EN, 0)

	Method (_STA, 0, NotSerialized)
	{
		Return (0x0F)
	}

	/* Retrieve event. */
	Method (MHKP, 0, NotSerialized)
	{
		Store (BTN, Local0)
		If (LNotEqual (Local0, Zero)) {
			Store (Zero, BTN)
			Add (Local0, 0x1000, Local0)
			Return (Local0)
		}
		Store (BTAB, Local0)
		If (LNotEqual (Local0, Zero)) {
			Store (Zero, BTAB)
			Add (Local0, 0x5000, Local0)
			Return (Local0)
		}
		Return (Zero)
	}

	/* Report event  */
	Method (RHK, 1, NotSerialized) {
		ShiftLeft (One, Subtract (Arg0, 1), Local0)
		If (And (EMSK, Local0)) {
			Store (Arg0, BTN)
			Notify (HKEY, 0x80)
		}
	}

	/* Report tablet  */
	Method (RTAB, 1, NotSerialized) {
		ShiftLeft (One, Subtract (Arg0, 1), Local0)
		If (And (ETAB, Local0)) {
			Store (Arg0, BTAB)
			Notify (HKEY, 0x80)
		}
	}

	/* Enable/disable all events.  */
	Method (MHKC, 1, NotSerialized) {
		If (Arg0) {
			Store (DHKN, EMSK)
			Store (Ones, ETAB)
		}
		Else
		{
			Store (Zero, EMSK)
			Store (Zero, ETAB)
		}
		Store (Arg0, EN)
	}

	/* Enable/disable event.  */
	Method (MHKM, 2, NotSerialized) {
		If (LLessEqual (Arg0, 0x20)) {
			ShiftLeft (One, Subtract (Arg0, 1), Local0)
			If (Arg1)
			{
				Or (DHKN, Local0, DHKN)
			}
			Else
			{
				And (DHKN, Not (Local0), DHKN)
			}
			If (EN)
			{
				Store (DHKN, EMSK)
			}
		}
	}

	/* Mask hotkey all. */
	Method (MHKA, 0, NotSerialized)
	{
		Return (0x07FFFFFF)
	}

	/* Report tablet mode switch state */
	Method (MHKG, 0, NotSerialized)
	{
		Return (ShiftLeft(TBSW, 3))
	}

	/* Mute audio */
	Method (SSMS, 1, NotSerialized)
	{
		Store(Arg0, ALMT)
	}

	/* Control mute microphone LED */
	Method (MMTS, 1, NotSerialized)
	{
		If (Arg0)
		{
			TLED(0x8E)
		}
		Else
		{
			TLED(0x0E)
		}
	}

	/* Version */
	Method (MHKV, 0, NotSerialized)
	{
		Return (0x0100)
	}

	/* Master wireless switch state */
	Method (WLSW, 0, NotSerialized)
	{
		Return (\_SB.PCI0.LPCB.EC.GSTS)
	}

	/* Set to one on first boot */
	Name (INIT, 0)

	/* Has thinkpad_acpi module loaded */
	Name (HAST, 0)

	/* State after sleep */
	Name (WBDC, 0)
	/*
	 * Returns the current state:
	 *  Bit 0: BT HW present
	 *  Bit 1: BT radio enabled
	 *  Bit 2: BT state at resume
	 */
	Method (GBDC, 0)
	{
		Store (One, HAST)

		If (HBDC) {
			Store(One, Local0)
			If(\_SB.PCI0.LPCB.EC.BTEB)
			{
				Or(Local0, 2, Local0)
			}
			Or(Local0, ShiftLeft(WBDC, 2), Local0)
			Return (Local0)
		} Else {
			Return (0)
		}
	}

	/*
	 * Set the current state:
	 *  Bit 1: BT radio enabled
	 *  Bit 2: BT state at resume
	 */
	Method (SBDC, 1)
	{
		Store (One, HAST)

		If (HBDC) {
			ShiftRight (And(Arg0, 2), 1, Local0)
			Store (Local0, \_SB.PCI0.LPCB.EC.BTEB)
			ShiftRight (And(Arg0, 4), 2, Local0)
			Store (Local0, WBDC)
		}
	}

	/* State after sleep */
	Name (WWAN, 0)
	/*
	 * Returns the current state:
	 *  Bit 0: WWAN HW present
	 *  Bit 1: WWAN radio enabled
	 *  Bit 2: WWAN state at resume
	 */
	Method (GWAN, 0)
	{
		Store (One, HAST)

		If (HWAN) {
			Store(One, Local0)
			If(\_SB.PCI0.LPCB.EC.WWEB)
			{
				Or(Local0, 2, Local0)
			}
			Or(Local0, ShiftLeft(WWAN, 2), Local0)
			Return (Local0)
		} Else {
			Return (0)
		}
	}

	/*
	 * Set the current state:
	 *  Bit 1: WWAN radio enabled
	 *  Bit 2: WWAN state at resume
	 */
	Method (SWAN, 1)
	{
		Store (One, HAST)

		If (HWAN) {
			ShiftRight (And(Arg0, 2), 1, Local0)
			Store (Local0, \_SB.PCI0.LPCB.EC.WWEB)
			ShiftRight (And(Arg0, 4), 2, WWAN)
		}
	}

	/*
	 * Argument is unused.
	 * Returns the current state:
	 *  Bit 9: Backlight HW present
	 *  Bit 0-1: Brightness level
	 */
	Method (MLCG, 1)
	{
		If (HKBL) {
			Store (0x200, Local0)
			/* FIXME: Support 2bit brightness control */
			Or (Local0, \_SB.PCI0.LPCB.EC.KBLT, Local0)
			Return (Local0)
		} Else {
			Return (0)
		}
	}

	/*
	 * Set the current state:
	 * Bit 0-1: Brightness level
	 */
	Method (MLCS, 1)
	{
		If (HKBL) {
			/* FIXME: Support 2bit brightness control */
			Store (And(Arg0, 1), \_SB.PCI0.LPCB.EC.WWEB)
		}
	}

	/*
	 * Returns the current state:
	 *  Bit 0: UWB HW present
	 *  Bit 1: UWB radio enabled
	 */
	Method (GUWB, 0)
	{
		If (HUWB) {
			Store (One, Local0)
			If(\_SB.PCI0.LPCB.EC.UWBE)
			{
				Or(Local0, 2, Local0)
			}
			Return (Local0)
		} Else {
			Return (0)
		}
	}

	/*
	 * Set the current state:
	 *  Bit 1: UWB radio enabled
	 */
	Method (SUWB, 1)
	{
		If (HUWB) {
			ShiftRight (And(Arg0, 2), 1, Local0)
			Store (Local0, \_SB.PCI0.LPCB.EC.UWBE)
		}
	}

	/*
	 * Called from _WAK
	 */
	Method (WAKE, 1)
	{
		If (HAST) {
			Store (WBDC, \_SB.PCI0.LPCB.EC.BTEB)
			Store (WWAN, \_SB.PCI0.LPCB.EC.WWEB)
		}
	}

	#if CONFIG(H8_HAS_BAT_TRESHOLDS_IMPL)
	#include "thinkpad_bat_thresholds.asl"
	#endif
}
