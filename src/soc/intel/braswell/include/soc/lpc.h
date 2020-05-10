/* SPDX-License-Identifier: GPL-2.0-only */

#ifndef _SOC_LPC_H_
#define _SOC_LPC_H_

/* PCI config registers in LPC bridge. */
#define REVID		0x08
#define ABASE		0x40
#define PBASE		0x44
#define GBASE		0x48
#define IOBASE		0x4c
#define IBASE		0x50
#define SBASE		0x54
#define MPBASE		0x58
#define PUBASE		0x5c
#define UART_CONT	0x80
#define RCBA		0xf0

/* iLB Memory Mapped IO */
#define ILB_OIC		0x60
#define  SIRQEN		(1 << 12)

/* Memory Mapped IO in LPC bridge */
#define SCNT		0x10
#define SCNT_MODE	(1 << 7) /* When cleared, SERIRQ is in quiet mode */

#define RID_A_STEPPING_START 1
#define RID_B_STEPPING_START 5
#define RID_C_STEPPING_START 0x21
#define RID_D_STEPPING_START 0x35
enum soc_stepping {
	STEP_A0,
	STEP_A1,
	STEP_B0,
	STEP_B1,
	STEP_B2,
	STEP_B3,
	STEP_C0,
	STEP_D1,
};

/* Registers behind the RCBA_BASE_ADDRESS bar. */
#define GCS		0x00
# define BILD		(1 << 0)

#endif /* _SOC_LPC_H_ */
