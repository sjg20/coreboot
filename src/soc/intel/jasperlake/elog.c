/* SPDX-License-Identifier: GPL-2.0-only */

#include <bootstate.h>
#include <console/console.h>
#include <device/pci_ops.h>
#include <elog.h>
#include <intelblocks/pmclib.h>
#include <soc/pci_devs.h>
#include <soc/pm.h>
#include <stdint.h>
#include <types.h>

static void pch_log_gpio_gpe(u32 gpe0_sts, u32 gpe0_en, int start)
{
	int i;

	gpe0_sts &= gpe0_en;

	for (i = 0; i <= 31; i++) {
		if (gpe0_sts & (1 << i))
			elog_add_event_wake(ELOG_WAKE_SOURCE_GPE, i + start);
	}
}

static void pch_log_rp_wake_source(void)
{
	size_t i;
	struct pme_map {
		pci_devfn_t devfn;
		unsigned int wake_source;
	};

	const struct pme_map pme_map[] = {
		{ PCH_DEVFN_PCIE1, ELOG_WAKE_SOURCE_PME_PCIE1 },
		{ PCH_DEVFN_PCIE2, ELOG_WAKE_SOURCE_PME_PCIE2 },
		{ PCH_DEVFN_PCIE3, ELOG_WAKE_SOURCE_PME_PCIE3 },
		{ PCH_DEVFN_PCIE4, ELOG_WAKE_SOURCE_PME_PCIE4 },
		{ PCH_DEVFN_PCIE5, ELOG_WAKE_SOURCE_PME_PCIE5 },
		{ PCH_DEVFN_PCIE6, ELOG_WAKE_SOURCE_PME_PCIE6 },
		{ PCH_DEVFN_PCIE7, ELOG_WAKE_SOURCE_PME_PCIE7 },
		{ PCH_DEVFN_PCIE8, ELOG_WAKE_SOURCE_PME_PCIE8 },
		{ PCH_DEVFN_PCIE9, ELOG_WAKE_SOURCE_PME_PCIE9 },
		{ PCH_DEVFN_PCIE10, ELOG_WAKE_SOURCE_PME_PCIE10 },
		{ PCH_DEVFN_PCIE11, ELOG_WAKE_SOURCE_PME_PCIE11 },
		{ PCH_DEVFN_PCIE12, ELOG_WAKE_SOURCE_PME_PCIE12 },
	};

	for (i = 0; i < MIN(CONFIG_MAX_ROOT_PORTS, ARRAY_SIZE(pme_map)); ++i) {
		const struct device *dev = pcidev_path_on_root(pme_map[i].devfn);
		if (!dev)
			continue;

		if (pci_dev_is_wake_source(dev))
			elog_add_event_wake(pme_map[i].wake_source, 0);
	}
}

static void pch_log_wake_source(struct chipset_power_state *ps)
{
	/* Power Button */
	if (ps->pm1_sts & PWRBTN_STS)
		elog_add_event_wake(ELOG_WAKE_SOURCE_PWRBTN, 0);

	/* RTC */
	if (ps->pm1_sts & RTC_STS)
		elog_add_event_wake(ELOG_WAKE_SOURCE_RTC, 0);

	/* PCI Express */
	if (ps->pm1_sts & PCIEXPWAK_STS)
		pch_log_rp_wake_source();

	/* PME (TODO: determine wake device) */
	if (ps->gpe0_sts[GPE_STD] & PME_STS)
		elog_add_event_wake(ELOG_WAKE_SOURCE_PME, 0);

	/* Internal PME (TODO: determine wake device) */
	if (ps->gpe0_sts[GPE_STD] & PME_B0_STS)
		elog_add_event_wake(ELOG_WAKE_SOURCE_PME_INTERNAL, 0);

	/* SMBUS Wake */
	if (ps->gpe0_sts[GPE_STD] & SMB_WAK_STS)
		elog_add_event_wake(ELOG_WAKE_SOURCE_SMBUS, 0);

	/* Log GPIO events in set 1-3 */
	pch_log_gpio_gpe(ps->gpe0_sts[GPE_31_0], ps->gpe0_en[GPE_31_0], 0);
	pch_log_gpio_gpe(ps->gpe0_sts[GPE_63_32], ps->gpe0_en[GPE_63_32], 32);
	pch_log_gpio_gpe(ps->gpe0_sts[GPE_95_64], ps->gpe0_en[GPE_95_64], 64);
	/* Treat the STD as an extension of GPIO to obtain visibility. */
	pch_log_gpio_gpe(ps->gpe0_sts[GPE_STD], ps->gpe0_en[GPE_STD], 96);
}

static void pch_log_power_and_resets(struct chipset_power_state *ps)
{
	/* Thermal Trip */
	if (ps->gblrst_cause[0] & GBLRST_CAUSE0_THERMTRIP)
		elog_add_event(ELOG_TYPE_THERM_TRIP);

	/* PWR_FLR Power Failure */
	if (ps->gen_pmcon_a & PWR_FLR)
		elog_add_event(ELOG_TYPE_POWER_FAIL);

	/* SUS Well Power Failure */
	if (ps->gen_pmcon_a & SUS_PWR_FLR)
		elog_add_event(ELOG_TYPE_SUS_POWER_FAIL);

	/* TCO Timeout */
	if (ps->prev_sleep_state != ACPI_S3 &&
	    ps->tco2_sts & TCO_STS_SECOND_TO)
		elog_add_event(ELOG_TYPE_TCO_RESET);

	/* Power Button Override */
	if (ps->pm1_sts & PRBTNOR_STS)
		elog_add_event(ELOG_TYPE_POWER_BUTTON_OVERRIDE);

	/* RTC reset */
	if (ps->gen_pmcon_b & RTC_BATTERY_DEAD)
		elog_add_event(ELOG_TYPE_RTC_RESET);

	/* Host Reset Status */
	if (ps->gen_pmcon_a & HOST_RST_STS)
		elog_add_event(ELOG_TYPE_SYSTEM_RESET);

	/* ACPI Wake Event */
	if (ps->prev_sleep_state != ACPI_S0)
		elog_add_event_byte(ELOG_TYPE_ACPI_WAKE, ps->prev_sleep_state);
}

static void pch_log_state(void *unused)
{
	struct chipset_power_state *ps = pmc_get_power_state();

	if (!ps) {
		printk(BIOS_ERR, "chipset_power_state not found!\n");
		return;
	}

	/* Power and Reset */
	pch_log_power_and_resets(ps);

	/* Wake Sources */
	if (ps->prev_sleep_state > ACPI_S0)
		pch_log_wake_source(ps);
}

BOOT_STATE_INIT_ENTRY(BS_DEV_INIT, BS_ON_EXIT, pch_log_state, NULL);

void elog_gsmi_cb_platform_log_wake_source(void)
{
	struct chipset_power_state ps;
	pmc_fill_pm_reg_info(&ps);
	pch_log_wake_source(&ps);
}
