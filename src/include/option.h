/* SPDX-License-Identifier: GPL-2.0-only */

#ifndef _OPTION_H_
#define _OPTION_H_

#include <types.h>

void sanitize_cmos(void);

#if CONFIG(OPTION_BACKEND_NONE)

static inline unsigned int get_uint_option(const char *name, const unsigned int fallback)
{
	return fallback;
}

static inline enum cb_err set_uint_option(const char *name, unsigned int value)
{
	return CB_CMOS_OTABLE_DISABLED;
}

#else /* !OPTION_BACKEND_NONE */

unsigned int get_uint_option(const char *name, const unsigned int fallback);
enum cb_err set_uint_option(const char *name, unsigned int value);

#endif /* OPTION_BACKEND_NONE? */

#endif /* _OPTION_H_ */
