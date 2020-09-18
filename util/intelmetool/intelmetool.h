/* SPDX-License-Identifier: GPL-2.0-only */

#define ME_NOT_PRESENT 0
#define ME_FOUND_NOTHING 1
#define ME_FOUND_SOMETHING_NOT_SURE 2
#define ME_CAN_DISABLE_IF_PRESENT 3
#define ME_PRESENT_CAN_DISABLE 4
#define ME_PRESENT_CANNOT_DISABLE 5

#define INTELMETOOL_VERSION "1.1"

#define GPLV2COPYRIGHT \
"This program is free software: you can redistribute it and/or modify\n" \
"it under the terms of the GNU General Public License as published by\n" \
"the Free Software Foundation, version 2 of the License.\n\n" \
"This program is distributed in the hope that it will be useful,\n" \
"but WITHOUT ANY WARRANTY; without even the implied warranty of\n" \
"MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n" \
"GNU General Public License for more details.\n\n"

#if defined(__GLIBC__)
#include <sys/io.h>
#endif
#if (defined(__MACH__) && defined(__APPLE__))
/* DirectHW is available here: https://www.coreboot.org/DirectHW */
#define __DARWIN__
#include <DirectHW/DirectHW.h>
#endif
#ifdef __NetBSD__
#include <pciutils/pci.h>
#else
#include <pci/pci.h>
#endif

#define CNRM  "\x1B[0m"
#define CRED  "\x1B[31m"
#define CGRN  "\x1B[32m"
#define CYEL  "\x1B[33m"
#define CBLU  "\x1B[34m"
#define CMAG  "\x1B[35m"
#define CCYN  "\x1B[36m"
#define CWHT  "\x1B[37m"
#define RESET "\033[0m"

#define CPU_ID_SIZE 13
#define FD2 0x3428
#define ME_COMMAND_DELAY 10000
#define ME_MESSAGE_LEN 256

extern int debug;

#define PCI_VENDOR_ID_INTEL 0x8086

// Chipset does not have ME
#define PCI_DEVICE_ID_INTEL_82810		0x7120
#define PCI_DEVICE_ID_INTEL_82810_DC		0x7122
#define PCI_DEVICE_ID_INTEL_82810E_DC		0x7124
#define PCI_DEVICE_ID_INTEL_82830M		0x3575
#define PCI_DEVICE_ID_INTEL_82845		0x1a30
#define PCI_DEVICE_ID_INTEL_82865		0x2570
#define PCI_DEVICE_ID_INTEL_82915		0x2580
#define PCI_DEVICE_ID_INTEL_82945P		0x2770
#define PCI_DEVICE_ID_INTEL_82945GM		0x27a0
#define PCI_DEVICE_ID_INTEL_82945GSE		0x27ac
#define PCI_DEVICE_ID_INTEL_82X58		0x3405
#define PCI_DEVICE_ID_INTEL_ATOM_DXXX		0xa000
#define PCI_DEVICE_ID_INTEL_I63XX		0x2670
#define PCI_DEVICE_ID_INTEL_I5000X		0x25c0
#define PCI_DEVICE_ID_INTEL_I5000Z		0x25d0
#define PCI_DEVICE_ID_INTEL_I5000V		0x25d4
#define PCI_DEVICE_ID_INTEL_I5000P		0x25d8
#define PCI_DEVICE_ID_INTEL_82443LX		0x7180
#define PCI_DEVICE_ID_INTEL_82443BX		0x7190
#define PCI_DEVICE_ID_INTEL_82443BX_NO_AGP	0x7192
#define PCI_DEVICE_ID_INTEL_82371XX		0x7110
#define PCI_DEVICE_ID_INTEL_ICH			0x2410
#define PCI_DEVICE_ID_INTEL_ICH0		0x2420
#define PCI_DEVICE_ID_INTEL_ICH2		0x2440
#define PCI_DEVICE_ID_INTEL_ICH4		0x24c0
#define PCI_DEVICE_ID_INTEL_ICH4M		0x24cc
#define PCI_DEVICE_ID_INTEL_ICH5		0x24d0
#define PCI_DEVICE_ID_INTEL_ICH6		0x2640
#define PCI_DEVICE_ID_INTEL_ICH7DH		0x27b0
#define PCI_DEVICE_ID_INTEL_ICH7		0x27b8
#define PCI_DEVICE_ID_INTEL_ICH7M		0x27b9
#define PCI_DEVICE_ID_INTEL_ICH7MDH		0x27bd
#define PCI_DEVICE_ID_INTEL_NM10		0x27bc

#define PCI_DEV_NO_ME(x) ( \
	((x) == PCI_DEVICE_ID_INTEL_82810) || \
	((x) == PCI_DEVICE_ID_INTEL_82810_DC) || \
	((x) == PCI_DEVICE_ID_INTEL_82810E_DC) || \
	((x) == PCI_DEVICE_ID_INTEL_82830M) || \
	((x) == PCI_DEVICE_ID_INTEL_82845) || \
	((x) == PCI_DEVICE_ID_INTEL_82865) || \
	((x) == PCI_DEVICE_ID_INTEL_82915) || \
	((x) == PCI_DEVICE_ID_INTEL_82945P) || \
	((x) == PCI_DEVICE_ID_INTEL_82945GM) || \
	((x) == PCI_DEVICE_ID_INTEL_82945GSE) || \
	((x) == PCI_DEVICE_ID_INTEL_82X58) || \
	((x) == PCI_DEVICE_ID_INTEL_ATOM_DXXX) || \
	((x) == PCI_DEVICE_ID_INTEL_I63XX) || \
	((x) == PCI_DEVICE_ID_INTEL_I5000X) || \
	((x) == PCI_DEVICE_ID_INTEL_I5000Z) || \
	((x) == PCI_DEVICE_ID_INTEL_I5000V) || \
	((x) == PCI_DEVICE_ID_INTEL_I5000P) || \
	((x) == PCI_DEVICE_ID_INTEL_82443LX) || \
	((x) == PCI_DEVICE_ID_INTEL_82443BX) || \
	((x) == PCI_DEVICE_ID_INTEL_82443BX_NO_AGP) || \
	((x) == PCI_DEVICE_ID_INTEL_82371XX) || \
	((x) == PCI_DEVICE_ID_INTEL_ICH) || \
	((x) == PCI_DEVICE_ID_INTEL_ICH0) || \
	((x) == PCI_DEVICE_ID_INTEL_ICH2) || \
	((x) == PCI_DEVICE_ID_INTEL_ICH4) || \
	((x) == PCI_DEVICE_ID_INTEL_ICH4M) || \
	((x) == PCI_DEVICE_ID_INTEL_ICH5) || \
	((x) == PCI_DEVICE_ID_INTEL_ICH6) || \
	((x) == PCI_DEVICE_ID_INTEL_ICH7DH) || \
	((x) == PCI_DEVICE_ID_INTEL_ICH7) || \
	((x) == PCI_DEVICE_ID_INTEL_ICH7M) || \
	((x) == PCI_DEVICE_ID_INTEL_ICH7MDH) || \
	((x) == PCI_DEVICE_ID_INTEL_NM10))

// Definitely has ME and can be disabled
#define PCI_DEVICE_ID_INTEL_ICH8ME		0x2811
#define PCI_DEVICE_ID_INTEL_ICH9ME		0x2917
#define PCI_DEVICE_ID_INTEL_ICH9M		0x2919

#define PCI_DEV_HAS_ME_DISABLE(x) ( \
	((x) == PCI_DEVICE_ID_INTEL_ICH8ME) || \
	((x) == PCI_DEVICE_ID_INTEL_ICH9ME) || \
	((x) == PCI_DEVICE_ID_INTEL_ICH9M))

// Definitely has ME and is very difficult to remove
#define PCI_DEVICE_ID_INTEL_ICH10R		0x3a16
#define PCI_DEVICE_ID_INTEL_3400_DESKTOP	0x3b00
#define PCI_DEVICE_ID_INTEL_3400_MOBILE		0x3b01
#define PCI_DEVICE_ID_INTEL_P55			0x3b02
#define PCI_DEVICE_ID_INTEL_PM55		0x3b03
#define PCI_DEVICE_ID_INTEL_H55			0x3b06
#define PCI_DEVICE_ID_INTEL_QM57		0x3b07
#define PCI_DEVICE_ID_INTEL_H57			0x3b08
#define PCI_DEVICE_ID_INTEL_HM55		0x3b09
#define PCI_DEVICE_ID_INTEL_Q57			0x3b0a
#define PCI_DEVICE_ID_INTEL_HM57		0x3b0b
#define PCI_DEVICE_ID_INTEL_3400_MOBILE_SFF	0x3b0d
#define PCI_DEVICE_ID_INTEL_B55_A		0x3b0e
#define PCI_DEVICE_ID_INTEL_QS57		0x3b0f
#define PCI_DEVICE_ID_INTEL_3400		0x3b12
#define PCI_DEVICE_ID_INTEL_3420		0x3b14
#define PCI_DEVICE_ID_INTEL_3450		0x3b16
#define PCI_DEVICE_ID_INTEL_B55_B		0x3b1e
#define PCI_DEVICE_ID_INTEL_Z68			0x1c44
#define PCI_DEVICE_ID_INTEL_P67			0x1c46
#define PCI_DEVICE_ID_INTEL_UM67		0x1c47
#define PCI_DEVICE_ID_INTEL_HM65		0x1c49
#define PCI_DEVICE_ID_INTEL_H67			0x1c4a
#define PCI_DEVICE_ID_INTEL_HM67		0x1c4b
#define PCI_DEVICE_ID_INTEL_Q65			0x1c4c
#define PCI_DEVICE_ID_INTEL_QS67		0x1c4d
#define PCI_DEVICE_ID_INTEL_Q67			0x1c4e
#define PCI_DEVICE_ID_INTEL_QM67		0x1c4f
#define PCI_DEVICE_ID_INTEL_B65			0x1c50
#define PCI_DEVICE_ID_INTEL_C202		0x1c52
#define PCI_DEVICE_ID_INTEL_C204		0x1c54
#define PCI_DEVICE_ID_INTEL_C206		0x1c56
#define PCI_DEVICE_ID_INTEL_H61			0x1c5c
#define PCI_DEVICE_ID_INTEL_Z77			0x1e44
#define PCI_DEVICE_ID_INTEL_Z75			0x1e46
#define PCI_DEVICE_ID_INTEL_Q77			0x1e47
#define PCI_DEVICE_ID_INTEL_Q75			0x1e48
#define PCI_DEVICE_ID_INTEL_B75			0x1e49
#define PCI_DEVICE_ID_INTEL_H77			0x1e4a
#define PCI_DEVICE_ID_INTEL_C216		0x1e53
#define PCI_DEVICE_ID_INTEL_QM77		0x1e55
#define PCI_DEVICE_ID_INTEL_QS77		0x1e56
#define PCI_DEVICE_ID_INTEL_HM77		0x1e57
#define PCI_DEVICE_ID_INTEL_UM77		0x1e58
#define PCI_DEVICE_ID_INTEL_HM76		0x1e59
#define PCI_DEVICE_ID_INTEL_HM75		0x1e5d
#define PCI_DEVICE_ID_INTEL_HM70		0x1e5e
#define PCI_DEVICE_ID_INTEL_NM70		0x1e5f
#define PCI_DEVICE_ID_INTEL_DH89XXCC		0x2310
#define PCI_DEVICE_ID_INTEL_LYNXPOINT_LP_FULL	0x9c41
#define PCI_DEVICE_ID_INTEL_LYNXPOINT_LP_PREM	0x9c43
#define PCI_DEVICE_ID_INTEL_LYNXPOINT_LP_BASE	0x9c45
#define PCI_DEVICE_ID_INTEL_H81			0x8c5c
#define PCI_DEVICE_ID_INTEL_B85			0x8c50
#define PCI_DEVICE_ID_INTEL_Q85			0x8c4c
#define PCI_DEVICE_ID_INTEL_Q87			0x8c4e
#define PCI_DEVICE_ID_INTEL_QM87		0x8c4f
#define PCI_DEVICE_ID_INTEL_H87			0x8c4a
#define PCI_DEVICE_ID_INTEL_HM87		0x8c4b
#define PCI_DEVICE_ID_INTEL_Z87			0x8c44
#define PCI_DEVICE_ID_INTEL_X99			0x8d47
#define PCI_DEVICE_ID_INTEL_WILDCAT_LP1		0x9cc1
#define PCI_DEVICE_ID_INTEL_WILDCAT_LP2		0x9cc2
#define PCI_DEVICE_ID_INTEL_WILDCAT_LP3		0x9cc3
#define PCI_DEVICE_ID_INTEL_WILDCAT_LP4		0x9cc5
#define PCI_DEVICE_ID_INTEL_WILDCAT_LP5		0x9cc6
#define PCI_DEVICE_ID_INTEL_WILDCAT_LP6		0x9cc7
#define PCI_DEVICE_ID_INTEL_WILDCAT_LP7		0x9cc9
#define PCI_DEVICE_ID_INTEL_SUNRISE_LP1		0x9d43
#define PCI_DEVICE_ID_INTEL_SUNRISE_LP2		0x9d48
#define PCI_DEVICE_ID_INTEL_SUNRISE_LP3		0x9d4e
#define PCI_DEVICE_ID_INTEL_SUNRISE_LP4		0x9d56
#define PCI_DEVICE_ID_INTEL_SUNRISE_LP5		0x9d58
#define PCI_DEVICE_ID_INTEL_SUNRISE_H0		0xa140
#define PCI_DEVICE_ID_INTEL_SUNRISE_H1		0xa141
#define PCI_DEVICE_ID_INTEL_SUNRISE_H2		0xa142
#define PCI_DEVICE_ID_INTEL_SUNRISE_H3		0xa143
#define PCI_DEVICE_ID_INTEL_SUNRISE_H4		0xa144
#define PCI_DEVICE_ID_INTEL_SUNRISE_H5		0xa145
#define PCI_DEVICE_ID_INTEL_SUNRISE_H6		0xa146
#define PCI_DEVICE_ID_INTEL_SUNRISE_H7		0xa147
#define PCI_DEVICE_ID_INTEL_SUNRISE_H8		0xa148
#define PCI_DEVICE_ID_INTEL_SUNRISE_H9		0xa149
#define PCI_DEVICE_ID_INTEL_SUNRISE_H10		0xa14a
#define PCI_DEVICE_ID_INTEL_SUNRISE_H11		0xa14b
#define PCI_DEVICE_ID_INTEL_SUNRISE_H12		0xa14c
#define PCI_DEVICE_ID_INTEL_SUNRISE_H13		0xa14d
#define PCI_DEVICE_ID_INTEL_SUNRISE_H14		0xa14e
#define PCI_DEVICE_ID_INTEL_SUNRISE_H15		0xa14f
#define PCI_DEVICE_ID_INTEL_SUNRISE_H16		0xa150
#define PCI_DEVICE_ID_INTEL_SUNRISE_H17		0xa151
#define PCI_DEVICE_ID_INTEL_SUNRISE_H18		0xa152
#define PCI_DEVICE_ID_INTEL_SUNRISE_H19		0xa153
#define PCI_DEVICE_ID_INTEL_SUNRISE_H20		0xa154
#define PCI_DEVICE_ID_INTEL_SUNRISE_H21		0xa155
#define PCI_DEVICE_ID_INTEL_SUNRISE_H22		0xa156
#define PCI_DEVICE_ID_INTEL_SUNRISE_H23		0xa157
#define PCI_DEVICE_ID_INTEL_SUNRISE_H24		0xa158
#define PCI_DEVICE_ID_INTEL_SUNRISE_H25		0xa159
#define PCI_DEVICE_ID_INTEL_SUNRISE_H26		0xa15a
#define PCI_DEVICE_ID_INTEL_SUNRISE_H27		0xa15b
#define PCI_DEVICE_ID_INTEL_SUNRISE_H28		0xa15c
#define PCI_DEVICE_ID_INTEL_SUNRISE_H29		0xa15d
#define PCI_DEVICE_ID_INTEL_SUNRISE_H30		0xa15e
#define PCI_DEVICE_ID_INTEL_SUNRISE_H31		0xa15f
#define PCI_DEVICE_ID_INTEL_LEWISBURG_1		0xa1c1
#define PCI_DEVICE_ID_INTEL_LEWISBURG_2		0xa1c2
#define PCI_DEVICE_ID_INTEL_LEWISBURG_3		0xa1c3
#define PCI_DEVICE_ID_INTEL_LEWISBURG_4		0xa1c4
#define PCI_DEVICE_ID_INTEL_LEWISBURG_5		0xa1c5
#define PCI_DEVICE_ID_INTEL_LEWISBURG_6		0xa1c6
#define PCI_DEVICE_ID_INTEL_LEWISBURG_7		0xa1c7

#define PCI_DEV_HAS_ME_DIFFICULT(x) ( \
	((x) == PCI_DEVICE_ID_INTEL_ICH10R) || \
	((x) == PCI_DEVICE_ID_INTEL_3400_DESKTOP) || \
	((x) == PCI_DEVICE_ID_INTEL_3400_MOBILE) || \
	((x) == PCI_DEVICE_ID_INTEL_P55) || \
	((x) == PCI_DEVICE_ID_INTEL_PM55) || \
	((x) == PCI_DEVICE_ID_INTEL_H55) || \
	((x) == PCI_DEVICE_ID_INTEL_QM57) || \
	((x) == PCI_DEVICE_ID_INTEL_H57) || \
	((x) == PCI_DEVICE_ID_INTEL_HM55) || \
	((x) == PCI_DEVICE_ID_INTEL_Q57) || \
	((x) == PCI_DEVICE_ID_INTEL_HM57) || \
	((x) == PCI_DEVICE_ID_INTEL_3400_MOBILE_SFF) || \
	((x) == PCI_DEVICE_ID_INTEL_B55_A) || \
	((x) == PCI_DEVICE_ID_INTEL_QS57) || \
	((x) == PCI_DEVICE_ID_INTEL_3400) || \
	((x) == PCI_DEVICE_ID_INTEL_3420) || \
	((x) == PCI_DEVICE_ID_INTEL_3450) || \
	((x) == PCI_DEVICE_ID_INTEL_B55_B) || \
	((x) == PCI_DEVICE_ID_INTEL_Z68) || \
	((x) == PCI_DEVICE_ID_INTEL_P67) || \
	((x) == PCI_DEVICE_ID_INTEL_UM67) || \
	((x) == PCI_DEVICE_ID_INTEL_HM65) || \
	((x) == PCI_DEVICE_ID_INTEL_H67) || \
	((x) == PCI_DEVICE_ID_INTEL_HM67) || \
	((x) == PCI_DEVICE_ID_INTEL_Q65) || \
	((x) == PCI_DEVICE_ID_INTEL_QS67) || \
	((x) == PCI_DEVICE_ID_INTEL_Q67) || \
	((x) == PCI_DEVICE_ID_INTEL_QM67) || \
	((x) == PCI_DEVICE_ID_INTEL_B65) || \
	((x) == PCI_DEVICE_ID_INTEL_C202) || \
	((x) == PCI_DEVICE_ID_INTEL_C204) || \
	((x) == PCI_DEVICE_ID_INTEL_C206) || \
	((x) == PCI_DEVICE_ID_INTEL_H61) || \
	((x) == PCI_DEVICE_ID_INTEL_Z77) || \
	((x) == PCI_DEVICE_ID_INTEL_Z75) || \
	((x) == PCI_DEVICE_ID_INTEL_Q77) || \
	((x) == PCI_DEVICE_ID_INTEL_Q75) || \
	((x) == PCI_DEVICE_ID_INTEL_B75) || \
	((x) == PCI_DEVICE_ID_INTEL_H77) || \
	((x) == PCI_DEVICE_ID_INTEL_C216) || \
	((x) == PCI_DEVICE_ID_INTEL_QM77) || \
	((x) == PCI_DEVICE_ID_INTEL_QS77) || \
	((x) == PCI_DEVICE_ID_INTEL_HM77) || \
	((x) == PCI_DEVICE_ID_INTEL_UM77) || \
	((x) == PCI_DEVICE_ID_INTEL_HM76) || \
	((x) == PCI_DEVICE_ID_INTEL_HM75) || \
	((x) == PCI_DEVICE_ID_INTEL_HM70) || \
	((x) == PCI_DEVICE_ID_INTEL_NM70) || \
	((x) == PCI_DEVICE_ID_INTEL_DH89XXCC) || \
	((x) == PCI_DEVICE_ID_INTEL_LYNXPOINT_LP_FULL) || \
	((x) == PCI_DEVICE_ID_INTEL_LYNXPOINT_LP_PREM) || \
	((x) == PCI_DEVICE_ID_INTEL_LYNXPOINT_LP_BASE) || \
	((x) == PCI_DEVICE_ID_INTEL_H81) || \
	((x) == PCI_DEVICE_ID_INTEL_B85) || \
	((x) == PCI_DEVICE_ID_INTEL_Q85) || \
	((x) == PCI_DEVICE_ID_INTEL_Q87) || \
	((x) == PCI_DEVICE_ID_INTEL_QM87) || \
	((x) == PCI_DEVICE_ID_INTEL_H87) || \
	((x) == PCI_DEVICE_ID_INTEL_HM87) || \
	((x) == PCI_DEVICE_ID_INTEL_Z87) || \
	((x) == PCI_DEVICE_ID_INTEL_X99) || \
	((x) == PCI_DEVICE_ID_INTEL_WILDCAT_LP1) || \
	((x) == PCI_DEVICE_ID_INTEL_WILDCAT_LP2) || \
	((x) == PCI_DEVICE_ID_INTEL_WILDCAT_LP3) || \
	((x) == PCI_DEVICE_ID_INTEL_WILDCAT_LP4) || \
	((x) == PCI_DEVICE_ID_INTEL_WILDCAT_LP5) || \
	((x) == PCI_DEVICE_ID_INTEL_WILDCAT_LP6) || \
	((x) == PCI_DEVICE_ID_INTEL_WILDCAT_LP7) || \
	((x) == PCI_DEVICE_ID_INTEL_SUNRISE_LP1) || \
	((x) == PCI_DEVICE_ID_INTEL_SUNRISE_LP2) || \
	((x) == PCI_DEVICE_ID_INTEL_SUNRISE_LP3) || \
	((x) == PCI_DEVICE_ID_INTEL_SUNRISE_LP4) || \
	((x) == PCI_DEVICE_ID_INTEL_SUNRISE_LP5) || \
	((x) == PCI_DEVICE_ID_INTEL_SUNRISE_H0) || \
	((x) == PCI_DEVICE_ID_INTEL_SUNRISE_H1) || \
	((x) == PCI_DEVICE_ID_INTEL_SUNRISE_H2) || \
	((x) == PCI_DEVICE_ID_INTEL_SUNRISE_H3) || \
	((x) == PCI_DEVICE_ID_INTEL_SUNRISE_H4) || \
	((x) == PCI_DEVICE_ID_INTEL_SUNRISE_H5) || \
	((x) == PCI_DEVICE_ID_INTEL_SUNRISE_H6) || \
	((x) == PCI_DEVICE_ID_INTEL_SUNRISE_H7) || \
	((x) == PCI_DEVICE_ID_INTEL_SUNRISE_H8) || \
	((x) == PCI_DEVICE_ID_INTEL_SUNRISE_H9) || \
	((x) == PCI_DEVICE_ID_INTEL_SUNRISE_H10) || \
	((x) == PCI_DEVICE_ID_INTEL_SUNRISE_H11) || \
	((x) == PCI_DEVICE_ID_INTEL_SUNRISE_H12) || \
	((x) == PCI_DEVICE_ID_INTEL_SUNRISE_H13) || \
	((x) == PCI_DEVICE_ID_INTEL_SUNRISE_H14) || \
	((x) == PCI_DEVICE_ID_INTEL_SUNRISE_H15) || \
	((x) == PCI_DEVICE_ID_INTEL_SUNRISE_H16) || \
	((x) == PCI_DEVICE_ID_INTEL_SUNRISE_H17) || \
	((x) == PCI_DEVICE_ID_INTEL_SUNRISE_H18) || \
	((x) == PCI_DEVICE_ID_INTEL_SUNRISE_H19) || \
	((x) == PCI_DEVICE_ID_INTEL_SUNRISE_H20) || \
	((x) == PCI_DEVICE_ID_INTEL_SUNRISE_H21) || \
	((x) == PCI_DEVICE_ID_INTEL_SUNRISE_H22) || \
	((x) == PCI_DEVICE_ID_INTEL_SUNRISE_H23) || \
	((x) == PCI_DEVICE_ID_INTEL_SUNRISE_H24) || \
	((x) == PCI_DEVICE_ID_INTEL_SUNRISE_H25) || \
	((x) == PCI_DEVICE_ID_INTEL_SUNRISE_H26) || \
	((x) == PCI_DEVICE_ID_INTEL_SUNRISE_H27) || \
	((x) == PCI_DEVICE_ID_INTEL_SUNRISE_H28) || \
	((x) == PCI_DEVICE_ID_INTEL_SUNRISE_H29) || \
	((x) == PCI_DEVICE_ID_INTEL_SUNRISE_H30) || \
	((x) == PCI_DEVICE_ID_INTEL_SUNRISE_H31) || \
	((x) == PCI_DEVICE_ID_INTEL_LEWISBURG_1) || \
	((x) == PCI_DEVICE_ID_INTEL_LEWISBURG_2) || \
	((x) == PCI_DEVICE_ID_INTEL_LEWISBURG_3) || \
	((x) == PCI_DEVICE_ID_INTEL_LEWISBURG_4) || \
	((x) == PCI_DEVICE_ID_INTEL_LEWISBURG_5) || \
	((x) == PCI_DEVICE_ID_INTEL_LEWISBURG_6) || \
	((x) == PCI_DEVICE_ID_INTEL_LEWISBURG_7) || \
	0)

// Not sure if ME present, but should be able to disable it easily
#define PCI_DEVICE_ID_INTEL_ICH8		0x2810
#define PCI_DEVICE_ID_INTEL_ICH8M		0x2815
#define PCI_DEVICE_ID_INTEL_ICH9DH		0x2912
#define PCI_DEVICE_ID_INTEL_ICH9DO		0x2914
#define PCI_DEVICE_ID_INTEL_ICH9R		0x2916
#define PCI_DEVICE_ID_INTEL_ICH9		0x2918

#define PCI_DEV_CAN_DISABLE_ME_IF_PRESENT(x) ( \
	((x) == PCI_DEVICE_ID_INTEL_ICH8) || \
	((x) == PCI_DEVICE_ID_INTEL_ICH8M) || \
	((x) == PCI_DEVICE_ID_INTEL_ICH9DH) || \
	((x) == PCI_DEVICE_ID_INTEL_ICH9DO) || \
	((x) == PCI_DEVICE_ID_INTEL_ICH9R) || \
	((x) == PCI_DEVICE_ID_INTEL_ICH9))

// Not sure at all
#define PCI_DEVICE_ID_INTEL_SCH_POULSBO_LPC	0x8119
#define PCI_DEVICE_ID_INTEL_SCH_POULSBO		0x8100

#define PCI_DEV_ME_NOT_SURE(x) ( \
	((x) == PCI_DEVICE_ID_INTEL_SCH_POULSBO_LPC) || \
	((x) == PCI_DEVICE_ID_INTEL_SCH_POULSBO))

// ME PCI IDs (HECI)
#define PCI_DEVICE_ID_INTEL_COUGARPOINT_1	0x1C3A /* Cougar Point */
#define PCI_DEVICE_ID_INTEL_PATSBURG_1	0x1D3A /* C600/X79 Patsburg */
#define PCI_DEVICE_ID_INTEL_PANTHERPOINT_1	0x1CBA /* Panther Point */
#define PCI_DEVICE_ID_INTEL_PANTHERPOINT_2	0x1DBA /* Panther Point */
#define PCI_DEVICE_ID_INTEL_PANTHERPOINT_3	0x1E3A /* Panther Point */
#define PCI_DEVICE_ID_INTEL_CAVECREEK	0x2364 /* Cave Creek */
#define PCI_DEVICE_ID_INTEL_BEARLAKE_1 0x28B4 /* Bearlake */
#define PCI_DEVICE_ID_INTEL_BEARLAKE_2 0x28C4 /* Bearlake */
#define PCI_DEVICE_ID_INTEL_BEARLAKE_3 0x28D4 /* Bearlake */
#define PCI_DEVICE_ID_INTEL_BEARLAKE_4 0x28E4 /* Bearlake */
#define PCI_DEVICE_ID_INTEL_BEARLAKE_5 0x28F4 /* Bearlake */
#define PCI_DEVICE_ID_INTEL_82946GZ 0x2974 /* 82946GZ/GL */
#define PCI_DEVICE_ID_INTEL_82G35	0x2984 /* 82G35 Express */
#define PCI_DEVICE_ID_INTEL_82Q963	0x2994 /* 82Q963/Q965 */
#define PCI_DEVICE_ID_INTEL_82P965 0x29A4 /* 82P965/G965 */
#define PCI_DEVICE_ID_INTEL_82Q35 0x29B4 /* 82Q35 Express */
#define PCI_DEVICE_ID_INTEL_82G33 0x29C4 /* 82G33/G31/P35/P31 Express */
#define PCI_DEVICE_ID_INTEL_82Q33 0x29D4 /* 82Q33 Express */
#define PCI_DEVICE_ID_INTEL_82X38 0x29E4 /* 82X38/X48 Express */
#define PCI_DEVICE_ID_INTEL_3200 0x29F4 /* 3200/3210 Server */
#define PCI_DEVICE_ID_INTEL_PM965	0x2A04 /* Mobile PM965/GM965 */
#define PCI_DEVICE_ID_INTEL_GME965	0x2A14 /* Mobile GME965/GLE960 */
#define PCI_DEVICE_ID_INTEL_CANTIGA_1	0x2A44 /* Cantiga */
#define PCI_DEVICE_ID_INTEL_CANTIGA_2	0x2a50 /* Cantiga */
#define PCI_DEVICE_ID_INTEL_CANTIGA_3	0x2A54 /* Cantiga */
#define PCI_DEVICE_ID_INTEL_CANTIGA_4 0x2A64 /* Cantiga */
#define PCI_DEVICE_ID_INTEL_CANTIGA_5	0x2A74 /* Cantiga */
#define PCI_DEVICE_ID_INTEL_EAGLELAKE_1 0x2E04 /* Eaglelake */
#define PCI_DEVICE_ID_INTEL_EAGLELAKE_2 0x2E14 /* Eaglelake */
#define PCI_DEVICE_ID_INTEL_EAGLELAKE_3	0x2E24 /* Eaglelake */
#define PCI_DEVICE_ID_INTEL_EAGLELAKE_4 0x2E34 /* Eaglelake */
#define PCI_DEVICE_ID_INTEL_CALPELLA_1 0x3B64 /* Calpella */
#define PCI_DEVICE_ID_INTEL_CALPELLA_2 0x3B65 /* Calpella */
#define PCI_DEVICE_ID_INTEL_LYNXPOINT_1	0x8C3A /* Lynx Point H */
#define PCI_DEVICE_ID_INTEL_LYNXPOINT_2 0x8CBA /* Lynx Point H Refresh */
#define PCI_DEVICE_ID_INTEL_LYNXPOINT_3 0x8D3A /* Lynx Point - Wellsburg */
#define PCI_DEVICE_ID_INTEL_LYNXPOINT_4 0x9C3A /* Lynx Point LP */
#define PCI_DEVICE_ID_INTEL_WILDCAT_1 0x9CBA /* Wildcat Point LP */
#define PCI_DEVICE_ID_INTEL_WILDCAT_2 0x9CBB /* Wildcat Point LP 2 */
#define PCI_DEVICE_ID_INTEL_SUNRISE_LP 0x9d3a /* SUNRISE Point-LP */
#define PCI_DEVICE_ID_INTEL_CANNONPOINT_LP 0x9de0 /* Cannon Point-LP */
#define PCI_DEVICE_ID_INTEL_SUNRISE_H1_ME 0xa13a /* SUNRISE Point-H 1 */
#define PCI_DEVICE_ID_INTEL_SUNRISE_H2_ME 0xa13b /* SUNRISE Point-H 2 */
#define PCI_DEVICE_ID_INTEL_SUNRISE_H3_ME 0xA13E /* SUNRISE Point-H 3 */
#define PCI_DEVICE_ID_INTEL_LEWISBURG_CSME1 0xA1BA /* CSME Lewisburg #1 */
#define PCI_DEVICE_ID_INTEL_LEWISBURG_CSME2 0xA1BB /* CSME Lewisburg #2 */
#define PCI_DEVICE_ID_INTEL_LEWISBURG_CSME3 0xA1BE /* CSME Lewisburg #3 */
#define PCI_DEVICE_ID_INTEL_LEWISBURG_IE1 0xA1F8 /* IE Lewisburg #1 */
#define PCI_DEVICE_ID_INTEL_LEWISBURG_IE2 0xA1F9 /* IE Lewisburg #2 */
#define PCI_DEVICE_ID_INTEL_LEWISBURG_IE3 0xA1FC /* IE Lewisburg #3 */
#define PCI_DEVICE_ID_INTEL_CANNONLAKE 0xA360 /* Cannon Lake */

#define PCI_DEV_HAS_SUPPORTED_ME(x) ( \
	((x) ==  PCI_DEVICE_ID_INTEL_COUGARPOINT_1) || \
	((x) ==  PCI_DEVICE_ID_INTEL_PATSBURG_1) || \
	((x) ==  PCI_DEVICE_ID_INTEL_PANTHERPOINT_1) || \
	((x) ==  PCI_DEVICE_ID_INTEL_PANTHERPOINT_2) || \
	((x) ==  PCI_DEVICE_ID_INTEL_PANTHERPOINT_3) || \
	((x) ==  PCI_DEVICE_ID_INTEL_CAVECREEK) || \
	((x) ==  PCI_DEVICE_ID_INTEL_BEARLAKE_1) || \
	((x) ==  PCI_DEVICE_ID_INTEL_BEARLAKE_2) || \
	((x) ==  PCI_DEVICE_ID_INTEL_BEARLAKE_3) || \
	((x) ==  PCI_DEVICE_ID_INTEL_BEARLAKE_4) || \
	((x) ==  PCI_DEVICE_ID_INTEL_BEARLAKE_5) || \
	((x) ==  PCI_DEVICE_ID_INTEL_82946GZ) || \
	((x) ==  PCI_DEVICE_ID_INTEL_82G35) || \
	((x) ==  PCI_DEVICE_ID_INTEL_82Q963) || \
	((x) ==  PCI_DEVICE_ID_INTEL_82P965) || \
	((x) ==  PCI_DEVICE_ID_INTEL_82Q35) || \
	((x) ==  PCI_DEVICE_ID_INTEL_82G33) || \
	((x) ==  PCI_DEVICE_ID_INTEL_82Q33) || \
	((x) ==  PCI_DEVICE_ID_INTEL_82X38) || \
	((x) ==  PCI_DEVICE_ID_INTEL_3200) || \
	((x) ==  PCI_DEVICE_ID_INTEL_PM965) || \
	((x) ==  PCI_DEVICE_ID_INTEL_GME965) || \
	((x) ==  PCI_DEVICE_ID_INTEL_CANTIGA_1) || \
	((x) ==  PCI_DEVICE_ID_INTEL_CANTIGA_2) || \
	((x) ==  PCI_DEVICE_ID_INTEL_CANTIGA_3) || \
	((x) ==  PCI_DEVICE_ID_INTEL_CANTIGA_4) || \
	((x) ==  PCI_DEVICE_ID_INTEL_CANTIGA_5) || \
	((x) ==  PCI_DEVICE_ID_INTEL_EAGLELAKE_1) || \
	((x) ==  PCI_DEVICE_ID_INTEL_EAGLELAKE_2) || \
	((x) ==  PCI_DEVICE_ID_INTEL_EAGLELAKE_3) || \
	((x) ==  PCI_DEVICE_ID_INTEL_EAGLELAKE_4) || \
	((x) ==  PCI_DEVICE_ID_INTEL_CALPELLA_1) || \
	((x) ==  PCI_DEVICE_ID_INTEL_CALPELLA_2) || \
	((x) ==  PCI_DEVICE_ID_INTEL_LYNXPOINT_1) || \
	((x) ==  PCI_DEVICE_ID_INTEL_LYNXPOINT_2) || \
	((x) ==  PCI_DEVICE_ID_INTEL_LYNXPOINT_3) || \
	((x) ==  PCI_DEVICE_ID_INTEL_LYNXPOINT_4) || \
	((x) ==  PCI_DEVICE_ID_INTEL_WILDCAT_1) || \
	((x) ==  PCI_DEVICE_ID_INTEL_WILDCAT_2) || \
	((x) ==  PCI_DEVICE_ID_INTEL_SUNRISE_LP) || \
	((x) ==  PCI_DEVICE_ID_INTEL_CANNONPOINT_LP) || \
	((x) ==  PCI_DEVICE_ID_INTEL_SUNRISE_H1_ME) || \
	((x) ==  PCI_DEVICE_ID_INTEL_SUNRISE_H2_ME) || \
	((x) ==  PCI_DEVICE_ID_INTEL_SUNRISE_H3_ME) || \
	((x) ==  PCI_DEVICE_ID_INTEL_LEWISBURG_CSME1) || \
	((x) ==  PCI_DEVICE_ID_INTEL_LEWISBURG_CSME2) || \
	((x) ==  PCI_DEVICE_ID_INTEL_LEWISBURG_CSME3) || \
	((x) ==  PCI_DEVICE_ID_INTEL_LEWISBURG_IE1) || \
	((x) ==  PCI_DEVICE_ID_INTEL_LEWISBURG_IE2) || \
	((x) ==  PCI_DEVICE_ID_INTEL_LEWISBURG_IE3) || \
	((x) ==  PCI_DEVICE_ID_INTEL_CANNONLAKE) || \
	0)
