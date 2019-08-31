/*
 * This file is part of the coreboot project.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

/*
 * Processor Object
 *
 */
Scope (\_PR) {		/* define processor scope */
	Processor(
		P000,		/* name space name */
		0,			/* Unique number for this processor */
		0x810,		/* PBLK system I/O address !hardcoded! */
		0x06		/* PBLKLEN for boot processor */
		) {
	}

	Processor(
		P001,		/* name space name */
		1,			/* Unique number for this processor */
		0x0810,		/* PBLK system I/O address !hardcoded! */
		0x06		/* PBLKLEN for boot processor */
		) {
	}
	Processor(
		P002,		/* name space name */
		2,			/* Unique number for this processor */
		0x0810,		/* PBLK system I/O address !hardcoded! */
		0x06		/* PBLKLEN for boot processor */
		) {
	}
	Processor(
		P003,		/* name space name */
		3,			/* Unique number for this processor */
		0x0810,		/* PBLK system I/O address !hardcoded! */
		0x06		/* PBLKLEN for boot processor */
		) {
	}
	Processor(
		P004,		/* name space name */
		4,			/* Unique number for this processor */
		0x0810,		/* PBLK system I/O address !hardcoded! */
		0x06		/* PBLKLEN for boot processor */
		) {
	}
	Processor(
		P005,		/* name space name */
		5,			/* Unique number for this processor */
		0x0810,		/* PBLK system I/O address !hardcoded! */
		0x06		/* PBLKLEN for boot processor */
		) {
	}
	Processor(
		P006,		/* name space name */
		6,			/* Unique number for this processor */
		0x0810,		/* PBLK system I/O address !hardcoded! */
		0x06		/* PBLKLEN for boot processor */
		) {
	}
	Processor(
		P007,		/* name space name */
		7,			/* Unique number for this processor */
		0x0810,		/* PBLK system I/O address !hardcoded! */
		0x06		/* PBLKLEN for boot processor */
		) {
	}
} /* End _PR scope */
