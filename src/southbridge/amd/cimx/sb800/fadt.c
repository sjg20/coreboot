/* SPDX-License-Identifier: GPL-2.0-only */


/*
 * ACPI - create the Fixed ACPI Description Tables (FADT)
 */


#include <string.h>
#include <console/console.h>
#include <acpi/acpi.h>
#include <arch/io.h>
#include <device/device.h>
#include <version.h>

#include "SBPLATFORM.h"

#ifndef FADT_BOOT_ARCH
#if LEGACY_FREE
	#define FADT_BOOT_ARCH ACPI_FADT_LEGACY_FREE
#else
	#define FADT_BOOT_ARCH (ACPI_FADT_LEGACY_DEVICES | ACPI_FADT_8042)
#endif
#endif

#ifndef FADT_PM_PROFILE
	#define FADT_PM_PROFILE PM_UNSPECIFIED
#endif

/*
 * Reference section 5.2.9 Fixed ACPI Description Table (FADT)
 * in the ACPI 3.0b specification.
 */
void acpi_create_fadt(acpi_fadt_t * fadt, acpi_facs_t * facs, void *dsdt)
{
	u16 val = 0;
	acpi_header_t *header = &(fadt->header);

	printk(BIOS_DEBUG, "ACPI_BLK_BASE: 0x%04x\n", ACPI_BLK_BASE);

	/* Prepare the header */
	memset((void *)fadt, 0, sizeof(acpi_fadt_t));
	memcpy(header->signature, "FACP", 4);
	header->length = sizeof(acpi_fadt_t);
	header->revision = get_acpi_table_revision(FADT);
	memcpy(header->oem_id, OEM_ID, 6);
	memcpy(header->oem_table_id, ACPI_TABLE_CREATOR, 8);
	memcpy(header->asl_compiler_id, ASLC, 4);
	header->asl_compiler_revision = asl_revision;

	if ((uintptr_t)facs > 0xffffffff)
		printk(BIOS_DEBUG, "ACPI: FACS lives above 4G\n");
	else
		fadt->firmware_ctrl = (uintptr_t)facs;

	if ((uintptr_t)dsdt > 0xffffffff)
		printk(BIOS_DEBUG, "ACPI: DSDT lives above 4G\n");
	else
		fadt->dsdt = (uintptr_t)dsdt;

	fadt->reserved = 0;		/* reserved, should be 0 ACPI 3.0 */
	fadt->preferred_pm_profile = FADT_PM_PROFILE;
	fadt->sci_int = 9;		/* HUDSON 1 - IRQ 09 - ACPI SCI */

	val = PM1_EVT_BLK_ADDRESS;
	WritePMIO(SB_PMIOA_REG60, AccWidthUint16, &val);
	val = PM1_CNT_BLK_ADDRESS;
	WritePMIO(SB_PMIOA_REG62, AccWidthUint16, &val);
	val = PM1_TMR_BLK_ADDRESS;
	WritePMIO(SB_PMIOA_REG64, AccWidthUint16, &val);
	val = GPE0_BLK_ADDRESS;
	WritePMIO(SB_PMIOA_REG68, AccWidthUint16, &val);

	/* CpuControl is in \_PR.CP00, 6 bytes */
	val = CPU_CNT_BLK_ADDRESS;
	WritePMIO(SB_PMIOA_REG66, AccWidthUint16, &val);
	val = 0;
	WritePMIO(SB_PMIOA_REG6A, AccWidthUint16, &val);
	val = ACPI_PMA_CNT_BLK_ADDRESS;
	WritePMIO(SB_PMIOA_REG6E, AccWidthUint16, &val);

	/* AcpiDecodeEnable, When set, SB uses the contents of the
	 * PM registers at index 60-6B to decode ACPI I/O address.
	 * AcpiSmiEn & SmiCmdEn*/
	val = BIT0 | BIT1 | BIT2 | BIT4;
	WritePMIO(SB_PMIOA_REG74, AccWidthUint16, &val);

	/* RTC_En_En, TMR_En_En, GBL_EN_EN */
	outl(0x1, PM1_CNT_BLK_ADDRESS);		  /* set SCI_EN */
	fadt->pm1a_evt_blk = PM1_EVT_BLK_ADDRESS;
	fadt->pm1b_evt_blk = 0x0000;
	fadt->pm1a_cnt_blk = PM1_CNT_BLK_ADDRESS;
	fadt->pm1b_cnt_blk = 0x0000;
	fadt->pm2_cnt_blk = ACPI_PMA_CNT_BLK_ADDRESS;
	fadt->pm_tmr_blk = PM1_TMR_BLK_ADDRESS;
	fadt->gpe0_blk = GPE0_BLK_ADDRESS;
	fadt->gpe1_blk = 0;		/* No gpe1 block in hudson1 */

	fadt->pm1_evt_len = 4;	/* 32 bits */
	fadt->pm1_cnt_len = 2;	/* 16 bits */
	fadt->pm2_cnt_len = 1;	/* 8 bits */
	fadt->pm_tmr_len = 4;	/* 32 bits */
	fadt->gpe0_blk_len = 8;	/* 64 bits */
	fadt->gpe1_blk_len = 0;
	fadt->gpe1_base = 0;

	fadt->p_lvl2_lat = ACPI_FADT_C2_NOT_SUPPORTED;
	fadt->p_lvl3_lat = ACPI_FADT_C3_NOT_SUPPORTED;
	fadt->flush_size = 0;	/* set to 0 if WBINVD is 1 in flags */
	fadt->flush_stride = 0;	/* set to 0 if WBINVD is 1 in flags */
	fadt->duty_offset = 1;	/* CLK_VAL bits 3:1 */
	fadt->duty_width = 3;	/* CLK_VAL bits 3:1 */
	fadt->day_alrm = 0;	/* 0x7d these have to be */
	fadt->mon_alrm = 0;	/* 0x7e added to cmos.layout */
	fadt->century = 0;	/* 0x7f to make rtc alarm work */
	fadt->iapc_boot_arch = FADT_BOOT_ARCH;	/* See table 5-10 */
	fadt->res2 = 0;		/* reserved, MUST be 0 ACPI 3.0 */
	fadt->flags = ACPI_FADT_WBINVD | /* See table 5-10 ACPI 3.0a spec */
				ACPI_FADT_C1_SUPPORTED |
				ACPI_FADT_SLEEP_BUTTON |
				ACPI_FADT_S4_RTC_WAKE |
				ACPI_FADT_32BIT_TIMER |
				ACPI_FADT_RESET_REGISTER |
				ACPI_FADT_PCI_EXPRESS_WAKE |
				ACPI_FADT_S4_RTC_VALID |
				ACPI_FADT_REMOTE_POWER_ON;

	/* Format is from 5.2.3.1: Generic Address Structure */
	/* reset_reg: see section 4.7.3.6 ACPI 3.0a spec */
	/* 8 bit write of value 0x06 to 0xCF9 in IO space */
	fadt->reset_reg.space_id = ACPI_ADDRESS_SPACE_IO;
	fadt->reset_reg.bit_width = 8;
	fadt->reset_reg.bit_offset = 0;
	fadt->reset_reg.access_size = ACPI_ACCESS_SIZE_BYTE_ACCESS;
	fadt->reset_reg.addrl = 0xcf9;
	fadt->reset_reg.addrh = 0x0;
	fadt->reset_value = 6;

	fadt->ARM_boot_arch = 0;	/* MUST be 0 ACPI 3.0 */
	fadt->FADT_MinorVersion = 0;	/* MUST be 0 ACPI 3.0 */

	fadt->x_firmware_ctl_l = ((uintptr_t)facs) & 0xffffffff;
	fadt->x_firmware_ctl_h = ((uint64_t)(uintptr_t)facs) >> 32;
	fadt->x_dsdt_l = ((uintptr_t)dsdt) & 0xffffffff;
	fadt->x_dsdt_h = ((uint64_t)(uintptr_t)dsdt) >> 32;

	fadt->x_pm1a_evt_blk.space_id = ACPI_ADDRESS_SPACE_IO;
	fadt->x_pm1a_evt_blk.bit_width = 32;
	fadt->x_pm1a_evt_blk.bit_offset = 0;
	fadt->x_pm1a_evt_blk.access_size = ACPI_ACCESS_SIZE_WORD_ACCESS;
	fadt->x_pm1a_evt_blk.addrl = PM1_EVT_BLK_ADDRESS;
	fadt->x_pm1a_evt_blk.addrh = 0x0;

	fadt->x_pm1b_evt_blk.space_id = ACPI_ADDRESS_SPACE_IO;
	fadt->x_pm1b_evt_blk.bit_width = 0;
	fadt->x_pm1b_evt_blk.bit_offset = 0;
	fadt->x_pm1b_evt_blk.access_size = 0;
	fadt->x_pm1b_evt_blk.addrl = 0x0;
	fadt->x_pm1b_evt_blk.addrh = 0x0;


	fadt->x_pm1a_cnt_blk.space_id = ACPI_ADDRESS_SPACE_IO;
	fadt->x_pm1a_cnt_blk.bit_width = 16;
	fadt->x_pm1a_cnt_blk.bit_offset = 0;
	fadt->x_pm1a_cnt_blk.access_size = 0;
	fadt->x_pm1a_cnt_blk.addrl = PM1_CNT_BLK_ADDRESS;
	fadt->x_pm1a_cnt_blk.addrh = 0x0;

	fadt->x_pm1b_cnt_blk.space_id = ACPI_ADDRESS_SPACE_IO;
	fadt->x_pm1b_cnt_blk.bit_width = 0;
	fadt->x_pm1b_cnt_blk.bit_offset = 0;
	fadt->x_pm1b_cnt_blk.access_size = 0;
	fadt->x_pm1b_cnt_blk.addrl = 0x0;
	fadt->x_pm1b_cnt_blk.addrh = 0x0;


	fadt->x_pm2_cnt_blk.space_id = ACPI_ADDRESS_SPACE_IO;
	fadt->x_pm2_cnt_blk.bit_width = 8;	/* Hudson 1 Pm2Control is 8 bits */
	fadt->x_pm2_cnt_blk.bit_offset = 0;
	fadt->x_pm2_cnt_blk.access_size = ACPI_ACCESS_SIZE_BYTE_ACCESS;
	fadt->x_pm2_cnt_blk.addrl = ACPI_PMA_CNT_BLK_ADDRESS;
	fadt->x_pm2_cnt_blk.addrh = 0x0;


	fadt->x_pm_tmr_blk.space_id = ACPI_ADDRESS_SPACE_IO;
	fadt->x_pm_tmr_blk.bit_width = 32;
	fadt->x_pm_tmr_blk.bit_offset = 0;
	fadt->x_pm_tmr_blk.access_size = ACPI_ACCESS_SIZE_DWORD_ACCESS;
	fadt->x_pm_tmr_blk.addrl = PM1_TMR_BLK_ADDRESS;
	fadt->x_pm_tmr_blk.addrh = 0x0;


	fadt->x_gpe0_blk.space_id = ACPI_ADDRESS_SPACE_IO;
	fadt->x_gpe0_blk.bit_width = 64; /* EventStatus + Event Enable */
	fadt->x_gpe0_blk.bit_offset = 0;
	fadt->x_gpe0_blk.access_size = ACPI_ACCESS_SIZE_DWORD_ACCESS;
	fadt->x_gpe0_blk.addrl = GPE0_BLK_ADDRESS;
	fadt->x_gpe0_blk.addrh = 0x0;


	fadt->x_gpe1_blk.space_id = ACPI_ADDRESS_SPACE_IO;
	fadt->x_gpe1_blk.bit_width = 0;
	fadt->x_gpe1_blk.bit_offset = 0;
	fadt->x_gpe1_blk.access_size = 0;
	fadt->x_gpe1_blk.addrl = 0;
	fadt->x_gpe1_blk.addrh = 0x0;

	header->checksum = acpi_checksum((void *)fadt, sizeof(acpi_fadt_t));

}
