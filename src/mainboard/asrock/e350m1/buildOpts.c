/* SPDX-License-Identifier: GPL-2.0-only */

/* Select the CPU family */
#define INSTALL_FAMILY_14_SUPPORT		TRUE

/* Select the CPU socket type */
#define INSTALL_FT1_SOCKET_SUPPORT		TRUE

/* Agesa optional capabilities selection */
#define BLDOPT_REMOVE_UDIMMS_SUPPORT		FALSE
#define BLDOPT_REMOVE_RDIMMS_SUPPORT		TRUE
#define BLDOPT_REMOVE_LRDIMMS_SUPPORT		FALSE
#define BLDOPT_REMOVE_ECC_SUPPORT		FALSE
#define BLDOPT_REMOVE_BANK_INTERLEAVE		FALSE
#define BLDOPT_REMOVE_WHEA			TRUE

#define BLDCFG_VRM_NB_LOW_POWER_THRESHOLD	1

#define BLDCFG_AMD_PLATFORM_TYPE		AMD_PLATFORM_MOBILE
#define BLDCFG_CFG_GNB_HD_AUDIO			TRUE
#define BLDCFG_MEMORY_SODIMM_CAPABLE		TRUE
#define BLDCFG_MEMORY_LRDIMM_CAPABLE		FALSE
#define BLDCFG_MEMORY_CHANNEL_INTERLEAVING	FALSE

/* Agesa configuration values selection */
#include <AGESA.h>

/* Include the files that instantiate the configuration definitions */
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

/* FIXME: This is most likely wrong */
#undef AGESA_VERSION_STRING
                  // This is the release version number of the AGESA component
                  // This string MUST be exactly 12 characters long
#define AGESA_VERSION_STRING  {'V', '0', '.', '0', '.', '0', '.', '1', ' ', ' ', ' ', ' '}

/* Instantiate all solution relevant data */
#include <PlatformInstall.h>
