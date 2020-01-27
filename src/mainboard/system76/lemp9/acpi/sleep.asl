/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2019 System76
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

/* Method called from _PTS prior to enter sleep state */
Method (MPTS, 1) {
	\_SB.PCI0.LPCB.EC0.PTS (Arg0)
}

/* Method called from _WAK prior to wakeup */
Method (MWAK, 1) {
	\_SB.PCI0.LPCB.EC0.WAK (Arg0)
}
