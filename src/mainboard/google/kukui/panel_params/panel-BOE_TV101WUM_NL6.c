/* SPDX-License-Identifier: GPL-2.0-only */
/* This file is part of the coreboot project. */

#include "../panel.h"

struct panel_serializable_data BOE_TV101WUM_NL6 = {
	.edid = {
		.ascii_string = "TV101WUM-NL6",
		.manufacturer_name = "BOE",
		.panel_bits_per_color = 8,
		.panel_bits_per_pixel = 24,
		.mode = {
			.pixel_clock = 159425,
			.lvds_dual_channel = 0,
			.refresh = 60,
			.ha = 1200, .hbl = 164, .hso = 100, .hspw = 24,
			.va = 1920, .vbl = 28, .vso = 10, .vspw = 4,
			.phsync = '-', .pvsync = '-',
			.x_mm = 135, .y_mm = 216,
		},
	},
	.orientation = LB_FB_ORIENTATION_LEFT_UP,
	.init = {
		INIT_DELAY_CMD(24),
		INIT_DCS_CMD(0xB0, 0x05),
		INIT_DCS_CMD(0xB1, 0xE5),
		INIT_DCS_CMD(0xB3, 0x52),
		INIT_DCS_CMD(0xB0, 0x00),
		INIT_DCS_CMD(0xB3, 0x88),
		INIT_DCS_CMD(0xB0, 0x04),
		INIT_DCS_CMD(0xB8, 0x00),
		INIT_DCS_CMD(0xB0, 0x00),
		INIT_DCS_CMD(0xB6, 0x03),
		INIT_DCS_CMD(0xBA, 0x8B),
		INIT_DCS_CMD(0xBF, 0x1A),
		INIT_DCS_CMD(0xC0, 0x0F),
		INIT_DCS_CMD(0xC2, 0x0C),
		INIT_DCS_CMD(0xC3, 0x02),
		INIT_DCS_CMD(0xC4, 0x0C),
		INIT_DCS_CMD(0xC5, 0x02),
		INIT_DCS_CMD(0xB0, 0x01),
		INIT_DCS_CMD(0xE0, 0x26),
		INIT_DCS_CMD(0xE1, 0x26),
		INIT_DCS_CMD(0xDC, 0x00),
		INIT_DCS_CMD(0xDD, 0x00),
		INIT_DCS_CMD(0xCC, 0x26),
		INIT_DCS_CMD(0xCD, 0x26),
		INIT_DCS_CMD(0xC8, 0x00),
		INIT_DCS_CMD(0xC9, 0x00),
		INIT_DCS_CMD(0xD2, 0x03),
		INIT_DCS_CMD(0xD3, 0x03),
		INIT_DCS_CMD(0xE6, 0x04),
		INIT_DCS_CMD(0xE7, 0x04),
		INIT_DCS_CMD(0xC4, 0x09),
		INIT_DCS_CMD(0xC5, 0x09),
		INIT_DCS_CMD(0xD8, 0x0A),
		INIT_DCS_CMD(0xD9, 0x0A),
		INIT_DCS_CMD(0xC2, 0x0B),
		INIT_DCS_CMD(0xC3, 0x0B),
		INIT_DCS_CMD(0xD6, 0x0C),
		INIT_DCS_CMD(0xD7, 0x0C),
		INIT_DCS_CMD(0xC0, 0x05),
		INIT_DCS_CMD(0xC1, 0x05),
		INIT_DCS_CMD(0xD4, 0x06),
		INIT_DCS_CMD(0xD5, 0x06),
		INIT_DCS_CMD(0xCA, 0x07),
		INIT_DCS_CMD(0xCB, 0x07),
		INIT_DCS_CMD(0xDE, 0x08),
		INIT_DCS_CMD(0xDF, 0x08),
		INIT_DCS_CMD(0xB0, 0x02),
		INIT_DCS_CMD(0xC0, 0x00),
		INIT_DCS_CMD(0xC1, 0x0D),
		INIT_DCS_CMD(0xC2, 0x17),
		INIT_DCS_CMD(0xC3, 0x26),
		INIT_DCS_CMD(0xC4, 0x31),
		INIT_DCS_CMD(0xC5, 0x1C),
		INIT_DCS_CMD(0xC6, 0x2C),
		INIT_DCS_CMD(0xC7, 0x33),
		INIT_DCS_CMD(0xC8, 0x31),
		INIT_DCS_CMD(0xC9, 0x37),
		INIT_DCS_CMD(0xCA, 0x37),
		INIT_DCS_CMD(0xCB, 0x37),
		INIT_DCS_CMD(0xCC, 0x39),
		INIT_DCS_CMD(0xCD, 0x2E),
		INIT_DCS_CMD(0xCE, 0x2F),
		INIT_DCS_CMD(0xCF, 0x2F),
		INIT_DCS_CMD(0xD0, 0x07),
		INIT_DCS_CMD(0xD2, 0x00),
		INIT_DCS_CMD(0xD3, 0x0D),
		INIT_DCS_CMD(0xD4, 0x17),
		INIT_DCS_CMD(0xD5, 0x26),
		INIT_DCS_CMD(0xD6, 0x31),
		INIT_DCS_CMD(0xD7, 0x3F),
		INIT_DCS_CMD(0xD8, 0x3F),
		INIT_DCS_CMD(0xD9, 0x3F),
		INIT_DCS_CMD(0xDA, 0x3F),
		INIT_DCS_CMD(0xDB, 0x37),
		INIT_DCS_CMD(0xDC, 0x37),
		INIT_DCS_CMD(0xDD, 0x37),
		INIT_DCS_CMD(0xDE, 0x39),
		INIT_DCS_CMD(0xDF, 0x2E),
		INIT_DCS_CMD(0xE0, 0x2F),
		INIT_DCS_CMD(0xE1, 0x2F),
		INIT_DCS_CMD(0xE2, 0x07),
		INIT_DCS_CMD(0xB0, 0x03),
		INIT_DCS_CMD(0xC8, 0x0B),
		INIT_DCS_CMD(0xC9, 0x07),
		INIT_DCS_CMD(0xC3, 0x00),
		INIT_DCS_CMD(0xE7, 0x00),
		INIT_DCS_CMD(0xC5, 0x2A),
		INIT_DCS_CMD(0xDE, 0x2A),
		INIT_DCS_CMD(0xCA, 0x43),
		INIT_DCS_CMD(0xC9, 0x07),
		INIT_DCS_CMD(0xE4, 0xC0),
		INIT_DCS_CMD(0xE5, 0x0D),
		INIT_DCS_CMD(0xCB, 0x00),
		INIT_DCS_CMD(0xB0, 0x06),
		INIT_DCS_CMD(0xB8, 0xA5),
		INIT_DCS_CMD(0xC0, 0xA5),
		INIT_DCS_CMD(0xC7, 0x0F),
		INIT_DCS_CMD(0xD5, 0x32),
		INIT_DCS_CMD(0xB8, 0x00),
		INIT_DCS_CMD(0xC0, 0x00),
		INIT_DCS_CMD(0xBC, 0x00),
		INIT_DCS_CMD(0xB0, 0x07),
		INIT_DCS_CMD(0xB1, 0x00),
		INIT_DCS_CMD(0xB2, 0x02),
		INIT_DCS_CMD(0xB3, 0x0F),
		INIT_DCS_CMD(0xB4, 0x25),
		INIT_DCS_CMD(0xB5, 0x39),
		INIT_DCS_CMD(0xB6, 0x4E),
		INIT_DCS_CMD(0xB7, 0x72),
		INIT_DCS_CMD(0xB8, 0x97),
		INIT_DCS_CMD(0xB9, 0xDC),
		INIT_DCS_CMD(0xBA, 0x22),
		INIT_DCS_CMD(0xBB, 0xA4),
		INIT_DCS_CMD(0xBC, 0x2B),
		INIT_DCS_CMD(0xBD, 0x2F),
		INIT_DCS_CMD(0xBE, 0xA9),
		INIT_DCS_CMD(0xBF, 0x25),
		INIT_DCS_CMD(0xC0, 0x61),
		INIT_DCS_CMD(0xC1, 0x97),
		INIT_DCS_CMD(0xC2, 0xB2),
		INIT_DCS_CMD(0xC3, 0xCD),
		INIT_DCS_CMD(0xC4, 0xD9),
		INIT_DCS_CMD(0xC5, 0xE7),
		INIT_DCS_CMD(0xC6, 0xF4),
		INIT_DCS_CMD(0xC7, 0xFA),
		INIT_DCS_CMD(0xC8, 0xFC),
		INIT_DCS_CMD(0xC9, 0x00),
		INIT_DCS_CMD(0xCA, 0x00),
		INIT_DCS_CMD(0xCB, 0x16),
		INIT_DCS_CMD(0xCC, 0xAF),
		INIT_DCS_CMD(0xCD, 0xFF),
		INIT_DCS_CMD(0xCE, 0xFF),
		INIT_DCS_CMD(0xB0, 0x08),
		INIT_DCS_CMD(0xB1, 0x04),
		INIT_DCS_CMD(0xB2, 0x05),
		INIT_DCS_CMD(0xB3, 0x11),
		INIT_DCS_CMD(0xB4, 0x24),
		INIT_DCS_CMD(0xB5, 0x39),
		INIT_DCS_CMD(0xB6, 0x4F),
		INIT_DCS_CMD(0xB7, 0x72),
		INIT_DCS_CMD(0xB8, 0x98),
		INIT_DCS_CMD(0xB9, 0xDC),
		INIT_DCS_CMD(0xBA, 0x23),
		INIT_DCS_CMD(0xBB, 0xA6),
		INIT_DCS_CMD(0xBC, 0x2C),
		INIT_DCS_CMD(0xBD, 0x30),
		INIT_DCS_CMD(0xBE, 0xAA),
		INIT_DCS_CMD(0xBF, 0x26),
		INIT_DCS_CMD(0xC0, 0x62),
		INIT_DCS_CMD(0xC1, 0x9B),
		INIT_DCS_CMD(0xC2, 0xB5),
		INIT_DCS_CMD(0xC3, 0xCF),
		INIT_DCS_CMD(0xC4, 0xDB),
		INIT_DCS_CMD(0xC5, 0xE8),
		INIT_DCS_CMD(0xC6, 0xF5),
		INIT_DCS_CMD(0xC7, 0xFA),
		INIT_DCS_CMD(0xC8, 0xFC),
		INIT_DCS_CMD(0xC9, 0x00),
		INIT_DCS_CMD(0xCA, 0x00),
		INIT_DCS_CMD(0xCB, 0x16),
		INIT_DCS_CMD(0xCC, 0xAF),
		INIT_DCS_CMD(0xCD, 0xFF),
		INIT_DCS_CMD(0xCE, 0xFF),
		INIT_DCS_CMD(0xB0, 0x09),
		INIT_DCS_CMD(0xB1, 0x04),
		INIT_DCS_CMD(0xB2, 0x02),
		INIT_DCS_CMD(0xB3, 0x16),
		INIT_DCS_CMD(0xB4, 0x24),
		INIT_DCS_CMD(0xB5, 0x3B),
		INIT_DCS_CMD(0xB6, 0x4F),
		INIT_DCS_CMD(0xB7, 0x73),
		INIT_DCS_CMD(0xB8, 0x99),
		INIT_DCS_CMD(0xB9, 0xE0),
		INIT_DCS_CMD(0xBA, 0x26),
		INIT_DCS_CMD(0xBB, 0xAD),
		INIT_DCS_CMD(0xBC, 0x36),
		INIT_DCS_CMD(0xBD, 0x3A),
		INIT_DCS_CMD(0xBE, 0xAE),
		INIT_DCS_CMD(0xBF, 0x2A),
		INIT_DCS_CMD(0xC0, 0x66),
		INIT_DCS_CMD(0xC1, 0x9E),
		INIT_DCS_CMD(0xC2, 0xB8),
		INIT_DCS_CMD(0xC3, 0xD1),
		INIT_DCS_CMD(0xC4, 0xDD),
		INIT_DCS_CMD(0xC5, 0xE9),
		INIT_DCS_CMD(0xC6, 0xF6),
		INIT_DCS_CMD(0xC7, 0xFA),
		INIT_DCS_CMD(0xC8, 0xFC),
		INIT_DCS_CMD(0xC9, 0x00),
		INIT_DCS_CMD(0xCA, 0x00),
		INIT_DCS_CMD(0xCB, 0x16),
		INIT_DCS_CMD(0xCC, 0xAF),
		INIT_DCS_CMD(0xCD, 0xFF),
		INIT_DCS_CMD(0xCE, 0xFF),
		INIT_DCS_CMD(0xB0, 0x0A),
		INIT_DCS_CMD(0xB1, 0x00),
		INIT_DCS_CMD(0xB2, 0x02),
		INIT_DCS_CMD(0xB3, 0x0F),
		INIT_DCS_CMD(0xB4, 0x25),
		INIT_DCS_CMD(0xB5, 0x39),
		INIT_DCS_CMD(0xB6, 0x4E),
		INIT_DCS_CMD(0xB7, 0x72),
		INIT_DCS_CMD(0xB8, 0x97),
		INIT_DCS_CMD(0xB9, 0xDC),
		INIT_DCS_CMD(0xBA, 0x22),
		INIT_DCS_CMD(0xBB, 0xA4),
		INIT_DCS_CMD(0xBC, 0x2B),
		INIT_DCS_CMD(0xBD, 0x2F),
		INIT_DCS_CMD(0xBE, 0xA9),
		INIT_DCS_CMD(0xBF, 0x25),
		INIT_DCS_CMD(0xC0, 0x61),
		INIT_DCS_CMD(0xC1, 0x97),
		INIT_DCS_CMD(0xC2, 0xB2),
		INIT_DCS_CMD(0xC3, 0xCD),
		INIT_DCS_CMD(0xC4, 0xD9),
		INIT_DCS_CMD(0xC5, 0xE7),
		INIT_DCS_CMD(0xC6, 0xF4),
		INIT_DCS_CMD(0xC7, 0xFA),
		INIT_DCS_CMD(0xC8, 0xFC),
		INIT_DCS_CMD(0xC9, 0x00),
		INIT_DCS_CMD(0xCA, 0x00),
		INIT_DCS_CMD(0xCB, 0x16),
		INIT_DCS_CMD(0xCC, 0xAF),
		INIT_DCS_CMD(0xCD, 0xFF),
		INIT_DCS_CMD(0xCE, 0xFF),
		INIT_DCS_CMD(0xB0, 0x0B),
		INIT_DCS_CMD(0xB1, 0x04),
		INIT_DCS_CMD(0xB2, 0x05),
		INIT_DCS_CMD(0xB3, 0x11),
		INIT_DCS_CMD(0xB4, 0x24),
		INIT_DCS_CMD(0xB5, 0x39),
		INIT_DCS_CMD(0xB6, 0x4F),
		INIT_DCS_CMD(0xB7, 0x72),
		INIT_DCS_CMD(0xB8, 0x98),
		INIT_DCS_CMD(0xB9, 0xDC),
		INIT_DCS_CMD(0xBA, 0x23),
		INIT_DCS_CMD(0xBB, 0xA6),
		INIT_DCS_CMD(0xBC, 0x2C),
		INIT_DCS_CMD(0xBD, 0x30),
		INIT_DCS_CMD(0xBE, 0xAA),
		INIT_DCS_CMD(0xBF, 0x26),
		INIT_DCS_CMD(0xC0, 0x62),
		INIT_DCS_CMD(0xC1, 0x9B),
		INIT_DCS_CMD(0xC2, 0xB5),
		INIT_DCS_CMD(0xC3, 0xCF),
		INIT_DCS_CMD(0xC4, 0xDB),
		INIT_DCS_CMD(0xC5, 0xE8),
		INIT_DCS_CMD(0xC6, 0xF5),
		INIT_DCS_CMD(0xC7, 0xFA),
		INIT_DCS_CMD(0xC8, 0xFC),
		INIT_DCS_CMD(0xC9, 0x00),
		INIT_DCS_CMD(0xCA, 0x00),
		INIT_DCS_CMD(0xCB, 0x16),
		INIT_DCS_CMD(0xCC, 0xAF),
		INIT_DCS_CMD(0xCD, 0xFF),
		INIT_DCS_CMD(0xCE, 0xFF),
		INIT_DCS_CMD(0xB0, 0x0C),
		INIT_DCS_CMD(0xB1, 0x04),
		INIT_DCS_CMD(0xB2, 0x02),
		INIT_DCS_CMD(0xB3, 0x16),
		INIT_DCS_CMD(0xB4, 0x24),
		INIT_DCS_CMD(0xB5, 0x3B),
		INIT_DCS_CMD(0xB6, 0x4F),
		INIT_DCS_CMD(0xB7, 0x73),
		INIT_DCS_CMD(0xB8, 0x99),
		INIT_DCS_CMD(0xB9, 0xE0),
		INIT_DCS_CMD(0xBA, 0x26),
		INIT_DCS_CMD(0xBB, 0xAD),
		INIT_DCS_CMD(0xBC, 0x36),
		INIT_DCS_CMD(0xBD, 0x3A),
		INIT_DCS_CMD(0xBE, 0xAE),
		INIT_DCS_CMD(0xBF, 0x2A),
		INIT_DCS_CMD(0xC0, 0x66),
		INIT_DCS_CMD(0xC1, 0x9E),
		INIT_DCS_CMD(0xC2, 0xB8),
		INIT_DCS_CMD(0xC3, 0xD1),
		INIT_DCS_CMD(0xC4, 0xDD),
		INIT_DCS_CMD(0xC5, 0xE9),
		INIT_DCS_CMD(0xC6, 0xF6),
		INIT_DCS_CMD(0xC7, 0xFA),
		INIT_DCS_CMD(0xC8, 0xFC),
		INIT_DCS_CMD(0xC9, 0x00),
		INIT_DCS_CMD(0xCA, 0x00),
		INIT_DCS_CMD(0xCB, 0x16),
		INIT_DCS_CMD(0xCC, 0xAF),
		INIT_DCS_CMD(0xCD, 0xFF),
		INIT_DCS_CMD(0xCE, 0xFF),
		INIT_DCS_CMD(0xB0, 0x00),
		INIT_DCS_CMD(0xB3, 0x08),
		INIT_DCS_CMD(0xB0, 0x04),
		INIT_DCS_CMD(0xB8, 0x68),
		INIT_DELAY_CMD(150),
		INIT_END_CMD,
	},
};
