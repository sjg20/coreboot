/* SPDX-License-Identifier: GPL-2.0-only */
/* This file is part of the coreboot project. */

#ifndef __MAINBOARD_GOOGLE_FOSTER_PMIC_H__
#define __MAINBOARD_GOOGLE_FOSTER_PMIC_H__

#include <stdint.h>

#define MAX77620_SD0_REG		0x16
#define MAX77620_SD1_REG		0x17
#define MAX77620_SD2_REG		0x18
#define MAX77620_SD3_REG		0x19
#define MAX77620_VDVSSD0_REG		0x1B
#define MAX77620_CNFG2SD_REG		0x22

#define MAX77620_CNFG1_L0_REG		0x23
#define MAX77620_CNFG2_L0_REG		0x24
#define MAX77620_CNFG1_L1_REG		0x25
#define MAX77620_CNFG2_L1_REG		0x26
#define MAX77620_CNFG1_L2_REG		0x27
#define MAX77620_CNFG2_L2_REG		0x28
#define MAX77620_CNFG1_L3_REG		0x29
#define MAX77620_CNFG2_L3_REG		0x2A
#define MAX77620_CNFG1_L4_REG		0x2B
#define MAX77620_CNFG2_L4_REG		0x2C
#define MAX77620_CNFG1_L5_REG		0x2D
#define MAX77620_CNFG2_L5_REG		0x2E
#define MAX77620_CNFG1_L6_REG		0x2F
#define MAX77620_CNFG2_L6_REG		0x30
#define MAX77620_CNFG1_L7_REG		0x31
#define MAX77620_CNFG2_L7_REG		0x32
#define MAX77620_CNFG1_L8_REG		0x33
#define MAX77620_CNFG2_L8_REG		0x34
#define MAX77620_CNFG3_LDO_REG		0x35

#define MAX77620_GPIO0_REG		0x36
#define MAX77620_GPIO1_REG		0x37
#define MAX77620_GPIO2_REG		0x38
#define MAX77620_GPIO3_REG		0x39
#define MAX77620_GPIO4_REG		0x3A
#define MAX77620_GPIO5_REG		0x3B
#define MAX77620_GPIO6_REG		0x3C
#define MAX77620_GPIO7_REG		0x3D
#define MAX77620_GPIO_PUE_GPIO		0x3E
#define MAX77620_GPIO_PDE_GPIO		0x3F

#define MAX77620_AME_GPIO		0x40
#define MAX77620_REG_ONOFF_CFG1		0x41
#define MAX77620_REG_ONOFF_CFG2		0x42

#define MAX77620_CID0_REG		0x58
#define MAX77620_CID1_REG		0x59
#define MAX77620_CID2_REG		0x5A
#define MAX77620_CID3_REG		0x5B
#define MAX77620_CID4_REG		0x5C
#define MAX77620_CID5_REG		0x5D

#define MAX77621_VOUT_REG		0x00
#define MAX77621_VOUT_DVC_REG		0x01
#define MAX77621_CONTROL1_REG		0x02
#define MAX77621_CONTROL2_REG		0x03

void pmic_init(unsigned int bus);
void pmic_write_reg_77620(unsigned int bus, uint8_t reg, uint8_t val,
					int delay);

#endif /* __MAINBOARD_GOOGLE_FOSTER_PMIC_H__ */
