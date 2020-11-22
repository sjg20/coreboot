/* SPDX-License-Identifier: GPL-2.0-only */

#include <assert.h>
#include <boardid.h>
#include <console/console.h>
#include <soc/auxadc.h>

/* board_id is provided by ec/google/chromeec/ec_boardid.c */

#define ADC_LEVELS 15

enum {
	RAM_ID_CHANNEL = 3,
};

static const unsigned int ram_voltages[ADC_LEVELS] = {
	/* ID : Voltage (unit: uV) */
	[0]  =   74300,
	[1]  =  211700,
	[2]  =  318800,
	[3]  =  428600,
	[4]  =  541700,
	[5]  =  665800,
	[6]  =  781400,
	[7]  =  900000,
	[8]  = 1023100,
	[9]  = 1137000,
	[10] = 1240000,
	[11] = 1342600,
	[12] = 1457500,
	[13] = 1575600,
	[14] = 1683600,
};

static const unsigned int *adc_voltages[] = {
	[RAM_ID_CHANNEL] = ram_voltages,
};

static uint32_t get_adc_index(unsigned int channel)
{
	unsigned int value = auxadc_get_voltage_uv(channel);

	assert(channel < ARRAY_SIZE(adc_voltages));
	const unsigned int *voltages = adc_voltages[channel];
	assert(voltages);

	/* Find the closest voltage */
	uint32_t id;
	for (id = 0; id < ADC_LEVELS - 1; id++)
		if (value < (voltages[id] + voltages[id + 1]) / 2)
			break;

	printk(BIOS_DEBUG, "ADC[%u]: Raw value=%u ID=%u\n", channel, value, id);
	return id;
}

uint32_t sku_id(void)
{
	return 0;
}

uint32_t ram_code(void)
{
	static uint32_t cached_ram_code = BOARD_ID_INIT;

	if (cached_ram_code == BOARD_ID_INIT)
		cached_ram_code = get_adc_index(RAM_ID_CHANNEL);

	return cached_ram_code;
}
