/* SPDX-License-Identifier: GPL-2.0-only OR MIT */

#include <soc/mt6315.h>

/*
 * These values are used by MediaTek internally.
 * We can find these registers in "MT6315 datasheet v1.3.pdf".
 * The setting values are provided by MeidaTek designers.
 */

static const struct mt6315_setting init_setting_cpu[] = {
	{0x13, 0x2, 0x2, 0},
	{0x15, 0x1F, 0x1F, 0},
	{0x22, 0x12, 0x12, 0},
	{0x8A, 0x6, 0xF, 0},
	{0x10B, 0x3, 0x3, 0},
	{0x38B, 0x4, 0xFF, 0},
	{0xA07, 0x0, 0x1, 0},
	{0xA1A, 0x1F, 0x1F, 0},
	{0x1457, 0x0, 0xFF, 0},
	{0x997, 0xB, 0x7F, 0},
	{0x999, 0xF0, 0xF0, 0},
	{0x9A0, 0x1, 0x1F, 0},
	{0x9A1, 0x1, 0x1F, 0},
	{0x9A2, 0x0, 0x1F, 0},
	{0x9A3, 0x2, 0x1F, 0},
	{0xA0C, 0x0, 0x78, 0},
	{0xA11, 0x1, 0x1F, 0},
	{0xA1A, 0x1F, 0x1F, 0},
	{0x1440, 0xD, 0xF, 0},
	{0x1487, 0x58, 0xFF, 0},
	{0x148B, 0x1, 0x7F, 0},
	{0x148C, 0x1, 0x7F, 0},
	{0x1507, 0x58, 0xFF, 0},
	{0x150B, 0x1, 0x7F, 0},
	{0x150C, 0x1, 0x7F, 0},
	{0x1587, 0xB4, 0xFF, 0},
	{0x158B, 0x1, 0x7F, 0},
	{0x158C, 0x3, 0x7F, 0},
	{0x1607, 0x60, 0xFF, 0},
	{0x160B, 0x1, 0x7F, 0},
	{0x160C, 0x3, 0x7F, 0},
	{0x1687, 0x22, 0x76, 0},
	{0x1688, 0xE, 0x2F, 0},
	{0x1689, 0xA1, 0xE1, 0},
	{0x168A, 0x79, 0x7F, 0},
	{0x168B, 0x12, 0x3F, 0},
	{0x168E, 0xD7, 0xFF, 0},
	{0x168F, 0x81, 0xFF, 0},
	{0x1690, 0x3, 0x3F, 0},
	{0x1691, 0x22, 0x76, 0},
	{0x1692, 0xE, 0x2F, 0},
	{0x1693, 0xA1, 0xE1, 0},
	{0x1694, 0x79, 0x7F, 0},
	{0x1695, 0x12, 0x3F, 0},
	{0x1698, 0xD7, 0xFF, 0},
	{0x1699, 0x81, 0xFF, 0},
	{0x169A, 0x3, 0x3F, 0},
	{0x169B, 0x20, 0x70, 0},
	{0x169C, 0xE, 0x2F, 0},
	{0x169D, 0x81, 0xC1, 0},
	{0x169E, 0xF8, 0xF8, 0},
	{0x169F, 0x12, 0x3F, 0},
	{0x16A2, 0xDB, 0xFF, 0},
	{0x16A3, 0xA1, 0xFF, 0},
	{0x16A4, 0x3, 0xF, 0},
	{0x16A5, 0x20, 0x70, 0},
	{0x16A6, 0xE, 0x2F, 0},
	{0x16A7, 0x81, 0xC1, 0},
	{0x16A8, 0xF8, 0xF8, 0},
	{0x16A9, 0x12, 0x3F, 0},
	{0x16AC, 0xDB, 0xFF, 0},
	{0x16AD, 0xA1, 0xFF, 0},
	{0x16AE, 0x3, 0xF, 0},
	{0x16B8, 0x20, 0xE0, 0},
	{0x16B9, 0x0, 0xF0, 0},
};

void mt6315_init_setting(void)
{
	for (int i = 0; i < ARRAY_SIZE(init_setting_cpu); i++)
		mt6315_write_field(MT6315_CPU,
			init_setting_cpu[i].addr, init_setting_cpu[i].val,
			init_setting_cpu[i].mask, init_setting_cpu[i].shift);
}
