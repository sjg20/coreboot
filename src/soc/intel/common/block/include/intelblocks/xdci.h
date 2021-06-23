/* SPDX-License-Identifier: GPL-2.0-only */

#ifndef SOC_INTEL_COMMON_BLOCK_XDCI_H
#define SOC_INTEL_COMMON_BLOCK_XDCI_H

void soc_xdci_init(struct device *dev);
bool xdci_can_enable(unsigned int xdci_devfn);

#endif	/* SOC_INTEL_COMMON_BLOCK_XDCI_H */
