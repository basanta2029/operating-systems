#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "process.h"
#include "util.h"

// Define the comparer function here
int my_comparer(const void *this, const void *that) {
    const Process *procA = (const Process *)this;
    const Process *procB = (const Process *)that;

    // Sort by priority in descending order
    if (procA->priority != procB->priority) {
        return procB->priority - procA->priority;
    }
    // For equal priority, sort by arrival time in ascending order
    return procA->arrival_time - procB->arrival_time;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: ./func_ptr <input-file-path>\n");
        return 1;
    }

    FILE *input_file = fopen(argv[1], "r");
    if (!input_file) {
        perror("Error opening file");
        return 1;
    }

    Process *processes = parse_file(input_file);
    if (!processes) {
        fprintf(stderr, "Error parsing file\n");
        fclose(input_file);
        return 1;
    }

    fclose(input_file);

    qsort(processes, P_SIZE, sizeof(Process), my_comparer);

    print_processes(processes, P_SIZE);

    free(processes);
    return 0;
}