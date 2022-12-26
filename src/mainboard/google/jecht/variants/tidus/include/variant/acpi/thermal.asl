/* SPDX-License-Identifier: GPL-2.0-only */

/* Generated by acpigen */
External (\PPKG, MethodObj)

#include "../thermal.h"

// Thermal Zone

#define HAVE_THERMALZONE
Scope (\_TZ)
{
	ThermalZone (THRM)
	{
		Name (_TC1, 0x02)
		Name (_TC2, 0x05)

		// Thermal zone polling frequency: 10 seconds
		Name (_TZP, 100)

		// Thermal sampling period for passive cooling: 2 seconds
		Name (_TSP, 20)

		Name (F0ON, FAN0_2_THRESHOLD_ON)
		Name (F0OF, FAN0_2_THRESHOLD_OFF)
		Name (F0PW, FAN0_2_PWM)
		Name (F1ON, FAN1_2_THRESHOLD_ON)
		Name (F1OF, FAN1_2_THRESHOLD_OFF)
		Name (F1PW, FAN1_2_PWM)
		Name (F2ON, FAN2_2_THRESHOLD_ON)
		Name (F2OF, FAN2_2_THRESHOLD_OFF)
		Name (F2PW, FAN2_2_PWM)
		Name (F3ON, FAN3_2_THRESHOLD_ON)
		Name (F3OF, FAN3_2_THRESHOLD_OFF)
		Name (F3PW, FAN3_2_PWM)
		Name (F4PW, FAN4_2_PWM)
		Name (THTB, 2)

		// Convert from Degrees C to 1/10 Kelvin for ACPI
		Method (CTOK, 1) {
			// 10th of Degrees C
			Local0 = Arg0 * 10

			// Convert to Kelvin
			Local0 += 2732

			Return (Local0)
		}

		// Thermal Table 0
		Method (TTB0, 0) {
			F0ON = FAN0_0_THRESHOLD_ON
			F0OF = FAN0_0_THRESHOLD_OFF
			F0PW = FAN0_0_PWM
			F1ON = FAN1_0_THRESHOLD_ON
			F1OF = FAN1_0_THRESHOLD_OFF
			F1PW = FAN1_0_PWM
			F2ON = FAN2_0_THRESHOLD_ON
			F2OF = FAN2_0_THRESHOLD_OFF
			F2PW = FAN2_0_PWM
			F3ON = FAN3_0_THRESHOLD_ON
			F3OF = FAN3_0_THRESHOLD_OFF
			F3PW = FAN3_0_PWM
			F4PW = FAN4_0_PWM
			THTB = 0
		}

		// Thermal Table 1
		Method (TTB1, 0) {
			F0ON = FAN0_1_THRESHOLD_ON
			F0OF = FAN0_1_THRESHOLD_OFF
			F0PW = FAN0_1_PWM
			F1ON = FAN1_1_THRESHOLD_ON
			F1OF = FAN1_1_THRESHOLD_OFF
			F1PW = FAN1_1_PWM
			F2ON = FAN2_1_THRESHOLD_ON
			F2OF = FAN2_1_THRESHOLD_OFF
			F2PW = FAN2_1_PWM
			F3ON = FAN3_1_THRESHOLD_ON
			F3OF = FAN3_1_THRESHOLD_OFF
			F3PW = FAN3_1_PWM
			F4PW = FAN4_1_PWM
			THTB = 1
		}

		// Thermal Table 2
		Method (TTB2, 0) {
			F0ON = FAN0_2_THRESHOLD_ON
			F0OF = FAN0_2_THRESHOLD_OFF
			F0PW = FAN0_2_PWM
			F1ON = FAN1_2_THRESHOLD_ON
			F1OF = FAN1_2_THRESHOLD_OFF
			F1PW = FAN1_2_PWM
			F2ON = FAN2_2_THRESHOLD_ON
			F2OF = FAN2_2_THRESHOLD_OFF
			F2PW = FAN2_2_PWM
			F3ON = FAN3_2_THRESHOLD_ON
			F3OF = FAN3_2_THRESHOLD_OFF
			F3PW = FAN3_2_PWM
			F4PW = FAN4_2_PWM
			THTB = 2
		}

		// Update Thermal Table
		Method (UPTB, 0) {
			// Get System Temperature via SuperIO TMPIN2
			Local0 = \_SB.PCI0.LPCB.SIO.ENVC.TIN2

			// Check for "no reading available
			If (Local0 == 0x80) {
				Local0 = THERMAL_POLICY_0_THRESHOLD_ON
			}

			// Check for invalid readings
			If (Local0 == 255 || Local0 == 0) {
				Local0 = THERMAL_POLICY_0_THRESHOLD_ON
			}

			If (THTB == 2) {
				If (Local0 >= THERMAL_POLICY_0_THRESHOLD_ON) {
					TTB0 ()
				} ElseIf (Local0 >= THERMAL_POLICY_1_THRESHOLD_ON) {
					TTB1 ()
				}
			} ElseIf (THTB == 1) {
				If (Local0 >= THERMAL_POLICY_0_THRESHOLD_ON) {
					TTB0 ()
				} ElseIf (Local0 <= THERMAL_POLICY_1_THRESHOLD_OFF) {
					TTB2 ()
				}
			} Else {
				If (Local0 < THERMAL_POLICY_1_THRESHOLD_OFF) {
					TTB2 ()
				} ElseIf (Local0 <= THERMAL_POLICY_0_THRESHOLD_OFF) {
					TTB1 ()
				}
			}
		}

		// Threshold for OS to shutdown
		Method (_CRT, 0, Serialized)
		{
			Return (CTOK (\TCRT))
		}

		// Threshold for passive cooling
		Method (_PSV, 0, Serialized)
		{
			Return (CTOK (\TPSV))
		}

		// Processors used for passive cooling
		Method (_PSL, 0, Serialized)
		{
			Return (\PPKG ())
		}

		// Start fan at state 4 = lowest temp state
		Method (_INI)
		{
			\FLVL = 4
			\_SB.PCI0.LPCB.SIO.ENVC.F2PS = FAN4_2_PWM
			Notify (\_TZ.THRM, 0x81)
		}

		Method (TCHK, 0, Serialized)
		{
			// Update Thermal Table
			UPTB ()

			// Get CPU Temperature from PECI via SuperIO TMPIN3
			Local0 = \_SB.PCI0.LPCB.SIO.ENVC.TIN3

			// Check for "no reading available
			If (Local0 == 0x80) {
				Return (CTOK (FAN0_0_THRESHOLD_ON))
			}

			// Check for invalid readings
			If (Local0 == 255 || Local0 == 0) {
				Return (CTOK (FAN0_0_THRESHOLD_ON))
			}

			// PECI raw value is an offset from Tj_max
			Local1 = 255 - Local0

			// Handle values greater than Tj_max
			If (Local1 >= \TMAX) {
				Return (CTOK (\TMAX))
			}

			// Subtract from Tj_max to get temperature
			Local0 = \TMAX - Local1
			Return (CTOK (Local0))
		}

		Method (_TMP, 0, Serialized)
		{
			// Get temperature from SuperIO in deci-kelvin
			Local0 = TCHK ()

			// Critical temperature in deci-kelvin
			Local1 = CTOK (\TMAX)

			If (Local0 >= Local1) {
				Printf ("CRITICAL TEMPERATURE: %o", Local0)

				// Wait 1 second for SuperIO to re-poll
				Sleep (1000)

				// Re-read temperature from SuperIO
				Local0 = TCHK ()

				Printf ("RE-READ TEMPERATURE: %o", Local0)
			}

			Return (Local0)
		}

		Method (_AC0) {
			If (\FLVL <= 0) {
				Return (CTOK (F0OF))
			} Else {
				Return (CTOK (F0ON))
			}
		}

		Method (_AC1) {
			If (\FLVL <= 1) {
				Return (CTOK (F1OF))
			} Else {
				Return (CTOK (F1ON))
			}
		}

		Method (_AC2) {
			If (\FLVL <= 2) {
				Return (CTOK (F2OF))
			} Else {
				Return (CTOK (F2ON))
			}
		}

		Method (_AC3) {
			If (\FLVL <= 3) {
				Return (CTOK (F3OF))
			} Else {
				Return (CTOK (F3ON))
			}
		}

		Method (_AC4) {
			If (\FLVL <= 4) {
				Return (CTOK (0))
			} Else {
				Return (CTOK (0))
			}
		}

		Name (_AL0, Package () { FAN0 })
		Name (_AL1, Package () { FAN1 })
		Name (_AL2, Package () { FAN2 })
		Name (_AL3, Package () { FAN3 })
		Name (_AL4, Package () { FAN4 })

		PowerResource (FNP0, 0, 0)
		{
			Method (_STA) {
				If (\FLVL <= 0) {
					Return (1)
				} Else {
					Return (Zero)
				}
			}
			Method (_ON)  {
				If (! _STA ()) {
					\FLVL = 0
					\_SB.PCI0.LPCB.SIO.ENVC.F2PS = F0PW
					Notify (\_TZ.THRM, 0x81)
				}
			}
			Method (_OFF) {
				If (_STA ()) {
					\FLVL = 1
					\_SB.PCI0.LPCB.SIO.ENVC.F2PS = F1PW
					Notify (\_TZ.THRM, 0x81)
				}
			}
		}

		PowerResource (FNP1, 0, 0)
		{
			Method (_STA) {
				If (\FLVL <= 1) {
					Return (1)
				} Else {
					Return (Zero)
				}
			}
			Method (_ON)  {
				If (! _STA ()) {
					\FLVL = 1
					\_SB.PCI0.LPCB.SIO.ENVC.F2PS = F1PW
					Notify (\_TZ.THRM, 0x81)
				}
			}
			Method (_OFF) {
				If (_STA ()) {
					\FLVL = 2
					\_SB.PCI0.LPCB.SIO.ENVC.F2PS = F2PW
					Notify (\_TZ.THRM, 0x81)
				}
			}
		}

		PowerResource (FNP2, 0, 0)
		{
			Method (_STA) {
				If (\FLVL <= 2) {
					Return (1)
				} Else {
					Return (Zero)
				}
			}
			Method (_ON)  {
				If (! _STA ()) {
					\FLVL = 2
					\_SB.PCI0.LPCB.SIO.ENVC.F2PS = F2PW
					Notify (\_TZ.THRM, 0x81)
				}
			}
			Method (_OFF) {
				If (_STA ()) {
					\FLVL = 3
					\_SB.PCI0.LPCB.SIO.ENVC.F2PS = F3PW
					Notify (\_TZ.THRM, 0x81)
				}
			}
		}

		PowerResource (FNP3, 0, 0)
		{
			Method (_STA) {
				If (\FLVL <= 3) {
					Return (1)
				} Else {
					Return (Zero)
				}
			}
			Method (_ON)  {
				If (! _STA ()) {
					\FLVL = 3
					\_SB.PCI0.LPCB.SIO.ENVC.F2PS = F3PW
					Notify (\_TZ.THRM, 0x81)
				}
			}
			Method (_OFF) {
				If (_STA ()) {
					\FLVL = 4
					\_SB.PCI0.LPCB.SIO.ENVC.F2PS = F4PW
					Notify (\_TZ.THRM, 0x81)
				}
			}
		}

		PowerResource (FNP4, 0, 0)
		{
			Method (_STA) {
				If (\FLVL <= 4) {
					Return (1)
				} Else {
					Return (Zero)
				}
			}
			Method (_ON)  {
				If (! _STA ()) {
					\FLVL = 4
					\_SB.PCI0.LPCB.SIO.ENVC.F2PS = F4PW
					Notify (\_TZ.THRM, 0x81)
				}
			}
			Method (_OFF) {
				If (_STA ()) {
					\FLVL = 4
					\_SB.PCI0.LPCB.SIO.ENVC.F2PS = F4PW
					Notify (\_TZ.THRM, 0x81)
				}
			}
		}

		Device (FAN0)
		{
			Name (_HID, EISAID ("PNP0C0B"))
			Name (_UID, 0)
			Name (_PR0, Package () { FNP0 })
		}

		Device (FAN1)
		{
			Name (_HID, EISAID ("PNP0C0B"))
			Name (_UID, 1)
			Name (_PR0, Package () { FNP1 })
		}

		Device (FAN2)
		{
			Name (_HID, EISAID ("PNP0C0B"))
			Name (_UID, 2)
			Name (_PR0, Package () { FNP2 })
		}

		Device (FAN3)
		{
			Name (_HID, EISAID ("PNP0C0B"))
			Name (_UID, 3)
			Name (_PR0, Package () { FNP3 })
		}

		Device (FAN4)
		{
			Name (_HID, EISAID ("PNP0C0B"))
			Name (_UID, 4)
			Name (_PR0, Package () { FNP4 })
		}
	}
}
