/* SPDX-License-Identifier: GPL-2.0-only */

#ifndef EC_GOOGLE_CHROMEEC_MUX_CONN_CHIP_H
#define EC_GOOGLE_CHROMEEC_MUX_CONN_CHIP_H

struct ec_google_chromeec_mux_conn_config {
	/* When set to true, this signifies that the mux device
	 * is used as a Type-C mode switch in addition to
	 * a retimer switch. */
	bool mode_switch;
};

#endif /* EC_GOOGLE_CHROMEEC_MUX_CONN_CHIP_H */
