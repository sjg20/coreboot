/* This file is part of the ectool project. */
/* SPDX-License-Identifier: GPL-2.0-only */

#ifndef _EC_H
#define _EC_H

/* EC_SC input */
#define   EC_SMI_EVT	(1 << 6)	// 1: SMI event pending
#define   EC_SCI_EVT	(1 << 5)	// 1: SCI event pending
#define   EC_BURST	(1 << 4)	// controller is in burst mode
#define   EC_CMD	(1 << 3)	// 1: byte in data register is command
				 	// 0: byte in data register is data
#define   EC_IBF	(1 << 1)	// 1: input buffer full (data ready for ec)
#define   EC_OBF	(1 << 0)	// 1: output buffer full (data ready for host)

/* EC_SC output */
#define   RD_EC		0x80	// Read Embedded Controller
#define   WR_EC		0x81	// Write Embedded Controller
#define   BE_EC		0x82	// Burst Enable Embedded Controller
#define   BD_EC 	0x83	// Burst Disable Embedded Controller
#define   QR_EC 	0x84	// Query Embedded Controller
#define   RX_EC		0xf0	// Read Extended operation
#define   WX_EC		0xf1	// Write Extended operation

int send_ec_command(uint8_t command);
int send_ec_data(uint8_t data);
int send_ec_data_nowait(uint8_t data);
uint8_t recv_ec_data(void);
uint8_t ec_read(uint8_t addr);
int ec_write(uint8_t addr, uint8_t data);
uint8_t ec_ext_read(uint16_t addr);
int ec_ext_write(uint16_t addr, uint8_t data);
uint8_t ec_idx_read(uint16_t addr);
uint8_t ec_query(void);
int get_ec_ports(void);
#endif
