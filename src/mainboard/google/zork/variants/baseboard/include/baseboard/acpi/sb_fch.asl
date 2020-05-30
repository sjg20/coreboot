/* SPDX-License-Identifier: GPL-2.0-or-later */

#include <soc/gpio.h>
#include <soc/iomap.h>

Device (AAHB)
{
	Name (_HID, "AAHB0000")
	Name (_UID, 0x0)
	Name (_CRS, ResourceTemplate()
	{
		Memory32Fixed (ReadWrite, ALINK_AHB_ADDRESS, 0x2000)
	})

	Method (_STA, 0x0, NotSerialized)
	{
		Return (0x0F)
	}
}

Device (GPIO)
{
	Name (_HID, GPIO_DEVICE_NAME)
	Name (_CID, GPIO_DEVICE_NAME)
	Name (_UID, 0)
	Name (_DDN, GPIO_DEVICE_DESC)

	Method(_CRS ,0) {
		local0=ResourceTemplate(){
			Interrupt (
				ResourceConsumer,
				Level,
				ActiveLow,
				Exclusive, , , IRQR)
			{ 0 }
			Memory32Fixed (ReadWrite, 0xFED81500, 0x300)
		}
		CreateDWordField(local0, IRQR._INT, IRQN)
		If(PMOD) {
			IRQN=IGPI
		} Else {
			IRQN=PGPI
		}
		If (IRQN == 0x1f) {
			Return(ResourceTemplate(){
				Memory32Fixed (ReadWrite, 0xFED81500, 0x300)
			})
		} Else {
			Return(local0)
		}
	}

	Method (_STA, 0x0, NotSerialized)
	{
		Return (0x0F)
	}
}

Device (MMC0)
{
	Name (_HID, "AMDI0040")
	Name (_UID, 0x0)
	Method(_CRS ,0) {
		local0=ResourceTemplate(){
			Interrupt (
				ResourceConsumer,
				Level,
				ActiveLow,
				Exclusive, , , IRQR)
			{ 0 }
			Memory32Fixed (ReadWrite, APU_EMMC_BASE, 0x1000)
		}
		CreateDWordField(local0, IRQR._INT, IRQN)
		If(PMOD) {
			IRQN=IMMC
		} Else {
			IRQN=PMMC
		}
		If (IRQN == 0x1f) {
			Return(ResourceTemplate(){
				Memory32Fixed (ReadWrite, APU_EMMC_BASE, 0x1000)
			})
		} Else {
			Return(local0)
		}
	}

	Method (_STA, 0x0, NotSerialized)
	{
		Return (0x0F)
	}
}

Device (FUR0)
{
	Name (_HID, "AMD0020")
	Name (_UID, 0x0)
	Method(_CRS ,0) {
		local0=ResourceTemplate(){
			Interrupt (
				ResourceConsumer,
				Edge,
				ActiveHigh,
				Exclusive, , , IRQR)
			{ 0 }
			Memory32Fixed (ReadWrite, APU_UART0_BASE, 0x1000)
			Memory32Fixed (ReadWrite, APU_DMAC0_BASE, 0x1000)
		}
		CreateDWordField(local0, IRQR._INT, IRQN)
		If(PMOD) {
			IRQN=IUA0
		} Else {
			IRQN=PUA0
		}
		If (IRQN == 0x1f) {
			Return(ResourceTemplate(){
				Memory32Fixed (ReadWrite, APU_UART0_BASE, 0x1000)
				Memory32Fixed (ReadWrite, APU_DMAC0_BASE, 0x1000)
			})
		} Else {
			Return(local0)
		}
	}

	Method (_STA, 0x0, NotSerialized)
	{
		Return (0x0F)
	}
}

Device (FUR1) {
	Name (_HID, "AMD0020")
	Name (_UID, 0x1)
	Method(_CRS ,0) {
		local0=ResourceTemplate(){
			Interrupt (
				ResourceConsumer,
				Edge,
				ActiveHigh,
				Exclusive, , , IRQR)
			{ 0 }
			Memory32Fixed (ReadWrite, APU_UART1_BASE, 0x1000)
			Memory32Fixed (ReadWrite, APU_DMAC1_BASE, 0x1000)
		}
		CreateDWordField(local0, IRQR._INT, IRQN)
		If(PMOD) {
			IRQN=IUA1
		} Else {
			IRQN=PUA1
		}
		If (IRQN == 0x1f) {
			Return(ResourceTemplate(){
				Memory32Fixed (ReadWrite, APU_UART1_BASE, 0x1000)
				Memory32Fixed (ReadWrite, APU_DMAC1_BASE, 0x1000)
			})
		} Else {
			Return(local0)
		}
	}

	Method (_STA, 0x0, NotSerialized)
	{
		Return (0x0F)
	}
}

Device (I2C2) {
	Name (_HID, "AMD0010")
	Name (_UID, 0x2)
	Method(_CRS ,0) {
		local0=ResourceTemplate(){
			Interrupt (
				ResourceConsumer,
				Edge,
				ActiveHigh,
				Exclusive, , , IRQR)
			{ 0 }
			Memory32Fixed (ReadWrite, APU_I2C2_BASE, 0x1000)
		}
		CreateDWordField(local0, IRQR._INT, IRQN)
		If(PMOD) {
			IRQN=II22
		} Else {
			IRQN=PI22
		}
		If (IRQN == 0x1f) {
			Return(ResourceTemplate(){
				Memory32Fixed (ReadWrite, APU_I2C2_BASE, 0x1000)
			})
		} Else {
			Return(local0)
		}
	}

	Method (_STA, 0x0, NotSerialized)
	{
		Return (0x0F)
	}
}

Device (I2C3)
{
	Name (_HID, "AMD0010")
	Name (_UID, 0x3)
	Method(_CRS ,0) {
		local0=ResourceTemplate(){
			Interrupt (
				ResourceConsumer,
				Edge,
				ActiveHigh,
				Exclusive, , , IRQR)
			{ 0 }
			Memory32Fixed (ReadWrite, APU_I2C3_BASE, 0x1000)
		}
		CreateDWordField(local0, IRQR._INT, IRQN)
		If(PMOD) {
			IRQN=II23
		} Else {
			IRQN=PI23
		}
		If (IRQN == 0x1f) {
			Return(ResourceTemplate(){
				Memory32Fixed (ReadWrite, APU_I2C3_BASE, 0x1000)
			})
		} Else {
			Return(local0)
		}
	}
	Method (_STA, 0x0, NotSerialized)
	{
		Return (0x0F)
	}
}

Device (MISC)
{
	Name (_HID, "AMD0040")
	Name (_UID, 0x3)
	Name (_CRS, ResourceTemplate() {
		Memory32Fixed(ReadWrite, ACPIMMIO_MISC_BASE, 0x100)
	})
	Method (_STA, 0x0, NotSerialized)
	{
		Return (0x0F)
	}
}
