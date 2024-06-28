/* SPDX-License-Identifier: GPL-2.0-only */

#include <assert.h>
#include <cbfs.h>
#include <cbmem.h>
#include <commonlib/ccb_api.h>
#include <console/console.h>
#include <fmap.h>
#include <program_loading.h>
#include <string.h>
#include <symbols.h>

#if ENV_HOLDS_CCB
struct ccb ccb_static __attribute__((__section__(".init"))) = {
	CCB_MAGIC,
	/* flags must always be zero during the build */
};
#endif

_Static_assert(sizeof(struct ccb) <= CCB_SIZE, \
	       "CCB_SIZE must be no smaller than sizeof(struct ccb must)");

static struct ccb ccb_holder;
static const struct ccb *ccb_glob;

const struct ccb *ccb_get(void)
{
	return ccb_glob;
}

int ccb_get_flags(void)
{
	return ccb_glob ? ccb_glob->flags : 0;
}

static void add_ccb_to_cbmem(int is_recovery)
{
	const struct ccb *ccb;
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

static struct ccb *locate_ccb(struct region_device *rdev)
{
	struct ccb *ccb;

	/* This function handles three main situations:
	 *
	 * 1. (bootblock) The CCB is in a variable. It must be copied into the
	 *    cache so it is accessible through the pre-RAM stages, just like
	 *    the timestamp cache
	 * 2. (romstage) The CCB is in the cache. It must be copied into a CBMEM
	 *    entry so it is accessible through the post-RAM stages
	 * 3. (ramstage) The CCB is in CBMEM. It can be accessed directly.
	 */
	memset(rdev, '\0', sizeof(*rdev));
#if ENV_HOLDS_CCB
	ccb = &ccb_static;
	if (REGION_SIZE(ccb) < sizeof(*ccb)) {
		BUG();
		return NULL;
	}
#else
	if (CONFIG(CCB_CBFS)) {
		struct prog ccb_file = PROG_INIT(PROG_CCB, "ccb");
		union cbfs_mdata mdata;

		if (_cbfs_boot_lookup(prog_name(&ccb_file), true, &mdata, rdev)) {
			printk(BIOS_WARNING, "CCB: No file in CBFS\n");
			return NULL;
		}
		if (region_device_sz(rdev) != sizeof(struct ccb)) {
			printk(BIOS_ERR, "CCB: Incorrect file size in CBFS\n");
			return NULL;
		}
		ccb = rdev_mmap_full(rdev);
		return ccb;
	}

	if (CONFIG(CCB_FMAP)) {
		if (fmap_locate_area_as_rdev(CCB_REGION, rdev)) {
			printk(BIOS_ERR, "CCB: Not found in FMAP\n");
			return NULL;
		}
		ccb = rdev_mmap_full(rdev);
		if (!ccb) {
			printk(BIOS_ERR, "CCB: Cannot map\n");
			return NULL;
		}
		printk(BIOS_ERR, "CCB: Found in FMAP\n");
		return ccb;
	}

	if (ENV_CREATES_CBMEM) {
		if (!ENV_ROMSTAGE_OR_BEFORE)
			return NULL;

		/* Point to the cached CCB. This will be added to CBMEM. */
		ccb = (void *)_ccb;
	} else if (ENV_HAS_CBMEM) {
		ccb = cbmem_find(CBMEM_ID_CCB);
		if (!ccb)
			printk(BIOS_ERR, "CCB: Not found in CBMEM\n");
	}
#endif

	return ccb;
}

void ccb_check(void)
{
	struct region_device rdev;
	struct ccb *ccb;

	ccb = locate_ccb(&rdev);
	if (ccb) {
		printk(BIOS_INFO, "CCB: ready\n");
		printk(BIOS_INFO, "magic %x, flags %x\n", ccb->magic, ccb->flags);
		if (rdev_valid(&rdev))
			rdev_munmap(&rdev, ccb);
	}
}

void ccb_init(void)
{
	struct region_device rdev;
	struct ccb *ccb;

	ccb = locate_ccb(&rdev);

	if (ccb) {
#if ENV_HOLDS_CCB
		/* Copy the CCB into the cache for use by romstage. */
		memcpy((void *)_ccb, ccb, sizeof(*ccb));
#endif

		if (rdev_valid(&rdev)) {
			ccb_holder = *ccb;
			ccb = &ccb_holder;
			rdev_munmap(&rdev, ccb);
		}
		printk(BIOS_INFO, "ccb flags %x\n", ccb->flags);
		ccb_glob = ccb;
	}
}
