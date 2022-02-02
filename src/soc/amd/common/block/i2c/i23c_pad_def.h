/* SPDX-License-Identifier: GPL-2.0-only */

#ifndef AMD_BLOCK_I23C_PAD_DEF_H
#define AMD_BLOCK_I23C_PAD_DEF_H

#include <types.h>

/* MISC_I2Cx_PAD_CTRL and MISC_I23Cx_PAD_CTRL are in the same place, but have different bit
   definitions. Which one is present depends on the SoC. */
#define MISC_I23C0_PAD_CTRL		0xd8
#define MISC_I23C_PAD_CTRL(bus)		(MISC_I23C0_PAD_CTRL + 4 * (bus))

#define   I23C_PAD_CTRL_OD_RP_SW_MASK	(BIT(0) | BIT(1) | BIT(2) | BIT(3))
#define     I23C_PAD_CTRL_OD_RP_SW_SHIFT	0
#define   I23C_PAD_CTRL_RX_SEL_MASK		(BIT(4) | BIT(5))
#define     I23C_PAD_CTRL_RX_SHIFT		4
#define     I23C_PAD_CTRL_RX_SEL_OFF		(0 << I23C_PAD_CTRL_RX_SHIFT)
#define     I23C_PAD_CTRL_RX_SEL_ON		(3 << I23C_PAD_CTRL_RX_SHIFT)
#define   I23C_PAD_CTRL_SLEW_N_MASK		(BIT(6) | BIT(7))
#define     I23C_PAD_CTRL_SLEW_N_SHIFT		7
#define     I23C_PAD_CTRL_SLEW_N_DIS		(0 << I23C_PAD_CTRL_SLEW_N_SHIFT)
#define     I23C_PAD_CTRL_SLEW_N_FAST		(3 << I23C_PAD_CTRL_SLEW_N_SHIFT)
#define   I23C_PAD_CTRL_FALLSLEW_SEL_MASK	(BIT(8) | BIT(9))
#define     I23C_PAD_CTRL_FALLSLEW_SEL_SHIFT	8
#define     I23C_PAD_CTRL_FALLSLEW_SEL_STD	(0 << I23C_PAD_CTRL_FALLSLEW_SEL_SHIFT)
#define     I23C_PAD_CTRL_FALLSLEW_SEL_LOW	(3 << I23C_PAD_CTRL_FALLSLEW_SEL_SHIFT)
#define   I23C_PAD_CTRL_SPIKE_RC_EN_MASK	(BIT(10) | BIT(11))
#define     I23C_PAD_CTRL_SPIKE_RC_EN_SHIFT	10
#define     I23C_PAD_CTRL_SPIKE_RC_DIS		(0 << I23C_PAD_CTRL_SPIKE_RC_EN_SHIFT)
#define     I23C_PAD_CTRL_SPIKE_RC_EN		(3 << I23C_PAD_CTRL_SPIKE_RC_EN_SHIFT)
#define   I23C_PAD_CTRL_CAP_DOWN		BIT(12)
#define   I23C_PAD_CTRL_CAP_UP			BIT(13)
#define   I23C_PAD_CTRL_RES_DOWN		BIT(14)
#define   I23C_PAD_CTRL_RES_UP			BIT(15)
#define   I23C_PAD_CTRL_BIAS_CRT_EN_MASK	(BIT(16) | BIT(17))
#define     I23C_PAD_CTRL_BIAS_CRT_EN_SHIFT	16
#define     I23C_PAD_CTRL_BIAS_CRT_DIS		(0 << I23C_PAD_CTRL_BIAS_CRT_EN_SHIFT)
#define     I23C_PAD_CTRL_BIAS_CRT_EN		(3 << I23C_PAD_CTRL_BIAS_CRT_EN_SHIFT)
#define   I23C_PAD_CTRL_SPARE0			BIT(18)
#define   I23C_PAD_CTRL_SPARE1			BIT(19)
#define   I23C_PAD_CTRL_COMP_SEL0		BIT(20) /* unused */
#define   I23C_PAD_CTRL_COMP_SEL1		BIT(21) /* unused */
#define   I23C_PAD_CTRL_RES_BIAS_EN_MASK	(BIT(22) | BIT(23))
#define     I23C_PAD_CTRL_RES_BIAS_EN_SHIFT	22
#define     I23C_PAD_CTRL_RES_BIAS_T_COMP	(0 << I23C_PAD_CTRL_RES_BIAS_EN_SHIFT)
#define     I23C_PAD_CTRL_RES_BIAS_CONST_GM	(3 << I23C_PAD_CTRL_RES_BIAS_EN_SHIFT)
#define   I23C_PAD_CTRL_SLEW_P_MASK		(BIT(24) | BIT(25))
#define     I23C_PAD_CTRL_SLEW_P_SHIFT		24
#define     I23C_PAD_CTRL_SLEW_P_DIS		(0 << I23C_PAD_CTRL_SLEW_P_SHIFT)
#define     I23C_PAD_CTRL_SLEW_P_EN		(3 << I23C_PAD_CTRL_SLEW_P_SHIFT)
#define   I23C_PAD_CTRL_MODE_I3C_I2C_MASK	(BIT(26) | BIT(27))
#define     I23C_PAD_CTRL_MODE_I3C_I2C_SHIFT	26
#define     I23C_PAD_CTRL_MODE_I2C		(0 << I23C_PAD_CTRL_MODE_I3C_I2C_SHIFT)
#define     I23C_PAD_CTRL_MODE_I3C		(3 << I23C_PAD_CTRL_MODE_I3C_I2C_SHIFT)
#define   I23C_PAD_CTRL_MODE_1_8V_1_1V_MASK	(BIT(28) | BIT(29))
#define     I23C_PAD_CTRL_MODE_1_8V_1_1V_SHIFT	28
#define     I23C_PAD_CTRL_MODE_1_1V		(0 << I23C_PAD_CTRL_MODE_1_8V_1_1V_SHIFT)
#define     I23C_PAD_CTRL_MODE_1_8V		(3 << I23C_PAD_CTRL_MODE_1_8V_1_1V_SHIFT)
#define   I23C_PAD_CTRL_SPIKE_C_SEL_MASK	(BIT(30) | BIT(31))
#define     I23C_PAD_CTRL_SPIKE_C_SEL_SHIFT	30
#define     I23C_PAD_CTRL_SPIKE_C_SEL_DIS	(0 << I23C_PAD_CTRL_SPIKE_C_SEL_SHIFT)
#define     I23C_PAD_CTRL_SPIKE_C_SEL_EN	(3 << I23C_PAD_CTRL_SPIKE_C_SEL_SHIFT)

#endif /* AMD_BLOCK_I23C_PAD_DEF_H */
