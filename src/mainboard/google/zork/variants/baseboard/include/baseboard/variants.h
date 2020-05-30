/* SPDX-License-Identifier: GPL-2.0-or-later */


#ifndef __BASEBOARD_VARIANTS_H__
#define __BASEBOARD_VARIANTS_H__

#include <stddef.h>
#include <boardid.h>
#include <ec/google/chromeec/ec.h>
#include <soc/platform_descriptors.h>
#include "chip.h"

const struct sci_source *get_gpe_table(size_t *num);
const struct soc_amd_gpio *variant_early_gpio_table(size_t *size);
const struct soc_amd_gpio *variant_romstage_gpio_table(size_t *size);
const struct soc_amd_gpio *variant_wifi_romstage_gpio_table(size_t *size);
/*
 * This function provides base GPIO configuration table. It is typically provided by
 * baseboard using a weak implementation. If GPIO configuration for a variant differs
 * significantly from the baseboard, then the variant can also provide a strong implementation
 * of this function.
 */
const struct soc_amd_gpio *variant_base_gpio_table(size_t *size);
/*
 * This function allows variant to override any GPIOs that are different than the base GPIO
 * configuration provided by variant_base_gpio_table().
 */
const struct soc_amd_gpio *variant_override_gpio_table(size_t *size);
void variant_romstage_entry(void);
/* Modify devictree settings during ramstage. */
void variant_devtree_update(void);

/* Per variant FSP-S initialization, default implementation in baseboard and
 * overrideable by the variant. */
void variant_get_pcie_ddi_descriptors(const picasso_fsp_pcie_descriptor **pcie_descs,
				      size_t *pcie_num,
				      const picasso_fsp_ddi_descriptor **ddi_descs,
				      size_t *ddi_num);

/* Provide the descriptors for the associated baseboard for the variant. These functions
 * can be used for obtaining the baseboard's descriptors if the variant followed the
 * baseboard. */
const picasso_fsp_pcie_descriptor *baseboard_get_pcie_descriptors(size_t *num);
const picasso_fsp_ddi_descriptor *baseboard_get_ddi_descriptors(size_t *num);

/* Retrieve attributes from FW_CONFIG in CBI. */
/* Return 1 if FW_CONFIG expected to be valid, else 0. */
int variant_fw_config_valid(void);
/* Return 0 if non-existent, 1 if present. */
int variant_has_emmc(void);
/* Return 0 if non-existent, 1 if present. */
int variant_has_nvme(void);

/* Determine if booting in factory by using CROS_SKU_UNPROVISIONED. */
int boot_is_factory_unprovisioned(void);

#endif /* __BASEBOARD_VARIANTS_H__ */
