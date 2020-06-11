/* SPDX-License-Identifier: GPL-2.0-only */

#include <stdint.h>
#include <amdblocks/acpimmio.h>
#include <soc/southbridge.h>
#include <delay.h>

#define FCH_AOAC_UART_FOR_CONSOLE \
		(CONFIG_UART_FOR_CONSOLE == 0 ? FCH_AOAC_DEV_UART0 \
		: CONFIG_UART_FOR_CONSOLE == 1 ? FCH_AOAC_DEV_UART1 \
		: CONFIG_UART_FOR_CONSOLE == 2 ? FCH_AOAC_DEV_UART2 \
		: CONFIG_UART_FOR_CONSOLE == 3 ? FCH_AOAC_DEV_UART3 \
		: -1)
#if FCH_AOAC_UART_FOR_CONSOLE == -1
# error Unsupported UART_FOR_CONSOLE chosen
#endif

/*
 * Table of devices that need their AOAC registers enabled and waited
 * upon (usually about .55 milliseconds). Instead of individual delays
 * waiting for each device to become available, a single delay will be
 * executed.  The console UART is handled separately from this table.
 */
const static int aoac_devs[] = {
	FCH_AOAC_DEV_AMBA,
	FCH_AOAC_DEV_I2C2,
	FCH_AOAC_DEV_I2C3,
	FCH_AOAC_DEV_I2C4,
	FCH_AOAC_DEV_ESPI,
};

void power_on_aoac_device(int dev)
{
	uint8_t byte;

	/* Power on the UART and AMBA devices */
	byte = aoac_read8(AOAC_DEV_D3_CTL(dev));
	byte |= FCH_AOAC_PWR_ON_DEV;
	aoac_write8(AOAC_DEV_D3_CTL(dev), byte);
}

void power_off_aoac_device(int dev)
{
	uint8_t byte;

	/* Power on the UART and AMBA devices */
	byte = aoac_read8(AOAC_DEV_D3_CTL(dev));
	byte &= ~FCH_AOAC_PWR_ON_DEV;
	aoac_write8(AOAC_DEV_D3_CTL(dev), byte);
}

bool is_aoac_device_enabled(int dev)
{
	uint8_t byte;

	byte = aoac_read8(AOAC_DEV_D3_STATE(dev));
	byte &= (FCH_AOAC_PWR_RST_STATE | FCH_AOAC_RST_CLK_OK_STATE);
	if (byte == (FCH_AOAC_PWR_RST_STATE | FCH_AOAC_RST_CLK_OK_STATE))
		return true;
	else
		return false;
}

static void enable_aoac_console_uart(void)
{
	if (!CONFIG(PICASSO_UART))
		return;

	power_on_aoac_device(FCH_AOAC_UART_FOR_CONSOLE);
}

static bool is_aoac_console_uart_enabled(void)
{
	if (!CONFIG(PICASSO_UART))
		return true;

	return is_aoac_device_enabled(FCH_AOAC_UART_FOR_CONSOLE);
}

void enable_aoac_devices(void)
{
	bool status;
	int i;

	for (i = 0; i < ARRAY_SIZE(aoac_devs); i++)
		power_on_aoac_device(aoac_devs[i]);
	enable_aoac_console_uart();

	/* Wait for AOAC devices to indicate power and clock OK */
	do {
		udelay(100);
		status = true;
		for (i = 0; i < ARRAY_SIZE(aoac_devs); i++)
			status &= is_aoac_device_enabled(aoac_devs[i]);
		status &= is_aoac_console_uart_enabled();
	} while (!status);
}
