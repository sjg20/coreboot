/* SPDX-License-Identifier: GPL-2.0-only */

/* Pre-RAM driver for SMSC LPC47N227 Super I/O chip. */

#include <arch/io.h>
#include <assert.h>
#include <device/pnp_ops.h>

#include "lpc47n227.h"

void pnp_enter_conf_state(pnp_devfn_t dev)
{
	u16 port = dev >> 8;
	outb(0x55, port);
}

void pnp_exit_conf_state(pnp_devfn_t dev)
{
	u16 port = dev >> 8;
	outb(0xaa, port);
}

/**
 * Program the base I/O port for the specified logical device.
 *
 * @param dev High 8 bits = Super I/O port, low 8 bits = logical device number.
 * @param iobase Base I/O port for the logical device.
 */
static void lpc47n227_pnp_set_iobase(pnp_devfn_t dev, u16 iobase)
{
	/* LPC47N227 requires base ports to be a multiple of 4. */
	/* it's not very useful to do an ASSERT here: if it trips,
	 * there's no console to report it.
	ASSERT(!(iobase & 0x3));
	*/

	switch (dev & 0xFF) {
	case LPC47N227_PP:
		pnp_write_config(dev, 0x23, (iobase >> 2) & 0xff);
		break;
	case LPC47N227_SP1:
		pnp_write_config(dev, 0x24, (iobase >> 2) & 0xff);
		break;
	case LPC47N227_SP2:
		pnp_write_config(dev, 0x25, (iobase >> 2) & 0xff);
		break;
	default:
		break;
	}
}

/**
 * Enable or disable the specified logical device.
 *
 * Technically, a full disable requires setting the device's base I/O port
 * below 0x100. We don't do that here, because we don't have access to a data
 * structure that specifies what the 'real' base port is (when asked to enable
 * the device). Also the function is used only to disable the device while its
 * true base port is programmed (see lpc47n227_enable_serial() below).
 *
 * @param dev High 8 bits = Super I/O port, low 8 bits = logical device number.
 * @param enable 0 to disable, anything else to enable.
 */
static void lpc47n227_pnp_set_enable(pnp_devfn_t dev, int enable)
{
	u8 power_register = 0, power_mask = 0, current_power, new_power;

	switch (dev & 0xFF) {
	case LPC47N227_PP:
		power_register = 0x01;
		power_mask = 0x04;
		break;
	case LPC47N227_SP1:
		power_register = 0x02;
		power_mask = 0x08;
		break;
	case LPC47N227_SP2:
		power_register = 0x02;
		power_mask = 0x80;
		break;
	default:
		return;
	}

	current_power = pnp_read_config(dev, power_register);
	new_power = current_power & ~power_mask; /* Disable by default. */
	if (enable)
		new_power |= power_mask; /* Enable. */
	pnp_write_config(dev, power_register, new_power);
}

/**
 * Configure the base I/O port of the specified serial device and enable the
 * serial device.
 *
 * @param dev High 8 bits = Super I/O port, low 8 bits = logical device number.
 * @param iobase Processor I/O port address to assign to this serial device.
 */
void lpc47n227_enable_serial(pnp_devfn_t dev, u16 iobase)
{
	/*
	 * NOTE: Cannot use pnp_set_XXX() here because they assume chip
	 * support for logical devices, which the LPC47N227 doesn't have.
	 */
	pnp_enter_conf_state(dev);
	lpc47n227_pnp_set_enable(dev, 0);
	lpc47n227_pnp_set_iobase(dev, iobase);
	lpc47n227_pnp_set_enable(dev, 1);
	pnp_exit_conf_state(dev);
}
