/* SPDX-License-Identifier: GPL-2.0-only */

#include <assert.h>
#include <cbfs.h>
#include <cbmem.h>
#include <commonlib/ccb_api.h>
#include <console/console.h>
#include <program_loading.h>
#include <string.h>
#include <symbols.h>

#if ENV_HOLDS_CCB
struct ccb ccb_static __attribute__((__section__(".init"))) = {
	CCB_MAGIC,
	/* flags must always be zero during the build */
};
#endif

const struct ccb *ccb;

const struct ccb *ccb_get(void)
{
	return ccb;
}

int ccb_get_flags(void)
{
	return ccb ? ccb->flags : 0;
}

static void add_ccb_to_cbmem(int is_recovery)
{
	struct ccb *ptr;

	ccb = ccb_get();
	if (ccb) {
		ptr = cbmem_add(CBMEM_ID_CCB, sizeof(*ccb));
		if (ptr) {
			printk(BIOS_DEBUG, "CCB: Adding to CBMEM\n");
			*ptr = *ccb;
		}
	}
}

CBMEM_READY_HOOK(add_ccb_to_cbmem);

void ccb_init(void)
{
	/* This function handles three main situations:
	 *
	 * 1. (bootblock) The CCB is in a variable. It must be copied into the
	 *    cache so it is accessible through the pre-RAM stages, just like
	 *    the timestamp cache
	 * 2. (romstage) The CCB is in the cache. It must be copied into a CBMEM
	 *    entry so it is accessible through the post-RAM stages
	 * 3. (ramstage) The CCB is in CBMEM. It can be accessed directly.
	 */
#if ENV_HOLDS_CCB
	ccb = &ccb_static;
	if (REGION_SIZE(ccb) < sizeof(*ccb)) {
		BUG();
	} else {
		/* Copy the CCB into the cache for use by romstage. */
		memcpy((void *)_ccb, ccb, sizeof(*ccb));
	}
#else
	if (CONFIG(CCB_CBFS)) {
		struct prog ccb_file = PROG_INIT(PROG_CCB, "ccb");
		struct region_device rdev;
		union cbfs_mdata mdata;

		if (_cbfs_boot_lookup(prog_name(&ccb_file), true, &mdata, &rdev))
			return;
		if (region_device_sz(&rdev) != sizeof(struct ccb)) {
			printk(BIOS_ERR, "CCB: Incorect file size in CBFS\n");
			return;
		}
		ccb = rdev_mmap_full(&rdev);
		return;
	}

	if (ENV_CREATES_CBMEM) {
		if (!ENV_ROMSTAGE_OR_BEFORE)
			return;

		/* Point to the cached CCB. This will be added to CBMEM. */
		ccb = (void *)_ccb;
	} else {
		ccb = cbmem_find(CBMEM_ID_CCB);
	}
#endif
}
