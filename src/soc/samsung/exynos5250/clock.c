/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2010 Samsung Electronics
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <device/mmio.h>
#include <assert.h>
#include <console/console.h>
#include <soc/clk.h>
#include <soc/periph.h>
#include <stdlib.h>
#include <timer.h>

/* input clock of PLL: SMDK5250 has 24MHz input clock */
#define CONF_SYS_CLK_FREQ            24000000

static struct arm_clk_ratios arm_clk_ratios[] = {
	{
		.arm_freq_mhz = 600,

		.apll_mdiv = 0xc8,
		.apll_pdiv = 0x4,
		.apll_sdiv = 0x1,

		.arm2_ratio = 0x0,
		.apll_ratio = 0x1,
		.pclk_dbg_ratio = 0x1,
		.atb_ratio = 0x2,
		.periph_ratio = 0x7,
		.acp_ratio = 0x7,
		.cpud_ratio = 0x1,
		.arm_ratio = 0x0,
	}, {
		.arm_freq_mhz = 800,

		.apll_mdiv = 0x64,
		.apll_pdiv = 0x3,
		.apll_sdiv = 0x0,

		.arm2_ratio = 0x0,
		.apll_ratio = 0x1,
		.pclk_dbg_ratio = 0x1,
		.atb_ratio = 0x3,
		.periph_ratio = 0x7,
		.acp_ratio = 0x7,
		.cpud_ratio = 0x2,
		.arm_ratio = 0x0,
	}, {
		.arm_freq_mhz = 1000,

		.apll_mdiv = 0x7d,
		.apll_pdiv = 0x3,
		.apll_sdiv = 0x0,

		.arm2_ratio = 0x0,
		.apll_ratio = 0x1,
		.pclk_dbg_ratio = 0x1,
		.atb_ratio = 0x4,
		.periph_ratio = 0x7,
		.acp_ratio = 0x7,
		.cpud_ratio = 0x2,
		.arm_ratio = 0x0,
	}, {
		.arm_freq_mhz = 1200,

		.apll_mdiv = 0x96,
		.apll_pdiv = 0x3,
		.apll_sdiv = 0x0,

		.arm2_ratio = 0x0,
		.apll_ratio = 0x3,
		.pclk_dbg_ratio = 0x1,
		.atb_ratio = 0x5,
		.periph_ratio = 0x7,
		.acp_ratio = 0x7,
		.cpud_ratio = 0x3,
		.arm_ratio = 0x0,
	}, {
		.arm_freq_mhz = 1400,

		.apll_mdiv = 0xaf,
		.apll_pdiv = 0x3,
		.apll_sdiv = 0x0,

		.arm2_ratio = 0x0,
		.apll_ratio = 0x3,
		.pclk_dbg_ratio = 0x1,
		.atb_ratio = 0x6,
		.periph_ratio = 0x7,
		.acp_ratio = 0x7,
		.cpud_ratio = 0x3,
		.arm_ratio = 0x0,
	}, {
		.arm_freq_mhz = 1700,

		.apll_mdiv = 0x1a9,
		.apll_pdiv = 0x6,
		.apll_sdiv = 0x0,

		.arm2_ratio = 0x0,
		.apll_ratio = 0x3,
		.pclk_dbg_ratio = 0x1,
		.atb_ratio = 0x6,
		.periph_ratio = 0x7,
		.acp_ratio = 0x7,
		.cpud_ratio = 0x3,
		.arm_ratio = 0x0,
	}
};

/* src_bit div_bit prediv_bit */
static struct clk_bit_info clk_bit_info[PERIPH_ID_COUNT] = {
	{0,	4,	0,	-1},
	{4,	4,	4,	-1},
	{8,	4,	8,	-1},
	{12,	4,	12,	-1},
	{0,	4,	0,	8},
	{4,	4,	16,	24},
	{8,	4,	0,	8},
	{12,	4,	16,	24},
	{-1,	-1,	-1,	-1},
	{16,	4,	0,	8}, /* PERIPH_ID_SROMC */
	{20,	4,	16,	24},
	{24,	4,	0,	8},
	{0,	4,	0,	4},
	{4,	4,	12,	16},
	{-1,	4,	-1,	-1},
	{-1,	4,	-1,	-1},
	{-1,	4,	24,	0},
	{-1,	4,	24,	0},
	{-1,	4,	24,	0},
	{-1,	4,	24,	0},
	{-1,	4,	24,	0},
	{-1,	4,	24,	0},
	{-1,	4,	24,	0},
	{-1,	4,	24,	0},
	{24,	4,	0,	-1},
	{24,	4,	0,	-1},
	{24,	4,	0,	-1},
	{24,	4,	0,	-1},
	{24,	4,	0,	-1},
	{-1,	-1,	-1,	-1},
	{-1,	-1,	-1,	-1},
	{-1,	-1,	-1,	-1}, /* PERIPH_ID_I2S1 */
	{24,	1,	20,	-1}, /* PERIPH_ID_SATA */
};

/* Epll Clock division values to achieve different frequency output */
static struct st_epll_con_val epll_div[] = {
	{ 192000000, 0, 48, 3, 1, 0 },
	{ 180000000, 0, 45, 3, 1, 0 },
	{  73728000, 1, 73, 3, 3, 47710 },
	{  67737600, 1, 90, 4, 3, 20762 },
	{  49152000, 0, 49, 3, 3, 9961 },
	{  45158400, 0, 45, 3, 3, 10381 },
	{ 180633600, 0, 45, 3, 1, 10381 }
};

/* exynos5: return pll clock frequency */
unsigned long get_pll_clk(int pllreg)
{
	unsigned long r, m, p, s, k = 0, mask, fout;
	unsigned int freq;

	switch (pllreg) {
	case APLL:
		r = read32(&exynos_clock->apll_con0);
		break;
	case BPLL:
		r = read32(&exynos_clock->bpll_con0);
		break;
	case MPLL:
		r = read32(&exynos_clock->mpll_con0);
		break;
	case EPLL:
		r = read32(&exynos_clock->epll_con0);
		k = read32(&exynos_clock->epll_con1);
		break;
	case VPLL:
		r = read32(&exynos_clock->vpll_con0);
		k = read32(&exynos_clock->vpll_con1);
		break;
	default:
		printk(BIOS_DEBUG, "Unsupported PLL (%d)\n", pllreg);
		return 0;
	}

	/*
	 * APLL_CON: MIDV [25:16]
	 * MPLL_CON: MIDV [25:16]
	 * EPLL_CON: MIDV [24:16]
	 * VPLL_CON: MIDV [24:16]
	 */
	if (pllreg == APLL || pllreg == BPLL || pllreg == MPLL)
		mask = 0x3ff;
	else
		mask = 0x1ff;

	m = (r >> 16) & mask;

	/* PDIV [13:8] */
	p = (r >> 8) & 0x3f;
	/* SDIV [2:0] */
	s = r & 0x7;

	freq = CONF_SYS_CLK_FREQ;

	if (pllreg == EPLL) {
		k = k & 0xffff;
		/* FOUT = (MDIV + K / 65536) * FIN / (PDIV * 2^SDIV) */
		fout = (m + k / 65536) * (freq / (p * (1 << s)));
	} else if (pllreg == VPLL) {
		k = k & 0xfff;
		/* FOUT = (MDIV + K / 1024) * FIN / (PDIV * 2^SDIV) */
		fout = (m + k / 1024) * (freq / (p * (1 << s)));
	} else {
		/* FOUT = MDIV * FIN / (PDIV * 2^SDIV) */
		fout = m * (freq / (p * (1 << s)));
	}

	return fout;
}

unsigned long clock_get_periph_rate(enum periph_id peripheral)
{
	struct clk_bit_info *bit_info = &clk_bit_info[peripheral];
	unsigned long sclk, sub_clk;
	unsigned int src, div, sub_div;

	switch (peripheral) {
	case PERIPH_ID_UART0:
	case PERIPH_ID_UART1:
	case PERIPH_ID_UART2:
	case PERIPH_ID_UART3:
		src = read32(&exynos_clock->src_peric0);
		div = read32(&exynos_clock->div_peric0);
		break;
	case PERIPH_ID_PWM0:
	case PERIPH_ID_PWM1:
	case PERIPH_ID_PWM2:
	case PERIPH_ID_PWM3:
	case PERIPH_ID_PWM4:
		src = read32(&exynos_clock->src_peric0);
		div = read32(&exynos_clock->div_peric3);
		break;
	case PERIPH_ID_SPI0:
	case PERIPH_ID_SPI1:
		src = read32(&exynos_clock->src_peric1);
		div = read32(&exynos_clock->div_peric1);
		break;
	case PERIPH_ID_SPI2:
		src = read32(&exynos_clock->src_peric1);
		div = read32(&exynos_clock->div_peric2);
		break;
	case PERIPH_ID_SPI3:
	case PERIPH_ID_SPI4:
		src = read32(&exynos_clock->sclk_src_isp);
		div = read32(&exynos_clock->sclk_div_isp);
		break;
	case PERIPH_ID_SATA:
		src = read32(&exynos_clock->src_fsys);
		div = read32(&exynos_clock->div_fsys0);
		break;
	case PERIPH_ID_SDMMC0:
	case PERIPH_ID_SDMMC1:
	case PERIPH_ID_SDMMC2:
	case PERIPH_ID_SDMMC3:
		src = read32(&exynos_clock->src_fsys);
		div = read32(&exynos_clock->div_fsys1);
		break;
	case PERIPH_ID_I2C0:
	case PERIPH_ID_I2C1:
	case PERIPH_ID_I2C2:
	case PERIPH_ID_I2C3:
	case PERIPH_ID_I2C4:
	case PERIPH_ID_I2C5:
	case PERIPH_ID_I2C6:
	case PERIPH_ID_I2C7:
		sclk = get_pll_clk(MPLL);
		sub_div = ((read32(&exynos_clock->div_top1)
			    >> bit_info->div_bit) & 0x7) + 1;
		div = ((read32(&exynos_clock->div_top0)
		        >> bit_info->prediv_bit) & 0x7) + 1;
		return (sclk / sub_div) / div;
	default:
		printk(BIOS_DEBUG, "%s: invalid peripheral %d", __func__, peripheral);
		return -1;
	};

	src = (src >> bit_info->src_bit) & ((1 << bit_info->n_src_bits) - 1);
	if (peripheral == PERIPH_ID_SATA) {
		if (src)
			sclk = get_pll_clk(BPLL);
		else
			sclk = get_pll_clk(MPLL);
	} else {
		if (src == SRC_MPLL)
			sclk = get_pll_clk(MPLL);
		else if (src == SRC_EPLL)
			sclk = get_pll_clk(EPLL);
		else if (src == SRC_VPLL)
			sclk = get_pll_clk(VPLL);
		else
			return 0;
	}

	sub_div = (div >> bit_info->div_bit) & 0xf;
	sub_clk = sclk / (sub_div + 1);

	if (peripheral == PERIPH_ID_SDMMC0 || peripheral == PERIPH_ID_SDMMC2) {
		div = (div >> bit_info->prediv_bit) & 0xff;
		return sub_clk / (div + 1);
	}

	return sub_clk;
}

/* exynos5: return ARM clock frequency */
unsigned long get_arm_clk(void)
{
	unsigned long div;
	unsigned long armclk;
	unsigned int arm_ratio;
	unsigned int arm2_ratio;

	div = read32(&exynos_clock->div_cpu0);

	/* ARM_RATIO: [2:0], ARM2_RATIO: [30:28] */
	arm_ratio = (div >> 0) & 0x7;
	arm2_ratio = (div >> 28) & 0x7;

	armclk = get_pll_clk(APLL) / (arm_ratio + 1);
	armclk /= (arm2_ratio + 1);

	return armclk;
}

struct arm_clk_ratios *get_arm_clk_ratios(void)
{
	struct arm_clk_ratios *arm_ratio;
	unsigned long arm_freq = 1700;	/* FIXME: use get_arm_clk() */
	int i;

	for (i = 0, arm_ratio = arm_clk_ratios; i < ARRAY_SIZE(arm_clk_ratios);
		i++, arm_ratio++) {
		if (arm_ratio->arm_freq_mhz == arm_freq)
			return arm_ratio;
	}

	return NULL;
}

/* exynos5: set the mmc clock */
void set_mmc_clk(int dev_index, unsigned int div)
{
	unsigned int *addr;
	unsigned int val;

	/*
	 * CLK_DIV_FSYS1
	 * MMC0_PRE_RATIO [15:8], MMC1_PRE_RATIO [31:24]
	 * CLK_DIV_FSYS2
	 * MMC2_PRE_RATIO [15:8], MMC3_PRE_RATIO [31:24]
	 */
	if (dev_index < 2) {
		addr = &exynos_clock->div_fsys1;
	} else {
		addr = &exynos_clock->div_fsys2;
		dev_index -= 2;
	}

	val = read32(addr);
	val &= ~(0xff << ((dev_index << 4) + 8));
	val |= (div & 0xff) << ((dev_index << 4) + 8);
	write32(addr, val);
}

void clock_ll_set_pre_ratio(enum periph_id periph_id, unsigned int divisor)
{
	unsigned int shift;
	unsigned int mask = 0xff;
	u32 *reg;

	/*
	 * For now we only handle a very small subset of peripherals here.
	 * Others will need to (and do) mangle the clock registers
	 * themselves, At some point it is hoped that this function can work
	 * from a table or calculated register offset / mask. For now this
	 * is at least better than spreading clock control code around
	 * U-Boot.
	 */
	switch (periph_id) {
	case PERIPH_ID_SPI0:
		reg = &exynos_clock->div_peric1;
		shift = 8;
		break;
	case PERIPH_ID_SPI1:
		reg = &exynos_clock->div_peric1;
		shift = 24;
		break;
	case PERIPH_ID_SPI2:
		reg = &exynos_clock->div_peric2;
		shift = 8;
		break;
	case PERIPH_ID_SPI3:
		reg = &exynos_clock->sclk_div_isp;
		shift = 4;
		break;
	case PERIPH_ID_SPI4:
		reg = &exynos_clock->sclk_div_isp;
		shift = 16;
		break;
	default:
		printk(BIOS_DEBUG, "%s: Unsupported peripheral ID %d\n", __func__,
		      periph_id);
		return;
	}
	clrsetbits_le32(reg, mask << shift, (divisor & mask) << shift);
}

void clock_ll_set_ratio(enum periph_id periph_id, unsigned int divisor)
{
	unsigned int shift;
	unsigned int mask = 0xff;
	u32 *reg;

	switch (periph_id) {
	case PERIPH_ID_SPI0:
		reg = &exynos_clock->div_peric1;
		shift = 0;
		break;
	case PERIPH_ID_SPI1:
		reg = &exynos_clock->div_peric1;
		shift = 16;
		break;
	case PERIPH_ID_SPI2:
		reg = &exynos_clock->div_peric2;
		shift = 0;
		break;
	case PERIPH_ID_SPI3:
		reg = &exynos_clock->sclk_div_isp;
		shift = 0;
		break;
	case PERIPH_ID_SPI4:
		reg = &exynos_clock->sclk_div_isp;
		shift = 12;
		break;
	default:
		printk(BIOS_DEBUG, "%s: Unsupported peripheral ID %d\n", __func__,
		      periph_id);
		return;
	}
	clrsetbits_le32(reg, mask << shift, (divisor & mask) << shift);
}

/**
 * Linearly searches for the most accurate main and fine stage clock scalars
 * (divisors) for a specified target frequency and scalar bit sizes by checking
 * all multiples of main_scalar_bits values. Will always return scalars up to or
 * slower than target.
 *
 * @param main_scalar_bits	Number of main scalar bits, must be > 0 and < 32
 * @param fine_scalar_bits	Number of fine scalar bits, must be > 0 and < 32
 * @param input_rate		Clock frequency to be scaled in Hz
 * @param target_rate		Desired clock frequency in Hz
 * @param best_fine_scalar	Pointer to store the fine stage divisor
 *
 * @return best_main_scalar	Main scalar for desired frequency or -1 if none
 * found
 */
static int clock_calc_best_scalar(unsigned int main_scaler_bits,
	unsigned int fine_scalar_bits, unsigned int input_rate,
	unsigned int target_rate, unsigned int *best_fine_scalar)
{
	int i;
	int best_main_scalar = -1;
	unsigned int best_error = target_rate;
	const unsigned int cap = (1 << fine_scalar_bits) - 1;
	const unsigned int loops = 1 << main_scaler_bits;

	printk(BIOS_DEBUG, "Input Rate is %u, Target is %u, Cap is %u\n", input_rate,
			target_rate, cap);

	ASSERT(best_fine_scalar != NULL);
	ASSERT(main_scaler_bits <= fine_scalar_bits);

	*best_fine_scalar = 1;

	if (input_rate == 0 || target_rate == 0)
		return -1;

	if (target_rate >= input_rate)
		return 1;

	for (i = 1; i <= loops; i++) {
		const unsigned int effective_div = MAX(MIN(input_rate / i /
							target_rate, cap), 1);
		const unsigned int effective_rate = input_rate / i /
							effective_div;
		const int error = target_rate - effective_rate;

		printk(BIOS_DEBUG, "%d|effdiv:%u, effrate:%u, error:%d\n", i, effective_div,
				effective_rate, error);

		if (error >= 0 && error <= best_error) {
			best_error = error;
			best_main_scalar = i;
			*best_fine_scalar = effective_div;
		}
	}

	return best_main_scalar;
}

int clock_set_rate(enum periph_id periph_id, unsigned int rate)
{
	int main_scalar;
	unsigned int fine;

	switch (periph_id) {
	case PERIPH_ID_SPI0:
	case PERIPH_ID_SPI1:
	case PERIPH_ID_SPI2:
	case PERIPH_ID_SPI3:
	case PERIPH_ID_SPI4:
		main_scalar = clock_calc_best_scalar(4, 8, 400000000, rate, &fine);
		if (main_scalar < 0) {
			printk(BIOS_DEBUG, "%s: Cannot set clock rate for periph %d",
					__func__, periph_id);
			return -1;
		}
		clock_ll_set_ratio(periph_id, main_scalar - 1);
		clock_ll_set_pre_ratio(periph_id, fine - 1);
		break;
	default:
		printk(BIOS_DEBUG, "%s: Unsupported peripheral ID %d\n", __func__,
		      periph_id);
		return -1;
	}

	return 0;
}

int clock_set_mshci(enum periph_id peripheral)
{
	u32 *addr;
	unsigned int clock;
	unsigned int tmp;
	unsigned int i;

	/* get mpll clock */
	clock = get_pll_clk(MPLL) / 1000000;

	/*
	 * CLK_DIV_FSYS1
	 * MMC0_PRE_RATIO [15:8], MMC0_RATIO [3:0]
	 * CLK_DIV_FSYS2
	 * MMC2_PRE_RATIO [15:8], MMC2_RATIO [3:0]
	 */
	switch (peripheral) {
	case PERIPH_ID_SDMMC0:
		addr = &exynos_clock->div_fsys1;
		break;
	case PERIPH_ID_SDMMC2:
		addr = &exynos_clock->div_fsys2;
		break;
	default:
		printk(BIOS_DEBUG, "invalid peripheral\n");
		return -1;
	}
	tmp = read32(addr) & ~0xff0f;
	for (i = 0; i <= 0xf; i++) {
		if ((clock / (i + 1)) <= 400) {
			write32(addr, tmp | i << 0);
			break;
		}
	}
	return 0;
}

int clock_epll_set_rate(unsigned long rate)
{
	unsigned int epll_con, epll_con_k;
	unsigned int i;
	unsigned int lockcnt;
	struct stopwatch sw;

	epll_con = read32(&exynos_clock->epll_con0);
	epll_con &= ~((EPLL_CON0_LOCK_DET_EN_MASK <<
			EPLL_CON0_LOCK_DET_EN_SHIFT) |
		EPLL_CON0_MDIV_MASK << EPLL_CON0_MDIV_SHIFT |
		EPLL_CON0_PDIV_MASK << EPLL_CON0_PDIV_SHIFT |
		EPLL_CON0_SDIV_MASK << EPLL_CON0_SDIV_SHIFT);

	for (i = 0; i < ARRAY_SIZE(epll_div); i++) {
		if (epll_div[i].freq_out == rate)
			break;
	}

	if (i == ARRAY_SIZE(epll_div))
		return -1;

	epll_con_k = epll_div[i].k_dsm << 0;
	epll_con |= epll_div[i].en_lock_det << EPLL_CON0_LOCK_DET_EN_SHIFT;
	epll_con |= epll_div[i].m_div << EPLL_CON0_MDIV_SHIFT;
	epll_con |= epll_div[i].p_div << EPLL_CON0_PDIV_SHIFT;
	epll_con |= epll_div[i].s_div << EPLL_CON0_SDIV_SHIFT;

	/*
	 * Required period (in cycles) to generate a stable clock output.
	 * The maximum clock time can be up to 3000 * PDIV cycles of PLLs
	 * frequency input (as per spec)
	 */
	lockcnt = 3000 * epll_div[i].p_div;

	write32(&exynos_clock->epll_lock, lockcnt);
	write32(&exynos_clock->epll_con0, epll_con);
	write32(&exynos_clock->epll_con1, epll_con_k);

	stopwatch_init_msecs_expire(&sw, TIMEOUT_EPLL_LOCK);

	while (!(read32(&exynos_clock->epll_con0) &
			(0x1 << EXYNOS5_EPLLCON0_LOCKED_SHIFT))) {
		if (stopwatch_expired(&sw)) {
			printk(BIOS_DEBUG,
				"%s: Timeout waiting for EPLL lock\n",
				__func__);
			return -1;
		}
	}

	return 0;
}

void clock_select_i2s_clk_source(void)
{
	clrsetbits_le32(&exynos_clock->src_peric1, AUDIO1_SEL_MASK,
			(CLK_SRC_SCLK_EPLL));
}

int clock_set_i2s_clk_prescaler(unsigned int src_frq, unsigned int dst_frq)
{
	unsigned int div ;

	if ((dst_frq == 0) || (src_frq == 0)) {
		printk(BIOS_DEBUG, "%s: Invalid frequency input for prescaler\n", __func__);
		printk(BIOS_DEBUG, "src frq = %d des frq = %d ", src_frq, dst_frq);
		return -1;
	}

	div = (src_frq / dst_frq);
	if (div > AUDIO_1_RATIO_MASK) {
		printk(BIOS_DEBUG, "%s: Frequency ratio is out of range\n", __func__);
		printk(BIOS_DEBUG, "src frq = %d des frq = %d ", src_frq, dst_frq);
		return -1;
	}
	clrsetbits_le32(&exynos_clock->div_peric4, AUDIO_1_RATIO_MASK,
				(div & AUDIO_1_RATIO_MASK));
	return 0;
}
