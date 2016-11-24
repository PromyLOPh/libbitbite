#include <check.h>
#include <stdlib.h>

Suite *testBitbuffer ();

#define unused __attribute__((unused))

/*	test suite runner
 */
int main (int unused argc, char unused **argv) {
	int numberFailed;
	SRunner *sr = srunner_create (testBitbuffer ());

	srunner_run_all (sr, CK_ENV);
	numberFailed = srunner_ntests_failed (sr);
	srunner_free (sr);

	return (numberFailed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

