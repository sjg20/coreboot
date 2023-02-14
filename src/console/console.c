/* SPDX-License-Identifier: GPL-2.0-only */

#include <console/cbmem_console.h>
#include <console/console.h>
#include <console/flash.h>
#include <console/i2c_smbus.h>
#include <console/ne2k.h>
#include <console/qemu_debugcon.h>
#include <console/simnow.h>
#include <console/spi.h>
#include <console/spkmodem.h>
#include <console/streams.h>
#include <console/system76_ec.h>
#include <console/uart.h>
#include <console/usb.h>
#include <ctype.h>
#include <types.h>

#define MAX_LINE_LENGTH_BYTES (64)
#define DEFAULT_LINE_LENGTH_BYTES (16)
typedef unsigned int uint;

int print_buffer(unsigned long addr, const void *data, unsigned int width,
		 unsigned int count, unsigned int linelen)
{
	/* linebuf as a union causes proper alignment */
	union linebuf {
		uint32_t ui[MAX_LINE_LENGTH_BYTES/sizeof(uint32_t) + 1];
		uint16_t us[MAX_LINE_LENGTH_BYTES/sizeof(uint16_t) + 1];
		uint8_t  uc[MAX_LINE_LENGTH_BYTES/sizeof(uint8_t) + 1];
	} lb;
	int i;
	uint32_t x;

	if (linelen*width > MAX_LINE_LENGTH_BYTES)
		linelen = MAX_LINE_LENGTH_BYTES / width;
	if (linelen < 1)
		linelen = DEFAULT_LINE_LENGTH_BYTES / width;

	while (count) {
		uint thislinelen = linelen;
		printk(BIOS_INFO, "%08lx:", addr);

		/* check for overflow condition */
		if (count < thislinelen)
			thislinelen = count;

		/* Copy from memory into linebuf and print hex values */
		for (i = 0; i < thislinelen; i++) {
			if (width == 4)
				x = lb.ui[i] = *(volatile uint32_t *)data;
			else if (width == 2)
				x = lb.us[i] = *(volatile uint16_t *)data;
			else
				x = lb.uc[i] = *(volatile uint8_t *)data;
			printk(BIOS_INFO, " %0*x", width * 2, x);
			data += width;
		}

		while (thislinelen < linelen) {
			/* fill line with whitespace for nice ASCII print */
			for (i=0; i<width*2+1; i++)
				printk(BIOS_INFO, " ");
			linelen--;
		}

		/* Print data in ASCII characters */
		for (i = 0; i < thislinelen * width; i++) {
			if (!isprint(lb.uc[i]) || lb.uc[i] >= 0x80)
				lb.uc[i] = '.';
		}
		lb.uc[i] = '\0';
		printk(BIOS_INFO, "    %s\n", lb.uc);

		/* update references */
		addr += thislinelen * width;
		count -= thislinelen;

	}

	return 0;
}

/* Note: when adding a new console, make sure you update the definition of
   HAS_ONLY_FAST_CONSOLES in <console.h>! */
void console_hw_init(void)
{
	__cbmemc_init();
	__spkmodem_init();
	__qemu_debugcon_init();

	__uart_init();
	__ne2k_init();
	__usbdebug_init();
	__spiconsole_init();
	__flashconsole_init();
	__system76_ec_init();
	__i2c_smbus_console_init();
	__simnow_console_init();
}

void console_interactive_tx_byte(unsigned char byte, void *data_unused)
{
	if (byte == '\n') {
		/* Some consoles want newline conversion to keep terminals happy. */
		__uart_tx_byte('\r');
		__usb_tx_byte('\r');
		__i2c_smbus_console_tx_byte('\r');
	}

	__spkmodem_tx_byte(byte);
	__qemu_debugcon_tx_byte(byte);
	__uart_tx_byte(byte);
	__ne2k_tx_byte(byte);
	__usb_tx_byte(byte);
	__spiconsole_tx_byte(byte);
	__system76_ec_tx_byte(byte);
	__i2c_smbus_console_tx_byte(byte);
	__simnow_console_tx_byte(byte);
}

void console_stored_tx_byte(unsigned char byte, void *data_unused)
{
	__flashconsole_tx_byte(byte);
	__cbmemc_tx_byte(byte);
}

void console_tx_byte(unsigned char byte)
{
	console_interactive_tx_byte(byte, NULL);
	console_stored_tx_byte(byte, NULL);
}

void console_tx_flush(void)
{
	__uart_tx_flush();
	__ne2k_tx_flush();
	__usb_tx_flush();
	__flashconsole_tx_flush();
	__system76_ec_tx_flush();
}

void console_write_line(uint8_t *buffer, size_t number_of_bytes)
{
	/* Finish displaying all of the console data if requested */
	if (number_of_bytes == 0) {
		console_tx_flush();
		return;
	}

	/* Output the console data */
	while (number_of_bytes--)
		console_tx_byte(*buffer++);
}

#if CONFIG(GDB_STUB) && (ENV_ROMSTAGE || ENV_RAMSTAGE)
void gdb_hw_init(void)
{
	__gdb_hw_init();
}

void gdb_tx_byte(unsigned char byte)
{
	__gdb_tx_byte(byte);
}

void gdb_tx_flush(void)
{
	__gdb_tx_flush();
}

unsigned char gdb_rx_byte(void)
{
	return __gdb_rx_byte();
}
#endif
