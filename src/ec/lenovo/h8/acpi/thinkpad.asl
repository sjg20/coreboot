/* SPDX-License-Identifier: GPL-2.0-only */

Device (HKEY)
{
	/* Generated by ssdt.c */
	External (\HBDC, IntObj)
	External (\HWAN, IntObj)
	External (\HKBL, IntObj)
	External (\HUWB, IntObj)

	Name (_HID, EisaId (CONFIG_THINKPADEC_HKEY_EISAID))

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
		Local0 = BTN
		If (Local0 != 0) {
			BTN = Zero
			Local0 += 0x1000
			Return (Local0)
		}
		Local0 = BTAB
		If (Local0 != 0) {
			BTAB = Zero
			Local0 += 0x5000
			Return (Local0)
		}
		Return (Zero)
	}

	/* Report event  */
	Method (RHK, 1, NotSerialized) {
		ShiftLeft (One, Arg0 - 1, Local0)
		If (EMSK & Local0) {
			BTN = Arg0
			Notify (HKEY, 0x80)
		}
	}

	/* Report tablet  */
	Method (RTAB, 1, NotSerialized) {
		ShiftLeft (One, Arg0 - 1, Local0)
		If (ETAB & Local0) {
			BTAB = Arg0
			Notify (HKEY, 0x80)
		}
	}

	/* Enable/disable all events.  */
	Method (MHKC, 1, NotSerialized) {
		If (Arg0) {
			EMSK = DHKN
			ETAB = Ones
		}
		Else
		{
			EMSK = Zero
			ETAB = Zero
		}
		EN = Arg0
	}

	/* Enable/disable event.  */
	Method (MHKM, 2, NotSerialized) {
		If (Arg0 <= 0x20) {
			ShiftLeft (One, Arg0 - 1, Local0)
			If (Arg1)
			{
				Or (DHKN, Local0, DHKN)
			}
			Else
			{
				DHKN = DHKN & ~Local0
			}
			If (EN)
			{
				EMSK = DHKN
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
		ALMT = Arg0
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
		HAST = One

		If (HBDC) {
			Local0 = One
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
		HAST = One

		If (HBDC) {
			Local0 = (Arg0 & 2) >> 1
			\_SB.PCI0.LPCB.EC.BTEB = Local0
			Local0 = (Arg0 & 4) >> 2
			WBDC = Local0
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
		HAST = One

		If (HWAN) {
			Local0 = One
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
		HAST = One

		If (HWAN) {
			Local0 = (Arg0 & 2) >> 1
			\_SB.PCI0.LPCB.EC.WWEB = Local0
			WWAN = (Arg0 & 4) >> 2
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
			Local0 = 0x200
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
			\_SB.PCI0.LPCB.EC.WWEB = Arg0 & 1
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
			Local0 = One
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
			Local0 = (Arg0 & 2) >> 1
			\_SB.PCI0.LPCB.EC.UWBE = Local0
		}
	}

	/*
	 * Called from _WAK
	 */
	Method (WAKE, 1)
	{
		If (HAST) {
			\_SB.PCI0.LPCB.EC.BTEB = WBDC
			\_SB.PCI0.LPCB.EC.WWEB = WWAN
		}
	}

	#if CONFIG(H8_HAS_BAT_THRESHOLDS_IMPL)
	#include "thinkpad_bat_thresholds.asl"
	#endif
}
