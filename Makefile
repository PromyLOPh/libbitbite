.PHONY: runtest

runtest: test
	./$<

test: test.c bitbuffer.c bitbuffer_test.c
	gcc -Wall -Wextra -Werror -std=c11 -D_DEFAULT_SOURCE -o $@ $+ -lcheck

