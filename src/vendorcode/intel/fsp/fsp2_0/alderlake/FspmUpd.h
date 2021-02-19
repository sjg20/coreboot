/** @file

Copyright (c) 2021, Intel Corporation. All rights reserved.<BR>

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.
* Redistributions in binary form must reproduce the above copyright notice, this
  list of conditions and the following disclaimer in the documentation and/or
  other materials provided with the distribution.
* Neither the name of Intel Corporation nor the names of its contributors may
  be used to endorse or promote products derived from this software without
  specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
  THE POSSIBILITY OF SUCH DAMAGE.

  This file is automatically generated. Please do NOT modify !!!

**/

#ifndef __FSPMUPD_H__
#define __FSPMUPD_H__

#include <FspUpd.h>

#pragma pack(1)


#include <MemInfoHob.h>

///
/// The ChipsetInit Info structure provides the information of ME ChipsetInit CRC and BIOS ChipsetInit CRC.
///
typedef struct {
  UINT8             Revision;         ///< Chipset Init Info Revision
  UINT8             Rsvd[3];          ///< Reserved
  UINT16            MeChipInitCrc;    ///< 16 bit CRC value of MeChipInit Table
  UINT16            BiosChipInitCrc;  ///< 16 bit CRC value of PchChipInit Table
} CHIPSET_INIT_INFO;


/** Fsp M Configuration
**/
typedef struct {

/** Offset 0x0040 - Platform Reserved Memory Size
  The minimum platform memory size required to pass control into DXE
**/
  UINT64                      PlatformMemorySize;

/** Offset 0x0048 - SPD Data Length
  Length of SPD Data
  0x100:256 Bytes, 0x200:512 Bytes, 0x400:1024 Bytes
**/
  UINT16                      MemorySpdDataLen;

/** Offset 0x004A - Reserved
**/
  UINT8                       Reserved0[2];

/** Offset 0x004C - MemorySpdPtr00
**/
  UINT32                      MemorySpdPtr00;

/** Offset 0x0050 - MemorySpdPtr01
**/
  UINT32                      MemorySpdPtr01;

/** Offset 0x0054 - MemorySpdPtr02
**/
  UINT32                      MemorySpdPtr02;

/** Offset 0x0058 - MemorySpdPtr03
**/
  UINT32                      MemorySpdPtr03;

/** Offset 0x005C - MemorySpdPtr04
**/
  UINT32                      MemorySpdPtr04;

/** Offset 0x0060 - MemorySpdPtr05
**/
  UINT32                      MemorySpdPtr05;

/** Offset 0x0064 - MemorySpdPtr06
**/
  UINT32                      MemorySpdPtr06;

/** Offset 0x0068 - MemorySpdPtr07
**/
  UINT32                      MemorySpdPtr07;

/** Offset 0x006C - MemorySpdPtr08
**/
  UINT32                      MemorySpdPtr08;

/** Offset 0x0070 - MemorySpdPtr09
**/
  UINT32                      MemorySpdPtr09;

/** Offset 0x0074 - MemorySpdPtr10
**/
  UINT32                      MemorySpdPtr10;

/** Offset 0x0078 - MemorySpdPtr11
**/
  UINT32                      MemorySpdPtr11;

/** Offset 0x007C - MemorySpdPtr12
**/
  UINT32                      MemorySpdPtr12;

/** Offset 0x0080 - MemorySpdPtr13
**/
  UINT32                      MemorySpdPtr13;

/** Offset 0x0084 - MemorySpdPtr14
**/
  UINT32                      MemorySpdPtr14;

/** Offset 0x0088 - MemorySpdPtr15
**/
  UINT32                      MemorySpdPtr15;

/** Offset 0x008C - RcompResistor settings
  Indicates  RcompResistor settings: Board-dependent
**/
  UINT16                      RcompResistor;

/** Offset 0x008E - RcompTarget settings
  RcompTarget settings: board-dependent
**/
  UINT16                      RcompTarget[5];

/** Offset 0x0098 - DqsMapCpu2DramCh0
**/
  UINT8                       DqsMapCpu2DramCh0[2];

/** Offset 0x009A - DqsMapCpu2DramCh1
**/
  UINT8                       DqsMapCpu2DramCh1[2];

/** Offset 0x009C - DqsMapCpu2DramCh2
**/
  UINT8                       DqsMapCpu2DramCh2[2];

/** Offset 0x009E - DqsMapCpu2DramCh3
**/
  UINT8                       DqsMapCpu2DramCh3[2];

/** Offset 0x00A0 - DqsMapCpu2DramCh4
**/
  UINT8                       DqsMapCpu2DramCh4[2];

/** Offset 0x00A2 - DqsMapCpu2DramCh5
**/
  UINT8                       DqsMapCpu2DramCh5[2];

/** Offset 0x00A4 - DqsMapCpu2DramCh6
**/
  UINT8                       DqsMapCpu2DramCh6[2];

/** Offset 0x00A6 - DqsMapCpu2DramCh7
**/
  UINT8                       DqsMapCpu2DramCh7[2];

/** Offset 0x00A8 - DqMapCpu2DramCh0
**/
  UINT8                       DqMapCpu2DramCh0[16];

/** Offset 0x00B8 - DqMapCpu2DramCh1
**/
  UINT8                       DqMapCpu2DramCh1[16];

/** Offset 0x00C8 - DqMapCpu2DramCh2
**/
  UINT8                       DqMapCpu2DramCh2[16];

/** Offset 0x00D8 - DqMapCpu2DramCh3
**/
  UINT8                       DqMapCpu2DramCh3[16];

/** Offset 0x00E8 - DqMapCpu2DramCh4
**/
  UINT8                       DqMapCpu2DramCh4[16];

/** Offset 0x00F8 - DqMapCpu2DramCh5
**/
  UINT8                       DqMapCpu2DramCh5[16];

/** Offset 0x0108 - DqMapCpu2DramCh6
**/
  UINT8                       DqMapCpu2DramCh6[16];

/** Offset 0x0118 - DqMapCpu2DramCh7
**/
  UINT8                       DqMapCpu2DramCh7[16];

/** Offset 0x0128 - Dqs Pins Interleaved Setting
  Indicates DqPinsInterleaved setting: board-dependent
  $EN_DIS
**/
  UINT8                       DqPinsInterleaved;

/** Offset 0x0129 - Reserved
**/
  UINT8                       Reserved1;

/** Offset 0x012A - MRC Fast Boot
  Enables/Disable the MRC fast path thru the MRC
  $EN_DIS
**/
  UINT8                       MrcFastBoot;

/** Offset 0x012B - Rank Margin Tool per Task
  This option enables the user to execute Rank Margin Tool per major training step
  in the MRC.
  $EN_DIS
**/
  UINT8                       RmtPerTask;

/** Offset 0x012C - Reserved
**/
  UINT8                       Reserved2[4];

/** Offset 0x0130 - Tseg Size
  Size of SMRAM memory reserved. 0x400000 for Release build and 0x1000000 for Debug build
  0x0400000:4MB, 0x01000000:16MB
**/
  UINT32                      TsegSize;

/** Offset 0x0134 - Reserved
**/
  UINT8                      Reserved3[3];

/** Offset 0x0137 - Enable SMBus
  Enable/disable SMBus controller.
  $EN_DIS
**/
  UINT8                       SmbusEnable;

/** Offset 0x0138 - Spd Address Tabl
  Specify SPD Address table for CH0D0/CH0D1/CH1D0&CH1D1. MemorySpdPtr will be used
  if SPD Address is 00
**/
  UINT8                       SpdAddressTable[16];

/** Offset 0x0148 - Platform Debug Consent
  Enabled(All Probes+TraceHub) supports all probes with TraceHub enabled and blocks
  s0ix\n
  Enabled(Low Power) does not suppoert DCI OOB 4-wire with TraceHub disabled, s0ix
  is viable\n
  Manual:user needs to configure Advanced Debug Settings manually, aimed at advanced users
  0:Disabled, 2:Enabled (All Probes+TraceHub), 6:Enable (Low Power), 7:Manual
**/
  UINT8                       PlatformDebugConsent;

/** Offset 0x0149 - Reserved
**/
  UINT8                       Reserved4[14];

/** Offset 0x0157 - State of X2APIC_OPT_OUT bit in the DMAR table
  0=Disable/Clear, 1=Enable/Set
  $EN_DIS
**/
  UINT8                       X2ApicOptOut;

/** Offset 0x0158 - Reserved
**/
  UINT8                       Reserved5[40];

/** Offset 0x0180 - Disable VT-d
  0=Enable/FALSE(VT-d enabled), 1=Disable/TRUE (VT-d disabled)
  $EN_DIS
**/
  UINT8                       VtdDisable;

/** Offset 0x0181 - Reserved
**/
  UINT8                       Reserved6[4];

/** Offset 0x0185 - Internal Graphics Pre-allocated Memory
  Size of memory preallocated for internal graphics.
  0x00:0MB, 0x01:32MB, 0x02:64MB, 0x03:96MB, 0x04:128MB, 0x05:160MB, 0xF0:4MB, 0xF1:8MB,
  0xF2:12MB, 0xF3:16MB, 0xF4:20MB, 0xF5:24MB, 0xF6:28MB, 0xF7:32MB, 0xF8:36MB, 0xF9:40MB,
  0xFA:44MB, 0xFB:48MB, 0xFC:52MB, 0xFD:56MB, 0xFE:60MB
**/
  UINT8                       IgdDvmt50PreAlloc;

/** Offset 0x0186 - Internal Graphics
  Enable/disable internal graphics.
  $EN_DIS
**/
  UINT8                       InternalGfx;

/** Offset 0x0187 - Reserved
**/
  UINT8                       Reserved7;

/** Offset 0x0188 - Board Type
  MrcBoardType, Options are 0=Mobile/Mobile Halo, 1=Desktop/DT Halo, 5=ULT/ULX/Mobile
  Halo, 7=UP Server
  0:Mobile/Mobile Halo, 1:Desktop/DT Halo, 5:ULT/ULX/Mobile Halo, 7:UP Server
**/
  UINT8                       UserBd;

/** Offset 0x0189 - Reserved
**/
  UINT8                       Reserved8[3];

/** Offset 0x018C - SA GV
  System Agent dynamic frequency support and when enabled memory will be training
  at three different frequencies.
  0:Disabled, 1:FixedPoint0, 2:FixedPoint1, 3:FixedPoint2, 4:FixedPoint3, 5:Enabled
**/
  UINT8                       SaGv;

/** Offset 0x018D - Reserved
**/
  UINT8                       Reserved9[2];

/** Offset 0x018F - Rank Margin Tool
  Enable/disable Rank Margin Tool.
  $EN_DIS
**/
  UINT8                       RMT;

/** Offset 0x0190 - Controller 0 Channel 0 DIMM Control
  Controller 1 Channel 0 DIMM Control Support - Enable or Disable Dimms on Channel A.
  0:Enable both DIMMs, 1:Disable DIMM0, 2:Disable DIMM1, 3:Disable both DIMMs
**/
  UINT8                       DisableDimmMc0Ch0;

/** Offset 0x0191 - Controller 0 Channel 1 DIMM Control
  Controller 1 Channel 1 DIMM Control Support - Enable or Disable Dimms on Channel B.
  0:Enable both DIMMs, 1:Disable DIMM0, 2:Disable DIMM1, 3:Disable both DIMMs
**/
  UINT8                       DisableDimmMc0Ch1;

/** Offset 0x0192 - Controller 0 Channel 2 DIMM Control
  Controller 0 Channel 2 DIMM Control Support - Enable or Disable Dimms on Channel A.
  0:Enable both DIMMs, 1:Disable DIMM0, 2:Disable DIMM1, 3:Disable both DIMMs
**/
  UINT8                       DisableDimmMc0Ch2;

/** Offset 0x0193 - Controller 0 Channel 3 DIMM Control
  Controller 0 Channel 3 DIMM Control Support - Enable or Disable Dimms on Channel B.
  0:Enable both DIMMs, 1:Disable DIMM0, 2:Disable DIMM1, 3:Disable both DIMMs
**/
  UINT8                       DisableDimmMc0Ch3;

/** Offset 0x0194 - Controller 1 Channel 0 DIMM Control
  Controller 1 Channel 0 DIMM Control Support - Enable or Disable Dimms on Channel A.
  0:Enable both DIMMs, 1:Disable DIMM0, 2:Disable DIMM1, 3:Disable both DIMMs
**/
  UINT8                       DisableDimmMc1Ch0;

/** Offset 0x0195 - Controller 1 Channel 1 DIMM Control
  Controller 1 Channel 1 DIMM Control Support - Enable or Disable Dimms on Channel B.
  0:Enable both DIMMs, 1:Disable DIMM0, 2:Disable DIMM1, 3:Disable both DIMMs
**/
  UINT8                       DisableDimmMc1Ch1;

/** Offset 0x0196 - Controller 1 Channel 2 DIMM Control
  Controller 1 Channel 2 DIMM Control Support - Enable or Disable Dimms on Channel A.
  0:Enable both DIMMs, 1:Disable DIMM0, 2:Disable DIMM1, 3:Disable both DIMMs
**/
  UINT8                       DisableDimmMc1Ch2;

/** Offset 0x0197 - Controller 1 Channel 3 DIMM Control
  Controller 1 Channel 3 DIMM Control Support - Enable or Disable Dimms on Channel B.
  0:Enable both DIMMs, 1:Disable DIMM0, 2:Disable DIMM1, 3:Disable both DIMMs
**/
  UINT8                       DisableDimmMc1Ch3;

/** Offset 0x0198 - Reserved
**/
  UINT8                       Reserved10[2];

/** Offset 0x019A - Memory Reference Clock
  100MHz, 133MHz.
  0:133MHz, 1:100MHz
**/
  UINT8                       RefClk;

/** Offset 0x019B - Reserved
**/
  UINT8                       Reserved11[22];

/** Offset 0x01B1 - Enable Intel HD Audio (Azalia)
  0: Disable, 1: Enable (Default) Azalia controller
  $EN_DIS
**/
  UINT8                       PchHdaEnable;

/** Offset 0x01B2 - Enable PCH ISH Controller
  0: Disable, 1: Enable (Default) ISH Controller
  $EN_DIS
**/
  UINT8                       PchIshEnable;

/** Offset 0x01B3 - Reserved
**/
  UINT8                       Reserved12[107];

/** Offset 0x021E - IMGU CLKOUT Configuration
  The configuration of IMGU CLKOUT, 0: Disable;<b>1: Enable</b>.
  $EN_DIS
**/
  UINT8                       ImguClkOutEn[6];

/** Offset 0x0224 - Enable PCIE RP Mask
  Enable/disable PCIE Root Ports. 0: disable, 1: enable. One bit for each port, bit0
  for port1, bit1 for port2, and so on.
**/
  UINT32                      CpuPcieRpEnableMask;

/** Offset 0x0228 - Reserved
**/
  UINT8                       Reserved13;

/** Offset 0x0229 - RpClockReqMsgEnable
**/
  UINT8                       RpClockReqMsgEnable[3];

/** Offset 0x022C - RpPcieThresholdBytes
**/
  UINT8                       RpPcieThresholdBytes[4];

/** Offset 0x0230 - Reserved
**/
  UINT8                       Reserved14;

/** Offset 0x0231 - Program GPIOs for LFP on DDI port-A device
  0=Disabled,1(Default)=eDP, 2=MIPI DSI
  0:Disabled, 1:eDP, 2:MIPI DSI
**/
  UINT8                       DdiPortAConfig;

/** Offset 0x0232 - Program GPIOs for LFP on DDI port-B device
  0(Default)=Disabled,1=eDP, 2=MIPI DSI
  0:Disabled, 1:eDP, 2:MIPI DSI
**/
  UINT8                       DdiPortBConfig;

/** Offset 0x0233 - Enable or disable HPD of DDI port A
  0(Default)=Disable, 1=Enable
  $EN_DIS
**/
  UINT8                       DdiPortAHpd;

/** Offset 0x0234 - Enable or disable HPD of DDI port B
  0=Disable, 1(Default)=Enable
  $EN_DIS
**/
  UINT8                       DdiPortBHpd;

/** Offset 0x0235 - Enable or disable HPD of DDI port C
  0(Default)=Disable, 1=Enable
  $EN_DIS
**/
  UINT8                       DdiPortCHpd;

/** Offset 0x0236 - Enable or disable HPD of DDI port 1
  0=Disable, 1(Default)=Enable
  $EN_DIS
**/
  UINT8                       DdiPort1Hpd;

/** Offset 0x0237 - Enable or disable HPD of DDI port 2
  0(Default)=Disable, 1=Enable
  $EN_DIS
**/
  UINT8                       DdiPort2Hpd;

/** Offset 0x0238 - Enable or disable HPD of DDI port 3
  0(Default)=Disable, 1=Enable
  $EN_DIS
**/
  UINT8                       DdiPort3Hpd;

/** Offset 0x0239 - Enable or disable HPD of DDI port 4
  0(Default)=Disable, 1=Enable
  $EN_DIS
**/
  UINT8                       DdiPort4Hpd;

/** Offset 0x023A - Enable or disable DDC of DDI port A
  0(Default)=Disable, 1=Enable
  $EN_DIS
**/
  UINT8                       DdiPortADdc;

/** Offset 0x023B - Enable or disable DDC of DDI port B
  0=Disable, 1(Default)=Enable
  $EN_DIS
**/
  UINT8                       DdiPortBDdc;

/** Offset 0x023C - Enable or disable DDC of DDI port C
  0(Default)=Disable, 1=Enable
  $EN_DIS
**/
  UINT8                       DdiPortCDdc;

/** Offset 0x023D - Enable DDC setting of DDI Port 1
  0(Default)=Disable, 1=Enable
  $EN_DIS
**/
  UINT8                       DdiPort1Ddc;

/** Offset 0x023E - Enable DDC setting of DDI Port 2
  0(Default)=Disable, 1=Enable
  $EN_DIS
**/
  UINT8                       DdiPort2Ddc;

/** Offset 0x023F - Enable DDC setting of DDI Port 3
  0(Default)=Disable, 1=Enable
  $EN_DIS
**/
  UINT8                       DdiPort3Ddc;

/** Offset 0x0240 - Enable DDC setting of DDI Port 4
  0(Default)=Disable, 1=Enable
  $EN_DIS
**/
  UINT8                       DdiPort4Ddc;

/** Offset 0x0241 - Reserved
**/
  UINT8                       Reserved15[141];

/** Offset 0x02CE - DMI Gen3 Root port preset values per lane
  Used for programming DMI Gen3 preset values per lane. Range: 0-9, 8 is default for each lane
**/
  UINT8                       DmiGen3RootPortPreset[8];

/** Offset 0x02D6 - Reserved
**/
  UINT8                       Reserved16[150];

/** Offset 0x036C - C6DRAM power gating feature
  This policy indicates whether or not BIOS should allocate PRMRR memory for C6DRAM
  power gating feature.- 0: Don't allocate any PRMRR memory for C6DRAM power gating
  feature.- <b>1: Allocate PRMRR memory for C6DRAM power gating feature</b>.
  $EN_DIS
**/
  UINT8                       EnableC6Dram;

/** Offset 0x036D - Reserved
**/
  UINT8                       Reserved17[5];

/** Offset 0x0372 - Hyper Threading Enable/Disable
  Enable or Disable Hyper Threading; 0: Disable; <b>1: Enable</b>
  $EN_DIS
**/
  UINT8                       HyperThreading;

/** Offset 0x0373 - Reserved
**/
  UINT8                       Reserved18;

/** Offset 0x0374 - CPU ratio value
  CPU ratio value. Valid Range 0 to 63
**/
  UINT8                       CpuRatio;

/** Offset 0x0375 - Boot frequency
  Sets the boot frequency starting from reset vector.- 0: Maximum battery performance.
  1: Maximum non-turbo performance. <b>2: Turbo performance </b>
  0:0, 1:1, 2:2
**/
  UINT8                       BootFrequency;

/** Offset 0x0376 - Reserved
**/
  UINT8                       Reserved19;

/** Offset 0x0377 - Processor Early Power On Configuration FCLK setting
  <b>0: 800 MHz (ULT/ULX)</b>. <b>1: 1 GHz (DT/Halo)</b>. Not supported on ULT/ULX.-
  2: 400 MHz. - 3: Reserved
  0:800 MHz, 1: 1 GHz, 2: 400 MHz, 3: Reserved
**/
  UINT8                       FClkFrequency;

/** Offset 0x0378 - Reserved
**/
  UINT8                       Reserved20;

/** Offset 0x0379 - Enable or Disable VMX
  Enable or Disable VMX; 0: Disable; <b>1: Enable</b>.
  $EN_DIS
**/
  UINT8                       VmxEnable;

/** Offset 0x037A - Reserved
**/
  UINT8                       Reserved21[20];

/** Offset 0x038E - Enable or Disable TME
  Enable or Disable TME; <b>0: Disable</b>; 1: Enable.
  $EN_DIS
**/
  UINT8                       TmeEnable;

/** Offset 0x038F - Reserved
**/
  UINT8                       Reserved22[3];

/** Offset 0x0392 - BiosGuard
  Enable/Disable. 0: Disable, Enable/Disable BIOS Guard feature, 1: enable
  $EN_DIS
**/
  UINT8                       BiosGuard;

/** Offset 0x0393
**/
  UINT8                       BiosGuardToolsInterface;

/** Offset 0x0394 - Reserved
**/
  UINT8                       Reserved23[4];

/** Offset 0x0398 - PrmrrSize
  Enable/Disable. 0: Disable, define default value of PrmrrSize , 1: enable
**/
  UINT32                      PrmrrSize;

/** Offset 0x039C - SinitMemorySize
  Enable/Disable. 0: Disable, define default value of SinitMemorySize , 1: enable
**/
  UINT32                      SinitMemorySize;

/** Offset 0x03A0 - Reserved
**/
  UINT8                      Reserved24[8];

/** Offset 0x03A8 - TxtHeapMemorySize
  Enable/Disable. 0: Disable, define default value of TxtHeapMemorySize , 1: enable
**/
  UINT32                      TxtHeapMemorySize;

/** Offset 0x03AC - TxtDprMemorySize
  Enable/Disable. 0: Disable, define default value of TxtDprMemorySize , 1: enable
**/
  UINT32                      TxtDprMemorySize;

/** Offset 0x03B0 - Reserved
**/
  UINT8                      Reserved25[625];

/** Offset 0x0621 - Number of RsvdSmbusAddressTable.
  The number of elements in the RsvdSmbusAddressTable.
**/
  UINT8                       PchNumRsvdSmbusAddresses;

/** Offset 0x0622 - Reserved
**/
  UINT8                      Reserved26[3];

/** Offset 0x0625 - Usage type for ClkSrc
  0-23: PCH rootport, 0x40-0x43: PEG port, 0x70:LAN, 0x80: unspecified but in use
  (free running), 0xFF: not used
**/
  UINT8                       PcieClkSrcUsage[18];

/** Offset 0x0637 - Reserved
**/
  UINT8                       Reserved27[14];

/** Offset 0x0645 - ClkReq-to-ClkSrc mapping
  Number of ClkReq signal assigned to ClkSrc
**/
  UINT8                       PcieClkSrcClkReq[18];

/** Offset 0x0657 - Reserved
**/
  UINT8                       Reserved28[93];

/** Offset 0x06B4 - Enable PCIE RP Mask
  Enable/disable PCIE Root Ports. 0: disable, 1: enable. One bit for each port, bit0
  for port1, bit1 for port2, and so on.
**/
  UINT32                      PcieRpEnableMask;

/** Offset 0x06B8 - Reserved
**/
  UINT8                       Reserved29[2];

/** Offset 0x06BA - Enable HD Audio Link
  Enable/disable HD Audio Link. Muxed with SSP0/SSP1/SNDW1.
  $EN_DIS
**/
  UINT8                       PchHdaAudioLinkHdaEnable;

/** Offset 0x06BB - Reserved
**/
  UINT8                       Reserved30[3];

/** Offset 0x06BE - Enable HD Audio DMIC_N Link
  Enable/disable HD Audio DMIC1 link. Muxed with SNDW3.
**/
  UINT8                       PchHdaAudioLinkDmicEnable[2];

/** Offset 0x06C0 - DMIC<N> ClkA Pin Muxing (N - DMIC number)
  Determines DMIC<N> ClkA Pin muxing. See  GPIO_*_MUXING_DMIC<N>_CLKA_*
**/
  UINT32                      PchHdaAudioLinkDmicClkAPinMux[2];

/** Offset 0x06C8 - DMIC<N> ClkB Pin Muxing
  Determines DMIC<N> ClkA Pin muxing. See GPIO_*_MUXING_DMIC<N>_CLKB_*
**/
  UINT32                      PchHdaAudioLinkDmicClkBPinMux[2];

/** Offset 0x06D0 - Enable HD Audio DSP
  Enable/disable HD Audio DSP feature.
  $EN_DIS
**/
  UINT8                       PchHdaDspEnable;

/** Offset 0x06D1 - Reserved
**/
  UINT8                       Reserved31[3];

/** Offset 0x06D4 - DMIC<N> Data Pin Muxing
  Determines DMIC<N> Data Pin muxing. See GPIO_*_MUXING_DMIC<N>_DATA_*
**/
  UINT32                      PchHdaAudioLinkDmicDataPinMux[2];

/** Offset 0x06DC - Enable HD Audio SSP0 Link
  Enable/disable HD Audio SSP_N/I2S link. Muxed with HDA. N-number 0-5
**/
  UINT8                       PchHdaAudioLinkSspEnable[6];

/** Offset 0x06E2 - Enable HD Audio SoundWire#N Link
  Enable/disable HD Audio SNDW#N link. Muxed with HDA.
**/
  UINT8                       PchHdaAudioLinkSndwEnable[4];

/** Offset 0x06E6 - iDisp-Link Frequency
  iDisp-Link Freq (PCH_HDAUDIO_LINK_FREQUENCY enum): 4: 96MHz, 3: 48MHz.
  4: 96MHz, 3: 48MHz
**/
  UINT8                       PchHdaIDispLinkFrequency;

/** Offset 0x06E7 - iDisp-Link T-mode
  iDisp-Link T-Mode (PCH_HDAUDIO_IDISP_TMODE enum): 0: 2T, 2: 4T, 3: 8T, 4: 16T
  0: 2T, 2: 4T, 3: 8T, 4: 16T
**/
  UINT8                       PchHdaIDispLinkTmode;

/** Offset 0x06E8 - iDisplay Audio Codec disconnection
  0: Not disconnected, enumerable, 1: Disconnected SDI, not enumerable.
  $EN_DIS
**/
  UINT8                       PchHdaIDispCodecDisconnect;

/** Offset 0x06E9 - Debug Interfaces
  Debug Interfaces. BIT0-RAM, BIT1-UART, BIT3-USB3, BIT4-Serial IO, BIT5-TraceHub,
  BIT2 - Not used.
**/
  UINT8                       PcdDebugInterfaceFlags;

/** Offset 0x06EA - Serial Io Uart Debug Controller Number
  Select SerialIo Uart Controller for debug. Note: If UART0 is selected as CNVi BT
  Core interface, it cannot be used for debug purpose.
  0:SerialIoUart0, 1:SerialIoUart1, 2:SerialIoUart2
**/
  UINT8                       SerialIoUartDebugControllerNumber;

/** Offset 0x06EB - Reserved
**/
  UINT8                       Reserved32[13];

/** Offset 0x06F8 - ISA Serial Base selection
  Select ISA Serial Base address. Default is 0x3F8.
  0:0x3F8, 1:0x2F8
**/
  UINT8                       PcdIsaSerialUartBase;

/** Offset 0x06F9 - Reserved
**/
  UINT8                       Reserved33[4];

/** Offset 0x06FD - MRC Safe Config
  Enables/Disable MRC Safe Config
  $EN_DIS
**/
  UINT8                       MrcSafeConfig;

/** Offset 0x06FE - TCSS Thunderbolt PCIE Root Port 0 Enable
  Set TCSS Thunderbolt PCIE Root Port 0. 0:Disabled  1:Enabled
  $EN_DIS
**/
  UINT8                       TcssItbtPcie0En;

/** Offset 0x06FF - TCSS Thunderbolt PCIE Root Port 1 Enable
  Set TCSS Thunderbolt PCIE Root Port 1. 0:Disabled  1:Enabled
  $EN_DIS
**/
  UINT8                       TcssItbtPcie1En;

/** Offset 0x0700 - TCSS Thunderbolt PCIE Root Port 2 Enable
  Set TCSS Thunderbolt PCIE Root Port 2. 0:Disabled  1:Enabled
  $EN_DIS
**/
  UINT8                       TcssItbtPcie2En;

/** Offset 0x0701 - TCSS Thunderbolt PCIE Root Port 3 Enable
  Set TCSS Thunderbolt PCIE Root Port 3. 0:Disabled  1:Enabled
  $EN_DIS
**/
  UINT8                       TcssItbtPcie3En;

/** Offset 0x0702 - TCSS USB HOST (xHCI) Enable
  Set TCSS XHCI. 0:Disabled  1:Enabled - Must be enabled if xDCI is enabled below
  $EN_DIS
**/
  UINT8                       TcssXhciEn;

/** Offset 0x0703 - TCSS USB DEVICE (xDCI) Enable
  Set TCSS XDCI. 0:Disabled  1:Enabled - xHCI must be enabled if xDCI is enabled
  $EN_DIS
**/
  UINT8                       TcssXdciEn;

/** Offset 0x0704 - TCSS DMA0 Enable
  Set TCSS DMA0. 0:Disabled  1:Enabled
  $EN_DIS
**/
  UINT8                       TcssDma0En;

/** Offset 0x0705 - TCSS DMA1 Enable
  Set TCSS DMA1. 0:Disabled  1:Enabled
  $EN_DIS
**/
  UINT8                       TcssDma1En;

/** Offset 0x0706 - Reserved
**/
  UINT8                       Reserved34[2];

/** Offset 0x0708 - Early Command Training
  Enables/Disable Early Command Training
  $EN_DIS
**/
  UINT8                       ECT;

/** Offset 0x0709 - Reserved
**/
  UINT8                       Reserved35[58];

/** Offset 0x0743 - Rank Margin Tool Per Bit
  Enable/Disable Rank Margin Tool Per Bit
  $EN_DIS
**/
  UINT8                       RMTBIT;

/** Offset 0x0744 - Reserved
**/
  UINT8                       Reserved36[6];

/** Offset 0x074A - Ch Hash Mask
  Set the BIT(s) to be included in the XOR function. NOTE BIT mask corresponds to
  BITS [19:6] Default is 0x30CC
**/
  UINT16                      ChHashMask;

/** Offset 0x074C - Reserved
**/
  UINT8                      Reserved37[66];

/** Offset 0x078E - PcdSerialDebugLevel
  Serial Debug Message Level. 0:Disable, 1:Error Only, 2:Error & Warnings, 3:Load,
  Error, Warnings & Info, 4:Load, Error, Warnings, Info & Event, 5:Load, Error, Warnings,
  Info & Verbose.
  0:Disable, 1:Error Only, 2:Error and Warnings, 3:Load Error Warnings and Info, 4:Load
  Error Warnings and Info & Event, 5:Load Error Warnings Info and Verbose
**/
  UINT8                       PcdSerialDebugLevel;

/** Offset 0x078F - Reserved
**/
  UINT8                       Reserved38[2];

/** Offset 0x0791 - Safe Mode Support
  This option configures the varous items in the IO and MC to be more conservative.(def=Disable)
  $EN_DIS
**/
  UINT8                       SafeMode;

/** Offset 0x0792 - Reserved
**/
  UINT8                       Reserved39[2];

/** Offset 0x0794 - TCSS USB Port Enable
  Bitmap for per port enabling
**/
  UINT8                       UsbTcPortEnPreMem;

/** Offset 0x0795 - Reserved
**/
  UINT8                       Reserved40[3];

/** Offset 0x0798 - RMTLoopCount
  Specifies the Loop Count to be used during Rank Margin Tool Testing. 0 - AUTO
**/
  UINT8                       RMTLoopCount;

/** Offset 0x0799 - Reserved
**/
  UINT8                       Reserved41[29];

/** Offset 0x07B6 - Command Pins Mapping
  BitMask where bits [3:0] are Controller 0 Channel [3:0] and bits [7:4] are Controller
  1 Channel [3:0]. 0 = CCC pin mapping is Ascending, 1 = CCC pin mapping is Descending.
**/
  UINT8                       Lp5CccConfig;

/** Offset 0x07B7 - Reserved
**/
  UINT8                       Reserved42[12];

/** Offset 0x07C3 - Skip external display device scanning
  Enable: Do not scan for external display device, Disable (Default): Scan external
  display devices
  $EN_DIS
**/
  UINT8                       SkipExtGfxScan;

/** Offset 0x07C4 - Reserved
**/
  UINT8                       Reserved43;

/** Offset 0x07C5 - Lock PCU Thermal Management registers
  Lock PCU Thermal Management registers. Enable(Default)=1, Disable=0
  $EN_DIS
**/
  UINT8                       LockPTMregs;

/** Offset 0x07C6 - Reserved
**/
  UINT8                       Reserved44[131];

/** Offset 0x0849 - Skip CPU replacement check
  Test, 0: disable, 1: enable, Setting this option to skip CPU replacement check
  $EN_DIS
**/
  UINT8                       SkipCpuReplacementCheck;

/** Offset 0x084A - Reserved
**/
  UINT8                       Reserved45[292];

/** Offset 0x096E - Serial Io Uart Debug Mode
  Select SerialIo Uart Controller mode
  0:SerialIoUartDisabled, 1:SerialIoUartPci, 2:SerialIoUartHidden, 3:SerialIoUartCom,
  4:SerialIoUartSkipInit
**/
  UINT8                       SerialIoUartDebugMode;

/** Offset 0x096F - Reserved
**/
  UINT8                       Reserved46[185];

/** Offset 0x0A28 - GPIO Override
  Gpio Override Level - FSP will not configure any GPIOs and rely on GPIO setings
  before moved to FSP. Available configurations 0: Disable; 1: Level 1 - Skips GPIO
  configuration in PEI/FSPM/FSPT phase;2: Level 2 - Reserved for future use
**/
  UINT8                       GpioOverride;

/** Offset 0x0A29 - Reserved
**/
  UINT8                       Reserved47[23];
} FSP_M_CONFIG;

/** Fsp M UPD Configuration
**/
typedef struct {

/** Offset 0x0000
**/
  FSP_UPD_HEADER              FspUpdHeader;

/** Offset 0x0020
**/
  FSPM_ARCH_UPD               FspmArchUpd;

/** Offset 0x0040
**/
  FSP_M_CONFIG                FspmConfig;

/** Offset 0x0A40
**/
  UINT8                       UnusedUpdSpace25[6];

/** Offset 0x0A46
**/
  UINT16                      UpdTerminator;
} FSPM_UPD;

#pragma pack()

#endif
