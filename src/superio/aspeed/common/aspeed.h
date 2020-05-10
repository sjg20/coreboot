/* SPDX-License-Identifier: GPL-2.0-or-later */

#ifndef SUPERIO_ASPEED_COMMON_ROMSTAGE_H
#define SUPERIO_ASPEED_COMMON_ROMSTAGE_H

#include <device/pnp_type.h>
#include <stdint.h>

/* AST2300/2400/2500/2600 use the same memory base */
#define ASPEED_MEM_BASE1 0x1E6E0000
#define ASPEED_MMC_BASE      (ASPEED_MEM_BASE1)
#define ASPEED_USB_BASE      (ASPEED_MEM_BASE1 + 0x1000)
#define ASPEED_SCU_BASE      (ASPEED_MEM_BASE1 + 0x2000)
#define ASPEED_HACE_BASE     (ASPEED_MEM_BASE1 + 0x3000)
#define ASPEED_JTAG_BASE     (ASPEED_MEM_BASE1 + 0x4000)
#define ASPEED_GFX_BASE      (ASPEED_MEM_BASE1 + 0x6000)
#define ASPEED_X_DMA_BASE    (ASPEED_MEM_BASE1 + 0x7000)
#define ASPEED_MCTP_BASE     (ASPEED_MEM_BASE1 + 0x8000)
#define ASPEED_ADC_BASE      (ASPEED_MEM_BASE1 + 0x9000)
#define ASPEED_LPC_PLUS_BASE (ASPEED_MEM_BASE1 + 0xC000)
#define ASPEED_PCIE_BASE     (ASPEED_MEM_BASE1 + 0xD000)
#define ASPEED_ESPI_BASE     (ASPEED_MEM_BASE1 + 0xE000)
#define ASPEED_BAT_BASE      (ASPEED_MEM_BASE1 + 0xF000)
#define ASPEED_MEM_BASE2 0x1E780000
#define ASPEED_GPIO_BASE    (ASPEED_MEM_BASE2)
#define ASPEED_RTC_BASE     (ASPEED_MEM_BASE2 + 0x1000)
#define ASPEED_TIMER_BASE   (ASPEED_MEM_BASE2 + 0x2000)
#define ASPEED_UART1_BASE   (ASPEED_MEM_BASE2 + 0x3000)
#define ASPEED_UART5_BASE   (ASPEED_MEM_BASE2 + 0x4000)
#define ASPEED_WDT_BASE     (ASPEED_MEM_BASE2 + 0x5000)
#define ASPEED_PWM_FAN_BASE (ASPEED_MEM_BASE2 + 0x6000)
#define ASPEED_VUART_BASE   (ASPEED_MEM_BASE2 + 0x7000)
#define ASPEED_PUART_BASE   (ASPEED_MEM_BASE2 + 0x8000)
#define ASPEED_LPC_BASE     (ASPEED_MEM_BASE2 + 0x9000)
#define ASPEED_I2C_BASE     (ASPEED_MEM_BASE2 + 0xA000)
#define ASPEED_PECI_BASE    (ASPEED_MEM_BASE2 + 0xB000)
#define ASPEED_APB2PCI_BASE (ASPEED_MEM_BASE2 + 0xC000)
#define ASPEED_UART2_BASE   (ASPEED_MEM_BASE2 + 0xD000)
#define ASPEED_UART3_BASE   (ASPEED_MEM_BASE2 + 0xE000)
#define ASPEED_UART4_BASE   (ASPEED_MEM_BASE2 + 0xF000)

/* System Control Unit */
#define PRO_KEY_REG 0x00
#define PRO_KEY_PASSWORD 0x1688A8A8
#define SYS_RESET_CTL_REG 0x04
#define CLK_SEL_REG 0x08
#define CLK_STOP_CTL_REG 0x0C
#define FRQ_CNT_CTL_REG 0x10
#define FRQ_CNT_CMP_REG 0x14
#define INT_CTL_STS_REG 0x18
#define D2_PLL_PARM_REG 0x1C
#define M_PLL_PARM_REG 0x20
#define H_PLL_PARM_REG 0x24
#define D_PLL_PARM_REG 0x28
#define MISC_CTL_REG 0x2C
#define PCI_CFG_SET_REG1 0x30
#define PCI_CFG_SET_REG2 0x34
#define PCI_CFG_SET_REG3 0x38
#define SYS_RESET_CTL_STS_REG 0x3C
#define VGA_FUNC_HANDSHAKE_REG1 0x40
#define VGA_FUNC_HANDSHAKE_REG2 0x44
#define MAC_CLK_DELAY_SET_REG 0x48
#define MISC_2_CTL_REG 0x4C
#define VGA_SCRATCH_REG1 0x50
#define VGA_SCRATCH_REG2 0x54
#define VGA_SCRATCH_REG3 0x58
#define VGA_SCRATCH_REG4 0x5C
#define VGA_SCRATCH_REG5 0x60
#define VGA_SCRATCH_REG6 0x64
#define VGA_SCRATCH_REG7 0x68
#define VGA_SCRATCH_REG8 0x6C
#define HW_STRAP_REG 0x70
#define RAN_NUM_GEN_CTL_REG 0x74
#define RAN_NUM_GEN_DATA_OUT_REG 0x78
#define SILICON_REV_ID_REG 0x7C
#define MUL_FUNC_PIN_CTL1_REG 0x80
#define UART3_TXD3_EN_BIT 22
#define UART3_RXD3_EN_BIT 23
#define UART4_TXD4_EN_BIT 30
#define UART4_RXD4_EN_BIT 31
#define MUL_FUNC_PIN_CTL2_REG 0x84
#define UART1_TXD1_EN_BIT 22
#define UART1_RXD1_EN_BIT 23
#define UART2_TXD2_EN_BIT 30
#define UART2_RXD2_EN_BIT 31
#define MUL_FUNC_PIN_CTL3_REG 0x88
#define MUL_FUNC_PIN_CTL4_REG 0x8C
#define MUL_FUNC_PIN_CTL5_REG 0x90
#define MUL_FUNC_PIN_CTL6_REG 0x94
#define DIGI_VIDEO_OUT_PINS_DIS 0
#define DIGI_VIDEO_OUT_PINS_EN 1
#define EXTRST_RESET_SEL_REG 0x9C
#define MUL_FUNC_PIN_CTL7_REG 0xA0
#define MUL_FUNC_PIN_CTL8_REG 0xA4
#define MUL_FUNC_PIN_CTL9_REG 0xA8
#define MUL_FUNC_PIN_CTL10_REG 0xAC
#define MAC_CLK_DELAY_100M_REG 0xB8
#define MAC_CLK_DELAY_10M_REG 0xBC
#define PWR_SAVE_WAKEUP_EN_REG 0xC0
#define PWR_SAVE_WAKEUP_CTL_REG 0xC4
#define SYS_RESET_CTL_SET2_REG 0xD4
#define CLK_SEL_SET2_REG 0xD8
#define CLK_STOP_CTL_SET2_REG 0xDC
#define SCU_FREE_RUN_CNT_READ_BACK_REG 0xE0
#define SCU_FREE_RUN_CNT_EXT_READ_BACK_REG 0xE4
#define CLK_DUTY_MEASURE_CTL_REG 0xE8
#define CLK_DUTY_MEASURE_RESULT_REG 0xEC
#define CPU2_CTL_REG 0x100
#define CPU2_BASE_ADDR_SEG_REG1 0x104
#define CPU2_BASE_ADDR_SEG_REG2 0x108
#define CPU2_BASE_ADDR_SEG_REG3 0x10C
#define CPU2_BASE_ADDR_SEG_REG4 0x110
#define CPU2_BASE_ADDR_SEG_REG5 0x114
#define CPU2_BASE_ADDR_SEG_REG6 0x118
#define CPU2_BASE_ADDR_SEG_REG7 0x11C
#define CPU2_BASE_ADDR_SEG_REG8 0x120
#define CPU2_BASE_ADDR_SEG_REG9 0x124
#define CPU2_CACHE_FUNC_CTL_REG 0x128
#define D_PLL_EXT_PARM_REG1 0x130
#define D_PLL_EXT_PARM_REG2 0x134
#define D_PLL_EXT_PARM_REG3 0x138
#define D2_PLL_EXT_PARM_REG1 0x13C
#define D2_PLL_EXT_PARM_REG2 0x140
#define D2_PLL_EXT_PARM_REG3 0x144
#define EXT_PARM_M_H_PLL_REG 0x148
#define CHIP_UNIQ_ID_L_REG 0x150
#define CHIP_UNIQ_ID_H_REG 0x154
#define GEN_UART_24M_H_PLL_REG 0x160
#define PCIE_CFG_SET_CTL_REG 0x180
#define BMC_MMIO_DECODE_SET_REG 0x184
#define FIRST_RELO_CTL_DECODE_AREA_LOCA_REG 0x188
#define SECOND_RELO_CTL_DECODE_AREA_LOCA_REG 0x18C
#define MAILBOX_DECODE_AREA_LOCA_REG 0x190
#define SHARED_SRAM_AREA_DECODE_LOCA_REG1 0x194
#define SHARED_SRAM_AREA_DECODE_LOCA_REG2 0x198
#define BMC_DEV_CLASS_CODE_REV_ID_REG 0x19C
#define BMC_DEV_ID_REG 0x1A4
#define CLK_DUTY_SEL_REG 0x1DC

/* LPC Controller */
#define HICR0_REG 0x00
#define HICR1_REG 0x04
#define HICR2_REG 0x08
#define HICR3_REG 0x0C
#define HICR4_REG 0x10
#define LADR3H_REG 0x14
#define LADR3L_REG 0x18
#define LADR12H_REG 0x1C
#define LADR12L_REG 0x20
#define IDR1_REG 0x24
#define IDR2_REG 0x28
#define IDR3_REG 0x2C
#define ODR1_REG 0x30
#define ODR2_REG 0x34
#define ODR3_REG 0x38
#define STR1_REG 0x3C
#define STR2_REG 0x40
#define STR3_REG 0x44
#define BTR0_REG 0x48
#define BRT1_REG 0x4C
#define BTCSR0_REG 0x50
#define BTCSR1_REG 0x54
#define BTCR_REG 0x58
#define BTDTR_REG 0x5C
#define BTIMSR_REG 0x60
#define BTFVSR0_REG 0x64
#define BTFVSR1_REG 0x68
#define SIRQCR0_REG 0x70
#define SIRQCR1_REG 0x74
#define SIRQCR2_REG 0x78
#define SIRQCR3_REG 0x7C
#define HICR5_REG 0x80
#define SNOOP_ADDR_EN 0
#define HICR6_REG 0x84
#define HICR7_REG 0x88
#define HICR8_REG 0x8C
#define SNPWADR_REG 0x90
#define SNOOP_ADDR_PORT80 0x80
#define SNPWDR_REG 0x94
#define HICR9_REG 0x98
#define HICRA_REG 0x9C
#define LHCR0_REG 0xA0
#define LHCR1_REG 0xA4
#define LHCR2_REG 0xA8
#define LHCR3_REG 0xAC
#define LHCR4_REG 0xB0
#define LHCR5_REG 0xB4
#define LHCR6_REG 0xB8
#define LHCR7_REG 0xBC
#define LHCR8_REG 0xC0
#define PCCR6_REG 0xC4
#define LHCRA_REG 0xC8
#define LHCRB_REG 0xCC
#define PCCR4_REG 0xD0
#define PCCR5_REG 0xD4
#define HICRB_REG 0x100
#define HICRC_REG 0x104
#define HISR0_REG 0x108
#define HISR1_REG 0x10C
#define LADR4_REG 0x110
#define IDR4_REG 0x114
#define ODR4_REG 0x118
#define STR4_REG 0x11C
#define LSADR12_REG 0x120
#define IDR5_REG 0x124
#define ODR5_REG 0x12C
#define PCCR0_REG 0x130
#define PCCR1_REG 0x134
#define PCCR2_REG 0x138
#define PCCR3_REG 0x13C
#define IBTCR0_REG 0x140
#define IBTCR1_REG 0x144
#define IBTCR2_REG 0x148
#define IBTCR3_REG 0x14C
#define IBTCR4_REG 0x150
#define IBTCR5_REG 0x154
#define IBTCR6_REG 0x158
#define SRUART1_REG 0x160
#define SRUART2_REG 0x164
#define SRUART3_REG 0x168
#define SRUART4_REG 0x16C
#define SCR0SIO_REG 0x170
#define SCR1SIO_REG 0x174
#define SCR2SIO_REG 0x178
#define SCR3SIO_REG 0x17C
#define SWCR_03_00_REG 0x180
#define SWCR_07_04_REG 0x184
#define SWCR_0B_08_REG 0x188
#define SWCR_0F_0C_REG 0x18C
#define SWCR_13_10_REG 0x190
#define SWCR_17_14_REG 0x194
#define SWCR_1B_18_REG 0x198
#define SWCR_1F_1C_REG 0x19C
#define ACPI_E3_E0_REG 0x1A0
#define ACPI_C1_C0_REG 0x1A4
#define ACPI_B3_B0_REG 0x1A8
#define ACPI_B7_B4_REG 0x1AC
#define MBXDAT_0_REG 0x200
#define MBXDAT_1_REG 0x204
#define MBXDAT_2_REG 0x208
#define MBXDAT_3_REG 0x20C
#define MBXDAT_4_REG 0x210
#define MBXDAT_5_REG 0x214
#define MBXDAT_6_REG 0x218
#define MBXDAT_7_REG 0x21C
#define MBXDAT_8_REG 0x220
#define MBXDAT_9_REG 0x224
#define MBXDAT_A_REG 0x228
#define MBXDAT_B_REG 0x22C
#define MBXDAT_C_REG 0x230
#define MBXDAT_D_REG 0x234
#define MBXDAT_E_REG 0x238
#define MBXDAT_F_REG 0x23C
#define MBXSTS_0_REG 0x240
#define MBXSTS_1_REG 0x244
#define MBXBCR_REG 0x248
#define MBXHCR_REG 0x24C
#define MBXBIE_0_REG 0x250
#define MBXBIE_1_REG 0x254
#define MBXHIE_0_REG 0x258
#define MBXHIE_1_REG 0x25C

/* GPIO Controller */
#define A_B_C_D_DATA_VALUE_REG 0x00
#define A_B_C_D_DIRECTION_REG 0x04
#define A_B_C_D_INT_EN_REG 0x08
#define A_B_C_D_INT_SEN_T0_REG 0x0C
#define A_B_C_D_INT_SEN_T1_REG 0x10
#define A_B_C_D_INT_SEN_T2_REG 0x14
#define A_B_C_D_INT_STS_REG 0x18
#define A_B_C_D_RESET_TOLE_REG 0x1C
#define E_F_G_H_DATA_VALUE_REG 0x20
#define E_F_G_H_DIRECTION_REG 0x24
#define E_F_G_H_INT_EN_REG 0x28
#define E_F_G_H_INT_SEN_T0_REG 0x2C
#define E_F_G_H_INT_SEN_T1_REG 0x30
#define E_F_G_H_INT_SEN_T2_REG 0x34
#define E_F_G_H_INT_STS_REG 0x38
#define E_F_G_H_RESET_TOLE_REG 0x3C
#define A_B_C_D_DEBOUNCE_SET_REG1 0x40
#define A_B_C_D_DEBOUNCE_SET_REG2 0x44
#define E_F_G_H_DEBOUNCE_SET_REG1 0x48
#define E_F_G_H_DEBOUNCE_SET_REG2 0x4C
#define DEBOUNCE_TIMER_SET_REG1 0x50
#define DEBOUNCE_TIMER_SET_REG2 0x54
#define DEBOUNCE_TIMER_SET_REG3 0x58
#define A_B_C_D_CMD_SOURCE0_REG 0x60
#define A_B_C_D_CMD_SOURCE1_REG 0x64
#define E_F_G_H_CMD_SOURCE0_REG 0x68
#define E_F_G_H_CMD_SOURCE1_REG 0x6C
#define I_J_K_L_DATA_VALUE_REG 0x70
#define I_J_K_L_DIRECTION_REG 0x74
#define M_N_O_P_DATA_VALUE_REG 0x78
#define M_N_O_P_DIRECTION_REG 0x7C
#define Q_R_S_T_DATA_VALUE_REG 0x80
#define Q_R_S_T_DIRECTION_REG 0x84
#define U_V_W_X_DATA_VALUE_REG 0x88
#define U_V_W_X_DIRECTION_REG 0x8C
#define I_J_K_L_CMD_SOURCE0_REG 0x90
#define I_J_K_L_CMD_SOURCE1_REG 0x94
#define I_J_K_L_INT_EN_REG 0x98
#define I_J_K_L_INT_SEN_T0_REG 0x9C
#define I_J_K_L_INT_SEN_T1_REG 0xA0
#define I_J_K_L_INT_SEN_T2_REG 0xA4
#define I_J_K_L_INT_STS_REG 0xA8
#define I_J_K_L_RESET_TOLE_REG 0xAC
#define I_J_K_L_DEBOUNCE_SET_REG1 0xB0
#define I_J_K_L_DEBOUNCE_SET_REG2 0xB4
#define I_J_K_L_INPUT_MASK 0xB8
#define A_B_C_D_DATA_READ_REG 0xC0
#define E_F_G_H_DATA_READ_REG 0xC4
#define I_J_K_L_DATA_READ_REG 0xC8
#define M_N_O_P_DATA_READ_REG 0xCC
#define Q_R_S_T_DATA_READ_REG 0xD0
#define U_V_W_X_DATA_READ_REG 0xD4
#define Y_Z_AA_AB_DATA_READ_REG 0xD8
#define AC_DATA_READ_REG 0xDC
#define M_N_O_P_CMD_SOURCE0_REG 0xE0
#define M_N_O_P_CMD_SOURCE1_REG 0xE4
#define M_N_O_P_INT_EN_REG 0xE8
#define M_N_O_P_INT_SEN_T0_REG 0xEC
#define M_N_O_P_INT_SEN_T1_REG 0xF0
#define M_N_O_P_INT_SEN_T2_REG 0xF4
#define M_N_O_P_INT_STS_REG 0xF8
#define M_N_O_P_RESET_TOLE_REG 0xFC
#define M_N_O_P_DEBOUNCE_SET_REG1 0x100
#define M_N_O_P_DEBOUNCE_SET_REG2 0x104
#define M_N_O_P_INPUT_MASK 0x108
#define Q_R_S_T_CMD_SOURCE0_REG 0x110
#define Q_R_S_T_CMD_SOURCE1_REG 0x114
#define Q_R_S_T_INT_EN_REG 0x118
#define Q_R_S_T_INT_SEN_T0_REG 0x11C
#define Q_R_S_T_INT_SEN_T1_REG 0x120
#define Q_R_S_T_INT_SEN_T2_REG 0x124
#define Q_R_S_T_INT_STS_REG 0x128
#define Q_R_S_T_RESET_TOLE_REG 0x12C
#define Q_R_S_T_DEBOUNCE_SET_REG1 0x130
#define Q_R_S_T_DEBOUNCE_SET_REG2 0x134
#define Q_R_S_T_INPUT_MASK 0x138
#define U_V_W_X_CMD_SOURCE0_REG 0x140
#define U_V_W_X_CMD_SOURCE1_REG 0x144
#define U_V_W_X_INT_EN_REG 0x148
#define U_V_W_X_INT_SEN_T0_REG 0x14C
#define U_V_W_X_INT_SEN_T1_REG 0x150
#define U_V_W_X_INT_SEN_T2_REG 0x154
#define U_V_W_X_INT_STS_REG 0x158
#define U_V_W_X_RESET_TOLE_REG 0x15C
#define U_V_W_X_DEBOUNCE_SET_REG1 0x160
#define U_V_W_X_DEBOUNCE_SET_REG2 0x164
#define U_V_W_X_INPUT_MASK 0x168
#define Y_Z_AA_AB_CMD_SOURCE0_REG 0x170
#define Y_Z_AA_AB_CMD_SOURCE1_REG 0x174
#define Y_Z_AA_AB_INT_EN_REG 0x178
#define Y_Z_AA_AB_INT_SEN_T0_REG 0x17C
#define Y_Z_AA_AB_INT_SEN_T1_REG 0x180
#define Y_Z_AA_AB_INT_SEN_T2_REG 0x184
#define Y_Z_AA_AB_INT_STS_REG 0x188
#define Y_Z_AA_AB_RESET_TOLE_REG 0x18C
#define Y_Z_AA_AB_DEBOUNCE_SET_REG1 0x190
#define Y_Z_AA_AB_DEBOUNCE_SET_REG2 0x194
#define Y_Z_AA_AB_INPUT_MASK 0x198
#define AC_CMD_SOURCE0_REG 0x1A0
#define AC_CMD_SOURCE1_REG 0x1A4
#define AC_INT_EN_REG 0x1A8
#define AC_INT_SEN_T0_REG 0x1AC
#define AC_INT_SEN_T1_REG 0x1B0
#define AC_INT_SEN_T2_REG 0x1B4
#define AC_INT_STS_REG 0x1B8
#define AC_RESET_TOLE_REG 0x1BC
#define AC_DEBOUNCE_SET_REG1 0x1C0
#define AC_DEBOUNCE_SET_REG2 0x1C4
#define AC_INPUT_MASK 0x1C8
#define A_B_C_D_INPUT_MASK 0x1D0
#define E_F_G_H_INPUT_MASK 0x1D4
#define Y_Z_AA_AB_DATA_VALUE_REG 0x1E0
#define Y_Z_AA_AB_DIRECTION_REG 0x1E4
#define AC_DATA_VALUE_REG 0x1E8
#define AC_DIRECTION_REG 0x1EC

/* SuperIO Controller */
#define LDN_ILPC2AHB 0xD
#define LDN_SUART1 0x02
#define LDN_SUART2 0x03
#define LDN_SUART3 0x0B
#define LDN_SUART4 0x0C
#define LDN_SEL_REG 0x07
#define ACT_REG 0x30
#define ACTIVATE_VALUE 0x01
#define DEACTIVATE_VALUE 0x00
#define PORT80_GPIO_EN 0x80
#define PORT80_GPIO_SEL_REG 0x38
#define INV_GPIO_EN 0x80
#define LPC2AHB_ADD0_REG 0xF0
#define LPC2AHB_ADD1_REG 0xF1
#define LPC2AHB_ADD2_REG 0xF2
#define LPC2AHB_ADD3_REG 0xF3
#define LPC2AHB_DAT0_REG 0xF4
#define LPC2AHB_DAT1_REG 0xF5
#define LPC2AHB_DAT2_REG 0xF6
#define LPC2AHB_DAT3_REG 0xF7
#define LPC2AHB_LEN_REG 0xF8
#define LPC2AHB_1_BYTE 0x00
#define LPC2AHB_2_BYTE 0x01
#define LPC2AHB_4_BYTE 0x02
#define LPC2AHB_RW_REG 0xFE

#define ASPEED_ENTRY_KEY 0xA5
#define ASPEED_EXIT_KEY 0xAA

#define TO_BE_UPDATE 0
#define AndMask32(HighBit, LowBit) ~((((uint32_t) 1 << (HighBit - LowBit + 1)) - 1) << LowBit)

typedef enum {
	GPIOA = 0,
	GPIOB,
	GPIOC,
	GPIOD,
	GPIOE,
	GPIOF,
	GPIOG,
	GPIOH,
	GPIOI,
	GPIOJ,
	GPIOK,
	GPIOL,
	GPIOM,
	GPION,
	GPIOO,
	GPIOP,
	GPIOQ,
	GPIOR,
	GPIOS,
	GPIOT,
	GPIOU,
	GPIOV,
	GPIOW,
	GPIOX,
	GPIOY,
	GPIOZ,
	GPIOAA,
	GPIOAB,
} gpio_group_sel;

enum {
	Step1 = 0,
	Step2,
	Step3,
	Step4,
	Step5,
	Step6,
	Step7,
	Step8,
	Step9,
	Step10,
	Step11,
	Step12,
	Step13,
	Step14,
	Step15,
	Step16,
	Step17,
	Step18,
	Step19,
	Step20,
};

enum {
	ARM = 0,
	LPC,
	CoprocessorCPU,
	Reserved,
};

typedef enum {
	SIO = 0,
	MEM,
	NOP,
} config_type;

typedef struct config_data {
	config_type type;
	uint32_t base;
	uint16_t reg;
	uint32_t and;
	uint32_t or;
} config_data;

void aspeed_enable_serial(pnp_devfn_t dev, uint16_t iobase);
void aspeed_early_config(pnp_devfn_t dev, config_data *table, uint8_t count);

/* Enable SuperIO feature which is described in ASPEED datasheet */
void aspeed_enable_port80_direct_gpio(pnp_devfn_t dev, gpio_group_sel g);

/* Enable UART multi-function pins which is described in ASPEED datasheet */
void aspeed_enable_uart_pin(pnp_devfn_t dev);

void pnp_enter_conf_state(pnp_devfn_t dev);
void pnp_exit_conf_state(pnp_devfn_t dev);
void lpc_read(uint8_t port, uint32_t addr, uint32_t *value);
void lpc_write(uint8_t port, uint32_t addr, uint32_t data);

#endif /* SUPERIO_ASPEED_COMMON_ROMSTAGE_H */
