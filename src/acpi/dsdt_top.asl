/* SPDX-License-Identifier: GPL-2.0-only */

#include <acpi/acpigen_extern.asl>

#if CONFIG(CHROMEOS)
/* Chrome OS specific */
#include <vendorcode/google/chromeos/acpi/gnvs.asl>
#include <vendorcode/google/chromeos/acpi/chromeos.asl>
#endif

/* Operating system enumeration. */
Name (OSYS, 0)

/* Zero => PIC mode, One => APIC Mode */
Name (PICM, Zero)

/* Power state (AC = 1) */
Name (PWRS, One)
