/* SPDX-License-Identifier: GPL-2.0-only */

	Name(PCBA, CONFIG_MMCONF_BASE_ADDRESS)	/* Base address of PCIe config space */
	Name(PCLN, Multiply(0x100000, CONFIG_MMCONF_BUS_NUMBER)) /* Length of PCIe config space, 1MB each bus */

	/* AcpiGpe0Blk */
	OperationRegion(GP0B, SystemMemory, 0xfed80814, 0x04)
		Field(GP0B, ByteAcc, NoLock, Preserve) {
		, 11,
		USBS, 1,
	}
