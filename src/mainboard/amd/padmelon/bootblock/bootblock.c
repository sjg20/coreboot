/*
 * This file is part of the coreboot project.
 *
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

#include <bootblock_common.h>
#include <soc/southbridge.h>
#include <amdblocks/lpc.h>
#include <device/pci_ops.h>
#include <soc/pci_devs.h>
#include <drivers/uart/uart8250reg.h>
#include <arch/io.h>
#include "../gpio.h"

/* Enable IO access to port, then enable UART HW control pins */
static void enable_serial(unsigned int base_port, unsigned int io_enable)
{
	u32 temp;
	u8 reg;
	temp = pci_read_config32(SOC_LPC_DEV, LPC_IO_PORT_DECODE_ENABLE);
	temp |= io_enable;
	pci_write_config32(SOC_LPC_DEV, LPC_IO_PORT_DECODE_ENABLE, temp);

	/*
	 * Remove this section if HW handshake is not needed. This is needed
	 * only for those who don't have a modified serial cable (connecting
	 * DCD to DTR and DSR, plus connecting RTS to CTS). When you buy cables
	 * on any store, they don't have these modification.
	 */
	reg = inb(base_port + UART8250_MCR);
	reg |= UART8250_MCR_DTR | UART8250_MCR_RTS;
	outb(reg, base_port + UART8250_MCR);
}

void bootblock_mainboard_early_init(void)
{
	sb_clk_output_48Mhz(2);
	/*
	 * UARTs enabled by default at reset, just need RTS, CTS
	 * and access to the IO address.
	 */
	enable_serial(0x03f8, DECODE_ENABLE_SERIAL_PORT0);
	enable_serial(0x02f8, DECODE_ENABLE_SERIAL_PORT1);
}

void bootblock_mainboard_init(void)
{
	size_t num_gpios;
	const struct soc_amd_gpio *gpios;

	gpios = early_gpio_table(&num_gpios);
	program_gpios(gpios, num_gpios);
}
