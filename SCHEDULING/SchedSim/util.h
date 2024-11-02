#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include "process.h"

/**
 * Parses an input file to create an array of ProcessType.
 * @param f A file pointer to the open input file.
 * @param P_SIZE A pointer to an integer that will store the number of processes parsed.
 * @return A dynamically allocated array of ProcessType.
 */
ProcessType *parse_file(FILE *f, int *P_SIZE);

#endif  // UTIL_H