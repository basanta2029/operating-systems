// list/list.h
// 
// Interface definition for linked list.
//
// <Author>

#include <stdbool.h>

/* Defines the type of the elements in the linked list.
 * You can change this type if you want to store different types of elements. */
typedef int elem;

/* Defines the node structure. Each node contains an element (value),
 * and a pointer to the next node in the list.
 * The last node should have `next` set to NULL. */
struct node {
	elem value;
	struct node *next;
};
typedef struct node node_t;

/* Defines the list structure, which simply points to the first node
 * (head) of the linked list. */
struct list {
	node_t *head;
};
typedef struct list list_t;

/* Functions for allocating and freeing the list. 
 * These functions handle the memory allocation and deallocation for the linked list. */
list_t *list_alloc();  // Allocates a new list.
void list_free(list_t *l);  // Frees the entire list and its nodes.

/* Prints the elements of the list in some format. */
void list_print(list_t *l);

/* Returns a string representation of the list. */
char* listToString(list_t *l);

/* Returns the number of elements in the list. */
int list_length(list_t *l);

/* Methods for adding elements to the list. */
void list_add_to_back(list_t *l, elem value);  // Adds an element to the back of the list.
void list_add_to_front(list_t *l, elem value);  // Adds an element to the front of the list.
void list_add_at_index(list_t *l, elem value, int index);  // Adds an element at a specific index.

/* Methods for removing elements from the list.
 * Returns the removed element. */
elem list_remove_from_back(list_t *l);  // Removes and returns the last element.
elem list_remove_from_front(list_t *l);  // Removes and returns the first element.
elem list_remove_at_index(list_t *l, int index);  // Removes and returns the element at a specific index.

/* Checks if a given element exists in the list.
 * Returns true if the element is found, false otherwise. */
bool list_is_in(list_t *l, elem value);

/* Returns the element at the given index.
 * Indexing starts from 0. Returns -1 if the index is invalid. */
elem list_get_elem_at(list_t *l, int index);

/* Returns the index of the given element in the list.
 * Returns -1 if the element is not found. */
int list_get_index_of(list_t *l, elem value);