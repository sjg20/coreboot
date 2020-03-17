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

#include <stdint.h>

const struct s_tpm_extend_cmd{
	uint8_t buffer[34];
	uint16_t pcrNum;
	uint16_t inDigest;
} tpm_extend_cmd = {{0x0, 0xc1, 0x0, 0x0, 0x0, 0x22, 0x0, 0x0, 0x0, 0x14, },
10, 14, };

const struct s_tpm_get_random_cmd{
	uint8_t buffer[14];
	uint16_t bytesRequested;
} tpm_get_random_cmd = {{0x0, 0xc1, 0x0, 0x0, 0x0, 0xe, 0x0, 0x0, 0x0, 0x46, },
10, };

const struct s_tpm_getownership_cmd{
	uint8_t buffer[22];
} tpm_getownership_cmd = {
	{0x0, 0xc1, 0x0, 0x0, 0x0, 0x16, 0x0, 0x0, 0x0, 0x65,
	0x0, 0x0, 0x0, 0x5, 0x0, 0x0, 0x0, 0x4, 0x0, 0x0, 0x1, 0x11, },
};

const struct s_tpm_getpermissions_cmd{
	uint8_t buffer[22];
	uint16_t index;
} tpm_getpermissions_cmd = {
	{0x0, 0xc1, 0x0, 0x0, 0x0, 0x16, 0x0, 0x0, 0x0, 0x65,
	0x0, 0x0, 0x0, 0x11, 0x0, 0x0, 0x0, 0x4, },
18, };

const struct s_tpm_getstclearflags_cmd{
	uint8_t buffer[22];
} tpm_getstclearflags_cmd = {
	{0x0, 0xc1, 0x0, 0x0, 0x0, 0x16, 0x0, 0x0, 0x0, 0x65,
	0x0, 0x0, 0x0, 0x4, 0x0, 0x0, 0x0, 0x4, 0x0, 0x0, 0x1, 0x9, },
};

const struct s_tpm_getflags_cmd{
	uint8_t buffer[22];
} tpm_getflags_cmd = {
	{0x0, 0xc1, 0x0, 0x0, 0x0, 0x16, 0x0, 0x0, 0x0, 0x65,
	0x0, 0x0, 0x0, 0x4, 0x0, 0x0, 0x0, 0x4, 0x0, 0x0, 0x1, 0x8, },
};

const struct s_tpm_physicalsetdeactivated_cmd{
	uint8_t buffer[11];
	uint16_t deactivated;
} tpm_physicalsetdeactivated_cmd = {
	{0x0, 0xc1, 0x0, 0x0, 0x0, 0xb, 0x0, 0x0, 0x0, 0x72, },
10, };

const struct s_tpm_physicalenable_cmd{
	uint8_t buffer[10];
} tpm_physicalenable_cmd = {
	{0x0, 0xc1, 0x0, 0x0, 0x0, 0xa, 0x0, 0x0, 0x0, 0x6f, },
};

const struct s_tpm_physicaldisable_cmd{
	uint8_t buffer[10];
} tpm_physicaldisable_cmd = {
	{0x0, 0xc1, 0x0, 0x0, 0x0, 0xa, 0x0, 0x0, 0x0, 0x70, },
};

const struct s_tpm_forceclear_cmd{
	uint8_t buffer[10];
} tpm_forceclear_cmd = {{0x0, 0xc1, 0x0, 0x0, 0x0, 0xa, 0x0, 0x0, 0x0, 0x5d, },
};

const struct s_tpm_readpubek_cmd{
	uint8_t buffer[30];
} tpm_readpubek_cmd = {{0x0, 0xc1, 0x0, 0x0, 0x0, 0x1e, 0x0, 0x0, 0x0, 0x7c, },
};

const struct s_tpm_continueselftest_cmd{
	uint8_t buffer[10];
} tpm_continueselftest_cmd = {
	{0x0, 0xc1, 0x0, 0x0, 0x0, 0xa, 0x0, 0x0, 0x0, 0x53, },
};

const struct s_tpm_selftestfull_cmd{
	uint8_t buffer[10];
} tpm_selftestfull_cmd = {
	{0x0, 0xc1, 0x0, 0x0, 0x0, 0xa, 0x0, 0x0, 0x0, 0x50, },
};

const struct s_tpm_resume_cmd{
	uint8_t buffer[12];
} tpm_resume_cmd = {
	{0x0, 0xc1, 0x0, 0x0, 0x0, 0xc, 0x0, 0x0, 0x0, 0x99, 0x0, 0x2, },
};

const struct s_tpm_savestate_cmd{
	uint8_t buffer[10];
} tpm_savestate_cmd = {{0x0, 0xc1, 0x0, 0x0, 0x0, 0xa, 0x0, 0x0, 0x0, 0x98, },
};

const struct s_tpm_startup_cmd{
	uint8_t buffer[12];
} tpm_startup_cmd = {
	{0x0, 0xc1, 0x0, 0x0, 0x0, 0xc, 0x0, 0x0, 0x0, 0x99, 0x0, 0x1, },
};

const struct s_tpm_finalizepp_cmd{
	uint8_t buffer[12];
} tpm_finalizepp_cmd = {
	{0x0, 0xc1, 0x0, 0x0, 0x0, 0xc, 0x40, 0x0, 0x0, 0xa, 0x2, 0xa0, },
};

const struct s_tpm_pplock_cmd{
	uint8_t buffer[12];
} tpm_pplock_cmd = {
	{0x0, 0xc1, 0x0, 0x0, 0x0, 0xc, 0x40, 0x0, 0x0, 0xa, 0x0, 0x4, },
};

const struct s_tpm_ppenable_cmd{
	uint8_t buffer[12];
} tpm_ppenable_cmd = {
	{0x0, 0xc1, 0x0, 0x0, 0x0, 0xc, 0x40, 0x0, 0x0, 0xa, 0x0, 0x20, },
};

const struct s_tpm_ppassert_cmd{
	uint8_t buffer[12];
} tpm_ppassert_cmd = {
	{0x0, 0xc1, 0x0, 0x0, 0x0, 0xc, 0x40, 0x0, 0x0, 0xa, 0x0, 0x8, },
};

const struct s_tpm_pcr_read_cmd{
	uint8_t buffer[14];
	uint16_t pcrNum;
} tpm_pcr_read_cmd = {{0x0, 0xc1, 0x0, 0x0, 0x0, 0xe, 0x0, 0x0, 0x0, 0x15, },
10, };

const struct s_tpm_nv_read_cmd{
	uint8_t buffer[22];
	uint16_t index;
	uint16_t length;
} tpm_nv_read_cmd = {{0x0, 0xc1, 0x0, 0x0, 0x0, 0x16, 0x0, 0x0, 0x0, 0xcf, },
10, 18, };

const struct s_tpm_nv_write_cmd{
	uint8_t buffer[256];
	uint16_t index;
	uint16_t length;
	uint16_t data;
} tpm_nv_write_cmd = {{0x0, 0xc1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xcd, },
10, 18, 22, };

const struct s_tpm_nv_definespace_cmd{
	uint8_t buffer[101];
	uint16_t index;
	uint16_t perm;
	uint16_t size;
} tpm_nv_definespace_cmd = {
	{0x0, 0xc1, 0x0, 0x0, 0x0, 0x65, 0x0, 0x0, 0x0, 0xcc,
	0x0, 0x18, 0, 0, 0, 0, 0x0, 0x3, 0, 0, 0, 0x1f, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0x0, 0x3, 0, 0, 0, 0x1f, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x0, 0x17,
	},
	12, 70, 77,
};

const int kWriteInfoLength = 12;
const int kNvDataPublicPermissionsOffset = 60;
