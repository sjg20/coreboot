/* SPDX-License-Identifier: GPL-2.0-only */

/* The _PTS method (Prepare To Sleep) is called before the OS is
 * entering a sleep state. The sleep state number is passed in Arg0
 */

Method(_PTS,1)
{
	Store (Zero, GP35)  // Disable WLAN
	Store (Zero, GP38)  // Disable WWAN

	If (S33G) {
		Store (Zero, GP43)  // Enable HSPA
	} Else {
		Store (One, GP43)   // Disable HSPA
	}

	If (LEqual (Arg0, 3)) {
		// NVS has a flag to determine USB policy in S3
		If (S3U0) {
			Store (One, GP47)   // Enable USB0
		} Else {
			Store (Zero, GP47)  // Disable USB0
		}

		// NVS has a flag to determine USB policy in S3
		If (S3U1) {
			Store (One, GP56)   // Enable USB1
		} Else {
			Store (Zero, GP56)  // Disable USB1
		}
	}
	If (LEqual (Arg0, 5)) {
		// NVS has a flag to determine USB policy in S5
		If (S5U0) {
			Store (One, GP47)   // Enable USB0
		} Else {
			Store (Zero, GP47)  // Disable USB0
		}

		// NVS has a flag to determine USB policy in S5
		If (S5U1) {
			Store (One, GP56)   // Enable USB1
		} Else {
			Store (Zero, GP56)  // Disable USB1
		}
	}
}

/* The _WAK method is called on system wakeup */

Method(_WAK,1)
{
	/* Update in case state changed while asleep */
	Store (\_SB.PCI0.LPCB.EC0.ACEX, \PWRS)

	/* Enable OS control of fan */
	Store (One, \_SB.PCI0.LPCB.EC0.FCOS)

	Return(Package(){0,0})
}
