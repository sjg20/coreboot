/* SPDX-License-Identifier: GPL-2.0-only */

#ifndef SOC_MEDIATEK_COMMON_DEVAPC_H
#define SOC_MEDIATEK_COMMON_DEVAPC_H

#define DAPC_PERM_ATTR_4(DEV_NAME, PERM_ATTR0, PERM_ATTR1, \
			 PERM_ATTR2, PERM_ATTR3) \
	(unsigned char)PERM_ATTR0, (unsigned char)PERM_ATTR1, \
	(unsigned char)PERM_ATTR2, (unsigned char)PERM_ATTR3,

#define DAPC_PERM_ATTR_8(DEV_NAME, PERM_ATTR0, PERM_ATTR1, \
			 PERM_ATTR2, PERM_ATTR3, PERM_ATTR4, PERM_ATTR5, \
			 PERM_ATTR6, PERM_ATTR7) \
	DAPC_PERM_ATTR_4(DEV_NAME, PERM_ATTR0, PERM_ATTR1, \
			 PERM_ATTR2, PERM_ATTR3) \
	DAPC_PERM_ATTR_4(DEV_NAME, PERM_ATTR4, PERM_ATTR5, \
			 PERM_ATTR6, PERM_ATTR7)

#define DAPC_PERM_ATTR_16(DEV_NAME, PERM_ATTR0, PERM_ATTR1, \
			  PERM_ATTR2, PERM_ATTR3, PERM_ATTR4, PERM_ATTR5, \
			  PERM_ATTR6, PERM_ATTR7, PERM_ATTR8, PERM_ATTR9, \
			  PERM_ATTR10, PERM_ATTR11, PERM_ATTR12, PERM_ATTR13, \
			  PERM_ATTR14, PERM_ATTR15) \
	DAPC_PERM_ATTR_8(DEV_NAME, PERM_ATTR0, PERM_ATTR1, \
			 PERM_ATTR2, PERM_ATTR3, \
			 PERM_ATTR4, PERM_ATTR5, \
			 PERM_ATTR6, PERM_ATTR7) \
	DAPC_PERM_ATTR_8(DEV_NAME, PERM_ATTR8, PERM_ATTR9, \
			 PERM_ATTR10, PERM_ATTR11, \
			 PERM_ATTR12, PERM_ATTR13, \
			 PERM_ATTR14, PERM_ATTR15)

#define FORBIDDEN2 FORBIDDEN, FORBIDDEN
#define FORBIDDEN3 FORBIDDEN2, FORBIDDEN
#define FORBIDDEN4 FORBIDDEN3, FORBIDDEN
#define FORBIDDEN5 FORBIDDEN4, FORBIDDEN
#define FORBIDDEN6 FORBIDDEN5, FORBIDDEN
#define FORBIDDEN7 FORBIDDEN6, FORBIDDEN
#define FORBIDDEN9 FORBIDDEN7, FORBIDDEN2
#define FORBIDDEN10 FORBIDDEN3, FORBIDDEN7
#define FORBIDDEN11 FORBIDDEN10, FORBIDDEN
#define FORBIDDEN12 FORBIDDEN11, FORBIDDEN
#define FORBIDDEN13 FORBIDDEN12, FORBIDDEN
#define FORBIDDEN14 FORBIDDEN13, FORBIDDEN
#define FORBIDDEN15 FORBIDDEN14, FORBIDDEN

#define NO_PROTECTION2 NO_PROTECTION, NO_PROTECTION
#define NO_PROTECTION3 NO_PROTECTION2, NO_PROTECTION
#define NO_PROTECTION4 NO_PROTECTION3, NO_PROTECTION

enum trans_type {
	NON_SECURE_TRANS = 0,
	SECURE_TRANS,
};

enum devapc_perm_type {
	NO_PROTECTION = 0,
	SEC_RW_ONLY,
	SEC_RW_NS_R,
	FORBIDDEN,
	PERM_NUM,
};

enum domain_id {
	DOMAIN_0 = 0,
	DOMAIN_1,
	DOMAIN_2,
	DOMAIN_3,
	DOMAIN_4,
	DOMAIN_5,
	DOMAIN_6,
	DOMAIN_7,
	DOMAIN_8,
	DOMAIN_9,
	DOMAIN_10,
	DOMAIN_11,
	DOMAIN_12,
	DOMAIN_13,
	DOMAIN_14,
	DOMAIN_15,
};

struct devapc_init_ops {
	uintptr_t base;
	void (*init)(uintptr_t base);
	void (*dump)(uintptr_t base);
};

extern const struct devapc_init_ops devapc_init[];
extern const size_t devapc_init_cnt;

void *getreg_domain(uintptr_t base, unsigned int offset,
		    enum domain_id domain_id, unsigned int index);
void *getreg(uintptr_t base, unsigned int offset);
void set_module_apc(uintptr_t base, uint32_t module, enum domain_id domain_id,
		    enum devapc_perm_type perm);
void dapc_init(void);

#endif
