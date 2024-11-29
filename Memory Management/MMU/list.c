#include <stdio.h>
#include <stdlib.h>
#include "list.h"

node_t *create_node(block_t *blk) {
    node_t *new_node = (node_t *)malloc(sizeof(node_t));
    new_node->blk = blk;
    new_node->next = NULL;
    return new_node;
}

block_t *create_block(int pid, int start, int end) {
    block_t *new_block = (block_t *)malloc(sizeof(block_t));
    new_block->pid = pid;
    new_block->start = start;
    new_block->end = end;
    return new_block;
}

void list_add_ascending_by_address(node_t **list, node_t *new_node) {
    if (*list == NULL || (*list)->blk->start > new_node->blk->start) {
        new_node->next = *list;
        *list = new_node;
        return;
    }

    node_t *curr = *list;
    while (curr->next != NULL && curr->next->blk->start < new_node->blk->start) {
        curr = curr->next;
    }

    new_node->next = curr->next;
    curr->next = new_node;
}

void list_sort_by_address(node_t **list) {
    if (*list == NULL || (*list)->next == NULL) return;

    node_t *sorted = NULL;
    node_t *curr = *list;

    while (curr != NULL) {
        node_t *next = curr->next;
        list_add_ascending_by_address(&sorted, curr);
        curr = next;
    }

    *list = sorted;
}