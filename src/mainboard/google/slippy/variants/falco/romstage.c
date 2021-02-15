/* SPDX-License-Identifier: GPL-2.0-only */

#include <string.h>
#include <northbridge/intel/haswell/raminit.h>
#include <southbridge/intel/lynxpoint/pch.h>
#include <southbridge/intel/lynxpoint/lp_gpio.h>
#include "../../variant.h"

/* Copy SPD data for on-board memory */
void copy_spd(struct pei_data *peid)
{
	const int gpio_vector[] = {13, 9, 47, -1};

	unsigned int spd_index = fill_spd_for_index(peid->spd_data[0], get_gpios(gpio_vector));

	/* Index 0-2,6 are 4GB config with both CH0 and CH1
	 * Index 3-5,7 are 2GB config with CH0 only
	 */
	switch (spd_index) {
	case 0: case 1: case 2: case 6:
		memcpy(peid->spd_data[1], peid->spd_data[0], SPD_LEN);
		break;
	case 3: case 4: case 5: case 7:
		peid->dimm_channel1_disabled = 3;
	}
}

const struct usb2_port_setting mainboard_usb2_ports[MAX_USB2_PORTS] = {
	/* Length, Enable, OCn#, Location */
	{ 0x0064, 1, 0,               /* P0: Port A, CN8 */
	  USB_PORT_BACK_PANEL },
	{ 0x0052, 1, 0,               /* P1: Port B, CN9  */
	  USB_PORT_BACK_PANEL },
	{ 0x0040, 1, USB_OC_PIN_SKIP, /* P2: CCD */
	  USB_PORT_INTERNAL },
	{ 0x0040, 1, USB_OC_PIN_SKIP, /* P3: BT */
	  USB_PORT_INTERNAL },
	{ 0x0040, 1, USB_OC_PIN_SKIP, /* P4: LTE */
	  USB_PORT_INTERNAL },
	{ 0x0040, 1, USB_OC_PIN_SKIP, /* P5: TOUCH */
	  USB_PORT_INTERNAL },
	{ 0x0040, 1, USB_OC_PIN_SKIP, /* P6: SD Card */
	  USB_PORT_INTERNAL },
	{ 0x0123, 1, 3,               /* P7: USB2 Port */
	  USB_PORT_INTERNAL },
};

const struct usb3_port_setting mainboard_usb3_ports[MAX_USB3_PORTS] = {
	/* Enable, OCn# */
	{ 1, 0               }, /* P1; Port A, CN8 */
	{ 1, 0               }, /* P2; Port B, CN9  */
	{ 0, USB_OC_PIN_SKIP }, /* P3; */
	{ 0, USB_OC_PIN_SKIP }, /* P4; */
};
