/*
 * This file is part of the coreboot project.
 *
 * Copyright 2018 Google LLC
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

Device (WLCO)
{
	Name (_HID, "GOOG000C")
	Name (_UID, 1)
	Name (_DDN, "Wilco EC Command Device")

	Method (_STA)
	{
		Return (0xf)
	}

	Name (_CRS, ResourceTemplate ()
	{
		IO (Decode16,
		    CONFIG_EC_BASE_HOST_DATA,
		    CONFIG_EC_BASE_HOST_DATA,
		    4, 4)
		IO (Decode16,
		    CONFIG_EC_BASE_HOST_COMMAND,
		    CONFIG_EC_BASE_HOST_COMMAND,
		    4, 4)
		IO (Decode16,
		    CONFIG_EC_BASE_PACKET,
		    CONFIG_EC_BASE_PACKET,
		    16, 16)
	})

	Name (_PRS, ResourceTemplate ()
	{
		StartDependentFn (0, 0) {
			IO (Decode16,
			    CONFIG_EC_BASE_HOST_DATA,
			    CONFIG_EC_BASE_HOST_DATA,
			    4, 4)
			IO (Decode16,
			    CONFIG_EC_BASE_HOST_COMMAND,
			    CONFIG_EC_BASE_HOST_COMMAND,
			    4, 4)
			IO (Decode16,
			    CONFIG_EC_BASE_PACKET,
			    CONFIG_EC_BASE_PACKET,
			    16, 16)
		}
		EndDependentFn ()
	})
}
