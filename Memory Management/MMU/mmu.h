#ifndef MMU_H
#define MMU_H

#include "list.h"  // For node_t and block_t definitions

// Function prototypes for memory management
void allocate_memory(int pid, int size, char policy);
void deallocate_memory(int pid);
void coalesce_memory();

#endif