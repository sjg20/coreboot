/** @file

Copyright (c) 2020, Intel Corporation. All rights reserved.<BR>

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

#ifndef __FIRMWARE_VERSION_INFO_H__
#define __FIRMWARE_VERSION_INFO_H__

#include <IndustryStandard/SmBios.h>

#define INTEL_FIRMWARE_VERSION_INFO_GROUP_NAME    "Firmware Version Info"

#pragma pack(1)

///
/// Firmware Version Structure
///
typedef struct {
  UINT8                       MajorVersion;
  UINT8                       MinorVersion;
  UINT8                       Revision;
  UINT16                      BuildNumber;
} INTEL_FIRMWARE_VERSION;

///
/// Firmware Version Info (FVI) Structure
///
typedef struct {
  SMBIOS_TABLE_STRING         ComponentName;  ///< String Index of Component Name
  SMBIOS_TABLE_STRING         VersionString;  ///< String Index of Version String
  INTEL_FIRMWARE_VERSION      Version;        ///< Firmware version
} INTEL_FIRMWARE_VERSION_INFO;

///
/// SMBIOS OEM Type Intel Firmware Version Info (FVI) Structure
///
typedef struct {
  SMBIOS_STRUCTURE            Header;         ///< SMBIOS structure header
  UINT8                       Count;          ///< Number of FVI entries in this structure
  INTEL_FIRMWARE_VERSION_INFO Fvi[1];         ///< FVI structure(s)
} SMBIOS_TABLE_TYPE_OEM_INTEL_FVI;

#pragma pack()

#endif
