/* SPDX-License-Identifier: BSD-3-Clause OR GPL-2.0-only */

#ifndef _CBFS_SERIALIZED_H_
#define _CBFS_SERIALIZED_H_

#include <stdint.h>
#include <vb2_sha.h>

/** These are standard values for the known compression
    algorithms that coreboot knows about for stages and
    payloads.  Of course, other CBFS users can use whatever
    values they want, as long as they understand them. */

#define CBFS_COMPRESS_NONE  0
#define CBFS_COMPRESS_LZMA  1
#define CBFS_COMPRESS_LZ4   2

/** These are standard component types for well known
    components (i.e - those that coreboot needs to consume.
    Users are welcome to use any other value for their
    components */

#define CBFS_TYPE_DELETED    0x00000000
#define CBFS_TYPE_DELETED2   0xffffffff
#define CBFS_TYPE_BOOTBLOCK  0x01
#define CBFS_TYPE_STAGE      0x10
#define CBFS_TYPE_SELF       0x20
#define CBFS_TYPE_FIT        0x21
#define CBFS_TYPE_OPTIONROM  0x30
#define CBFS_TYPE_BOOTSPLASH 0x40
#define CBFS_TYPE_RAW        0x50
#define CBFS_TYPE_VSA        0x51
#define CBFS_TYPE_MBI        0x52
#define CBFS_TYPE_MICROCODE  0x53
#define CBFS_TYPE_FSP        0x60
#define CBFS_TYPE_MRC        0x61
#define CBFS_TYPE_MMA        0x62
#define CBFS_TYPE_EFI        0x63
#define CBFS_TYPE_STRUCT     0x70
#define CBFS_COMPONENT_CMOS_DEFAULT 0xaa
#define CBFS_TYPE_SPD          0xab
#define CBFS_TYPE_MRC_CACHE    0xac
#define CBFS_COMPONENT_CMOS_LAYOUT 0x01aa

#define CBFS_HEADER_MAGIC  0x4F524243
#define CBFS_HEADER_VERSION1 0x31313131
#define CBFS_HEADER_VERSION2 0x31313132
#define CBFS_HEADER_VERSION  CBFS_HEADER_VERSION2

/* this is the master cbfs header - it must be located somewhere available
 * to bootblock (to load romstage). The last 4 bytes in the image contain its
 * relative offset from the end of the image (as a 32-bit signed integer). */

struct cbfs_header {
	uint32_t magic;
	uint32_t version;
	uint32_t romsize;
	uint32_t bootblocksize;
	uint32_t align; /* fixed to 64 bytes */
	uint32_t offset;
	uint32_t architecture;
	uint32_t pad[1];
} __packed;

/* this used to be flexible, but wasn't ever set to something different. */
#define CBFS_ALIGNMENT 64

/* "Unknown" refers to CBFS headers version 1,
 * before the architecture was defined (i.e., x86 only).
 */
#define CBFS_ARCHITECTURE_UNKNOWN  0xFFFFFFFF
#define CBFS_ARCHITECTURE_X86      0x00000001
#define CBFS_ARCHITECTURE_ARM      0x00000010

/** This is a component header - every entry in the CBFS
    will have this header.

    This is how the component is arranged in the ROM:

    --------------   <- 0
    component header
    --------------   <- sizeof(struct component)
    component name
    --------------   <- offset
    data
    ...
    --------------   <- offset + len
*/

#define CBFS_FILE_MAGIC "LARCHIVE"

struct cbfs_file {
	char magic[8];
	uint32_t len;
	uint32_t type;
	uint32_t attributes_offset;
	uint32_t offset;
} __packed;

/* The common fields of extended cbfs file attributes.
   Attributes are expected to start with tag/len, then append their
   specific fields. */
struct cbfs_file_attribute {
	uint32_t tag;
	/* len covers the whole structure, incl. tag and len */
	uint32_t len;
	uint8_t data[0];
} __packed;

/* Depending on how the header was initialized, it may be backed with 0x00 or
 * 0xff. Support both. */
#define CBFS_FILE_ATTR_TAG_UNUSED 0
#define CBFS_FILE_ATTR_TAG_UNUSED2 0xffffffff
#define CBFS_FILE_ATTR_TAG_COMPRESSION 0x42435a4c
#define CBFS_FILE_ATTR_TAG_HASH 0x68736148
#define CBFS_FILE_ATTR_TAG_POSITION 0x42435350  /* PSCB */
#define CBFS_FILE_ATTR_TAG_ALIGNMENT 0x42434c41 /* ALCB */
#define CBFS_FILE_ATTR_TAG_IBB 0x32494242 /* Initial BootBlock */

struct cbfs_file_attr_compression {
	uint32_t tag;
	uint32_t len;
	/* whole file compression format. 0 if no compression. */
	uint32_t compression;
	uint32_t decompressed_size;
} __packed;

/* Actual size in CBFS may be larger/smaller than struct size! */
struct cbfs_file_attr_hash {
	uint32_t tag;
	uint32_t len;
	struct vb2_hash hash;
} __packed;

struct cbfs_file_attr_position {
	uint32_t tag;
	uint32_t len;
	uint32_t position;
} __packed;

struct cbfs_file_attr_align {
	uint32_t tag;
	uint32_t len;
	uint32_t alignment;
} __packed;

/*** Component sub-headers ***/

/* Following are component sub-headers for the "standard"
   component types */

/** This is the sub-header for stage components.  Stages are
    loaded by coreboot during the normal boot process */

struct cbfs_stage {
	uint32_t compression;  /** Compression type */
	uint64_t entry;  /** entry point */
	uint64_t load;   /** Where to load in memory */
	uint32_t len;          /** length of data to load */
	uint32_t memlen;	   /** total length of object in memory */
} __packed;

/** this is the sub-header for payload components.  Payloads
    are loaded by coreboot at the end of the boot process */

struct cbfs_payload_segment {
	uint32_t type;
	uint32_t compression;
	uint32_t offset;
	uint64_t load_addr;
	uint32_t len;
	uint32_t mem_len;
} __packed;

struct cbfs_payload {
	struct cbfs_payload_segment segments;
};

#define PAYLOAD_SEGMENT_CODE   0x434F4445
#define PAYLOAD_SEGMENT_DATA   0x44415441
#define PAYLOAD_SEGMENT_BSS    0x42535320
#define PAYLOAD_SEGMENT_PARAMS 0x50415241
#define PAYLOAD_SEGMENT_ENTRY  0x454E5452

struct cbfs_optionrom {
	uint32_t compression;
	uint32_t len;
} __packed;

#endif /* _CBFS_SERIALIZED_H_ */
