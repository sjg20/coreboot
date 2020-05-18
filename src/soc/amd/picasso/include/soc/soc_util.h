/* SPDX-License-Identifier: GPL-2.0-only */

enum socket_type {
	SOCKET_FP5 = 0,
	SOCKET_AM4 = 2,
	SOCKET_FT5 = 3,
};

void print_socket_type(void);

int soc_is_pollock(void);
int soc_is_dali(void);
int soc_is_picasso(void);
int soc_is_raven2(void);
int soc_is_zen_plus(void);
