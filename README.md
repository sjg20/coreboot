coreboot README
===============

coreboot is a Free Software project aimed at replacing the proprietary BIOS
(firmware) found in most computers.  coreboot performs a little bit of
hardware initialization and then executes additional boot logic, called a
payload.

With the separation of hardware initialization and later boot logic,
coreboot can scale from specialized applications that run directly
firmware, run operating systems in flash, load custom
bootloaders, or implement firmware standards, like PC BIOS services or
UEFI. This allows for systems to only include the features necessary
in the target application, reducing the amount of code and flash space
required.

coreboot was formerly known as LinuxBIOS.


Payloads
--------

After the basic initialization of the hardware has been performed, any
desired "payload" can be started by coreboot.

See <https://www.coreboot.org/Payloads> for a list of supported payloads.


Supported Hardware
------------------

coreboot supports a wide range of chipsets, devices, and mainboards.

For details please consult:

 * <https://www.coreboot.org/Supported_Motherboards>
 * <https://www.coreboot.org/Supported_Chipsets_and_Devices>


Build Requirements
------------------

 * make
 * gcc / g++
   Because Linux distribution compilers tend to use lots of patches. coreboot
   does lots of "unusual" things in its build system, some of which break due
   to those patches, sometimes by gcc aborting, sometimes - and that's worse -
   by generating broken object code.
   Two options: use our toolchain (eg. make crosstools-i386) or enable the
   `ANY_TOOLCHAIN` Kconfig option if you're feeling lucky (no support in this
   case).
 * iasl (for targets with ACPI support)
 * pkg-config
 * libssl-dev (openssl)

Optional:

 * doxygen (for generating/viewing documentation)
 * gdb (for better debugging facilities on some targets)
 * ncurses (for `make menuconfig` and `make nconfig`)
 * flex and bison (for regenerating parsers)


Building coreboot
-----------------

Please consult <https://www.coreboot.org/Build_HOWTO> for details.


Testing coreboot Without Modifying Your Hardware
------------------------------------------------

If you want to test coreboot without any risks before you really decide
to use it on your hardware, you can use the QEMU system emulator to run
coreboot virtually in QEMU.

Please see <https://www.coreboot.org/QEMU> for details.


Website and Mailing List
------------------------

Further details on the project, a FAQ, many HOWTOs, news, development
guidelines and more can be found on the coreboot website:

  <https://www.coreboot.org>

You can contact us directly on the coreboot mailing list:

  <https://www.coreboot.org/Mailinglist>


Booting into U-Boot
-------------------

You can boot from coreboot into U-Boot from several places on Apollo Lake (APL).

cosarm/src/third_party/chromiumos-overlay$ pe
760e63c7841 (HEAD -> coral) debug bootstage
3b81dc29f18 quiet workon
3156f8f9bd6 quiet coreboot
3ac6559e567 disable new UI

# 	if use menu_ui ; then
# 		echo "CONFIG_MENU_UI=y" >> "${defconfig}"
# 	elif use legacy_menu_ui ; then
# 		echo "CONFIG_LEGACY_MENU_UI=y" >> "${defconfig}"
# 	else
# 		echo "CONFIG_LEGACY_CLAMSHELL_UI=y" >> "${defconfig}"
# 	fi

cc402e7a691 Automatic: master-release - Updating to a new version number from 13073.0.0

bootblock:

 * Note coreboot bootblock loads at ffff8000
 * (U-Boot) crosfw chromebook_coral
 * (chroot) cd ~/trunk/src/third_party/coreboot; ./build-board.sh coral
 * cp ~/cosarm/chroot/tmp/coreboot/coral/image-coral.serial.bin cb.rom && \
   cbfstool cb.rom remove -n fallback/payload && \
   cbfstool cb.rom add -t raw -f /tmp/b/chromebook_coral/spl/u-boot-spl.bin \
   -n fallback/payload && em100 -s -c w25q128fw -d cb.rom -r
 * Will be loaded at 0xfef10000
 * Check CONFIG_SPL_TEXT_BASE in U-Boot is also 0xfef10000
 * Set CONFIG_DEBUG_UART_BASE=0xddffc000
 * Call jump_to_uboot() from src/soc/intel/apollolake/bootblock/bootblock.c

romstage:

 * Note coreboot romstage loads at fef20000, stack is around 0xfef06c1c but
   gets updated by U-Boot SPL. Put both SPL and U-Boot into CBFS:
 * (U-Boot) crosfw chromebook_coral
 * (chroot) cd ~/trunk/src/third_party/coreboot; ./build-board.sh coral
 * cp ~/cosarm/chroot/tmp/coreboot/coral/image-coral.serial.bin cb.rom && \
   cbfstool cb.rom remove -n fallback/payload && \
   cbfstool cb.rom add -t raw -f /tmp/b/chromebook_coral/spl/u-boot-spl.bin \
     -n fallback/payload && \
   cbfstool cb.rom add-master-header -r RW_LEGACY && \
   cbfstool cb.rom add -t raw -f /tmp/b/chromebook_coral/u-boot.bin \
     -r RW_LEGACY -n altfw/u-boot && \
   cbfstool cb.rom extract -n vbt.bin -f vbt.bin && \
   cbfstool cb.rom remove -n vbt.bin &&
   cbfstool cb.rom add -n vbt.bin -f vbt.bin -t raw &&
   em100 -s -c w25q128fw -d cb.rom -r

 * Will be loaded at 0xfef10000
 * Check CONFIG_SPL_TEXT_BASE in U-Boot is also 0xfef10000
 * Set the stack at the start of start_from_tpl.S: mov	$0xfef10000, %esp
 * Call jump_to_uboot() from src/drivers/intel/fsp2_0/memory_init.c

Patch to reduce code size of SPL below 64KB limit. This could be increased by
changing CONFIG_SPL_TEXT_BASE
'''
diff --git a/configs/chromebook_coral_defconfig b/configs/chromebook_coral_defconfig
index aaa5e4a2925..ab664a55c63 100644
--- a/configs/chromebook_coral_defconfig
+++ b/configs/chromebook_coral_defconfig
@@ -10,6 +10,7 @@ CONFIG_DEBUG_UART_BASE=0xde000000
 CONFIG_DEBUG_UART_CLOCK=1843200
 CONFIG_VENDOR_GOOGLE=y
 CONFIG_TARGET_CHROMEBOOK_CORAL=y
+CONFIG_FSP_FROM_CBFS=y
 CONFIG_DEBUG_UART=y
 CONFIG_FSP_VERSION2=y
 CONFIG_GENERATE_PIRQ_TABLE=y
@@ -21,17 +22,14 @@ CONFIG_X86_OFFSET_SPL=0xffe80000
 CONFIG_INTEL_GENERIC_WIFI=y
 CONFIG_SPL_TEXT_BASE=0xfef10000
 CONFIG_BOOTSTAGE=y
-CONFIG_SPL_BOOTSTAGE=y
 CONFIG_TPL_BOOTSTAGE=y
 CONFIG_BOOTSTAGE_REPORT=y
-CONFIG_SPL_BOOTSTAGE_RECORD_COUNT=10
 CONFIG_BOOTSTAGE_STASH=y
 CONFIG_USE_BOOTARGS=y
 CONFIG_BOOTARGS="nr_cpus=1 console=ttyS2,115200n8 cros_legacy loglevel=9 init=/sbin/init oops=panic panic=-1 root=PARTUUID=35c775e7-3735-d745-93e5-d9e0238f7ed0/PARTNROFF=1 rootwait rw noinitrd vt.global_cursor_default=0 add_efi_memmap boot=local noresume noswap i915.modeset=1 nmi_watchdog=panic,lapic disablevmx=off"
 CONFIG_SYS_CONSOLE_INFO_QUIET=y
 CONFIG_SPL_LOG=y
 CONFIG_LOG_DEFAULT_LEVEL=4
-CONFIG_LOG_ERROR_RETURN=y
 CONFIG_DISPLAY_BOARDINFO_LATE=y
 CONFIG_LAST_STAGE_INIT=y
 CONFIG_BLOBLIST=y
@@ -105,9 +103,8 @@ CONFIG_USB_XHCI_HCD=y
 CONFIG_USB_STORAGE=y
 CONFIG_USB_KEYBOARD=y
 CONFIG_CONSOLE_SCROLL_LINES=5
+CONFIG_FS_CBFS=y
 CONFIG_SPL_FS_CBFS=y
-# CONFIG_SPL_USE_TINY_PRINTF is not set
-CONFIG_TPL_USE_TINY_PRINTF=y
 CONFIG_CMD_DHRYSTONE=y
 CONFIG_TPM=y
 # CONFIG_EFI_LOADER is not set
'''

ramstage: e.g.

 * (chroot) ./build-board.sh coral
 * Will be loaded at 0x1110000
 * Check CONFIG_SYS_TEXT_BASE in U-Boot is also 0x1110000
 * No need to touch CONFIG_DEBUG_UART_BASE as U-Boot reads coreboot sysinfo
 * cb-combine -t -s ram
 * cp ~/cosarm/chroot/tmp/coreboot/coral/image-coral.serial.bin cb.rom && \
   cbfstool cb.rom remove -r RW_LEGACY -n altfw/u-boot && \
   cbfstool cb.rom add -r RW_LEGACY -f /tmp/b/chromebook_coral/u-boot.bin \
   -n altfw/u-boot -t raw && em100 -s -c w25q128fw -d cb.rom -r

From dc, e.g.

 * cb-combine -t -s dc
 * Add call to VbExLegacy(1) in main.c before vboot_select_and_load_kernel()


'''coreboot patches
1ce84de80fd (HEAD -> coral5) docs
d655edb4f5c ram stage
499eedd7326 rom stage: jump to U-Boot just before meminit
1b8ea36fc75 bootblock
639bc5fa88b misc debug output
325405dbd19 apl: Show CAR info in platform_segment_loaded
332fd840f6e print_buffer
c41dff5defa quiet
1760119e0b0 Drop -Werror
963bcbef345 fix timezone
bdaad36a1b1 build-board.sh
efa3084d63e (us) UPSTREAM: nvidia/tegra210: Enable RETURN_FROM_VERSTAGE to free up space
'''

Copyright and License
---------------------

The copyright on coreboot is owned by quite a large number of individual
developers and companies. Please check the individual source files for details.

coreboot is licensed under the terms of the GNU General Public License (GPL).
Some files are licensed under the "GPL (version 2, or any later version)",
and some files are licensed under the "GPL, version 2". For some parts, which
were derived from other projects, other (GPL-compatible) licenses may apply.
Please check the individual source files for details.

This makes the resulting coreboot images licensed under the GPL, version 2.
