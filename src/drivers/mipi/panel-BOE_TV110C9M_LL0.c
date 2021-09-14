/* SPDX-License-Identifier: GPL-2.0-only */

#include <mipi/panel.h>

struct panel_serializable_data BOE_TV110C9M_LL0 = {
	.edid = {
		.ascii_string = "TV110C9M-LL0",
		.manufacturer_name = "BOE",
		.panel_bits_per_color = 8,
		.panel_bits_per_pixel = 24,
		.mode = {
			.pixel_clock = 166594,
			.lvds_dual_channel = 0,
			.refresh = 60,
			.ha = 1200, .hbl = 76, .hso = 40, .hspw = 8,
			.va = 2000, .vbl = 176, .vso = 26, .vspw = 2,
			.phsync = '-', .pvsync = '-',
			.x_mm = 143, .y_mm = 238,
		},
	},
	.init = {
		PANEL_DCS(0xFF, 0x20),
		PANEL_DCS(0xFB, 0x01),
		PANEL_DCS(0x05, 0xD9),
		PANEL_DCS(0x07, 0x78),
		PANEL_DCS(0x08, 0x5A),
		PANEL_DCS(0x0D, 0x63),
		PANEL_DCS(0x0E, 0x91),
		PANEL_DCS(0x0F, 0x73),
		PANEL_DCS(0x95, 0xEB),
		PANEL_DCS(0x96, 0xEB),
		PANEL_DCS(0x30, 0x11),
		PANEL_DCS(0x6D, 0x66),
		PANEL_DCS(0x75, 0xA2),
		PANEL_DCS(0x77, 0x3B),
		PANEL_DCS(0xB0, 0x00, 0x08, 0x00, 0x23, 0x00, 0x4D, 0x00, 0x6D, 0x00,
			0x89, 0x00, 0xA1, 0x00, 0xB6, 0x00, 0xC9),
		PANEL_DCS(0xB1, 0x00, 0xDA, 0x01, 0x13, 0x01, 0x3C, 0x01, 0x7E, 0x01,
			0xAB, 0x01, 0xF7, 0x02, 0x2F, 0x02, 0x31),
		PANEL_DCS(0xB2, 0x02, 0x67, 0x02, 0xA6, 0x02, 0xD1, 0x03, 0x08, 0x03,
			0x2E, 0x03, 0x5B, 0x03, 0x6B, 0x03, 0x7B),
		PANEL_DCS(0xB3, 0x03, 0x8E, 0x03, 0xA2, 0x03, 0xB7, 0x03, 0xE7, 0x03,
			0xFD, 0x03, 0xFF),
		PANEL_DCS(0xB4, 0x00, 0x08, 0x00, 0x23, 0x00, 0x4D, 0x00, 0x6D, 0x00,
			0x89, 0x00, 0xA1, 0x00, 0xB6, 0x00, 0xC9),
		PANEL_DCS(0xB5, 0x00, 0xDA, 0x01, 0x13, 0x01, 0x3C, 0x01, 0x7E, 0x01,
			0xAB, 0x01, 0xF7, 0x02, 0x2F, 0x02, 0x31),
		PANEL_DCS(0xB6, 0x02, 0x67, 0x02, 0xA6, 0x02, 0xD1, 0x03, 0x08, 0x03,
			0x2E, 0x03, 0x5B, 0x03, 0x6B, 0x03, 0x7B),
		PANEL_DCS(0xB7, 0x03, 0x8E, 0x03, 0xA2, 0x03, 0xB7, 0x03, 0xE7, 0x03,
			0xFD, 0x03, 0xFF),
		PANEL_DCS(0xB8, 0x00, 0x08, 0x00, 0x23, 0x00, 0x4D, 0x00, 0x6D, 0x00,
			0x89, 0x00, 0xA1, 0x00, 0xB6, 0x00, 0xC9),
		PANEL_DCS(0xB9, 0x00, 0xDA, 0x01, 0x13, 0x01, 0x3C, 0x01, 0x7E, 0x01,
			0xAB, 0x01, 0xF7, 0x02, 0x2F, 0x02, 0x31),
		PANEL_DCS(0xBA, 0x02, 0x67, 0x02, 0xA6, 0x02, 0xD1, 0x03, 0x08, 0x03,
			0x2E, 0x03, 0x5B, 0x03, 0x6B, 0x03, 0x7B),
		PANEL_DCS(0xBB, 0x03, 0x8E, 0x03, 0xA2, 0x03, 0xB7, 0x03, 0xE7, 0x03,
			0xFD, 0x03, 0xFF),
		PANEL_DCS(0xFF, 0x21),
		PANEL_DCS(0xFB, 0x01),
		PANEL_DCS(0xB0, 0x00, 0x00, 0x00, 0x1B, 0x00, 0x45, 0x00, 0x65, 0x00,
			0x81, 0x00, 0x99, 0x00, 0xAE, 0x00, 0xC1),
		PANEL_DCS(0xB1, 0x00, 0xD2, 0x01, 0x0B, 0x01, 0x34, 0x01, 0x76, 0x01,
			0xA3, 0x01, 0xEF, 0x02, 0x27, 0x02, 0x29),
		PANEL_DCS(0xB2, 0x02, 0x5F, 0x02, 0x9E, 0x02, 0xC9, 0x03, 0x00, 0x03,
			0x26, 0x03, 0x53, 0x03, 0x63, 0x03, 0x73),
		PANEL_DCS(0xB3, 0x03, 0x86, 0x03, 0x9A, 0x03, 0xAF, 0x03, 0xDF, 0x03,
			0xF5, 0x03, 0xF7),
		PANEL_DCS(0xB4, 0x00, 0x00, 0x00, 0x1B, 0x00, 0x45, 0x00, 0x65, 0x00,
			0x81, 0x00, 0x99, 0x00, 0xAE, 0x00, 0xC1),
		PANEL_DCS(0xB5, 0x00, 0xD2, 0x01, 0x0B, 0x01, 0x34, 0x01, 0x76, 0x01,
			0xA3, 0x01, 0xEF, 0x02, 0x27, 0x02, 0x29),
		PANEL_DCS(0xB6, 0x02, 0x5F, 0x02, 0x9E, 0x02, 0xC9, 0x03, 0x00, 0x03,
			0x26, 0x03, 0x53, 0x03, 0x63, 0x03, 0x73),
		PANEL_DCS(0xB7, 0x03, 0x86, 0x03, 0x9A, 0x03, 0xAF, 0x03, 0xDF, 0x03,
			0xF5, 0x03, 0xF7),
		PANEL_DCS(0xB8, 0x00, 0x00, 0x00, 0x1B, 0x00, 0x45, 0x00, 0x65, 0x00,
			0x81, 0x00, 0x99, 0x00, 0xAE, 0x00, 0xC1),
		PANEL_DCS(0xB9, 0x00, 0xD2, 0x01, 0x0B, 0x01, 0x34, 0x01, 0x76, 0x01,
			0xA3, 0x01, 0xEF, 0x02, 0x27, 0x02, 0x29),
		PANEL_DCS(0xBA, 0x02, 0x5F, 0x02, 0x9E, 0x02, 0xC9, 0x03, 0x00, 0x03,
			0x26, 0x03, 0x53, 0x03, 0x63, 0x03, 0x73),
		PANEL_DCS(0xBB, 0x03, 0x86, 0x03, 0x9A, 0x03, 0xAF, 0x03, 0xDF, 0x03,
			0xF5, 0x03, 0xF7),
		PANEL_DCS(0xFF, 0x24),
		PANEL_DCS(0xFB, 0x01),
		PANEL_DCS(0x00, 0x00),
		PANEL_DCS(0x01, 0x00),
		PANEL_DCS(0x02, 0x1C),
		PANEL_DCS(0x03, 0x1C),
		PANEL_DCS(0x04, 0x1D),
		PANEL_DCS(0x05, 0x1D),
		PANEL_DCS(0x06, 0x04),
		PANEL_DCS(0x07, 0x04),
		PANEL_DCS(0x08, 0x0F),
		PANEL_DCS(0x09, 0x0F),
		PANEL_DCS(0x0A, 0x0E),
		PANEL_DCS(0x0B, 0x0E),
		PANEL_DCS(0x0C, 0x0D),
		PANEL_DCS(0x0D, 0x0D),
		PANEL_DCS(0x0E, 0x0C),
		PANEL_DCS(0x0F, 0x0C),
		PANEL_DCS(0x10, 0x08),
		PANEL_DCS(0x11, 0x08),
		PANEL_DCS(0x12, 0x00),
		PANEL_DCS(0x13, 0x00),
		PANEL_DCS(0x14, 0x00),
		PANEL_DCS(0x15, 0x00),
		PANEL_DCS(0x16, 0x00),
		PANEL_DCS(0x17, 0x00),
		PANEL_DCS(0x18, 0x1C),
		PANEL_DCS(0x19, 0x1C),
		PANEL_DCS(0x1A, 0x1D),
		PANEL_DCS(0x1B, 0x1D),
		PANEL_DCS(0x1C, 0x04),
		PANEL_DCS(0x1D, 0x04),
		PANEL_DCS(0x1E, 0x0F),
		PANEL_DCS(0x1F, 0x0F),
		PANEL_DCS(0x20, 0x0E),
		PANEL_DCS(0x21, 0x0E),
		PANEL_DCS(0x22, 0x0D),
		PANEL_DCS(0x23, 0x0D),
		PANEL_DCS(0x24, 0x0C),
		PANEL_DCS(0x25, 0x0C),
		PANEL_DCS(0x26, 0x08),
		PANEL_DCS(0x27, 0x08),
		PANEL_DCS(0x28, 0x00),
		PANEL_DCS(0x29, 0x00),
		PANEL_DCS(0x2A, 0x00),
		PANEL_DCS(0x2B, 0x00),
		PANEL_DCS(0x2D, 0x20),
		PANEL_DCS(0x2F, 0x0A),
		PANEL_DCS(0x30, 0x44),
		PANEL_DCS(0x33, 0x0C),
		PANEL_DCS(0x34, 0x32),
		PANEL_DCS(0x37, 0x44),
		PANEL_DCS(0x38, 0x40),
		PANEL_DCS(0x39, 0x00),
		PANEL_DCS(0x3A, 0x5D),
		PANEL_DCS(0x3B, 0x60),
		PANEL_DCS(0x3D, 0x42),
		PANEL_DCS(0x3F, 0x06),
		PANEL_DCS(0x43, 0x06),
		PANEL_DCS(0x47, 0x66),
		PANEL_DCS(0x4A, 0x5D),
		PANEL_DCS(0x4B, 0x60),
		PANEL_DCS(0x4C, 0x91),
		PANEL_DCS(0x4D, 0x21),
		PANEL_DCS(0x4E, 0x43),
		PANEL_DCS(0x51, 0x12),
		PANEL_DCS(0x52, 0x34),
		PANEL_DCS(0x55, 0x82, 0x02),
		PANEL_DCS(0x56, 0x04),
		PANEL_DCS(0x58, 0x21),
		PANEL_DCS(0x59, 0x30),
		PANEL_DCS(0x5A, 0x60),
		PANEL_DCS(0x5B, 0x50),
		PANEL_DCS(0x5E, 0x00, 0x06),
		PANEL_DCS(0x5F, 0x00),
		PANEL_DCS(0x65, 0x82),
		PANEL_DCS(0x7E, 0x20),
		PANEL_DCS(0x7F, 0x3C),
		PANEL_DCS(0x82, 0x04),
		PANEL_DCS(0x97, 0xC0),
		PANEL_DCS(0xB6, 0x05, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05,
			0x05, 0x00, 0x00),
		PANEL_DCS(0x91, 0x44),
		PANEL_DCS(0x92, 0xA9),
		PANEL_DCS(0x93, 0x1A),
		PANEL_DCS(0x94, 0x96),
		PANEL_DCS(0xD7, 0x55),
		PANEL_DCS(0xDA, 0x0A),
		PANEL_DCS(0xDE, 0x08),
		PANEL_DCS(0xDB, 0x05),
		PANEL_DCS(0xDC, 0xA9),
		PANEL_DCS(0xDD, 0x22),
		PANEL_DCS(0xDF, 0x05),
		PANEL_DCS(0xE0, 0xA9),
		PANEL_DCS(0xE1, 0x05),
		PANEL_DCS(0xE2, 0xA9),
		PANEL_DCS(0xE3, 0x05),
		PANEL_DCS(0xE4, 0xA9),
		PANEL_DCS(0xE5, 0x05),
		PANEL_DCS(0xE6, 0xA9),
		PANEL_DCS(0x5C, 0x00),
		PANEL_DCS(0x5D, 0x00),
		PANEL_DCS(0x8D, 0x00),
		PANEL_DCS(0x8E, 0x00),
		PANEL_DCS(0xB5, 0x90),
		PANEL_DCS(0xFF, 0x25),
		PANEL_DCS(0xFB, 0x01),
		PANEL_DCS(0x05, 0x00),
		PANEL_DCS(0x19, 0x07),
		PANEL_DCS(0x1F, 0x60),
		PANEL_DCS(0x20, 0x50),
		PANEL_DCS(0x26, 0x60),
		PANEL_DCS(0x27, 0x50),
		PANEL_DCS(0x33, 0x60),
		PANEL_DCS(0x34, 0x50),
		PANEL_DCS(0x3F, 0xE0),
		PANEL_DCS(0x40, 0x00),
		PANEL_DCS(0x44, 0x00),
		PANEL_DCS(0x45, 0x40),
		PANEL_DCS(0x48, 0x60),
		PANEL_DCS(0x49, 0x50),
		PANEL_DCS(0x5B, 0x00),
		PANEL_DCS(0x5C, 0x00),
		PANEL_DCS(0x5D, 0x00),
		PANEL_DCS(0x5E, 0xD0),
		PANEL_DCS(0x61, 0x60),
		PANEL_DCS(0x62, 0x50),
		PANEL_DCS(0xF1, 0x10),
		PANEL_DCS(0xFF, 0x2A),
		PANEL_DCS(0xFB, 0x01),
		PANEL_DCS(0x64, 0x16),
		PANEL_DCS(0x67, 0x16),
		PANEL_DCS(0x6A, 0x16),
		PANEL_DCS(0x70, 0x30),
		PANEL_DCS(0xA2, 0xF3),
		PANEL_DCS(0xA3, 0xFF),
		PANEL_DCS(0xA4, 0xFF),
		PANEL_DCS(0xA5, 0xFF),
		PANEL_DCS(0xD6, 0x08),
		PANEL_DCS(0xFF, 0x26),
		PANEL_DCS(0xFB, 0x01),
		PANEL_DCS(0x00, 0xA1),
		PANEL_DCS(0x02, 0x31),
		PANEL_DCS(0x04, 0x28),
		PANEL_DCS(0x06, 0x30),
		PANEL_DCS(0x0C, 0x16),
		PANEL_DCS(0x0D, 0x0D),
		PANEL_DCS(0x0F, 0x00),
		PANEL_DCS(0x11, 0x00),
		PANEL_DCS(0x12, 0x50),
		PANEL_DCS(0x13, 0x56),
		PANEL_DCS(0x14, 0x57),
		PANEL_DCS(0x15, 0x00),
		PANEL_DCS(0x16, 0x10),
		PANEL_DCS(0x17, 0xA0),
		PANEL_DCS(0x18, 0x86),
		PANEL_DCS(0x19, 0x0D),
		PANEL_DCS(0x1A, 0x7F),
		PANEL_DCS(0x1B, 0x0C),
		PANEL_DCS(0x1C, 0xBF),
		PANEL_DCS(0x22, 0x00),
		PANEL_DCS(0x23, 0x00),
		PANEL_DCS(0x2A, 0x0D),
		PANEL_DCS(0x2B, 0x7F),
		PANEL_DCS(0x1D, 0x00),
		PANEL_DCS(0x1E, 0x65),
		PANEL_DCS(0x1F, 0x65),
		PANEL_DCS(0x24, 0x00),
		PANEL_DCS(0x25, 0x65),
		PANEL_DCS(0x2F, 0x05),
		PANEL_DCS(0x30, 0x65),
		PANEL_DCS(0x31, 0x05),
		PANEL_DCS(0x32, 0x7D),
		PANEL_DCS(0x39, 0x00),
		PANEL_DCS(0x3A, 0x65),
		PANEL_DCS(0x20, 0x01),
		PANEL_DCS(0x33, 0x11),
		PANEL_DCS(0x34, 0x78),
		PANEL_DCS(0x35, 0x16),
		PANEL_DCS(0xC8, 0x04),
		PANEL_DCS(0xC9, 0x80),
		PANEL_DCS(0xCA, 0x4E),
		PANEL_DCS(0xCB, 0x00),
		PANEL_DCS(0xA9, 0x4C),
		PANEL_DCS(0xAA, 0x47),
		PANEL_DCS(0xFF, 0x27),
		PANEL_DCS(0xFB, 0x01),
		PANEL_DCS(0x56, 0x06),
		PANEL_DCS(0x58, 0x80),
		PANEL_DCS(0x59, 0x75),
		PANEL_DCS(0x5A, 0x00),
		PANEL_DCS(0x5B, 0x02),
		PANEL_DCS(0x5C, 0x00),
		PANEL_DCS(0x5D, 0x00),
		PANEL_DCS(0x5E, 0x20),
		PANEL_DCS(0x5F, 0x10),
		PANEL_DCS(0x60, 0x00),
		PANEL_DCS(0x61, 0x2E),
		PANEL_DCS(0x62, 0x00),
		PANEL_DCS(0x63, 0x01),
		PANEL_DCS(0x64, 0x43),
		PANEL_DCS(0x65, 0x2D),
		PANEL_DCS(0x66, 0x00),
		PANEL_DCS(0x67, 0x01),
		PANEL_DCS(0x68, 0x44),
		PANEL_DCS(0x00, 0x00),
		PANEL_DCS(0x78, 0x00),
		PANEL_DCS(0xC3, 0x00),
		PANEL_DCS(0xFF, 0x2A),
		PANEL_DCS(0xFB, 0x01),
		PANEL_DCS(0x22, 0x2F),
		PANEL_DCS(0x23, 0x08),
		PANEL_DCS(0x24, 0x00),
		PANEL_DCS(0x25, 0x65),
		PANEL_DCS(0x26, 0xF8),
		PANEL_DCS(0x27, 0x00),
		PANEL_DCS(0x28, 0x1A),
		PANEL_DCS(0x29, 0x00),
		PANEL_DCS(0x2A, 0x1A),
		PANEL_DCS(0x2B, 0x00),
		PANEL_DCS(0x2D, 0x1A),
		PANEL_DCS(0xFF, 0x23),
		PANEL_DCS(0xFB, 0x01),
		PANEL_DCS(0x00, 0x80),
		PANEL_DCS(0x07, 0x00),
		PANEL_DCS(0xFF, 0x24),
		PANEL_DCS(0xC2, 0x06),
		PANEL_DCS(0xFF, 0x10),
		PANEL_DCS(0xFF, 0xE0),
		PANEL_DCS(0xFB, 0x01),
		PANEL_DCS(0x14, 0x60),
		PANEL_DCS(0x16, 0xC0),
		PANEL_DCS(0xFF, 0xF0),
		PANEL_DCS(0xFB, 0x01),
		PANEL_DCS(0x3A, 0x08),
		PANEL_DCS(0xFF, 0x10),
		PANEL_DCS(0xFB, 0x01),
		PANEL_DCS(0xB9, 0x01),
		PANEL_DCS(0xFF, 0x20),
		PANEL_DCS(0xFB, 0x01),
		PANEL_DCS(0x18, 0x40),
		PANEL_DCS(0xFF, 0x10),
		PANEL_DCS(0xFB, 0x01),
		PANEL_DCS(0xB9, 0x02),
		PANEL_DCS(0x35, 0x00),
		PANEL_DCS(0x51, 0x00, 0xFF),
		PANEL_DCS(0x53, 0x24),
		PANEL_DCS(0x55, 0x00),
		PANEL_DCS(0xBB, 0x13),
		PANEL_DCS(0x3B, 0x03, 0x96, 0x1A, 0x04, 0x04),
		PANEL_DELAY(100),
		PANEL_DCS(0x11),
		PANEL_DELAY(200),
		PANEL_DCS(0x29),
		PANEL_DELAY(100),
		PANEL_END,
	},
};
