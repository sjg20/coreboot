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

#ifndef __FSPMUPD_HELPER_H__
#define __FSPMUPD_HELPER_H__

#include <FspUpd.h>

#define SPEED_REC_96GT      0
#define SPEED_REC_104GT     1
#define ADAPTIVE_CTLE 	    0x3f

#define CPXSP_2S6KTI_EPARAM_TABLE \
        /* Socket 0  */                                                                                       \
        {0x0, (1 << SPEED_REC_96GT) | (1 << SPEED_REC_104GT), (1 << KTI_LINK0), 0x2C33383F, ADAPTIVE_CTLE},   \
        {0x0, (1 << SPEED_REC_96GT) | (1 << SPEED_REC_104GT), (1 << KTI_LINK1), 0x2B35353F, ADAPTIVE_CTLE},   \
        {0x0, (1 << SPEED_REC_96GT) | (1 << SPEED_REC_104GT), (1 << KTI_LINK2), 0x2D37353F, ADAPTIVE_CTLE},   \
        {0x0, (1 << SPEED_REC_96GT) | (1 << SPEED_REC_104GT), (1 << KTI_LINK3), 0x2D37353F, ADAPTIVE_CTLE},   \
        {0x0, (1 << SPEED_REC_96GT) | (1 << SPEED_REC_104GT), (1 << KTI_LINK4), 0x2D37353F, ADAPTIVE_CTLE},   \
        {0x0, (1 << SPEED_REC_96GT) | (1 << SPEED_REC_104GT), (1 << KTI_LINK5), 0x2C35363F, ADAPTIVE_CTLE},   \
        /* Socket 1 */                                                                                        \
        {0x1, (1 << SPEED_REC_96GT) | (1 << SPEED_REC_104GT), (1 << KTI_LINK0), 0x2C33383F, ADAPTIVE_CTLE},   \
        {0x1, (1 << SPEED_REC_96GT) | (1 << SPEED_REC_104GT), (1 << KTI_LINK1), 0x2B35353F, ADAPTIVE_CTLE},   \
        {0x1, (1 << SPEED_REC_96GT) | (1 << SPEED_REC_104GT), (1 << KTI_LINK2), 0x2D35373F, ADAPTIVE_CTLE},   \
        {0x1, (1 << SPEED_REC_96GT) | (1 << SPEED_REC_104GT), (1 << KTI_LINK3), 0x2D35373F, ADAPTIVE_CTLE},   \
        {0x1, (1 << SPEED_REC_96GT) | (1 << SPEED_REC_104GT), (1 << KTI_LINK4), 0x2A2F3A3F, ADAPTIVE_CTLE},   \
        {0x1, (1 << SPEED_REC_96GT) | (1 << SPEED_REC_104GT), (1 << KTI_LINK5), 0x2C35363F, ADAPTIVE_CTLE}

#define CPXSP_2S6KTI_EPARAM_TABLE_COUNT 12 // NOTE - needs to match number of elements in CPXSP_2S6KTI_EPARAM_TABLE


#pragma pack(1)

typedef struct {
	UINT8  SocketID;
	UINT8  Freq;
	UINT32 Link;
	UINT32 AllLanesTXEQ;
	UINT8  CTLEPEAK;
} ALL_LANES_EPARAM_LINK_INFO;

typedef enum {
	KTI_LINK0 =  0x0,
	KTI_LINK1,
	KTI_LINK2,
	KTI_LINK3,
	KTI_LINK4,
	KTI_LINK5
} KTI_LOGIC_LINK;

#define IIO_BIFURCATE_xxxxxxxx          0xFE
#define IIO_BIFURCATE_x4x4x4x4          0x0
#define IIO_BIFURCATE_x4x4xxx8          0x1
#define IIO_BIFURCATE_xxx8x4x4          0x2
#define IIO_BIFURCATE_xxx8xxx8          0x3
#define IIO_BIFURCATE_xxxxxx16          0x4
#define IIO_BIFURCATE_x2x2x4x8          0x5
#define IIO_BIFURCATE_x4x2x2x8          0x6
#define IIO_BIFURCATE_x8x2x2x4          0x7
#define IIO_BIFURCATE_x8x4x2x2          0x8
#define IIO_BIFURCATE_x2x2x4x4x4        0x9
#define IIO_BIFURCATE_x4x2x2x4x4        0xA
#define IIO_BIFURCATE_x4x4x2x2x4        0xB
#define IIO_BIFURCATE_x4x4x4x2x2        0xC
#define IIO_BIFURCATE_x2x2x2x2x8        0xD
#define IIO_BIFURCATE_x8x2x2x2x2        0xE
#define IIO_BIFURCATE_x2x2x2x2x4x4      0xF
#define IIO_BIFURCATE_x2x2x4x2x2x4      0x10
#define IIO_BIFURCATE_x2x2x4x4x2x2      0x11
#define IIO_BIFURCATE_x4x2x2x2x2x4      0x12
#define IIO_BIFURCATE_x4x2x2x4x2x2      0x13
#define IIO_BIFURCATE_x4x4x2x2x2x2      0x14
#define IIO_BIFURCATE_x2x2x2x2x2x2x4    0x15
#define IIO_BIFURCATE_x2x2x2x2x4x2x2    0x16
#define IIO_BIFURCATE_x2x2x4x2x2x2x2    0x17
#define IIO_BIFURCATE_x4x2x2x2x2x2x2    0x18
#define IIO_BIFURCATE_x2x2x2x2x2x2x2x2  0x19
#define IIO_BIFURCATE_AUTO              0xFF

typedef struct {
	UINT8 Socket;
	UINT8 IouNumber;
	UINT8 Bifurcation;
} UPD_IIO_BIFURCATION_DATA_ENTRY;

typedef enum {
        Iio_Socket0 = 0,
        Iio_Socket1,
        Iio_Socket2,
        Iio_Socket3,
        Iio_Socket4,
        Iio_Socket5,
        Iio_Socket6,
        Iio_Socket7
} IIO_SOCKETS;

typedef enum {
        Iio_Iou0 = 0,
        Iio_Iou1,
        Iio_Iou2,
        Iio_Iou3,
        Iio_Mcp0,
        Iio_Mcp1,
        Iio_IouMax
} IIO_IOUS;

#pragma pack()

#endif
