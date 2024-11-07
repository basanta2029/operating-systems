#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include "process.h"

int P_SIZE = 0; // Track the number of processes

Process* parse_file(FILE *f) {
    size_t capacity = 10;
    Process *pptr = malloc(capacity * sizeof(Process));

    if (!pptr) {
        perror("Memory allocation failed");
        return NULL;
    }

    while (1) {
        int pid, arrival_time, priority;
        int result = fscanf(f, "%d %d %d", &pid, &arrival_time, &priority);
        if (result != 3) break; // Stop if not enough data

        if (P_SIZE >= capacity) {
            capacity *= 2;
            pptr = realloc(pptr, capacity * sizeof(Process));
            if (!pptr) {
                perror("Memory reallocation failed");
                return NULL;
            }
        }

        pptr[P_SIZE].pid = pid;
        pptr[P_SIZE].arrival_time = arrival_time;
        pptr[P_SIZE].priority = priority;
        P_SIZE++;
    }

    return pptr;
}