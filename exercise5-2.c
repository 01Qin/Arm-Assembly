#include <stdio.h>
#include "pico/stdlib.h"
#include <string.h>

__attribute__(( naked )) void reverse(char *a)
{
	// the pointer to a character array is passed to the
	// subroutine in R0
	// remember to follow AAPCS:
	// push any register above r3 at the beginning and pop the same registers at the end
	// note: lr needs to be pushed because we are calling another subroutine
    // cortex-M0 requires popping to PC if LR was pushed. See the code below
	asm volatile
	(
			"push { r4-r7, lr } \n" // save original value of R4 as required by AAPCS
			"mov r4, r0 \n"

			"rev_loop: \n"
			"ldrb r5, [r4] \n"
			"cmp r5, #0 \n"
			"beq rev_done \n"

			"cmp r5, #'A' \n"
			"blt check_lower \n"
			"cmp r5, #'Z' \n"
			"bgt check_lower \n"

			"mov r6, r5 \n"
			"sub r6, #'A' \n"
			"mov r7, #'Z' \n"
			"sub r7, r6 \n"
			"mov r6, r7 \n"
			"b wr_bk \n"

			"check_lower: \n"
			"cmp r5, #'a' \n"
			"blt no_change \n"
			"cmp r5, #'z' \n"
			"bgt no_change \n"

			"mov r6, r5 \n"
			"sub r6, #'a' \n"
			"mov r7, #'z' \n"
			"sub r7, r6 \n"
			"mov r6, r7 \n"
			"b wr_bk \n"

			"no_change: \n"
			"mov r6, r5 \n"

			"wr_bk: \n"
			"strb r6, [r4] \n"
			"add r4, #1 \n"
			"b rev_loop \n"
			// r0 - r3 can be modified without preserving their original values
			"rev_done: \n"
			"pop { r4-r7, pc } \n" // cortex-M0 requires popping to PC if LR was pushed
            // "bx lr\n" // return to caller
	);
}

void fail() {
    printf("Failed\n"); // set a break point here
    while(1) {
        tight_loop_contents();
    }
}

void ok() {
    printf("\nAll ok\n"); // set a break point here
}

int main(void) {

    const uint led_pin = 22;
    int len = 0;

    // Initialize LED pin
    gpio_init(led_pin);
    gpio_set_dir(led_pin, GPIO_OUT);

    // Initialize chosen serial port
    stdio_init_all();

	// TODO: insert code here
	printf("\nExercise5\n");

	char test1[] = "Computer Architecture\n";
	const char test2[] = "Computer Architecture\n";
	reverse(test1);
	puts(test1);
	reverse(test1);
	puts(test1);
	if(strcmp(test1, test2)) {
		fail(); // error - string modified
	}
	char test3[] = "Johnny Ca$h:Live @Folsom\n";
	const char test4[] = "Johnny Ca$h:Live @Folsom\n";
	reverse(test3);
	puts(test3);
	reverse(test3);
	puts(test3);
	if(strcmp(test3, test4)) {
        fail(); // error - string modified
	}

	char test5[] = "If you like to gamble, I tell you I'm your man\n";
	const char test6[] = "If you like to gamble, I tell you I'm your man\n";
	reverse(test5);
	puts(test5);
	reverse(test5);
	puts(test5);
	if(strcmp(test5, test6)) {
        fail(); // error - string modified
	}

    ok();

    // Loop forever and blink an LED to indicaste success
    while (true) {
        // Blink LED
        gpio_put(led_pin, true);
        sleep_ms(1000);
        gpio_put(led_pin, false);
        sleep_ms(1000);
    }
	return 0 ;
}

