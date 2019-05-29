/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2010-2017 Advanced Micro Devices, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <stdint.h>
#include <device/device.h>
#include <device/pci_ops.h>
#include <device/pci_def.h>
#include <amdblocks/lpc.h>
#include <soc/iomap.h>
#include <soc/southbridge.h>

/* The LPC-ISA bridge is always at D14F3 */
#if !defined(__SIMPLE_DEVICE__)
#include <device/device.h>
#define _LPCB_DEV pcidev_on_root(0x14, 0x3)
#else
#define _LPCB_DEV PCI_DEV(0, 0x14, 0x3)
#endif

/*
 * Structure to simplify code obtaining the total of used wide IO
 * registers and the size assigned to each.
 */
static const struct wide_io_ioport_and_bits {
	uint32_t enable;
	uint16_t port;
	uint8_t alt;
} wio_io_en[] = {
	{
		.enable = LPC_WIDEIO0_ENABLE,
		.port = LPC_WIDEIO_GENERIC_PORT,
		.alt = LPC_ALT_WIDEIO0_ENABLE
	},
	{
		.enable = LPC_WIDEIO1_ENABLE,
		.port = LPC_WIDEIO1_GENERIC_PORT,
		.alt = LPC_ALT_WIDEIO1_ENABLE
	},
	{
		.enable = LPC_WIDEIO2_ENABLE,
		.port = LPC_WIDEIO2_GENERIC_PORT,
		.alt = LPC_ALT_WIDEIO2_ENABLE
	}
};

/**
 * @brief Find the size of a particular wide IO
 *
 * @param index = index of desired wide IO
 *
 * @return size of desired wide IO
 */
uint16_t lpc_wideio_size(int index)
{
	uint32_t enable_register;
	uint16_t size = 0;
	uint8_t alternate_register;

	if (index >= ARRAY_SIZE(wio_io_en))
		return size;
	enable_register = pci_read_config32(_LPCB_DEV,
				LPC_IO_OR_MEM_DECODE_ENABLE);
	alternate_register = pci_read_config8(_LPCB_DEV,
				LPC_ALT_WIDEIO_RANGE_ENABLE);
	if (enable_register & wio_io_en[index].enable)
		size = (alternate_register & wio_io_en[index].alt) ?
				16 : 512;
	return size;
}

/**
 * @brief Identify if any LPC wide IO is covering the IO range
 *
 * @param start = start of IO range
 * @param size = size of IO range
 *
 * @return Index of wide IO covering the range or error
 */
int lpc_find_wideio_range(uint16_t start, uint16_t size)
{
	int i, index = WIDEIO_RANGE_ERROR;
	uint16_t end, current_size, start_wideio, end_wideio;

	end = start + size;
	for (i = 0; i < ARRAY_SIZE(wio_io_en); i++) {
		current_size = lpc_wideio_size(i);
		if (current_size == 0)
			continue;
		start_wideio = pci_read_config16(_LPCB_DEV,
						 wio_io_en[i].port);
		end_wideio = start_wideio + current_size;
		if ((start >= start_wideio) && (end <= end_wideio)) {
			index = i;
			break;
		}
	}
	return index;
}

/**
 * @brief Program a LPC wide IO to support an IO range
 *
 * @param start = start of range to be routed through wide IO
 * @param size = size of range to be routed through wide IO
 *
 * @return Index of wide IO register used or error
 */
int lpc_set_wideio_range(uint16_t start, uint16_t size)
{
	int i, index = WIDEIO_RANGE_ERROR;
	uint32_t enable_register;
	uint8_t alternate_register;

	enable_register = pci_read_config32(_LPCB_DEV,
					   LPC_IO_OR_MEM_DECODE_ENABLE);
	alternate_register = pci_read_config8(_LPCB_DEV,
					      LPC_ALT_WIDEIO_RANGE_ENABLE);
	for (i = 0; i < ARRAY_SIZE(wio_io_en); i++) {
		if (enable_register & wio_io_en[i].enable)
			continue;
		index = i;
		pci_write_config16(_LPCB_DEV, wio_io_en[i].port, start);
		enable_register |= wio_io_en[i].enable;
		pci_write_config32(_LPCB_DEV, LPC_IO_OR_MEM_DECODE_ENABLE,
				   enable_register);
		if (size <= 16)
			alternate_register |= wio_io_en[i].alt;
		else
			alternate_register &= ~wio_io_en[i].alt;
		pci_write_config8(_LPCB_DEV,
				  LPC_ALT_WIDEIO_RANGE_ENABLE,
				  alternate_register);
		break;
	}
	return index;
}

void lpc_enable_port80(void)
{
	u8 byte;

	byte = pci_read_config8(_LPCB_DEV, LPC_IO_OR_MEM_DEC_EN_HIGH);
	byte |= DECODE_IO_PORT_ENABLE4_H;
	pci_write_config8(_LPCB_DEV, LPC_IO_OR_MEM_DEC_EN_HIGH, byte);
}

void lpc_enable_pci_port80(void)
{
	u8 byte;

	byte = pci_read_config8(_LPCB_DEV, LPC_IO_OR_MEM_DEC_EN_HIGH);
	byte &= ~DECODE_IO_PORT_ENABLE4_H; /* disable lpc port 80 */
	pci_write_config8(_LPCB_DEV, LPC_IO_OR_MEM_DEC_EN_HIGH, byte);
}

void lpc_enable_decode(uint32_t decodes)
{
	pci_write_config32(_LPCB_DEV, LPC_IO_PORT_DECODE_ENABLE, decodes);
}

uintptr_t lpc_spibase(void)
{
	u32 base, enables;

	/* Make sure the base address is predictable */
	base = pci_read_config32(_LPCB_DEV, SPIROM_BASE_ADDRESS_REGISTER);
	enables = base & SPI_PRESERVE_BITS;
	base &= ~(SPI_PRESERVE_BITS | SPI_BASE_RESERVED);

	if (!base) {
		base = SPI_BASE_ADDRESS;
		pci_write_config32(_LPCB_DEV, SPIROM_BASE_ADDRESS_REGISTER,
					base | enables | SPI_ROM_ENABLE);
		/* PCI_COMMAND_MEMORY is read-only and enabled. */
	}
	return base;
}

/*
 * Enable FCH to decode TPM associated Memory and IO regions
 *
 * Enable decoding of TPM cycles defined in TPM 1.2 spec
 * Enable decoding of legacy TPM addresses: IO addresses 0x7f-
 * 0x7e and 0xef-0xee.
 * This function should be called if TPM is connected in any way to the FCH and
 * conforms to the regions decoded.
 * Absent any other routing configuration the TPM cycles will be claimed by the
 * LPC bus
 */
void lpc_tpm_decode(void)
{
	u32 value;

	value = pci_read_config32(_LPCB_DEV, LPC_TRUSTED_PLATFORM_MODULE);
	value |= TPM_12_EN | TPM_LEGACY_EN;
	pci_write_config32(_LPCB_DEV, LPC_TRUSTED_PLATFORM_MODULE, value);
}

/*
 * Enable FCH to decode TPM associated Memory and IO regions to SPI
 *
 * This should be used if TPM is connected to SPI bus.
 * Assumes SPI address space is already configured via a call to lpc_spibase().
 */
void lpc_tpm_decode_spi(void)
{
	/* Enable TPM decoding to FCH */
	lpc_tpm_decode();

	/* Route TPM accesses to SPI */
	u32 spibase = pci_read_config32(_LPCB_DEV,
					SPIROM_BASE_ADDRESS_REGISTER);
	pci_write_config32(_LPCB_DEV, SPIROM_BASE_ADDRESS_REGISTER, spibase
					| ROUTE_TPM_2_SPI);
}

/*
 * Enable 4MB (LPC) ROM access at 0xFFC00000 - 0xFFFFFFFF.
 *
 * Hardware should enable LPC ROM by pin straps. This function does not
 * handle the theoretically possible PCI ROM, FWH, or SPI ROM configurations.
 *
 * The southbridge power-on default is to map 512K ROM space.
 *
 */
void lpc_enable_rom(void)
{
	u8 reg8;

	/*
	 * Decode variable LPC ROM address ranges 1 and 2.
	 * Bits 3-4 are not defined in any publicly available datasheet
	 */
	reg8 = pci_read_config8(_LPCB_DEV, LPC_IO_OR_MEM_DECODE_ENABLE);
	reg8 |= (1 << 3) | (1 << 4);
	pci_write_config8(_LPCB_DEV, LPC_IO_OR_MEM_DECODE_ENABLE, reg8);

	/*
	 * LPC ROM address range 1:
	 * Enable LPC ROM range mirroring start at 0x000e(0000).
	 */
	pci_write_config16(_LPCB_DEV, ROM_ADDRESS_RANGE1_START, 0x000e);

	/* Enable LPC ROM range mirroring end at 0x000f(ffff). */
	pci_write_config16(_LPCB_DEV, ROM_ADDRESS_RANGE1_END, 0x000f);

	/*
	 * LPC ROM address range 2:
	 *
	 * Enable LPC ROM range start at:
	 * 0xfff8(0000): 512KB
	 * 0xfff0(0000): 1MB
	 * 0xffe0(0000): 2MB
	 * 0xffc0(0000): 4MB
	 */
	pci_write_config16(_LPCB_DEV, ROM_ADDRESS_RANGE2_START, 0x10000
					- (CONFIG_COREBOOT_ROMSIZE_KB >> 6));

	/* Enable LPC ROM range end at 0xffff(ffff). */
	pci_write_config16(_LPCB_DEV, ROM_ADDRESS_RANGE2_END, 0xffff);
}

void lpc_enable_spi_prefetch(void)
{
	uint32_t dword;

	dword = pci_read_config32(_LPCB_DEV, LPC_ROM_DMA_EC_HOST_CONTROL);
	dword |= SPI_FROM_HOST_PREFETCH_EN | SPI_FROM_USB_PREFETCH_EN;
	pci_write_config32(_LPCB_DEV, LPC_ROM_DMA_EC_HOST_CONTROL, dword);
}

uintptr_t lpc_get_spibase(void)
{
	u32 base;

	base = pci_read_config32(_LPCB_DEV, SPIROM_BASE_ADDRESS_REGISTER);
	base = ALIGN_DOWN(base, SPI_BASE_ALIGNMENT);
	return (uintptr_t)base;
}

void lpc_set_spibase(u32 base, u32 enable)
{
	u32 reg32;

	/* only two types of CS# enables are allowed */
	enable &= SPI_ROM_ENABLE | SPI_ROM_ALT_ENABLE;

	reg32 = pci_read_config32(_LPCB_DEV, SPIROM_BASE_ADDRESS_REGISTER);

	reg32 &= SPI_BASE_ALIGNMENT - 1; /* preserve only reserved, enables */
	reg32 &= ~(SPI_ROM_ENABLE | SPI_ROM_ALT_ENABLE);
	reg32 |= enable;
	reg32 |= ALIGN_DOWN(base, SPI_BASE_ALIGNMENT);

	pci_write_config32(_LPCB_DEV, SPIROM_BASE_ADDRESS_REGISTER, reg32);
}
