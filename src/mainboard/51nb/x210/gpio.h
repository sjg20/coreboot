/* SPDX-License-Identifier: GPL-2.0-or-later */

#ifndef MAINBOARD_GPIO_H
#define MAINBOARD_GPIO_H

#include <soc/gpe.h>
#include <soc/gpio.h>

#ifndef __ACPI__

/* Pad configuration in ramstage. */
static const struct pad_config gpio_table[] = {
/* RCIN# */_PAD_CFG_STRUCT(GPP_A0, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE) | (1 << 1), 0),
/* LAD0 */_PAD_CFG_STRUCT(GPP_A1, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE) | (1 << 1), PAD_PULL(NATIVE)),
/* LAD1 */_PAD_CFG_STRUCT(GPP_A2, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE) | (1 << 1), PAD_PULL(NATIVE)),
/* LAD2 */_PAD_CFG_STRUCT(GPP_A3, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE) | (1 << 1), PAD_PULL(NATIVE)),
/* LAD3 */_PAD_CFG_STRUCT(GPP_A4, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE) | (1 << 1), PAD_PULL(NATIVE)),
/* LFRAME# */_PAD_CFG_STRUCT(GPP_A5, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), 0),
/* SERIRQ */_PAD_CFG_STRUCT(GPP_A6, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE) | (1 << 1), 0),
/* GPIO */_PAD_CFG_STRUCT(GPP_A7, PAD_FUNC(GPIO) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(RX_DISABLE) | 1, 0),
/* GPIO */_PAD_CFG_STRUCT(GPP_A8, PAD_FUNC(GPIO) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), PAD_PULL(20K_PU)),
/* CLKOUT_LPC0 */_PAD_CFG_STRUCT(GPP_A9, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), PAD_PULL(20K_PD)),
/* CLKOUT_LPC1 */_PAD_CFG_STRUCT(GPP_A10, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), PAD_PULL(20K_PD)),
/* GPIO */_PAD_CFG_STRUCT(GPP_A11, PAD_FUNC(GPIO) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(RX_DISABLE), 0),
/* GPIO */_PAD_CFG_STRUCT(GPP_A12, PAD_FUNC(GPIO) | PAD_TRIG(OFF) | PAD_BUF(RX_DISABLE), 0),
/* SUSWARN#/SUSPWRDNACK */_PAD_CFG_STRUCT(GPP_A13, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), 0),
/* SUS_STAT# */_PAD_CFG_STRUCT(GPP_A14, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), 0),
/* SUS_ACK# */_PAD_CFG_STRUCT(GPP_A15, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE) | (1 << 1), PAD_PULL(20K_PU)),
/* CLKOUT_48 */_PAD_CFG_STRUCT(GPP_A16, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_DISABLE), 0),
/* ISH_GP7 */_PAD_CFG_STRUCT(GPP_A17, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), 0),
/* GPIO */_PAD_CFG_STRUCT(GPP_A18, PAD_FUNC(GPIO) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), 0),
/* GPIO */_PAD_CFG_STRUCT(GPP_A19, PAD_FUNC(GPIO) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), 0),
/* GPIO */_PAD_CFG_STRUCT(GPP_A20, PAD_FUNC(GPIO) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), 0),
/* GPIO */_PAD_CFG_STRUCT(GPP_A21, PAD_FUNC(GPIO) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), 0),
/* GPIO */_PAD_CFG_STRUCT(GPP_A22, PAD_FUNC(GPIO) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(RX_DISABLE) | 1, 0),
/* GPIO */_PAD_CFG_STRUCT(GPP_A23, PAD_FUNC(GPIO) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_DISABLE), PAD_PULL(20K_PD)),
/* n/a */_PAD_CFG_STRUCT(GPP_B0, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), 0),
/* n/a */_PAD_CFG_STRUCT(GPP_B1, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), 0),
/* GPIO */_PAD_CFG_STRUCT(GPP_B2, PAD_FUNC(GPIO) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), 0),
/* GPIO */_PAD_CFG_STRUCT(GPP_B3, PAD_FUNC(GPIO) | PAD_RESET(PLTRST) | PAD_TRIG(OFF) | PAD_BUF(TX_DISABLE) | (1 << 1), 0),
/* GPIO */_PAD_CFG_STRUCT(GPP_B4, PAD_FUNC(GPIO) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(RX_DISABLE) | 1, 0),
/* SRCCLKREQ0# */_PAD_CFG_STRUCT(GPP_B5, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), 0),
/* SRCCLKREQ1# */_PAD_CFG_STRUCT(GPP_B6, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), 0),
/* SRCCLKREQ2# */_PAD_CFG_STRUCT(GPP_B7, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE) | (1 << 1), 0),
/* SRCCLKREQ3# */_PAD_CFG_STRUCT(GPP_B8, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE) | (1 << 1), 0),
/* SRCCLKREQ4# */_PAD_CFG_STRUCT(GPP_B9, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), 0),
/* GPIO */_PAD_CFG_STRUCT(GPP_B10, PAD_FUNC(GPIO) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_DISABLE) | (1 << 1), 0),
/* n/a */_PAD_CFG_STRUCT(GPP_B11, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), 0),
/* SLP_S0# */_PAD_CFG_STRUCT(GPP_B12, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), 0),
/* PLTRST# */_PAD_CFG_STRUCT(GPP_B13, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), 0),
/* GPIO */_PAD_CFG_STRUCT(GPP_B14, PAD_FUNC(GPIO) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(RX_DISABLE) | 1, PAD_PULL(20K_PD)),
/* GPIO */_PAD_CFG_STRUCT(GPP_B15, PAD_FUNC(GPIO) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), 0),
/* GPIO */_PAD_CFG_STRUCT(GPP_B16, PAD_FUNC(GPIO) | PAD_RESET(PLTRST) | PAD_TRIG(OFF) | PAD_RX_POL(INVERT) | PAD_BUF(TX_DISABLE) | (1 << 1), 0),
/* GPIO */_PAD_CFG_STRUCT(GPP_B17, PAD_FUNC(GPIO) | PAD_RESET(PLTRST) | PAD_TRIG(OFF) | PAD_RX_POL(INVERT) | PAD_BUF(TX_DISABLE) | (1 << 1), PAD_PULL(20K_PU)),
/* GPIO */_PAD_CFG_STRUCT(GPP_B18, PAD_FUNC(GPIO) | PAD_RESET(PLTRST) | PAD_TRIG(OFF) | PAD_RX_POL(INVERT) | PAD_BUF(TX_DISABLE) | (1 << 1), PAD_PULL(20K_PU)),
/* GPIO */_PAD_CFG_STRUCT(GPP_B19, PAD_FUNC(GPIO) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), 0),
/* GSPI1_CLK */_PAD_CFG_STRUCT(GPP_B20, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), PAD_PULL(20K_PD)),
/* GSPI1_MISO */_PAD_CFG_STRUCT(GPP_B21, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), PAD_PULL(20K_PD)),
/* GSPIO_MOSI */_PAD_CFG_STRUCT(GPP_B22, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), PAD_PULL(20K_PD)),
/* GPIO */_PAD_CFG_STRUCT(GPP_B23, PAD_FUNC(GPIO) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(RX_DISABLE) | 1, PAD_PULL(20K_PD)),
/* SMBCLK */_PAD_CFG_STRUCT(GPP_C0, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE) | (1 << 1), 0),
/* SMBDATA */_PAD_CFG_STRUCT(GPP_C1, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE) | (1 << 1), PAD_PULL(20K_PD)),
/* GPIO */_PAD_CFG_STRUCT(GPP_C2, PAD_FUNC(GPIO) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(RX_DISABLE) | 1, PAD_PULL(20K_PD)),
/* SML0CLK */_PAD_CFG_STRUCT(GPP_C3, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE) | (1 << 1), PAD_PULL(20K_PU)),
/* SML0DATA */_PAD_CFG_STRUCT(GPP_C4, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE) | (1 << 1), PAD_PULL(20K_PU)),
/* GPIO */_PAD_CFG_STRUCT(GPP_C5, PAD_FUNC(GPIO) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_RX_POL(INVERT) | PAD_BUF(TX_DISABLE), PAD_PULL(20K_PD)),
/* RESERVED */_PAD_CFG_STRUCT(GPP_C6, 0xffffffff, 0xffffff00),
/* RESERVED */_PAD_CFG_STRUCT(GPP_C7, 0xffffffff, 0xffffff00),
/* UART0_RXD */_PAD_CFG_STRUCT(GPP_C8, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE) | (1 << 1), PAD_PULL(20K_PU)),
/* UART0_TXD */_PAD_CFG_STRUCT(GPP_C9, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), 0),
/* UART0_RTS# */_PAD_CFG_STRUCT(GPP_C10, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), 0),
/* UART0_CTS# */_PAD_CFG_STRUCT(GPP_C11, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE) | (1 << 1), 0),
/* UART1_RXD */_PAD_CFG_STRUCT(GPP_C12, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE) | (1 << 1), 0),
/* UART1_TXD */_PAD_CFG_STRUCT(GPP_C13, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), 0),
/* UART1_RTS# */_PAD_CFG_STRUCT(GPP_C14, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), 0),
/* UART1_CTS# */_PAD_CFG_STRUCT(GPP_C15, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE) | (1 << 1), 0),
/* I2C0_SDA */_PAD_CFG_STRUCT(GPP_C16, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE) | (1 << 1), PAD_PULL(20K_PU)),
/* I2C0_SCL */_PAD_CFG_STRUCT(GPP_C17, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE) | (1 << 1), PAD_PULL(20K_PU)),
/* I2C1_SDA */_PAD_CFG_STRUCT(GPP_C18, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE) | (1 << 1), PAD_PULL(20K_PU)),
/* I2C1_SCL */_PAD_CFG_STRUCT(GPP_C19, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE) | (1 << 1), PAD_PULL(20K_PU)),
/* UART2_RXD */_PAD_CFG_STRUCT(GPP_C20, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE) | (1 << 1), PAD_PULL(20K_PU)),
/* UART2_TXD */_PAD_CFG_STRUCT(GPP_C21, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), 0),
/* UART2_RTS# */_PAD_CFG_STRUCT(GPP_C22, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), 0),
/* UART2_CTS# */_PAD_CFG_STRUCT(GPP_C23, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE) | (1 << 1), 0),
/* n/a */_PAD_CFG_STRUCT(GPP_D0, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), 0),
/* n/a */_PAD_CFG_STRUCT(GPP_D1, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), 0),
/* n/a */_PAD_CFG_STRUCT(GPP_D2, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), 0),
/* n/a */_PAD_CFG_STRUCT(GPP_D3, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), 0),
/* ISH_I2C2_SDA */_PAD_CFG_STRUCT(GPP_D4, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), 0),
/* I2S_SFRM */_PAD_CFG_STRUCT(GPP_D5, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE) | (1 << 1), PAD_PULL(20K_PU)),
/* I2S_TXD */_PAD_CFG_STRUCT(GPP_D6, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE) | (1 << 1), PAD_PULL(20K_PU)),
/* I2S_RXD */_PAD_CFG_STRUCT(GPP_D7, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE) | (1 << 1), PAD_PULL(20K_PU)),
/* I2S_SCLK */_PAD_CFG_STRUCT(GPP_D8, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE) | (1 << 1), PAD_PULL(20K_PU)),
/* GPIO */_PAD_CFG_STRUCT(GPP_D9, PAD_FUNC(GPIO) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_DISABLE) | (1 << 1), PAD_PULL(20K_PU)),
/* GPIO */_PAD_CFG_STRUCT(GPP_D10, PAD_FUNC(GPIO) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_DISABLE) | (1 << 1), PAD_PULL(20K_PU)),
/* GPIO */_PAD_CFG_STRUCT(GPP_D11, PAD_FUNC(GPIO) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_DISABLE) | (1 << 1), PAD_PULL(20K_PU)),
/* GPIO */_PAD_CFG_STRUCT(GPP_D12, PAD_FUNC(GPIO) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_DISABLE) | (1 << 1), PAD_PULL(20K_PU)),
/* ISH_UART0_RXD */_PAD_CFG_STRUCT(GPP_D13, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE) | (1 << 1), PAD_PULL(20K_PU)),
/* ISH_UART0_TXD */_PAD_CFG_STRUCT(GPP_D14, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), PAD_PULL(20K_PU)),
/* ISH_UART0_RTS# */_PAD_CFG_STRUCT(GPP_D15, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), 0),
/* ISH_UART0_CTS# */_PAD_CFG_STRUCT(GPP_D16, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE) | (1 << 1), 0),
/* DMIC_CLK1 */_PAD_CFG_STRUCT(GPP_D17, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), 0),
/* DMIC_DATA1 */_PAD_CFG_STRUCT(GPP_D18, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), PAD_PULL(20K_PD)),
/* DMIC_CLK0 */_PAD_CFG_STRUCT(GPP_D19, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), 0),
/* DMIC_DATA0 */_PAD_CFG_STRUCT(GPP_D20, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), PAD_PULL(20K_PD)),
/* n/a */_PAD_CFG_STRUCT(GPP_D21, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), 0),
/* n/a */_PAD_CFG_STRUCT(GPP_D22, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), 0),
/* ISH_I2C2_SCL */_PAD_CFG_STRUCT(GPP_D23, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), 0),
/* GPIO */_PAD_CFG_STRUCT(GPP_E0, PAD_FUNC(GPIO) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(RX_DISABLE), 0),
/* GPIO */_PAD_CFG_STRUCT(GPP_E1, PAD_FUNC(GPIO) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_RX_POL(INVERT) | PAD_BUF(TX_DISABLE) | (1 << 1), 0),
/* GPIO */_PAD_CFG_STRUCT(GPP_E2, PAD_FUNC(GPIO) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), 0),
/* GPIO */_PAD_CFG_STRUCT(GPP_E3, PAD_FUNC(GPIO) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_DISABLE) | (1 << 1) | 1, 0),
/* GPIO */_PAD_CFG_STRUCT(GPP_E4, PAD_FUNC(GPIO) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), 0),
/* SATA_DEVSLP1 */_PAD_CFG_STRUCT(GPP_E5, PAD_FUNC(NF1) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), 0),
/* SATA_DEVSLP2 */_PAD_CFG_STRUCT(GPP_E6, PAD_FUNC(NF1) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), 0),
/* GPIO */_PAD_CFG_STRUCT(GPP_E7, PAD_FUNC(GPIO) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), 0),
/* SATA_LED# */_PAD_CFG_STRUCT(GPP_E8, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), 0),
/* USB_OC0# */_PAD_CFG_STRUCT(GPP_E9, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE) | (1 << 1), 0),
/* USB_OC1# */_PAD_CFG_STRUCT(GPP_E10, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE) | (1 << 1), 0),
/* USB_OC2# */_PAD_CFG_STRUCT(GPP_E11, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE) | (1 << 1), 0),
/* GPIO */_PAD_CFG_STRUCT(GPP_E12, PAD_FUNC(GPIO) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), 0),
/* n/a */_PAD_CFG_STRUCT(GPP_E13, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), 0),
/* n/a */_PAD_CFG_STRUCT(GPP_E14, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), 0),
/* GPIO */_PAD_CFG_STRUCT(GPP_E15, PAD_FUNC(GPIO) | PAD_RESET(PLTRST) | PAD_IRQ_ROUTE(SCI) | PAD_RX_POL(INVERT) | PAD_BUF(TX_DISABLE) | (1 << 1), 0),
/* GPIO */_PAD_CFG_STRUCT(GPP_E16, PAD_FUNC(GPIO) | PAD_RESET(PLTRST) | PAD_TRIG(OFF) | PAD_BUF(TX_DISABLE) | (1 << 1), 0),
/* n/a */_PAD_CFG_STRUCT(GPP_E17, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE) | (1 << 1), 0),
/* n/a */_PAD_CFG_STRUCT(GPP_E18, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), PAD_PULL(20K_PU)),
/* n/a */_PAD_CFG_STRUCT(GPP_E19, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), PAD_PULL(20K_PD)),
/* n/a */_PAD_CFG_STRUCT(GPP_E20, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE) | (1 << 1), PAD_PULL(20K_PU)),
/* n/a */_PAD_CFG_STRUCT(GPP_E21, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE) | (1 << 1), PAD_PULL(20K_PD)),
/* GPIO */_PAD_CFG_STRUCT(GPP_E22, PAD_FUNC(GPIO) | PAD_RESET(DEEP) | PAD_TRIG(OFF), 0),
/* GPIO */_PAD_CFG_STRUCT(GPP_E23, PAD_FUNC(GPIO) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(RX_DISABLE) | 1, PAD_PULL(20K_PD)),
/* BATLOW# */_PAD_CFG_STRUCT(GPD0, PAD_FUNC(NF1) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE) | (1 << 1), PAD_PULL(20K_PU)),
/* ACPRESENT */_PAD_CFG_STRUCT(GPD1, PAD_FUNC(NF1) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE) | (1 << 1), 0),
/* LAN_WAKE# */_PAD_CFG_STRUCT(GPD2, PAD_FUNC(NF1) | PAD_TRIG(OFF) | PAD_BUF(RX_DISABLE) | (1 << 1), PAD_PULL(NATIVE)),
/* PWRBTN# */_PAD_CFG_STRUCT(GPD3, PAD_FUNC(NF1) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE) | (1 << 1), PAD_PULL(20K_PU)),
/* SLP_S3# */_PAD_CFG_STRUCT(GPD4, PAD_FUNC(NF1) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), 0),
/* SLP_S4# */_PAD_CFG_STRUCT(GPD5, PAD_FUNC(NF1) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), 0),
/* SLP_A# */_PAD_CFG_STRUCT(GPD6, PAD_FUNC(NF1) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), 0),
/* GPIO */_PAD_CFG_STRUCT(GPD7, PAD_FUNC(GPIO) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE) | 1, 0),
/* SUSCLK */_PAD_CFG_STRUCT(GPD8, PAD_FUNC(NF1) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), 0),
/* SLP_WLAN# */_PAD_CFG_STRUCT(GPD9, PAD_FUNC(NF1) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), 0),
/* SLP_S5# */_PAD_CFG_STRUCT(GPD10, PAD_FUNC(NF1) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), 0),
/* LANPHYPC */_PAD_CFG_STRUCT(GPD11, PAD_FUNC(NF1) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), 0),
/* SATAXPCIE3 */_PAD_CFG_STRUCT(GPP_F0, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), 0),
/* SATAXPCIE4 */_PAD_CFG_STRUCT(GPP_F1, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), 0),
/* SATAXPCIE5 */_PAD_CFG_STRUCT(GPP_F2, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), 0),
/* SATAXPCIE6 */_PAD_CFG_STRUCT(GPP_F3, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), 0),
/* SATAXPCIE7 */_PAD_CFG_STRUCT(GPP_F4, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE) | (1 << 1), PAD_CFG1_TOL_1V8 | PAD_PULL(20K_PU)),
/* SATA_DEVSLP3 */_PAD_CFG_STRUCT(GPP_F5, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE) | (1 << 1), PAD_CFG1_TOL_1V8 | PAD_PULL(20K_PU)),
/* SATA_DEVSLP4 */_PAD_CFG_STRUCT(GPP_F6, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE) | (1 << 1), PAD_CFG1_TOL_1V8 | PAD_PULL(20K_PU)),
/* SATA_DEVSLP5 */_PAD_CFG_STRUCT(GPP_F7, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE) | (1 << 1), PAD_CFG1_TOL_1V8 | PAD_PULL(20K_PU)),
/* SATA_DEVSLP6 */_PAD_CFG_STRUCT(GPP_F8, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE) | (1 << 1), PAD_CFG1_TOL_1V8 | PAD_PULL(20K_PU)),
/* SATA_DEVSLP7 */_PAD_CFG_STRUCT(GPP_F9, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE) | (1 << 1), PAD_CFG1_TOL_1V8 | PAD_PULL(20K_PU)),
/* n/a */_PAD_CFG_STRUCT(GPP_F10, PAD_FUNC(NF2) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE) | (1 << 1), PAD_CFG1_TOL_1V8 | PAD_PULL(20K_PU)),
/* n/a */_PAD_CFG_STRUCT(GPP_F11, PAD_FUNC(NF2) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE) | (1 << 1), PAD_CFG1_TOL_1V8 | PAD_PULL(20K_PU)),
/* SATA_SDATAOUT1 */_PAD_CFG_STRUCT(GPP_F12, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), 0),
/* SATA_SDATAOUT2 */_PAD_CFG_STRUCT(GPP_F13, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), 0),
/* n/a */_PAD_CFG_STRUCT(GPP_F14, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), 0),
/* USB_OC4# */_PAD_CFG_STRUCT(GPP_F15, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), 0),
/* USB_OC5# */_PAD_CFG_STRUCT(GPP_F16, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), 0),
/* USB_OC6# */_PAD_CFG_STRUCT(GPP_F17, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), 0),
/* USB_OC7# */_PAD_CFG_STRUCT(GPP_F18, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), 0),
/* eDP_VDDEN */_PAD_CFG_STRUCT(GPP_F19, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), 0),
/* eDP_BKLTEN */_PAD_CFG_STRUCT(GPP_F20, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), 0),
/* eDP_BKLTCTL */_PAD_CFG_STRUCT(GPP_F21, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), 0),
/* n/a */_PAD_CFG_STRUCT(GPP_F22, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), 0),
/* GPIO */_PAD_CFG_STRUCT(GPP_F23, PAD_FUNC(GPIO) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_DISABLE) | (1 << 1), 0),
/* FAN_TACH_0 */_PAD_CFG_STRUCT(GPP_G0, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), 0),
/* FAN_TACH_1 */_PAD_CFG_STRUCT(GPP_G1, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), 0),
/* FAN_TACH_2 */_PAD_CFG_STRUCT(GPP_G2, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), 0),
/* FAN_TACH_3 */_PAD_CFG_STRUCT(GPP_G3, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), 0),
/* FAN_TACH_4 */_PAD_CFG_STRUCT(GPP_G4, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), 0),
/* FAN_TACH_5 */_PAD_CFG_STRUCT(GPP_G5, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE) | (1 << 1), 0),
/* FAN_TACH_6 */_PAD_CFG_STRUCT(GPP_G6, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), 0),
/* FAN_TACH_7 */_PAD_CFG_STRUCT(GPP_G7, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF) | PAD_BUF(TX_RX_DISABLE), PAD_PULL(20K_PD)),
};

#endif

#endif
