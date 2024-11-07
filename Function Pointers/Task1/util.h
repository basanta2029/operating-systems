
// util.h
#ifndef UTIL_H
#define UTIL_H
#include "process.h"

// Utility function to load processes from a file
int load_processes(const char *filename, Process *processes, int max_count);
Process* parse_file(FILE *f);
#endif // UTIL_H

