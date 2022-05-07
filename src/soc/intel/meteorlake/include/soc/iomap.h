/* SPDX-License-Identifier: GPL-2.0-only */

#ifndef _SOC_METEORLAKE_IOMAP_H_
#define _SOC_METEORLAKE_IOMAP_H_

#include <soc/pcr_ids.h>

/*
 * Memory-mapped I/O registers.
 */
#define PCH_PRESERVED_BASE_ADDRESS	0xfd800000
#define PCH_PRESERVED_BASE_SIZE	0x01000000

#define MCH_BASE_ADDRESS	0xfedc0000
#define MCH_BASE_SIZE		0x20000

#define DMI_BASE_ADDRESS	0xfeda0000
#define DMI_BASE_SIZE		0x1000

#define EP_BASE_ADDRESS		0xfeda1000
#define EP_BASE_SIZE		0x1000

#define EDRAM_BASE_ADDRESS	0xfed80000
#define EDRAM_BASE_SIZE		0x4000

#define HPET_BASE_ADDRESS	0xfed00000

#define PCH_PWRM_BASE_ADDRESS	0xfe000000
#define PCH_PWRM_BASE_SIZE	0x10000

#define GPIO_BASE_SIZE		0x10000

#define HECI1_BASE_ADDRESS	0xfeda2000

#define VTD_BASE_ADDRESS	0xfc800000
#define VTD_BASE_SIZE		0x00002000

#define GFXVT_BASE_ADDRESS	0xfc800000
#define GFXVT_BASE_SIZE		0x1000

#define VTVC0_BASE_ADDRESS	0xfc801000
#define VTVC0_BASE_SIZE		0x1000

#define UART_BASE_SIZE		0x1000
#define UART_BASE_0_ADDRESS	0xfe03e000
/* Both UART BAR 0 and 1 are 4KB in size */
#define UART_BASE_0_ADDR(x)	(UART_BASE_0_ADDRESS + (2 * \
					UART_BASE_SIZE * (x)))
#define UART_BASE(x)		UART_BASE_0_ADDR(x)

#define EARLY_GSPI_BASE_ADDRESS 0xfe030000

#define EARLY_I2C_BASE_ADDRESS	0xfe020000
#define EARLY_I2C_BASE(x)	(EARLY_I2C_BASE_ADDRESS + (0x2000 * (x)))

#define SPI_BASE_ADDRESS	0xfe010000

#define REG_BASE_ADDRESS	0xd0000000
#define REG_BASE_SIZE		(256 * MiB)

#define P2SB_BAR		CONFIG_PCR_BASE_ADDRESS
#define P2SB_SIZE		(16 * MiB)

#define IOE_PCR_ABOVE_4G_BASE_ADDR	0x3fff0000000
#define IOE_P2SB_BAR		IOE_PCR_ABOVE_4G_BASE_ADDR
#define IOE_P2SB_SIZE		(256 * MiB)

#define IOM_BASE_ADDR		0x3fff0aa0000
#define IOM_BASE_SIZE		0x1600
#define IOM_BASE_ADDR_MAX	0x3fff0aa15ff

/*
 * I/O port address space
 */
#define ACPI_BASE_ADDRESS	0x1800
#define ACPI_BASE_SIZE		0x100

#define TCO_BASE_ADDRESS	0x400
#define TCO_BASE_SIZE		0x20
#endif
