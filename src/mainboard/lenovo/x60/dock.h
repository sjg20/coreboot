/* SPDX-License-Identifier: GPL-2.0-only */
/* This file is part of the coreboot project. */

#ifndef THINKPAD_X60_DOCK_H
#define THINKPAD_X60_DOCK_H

int dock_connect(void);
void dock_disconnect(void);
int dock_present(void);
int dlpc_init(void);
int dock_ultrabay_device_present(void);
#endif
