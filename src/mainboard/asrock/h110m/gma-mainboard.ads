--
-- This file is part of the coreboot project.
--
-- Copyright (C) 2018 Tristan Corrick <tristan@corrick.kiwi>
-- Copyright (C) 2019 Maxim Polyakov <max.senia.poliak@gmail.com>
--
-- This program is free software: you can redistribute it and/or modify
-- it under the terms of the GNU General Public License as published by
-- the Free Software Foundation, either version 2 of the License, or
-- (at your option) any later version.
--
-- This program is distributed in the hope that it will be useful,
-- but WITHOUT ANY WARRANTY; without even the implied warranty of
-- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
-- GNU General Public License for more details.
--

with HW.GFX.GMA;
with HW.GFX.GMA.Display_Probing;

use HW.GFX.GMA;
use HW.GFX.GMA.Display_Probing;

private package GMA.Mainboard is

	ports : constant Port_List :=
		(HDMI1, -- mainboard DVI port
		 HDMI3, -- mainboard HDMI port
		 Analog,
		 others => Disabled);

end GMA.Mainboard;
