/* $NoKeywords:$ */
/**
 * @file
 *
 * PCIe topology initialization service procedures.
 *
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:     AGESA
 * @e sub-project: GNB
 * @e \$Revision: 66529 $   @e \$Date: 2012-03-09 08:32:22 -0600 (Fri, 09 Mar 2012) $
 *
 */
/*
*****************************************************************************
*
 * Copyright (c) 2008 - 2012, Advanced Micro Devices, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of Advanced Micro Devices, Inc. nor the names of
 *       its contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL ADVANCED MICRO DEVICES, INC. BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
* ***************************************************************************
*
*/

/*----------------------------------------------------------------------------------------
 *                             M O D U L E S    U S E D
 *----------------------------------------------------------------------------------------
 */
#include  "AGESA.h"
#include  "Ids.h"
#include  "amdlib.h"
#include  "Gnb.h"
#include  "GnbPcie.h"
#include  "GnbPcieFamServices.h"
#include  "GnbCommonLib.h"
#include  "GnbPcieConfig.h"
#include  "GnbPcieInitLibV1.h"
#include  "GnbRegistersLN.h"
#include  "Filecode.h"
#define FILECODE PROC_GNB_MODULES_GNBPCIEINITLIBV1_PCIETOPOLOGYSERVICES_FILECODE
/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U  R E S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U  N C T I O N S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------*/
/**
 * Cleanup reconfig
 *
 *
 *
 * @param[in]  Wrapper             Pointer to wrapper config descriptor
 * @param[in]  Pcie                Pointer to global PCIe configuration
 */
VOID
PcieTopologyCleanUpReconfig (
  IN      PCIe_WRAPPER_CONFIG   *Wrapper,
  IN      PCIe_PLATFORM_CONFIG  *Pcie
  )
{
  if (PcieLibIsPcieWrapper (Wrapper)) {
    PcieRegisterRMW (
      Wrapper,
      WRAP_SPACE (Wrapper->WrapId, D0F0xE4_WRAP_8062_ADDRESS),
      D0F0xE4_WRAP_8062_ConfigXferMode_MASK,
      1 << D0F0xE4_WRAP_8062_ConfigXferMode_OFFSET,
      FALSE,
      Pcie
      );
  }
}


/*----------------------------------------------------------------------------------------*/
/**
 * Prepare for reconfiguration
 *
 *
 *
 * @param[in]  Wrapper             Pointer to wrapper config descriptor
 * @param[in]  Pcie                Pointer to global PCIe configuration
 */
VOID
PcieTopologyPrepareForReconfig (
  IN      PCIe_WRAPPER_CONFIG   *Wrapper,
  IN      PCIe_PLATFORM_CONFIG  *Pcie
  )
{
  D0F0xE4_WRAP_8062_STRUCT  D0F0xE4_WRAP_8062;
  UINT8                     CoreId;
  if (PcieLibIsPcieWrapper (Wrapper)) {
    for (CoreId = Wrapper->StartPcieCoreId; CoreId <= Wrapper->EndPcieCoreId; CoreId++) {
      PcieRegisterWriteField (
        Wrapper,
        CORE_SPACE (CoreId, 0x11 ),
        0 ,
        4 ,
        0xf,
        FALSE,
        Pcie
        );
    }

    D0F0xE4_WRAP_8062.Value = PcieRegisterRead (
                                 Wrapper,
                                 WRAP_SPACE (Wrapper->WrapId, D0F0xE4_WRAP_8062_ADDRESS),
                                 Pcie
                                 );

    D0F0xE4_WRAP_8062.Field.ConfigXferMode = 0x0;
    D0F0xE4_WRAP_8062.Field.BlockOnIdle = 0x0;
    PcieRegisterWrite (
      Wrapper,
      WRAP_SPACE (Wrapper->WrapId, D0F0xE4_WRAP_8062_ADDRESS),
      D0F0xE4_WRAP_8062.Value,
      FALSE,
      Pcie
      );
  }
}


CONST UINT8 LaneMuxSelectorTable[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };

/*----------------------------------------------------------------------------------------*/
/**
 * Locate mux array index
 *
 *
 *
 * @param[in, out]  LaneMuxSelectorArrayPtr     Pointer to mux selector array
 * @param[in]       LaneMuxValue                The value that match to array
 * @retval          Index                       Index successfully mapped
 */
STATIC UINT8
PcieTopologyLocateMuxIndex (
  IN OUT   UINT8 *LaneMuxSelectorArrayPtr,
  IN       UINT8  LaneMuxValue
  )
{
  UINT8  Index;
  for (Index = 0; Index < sizeof (LaneMuxSelectorTable); Index++ ) {
    if (LaneMuxSelectorArrayPtr [Index] ==  LaneMuxValue) {
      return Index;
    }
  }
  return 0;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Apply lane mux
 *
 *
 *
 * @param[in]  Wrapper             Pointer to wrapper config descriptor
 * @param[in]  Pcie                Pointer to global PCIe configuration
 */

VOID
PcieTopologyApplyLaneMux (
  IN      PCIe_WRAPPER_CONFIG   *Wrapper,
  IN      PCIe_PLATFORM_CONFIG  *Pcie
  )
{
  PCIe_ENGINE_CONFIG  *EngineList;
  UINT8               CurrentPhyLane;
  UINT8               CurrentCoreLane;
  UINT8               CoreLaneIndex;
  UINT8               PhyLaneIndex;
  UINT8               NumberOfPhyLane;
  UINT8               TxLaneMuxSelectorArray [sizeof (LaneMuxSelectorTable)];
  UINT8               RxLaneMuxSelectorArray [sizeof (LaneMuxSelectorTable)];
  UINT8               Index;
  UINT32              TxMaxSelectorValue;
  UINT32              RxMaxSelectorValue;

  IDS_HDT_CONSOLE (GNB_TRACE, "PcieTopologyApplyLaneMux Enter\n");
  if (PcieLibIsPcieWrapper (Wrapper)) {
    EngineList = PcieConfigGetChildEngine (Wrapper);
    LibAmdMemCopy (
      &TxLaneMuxSelectorArray[0],
      &LaneMuxSelectorTable[0],
      sizeof (LaneMuxSelectorTable),
      GnbLibGetHeader (Pcie)
      );
    LibAmdMemCopy (
      &RxLaneMuxSelectorArray[0],
      &LaneMuxSelectorTable[0],
      sizeof (LaneMuxSelectorTable),
      GnbLibGetHeader (Pcie)
      );
    while (EngineList != NULL) {
      if (PcieLibIsPcieEngine (EngineList) && PcieLibIsEngineAllocated (EngineList)) {
        CurrentPhyLane = (UINT8) PcieLibGetLoPhyLane (EngineList) - Wrapper->StartPhyLane;
        NumberOfPhyLane = (UINT8) PcieConfigGetNumberOfPhyLane (EngineList);
        CurrentCoreLane = (UINT8) EngineList->Type.Port.StartCoreLane;
        if (PcieUtilIsLinkReversed (FALSE, EngineList, Pcie)) {
          CurrentCoreLane = CurrentCoreLane + PcieConfigGetNumberOfCoreLane (EngineList) - NumberOfPhyLane;
        }
        for (Index = 0; Index < NumberOfPhyLane; Index = Index + 2 ) {
          CoreLaneIndex = (CurrentCoreLane + Index) / 2;
          PhyLaneIndex = (CurrentPhyLane + Index) / 2;

          if (RxLaneMuxSelectorArray [CoreLaneIndex] != PhyLaneIndex) {
            RxLaneMuxSelectorArray [PcieTopologyLocateMuxIndex (RxLaneMuxSelectorArray, PhyLaneIndex)] = RxLaneMuxSelectorArray [CoreLaneIndex];
            RxLaneMuxSelectorArray [CoreLaneIndex] = PhyLaneIndex;
          }
          if (TxLaneMuxSelectorArray [PhyLaneIndex] != CoreLaneIndex) {
            TxLaneMuxSelectorArray [PcieTopologyLocateMuxIndex (TxLaneMuxSelectorArray, CoreLaneIndex)] =  TxLaneMuxSelectorArray [PhyLaneIndex];
            TxLaneMuxSelectorArray [PhyLaneIndex] = CoreLaneIndex;
          }
        }
      }
      EngineList = PcieLibGetNextDescriptor (EngineList);
    }
    RxMaxSelectorValue = 0;
    TxMaxSelectorValue = 0;
    for (Index = 0; Index < sizeof (LaneMuxSelectorTable); Index++) {
      RxMaxSelectorValue |= (RxLaneMuxSelectorArray[Index] << (Index * 4));
      TxMaxSelectorValue |= (TxLaneMuxSelectorArray[Index] << (Index * 4));
    }
    PcieRegisterWrite (
      Wrapper,
      WRAP_SPACE (Wrapper->WrapId, D0F0xE4_WRAP_8021_ADDRESS),
      TxMaxSelectorValue,
      FALSE,
      Pcie
      );
    PcieRegisterWrite (
      Wrapper,
      WRAP_SPACE (Wrapper->WrapId, D0F0xE4_WRAP_8022_ADDRESS),
      RxMaxSelectorValue,
      FALSE,
      Pcie
      );
  }
  IDS_HDT_CONSOLE (GNB_TRACE, "PcieTopologyApplyLaneMux Exit\n");
}


/*----------------------------------------------------------------------------------------*/
/**
 * Select master PLL
 *
 *
 *
 * @param[in]  Wrapper             Pointer to wrapper config descriptor
 * @param[out] ConfigChanged       Pointer to boolean indicator that configuration was changed
 * @param[in]  Pcie                Pointer to global PCIe configuration
 */

VOID
PcieTopologySelectMasterPll (
  IN       PCIe_WRAPPER_CONFIG   *Wrapper,
     OUT   BOOLEAN               *ConfigChanged,
  IN       PCIe_PLATFORM_CONFIG  *Pcie
  )
{
  PCIe_ENGINE_CONFIG        *EngineList;
  UINT16                    MasterLane;
  UINT16                    MasterHotplugLane;
  D0F0xE4_WRAP_8013_STRUCT  D0F0xE4_WRAP_8013;
  D0F0xE4_WRAP_8013_STRUCT  D0F0xE4_WRAP_8013_BASE;
  IDS_HDT_CONSOLE (GNB_TRACE, "PcieTopologySelectMasterPll Enter\n");
  MasterLane = 0xFFFF;
  MasterHotplugLane = 0xFFFF;
  EngineList = PcieConfigGetChildEngine (Wrapper);
  while (EngineList != NULL) {
    if (PcieConfigIsEngineAllocated (EngineList) && EngineList->Type.Port.PortData.PortPresent != PortDisabled && PcieConfigIsPcieEngine (EngineList)) {
      if (EngineList->Type.Port.PortData.LinkHotplug != HotplugDisabled) {
        MasterHotplugLane = PcieConfigGetPcieEngineMasterLane (EngineList);
      } else {
        MasterLane = PcieConfigGetPcieEngineMasterLane (EngineList);
        if (PcieConfigIsSbPcieEngine (EngineList)) {
          break;
        }
      }
    }
    EngineList = PcieLibGetNextDescriptor (EngineList);
  }

  if (MasterLane == 0xffff) {
    if (MasterHotplugLane != 0xffff) {
      MasterLane = MasterHotplugLane;
    } else {
      MasterLane = 0x0;
    }
  }

  D0F0xE4_WRAP_8013.Value = PcieRegisterRead (
                              Wrapper,
                              WRAP_SPACE (Wrapper->WrapId, D0F0xE4_WRAP_8013_ADDRESS),
                              Pcie
                              );
  D0F0xE4_WRAP_8013_BASE.Value = D0F0xE4_WRAP_8013.Value;
  if ( MasterLane <= 3 ) {
    D0F0xE4_WRAP_8013.Field.MasterPciePllA = 0x1;
    D0F0xE4_WRAP_8013.Field.MasterPciePllB = 0x0;
    D0F0xE4_WRAP_8013.Field.MasterPciePllC = 0x0;
    D0F0xE4_WRAP_8013.Field.MasterPciePllD = 0x0;
    Wrapper->MasterPll = 0xA;
  } else if (MasterLane <= 7) {
    D0F0xE4_WRAP_8013.Field.MasterPciePllA = 0x0;
    D0F0xE4_WRAP_8013.Field.MasterPciePllB = 0x1;
    D0F0xE4_WRAP_8013.Field.MasterPciePllC = 0x0;
    D0F0xE4_WRAP_8013.Field.MasterPciePllD = 0x0;
    Wrapper->MasterPll = 0xB;
  } else if (MasterLane <= 11) {
    D0F0xE4_WRAP_8013.Field.MasterPciePllA = 0x0;
    D0F0xE4_WRAP_8013.Field.MasterPciePllB = 0x0;
    D0F0xE4_WRAP_8013.Field.MasterPciePllC = 0x1;
    D0F0xE4_WRAP_8013.Field.MasterPciePllD = 0x0;
    Wrapper->MasterPll = 0xC;
  } else {
    D0F0xE4_WRAP_8013.Field.MasterPciePllA = 0x0;
    D0F0xE4_WRAP_8013.Field.MasterPciePllB = 0x0;
    D0F0xE4_WRAP_8013.Field.MasterPciePllC = 0x0;
    D0F0xE4_WRAP_8013.Field.MasterPciePllD = 0x1;
    Wrapper->MasterPll = 0xD;
  }
  if (ConfigChanged != NULL) {
    *ConfigChanged = (D0F0xE4_WRAP_8013.Value == D0F0xE4_WRAP_8013_BASE.Value) ? FALSE : TRUE;
  }
  PcieRegisterWrite (
    Wrapper,
    WRAP_SPACE (Wrapper->WrapId, D0F0xE4_WRAP_8013_ADDRESS),
    D0F0xE4_WRAP_8013.Value,
    FALSE,
    Pcie
    );

  IDS_HDT_CONSOLE (GNB_TRACE, "PcieTopologySelectMasterPll Exit\n");
}

/*----------------------------------------------------------------------------------------*/
/**
 * Execute/clean up reconfiguration
 *
 *
 * @param[in]  Wrapper             Pointer to wrapper config descriptor
 * @param[in]  Pcie                Pointer to global PCIe configuration
 */
VOID
PcieTopologyExecuteReconfig (
  IN      PCIe_WRAPPER_CONFIG   *Wrapper,
  IN      PCIe_PLATFORM_CONFIG  *Pcie
  )
{
  D0F0xE4_WRAP_8062_STRUCT  D0F0xE4_WRAP_8062;
  D0F0xE4_WRAP_8060_STRUCT  D0F0xE4_WRAP_8060;

  if (PcieLibIsPcieWrapper (Wrapper)) {
    IDS_HDT_CONSOLE (GNB_TRACE, "PcieTopologyExecuteReconfig Enter\n");

    PcieTopologyInitSrbmReset (FALSE, Wrapper, Pcie);

    D0F0xE4_WRAP_8062.Value = PcieRegisterRead (
                                Wrapper,
                                WRAP_SPACE (Wrapper->WrapId, D0F0xE4_WRAP_8062_ADDRESS),
                                Pcie
                                );
    D0F0xE4_WRAP_8060.Value = PcieRegisterRead (
                                Wrapper,
                                WRAP_SPACE (Wrapper->WrapId, D0F0xE4_WRAP_8060_ADDRESS),
                                Pcie
                                );

    D0F0xE4_WRAP_8062.Field.ReconfigureEn = 0x1;
    PcieRegisterWrite (
      Wrapper,
      WRAP_SPACE (Wrapper->WrapId, D0F0xE4_WRAP_8062_ADDRESS),
      D0F0xE4_WRAP_8062.Value,
      FALSE,
      Pcie
      );
    D0F0xE4_WRAP_8060.Field.Reconfigure = 0x1;
    PcieRegisterWrite (
      Wrapper,
      WRAP_SPACE (Wrapper->WrapId, D0F0xE4_WRAP_8060_ADDRESS),
      D0F0xE4_WRAP_8060.Value,
      FALSE,
      Pcie
      );
    do {
      D0F0xE4_WRAP_8060.Value = PcieRegisterRead (
                                  Wrapper,
                                  WRAP_SPACE (Wrapper->WrapId, D0F0xE4_WRAP_8060_ADDRESS),
                                  Pcie
                                  );

    } while (D0F0xE4_WRAP_8060.Field.Reconfigure == 1);
    D0F0xE4_WRAP_8062.Field.ConfigXferMode = 0x1;
    D0F0xE4_WRAP_8062.Field.ReconfigureEn = 0x0;
    PcieRegisterWrite (
      Wrapper,
      WRAP_SPACE (Wrapper->WrapId, D0F0xE4_WRAP_8062_ADDRESS),
      D0F0xE4_WRAP_8062.Value,
      FALSE,
      Pcie
      );
    PcieTopologyInitSrbmReset (TRUE, Wrapper, Pcie);
    IDS_HDT_CONSOLE (GNB_TRACE, "PcieTopologyExecuteReconfig Exit\n");
  }
}

/*----------------------------------------------------------------------------------------*/
/**
 * Enable lane reversal
 *
 *
 * @param[in]  Wrapper             Pointer to wrapper config descriptor
 * @param[in]  Pcie                Pointer to global PCIe configuration
 */
VOID
PcieTopologySetLinkReversal (
  IN      PCIe_WRAPPER_CONFIG   *Wrapper,
  IN      PCIe_PLATFORM_CONFIG  *Pcie
  )
{
  PCIe_ENGINE_CONFIG  *EngineList;
  IDS_HDT_CONSOLE (GNB_TRACE, "PcieTopologySetLinkReversal Enter\n");
  EngineList = PcieConfigGetChildEngine (Wrapper);
  while (EngineList != NULL) {
    if (PcieLibIsEngineAllocated (EngineList)) {
      if (PcieLibIsPcieEngine (EngineList)) {
        if (EngineList->EngineData.StartLane > EngineList->EngineData.EndLane) {
            PciePortRegisterWriteField (
              EngineList,
              0xc1 ,
              4 ,
              1 ,
              0x1,
              FALSE,
              Pcie
              );
        }
      }
    }
    EngineList = PcieLibGetNextDescriptor (EngineList);
  }
  IDS_HDT_CONSOLE (GNB_TRACE, "PcieTopologySetLinkReversal Exit\n");
}


/*----------------------------------------------------------------------------------------*/
/**
 * Reduce link width
 *
 *
 * @param[in]  LinkWidth           Link width
 * @param[in]  Engine              Pointer to Engine config descriptor
 * @param[in]  Pcie                Pointer to global PCIe configuration
 */
VOID
PcieTopologyReduceLinkWidth (
  IN      UINT8                 LinkWidth,
  IN      PCIe_ENGINE_CONFIG    *Engine,
  IN      PCIe_PLATFORM_CONFIG  *Pcie
  )
{
  PCIe_WRAPPER_CONFIG       *Wrapper;
  UINT32                    LinkReversed;
  UINT8                     DeltaLinkWidthBitmap;
  UINT32                    LanesToDisable;
  Wrapper = PcieConfigGetParentWrapper (Engine);
  LinkReversed = PcieUtilIsLinkReversed (TRUE, Engine, Pcie);

  DeltaLinkWidthBitmap = (1 << (PcieConfigGetNumberOfCoreLane (Engine) - LinkWidth)) - 1;
  LanesToDisable = (DeltaLinkWidthBitmap << ((LinkReversed == 1) ? Engine->Type.Port.StartCoreLane : (Engine->Type.Port.StartCoreLane +  LinkWidth)));

  PcieTopologyLaneControl (
    DisableLanes,
    LanesToDisable,
    Wrapper,
    Pcie
    );
}

/*----------------------------------------------------------------------------------------*/
/**
 * Lanes enable/disable control
 *
 * @param[in]   Control             Lane control action
 * @param[in]   LaneBitMap          Core lanes bitmap
 * @param[in]   Wrapper             Pointer to Wrapper config descriptor
 * @param[in]   Pcie                Pointer to global PCIe configuration
 */
VOID
PcieTopologyLaneControl (
  IN      LANE_CONTROL          Control,
  IN      UINT32                LaneBitMap,
  IN      PCIe_WRAPPER_CONFIG   *Wrapper,
  IN      PCIe_PLATFORM_CONFIG  *Pcie
    )
{
  D0F0xE4_WRAP_8023_STRUCT  D0F0xE4_WRAP_8023;
  D0F0xE4_WRAP_8023.Value = PcieRegisterRead (
                            Wrapper,
                            WRAP_SPACE (Wrapper->WrapId, D0F0xE4_WRAP_8023_ADDRESS),
                            Pcie
                            );

  if (Control == EnableLanes) {
    D0F0xE4_WRAP_8023.Value |= LaneBitMap;
  } else if (Control == DisableLanes) {
    D0F0xE4_WRAP_8023.Value &= (~LaneBitMap);
  }
  D0F0xE4_WRAP_8023.Value &= ((1 << Wrapper->NumberOfLanes) - 1);
  PcieRegisterWrite (
    Wrapper,
    WRAP_SPACE (Wrapper->WrapId, D0F0xE4_WRAP_8023_ADDRESS),
    D0F0xE4_WRAP_8023.Value,
    TRUE,
    Pcie
    );
}

/*----------------------------------------------------------------------------------------*/
/**
 * Init SRBM reset
 *
 * @param[in]  SrbmResetEnable     SRBM reset enable flag.
 * @param[in]  Wrapper             Pointer to wrapper config descriptor
 * @param[in]  Pcie                Pointer to global PCIe configuration
 */
VOID
PcieTopologyInitSrbmReset (
  IN      BOOLEAN               SrbmResetEnable,
  IN      PCIe_WRAPPER_CONFIG   *Wrapper,
  IN      PCIe_PLATFORM_CONFIG  *Pcie
  )
{
  D0F0xE4_WRAP_8063_STRUCT  D0F0xE4_WRAP_8063;
  D0F0xE4_WRAP_8063.Value = PcieRegisterRead (
                               Wrapper,
                               WRAP_SPACE (Wrapper->WrapId, D0F0xE4_WRAP_8063_ADDRESS),
                               Pcie
                               );
  if (SrbmResetEnable) {
    D0F0xE4_WRAP_8063.Field.line331  = 0x1;
    D0F0xE4_WRAP_8063.Field.line332  = 0x1;
    D0F0xE4_WRAP_8063.Field.line338  = 0x1;
    D0F0xE4_WRAP_8063.Field.line339  = 0x1;
    D0F0xE4_WRAP_8063.Field.line340  = 0x1;
  } else {
    D0F0xE4_WRAP_8063.Field.line331  = 0x0;
    D0F0xE4_WRAP_8063.Field.line332  = 0x0;
    D0F0xE4_WRAP_8063.Field.line338  = 0x0;
    D0F0xE4_WRAP_8063.Field.line339  = 0x0;
    D0F0xE4_WRAP_8063.Field.line340  = 0x0;
  }
  PcieRegisterWrite (
    Wrapper,
    WRAP_SPACE (Wrapper->WrapId, D0F0xE4_WRAP_8063_ADDRESS),
    D0F0xE4_WRAP_8063.Value,
    FALSE,
    Pcie
    );

}

/*----------------------------------------------------------------------------------------*/
/**
 * Set core configuration according to PCIe port topology
 *
 *
 *
 * @param[in]  Wrapper             Pointer to wrapper config descriptor
 * @param[out] ConfigChanged       Pointer to boolean indicator that configuration was changed
 * @param[in]  Pcie                Pointer to global PCIe configuration
 * @retval     AGESA_SUCCESS       Topology successfully mapped
 * @retval     AGESA_ERROR         Topology can not be mapped
 */

AGESA_STATUS
PcieTopologySetCoreConfig (
  IN       PCIe_WRAPPER_CONFIG   *Wrapper,
     OUT   BOOLEAN               *ConfigChanged,
  IN       PCIe_PLATFORM_CONFIG  *Pcie
  )
{
  UINT8                     CoreId;
  AGESA_STATUS              Status;
  D0F0xE4_WRAP_0080_STRUCT  D0F0xE4_WRAP_0080;

  Status = AGESA_SUCCESS;
  if (PcieLibIsPcieWrapper (Wrapper)) {
    for (CoreId = Wrapper->StartPcieCoreId; CoreId <= Wrapper->EndPcieCoreId; CoreId++) {
      UINT64  ConfigurationSignature;
      UINT8   NewConfigurationValue;
      ConfigurationSignature = PcieConfigGetConfigurationSignature (Wrapper, CoreId);
      Status = PcieFmGetCoreConfigurationValue (Wrapper, CoreId, ConfigurationSignature, &NewConfigurationValue);
      if (Status == AGESA_SUCCESS) {
        IDS_HDT_CONSOLE (PCIE_MISC, "  Core Configuration: Wrapper [%s], CoreID [%d] - %s\n",
          PcieFmDebugGetWrapperNameString (Wrapper),
          CoreId,
          PcieFmDebugGetCoreConfigurationString (Wrapper, NewConfigurationValue)
          );
        D0F0xE4_WRAP_0080.Value = PcieRegisterRead (
                                    Wrapper,
                                    WRAP_SPACE (Wrapper->WrapId, D0F0xE4_WRAP_0080_ADDRESS),
                                    Pcie
                                    );
        if (ConfigChanged != NULL) {
          if (D0F0xE4_WRAP_0080.Field.StrapBifLinkConfig != NewConfigurationValue) {
            *ConfigChanged = TRUE;
          }
        }
        D0F0xE4_WRAP_0080.Field.StrapBifLinkConfig = NewConfigurationValue;
        PcieRegisterWrite (
          Wrapper,
          WRAP_SPACE (Wrapper->WrapId, D0F0xE4_WRAP_0080_ADDRESS),
          D0F0xE4_WRAP_0080.Value,
          FALSE,
          Pcie
          );
      } else {
        IDS_HDT_CONSOLE (PCIE_MISC, "  ERROR! Core Configuration : Wrapper [%s], Signature [0x%x, 0x%x]\n",
          PcieFmDebugGetWrapperNameString (Wrapper),
          ((UINT32*)&ConfigurationSignature)[1],
          ((UINT32*)&ConfigurationSignature)[0]
          );
        PcieConfigDisableAllEngines (PciePortEngine | PcieDdiEngine, Wrapper);
      }
    }
  }
  return Status;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Relinquish control to DDI for specific lanes
 *
 *
 * @param[in]  Wrapper         Pointer to wrapper configuration descriptor
 * @param[in]  Pcie            Pointer to global PCIe configuration
 */
VOID
PcieSetDdiOwnPhy (
  IN      PCIe_WRAPPER_CONFIG   *Wrapper,
  IN      PCIe_PLATFORM_CONFIG  *Pcie
  )
{
  ex502_STRUCT   ex502 ;
  UINT32                    LaneBitmap;

  if (PcieLibIsDdiWrapper (Wrapper)) {
    IDS_HDT_CONSOLE (GNB_TRACE, "PcieFmSetDdiOwnPhy Enter\n");
    LaneBitmap = PcieUtilGetWrapperLaneBitMap (LANE_TYPE_DDI_PHY_NATIVE, 0, Wrapper);
    ex502.Value = PcieRegisterRead (
                                Wrapper,
                                WRAP_SPACE (Wrapper->WrapId, 0x8040 ),
                                Pcie
                                );
    if ((LaneBitmap & BIT0) != 0) {
      ex502.Field.OwnPhyA = 0x1;
    }
    if ((LaneBitmap & BIT4) != 0) {
      ex502.Field.OwnPhyB = 0x1;
    }
    if ((LaneBitmap & BIT8) != 0) {
      ex502.Field.OwnPhyC = 0x1;
    }
    if ((LaneBitmap & BIT12) != 0) {
      ex502.Field.OwnPhyD = 0x1;
    }
    PcieRegisterWrite (
      Wrapper,
      WRAP_SPACE (Wrapper->WrapId, 0x8040 ),
      ex502.Value,
      FALSE,
      Pcie
      );
    IDS_HDT_CONSOLE (GNB_TRACE, "PcieFmSetDdiOwnPhy Exit\n");
  }
}

/*----------------------------------------------------------------------------------------*/
/**
 * Set TX control for PCIe lanes
 *
 *
 *
 * @param[in]  Wrapper             Pointer to wrapper config descriptor
 * @param[in]  Pcie                Pointer to global PCIe configuration
 */
VOID
PcieWrapSetTxS1CtrlForLaneMux (
  IN      PCIe_WRAPPER_CONFIG   *Wrapper,
  IN      PCIe_PLATFORM_CONFIG  *Pcie
  )
{
  D0F0xE4_WRAP_8025_STRUCT  D0F0xE4_WRAP_8025;
  UINT32                    LaneBitmap;
  UINTN                     Index;
  D0F0xE4_WRAP_8025.Value = PcieRegisterRead (
                              Wrapper,
                              WRAP_SPACE (Wrapper->WrapId, D0F0xE4_WRAP_8025_ADDRESS),
                              Pcie
                              );
  Index = 0;
  LaneBitmap =  PcieUtilGetWrapperLaneBitMap (LANE_TYPE_CORE_ALL, LANE_TYPE_PCIE_SB_CORE_CONFIG, Wrapper);
  while (LaneBitmap != 0) {
    if ((LaneBitmap & 0xf) != 0) {
      D0F0xE4_WRAP_8025.Value &= (~(0xff << (Index * 8)));
      D0F0xE4_WRAP_8025.Value |= (((0x03 << 3) | 0x1) << (Index * 8));
    }
    LaneBitmap >>= 4;
    ++Index;
  }
  PcieRegisterWrite (
    Wrapper,
    WRAP_SPACE (Wrapper->WrapId, D0F0xE4_WRAP_8025_ADDRESS),
    D0F0xE4_WRAP_8025.Value,
    FALSE,
    Pcie
    );
}

/*----------------------------------------------------------------------------------------*/
/**
 * Set TX control for lane muxes
 *
 *
 *
 * @param[in]  Wrapper             Pointer to wrapper config descriptor
 * @param[in]  Pcie                Pointer to global PCIe configuration
 */
VOID
PcieWrapSetTxOffCtrlForLaneMux (
  IN      PCIe_WRAPPER_CONFIG   *Wrapper,
  IN      PCIe_PLATFORM_CONFIG  *Pcie
  )
{
  PcieRegisterWrite (
    Wrapper,
    WRAP_SPACE (Wrapper->WrapId, D0F0xE4_WRAP_8025_ADDRESS),
    0x1f1f1f1f,
    FALSE,
    Pcie
    );
}
