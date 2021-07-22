/* SPDX-License-Identifier: GPL-2.0-only */

#include <tests/lib/cbfs_util.h>

TEST_REGION(cbfs_cache, TEST_CBFS_CACHE_SIZE);

const u8 test_data_1[TEST_DATA_1_SIZE] = { TEST_DATA_1 };
const u8 test_data_2[TEST_DATA_2_SIZE] = { TEST_DATA_2 };
const u8 test_data_int_1[TEST_DATA_INT_1_SIZE] = { BE64(TEST_DATA_INT_1) };
const u8 test_data_int_2[TEST_DATA_INT_2_SIZE] = { BE64(TEST_DATA_INT_2) };
const u8 test_data_int_3[TEST_DATA_INT_3_SIZE] = { BE64(TEST_DATA_INT_3) };

const u8 good_hash[VB2_SHA256_DIGEST_SIZE] = { TEST_SHA256 };
const u8 bad_hash[VB2_SHA256_DIGEST_SIZE] = { INVALID_SHA256 };

const struct cbfs_test_file file_no_hash = {
	.header = HEADER_INITIALIZER(CBFS_TYPE_RAW, 0, TEST_DATA_1_SIZE),
	.filename = TEST_DATA_1_FILENAME,
	.attrs_and_data = {
		TEST_DATA_1,
	},
};

const struct cbfs_test_file file_valid_hash = {
	.header = HEADER_INITIALIZER(CBFS_TYPE_RAW, HASH_ATTR_SIZE, TEST_DATA_1_SIZE),
	.filename = TEST_DATA_1_FILENAME,
	.attrs_and_data = {
		BE32(CBFS_FILE_ATTR_TAG_HASH),
		BE32(HASH_ATTR_SIZE),
		BE32(VB2_HASH_SHA256),
		TEST_SHA256,
		TEST_DATA_1,
	},
};

const struct cbfs_test_file file_broken_hash = {
	.header = HEADER_INITIALIZER(CBFS_TYPE_RAW, HASH_ATTR_SIZE, TEST_DATA_1_SIZE),
	.filename = TEST_DATA_1_FILENAME,
	.attrs_and_data = {
		BE32(CBFS_FILE_ATTR_TAG_HASH),
		BE32(HASH_ATTR_SIZE),
		BE32(VB2_HASH_SHA256),
		INVALID_SHA256,
		TEST_DATA_1,
	},
};
