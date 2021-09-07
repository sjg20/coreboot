/* SPDX-License-Identifier: GPL-2.0-only */

#ifndef SOC_MEDIATEK_COMMON_TRACKER_H
#define SOC_MEDIATEK_COMMON_TRACKER_H

#define BUS_DBG_CON			0x000
#define BUS_DBG_TIMER_CON0		0x004
#define BUS_DBG_TIMER_CON1		0x008
#define BUS_TRACE_CON_1			0x900
#define BUS_TRACE_CON_AO_1		0x9FC
#define BUS_TRACE_CON_2			0xA00
#define BUS_TRACE_CON_AO_2		0xAFC
#define BUS_TRACE_EN			16

#define SYS_TRACK_ENTRY			64
#define INFRA_ENTRY_NUM			32
#define PERI_ENTRY_NUM			16

#define AR_TRACK_OFFSET			0x0100
#define AW_TRACK_OFFSET			0x0300

#define BUSTRACKER_TIMEOUT		0x300

#define BUS_DBG_CON_IRQ_AR_STA0		0x00000100
#define BUS_DBG_CON_IRQ_AW_STA0		0x00000200
#define BUS_DBG_CON_IRQ_AR_STA1		0x00100000
#define BUS_DBG_CON_IRQ_AW_STA1		0x00200000
#define BUS_DBG_CON_TIMEOUT		(BUS_DBG_CON_IRQ_AR_STA0 | BUS_DBG_CON_IRQ_AW_STA0 | \
					 BUS_DBG_CON_IRQ_AR_STA1 | BUS_DBG_CON_IRQ_AW_STA1)

enum {
	TRACKER_SYSTRACKER = 0,
	TRACKER_INFRATRACKER,
	TRACKER_PERISYSTRACKER,
	TRACKER_NUM,
};

void bustracker_init(void);

#endif
