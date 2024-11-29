#ifndef LIST_H
#define LIST_H

typedef struct block {
    int pid;
    int start;
    int end;
} block_t;

typedef struct node {
    block_t *blk;
    struct node *next;
} node_t;

node_t *create_node(block_t *blk);
block_t *create_block(int pid, int start, int end);
void list_add_ascending_by_address(node_t **list, node_t *new_node);
void list_sort_by_address(node_t **list);

#endif