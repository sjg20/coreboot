/* SPDX-License-Identifier: GPL-2.0-only */

#include <mipi/panel.h>

struct panel_serializable_data AUO_B101UAN08_3 = {
	.edid = {
		.ascii_string = "B101UAN08.3",
		.manufacturer_name = "AUO",
		.panel_bits_per_color = 8,
		.panel_bits_per_pixel = 24,
		.mode = {
			.pixel_clock = 159192,
			.lvds_dual_channel = 0,
			.refresh = 60,
			.ha = 1200, .hbl = 144, .hso = 60, .hspw = 4,
			.va = 1920, .vbl = 60, .vso = 34, .vspw = 2,
			.phsync = '-', .pvsync = '-',
			.x_mm = 135, .y_mm = 216,
		},
	},
	.init = {
		PANEL_DELAY(24),
		PANEL_DCS(0xB0, 0x01),
		PANEL_DCS(0xC0, 0x48),
		PANEL_DCS(0xC1, 0x48),
		PANEL_DCS(0xC2, 0x47),
		PANEL_DCS(0xC3, 0x47),
		PANEL_DCS(0xC4, 0x46),
		PANEL_DCS(0xC5, 0x46),
		PANEL_DCS(0xC6, 0x45),
		PANEL_DCS(0xC7, 0x45),
		PANEL_DCS(0xC8, 0x64),
		PANEL_DCS(0xC9, 0x64),
		PANEL_DCS(0xCA, 0x4F),
		PANEL_DCS(0xCB, 0x4F),
		PANEL_DCS(0xCC, 0x40),
		PANEL_DCS(0xCD, 0x40),
		PANEL_DCS(0xCE, 0x66),
		PANEL_DCS(0xCF, 0x66),
		PANEL_DCS(0xD0, 0x4F),
		PANEL_DCS(0xD1, 0x4F),
		PANEL_DCS(0xD2, 0x41),
		PANEL_DCS(0xD3, 0x41),
		PANEL_DCS(0xD4, 0x48),
		PANEL_DCS(0xD5, 0x48),
		PANEL_DCS(0xD6, 0x47),
		PANEL_DCS(0xD7, 0x47),
		PANEL_DCS(0xD8, 0x46),
		PANEL_DCS(0xD9, 0x46),
		PANEL_DCS(0xDA, 0x45),
		PANEL_DCS(0xDB, 0x45),
		PANEL_DCS(0xDC, 0x64),
		PANEL_DCS(0xDD, 0x64),
		PANEL_DCS(0xDE, 0x4F),
		PANEL_DCS(0xDF, 0x4F),
		PANEL_DCS(0xE0, 0x40),
		PANEL_DCS(0xE1, 0x40),
		PANEL_DCS(0xE2, 0x66),
		PANEL_DCS(0xE3, 0x66),
		PANEL_DCS(0xE4, 0x4F),
		PANEL_DCS(0xE5, 0x4F),
		PANEL_DCS(0xE6, 0x41),
		PANEL_DCS(0xE7, 0x41),
		PANEL_DELAY(150),
		PANEL_END,
	},
};
