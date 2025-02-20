# SPDX-License-Identifier: GPL-2.0-only

bootblock-y += bootblock.c
bootblock-y += early_gpio.c
bootblock-y += ec.c

romstage-y += port_descriptors.c

ramstage-y += chromeos.c
ramstage-y += gpio.c
ramstage-y += port_descriptors.c

ifneq ($(wildcard $(MAINBOARD_BLOBS_DIR)/APCB_Updatable.bin),)
APCB_SOURCES = $(MAINBOARD_BLOBS_DIR)/APCB_Updatable.bin
APCB_SOURCES_RECOVERY = $(MAINBOARD_BLOBS_DIR)/APCB_DefaultRecovery.bin
else
files_added:: warn_no_apcb
endif

PHONY+=warn_no_apcb
warn_no_apcb:
	printf "\n\t** WARNING **\n"
	printf "coreboot has been built without an APCB.\n"
	printf "This image will not boot.\n\n"

ifeq ($(CONFIG_BIRMAN_HAVE_MCHP_FW),y)
$(call add_intermediate, add_mchp_fw)
	$(CBFSTOOL) $(obj)/coreboot.pre write -r EC -f $(CONFIG_BIRMAN_MCHP_SIG_FILE) --fill-upward

# calculate the absolute position from the config offset
BIRMAN_EC_POSITION=$(call int-add, \
	$(call int-subtract, 0xffffffff \
	$(CONFIG_ROM_SIZE)) $(CONFIG_BIRMAN_MCHP_FW_OFFSET) 1)

cbfs-files-y += apu/ecfw
apu/ecfw-file := $(CONFIG_BIRMAN_MCHP_FW_FILE)
apu/ecfw-position := $(BIRMAN_EC_POSITION)
apu/ecfw-type := raw

else
files_added:: warn_no_mchp
endif # CONFIG_BIRMAN_HAVE_MCHP_FW

PHONY+=warn_no_mchp
warn_no_mchp:
	printf "\n\t** WARNING **\n"
	printf "coreboot has been built without the EC FW.\n"
	printf "Do not flash this image.  Your Birman's power button\n"
	printf "will not respond when you press it.\n\n"
