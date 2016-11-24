#include <check.h>
#include <stdlib.h>
#include <assert.h>
#include "bitbuffer.h"

bitbuffer bb;
uint32_t buf[10];

static void testSetup () {
	srandom (0xbd3eb2e8);
	bitbufferInit (&bb, buf, sizeof (buf)*8);
}

START_TEST (testBitbufferInit) {
	ck_assert_ptr_eq (bitbufferGet (&bb), buf);
	ck_assert_uint_eq (bitbufferLength (&bb), 0);
} END_TEST

START_TEST (testBitbufferPushOneA) {
	bitbufferPush32 (&bb, 0x1, 1);
	ck_assert_uint_eq (buf[0], 0x1);
	ck_assert_uint_eq (bitbufferLength (&bb), 1);
} END_TEST

START_TEST (testBitbufferPushOneB) {
	bitbufferPush32 (&bb, 0x2, 2);
	ck_assert_uint_eq (buf[0], 0x2);
	ck_assert_uint_eq (bitbufferLength (&bb), 2);
} END_TEST

START_TEST (testBitbufferPushOneC) {
	bitbufferPush32 (&bb, 0x0, 32);
	ck_assert_uint_eq (buf[0], 0x0);
	ck_assert_uint_eq (bitbufferLength (&bb), 32);
} END_TEST

START_TEST (testBitbufferPushOneD) {
	uint32_t expect = random ();
	bitbufferPush32 (&bb, expect, 32);
	ck_assert_uint_eq (buf[0], expect);
	ck_assert_uint_eq (bitbufferLength (&bb), 32);
} END_TEST

START_TEST (testBitbufferPushOneTrailing) {
	bitbufferPush32 (&bb, 0xffffffff, 1);
	ck_assert_uint_eq (buf[0], 0x1);
	ck_assert_uint_eq (bitbufferLength (&bb), 1);
} END_TEST

START_TEST (testBitbufferPushTwo) {
	bitbufferPush32 (&bb, 0x1, 1);
	bitbufferPush32 (&bb, 0x1, 1);
	ck_assert_uint_eq (buf[0], 0x3);
	ck_assert_uint_eq (bitbufferLength (&bb), 2);
} END_TEST

START_TEST (testBitbufferPushBoundaryA) {
	bitbufferPush32 (&bb, 0xaaaaaaaa, 31);
	bitbufferPush32 (&bb, 0x1, 1);
	ck_assert_uint_eq (buf[0], (1<<31)|0xaaaaaaaa);
	ck_assert_uint_eq (bitbufferLength (&bb), 32);
} END_TEST

START_TEST (testBitbufferPushBoundaryB) {
	bitbufferPush32 (&bb, 0xaaaaaaaa, 32);
	bitbufferPush32 (&bb, 0xffffffff, 1);
	ck_assert_uint_eq (buf[0], 0xaaaaaaaa);
	ck_assert_uint_eq (buf[1], 0x1);
	ck_assert_uint_eq (bitbufferLength (&bb), 33);
} END_TEST

START_TEST (testBitbufferPushBoundaryC) {
	bitbufferPush32 (&bb, 0xaaaaaaaa, 31);
	bitbufferPush32 (&bb, 0xffffffff, 2);
	ck_assert_uint_eq (buf[0], (1<<31)|0xaaaaaaaa);
	ck_assert_uint_eq (buf[1], 0x1);
	ck_assert_uint_eq (bitbufferLength (&bb), 33);
} END_TEST

START_TEST (testBitbufferPushRandom) {
	for (unsigned int count = 0; count < 10000; count++) {
		uint32_t expect[10];
		for (unsigned int i = 0; i < sizeof (expect)/sizeof (*expect); i++) {
			expect[i] = random ();
			bitbufferPush32 (&bb, expect[i], sizeof (expect[i])*8);
		}
		fail_unless (memcmp (expect, buf, sizeof (expect) == 0));
	}
} END_TEST

START_TEST (testBitbufferOverflowA) {
	for (unsigned int i = 0; i < sizeof (buf)/sizeof (*buf); i++) {
		bool ret = bitbufferPush32 (&bb, 0xaaaaaaaa, 32);
		ck_assert (ret);
	}
	bool ret = bitbufferPush32 (&bb, 0xaaaaaaaa, 32);
	ck_assert (!ret);
} END_TEST

START_TEST (testBitbufferOverflowB) {
	const unsigned int pushsize = 17;
	for (unsigned int i = 0; i < sizeof (buf)*8/pushsize; i++) {
		bool ret = bitbufferPush32 (&bb, 0xaaaaaaaa, pushsize);
		ck_assert (ret);
	}
	bool ret = bitbufferPush32 (&bb, 0xaaaaaaaa, pushsize);
	ck_assert (!ret);
} END_TEST

Suite *testBitbuffer () {
	Suite *s = suite_create ("bitbuffer");

	/* add generic tests */
	TCase *tc_core = tcase_create ("generic");
	tcase_add_checked_fixture (tc_core, testSetup, NULL);
	tcase_add_test (tc_core, testBitbufferInit);
	tcase_add_test (tc_core, testBitbufferPushOneA);
	tcase_add_test (tc_core, testBitbufferPushOneB);
	tcase_add_test (tc_core, testBitbufferPushOneC);
	tcase_add_test (tc_core, testBitbufferPushOneD);
	tcase_add_test (tc_core, testBitbufferPushOneTrailing);
	tcase_add_test (tc_core, testBitbufferPushTwo);
	//tcase_add_test (tc_core, testBitbufferPushRandom);
	tcase_add_test (tc_core, testBitbufferPushBoundaryA);
	tcase_add_test (tc_core, testBitbufferPushBoundaryB);
	tcase_add_test (tc_core, testBitbufferPushBoundaryC);
	tcase_add_test (tc_core, testBitbufferOverflowA);
	tcase_add_test (tc_core, testBitbufferOverflowB);
	suite_add_tcase (s, tc_core);

	return s;
}

