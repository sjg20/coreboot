/* SPDX-License-Identifier: GPL-2.0-only */

/* TODO: Check if this is still correct */

#ifndef AMD_SABRINA_MSR_H
#define AMD_SABRINA_MSR_H

/* MSRC001_00[6B:64] P-state [7:0] bit definitions */
#define PSTATE_DEF_HI_ENABLE_SHIFT	31
#define PSTATE_DEF_HI_ENABLE_MASK	(0x1 << PSTATE_DEF_HI_ENABLE_SHIFT)
#define PSTATE_DEF_LO_CUR_DIV_SHIFT	30
#define PSTATE_DEF_LO_CUR_DIV_MASK	(0x3 << PSTATE_DEF_LO_CUR_DIV_SHIFT)
#define PSTATE_DEF_LO_CUR_VAL_SHIFT	22
#define PSTATE_DEF_LO_CUR_VAL_MASK	(0xFF << PSTATE_DEF_LO_CUR_VAL_SHIFT)
#define PSTATE_DEF_LO_CORE_VID_SHIFT	14
#define PSTATE_DEF_LO_CORE_VID_MASK	(0xFF << PSTATE_DEF_LO_CORE_VID_SHIFT)
#define PSTATE_DEF_LO_FREQ_DIV_SHIFT	8
#define PSTATE_DEF_LO_FREQ_DIV_MASK	(0x3F << PSTATE_DEF_LO_FREQ_DIV_SHIFT)
#define PSTATE_DEF_LO_FREQ_DIV_MIN	0x8
#define PSTATE_DEF_LO_EIGHTH_STEP_MAX	0x1A
#define PSTATE_DEF_LO_FREQ_DIV_MAX	0x3E
#define PSTATE_DEF_LO_FREQ_MUL_SHIFT	0
#define PSTATE_DEF_LO_FREQ_MUL_MASK	(0xFF << PSTATE_DEF_LO_FREQ_MUL_SHIFT)
#define PSTATE_DEF_LO_CORE_FREQ_BASE	25

#define MSR_CPPC_CAPABILITY_1				0xc00102b0
#define SHIFT_CPPC_CAPABILITY_1_HIGHEST_PERF		24
#define SHIFT_CPPC_CAPABILITY_1_NOMINAL_PERF		16
#define SHIFT_CPPC_CAPABILITY_1_LOW_NON_LIN_PERF	8
#define SHIFT_CPPC_CAPABILITY_1_LOWEST_PERF		0

#define MSR_CPPC_ENABLE				0xc00102b1
#define MSR_CPPC_REQUEST			0xc00102b3
#define SHIFT_CPPC_REQUEST_ENERGY_PERF_PREF	24
#define SHIFT_CPPC_REQUEST_DES_PERF		16
#define SHIFT_CPPC_REQUEST_MIN_PERF		8
#define SHIFT_CPPC_REQUEST_MAX_PERF		0

#define MSR_CPPC_STATUS		0xc00102b4

#define MSR_MAX_PERFORMANCE_FREQUENCY_CLOCK_COUNT	0xe7
#define MSR_ACTUAL_PERFORMANCE_FREQUENCY_CLOCK_COUNT	0xe8

#endif /* AMD_SABRINA_MSR_H */
