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

    int memory[8] = {0};

    // instructions: {opcode, operand}
    int instructions[][2] = {
    {LOAD, 5}, // load 5 into accumulator
    {ADD, 10}, // add 10 to accumulator
    {STORE, 3} // store result
    };

    int instruction_count = sizeof(instructions) / sizeof(instructions[0]);
    printf("Simulating Fetch-Decode-Execute Cycle:\n");

    while (pc < instruction_count) {
        int opcode = instructions[pc][0];
        int operand = instructions[pc][1];

        switch (opcode) {
            case LOAD:
            accumulator = operand;
            printf("LOAD: Accumulator = %d\n", accumulator);
                break;
            case ADD:
            accumulator += operand;
            printf("ADD: Accumulator = %d\n", accumulator);
                break;
            case STORE:
                if (operand >= 0 && operand < (int)(sizeof(memory) / sizeof(memory[0]))){
                    memory[operand] = accumulator;
                    printf("STORE: memory[%d] = %d\n", operand, accumulator);
        } else {
            printf("STORE: invalid address %d\n", operand);
        }
                break;
                default:
            printf("Unknown opcode: %d\n", opcode);
        }
        pc++;
    }
    printf("Memory dump: ");
    for (size_t i = 0; i < sizeof(memory)/sizeof(memory[0]); ++i) {
        printf("%d", memory[i]);
    }
    printf("\n");
    return 0;
}