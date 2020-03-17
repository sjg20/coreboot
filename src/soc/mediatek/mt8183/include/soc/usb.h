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

#ifndef SOC_MEDIATEK_MT8183_USB_H
#define SOC_MEDIATEK_MT8183_USB_H

#include <soc/usb_common.h>

struct ssusb_sif_port {
	struct sif_u2_phy_com u2phy;
	u32 reserved0[64*5];
	struct sif_u3phyd u3phyd;
	u32 reserved1[64];
	struct sif_u3phya u3phya;
	struct sif_u3phya_da u3phya_da;
	u32 reserved2[64 * 3];
};
check_member(ssusb_sif_port, u3phyd, 0x600);
check_member(ssusb_sif_port, u3phya, 0x800);
check_member(ssusb_sif_port, u3phya_da, 0x900);
check_member(ssusb_sif_port, reserved2, 0xa00);

#define USB_PORT_NUMBER 1

#endif
