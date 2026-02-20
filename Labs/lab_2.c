//
// Created by Quinn on 20.2.2026.
//
#include <stdio.h>

#define NUM_TASKS 3
#define TIME_QUANTUM 2

typedef struct {
    int id;
    int timeRequired;
    int timeRemaining;
} Task;

int main() {
    Task tasks[NUM_TASKS] = {
        {1, 5, 5,},
        {2, 8, 8},
        {3, 6, 6}
    };

    int tasksRemaining = NUM_TASKS;

    printf("Round-Robin Scheduler Simulation\n");
    printf("--------------------------------\n");

    while (tasksRemaining > 0) {
        for (int i = 0; i < NUM_TASKS; i++) {
            if(tasks[i].timeRemaining > 0) {
                printf("Task %d executing for ", tasks[i].id);

                if (tasks[i].timeRemaining <= TIME_QUANTUM){
                    printf("%d unit(s). Task completed!\n", tasks[i].timeRemaining);
                    tasks[i].timeRemaining = 0;
                    tasksRemaining--;
                } else {
                    printf("%d unit(s)", TIME_QUANTUM);
                    tasks[i].timeRemaining -= TIME_QUANTUM;
                }
                printf("Task %d remaining time: %d unit(s)\n", tasks[i].id, tasks[i].timeRemaining);
            }
        }
        printf("------------------------------\n");
    }
    printf("All tasks completed!\n");
    return 0;
}