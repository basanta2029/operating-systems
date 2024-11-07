#include <stdio.h>
#include "process.h"

void print_processes(Process *processes, int count) {
    for (int i = 0; i < count; i++) {
        printf("%d (%d, %d)\n", processes[i].pid, processes[i].priority, processes[i].arrival_time);
    }
}