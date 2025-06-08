#include <stdio.h>
#include <kernel/tty.h>
#include <test/test.h>
#include <stdint.h>

extern uint32_t endkernel;


void kernel_main(void) {
	terminal_initialize();

	int val = 3223;
	printf("%d\n", val);
}


