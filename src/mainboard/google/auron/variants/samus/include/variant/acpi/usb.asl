/* SPDX-License-Identifier: GPL-2.0-only */

Scope (\_SB.PCI0.XHCI.HUB7.PRT1)
{
	// USB-A Port 1 USB 2.0
	Name (_UPC, Package (0x04)
	{
		0xFF,	// Connectable
		Zero,	// USB Port
		Zero,	// Reserved
		Zero	// Reserved
	})

	// Visible
	Method (_PLD, 0, NotSerialized)
	{
		Return (GPLD (One))
	}
}
Scope (\_SB.PCI0.XHCI.HUB7.PRT2)
{
	// USB-A Port 2 USB 2.0
	Name (_UPC, Package (0x04)
	{
		0xFF,	// Connectable
		Zero,	// USB Port
		Zero,	// Reserved
		Zero	// Reserved
	})

	// Visible
	Method (_PLD, 0, NotSerialized)
	{
		Return (GPLD (One))
	}
}
Scope (\_SB.PCI0.XHCI.HUB7.PRT3)
{
	// USB-C USB 2.0 Port Left
	Name (_UPC, Package (0x04)
	{
		0xFF,	// Connectable
		Zero,	// USB Port
		Zero,	// Reserved
		Zero	// Reserved
	})

	// Visible
	Method (_PLD, 0, NotSerialized)
	{
		Return (GPLD (One))
	}
}
Scope (\_SB.PCI0.XHCI.HUB7.PRT4)
{
	// SD Card
	Name (_UPC, Package (0x04)
	{
		0xFF,	// Connectable
		0xFF,	// OEM Connector
		Zero,	// Reserved
		Zero	// Reserved
	})

	// Not Visible
	Method (_PLD, 0, NotSerialized)
	{
		Return (GPLD (Zero))
	}
}
Scope (\_SB.PCI0.XHCI.HUB7.PRT5)
{
	// USB-C USB 2.0 Port Right
	Name (_UPC, Package (0x04)
	{
		0xFF,	// Connectable
		Zero,	// USB Port
		Zero,	// Reserved
		Zero	// Reserved
	})

	// Visible
	Method (_PLD, 0, NotSerialized)
	{
		Return (GPLD (One))
	}
}
Scope (\_SB.PCI0.XHCI.HUB7.PRT7)
{
	// Webcam
	Name (_UPC, Package (0x04)
	{
		0xFF,	// Connectable
		0xFF,	// OEM Connector
		Zero,	// Reserved
		Zero	// Reserved
	})

	// Not Visible
	Method (_PLD, 0, NotSerialized)
	{
		Return (GPLD (Zero))
	}
}
Scope (\_SB.PCI0.XHCI.HUB7.PRT8)
{
	// Bluetooth
	Name (_UPC, Package (0x04)
	{
		0xFF,	// Connectable
		0xFF,	// OEM Connector
		Zero,	// Reserved
		Zero	// Reserved
	})

	// Not Visible
	Method (_PLD, 0, NotSerialized)
	{
		Return (GPLD (Zero))
	}
}
Scope (\_SB.PCI0.XHCI.HUB7.SSP3)
{
	// USB-C USB 3.0 Port Left
	Name (_UPC, Package (0x04)
	{
		0xFF,	// Connectable
		0x03,	// USB 3.0 Port
		Zero,	// Reserved
		Zero	// Reserved
	})
}
Scope (\_SB.PCI0.XHCI.HUB7.SSP4)
{
	// USB-C USB 3.0 Port Right
	Name (_UPC, Package (0x04)
	{
		0xFF,	// Connectable
		0x03,	// USB 3.0 Port
		Zero,	// Reserved
		Zero	// Reserved
	})
}
Scope (\_SB.PCI0.XHCI.HUB7.SSP5)
{
	// USB-A Port 1 USB 3.0
	Name (_UPC, Package (0x04)
	{
		0xFF,	// Connectable
		0x03,	// USB 3.0 Port
		Zero,	// Reserved
		Zero	// Reserved
	})
}
Scope (\_SB.PCI0.XHCI.HUB7.SSP6)
{
	// USB-A Port 2 USB 3.0
	Name (_UPC, Package (0x04)
	{
		0xFF,	// Connectable
		0x03,	// USB 3.0 Port
		Zero,	// Reserved
		Zero	// Reserved
	})
}
