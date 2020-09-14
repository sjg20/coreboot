/* SPDX-License-Identifier: GPL-2.0-or-later */

#ifndef MAINBOARD_GPIO_H
#define MAINBOARD_GPIO_H

#include <soc/gpe.h>
#include <soc/gpio.h>

/*
 * Bidirectional GPIO port when both RX and TX buffer is enabled
 * todo: move this macros to src/soc/intel/common/block/include/intelblocks/gpio_defs.h
 */
#ifndef PAD_CFG_GPIO_BIDIRECT
#define PAD_CFG_GPIO_BIDIRECT(pad, val, pull, rst, trig, own)		\
	_PAD_CFG_STRUCT(pad,						\
		PAD_FUNC(GPIO) | PAD_RESET(rst) | PAD_TRIG(trig) |	\
		PAD_BUF(NO_DISABLE) | val,				\
		PAD_PULL(pull) | PAD_CFG_OWN_GPIO(own))
#endif

#ifndef __ACPI__

/* Pad configuration in ramstage. */
static const struct pad_config gpio_table[] = {
	PAD_CFG_NF(GPP_A0, NONE, DEEP, NF1),
	PAD_CFG_NF(GPP_A1, NATIVE, DEEP, NF1),
	PAD_CFG_NF(GPP_A2, NATIVE, DEEP, NF1),
	PAD_CFG_NF(GPP_A3, NATIVE, DEEP, NF1),
	PAD_CFG_NF(GPP_A4, NATIVE, DEEP, NF1),
	PAD_CFG_NF(GPP_A5, NONE, DEEP, NF1),
	PAD_CFG_NF(GPP_A6, NONE, DEEP, NF1),
	PAD_CFG_GPO(GPP_A7, 1, DEEP),
	PAD_NC(GPP_A8, 20K_PU),
	PAD_CFG_NF(GPP_A9, 20K_PD, DEEP, NF1),
	PAD_CFG_NF(GPP_A10, 20K_PD, DEEP, NF1),
	PAD_CFG_GPO(GPP_A11, 0, DEEP),
	PAD_CFG_GPO(GPP_A12, 0, PWROK),
	PAD_CFG_NF(GPP_A13, NONE, DEEP, NF1),
	PAD_CFG_NF(GPP_A14, NONE, DEEP, NF1),
	PAD_CFG_NF(GPP_A15, 20K_PU, DEEP, NF1),
	PAD_CFG_NF(GPP_A16, NONE, DEEP, NF1),
	PAD_CFG_NF(GPP_A17, NONE, DEEP, NF1),
	PAD_NC(GPP_A18, NONE),
	PAD_NC(GPP_A19, NONE),
	PAD_NC(GPP_A20, NONE),
	PAD_NC(GPP_A21, NONE),
	PAD_CFG_GPO(GPP_A22, 1, DEEP),
	PAD_CFG_GPI_TRIG_OWN(GPP_A23, 20K_PD, DEEP, OFF, ACPI),
	PAD_CFG_NF(GPP_B0, NONE, DEEP, NF1),
	PAD_CFG_NF(GPP_B1, NONE, DEEP, NF1),
	PAD_NC(GPP_B2, NONE),
	PAD_CFG_GPI_TRIG_OWN(GPP_B3, NONE, PLTRST, OFF, ACPI),
	PAD_CFG_GPO(GPP_B4, 1, DEEP),
	PAD_CFG_NF(GPP_B5, NONE, DEEP, NF1),
	PAD_CFG_NF(GPP_B6, NONE, DEEP, NF1),
	PAD_CFG_NF(GPP_B7, NONE, DEEP, NF1),
	PAD_CFG_NF(GPP_B8, NONE, DEEP, NF1),
	PAD_CFG_NF(GPP_B9, NONE, DEEP, NF1),
	PAD_CFG_GPI_TRIG_OWN(GPP_B10, NONE, DEEP, OFF, ACPI),
	PAD_CFG_NF(GPP_B11, NONE, DEEP, NF1),
	PAD_CFG_NF(GPP_B12, NONE, DEEP, NF1),
	PAD_CFG_NF(GPP_B13, NONE, DEEP, NF1),
	PAD_CFG_TERM_GPO(GPP_B14, 1, 20K_PD, DEEP),
	PAD_NC(GPP_B15, NONE),
	PAD_CFG_GPI_TRIG_OWN(GPP_B16, NONE, PLTRST, OFF, ACPI),
	PAD_CFG_GPI_TRIG_OWN(GPP_B17, 20K_PU, PLTRST, OFF, ACPI),
	PAD_CFG_GPI_TRIG_OWN(GPP_B18, 20K_PU, PLTRST, OFF, ACPI),
	PAD_NC(GPP_B19, NONE),
	PAD_CFG_NF(GPP_B20, 20K_PD, DEEP, NF1),
	PAD_CFG_NF(GPP_B21, 20K_PD, DEEP, NF1),
	PAD_CFG_NF(GPP_B22, 20K_PD, DEEP, NF1),
	PAD_CFG_TERM_GPO(GPP_B23, 1, 20K_PD, DEEP),
	PAD_CFG_NF(GPP_C0, NONE, DEEP, NF1),
	PAD_CFG_NF(GPP_C1, 20K_PD, DEEP, NF1),
	PAD_CFG_TERM_GPO(GPP_C2, 1, 20K_PD, DEEP),
	PAD_CFG_NF(GPP_C3, 20K_PU, DEEP, NF1),
	PAD_CFG_NF(GPP_C4, 20K_PU, DEEP, NF1),
	PAD_CFG_GPI_TRIG_OWN(GPP_C5, 20K_PD, DEEP, OFF, ACPI),
	/* GPP_C6 - RESERVED */
	/* GPP_C7 - RESERVED */
	PAD_CFG_NF(GPP_C8, 20K_PU, DEEP, NF1),
	PAD_CFG_NF(GPP_C9, NONE, DEEP, NF1),
	PAD_CFG_NF(GPP_C10, NONE, DEEP, NF1),
	PAD_CFG_NF(GPP_C11, NONE, DEEP, NF1),
	PAD_CFG_NF(GPP_C12, NONE, DEEP, NF1),
	PAD_CFG_NF(GPP_C13, NONE, DEEP, NF1),
	PAD_CFG_NF(GPP_C14, NONE, DEEP, NF1),
	PAD_CFG_NF(GPP_C15, NONE, DEEP, NF1),
	PAD_CFG_NF(GPP_C16, 20K_PU, DEEP, NF1),
	PAD_CFG_NF(GPP_C17, 20K_PU, DEEP, NF1),
	PAD_CFG_NF(GPP_C18, 20K_PU, DEEP, NF1),
	PAD_CFG_NF(GPP_C19, 20K_PU, DEEP, NF1),
	PAD_CFG_NF(GPP_C20, 20K_PU, DEEP, NF1),
	PAD_CFG_NF(GPP_C21, NONE, DEEP, NF1),
	PAD_CFG_NF(GPP_C22, NONE, DEEP, NF1),
	PAD_CFG_NF(GPP_C23, NONE, DEEP, NF1),
	PAD_CFG_NF(GPP_D0, NONE, DEEP, NF1),
	PAD_CFG_NF(GPP_D1, NONE, DEEP, NF1),
	PAD_CFG_NF(GPP_D2, NONE, DEEP, NF1),
	PAD_CFG_NF(GPP_D3, NONE, DEEP, NF1),
	PAD_CFG_NF(GPP_D4, NONE, DEEP, NF1),
	PAD_CFG_NF(GPP_D5, 20K_PU, DEEP, NF1),
	PAD_CFG_NF(GPP_D6, 20K_PU, DEEP, NF1),
	PAD_CFG_NF(GPP_D7, 20K_PU, DEEP, NF1),
	PAD_CFG_NF(GPP_D8, 20K_PU, DEEP, NF1),
	PAD_CFG_GPI_TRIG_OWN(GPP_D9, 20K_PU, DEEP, OFF, ACPI),
	PAD_CFG_GPI_TRIG_OWN(GPP_D10, 20K_PU, DEEP, OFF, ACPI),
	PAD_CFG_GPI_TRIG_OWN(GPP_D11, 20K_PU, DEEP, OFF, ACPI),
	PAD_CFG_GPI_TRIG_OWN(GPP_D12, 20K_PU, DEEP, OFF, ACPI),
	PAD_CFG_NF(GPP_D13, 20K_PU, DEEP, NF1),
	PAD_CFG_NF(GPP_D14, 20K_PU, DEEP, NF1),
	PAD_CFG_NF(GPP_D15, NONE, DEEP, NF1),
	PAD_CFG_NF(GPP_D16, NONE, DEEP, NF1),
	PAD_CFG_NF(GPP_D17, NONE, DEEP, NF1),
	PAD_CFG_NF(GPP_D18, 20K_PD, DEEP, NF1),
	PAD_CFG_NF(GPP_D19, NONE, DEEP, NF1),
	PAD_CFG_NF(GPP_D20, 20K_PD, DEEP, NF1),
	PAD_CFG_NF(GPP_D21, NONE, DEEP, NF1),
	PAD_CFG_NF(GPP_D22, NONE, DEEP, NF1),
	PAD_CFG_NF(GPP_D23, NONE, DEEP, NF1),
	PAD_CFG_GPO(GPP_E0, 0, DEEP),
	PAD_CFG_GPI_TRIG_OWN(GPP_E1, NONE, DEEP, OFF, ACPI),
	PAD_NC(GPP_E2, NONE),
	PAD_CFG_GPI_TRIG_OWN(GPP_E3, NONE, DEEP, OFF, ACPI),
	PAD_NC(GPP_E4, NONE),
	PAD_CFG_NF(GPP_E5, NONE, PWROK, NF1),
	PAD_CFG_NF(GPP_E6, NONE, PWROK, NF1),
	PAD_NC(GPP_E7, NONE),
	PAD_CFG_NF(GPP_E8, NONE, DEEP, NF1),
	PAD_CFG_NF(GPP_E9, NONE, DEEP, NF1),
	PAD_CFG_NF(GPP_E10, NONE, DEEP, NF1),
	PAD_CFG_NF(GPP_E11, NONE, DEEP, NF1),
	PAD_NC(GPP_E12, NONE),
	PAD_CFG_NF(GPP_E13, NONE, DEEP, NF1),
	PAD_CFG_NF(GPP_E14, NONE, DEEP, NF1),
	PAD_CFG_GPI_SCI(GPP_E15, NONE, PLTRST, LEVEL, INVERT),
	PAD_CFG_GPI_TRIG_OWN(GPP_E16, NONE, PLTRST, OFF, ACPI),
	PAD_CFG_NF(GPP_E17, NONE, DEEP, NF1),
	PAD_CFG_NF(GPP_E18, 20K_PU, DEEP, NF1),
	PAD_CFG_NF(GPP_E19, 20K_PD, DEEP, NF1),
	PAD_CFG_NF(GPP_E20, 20K_PU, DEEP, NF1),
	PAD_CFG_NF(GPP_E21, 20K_PD, DEEP, NF1),
	PAD_CFG_GPIO_BIDIRECT(GPP_E22, 0, NONE, DEEP, OFF, ACPI),
	PAD_CFG_TERM_GPO(GPP_E23, 1, 20K_PD, DEEP),
	PAD_CFG_NF(GPD0, 20K_PU, PWROK, NF1),
	PAD_CFG_NF(GPD1, NONE, PWROK, NF1),
	PAD_CFG_NF(GPD2, NATIVE, PWROK, NF1),
	PAD_CFG_NF(GPD3, 20K_PU, PWROK, NF1),
	PAD_CFG_NF(GPD4, NONE, PWROK, NF1),
	PAD_CFG_NF(GPD5, NONE, PWROK, NF1),
	PAD_CFG_NF(GPD6, NONE, PWROK, NF1),
	PAD_NC(GPD7, NONE),
	PAD_CFG_NF(GPD8, NONE, PWROK, NF1),
	PAD_CFG_NF(GPD9, NONE, PWROK, NF1),
	PAD_CFG_NF(GPD10, NONE, PWROK, NF1),
	PAD_CFG_NF(GPD11, NONE, PWROK, NF1),
	PAD_CFG_NF(GPP_F0, NONE, DEEP, NF1),
	PAD_CFG_NF(GPP_F1, NONE, DEEP, NF1),
	PAD_CFG_NF(GPP_F2, NONE, DEEP, NF1),
	PAD_CFG_NF(GPP_F3, NONE, DEEP, NF1),
	PAD_CFG_NF_1V8(GPP_F4, 20K_PU, DEEP, NF1),
	PAD_CFG_NF_1V8(GPP_F5, 20K_PU, DEEP, NF1),
	PAD_CFG_NF_1V8(GPP_F6, 20K_PU, DEEP, NF1),
	PAD_CFG_NF_1V8(GPP_F7, 20K_PU, DEEP, NF1),
	PAD_CFG_NF_1V8(GPP_F8, 20K_PU, DEEP, NF1),
	PAD_CFG_NF_1V8(GPP_F9, 20K_PU, DEEP, NF1),
	PAD_CFG_NF_1V8(GPP_F10, 20K_PU, DEEP, NF2),
	PAD_CFG_NF_1V8(GPP_F11, 20K_PU, DEEP, NF2),
	PAD_CFG_NF(GPP_F12, NONE, DEEP, NF1),
	PAD_CFG_NF(GPP_F13, NONE, DEEP, NF1),
	PAD_CFG_NF(GPP_F14, NONE, DEEP, NF1),
	PAD_CFG_NF(GPP_F15, NONE, DEEP, NF1),
	PAD_CFG_NF(GPP_F16, NONE, DEEP, NF1),
	PAD_CFG_NF(GPP_F17, NONE, DEEP, NF1),
	PAD_CFG_NF(GPP_F18, NONE, DEEP, NF1),
	PAD_CFG_NF(GPP_F19, NONE, DEEP, NF1),
	PAD_CFG_NF(GPP_F20, NONE, DEEP, NF1),
	PAD_CFG_NF(GPP_F21, NONE, DEEP, NF1),
	PAD_CFG_NF(GPP_F22, NONE, DEEP, NF1),
	PAD_CFG_GPI_TRIG_OWN(GPP_F23, NONE, DEEP, OFF, ACPI),
	PAD_CFG_NF(GPP_G0, NONE, DEEP, NF1),
	PAD_CFG_NF(GPP_G1, NONE, DEEP, NF1),
	PAD_CFG_NF(GPP_G2, NONE, DEEP, NF1),
	PAD_CFG_NF(GPP_G3, NONE, DEEP, NF1),
	PAD_CFG_NF(GPP_G4, NONE, DEEP, NF1),
	PAD_CFG_NF(GPP_G5, NONE, DEEP, NF1),
	PAD_CFG_NF(GPP_G6, NONE, DEEP, NF1),
	PAD_CFG_NF(GPP_G7, 20K_PD, DEEP, NF1),
};

#endif

#endif
