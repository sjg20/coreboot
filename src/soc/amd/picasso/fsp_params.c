/* SPDX-License-Identifier: GPL-2.0-only */
/* This file is part of the coreboot project. */

#include <device/pci.h>
#include <soc/pci_devs.h>
#include <soc/platform_descriptors.h>
#include <fsp/api.h>
#include "chip.h"

static void fill_pcie_descriptors(FSP_S_CONFIG *scfg,
			const picasso_fsp_pcie_descriptor *descs, size_t num)
{
	size_t i;
	picasso_fsp_pcie_descriptor *fsp_pcie;

	/* FIXME: this violates C rules. */
	fsp_pcie = (picasso_fsp_pcie_descriptor *)(scfg->dxio_descriptor0);

	for (i = 0; i < num; i++) {
		fsp_pcie[i] = descs[i];
	}
}

static void fill_ddi_descriptors(FSP_S_CONFIG *scfg,
			const picasso_fsp_ddi_descriptor *descs, size_t num)
{
	size_t i;
	picasso_fsp_ddi_descriptor *fsp_ddi;

	/* FIXME: this violates C rules. */
	fsp_ddi = (picasso_fsp_ddi_descriptor *)&(scfg->ddi_descriptor0);

	for (i = 0; i < num; i++) {
		fsp_ddi[i] = descs[i];
	}
}
static void fsp_fill_pcie_ddi_descriptors(FSP_S_CONFIG *scfg)
{
	const picasso_fsp_pcie_descriptor *fsp_pcie;
	const picasso_fsp_ddi_descriptor *fsp_ddi;
	size_t num_pcie;
	size_t num_ddi;

	mainboard_get_pcie_ddi_descriptors(&fsp_pcie, &num_pcie,
						&fsp_ddi, &num_ddi);
	fill_pcie_descriptors(scfg, fsp_pcie, num_pcie);
	fill_ddi_descriptors(scfg, fsp_ddi, num_ddi);
}

void platform_fsp_silicon_init_params_cb(FSPS_UPD *supd)
{
	FSP_S_CONFIG *scfg = &supd->FspsConfig;

	fsp_fill_pcie_ddi_descriptors(scfg);
}
