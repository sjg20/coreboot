/** @file
 *
 * This file is automatically generated.
 *
 */

#ifndef __FSPSUPD_H__
#define __FSPSUPD_H__

#include <FspUpd.h>

#define FSPS_UPD_DXIO_DESCRIPTOR_COUNT	8
#define FSPS_UPD_DDI_DESCRIPTOR_COUNT	4
#define FSPS_UPD_USB2_PORT_COUNT	6
#define FSPS_UPD_RV2_USB3_PORT_COUNT	4

typedef struct __packed {
	/** Offset 0x0020**/	uint32_t                    emmc0_mode;
	/** Offset 0x0024**/	uint16_t                    emmc0_init_khz_preset;
	/** Offset 0x0026**/	uint8_t                     emmc0_sdr104_hs400_driver_strength;
	/** Offset 0x0027**/	uint8_t                     emmc0_ddr50_driver_strength;
	/** Offset 0x0028**/	uint8_t                     emmc0_sdr50_driver_strength;
	/** Offset 0x0029**/	uint8_t                     unused0[7];
	/** Offset 0x0030**/	uint8_t                     dxio_descriptor[FSPS_UPD_DXIO_DESCRIPTOR_COUNT][16];
	/** Offset 0x00B0**/	uint8_t                     unused1[16];
	/** Offset 0x00C0**/	uint32_t                    ddi_descriptor[FSPS_UPD_DDI_DESCRIPTOR_COUNT];
	/** Offset 0x00D0**/	uint8_t                     unused2[16];
	/** Offset 0x00E0**/	uint8_t                     fch_usb_version_major;
	/** Offset 0x00E1**/	uint8_t                     fch_usb_version_minor;
	/** Offset 0x00E2**/	uint8_t                     fch_usb_2_port_phy_tune[FSPS_UPD_USB2_PORT_COUNT][9];
	/** Offset 0x0118**/	uint8_t                     fch_usb_device_removable;
	/** Offset 0x0119**/	uint8_t                     fch_usb_3_port_force_gen1;
	/** Offset 0x011A**/	uint8_t                     fch_usb_u3_rx_det_wa_enable;
	/** Offset 0x011B**/	uint8_t                     fch_usb_u3_rx_det_wa_portmap;
	/** Offset 0x011C**/	uint8_t                     fch_usb_early_debug_select_enable;
	/** Offset 0x011D**/	uint8_t                     unused3;
	/** Offset 0x011E**/	uint32_t                    xhci_oc_pin_select;
	/** Offset 0x0122**/	uint8_t                     xhci0_force_gen1;
	/** Offset 0x0123**/	uint8_t                     xhci_sparse_mode_enable;
	/** Offset 0x0124**/	uint32_t                    gnb_ioapic_base;
	/** Offset 0x0128**/	uint8_t                     gnb_ioapic_id;
	/** Offset 0x0129**/	uint8_t                     fch_ioapic_id;
	/** Offset 0x012A**/	uint16_t                    edp_phy_override;
	/** Offset 0x012C**/	uint8_t                     edp_physel;
	/** Offset 0x012D**/	uint8_t                     edp_dp_vs_pemph_level;
	/** Offset 0x012E**/	uint16_t                    edp_margin_deemph;
	/** Offset 0x0130**/	uint8_t                     edp_deemph_6db_4;
	/** Offset 0x0131**/	uint8_t                     edp_boost_adj;
	/** Offset 0x0132**/	uint16_t                    backlight_pwmhz;
	/** Offset 0x0134**/	uint8_t                     pwron_digon_to_de;
	/** Offset 0x0135**/	uint8_t                     pwron_de_to_varybl;
	/** Offset 0x0136**/	uint8_t                     pwrdown_varybloff_to_de;
	/** Offset 0x0137**/	uint8_t                     pwrdown_de_to_digoff;
	/** Offset 0x0138**/	uint8_t                     pwroff_delay;
	/** Offset 0x0139**/	uint8_t                     pwron_varybl_to_blon;
	/** Offset 0x013A**/	uint8_t                     pwrdown_bloff_to_varybloff;
	/** Offset 0x013B**/	uint8_t                     min_allowed_bl_level;
	/** Offset 0x013C**/	uint8_t                     usb_3_phy_enable;
	/** Offset 0x013D**/	uint8_t                     usb_3_port_phy_tune[FSPS_UPD_RV2_USB3_PORT_COUNT][2];
	/** Offset 0x0145**/	uint8_t                     usb_3_rx_vref_ctrl;
	/** Offset 0x0146**/	uint8_t                     usb_3_rx_vref_ctrl_en;
	/** Offset 0x0147**/	uint8_t                     usb_3_tx_vboost_lvl;
	/** Offset 0x0148**/	uint8_t                     usb_3_tx_vboost_lvl_en;
	/** Offset 0x0149**/	uint8_t                     usb_3_rx_vref_ctrl_x;
	/** Offset 0x014A**/	uint8_t                     usb_3_rx_vref_ctrl_en_x;
	/** Offset 0x014B**/	uint8_t                     usb_3_tx_vboost_lvl_x;
	/** Offset 0x014C**/	uint8_t                     usb_3_tx_vboost_lvl_en_x;
	/** Offset 0x014D**/	uint8_t                     UnusedUpdSpace0[179];
	/** Offset 0x0200**/	uint16_t                    UpdTerminator;
} FSP_S_CONFIG;

/** Fsp S UPD Configuration
**/
typedef struct __packed {
	/** Offset 0x0000**/	FSP_UPD_HEADER              FspUpdHeader;
	/** Offset 0x0020**/	FSP_S_CONFIG                FspsConfig;
} FSPS_UPD;

#endif
