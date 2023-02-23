/* SPDX-License-Identifier: GPL-2.0-only */

#include <commonlib/ccb_api.h>
#include <console/console.h>
#include <cbmem.h>

#if ENV_HOLDS_CCB
struct ccb ccb_static __attribute__((section(".init"))) = {
	CCB_MAGIC,
	/* flags must always be zero during the build */
};
#endif

struct ccb *ccb;

struct ccb *ccb_get(void)
{
	return ccb;
}

int ccb_get_flags(void)
{
	return ccb->flags;
}

static void add_ccb_to_cbmem(int is_recovery)
{
	struct ccb *ptr;

	ccb = ccb_get();
	if (ccb) {
		ptr = cbmem_add(CBMEM_ID_CCB, sizeof(struct ccb));
		if (ptr) {
			printk(BIOS_DEBUG, "CCB: Adding to CBMEM\n");
			*ptr = *ccb;
		}
	}
}

CBMEM_READY_HOOK(add_ccb_to_cbmem);

void ccb_init(void)
{
#if ENV_HOLDS_CCB
	ccb = &ccb_static;
#else
	ccb = cbmem_find(CBMEM_ID_CCB);
#endif
	if (ccb)
		printk(BIOS_DEBUG, "CCB is ready\n");
}
