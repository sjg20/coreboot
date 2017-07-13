#include <stdint.h>
#include <string.h>
#include <device/pci_def.h>
#include <arch/io.h>
#include <device/pnp_def.h>
#include <cpu/x86/lapic.h>
#include <pc80/mc146818rtc.h>
#include <console/console.h>
#include <cpu/amd/model_fxx_rev.h>
#include "northbridge/amd/amdk8/incoherent_ht.c"
#include "southbridge/broadcom/bcm5785/early_smbus.c"
#include <northbridge/amd/amdk8/raminit.h>
#include <delay.h>
#include <cpu/x86/lapic.h>

#include <superio/nsc/pc87417/pc87417.h>
#include <cpu/amd/car.h>
#include <cpu/x86/bist.h>
#include "northbridge/amd/amdk8/setup_resource_map.c"
#include <northbridge/amd/amdk8/pre_f.h>

#define SERIAL_DEV PNP_DEV(0x2e, PC87417_SP1)
#define RTC_DEV PNP_DEV(0x2e, PC87417_RTC)

unsigned get_sbdn(unsigned bus);
static void memreset_setup(void) { }
void memreset(int controllers, const struct mem_controller *ctrl) { }

void activate_spd_rom(const struct mem_controller *ctrl)
{
#define SMBUS_HUB 0x71
	unsigned device=(ctrl->channel0[0])>>8;
	smbus_send_byte(SMBUS_HUB, device);
}

int spd_read_byte(unsigned device, unsigned address)
{
	return smbus_read_byte(device, address);
}

#include "southbridge/broadcom/bcm5785/early_setup.c"
#include "northbridge/amd/amdk8/raminit.c"
#include "lib/generic_sdram.c"
#include "resourcemap.c"
#include "cpu/amd/dualcore/dualcore.c"
#include <spd.h>
#include "cpu/amd/model_fxx/init_cpus.c"
#include "northbridge/amd/amdk8/early_ht.c"

#define RC0 (6 << 8)
#define RC1 (7 << 8)

void cache_as_ram_main(unsigned long bist, unsigned long cpu_init_detectedx)
{
	static const uint16_t spd_addr[] = {
		RC0|DIMM0, RC0|DIMM2, 0, 0,
		RC0|DIMM1, RC0|DIMM3, 0, 0,
		RC1|DIMM0, RC1|DIMM2, 0, 0,
		RC1|DIMM1, RC1|DIMM3, 0, 0,
	};

	int needs_reset;
	unsigned bsp_apicid = 0, nodes;
	struct mem_controller ctrl[8];

	if (!cpu_init_detectedx && boot_cpu()) {
		/* Nothing special needs to be done to find bus 0 */
		/* Allow the HT devices to be found */
		enumerate_ht_chain();
		bcm5785_enable_lpc();
		pc87417_enable_dev(RTC_DEV); /* Enable RTC */
	}

	if (bist == 0)
		bsp_apicid = init_cpus(cpu_init_detectedx);

	pc87417_enable_serial(SERIAL_DEV, CONFIG_TTYS0_BASE);
	console_init();

	/* Halt if there was a built in self test failure */
	report_bist_failure(bist);

	printk(BIOS_DEBUG, "bsp_apicid=%02x\n", bsp_apicid);

	setup_blast_resource_map();

#if 0
	dump_pci_device(PCI_DEV(0, 0x18, 0));
	dump_pci_device(PCI_DEV(0, 0x19, 0));
#endif

	needs_reset = setup_coherent_ht_domain();

#if IS_ENABLED(CONFIG_LOGICAL_CPUS)
	// It is said that we should start core1 after all core0 launched
	wait_all_core0_started();
	start_other_cores();
#endif
	wait_all_aps_started(bsp_apicid);

	needs_reset |= ht_setup_chains_x();

	bcm5785_early_setup();

	if (needs_reset) {
		printk(BIOS_INFO, "ht reset -\n");
		soft_reset();
	}

	allow_all_aps_stop(bsp_apicid);

	nodes = get_nodes();
	//It's the time to set ctrl now;
	fill_mem_ctrl(nodes, ctrl, spd_addr);

	enable_smbus();

	memreset_setup();

//	init_timer();

	sdram_initialize(nodes, ctrl);

#if 0
	print_pci_devices();
	dump_pci_devices();
#endif

	post_cache_as_ram();
}
