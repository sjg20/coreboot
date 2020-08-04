/**
Copyright (c) 2019-2020, Intel Corporation. All rights reserved.<BR>

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

**/


#ifndef _PREV_BOOT_ERR_SRC_GUID_H_
#define _PREV_BOOT_ERR_SRC_GUID_H_

#define FSP_PREV_BOOT_ERR_SRC_HOB_GUID { \
	0xc5, 0xb5, 0x38, 0x51, 0x69, 0x93, 0xec, 0x48, 0x5b, 0x97, \
	0x38, 0xa2, 0xf7, 0x09, 0x66, 0x75 \
	}

#define PREV_BOOT_ERR_SRC_HOB_SIZE  1000

typedef struct {
UINT16  Length;    // Actual size of the error sources  used in the HOB
UINT8  HobData[PREV_BOOT_ERR_SRC_HOB_SIZE -2];  // List of Error source structures of format //MCBANK_ERR_INFO  or CSR_ERR_INFO
}PREV_BOOT_ERR_SRC_HOB;

typedef struct{
UINT8  Type;    // McBankType = 1;
UINT8  Segment;
UINT8  Socket;
UINT16  ApicId;    // ApicId  is Needed only if it a core McBank.
UINT16  McBankNum;
UINT64  McBankStatus;
UINT64  McbankAddr;
UINT64  McBankMisc;
} MCBANK_ERR_INFO;

typedef struct {
UINT8  Type;    // PciExType =2 ;
UINT8  Segment;
UINT8  Bus;
UINT8  Device;
UINT8  Function;
UINT32  AerUncErrSts;
UINT8  AerHdrLogData[16];
} PCI_EX_ERR_INFO;

typedef struct {
UINT8  Type;    // Other Csr error type =3 ;
UINT8  Segment;
UINT8  Bus;
UINT8  Device;
UINT8  Function;
UINT16  offset;
UINT32  Value;
} CSR_ERR_INFO;

typedef enum {
  McBankType = 1,
  PciExType,
  CsrOtherType
} ERROR_ACCESS_TYPE;

#endif
