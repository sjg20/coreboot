/* SPDX-License-Identifier: GPL-2.0-only */

#include <soc/pei_data.h>
#include <soc/pei_wrapper.h>

/* Copy SPD data for on-board memory */
void mainboard_fill_spd_data(struct pei_data *pei_data)
{
	pei_data->spd_addresses[0] = 0xa0;
	pei_data->spd_addresses[2] = 0xa4;
}
