/**
 * @file
 *
 * PCIe link ASPM Black List
 *
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:     AGESA
 * @e sub-project: GNB
 * @e \$Revision: 84150 $   @e \$Date: 2012-12-12 15:46:25 -0600 (Wed, 12 Dec 2012) $
 *
 */
/*
*****************************************************************************
*
 * Copyright (c) 2008 - 2013, Advanced Micro Devices, Inc.
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
#include  "Gnb.h"
#include  "GnbPcie.h"
#include  "GnbCommonLib.h"
#include  "PcieAspmBlackList.h"
#include  "Filecode.h"
#define FILECODE PROC_GNB_MODULES_GNBPCIEINITLIBV1_PCIEASPMBLACKLIST_FILECODE
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


UINT16  AspmBrDeviceTable[] = {
 0x1002, 0x9441, (UINT16) ~(AspmL1 | AspmL0s),
 0x10B5, 0xFFFF, (UINT16) ~(AspmL1 | AspmL0s),
 0x10DE, 0x0402, (UINT16) ~(AspmL1 | AspmL0s),
 0x10DE, 0x0193, (UINT16) ~(AspmL1 | AspmL0s),
 0x10DE, 0x0422, (UINT16) ~(AspmL1 | AspmL0s),
 0x10DE, 0x0292, (UINT16) ~(AspmL1 | AspmL0s),
 0x10DE, 0x00F9, (UINT16) ~(AspmL1 | AspmL0s),
 0x10DE, 0x0141, (UINT16) ~(AspmL1 | AspmL0s),
 0x10DE, 0x0092, (UINT16) ~(AspmL1 | AspmL0s),
 0x10DE, 0x01D0, (UINT16) ~(AspmL1 | AspmL0s),
 0x10DE, 0x01D1, (UINT16) ~(AspmL1 | AspmL0s),
 0x10DE, 0x01D2, (UINT16) ~(AspmL1 | AspmL0s),
 0x10DE, 0x01D3, (UINT16) ~(AspmL1 | AspmL0s),
 0x10DE, 0x01D5, (UINT16) ~(AspmL1 | AspmL0s),
 0x10DE, 0x01D7, (UINT16) ~(AspmL1 | AspmL0s),
 0x10DE, 0x01D8, (UINT16) ~(AspmL1 | AspmL0s),
 0x10DE, 0x01DC, (UINT16) ~(AspmL1 | AspmL0s),
 0x10DE, 0x01DE, (UINT16) ~(AspmL1 | AspmL0s),
 0x10DE, 0x01DF, (UINT16) ~(AspmL1 | AspmL0s),
 0x10DE, 0x016A, (UINT16) ~(AspmL1 | AspmL0s),
 0x10DE, 0x0392, (UINT16) ~(AspmL1 | AspmL0s),
 0x168C, 0xFFFF, (UINT16) ~(AspmL0s),
 0x1B4B, 0x91A3, (UINT16) ~(AspmL0s),
 0x1B4B, 0x9123, (UINT16) ~(AspmL0s),
 0x1969, 0x1083, (UINT16) ~(AspmL0s),
 0x1033, 0x0194, (UINT16) ~(AspmL0s),
 0x1180, 0xE832, (UINT16) ~(AspmL0s),
 0x1180, 0xE823, (UINT16) ~(AspmL0s)
};

UINT16  Aspm168cL0sEnabled[] = {
  0x002B,
  0x002C,
  0x002E,
  0x002A,
  0x002D,
  0x0024,
  0x001B,
  0x0030,
  0x0032
};

/*----------------------------------------------------------------------------------------*/
/**
 * Pcie ASPM Black List
 *
 *
 *
 * @param[in] LinkAspm            PCie ASPM black list
 * @param[in] StdHeader           Standard configuration header
 * @retval     AGESA_STATUS
 */

AGESA_STATUS
PcieAspmBlackListFeature (
  IN       PCIe_LINK_ASPM         *LinkAspm,
  IN       AMD_CONFIG_PARAMS      *StdHeader
  )
{
  UINT32  UpstreamDeviceId;
  UINT32  DownstreamDeviceId;
  UINTN   i;
  UINT32  DeviceId;
  UINT32  VendorId;

  GnbLibPciRead (LinkAspm->UpstreamPort.AddressValue, AccessWidth32, &UpstreamDeviceId, StdHeader);
  GnbLibPciRead (LinkAspm->DownstreamPort.AddressValue, AccessWidth32, &DownstreamDeviceId, StdHeader);
  LinkAspm->BlackList = FALSE;
  for (i = 0; i < ARRAY_SIZE(AspmBrDeviceTable); i = i + 3) {
    VendorId = AspmBrDeviceTable[i];
    DeviceId = AspmBrDeviceTable[i + 1];
    if (VendorId == (UINT16)UpstreamDeviceId || VendorId == (UINT16)DownstreamDeviceId ) {
      if (DeviceId == 0xFFFF || DeviceId == (UpstreamDeviceId >> 16) || DeviceId == (DownstreamDeviceId >> 16)) {
        LinkAspm->UpstreamAspm &= AspmBrDeviceTable[i + 2];
        LinkAspm->DownstreamAspm &= AspmBrDeviceTable[i + 2];
        LinkAspm->BlackList = TRUE;
      }
    }
  }
  if ((UINT16)UpstreamDeviceId == 0x168c) {
    // Atheros (Ignore dev capability enable L1 if requested)
    LinkAspm->UpstreamAspm = LinkAspm->RequestedAspm & AspmL1;
    LinkAspm->DownstreamAspm = LinkAspm->UpstreamAspm;
    GnbLibPciRMW (LinkAspm->UpstreamPort.AddressValue | 0x70C, AccessS3SaveWidth32, 0x0, 0x0F003F01, StdHeader);

    DeviceId = UpstreamDeviceId >> 16;
    for (i = 0; i < ARRAY_SIZE(Aspm168cL0sEnabled); i++) {
      if (DeviceId == Aspm168cL0sEnabled[i]) {
        LinkAspm->UpstreamAspm = LinkAspm->RequestedAspm & AspmL0sL1;
        LinkAspm->DownstreamAspm = LinkAspm->UpstreamAspm & AspmL1;
      }
    }

  }
  if (UpstreamDeviceId == 0x10831969) {
    GnbLibPciRMW (LinkAspm->UpstreamPort.AddressValue | 0x12F8, AccessS3SaveWidth32, 0xFFF7F7FF, 0, StdHeader);
  }

  return AGESA_SUCCESS;
}
