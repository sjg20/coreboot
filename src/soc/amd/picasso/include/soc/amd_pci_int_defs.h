/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2014 Sage Electronic Engineering, LLC.
 * Copyright (C) 2019 Advanced Micro Devices, Inc.
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

#ifndef __AMD_PCI_INT_DEFS_H__
#define __AMD_PCI_INT_DEFS_H__

/*
 * PIRQ and device routing - these define the index into the
 * FCH PCI_INTR 0xC00/0xC01 interrupt routing table.
 */
/*
 * PIRQ and device routing - these define the index into the
 * FCH PCI_INTR 0xC00/0xC01 interrupt routing table.
 */
#define PIRQ_NC		0x1f	/* Not Used */
#define PIRQ_A		0x00	/* INT A */
#define PIRQ_B		0x01	/* INT B */
#define PIRQ_C		0x02	/* INT C */
#define PIRQ_D		0x03	/* INT D */
#define PIRQ_E		0x04	/* INT E */
#define PIRQ_F		0x05	/* INT F */
#define PIRQ_G		0x06	/* INT G */
#define PIRQ_H		0x07	/* INT H */
#define PIRQ_MISC	0x08	/* Miscellaneous IRQ Settings */
#define PIRQ_MISC0	0x09	/* Miscellaneous0 IRQ Settings */
#define PIRQ_MISC1	0x0a	/* Miscellaneous1 IRQ Settings */
#define PIRQ_MISC2	0x0b	/* Miscellaneous2 IRQ Settings */
#define PIRQ_SIRQA	0x0c	/* Serial IRQ INTA */
#define PIRQ_SIRQB	0x0d	/* Serial IRQ INTB */
#define PIRQ_SIRQC	0x0e	/* Serial IRQ INTC */
#define PIRQ_SIRQD	0x0f	/* Serial IRQ INTD */
#define PIRQ_SCI	0x10	/* SCI IRQ */
#define PIRQ_SMBUS	0x11	/* SMBUS */
#define PIRQ_ASF	0x12	/* ASF */
/* 0x13-0x15 reserved */
#define PIRQ_PMON	0x16	/* Performance Monitor */
#define PIRQ_SD		0x17	/* SD */
#define PIRQ_SDIO	0x1a	/* SDIO */
/* 0x1b-0x1f reserved */
#define PIRQ_CIR	0x20	/* CIR, no IRQ connected */
#define PIRQ_GPIOA	0x21	/* GPIOa from PAD_FANIN0 */
#define PIRQ_GPIOB	0x22	/* GPIOb from PAD_FANOUT0 */
#define PIRQ_GPIOC	0x23	/* GPIOc no IRQ connected */
/* 0x24-0x48 reserved */
#define PIRQ_SATA	0x41	/* SATA */
/* 0x42 reserved */
#define PIRQ_EMMC	0x43	/* eMMC */
/* 0x44-0x4f reserved */
#define PIRQ_GPP0	0x50	/* GPPInt0 */
#define PIRQ_GPP1	0x51	/* GPPInt1 */
#define PIRQ_GPP2	0x52	/* GPPInt2 */
#define PIRQ_GPP3	0x53	/* GPPInt3 */
/* 0x54-0x61 reserved */
#define PIRQ_GPIO	0x62	/* GPIO Controller Interrupt */
/* 0x63-0x6f reserved */
#define PIRQ_I2C0	0x70	/* I2C0 */
#define PIRQ_I2C1	0x71	/* I2C1 */
#define PIRQ_I2C2	0x72	/* I2C2 */
#define PIRQ_I2C3	0x73	/* I2C3 */
#define PIRQ_UART0	0x74	/* UART0 */
#define PIRQ_UART1	0x75	/* UART1 */
#define PIRQ_I2C4	0x76	/* I2C4 */
#define PIRQ_I2C5	0x77	/* I2C5 */
#define PIRQ_UART2	0x78	/* UART2 */
#define PIRQ_UART3	0x79	/* UART3 */
/* 0x7a-0x7f reserved */

#endif /* __AMD_PCI_INT_DEFS_H__ */
