## SPDX-License-Identifier: GPL-2.0-or-later

bootblock-y += bootblock.c

romstage-y += romstage.c
romstage-$(CONFIG_IPMI_KCS_ROMSTAGE) += ipmi.c

ramstage-y += ramstage.c ipmi.c
ramstage-$(CONFIG_HAVE_ACPI_TABLES) += fadt.c
all-y += console.c
smm-y += console.c
CPPFLAGS_common += -I$(src)/mainboard/$(MAINBOARDDIR)/include
