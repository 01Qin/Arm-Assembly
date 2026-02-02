#include <stdio.h>
#include "pico/stdlib.h"
#include <string.h>

__attribute__(( naked )) int prt(const char *a)
{
	// the pointer to a character array is passed to the
	// subroutine in R0
	// remember to follow AAPCS:
	// push any register above r3 at the beginning and pop the same registers at the end
	// note: lr needs to be pushed because we are calling another subroutine
    // cortex-M0 requires popping to PC if LR was pushed. See the code below
	asm volatile
	(
			"push { r4-r7, lr } \n" // we need to save return address because we call another subroutine
			"mov r4, r0 \n"
			"mov r5, #0 \n"

			"loop_start: \n"
			"ldrb r6, [r4] \n"
			"cmp r6, #0 \n"
			"beq loop_end \n"
			// r0 - r3 can (and will be) modified by putchar
			// so you have save the values yourself if you wish to keep
			// them safe. R4-R7 will not be modified by Board_UARTPutChar
			"cmp r6, #'A' \n"
			"blt no_convert \n"
			"cmp r6, #'Z' \n"
			"bgt no_convert \n"
			"add r6, r6, #32 \n"
			"no_convert: \n"

			"mov r0, r6 \n"
			"bl putchar \n"
			// to return a value copy it ro R0 before returning from subroutine
			"add r4, r4, #1 \n"
			"add r5, r5, #1 \n"
			"b loop_start \n"
			"loop_end: \n"

			"mov r0, r5 \n"

			"pop { r4-r7, pc } \n" // cortex-M0 requires popping to PC if LR was pushed
            // popping to PC will cause return from subroutine (~same as "bx lr")
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
	len = prt(test1);
	if(strcmp(test1, test2)) {
		fail(); // error - string modified
	}
	if(len != 22) {
		fail(); // error - incorrect length returned
	}
	char test3[] = "Johnny Ca$h:Live @Folsom\n";
	const char test4[] = "Johnny Ca$h:Live @Folsom\n";
	len = prt(test3);
	if(strcmp(test3, test4)) {
        fail(); // error - string modified
	}
	if(len != 25) {
		fail(); // error - incorrect length returned
	}

	char test5[] = "If you like to gamble, I tell you I'm your man\n";
	const char test6[] = "If you like to gamble, I tell you I'm your man\n";
	len = prt(test5);
	if(strcmp(test5, test6)) {
        fail(); // error - string modified
	}
	if(len != 47) {
		fail(); // error - incorrect length returned
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
