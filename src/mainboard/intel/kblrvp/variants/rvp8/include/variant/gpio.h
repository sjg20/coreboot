/*
 * This file is part of the coreboot project.
 *
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
 * GNU General Public License for more details.
 */

#ifndef _GPIORVP8_H
#define _GPIORVP8_H

#include <soc/gpe.h>
#include <soc/gpio.h>

/* TCA6424A  I/O Expander */
#define IO_EXPANDER_BUS         4
#define IO_EXPANDER_0_ADDR      0x22
#define IO_EXPANDER_P0CONF      0x0C    /* Port 0 conf offset */
#define IO_EXPANDER_P0DOUT      0x04    /* Port 0 data offset */
#define IO_EXPANDER_P1CONF      0x0D
#define IO_EXPANDER_P1DOUT      0x05
#define IO_EXPANDER_P2CONF      0x0E
#define IO_EXPANDER_P2DOUT      0x06
#define IO_EXPANDER_1_ADDR      0x23

/* GPE_EC_WAKE */
#define GPE_EC_WAKE		GPE0_LAN_WAK
#define EC_SMI_GPI		GPP_I3

/*
 * Gpio based irq for touchpad, 18th index in North Bank
 * MAX_DIRECT_IRQ + GPSW_SIZE + 19
 */
#define KBLRVP_TOUCHPAD_IRQ	33

#define KBLRVP_TOUCH_IRQ	31

#define BOARD_TOUCHPAD_NAME		"touchpad"
#define BOARD_TOUCHPAD_IRQ		KBLRVP_TOUCHPAD_IRQ
#define BOARD_TOUCHPAD_I2C_BUS		0
#define BOARD_TOUCHPAD_I2C_ADDR		0x20

#define BOARD_TOUCHSCREEN_NAME		"touchscreen"
#define BOARD_TOUCHSCREEN_IRQ		KBLRVP_TOUCH_IRQ
#define BOARD_TOUCHSCREEN_I2C_BUS	0
#define BOARD_TOUCHSCREEN_I2C_ADDR	0x4c

#ifndef __ACPI__

/* Pad configuration in ramstage. */
static const struct pad_config gpio_table[] = {
/* EC_PCH_RCIN */       PAD_CFG_NF(GPP_A0, NONE, DEEP, NF3),
/* EC_LPC_IO0 */        PAD_CFG_NF(GPP_A1, 20K_PU, DEEP, NF3),
/* EC_LPC_IO1*/         PAD_CFG_NF(GPP_A2, 20K_PU, DEEP, NF3),
/* EC_LPC_IO2 */        PAD_CFG_NF(GPP_A3, 20K_PU, DEEP, NF3),
/* EC_LPC_IO3 */        PAD_CFG_NF(GPP_A4, 20K_PU, DEEP, NF3),
/* LPC_FRAME */         PAD_CFG_NF(GPP_A5, NONE, DEEP, NF3),
/* LPC_SERIRQ */        PAD_CFG_NF(GPP_A6, NONE, DEEP, NF3),
/* PIRQAB */            PAD_CFG_GPI(GPP_A7, NONE, DEEP),
/* LPC_CLKRUN */        PAD_CFG_NF(GPP_A8, NONE, DEEP, NF1),
/* EC_LPC_CLK */        PAD_CFG_NF(GPP_A9, NONE, DEEP, NF3),
/* PCH_LPC_CLK */       PAD_CFG_NF(GPP_A10, 20K_PD, DEEP, NF1),
/* PMEB */              PAD_CFG_GPI(GPP_A11, NONE, DEEP),
/* SUS_PWR_ACK_R */     PAD_CFG_NF(GPP_A13, NONE, DEEP, NF1),
/* PM_SUS_ESPI_RST */   PAD_CFG_NF(GPP_A14, NONE, DEEP, NF3),
/* PCH_SUSACK */        PAD_CFG_NF(GPP_A15, 20K_PU, DEEP, NF1),
/* BT_RF_KILL */        PAD_CFG_GPO(GPP_B3, 1, DEEP),
/* EXTTS_SNI_DRV1 */    PAD_CFG_NF(GPP_B4, NONE, DEEP, NF1),
/* SRCCLKREQ0# */       PAD_CFG_GPI_ACPI_SCI(GPP_B5, NONE, DEEP, YES),
/* PM_SLP_S0 */         PAD_CFG_NF(GPP_B12, NONE, DEEP, NF1),
/* PCH_PLT_RST */       PAD_CFG_NF(GPP_B13, NONE, DEEP, NF1),
/* GPP_B_14_SPKR */     PAD_CFG_NF(GPP_B14, 20K_PD, DEEP, NF1),
/* GSPI0_MISO */        PAD_CFG_GPO(GPP_B17, 1, DEEP),
/* PCHHOTB */           PAD_CFG_NF(GPP_B23, 20K_PD, DEEP, NF2),
/* SMB_CLK */           PAD_CFG_NF(GPP_C0, NONE, DEEP, NF1),
/* SMB_DATA */          PAD_CFG_NF(GPP_C1, NONE, DEEP, NF1),
/* SMBALERT# */         PAD_CFG_GPO(GPP_C2, 1, DEEP),
/* SML0_CLK */          PAD_CFG_NF(GPP_C3, NONE, DEEP, NF1),
/* SML0_DATA */         PAD_CFG_NF(GPP_C4, NONE, DEEP, NF1),
/* SML1_CLK */          PAD_CFG_NF(GPP_C6, NONE, DEEP, NF1),
/* SML1_DATA */         PAD_CFG_NF(GPP_C7, NONE, DEEP, NF1),
/* UART0_RXD */         PAD_CFG_NF(GPP_C8, NONE, DEEP, NF1),
/* UART0_TXD */         PAD_CFG_NF(GPP_C9, NONE, DEEP, NF1),
/* UART0_RTS_N */       PAD_CFG_NF(GPP_C10, NONE, DEEP, NF1),
/* UART0_CTS_N */       PAD_CFG_NF(GPP_C11, NONE, DEEP, NF1),
/* GD_UART2_RXD */      PAD_CFG_NF(GPP_C20, NONE, DEEP, NF1),
/* GD_UART2_TXD */      PAD_CFG_NF(GPP_C21, NONE, DEEP, NF1),
/* UART2_RTS_N */       PAD_CFG_NF(GPP_C22, NONE, DEEP, NF1),
/* UART2_CTS_N */       PAD_CFG_NF(GPP_C23, NONE, DEEP, NF1),
/* SSP0_SFRM */         PAD_CFG_NF(GPP_D5, NONE, DEEP, NF1),
/* SSP0_TXD */          PAD_CFG_NF(GPP_D6, NONE, DEEP, NF1),
/* SSP0_RXD */          PAD_CFG_NF(GPP_D7, NONE, DEEP, NF1),
/* SSP0_SCLK */         PAD_CFG_NF(GPP_D8, NONE, DEEP, NF1),
/* SATAE_IFDET */       PAD_CFG_NF(GPP_E0, 20K_PU, DEEP, NF1),
/* SATAE_IFDET */       PAD_CFG_NF(GPP_E1, 20K_PU, DEEP, NF1),
/* CPU_GP0 */           PAD_CFG_NF(GPP_E3, NONE, DEEP, NF1),
/* SSD_SATA_DEVSLP */   PAD_CFG_NF(GPP_E4, NONE, DEEP, NF1),
/* SATALED# */          PAD_CFG_NF(GPP_E8, NONE, DEEP, NF1),
/* USB2_OC_0 */         PAD_CFG_NF(GPP_E9, NONE, DEEP, NF1),
/* USB2_OC_1 */         PAD_CFG_NF(GPP_E10, NONE, DEEP, NF1),
/* USB2_OC_2 */         PAD_CFG_NF(GPP_E11, NONE, DEEP, NF1),
/* USB2_OC_3 */         PAD_CFG_NF(GPP_E12, NONE, DEEP, NF1),
/* SATAXPCIE_4 */       PAD_CFG_NF(GPP_F1, 20K_PU, DEEP,NF1),
/* SATA_DEVSLP_3 */     PAD_CFG_GPI_ACPI_SCI(GPP_F5, NONE, DEEP, YES),
/* SATA_DEVSLP_4 */     PAD_CFG_NF(GPP_F6, NONE, DEEP, NF1),
/* SATA_SCLOCK */       PAD_CFG_GPI_APIC(GPP_F10, NONE, DEEP),
/* SATA_SLOAD */        PAD_CFG_GPI(GPP_F11, NONE, DEEP),
/* SATA_SDATAOUT1 */    PAD_CFG_GPI_APIC(GPP_F12, NONE, DEEP),
/* SATA_SDATAOUT0 */    PAD_CFG_GPI_APIC(GPP_F13, NONE, DEEP),
/* H_SKTOCC_N */        PAD_CFG_GPI_APIC(GPP_F14, NONE, DEEP),
/* USB_OC4_R_N */       PAD_CFG_NF(GPP_F15, NONE, DEEP, NF1),
/* USB_OC5_R_N */       PAD_CFG_NF(GPP_F16, NONE, DEEP, NF1),
/* USB_OC6_R_N */       PAD_CFG_NF(GPP_F17, NONE, DEEP, NF1),
/* USB_OC7_R_N */       PAD_CFG_GPO(GPP_F18, 1, DEEP),
/* GPIO_PEG_RESET */    PAD_CFG_GPO(GPP_F22, 1, DEEP),
/* VCORE_VBOOST_CTRL */ PAD_CFG_GPO(GPP_F23, 0, DEEP),
/* FAN_TACH_0 */        PAD_CFG_GPO(GPP_G0, 1, DEEP),
/* FAN_TACH_1 */        PAD_CFG_GPO(GPP_G1, 1, DEEP),
/* FAN_TACH_2 */        PAD_CFG_GPI_ACPI_SCI(GPP_G2, NONE, DEEP, YES),
/* FAN_TACH_3 */        PAD_CFG_GPI_ACPI_SCI(GPP_G3, NONE, DEEP, YES),
/* FAN_TACH_4 */        PAD_CFG_GPO(GPP_G4, 1, DEEP),
/* FAN_TACH_5 */        PAD_CFG_GPI_APIC(GPP_G5, NONE, DEEP),
/* FAN_TACH_6 */        PAD_CFG_GPI_ACPI_SCI(GPP_G6, NONE, DEEP, YES),
/* FAN_TACH_7 */        PAD_CFG_GPO(GPP_G7, 1, DEEP),
/* GSXDOUT */           PAD_CFG_GPI_ACPI_SCI(GPP_G12, 20K_PD, DEEP, YES),
/* GSXSLOAD */          PAD_CFG_GPO(GPP_G13, 1, DEEP),
/* GSXDIN */            PAD_CFG_GPI_ACPI_SCI(GPP_G14, NONE, DEEP, YES),
/* GSXSRESETB */        PAD_CFG_GPO(GPP_G15, 0, DEEP),
/* GSXCLK */            PAD_CFG_GPO(GPP_G16, 0, DEEP),
/* NMIB */              PAD_CFG_GPI_APIC(GPP_G18, NONE, DEEP),
/* SMIB */              PAD_CFG_NF(GPP_G19, NONE, DEEP, NF1),
/* TEST_SETUP_MENU */   PAD_CFG_GPI_APIC(GPP_G20, NONE, DEEP),
/* P_INTF_N */          PAD_CFG_GPI_ACPI_SCI(GPP_G21, NONE, DEEP, YES),
/* PCH_PEGSLOT1 */      PAD_CFG_GPO(GPP_G22, 1, DEEP),
/* IVCAM_DFU_R */       PAD_CFG_GPO(GPP_G23, 1, DEEP),
/* SRCCLKREQB_8 */      PAD_CFG_NF(GPP_H2, NONE, DEEP, NF1),
/* SML2CLK */           PAD_CFG_GPI(GPP_H10, NONE, DEEP),
/* SML2DATA */          PAD_CFG_GPI(GPP_H11, NONE, DEEP),
/* SML3CLK */           PAD_CFG_GPI_APIC(GPP_H13, NONE, DEEP),
/* SML3DATA */          PAD_CFG_GPI_APIC(GPP_H14, NONE, DEEP),
/* SML3ALERTB */        PAD_CFG_GPI_APIC(GPP_H15, NONE, DEEP),
/* SML4DATA */          PAD_CFG_GPO(GPP_H17, 1, DEEP),
/* LED_DRIVE */         PAD_CFG_GPO(GPP_H23, 0, DEEP),
/* DDSP_HPD_0 */        PAD_CFG_NF(GPP_I0, NONE, DEEP, NF1),
/* DDSP_HPD_1 */        PAD_CFG_NF(GPP_I1, NONE, DEEP, NF1),
/* DDSP_HPD_2 */        PAD_CFG_NF(GPP_I2, NONE, DEEP, NF1),
/* DDSP_HPD_1 */        PAD_CFG_GPI_ACPI_SMI(GPP_I3, NONE, DEEP, YES),
/* DDPB_CTRLCLK */      PAD_CFG_NF(GPP_I5, NONE, DEEP, NF1),
/* DDPB_CTRLDATA */     PAD_CFG_NF(GPP_I6, 20K_PD, DEEP, NF1),
/* DDPC_CTRLCLK */      PAD_CFG_NF(GPP_I7, NONE, DEEP, NF1),
/* DDPC_CTRLDATA */     PAD_CFG_NF(GPP_I8, 20K_PD, DEEP, NF1),
/* DDPD_CTRLCLK */      PAD_CFG_NF(GPP_I9, NONE, DEEP, NF1),
/* DDPD_CTRLDATA */     PAD_CFG_NF(GPP_I10, 20K_PD, DEEP, NF1),
/* EC_PCH_ACPRESENT */  PAD_CFG_GPO(GPD1, 0, DEEP),
/* EC_PCH_WAKE */       PAD_CFG_NF(GPD2, NONE, DEEP, NF1),
/* PM_PWRBTN_R_N */     PAD_CFG_NF(GPD3, 20K_PU, DEEP, NF1),
/* PM_SLP_S3# */        PAD_CFG_NF(GPD4, NONE, DEEP, NF1),
/* PM_SLP_S4# */        PAD_CFG_NF(GPD5, NONE, DEEP, NF1),
/* PM_SLP_SA# */        PAD_CFG_NF(GPD6, NONE, DEEP, NF1),
/* USB_WAKEOUT_N */     PAD_CFG_NF(GPD7, NONE, DEEP, NF1),
/* PM_SUSCLK */         PAD_CFG_NF(GPD8, NONE, DEEP, NF1),
/* PCH_SLP_WLAN# */     PAD_CFG_NF(GPD9, NONE, DEEP, NF1),
/* PM_SLP_S5# */        PAD_CFG_NF(GPD10, NONE, DEEP, NF1),
/* LANPHYC */           PAD_CFG_NF(GPD11, NONE, DEEP, NF1),

};

/* Early pad configuration in romstage. */
static const struct pad_config early_gpio_table[] = {
/* UART0_RXD */		PAD_CFG_NF(GPP_C8, NONE, DEEP, NF1),
/* UART0_TXD */		PAD_CFG_NF(GPP_C9, NONE, DEEP, NF1),
};


#endif
#endif
