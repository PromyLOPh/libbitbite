#include <check.h>
#include <stdlib.h>

Suite *testBitbuffer ();

/*	test suite runner
 */
int main (int argc, char **argv) {
	int numberFailed;
	SRunner *sr = srunner_create (testBitbuffer ());

	srunner_run_all (sr, CK_ENV);
	numberFailed = srunner_ntests_failed (sr);
	srunner_free (sr);

	return (numberFailed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

