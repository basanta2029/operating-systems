#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

#include "util.h"
#include "list.h"

/**
 * Parses the input file to extract the partition size and memory operations.
 * @param f - File pointer to the input file.
 * @param input - 2D array to store parsed operations (PID and block size/action).
 * @param n - Pointer to an integer to store the number of operations parsed.
 * @param PARTITION_SIZE - Pointer to an integer to store the initial partition size.
 */

void parse_file(FILE *f, int input[][2], int *n, int *PARTITION_SIZE) {
    fscanf(f, "%d\n", PARTITION_SIZE);

    while (!feof(f)) {
        fscanf(f, "%d %d\n", &input[*n][0], &input[*n][1]);
        (*n)++;
    }
}