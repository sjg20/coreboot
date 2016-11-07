/*
 * Copyright (c) 2013-2016, The Regents of the University of California
 *(Regents).
 * All Rights Reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Regents nor the
 *    names of its contributors may be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * IN NO EVENT SHALL REGENTS BE LIABLE TO ANY PARTY FOR DIRECT, INDIRECT,
 * SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES, INCLUDING LOST PROFITS,
 * ARISING
 * OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF REGENTS HAS
 * BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * REGENTS SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE. THE SOFTWARE AND ACCOMPANYING DOCUMENTATION, IF ANY, PROVIDED
 * HEREUNDER IS PROVIDED "AS IS". REGENTS HAS NO OBLIGATION TO PROVIDE
 * MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.
 */

#include <config.h>
#include <assert.h>
#include <string.h>
#include <commonlib/configstring.h>

void query_mem(const char *config_string, uintptr_t *base, size_t *size)
{
	query_result res = query_config_string(config_string, "ram{0{addr");
	*base = get_uint(res);
	res = query_config_string(config_string, "ram{0{size");
	*size = get_uint(res);
}

/* query_rtc returns the physical address of the rtc. */
void query_rtc(const char *config_string, uintptr_t *mtime)
{
	query_result res = query_config_string(config_string, "rtc{addr");
	*mtime = (uintptr_t)get_uint(res);
}

const char *configstring(void)
{
	uint32_t addr = *(uint32_t *)CONFIG_ARCH_CONFIGSTRING_RISCV;
	return (const char *)(uintptr_t)addr;
}
