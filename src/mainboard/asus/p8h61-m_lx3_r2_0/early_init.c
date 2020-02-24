/* SPDX-License-Identifier: GPL-2.0-only */
/* This file is part of the coreboot project. */

#include <bootblock_common.h>
#include <device/pnp_ops.h>
#include <northbridge/intel/sandybridge/raminit_native.h>
#include <northbridge/intel/sandybridge/sandybridge.h>
#include <southbridge/intel/bd82x6x/pch.h>
#include <superio/nuvoton/common/nuvoton.h>
#include <superio/nuvoton/nct6779d/nct6779d.h>

#define GLOBAL_DEV PNP_DEV(0x2e, 0)
#define ACPI_DEV PNP_DEV(0x2e, NCT6779D_ACPI)

const struct southbridge_usb_port mainboard_usb_ports[] = {
	{ 1, 0, 0 },
	{ 1, 0, 0 },
	{ 1, 0, 1 },
	{ 1, 0, 1 },
	{ 1, 0, 2 },
	{ 1, 0, 2 },
	{ 1, 0, 3 },
	{ 1, 0, 3 },
	{ 1, 0, 4 },
	{ 1, 0, 4 },
	{ 1, 0, 6 },
	{ 1, 0, 5 },
	{ 1, 0, 5 },
	{ 1, 0, 6 },
};

void bootblock_mainboard_early_init(void)
{
	nuvoton_pnp_enter_conf_state(GLOBAL_DEV);

	/* Select SIO pin states */
	pnp_write_config(GLOBAL_DEV, 0x1a, 0x00);
	pnp_write_config(GLOBAL_DEV, 0x1c, 0x71);
	pnp_write_config(GLOBAL_DEV, 0x1d, 0x0e);
	pnp_write_config(GLOBAL_DEV, 0x22, 0xd7);
	pnp_write_config(GLOBAL_DEV, 0x2a, 0x48);
	pnp_write_config(GLOBAL_DEV, 0x2c, 0x00);

	/* Power RAM in S3 */
	pnp_set_logical_device(ACPI_DEV);
	pnp_write_config(ACPI_DEV, 0xe4, 0x10);

	nuvoton_pnp_exit_conf_state(GLOBAL_DEV);

	/* Do not enable UART, the header is not populated by default */
}

void mainboard_get_spd(spd_raw_data *spd, bool id_only)
{
	read_spd(&spd[0], 0x50, id_only);
	read_spd(&spd[2], 0x52, id_only);
}
