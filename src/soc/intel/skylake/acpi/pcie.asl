/* SPDX-License-Identifier: GPL-2.0-only */
/* This file is part of the coreboot project. */

/* Intel PCH PCIe support */

Method (IRQM, 1, Serialized) {

	/* Interrupt Map INTA->INTA, INTB->INTB, INTC->INTC, INTD->INTD */
	Name (IQAA, Package () {
		Package () { 0x0000ffff, 0, 0, 16 },
		Package () { 0x0000ffff, 1, 0, 17 },
		Package () { 0x0000ffff, 2, 0, 18 },
		Package () { 0x0000ffff, 3, 0, 19 } })
	Name (IQAP, Package () {
		Package () { 0x0000ffff, 0, \_SB.PCI0.LNKA, 0 },
		Package () { 0x0000ffff, 1, \_SB.PCI0.LNKB, 0 },
		Package () { 0x0000ffff, 2, \_SB.PCI0.LNKC, 0 },
		Package () { 0x0000ffff, 3, \_SB.PCI0.LNKD, 0 } })

	/* Interrupt Map INTA->INTB, INTB->INTC, INTC->INTD, INTD->INTA */
	Name (IQBA, Package () {
		Package () { 0x0000ffff, 0, 0, 17 },
		Package () { 0x0000ffff, 1, 0, 18 },
		Package () { 0x0000ffff, 2, 0, 19 },
		Package () { 0x0000ffff, 3, 0, 16 } })
	Name (IQBP, Package () {
		Package () { 0x0000ffff, 0, \_SB.PCI0.LNKB, 0 },
		Package () { 0x0000ffff, 1, \_SB.PCI0.LNKC, 0 },
		Package () { 0x0000ffff, 2, \_SB.PCI0.LNKD, 0 },
		Package () { 0x0000ffff, 3, \_SB.PCI0.LNKA, 0 } })

	/* Interrupt Map INTA->INTC, INTB->INTD, INTC->INTA, INTD->INTB */
	Name (IQCA, Package () {
		Package () { 0x0000ffff, 0, 0, 18 },
		Package () { 0x0000ffff, 1, 0, 19 },
		Package () { 0x0000ffff, 2, 0, 16 },
		Package () { 0x0000ffff, 3, 0, 17 } })
	Name (IQCP, Package () {
		Package () { 0x0000ffff, 0, \_SB.PCI0.LNKC, 0 },
		Package () { 0x0000ffff, 1, \_SB.PCI0.LNKD, 0 },
		Package () { 0x0000ffff, 2, \_SB.PCI0.LNKA, 0 },
		Package () { 0x0000ffff, 3, \_SB.PCI0.LNKB, 0 } })

	/* Interrupt Map INTA->INTD, INTB->INTA, INTC->INTB, INTD->INTC */
	Name (IQDA, Package () {
		Package () { 0x0000ffff, 0, 0, 19 },
		Package () { 0x0000ffff, 1, 0, 16 },
		Package () { 0x0000ffff, 2, 0, 17 },
		Package () { 0x0000ffff, 3, 0, 18 } })
	Name (IQDP, Package () {
		Package () { 0x0000ffff, 0, \_SB.PCI0.LNKD, 0 },
		Package () { 0x0000ffff, 1, \_SB.PCI0.LNKA, 0 },
		Package () { 0x0000ffff, 2, \_SB.PCI0.LNKB, 0 },
		Package () { 0x0000ffff, 3, \_SB.PCI0.LNKC, 0 } })

	Switch (ToInteger (Arg0))
	{
		Case (Package () { 1, 5, 9, 13 }) {
			If (PICM) {
				Return (IQAA)
			} Else {
				Return (IQAP)
			}
		}

		Case (Package () { 2, 6, 10, 14 }) {
			If (PICM) {
				Return (IQBA)
			} Else {
				Return (IQBP)
			}
		}

		Case (Package () { 3, 7, 11, 15 }) {
			If (PICM) {
				Return (IQCA)
			} Else {
				Return (IQCP)
			}
		}

		Case (Package () { 4, 8, 12, 16 }) {
			If (PICM) {
				Return (IQDA)
			} Else {
				Return (IQDP)
			}
		}

		Default {
			If (PICM) {
				Return (IQDA)
			} Else {
				Return (IQDP)
			}
		}
	}
}

Device (RP01)
{
	Name (_ADR, 0x001C0000)

	OperationRegion (RPCS, PCI_Config, 0x4c, 4)
	Field (RPCS, AnyAcc, NoLock, Preserve)
	{
		, 24,
		RPPN, 8,	/* Root Port Number */
	}

	Method (_PRT)
	{
		Return (IRQM (RPPN))
	}
}

Device (RP02)
{
	Name (_ADR, 0x001C0001)

	OperationRegion (RPCS, PCI_Config, 0x4c, 4)
	Field (RPCS, AnyAcc, NoLock, Preserve)
	{
		, 24,
		RPPN, 8,	/* Root Port Number */
	}

	Method (_PRT)
	{
		Return (IRQM (RPPN))
	}
}

Device (RP03)
{
	Name (_ADR, 0x001C0002)

	OperationRegion (RPCS, PCI_Config, 0x4c, 4)
	Field (RPCS, AnyAcc, NoLock, Preserve)
	{
		, 24,
		RPPN, 8,	/* Root Port Number */
	}

	Method (_PRT)
	{
		Return (IRQM (RPPN))
	}
}

Device (RP04)
{
	Name (_ADR, 0x001C0003)

	OperationRegion (RPCS, PCI_Config, 0x4c, 4)
	Field (RPCS, AnyAcc, NoLock, Preserve)
	{
		, 24,
		RPPN, 8,	/* Root Port Number */
	}

	Method (_PRT)
	{
		Return (IRQM (RPPN))
	}
}

Device (RP05)
{
	Name (_ADR, 0x001C0004)

	OperationRegion (RPCS, PCI_Config, 0x4c, 4)
	Field (RPCS, AnyAcc, NoLock, Preserve)
	{
		, 24,
		RPPN, 8,	/* Root Port Number */
	}

	Method (_PRT)
	{
		Return (IRQM (RPPN))
	}
}

Device (RP06)
{
	Name (_ADR, 0x001C0005)

	OperationRegion (RPCS, PCI_Config, 0x4c, 4)
	Field (RPCS, AnyAcc, NoLock, Preserve)
	{
		, 24,
		RPPN, 8,	/* Root Port Number */
	}

	Method (_PRT)
	{
		Return (IRQM (RPPN))
	}
}

Device (RP07)
{
	Name (_ADR, 0x001C0006)

	OperationRegion (RPCS, PCI_Config, 0x4c, 4)
	Field (RPCS, AnyAcc, NoLock, Preserve)
	{
		, 24,
		RPPN, 8,	/* Root Port Number */
	}

	Method (_PRT)
	{
		Return (IRQM (RPPN))
	}
}

Device (RP08)
{
	Name (_ADR, 0x001C0007)

	OperationRegion (RPCS, PCI_Config, 0x4c, 4)
	Field (RPCS, AnyAcc, NoLock, Preserve)
	{
		, 24,
		RPPN, 8,	/* Root Port Number */
	}

	Method (_PRT)
	{
		Return (IRQM (RPPN))
	}
}

Device (RP09)
{
	Name (_ADR, 0x001D0000)

	OperationRegion (RPCS, PCI_Config, 0x4c, 4)
	Field (RPCS, AnyAcc, NoLock, Preserve)
	{
		, 24,
		RPPN, 8,	/* Root Port Number */
	}

	Method (_PRT)
	{
		Return (IRQM (RPPN))
	}
}

Device (RP10)
{
	Name (_ADR, 0x001D0001)

	OperationRegion (RPCS, PCI_Config, 0x4c, 4)
	Field (RPCS, AnyAcc, NoLock, Preserve)
	{
		, 24,
		RPPN, 8,	/* Root Port Number */
	}

	Method (_PRT)
	{
		Return (IRQM (RPPN))
	}
}

Device (RP11)
{
	Name (_ADR, 0x001D0002)

	OperationRegion (RPCS, PCI_Config, 0x4c, 4)
	Field (RPCS, AnyAcc, NoLock, Preserve)
	{
		, 24,
		RPPN, 8,	/* Root Port Number */
	}

	Method (_PRT)
	{
		Return (IRQM (RPPN))
	}
}

Device (RP12)
{
	Name (_ADR, 0x001D0003)

	OperationRegion (RPCS, PCI_Config, 0x4c, 4)
	Field (RPCS, AnyAcc, NoLock, Preserve)
	{
		, 24,
		RPPN, 8,	/* Root Port Number */
	}

	Method (_PRT)
	{
		Return (IRQM (RPPN))
	}
}

Device (RP13)
{
	Name (_ADR, 0x001D0004)

	OperationRegion (RPCS, PCI_Config, 0x4c, 4)
	Field (RPCS, AnyAcc, NoLock, Preserve)
	{
		, 24,
		RPPN, 8,	/* Root Port Number */
	}

	Method (_PRT)
	{
		Return (IRQM (RPPN))
	}
}

Device (RP14)
{
	Name (_ADR, 0x001D0005)

	OperationRegion (RPCS, PCI_Config, 0x4c, 4)
	Field (RPCS, AnyAcc, NoLock, Preserve)
	{
		, 24,
		RPPN, 8,	/* Root Port Number */
	}

	Method (_PRT)
	{
		Return (IRQM (RPPN))
	}
}

Device (RP15)
{
	Name (_ADR, 0x001D0006)

	OperationRegion (RPCS, PCI_Config, 0x4c, 4)
	Field (RPCS, AnyAcc, NoLock, Preserve)
	{
		, 24,
		RPPN, 8,	/* Root Port Number */
	}

	Method (_PRT)
	{
		Return (IRQM (RPPN))
	}
}

Device (RP16)
{
	Name (_ADR, 0x001D0007)

	OperationRegion (RPCS, PCI_Config, 0x4c, 4)
	Field (RPCS, AnyAcc, NoLock, Preserve)
	{
		, 24,
		RPPN, 8,	/* Root Port Number */
	}

	Method (_PRT)
	{
		Return (IRQM (RPPN))
	}
}
