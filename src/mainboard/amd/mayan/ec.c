/* SPDX-License-Identifier: GPL-2.0-only */

/* TODO: Update for mayan */

#include <ec/acpi/ec.h>
#include "ec.h"

#define MAYAN_EC_CMD		0x666
#define MAYAN_EC_DATA		0x662

#define EC_GPIO_3_ADDR		0xA3
#define EC_GPIO_LOM_RESET_AUX	BIT(1)

#define EC_GPIO_7_ADDR		0xA7
#define EC_GPIO_DT_PWREN	BIT(2)
#define EC_GPIO_WWAN_MODULE_RST	BIT(5)

#define EC_GPIO_8_ADDR		0xA8
#define EC_GPIO_SMBUS0_EN	BIT(0)

#define EC_GPIO_A_ADDR		0xAA
#define EC_GPIO_WWAN_PWREN	BIT(3)
#define EC_GPIO_M2_SSD0_PWREN	BIT(6)
#define EC_GPIO_LOM_PWREN	BIT(7)

#define EC_GPIO_C_ADDR		0xAC
#define EC_GPIO_DT_N_WLAN_SW	BIT(1)
#define EC_GPIO_MP2_SEL		BIT(2)
#define EC_GPIO_WWAN_N_LOM_SW	BIT(3)

#define EC_SW02_ADDR		0xB7
#define EC_SW02_MS		BIT(7)

static void configure_ec_gpio(void)
{
	uint8_t tmp;

	tmp = ec_read(EC_GPIO_3_ADDR);
	tmp |= EC_GPIO_LOM_RESET_AUX;
	ec_write(EC_GPIO_3_ADDR, tmp);

	tmp = ec_read(EC_GPIO_7_ADDR);
	tmp |= EC_GPIO_WWAN_MODULE_RST | EC_GPIO_DT_PWREN;
	ec_write(EC_GPIO_7_ADDR, tmp);

	tmp = ec_read(EC_GPIO_8_ADDR);
	tmp |= EC_GPIO_SMBUS0_EN;
	ec_write(EC_GPIO_8_ADDR, tmp);

	tmp = ec_read(EC_GPIO_A_ADDR);
	tmp |= EC_GPIO_M2_SSD0_PWREN | EC_GPIO_LOM_PWREN | EC_GPIO_WWAN_PWREN;
	ec_write(EC_GPIO_A_ADDR, tmp);

	tmp = ec_read(EC_GPIO_C_ADDR);
	tmp |= EC_GPIO_WWAN_N_LOM_SW | EC_GPIO_MP2_SEL | EC_GPIO_DT_N_WLAN_SW;
	ec_write(EC_GPIO_C_ADDR, tmp);

	tmp = ec_read(EC_SW02_ADDR);
	tmp |= EC_SW02_MS;
	ec_write(EC_SW02_ADDR, tmp);
}

void mayan_ec_init(void)
{
	ec_set_ports(MAYAN_EC_CMD, MAYAN_EC_DATA);
	configure_ec_gpio();
}
