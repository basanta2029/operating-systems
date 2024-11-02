#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

#include "util.h"
#include "process.h"

/**
 * Parses an input file to create an array of ProcessType.
 * @param f A file pointer to the open input file.
 * @param P_SIZE A pointer to an integer that will store the number of processes parsed.
 * @return A dynamically allocated array of ProcessType. 
 *         The caller is responsible for freeing this memory.
 */
ProcessType *parse_file(FILE *f, int *P_SIZE) {
    int i = 0;
    
    // First, count the number of processes
    ProcessType temp;
    *P_SIZE = 0;
    while (fscanf(f, "%d %d %d %d %d %d\n", &temp.pid, &temp.bt, &temp.art, &temp.wt, &temp.tat, &temp.pri) == 6) {
        (*P_SIZE)++;
    }

    // Reset the file pointer to the beginning of the file
    fseek(f, 0, SEEK_SET);

    // Allocate memory for the actual array of processes
    ProcessType *pptr = (ProcessType *)calloc(*P_SIZE, sizeof(ProcessType));
    if (!pptr) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    // Read the process details again and populate the array
    while (i < *P_SIZE && fscanf(f, "%d %d %d %d %d %d\n", &pptr[i].pid, &pptr[i].bt, &pptr[i].art, &pptr[i].wt, &pptr[i].tat, &pptr[i].pri) == 6) {
        i++;
    }

    return pptr;
}