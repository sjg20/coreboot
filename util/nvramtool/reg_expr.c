/*****************************************************************************\
 * reg_expr.c
 *****************************************************************************
 *  Please also read the file DISCLAIMER which is included in this software
 *  distribution.
 *
 *  This program is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License (as published by the
 *  Free Software Foundation) version 2, dated June 1991.
 *
 *  This program is distributed in the hope that it will be useful, but
 *  WITHOUT ANY WARRANTY; without even the IMPLIED WARRANTY OF
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the terms and
 *  conditions of the GNU General Public License for more details.
\*****************************************************************************/

#include <stdarg.h>
#include "common.h"
#include "reg_expr.h"

/****************************************************************************
 * compile_reg_expr
 *
 * Compile a regular expression.
 ****************************************************************************/
void compile_reg_expr(int cflags, const char *expr, regex_t *reg)
{
	static const size_t ERROR_BUF_SIZE = 256;
	char error_msg[ERROR_BUF_SIZE];
	int result;

	if ((result = regcomp(reg, expr, cflags)) != 0) {
		regerror(result, reg, error_msg, ERROR_BUF_SIZE);
		fprintf(stderr, "%s: %s\n", prog_name, error_msg);
		exit(1);
	}
}
