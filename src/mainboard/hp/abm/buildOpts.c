/* SPDX-License-Identifier: GPL-2.0-only */

/**
 * @file
 *
 * AMD User options selection for a Brazos platform solution system
 *
 * This file is placed in the user's platform directory and contains the
 * build option selections desired for that platform.
 *
 * For Information about this file, see @ref platforminstall.
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  Core
 * @e \$Revision: 23714 $   @e \$Date: 2009-12-09 17:28:37 -0600 (Wed, 09 Dec 2009) $
 */

#include <AGESA.h>

#define INSTALL_FT3_SOCKET_SUPPORT           TRUE
#define INSTALL_FAMILY_16_MODEL_0x_SUPPORT   TRUE

#define INSTALL_G34_SOCKET_SUPPORT  FALSE
#define INSTALL_C32_SOCKET_SUPPORT  FALSE
#define INSTALL_S1G3_SOCKET_SUPPORT FALSE
#define INSTALL_S1G4_SOCKET_SUPPORT FALSE
#define INSTALL_ASB2_SOCKET_SUPPORT FALSE
#define INSTALL_FS1_SOCKET_SUPPORT  FALSE
#define INSTALL_FM1_SOCKET_SUPPORT  FALSE
#define INSTALL_FP2_SOCKET_SUPPORT  FALSE
#define INSTALL_FT1_SOCKET_SUPPORT  FALSE
#define INSTALL_AM3_SOCKET_SUPPORT  FALSE
#define INSTALL_FM2_SOCKET_SUPPORT  FALSE

#ifdef BLDOPT_REMOVE_FT3_SOCKET_SUPPORT
  #if BLDOPT_REMOVE_FT3_SOCKET_SUPPORT == TRUE
    #undef INSTALL_FT3_SOCKET_SUPPORT
    #define INSTALL_FT3_SOCKET_SUPPORT     FALSE
  #endif
#endif

//#define BLDOPT_REMOVE_UDIMMS_SUPPORT           TRUE
//#define BLDOPT_REMOVE_RDIMMS_SUPPORT           TRUE
#define BLDOPT_REMOVE_LRDIMMS_SUPPORT          TRUE
//#define BLDOPT_REMOVE_ECC_SUPPORT              TRUE
//#define BLDOPT_REMOVE_BANK_INTERLEAVE          TRUE
//#define BLDOPT_REMOVE_DCT_INTERLEAVE           TRUE
#define BLDOPT_REMOVE_NODE_INTERLEAVE          TRUE
#define BLDOPT_REMOVE_PARALLEL_TRAINING        TRUE
#define BLDOPT_REMOVE_ONLINE_SPARE_SUPPORT     TRUE
//#define BLDOPT_REMOVE_MEM_RESTORE_SUPPORT      TRUE
#define BLDOPT_REMOVE_MULTISOCKET_SUPPORT        TRUE
//#define BLDOPT_REMOVE_ACPI_PSTATES             FALSE
#define BLDOPT_REMOVE_SRAT                     FALSE //TRUE
#define BLDOPT_REMOVE_SLIT                     FALSE //TRUE
#define BLDOPT_REMOVE_WHEA                     FALSE //TRUE
#define BLDOPT_REMOVE_CRAT                     TRUE
#define BLDOPT_REMOVE_CDIT                     TRUE
#define BLDOPT_REMOVE_DMI                      TRUE
//#define BLDOPT_REMOVE_EARLY_SAMPLES            FALSE
//#define BLDCFG_REMOVE_ACPI_PSTATES_PPC               TRUE
//#define BLDCFG_REMOVE_ACPI_PSTATES_PCT               TRUE
//#define BLDCFG_REMOVE_ACPI_PSTATES_PSD               TRUE
//#define BLDCFG_REMOVE_ACPI_PSTATES_PSS               TRUE
//#define BLDCFG_REMOVE_ACPI_PSTATES_XPSS              TRUE

//This element selects whether P-States should be forced to be independent,
// as reported by the ACPI _PSD object. For single-link processors,
// setting TRUE for OS to support this feature.

//#define BLDCFG_FORCE_INDEPENDENT_PSD_OBJECT  TRUE

/* Build configuration values here.
 */
#define BLDCFG_VRM_CURRENT_LIMIT                  15000
#define BLDCFG_VRM_NB_CURRENT_LIMIT               13000
#define BLDCFG_VRM_MAXIMUM_CURRENT_LIMIT          21000
#define BLDCFG_VRM_SVI_OCP_LEVEL                  BLDCFG_VRM_MAXIMUM_CURRENT_LIMIT
#define BLDCFG_VRM_NB_MAXIMUM_CURRENT_LIMIT       17000
#define BLDCFG_VRM_NB_SVI_OCP_LEVEL               BLDCFG_VRM_NB_MAXIMUM_CURRENT_LIMIT
#define BLDCFG_VRM_LOW_POWER_THRESHOLD            0
#define BLDCFG_VRM_NB_LOW_POWER_THRESHOLD         0
#define BLDCFG_VRM_SLEW_RATE                      10000
#define BLDCFG_VRM_NB_SLEW_RATE                   BLDCFG_VRM_SLEW_RATE
#define BLDCFG_VRM_HIGH_SPEED_ENABLE              TRUE

#define BLDCFG_PLAT_NUM_IO_APICS                 3
#define BLDCFG_GNB_IOAPIC_ADDRESS		0xFEC20000
#define BLDCFG_CORE_LEVELING_MODE                CORE_LEVEL_LOWEST
#define BLDCFG_MEM_INIT_PSTATE                   0
#define BLDCFG_PLATFORM_CSTATE_IO_BASE_ADDRESS    0x1770 // Specifies the IO addresses trapped by the
                                                         // core for C-state entry requests. A value
                                                         // of 0 in this field specifies that the core
                                                         // does not trap any IO addresses for C-state entry.
                                                         // Values greater than 0xFFF8 results in undefined behavior.
#define BLDCFG_PLATFORM_CSTATE_OPDATA             0x1770

#define BLDCFG_AMD_PLATFORM_TYPE                  AMD_PLATFORM_MOBILE

#define BLDCFG_MEMORY_BUS_FREQUENCY_LIMIT         DDR1866_FREQUENCY
#define BLDCFG_MEMORY_MODE_UNGANGED               TRUE
#define BLDCFG_MEMORY_QUAD_RANK_CAPABLE           TRUE
#define BLDCFG_MEMORY_QUADRANK_TYPE               QUADRANK_UNBUFFERED
#define BLDCFG_MEMORY_RDIMM_CAPABLE               FALSE
#define BLDCFG_MEMORY_UDIMM_CAPABLE               TRUE
#define BLDCFG_MEMORY_SODIMM_CAPABLE              TRUE
#define BLDCFG_MEMORY_ENABLE_BANK_INTERLEAVING    TRUE
#define BLDCFG_MEMORY_ENABLE_NODE_INTERLEAVING    FALSE
#define BLDCFG_MEMORY_CHANNEL_INTERLEAVING        TRUE
#define BLDCFG_MEMORY_POWER_DOWN                  TRUE
#define BLDCFG_POWER_DOWN_MODE                    POWER_DOWN_BY_CHIP_SELECT
#define BLDCFG_ONLINE_SPARE                       FALSE
#define BLDCFG_BANK_SWIZZLE                       TRUE
#define BLDCFG_TIMING_MODE_SELECT                 TIMING_MODE_AUTO
#define BLDCFG_MEMORY_CLOCK_SELECT                DDR1866_FREQUENCY
#define BLDCFG_DQS_TRAINING_CONTROL               TRUE
#define BLDCFG_IGNORE_SPD_CHECKSUM                FALSE
#define BLDCFG_USE_BURST_MODE                     FALSE
#define BLDCFG_MEMORY_ALL_CLOCKS_ON               FALSE
#define BLDCFG_ENABLE_ECC_FEATURE                 TRUE
#define BLDCFG_ECC_REDIRECTION                    FALSE
#define BLDCFG_SCRUB_DRAM_RATE                    0
#define BLDCFG_SCRUB_L2_RATE                      0
#define BLDCFG_SCRUB_L3_RATE                      0
#define BLDCFG_SCRUB_IC_RATE                      0
#define BLDCFG_SCRUB_DC_RATE                      0
#define BLDCFG_ECC_SYNC_FLOOD                     TRUE
#define BLDCFG_ECC_SYMBOL_SIZE                    4
#define BLDCFG_HEAP_DRAM_ADDRESS                  0xB0000ul
#define BLDCFG_1GB_ALIGN                          FALSE
#define BLDCFG_UMA_ALIGNMENT                      UMA_4MB_ALIGNED
#define BLDCFG_UMA_ALLOCATION_MODE                UMA_NONE
#define BLDCFG_PLATFORM_CSTATE_MODE               CStateModeDisabled
#define BLDCFG_IOMMU_SUPPORT                      FALSE
#define OPTION_GFX_INIT_SVIEW                     FALSE
//#define BLDCFG_PLATFORM_POWER_POLICY_MODE         BatteryLife

//#define BLDCFG_CFG_LCD_BACK_LIGHT_CONTROL         OEM_LCD_BACK_LIGHT_CONTROL
#define BLDCFG_CFG_ABM_SUPPORT                    TRUE

#define BLDCFG_CFG_GNB_HD_AUDIO                   TRUE
//#define BLDCFG_IGPU_SUBSYSTEM_ID            OEM_IGPU_SSID
//#define BLDCFG_IGPU_HD_AUDIO_SUBSYSTEM_ID   OEM_IGPU_HD_AUDIO_SSID
//#define BLFCFG_APU_PCIE_PORTS_SUBSYSTEM_ID  OEM_APU_PCIE_PORTS_SSID

#ifdef PCIEX_BASE_ADDRESS
#define BLDCFG_PCI_MMIO_BASE PCIEX_BASE_ADDRESS
#define BLDCFG_PCI_MMIO_SIZE (PCIEX_LENGTH >> 20)
#endif

#define BLDCFG_PROCESSOR_SCOPE_NAME0              'P'
#define BLDCFG_PROCESSOR_SCOPE_NAME1              '0'
#define BLDCFG_PCIE_TRAINING_ALGORITHM           PcieTrainingDistributed

/* Process the options...
 * This file include MUST occur AFTER the user option selection settings
 */
/*
 * Customized OEM build configurations for FCH component
 */
// #define BLDCFG_SMBUS0_BASE_ADDRESS            0xB00
// #define BLDCFG_SMBUS1_BASE_ADDRESS            0xB20
// #define BLDCFG_SIO_PME_BASE_ADDRESS           0xE00
// #define BLDCFG_ACPI_PM1_EVT_BLOCK_ADDRESS     0x400
// #define BLDCFG_ACPI_PM1_CNT_BLOCK_ADDRESS     0x404
// #define BLDCFG_ACPI_PM_TMR_BLOCK_ADDRESS      0x408
// #define BLDCFG_ACPI_CPU_CNT_BLOCK_ADDRESS     0x410
// #define BLDCFG_ACPI_GPE0_BLOCK_ADDRESS        0x420
// #define BLDCFG_SPI_BASE_ADDRESS               0xFEC10000
// #define BLDCFG_WATCHDOG_TIMER_BASE            0xFEC00000
// #define BLDCFG_HPET_BASE_ADDRESS              0xFED00000
// #define BLDCFG_SMI_CMD_PORT_ADDRESS           0xB0
// #define BLDCFG_ACPI_PMA_BLK_ADDRESS           0xFE00
// #define BLDCFG_ROM_BASE_ADDRESS               0xFED61000
// #define BLDCFG_AZALIA_SSID                    0x780D1022
// #define BLDCFG_SMBUS_SSID                     0x780B1022
// #define BLDCFG_IDE_SSID                       0x780C1022
// #define BLDCFG_SATA_AHCI_SSID                 0x78011022
// #define BLDCFG_SATA_IDE_SSID                  0x78001022
// #define BLDCFG_SATA_RAID5_SSID                0x78031022
// #define BLDCFG_SATA_RAID_SSID                 0x78021022
// #define BLDCFG_EHCI_SSID                      0x78081022
// #define BLDCFG_OHCI_SSID                      0x78071022
// #define BLDCFG_LPC_SSID                       0x780E1022
// #define BLDCFG_SD_SSID                        0x78061022
// #define BLDCFG_XHCI_SSID                      0x78121022
// #define BLDCFG_FCH_PORT80_BEHIND_PCIB         FALSE
// #define BLDCFG_FCH_ENABLE_ACPI_SLEEP_TRAP     TRUE
// #define BLDCFG_FCH_GPP_LINK_CONFIG            PortA4
// #define BLDCFG_FCH_GPP_PORT0_PRESENT          FALSE
// #define BLDCFG_FCH_GPP_PORT1_PRESENT          FALSE
// #define BLDCFG_FCH_GPP_PORT2_PRESENT          FALSE
// #define BLDCFG_FCH_GPP_PORT3_PRESENT          FALSE
// #define BLDCFG_FCH_GPP_PORT0_HOTPLUG          FALSE
// #define BLDCFG_FCH_GPP_PORT1_HOTPLUG          FALSE
// #define BLDCFG_FCH_GPP_PORT2_HOTPLUG          FALSE
// #define BLDCFG_FCH_GPP_PORT3_HOTPLUG          FALSE

/* Include the files that instantiate the configuration definitions. */
#include "cpuRegisters.h"
#include "cpuFamRegisters.h"
#include "cpuFamilyTranslation.h"
#include "AdvancedApi.h"
#include "heapManager.h"
#include "CreateStruct.h"
#include "cpuFeatures.h"
#include "Table.h"
#include "cpuEarlyInit.h"
#include "cpuLateInit.h"
#include "GnbInterface.h"

/*
 * Agesa optional capabilities selection.
 * Uncomment and mark FALSE those features you wish to include in the build.
 * Comment out or mark TRUE those features you want to REMOVE from the build.
 */

#define DFLT_SMBUS0_BASE_ADDRESS            0xB00
#define DFLT_SMBUS1_BASE_ADDRESS            0xB20
#define DFLT_SIO_PME_BASE_ADDRESS           0xE00
#define DFLT_ACPI_PM1_EVT_BLOCK_ADDRESS     0x800
#define DFLT_ACPI_PM1_CNT_BLOCK_ADDRESS     0x804
#define DFLT_ACPI_PM_TMR_BLOCK_ADDRESS      0x808
#define DFLT_ACPI_CPU_CNT_BLOCK_ADDRESS     0x810
#define DFLT_ACPI_GPE0_BLOCK_ADDRESS        0x820
#define DFLT_SPI_BASE_ADDRESS               0xFEC10000
#define DFLT_WATCHDOG_TIMER_BASE_ADDRESS    0xFEC000F0
#define DFLT_HPET_BASE_ADDRESS              0xFED00000
#define DFLT_SMI_CMD_PORT                   0xB0
#define DFLT_ACPI_PMA_CNT_BLK_ADDRESS       0xFE00
#define DFLT_GEC_BASE_ADDRESS               0xFED61000
#define DFLT_AZALIA_SSID                    0x780D1022
#define DFLT_SMBUS_SSID                     0x780B1022
#define DFLT_IDE_SSID                       0x780C1022
#define DFLT_SATA_AHCI_SSID                 0x78011022
#define DFLT_SATA_IDE_SSID                  0x78001022
#define DFLT_SATA_RAID5_SSID                0x78031022
#define DFLT_SATA_RAID_SSID                 0x78021022
#define DFLT_EHCI_SSID                      0x78081022
#define DFLT_OHCI_SSID                      0x78071022
#define DFLT_LPC_SSID                       0x780E1022
#define DFLT_SD_SSID                        0x78061022
#define DFLT_XHCI_SSID                      0x78121022
#define DFLT_FCH_PORT80_BEHIND_PCIB         FALSE
#define DFLT_FCH_ENABLE_ACPI_SLEEP_TRAP     TRUE
#define DFLT_FCH_GPP_LINK_CONFIG            PortA4
#define DFLT_FCH_GPP_PORT0_PRESENT          FALSE
#define DFLT_FCH_GPP_PORT1_PRESENT          FALSE
#define DFLT_FCH_GPP_PORT2_PRESENT          FALSE
#define DFLT_FCH_GPP_PORT3_PRESENT          FALSE
#define DFLT_FCH_GPP_PORT0_HOTPLUG          FALSE
#define DFLT_FCH_GPP_PORT1_HOTPLUG          FALSE
#define DFLT_FCH_GPP_PORT2_HOTPLUG          FALSE
#define DFLT_FCH_GPP_PORT3_HOTPLUG          FALSE

GPIO_CONTROL   hp_abm_gpio[] = {
	{ 45, Function2, GpioOutEnB | Sticky },                   // Signal input  APU_SD_LED
	{ 49, Function2, PullUpB | PullDown | Sticky },           // Signal output APU_ABM_LED_UID
	{ 50, Function2, PullUpB | PullDown | Sticky },           // Signal output APU_ABM_LED_HEALTH
	{ 51, Function2, GpioOut | PullUpB | PullDown | Sticky }, // Signal output APU_ABM_LED_FAULT
	{ 57, Function2, GpioOutEnB | Sticky },                   // Signal input  SATA_PRSNT_L
	{ 58, Function2, GpioOutEnB | Sticky },                   // Signal  i/o   APU_HDMI_CEC
	{ 64, Function2, GpioOutEnB | Sticky },                   // Signal input  SWC_APU_INT_L
	{ 68, Function0, GpioOutEnB | Sticky },                   // Signal input  CNTRL1_PRSNT
	{ 69, Function0, GpioOutEnB | Sticky },                   // Signal input  CNTRL2_PRSNT
	{ 71, Function0, GpioOut | PullUpB | PullDown | Sticky }, // Signal output APU_PROCHOT_L_R
	{-1}
};
#define BLDCFG_FCH_GPIO_CONTROL_LIST           (&hp_abm_gpio[0])

#include <PlatformInstall.h>
