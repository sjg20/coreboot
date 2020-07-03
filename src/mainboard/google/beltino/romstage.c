/* SPDX-License-Identifier: GPL-2.0-only */

#include <stdint.h>
#include <cpu/intel/haswell/haswell.h>
#include <northbridge/intel/haswell/haswell.h>
#include <northbridge/intel/haswell/raminit.h>
#include <southbridge/intel/lynxpoint/lp_gpio.h>
#include <southbridge/intel/lynxpoint/pch.h>

void mainboard_config_rcba(void)
{
	/*
	 *             GFX    INTA -> PIRQA (MSI)
	 * D28IP_P1IP  PCIE   INTA -> PIRQA
	 * D29IP_E1P   EHCI   INTA -> PIRQD
	 * D20IP_XHCI  XHCI   INTA -> PIRQC (MSI)
	 * D31IP_SIP   SATA   INTA -> PIRQF (MSI)
	 * D31IP_SMIP  SMBUS  INTB -> PIRQG
	 * D31IP_TTIP  THRT   INTC -> PIRQA
	 * D27IP_ZIP   HDA    INTA -> PIRQG (MSI)
	 */

	/* Device interrupt pin register (board specific) */
	RCBA32(D31IP) = (INTC << D31IP_TTIP) | (NOINT << D31IP_SIP2) |
			(INTB << D31IP_SMIP) | (INTA << D31IP_SIP);
	RCBA32(D29IP) = (INTA << D29IP_E1P);
	RCBA32(D28IP) = (INTA << D28IP_P1IP) | (INTC << D28IP_P3IP) |
			(INTB << D28IP_P4IP);
	RCBA32(D27IP) = (INTA << D27IP_ZIP);
	RCBA32(D26IP) = (INTA << D26IP_E2P);
	RCBA32(D22IP) = (NOINT << D22IP_MEI1IP);
	RCBA32(D20IP) = (INTA << D20IP_XHCI);

	/* Device interrupt route registers */
	RCBA16(D31IR) = DIR_ROUTE(PIRQG, PIRQC, PIRQB, PIRQA); /* LPC */
	RCBA16(D29IR) = DIR_ROUTE(PIRQD, PIRQD, PIRQD, PIRQD); /* EHCI */
	RCBA16(D28IR) = DIR_ROUTE(PIRQA, PIRQB, PIRQC, PIRQD); /* PCIE */
	RCBA16(D27IR) = DIR_ROUTE(PIRQG, PIRQG, PIRQG, PIRQG); /* HDA */
	RCBA16(D22IR) = DIR_ROUTE(PIRQA, PIRQA, PIRQA, PIRQA); /* ME */
	RCBA16(D21IR) = DIR_ROUTE(PIRQE, PIRQF, PIRQF, PIRQF); /* SIO */
	RCBA16(D20IR) = DIR_ROUTE(PIRQC, PIRQC, PIRQC, PIRQC); /* XHCI */
	RCBA16(D23IR) = DIR_ROUTE(PIRQH, PIRQH, PIRQH, PIRQH); /* SDIO */
}

void mainboard_fill_pei_data(struct pei_data *pei_data)
{
	pei_data->system_type = 5; /* ULT */
	pei_data->spd_addresses[0] = 0xa0;
	pei_data->spd_addresses[2] = 0xa4;
	pei_data->ec_present = 0;
	/*
	 * 0 = leave channel enabled
	 * 1 = disable dimm 0 on channel
	 * 2 = disable dimm 1 on channel
	 * 3 = disable dimm 0+1 on channel
	 */
	pei_data->dimm_channel0_disabled = 2;
	pei_data->dimm_channel1_disabled = 2;
	/* Enable 2x refresh mode */
	pei_data->ddr_refresh_2x = 1;
	pei_data->dq_pins_interleaved = 1;
	pei_data->max_ddr3_freq = 1600;
	pei_data->usb_xhci_on_resume = 1;

	struct usb2_port_setting usb2_ports[MAX_USB2_PORTS] = {
		/* Length, Enable, OCn#, Location */
		{ 0x0064, 1, 0,               /* P0: VP8 */
		  USB_PORT_MINI_PCIE },
		{ 0x0040, 1, 0,               /* P1: Port A, CN22 */
		  USB_PORT_INTERNAL },
		{ 0x0040, 1, 1,		      /* P2: Port B, CN23 */
		  USB_PORT_INTERNAL },
		{ 0x0040, 1, USB_OC_PIN_SKIP, /* P3: WLAN */
		  USB_PORT_INTERNAL },
		{ 0x0040, 1, 2,		      /* P4: Port C, CN25 */
		  USB_PORT_INTERNAL },
		{ 0x0040, 1, 2,		      /* P5: Port D, CN25 */
		  USB_PORT_INTERNAL },
		{ 0x0040, 1, USB_OC_PIN_SKIP, /* P6: Card Reader */
		  USB_PORT_INTERNAL },
		{ 0x0000, 0, 0,               /* P7: N/C */
		  USB_PORT_SKIP },
	};

	struct usb3_port_setting usb3_ports[MAX_USB3_PORTS] = {
		/* Enable, OCn# */
		{ 1, 0 }, /* P1; CN22 */
		{ 1, 1 }, /* P2; CN23  */
		{ 1, 2 }, /* P3; CN25 */
		{ 1, 2 }, /* P4; CN25 */
	};

	memcpy(pei_data->usb2_ports, usb2_ports, sizeof(usb2_ports));
	memcpy(pei_data->usb3_ports, usb3_ports, sizeof(usb3_ports));
}
