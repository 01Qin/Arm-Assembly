//
// Created by Quinn on 15.2.2026.
//
#include <stdio.h>

// opcodes
#define LOAD 1
#define ADD 2
#define STORE 3

int main() {
    int accumulator = 0; // temporary storage
    int pc = 0; // program counter
    // instructions: {opcode, operand}
    int instructions[][2] = {
    {LOAD, 5}, // load 5 into accumulator
    {ADD, 10}, // add 10 to accumulator
    {STORE, 0} // store result
    };

    int instruction_count = sizeof(instructions) / sizeof(instructions[0]);
    printf("Simulating Fetch-Decode-Execute Cycle:\n");

    while (pc < instruction_count) {
        int opcode = instructions[pc][0];
        int operand = instructions[pc][1];

        if (opcode == LOAD) {
            accumulator = operand;
            printf("LOAD: Accumulator = %d\n", accumulator);
        } else if (opcode == ADD) {
            accumulator += operand;
            printf("ADD: Accumulator = %d\n", accumulator);
        } else if (opcode == STORE) {
            printf("STORE: Result = %d\n", accumulator);
        }
        pc++;
    }
    return 0;
}