#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "list.h"
#include "mmu.h"


node_t *FREE_LIST = NULL;
node_t *ALLOCATED_LIST = NULL;

void print_list(const char *name, node_t *list) {
    printf("%s:\n", name);
    node_t *curr = list;
    while (curr != NULL) {
        printf("  PID: %d, Start: %d, End: %d\n", curr->blk->pid, curr->blk->start, curr->blk->end);
        curr = curr->next;
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <input file> -{F | B | W}\n", argv[0]);
        return 1;
    }

    char policy = argv[2][1];
    if (policy != 'F' && policy != 'B' && policy != 'W') {
        printf("Invalid allocation policy. Use -F, -B, or -W.\n");
        return 1;
    }

    FILE *input_file = fopen(argv[1], "r");
    if (!input_file) {
        perror("Error opening file");
        return 1;
    }

    int input[100][2], n = 0, PARTITION_SIZE = 0;
    parse_file(input_file, input, &n, &PARTITION_SIZE);
    fclose(input_file);

    printf("PARTITION_SIZE = %d\n", PARTITION_SIZE);
    printf("Allocation Policy: %s\n", policy == 'F' ? "First Fit" :
                                      policy == 'B' ? "Best Fit" : "Worst Fit");

    // Initialize FREE_LIST
    block_t *initial_block = create_block(0, 0, PARTITION_SIZE - 1);
    FREE_LIST = create_node(initial_block);

    for (int i = 0; i < n; i++) {
        int pid = input[i][0];
        int size = input[i][1];

        if (pid > 0) {
            printf("Allocating %d bytes to PID %d\n", size, pid);
            allocate_memory(pid, size, policy);
        } else if (pid == -99999) {
            printf("Coalescing memory...\n");
            coalesce_memory();
        } else {
            printf("Deallocating memory for PID %d\n", -pid);
            deallocate_memory(-pid);
        }

        print_list("Free List", FREE_LIST);
        print_list("Allocated List", ALLOCATED_LIST);
    }

    return 0;
}