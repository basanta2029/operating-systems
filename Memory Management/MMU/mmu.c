#include <stdio.h>
#include <stdlib.h>
#include "mmu.h"
#include "list.h"  // For node_t, block_t, and linked list functions

// External lists defined in main.c
extern node_t *FREE_LIST;
extern node_t *ALLOCATED_LIST;

// Function to allocate memory based on the selected policy
void allocate_memory(int pid, int size, char policy) {
    node_t *prev = NULL, *curr = FREE_LIST;
    node_t *best_fit = NULL, *worst_fit = NULL;

    // Determine allocation policy
    if (policy == 'F') {  // First Fit
        while (curr != NULL) {
            int block_size = curr->blk->end - curr->blk->start + 1;
            if (block_size >= size) {
                break;
            }
            prev = curr;
            curr = curr->next;
        }
    } else if (policy == 'B') {  // Best Fit
        while (curr != NULL) {
            int block_size = curr->blk->end - curr->blk->start + 1;
            if (block_size >= size &&
                (best_fit == NULL || block_size < best_fit->blk->end - best_fit->blk->start + 1)) {
                best_fit = curr;
            }
            curr = curr->next;
        }
        curr = best_fit;
    } else if (policy == 'W') {  // Worst Fit
        while (curr != NULL) {
            int block_size = curr->blk->end - curr->blk->start + 1;
            if (block_size >= size &&
                (worst_fit == NULL || block_size > worst_fit->blk->end - worst_fit->blk->start + 1)) {
                worst_fit = curr;
            }
            curr = curr->next;
        }
        curr = worst_fit;
    }

    if (curr == NULL) {
        printf("Error: Not Enough Memory\n");
        return;
    }

    // Allocate memory from selected block
    block_t *new_block = create_block(pid, curr->blk->start, curr->blk->start + size - 1);
    list_add_ascending_by_address(&ALLOCATED_LIST, create_node(new_block));

    // Update free block
    curr->blk->start += size;
    if (curr->blk->start > curr->blk->end) {
        if (prev == NULL) {
            FREE_LIST = curr->next;
        } else {
            prev->next = curr->next;
        }
        free(curr->blk);
        free(curr);
    }
}

// Function to deallocate memory for a specific PID
void deallocate_memory(int pid) {
    node_t *prev = NULL, *curr = ALLOCATED_LIST;

    // Find the node to deallocate
    while (curr != NULL && curr->blk->pid != pid) {
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL) {
        printf("Error: PID %d not found in allocated list\n", pid);
        return;
    }

    // Remove the node from ALLOCATED_LIST
    if (prev == NULL) {
        ALLOCATED_LIST = curr->next;
    } else {
        prev->next = curr->next;
    }

    // Add the block back to FREE_LIST
    list_add_ascending_by_address(&FREE_LIST, curr);
}

// Function to coalesce adjacent free memory blocks
void coalesce_memory() {
    // Sort the FREE_LIST by starting address
    list_sort_by_address(&FREE_LIST);

    node_t *curr = FREE_LIST;
    while (curr != NULL && curr->next != NULL) {
        if (curr->blk->end + 1 == curr->next->blk->start) {
            // Merge current and next blocks
            curr->blk->end = curr->next->blk->end;
            node_t *temp = curr->next;
            curr->next = curr->next->next;
            free(temp->blk);
            free(temp);
        } else {
            curr = curr->next;
        }
    }
}