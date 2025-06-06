#include <stdio.h>
#include <kernel/tty.h>
#include <test/test.h>

void kernel_main(void) {
	terminal_initialize();
	// printf("1\n");
	// printf("2\n");
	// printf("3\n");
	// printf("4\n");
	// printf("5\n");
	// printf("6\n");

	int val = 3223;
	printf("%d\n", val);
}
