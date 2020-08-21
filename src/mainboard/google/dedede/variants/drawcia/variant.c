/* SPDX-License-Identifier: GPL-2.0-only */

#include <bootstate.h>
#include <console/console.h>
#include <fw_config.h>
#include <sar.h>

const char *get_wifi_sar_cbfs_filename(void)
{
	const char *filename = NULL;

	if (fw_config_probe(FW_CONFIG(TABLETMODE, TABLETMODE_ENABLED)))
		filename = "wifi_sar-drawcia.hex";

	printk(BIOS_INFO, "SAR file name: %s\n", filename);
	return filename;
}
