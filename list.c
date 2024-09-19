// list/list.c
// 
// Implementation for linked list.
//
// <Author>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

// Helper function to create a new node with the given value
node_t *getNode(elem value) {
  node_t *mynode = (node_t *) malloc(sizeof(node_t));
  mynode->value = value;
  mynode->next = NULL;
  return mynode;
}

// Allocates memory for a new list
list_t *list_alloc() { 
  list_t* mylist =  (list_t *) malloc(sizeof(list_t)); 
  mylist->head = NULL;
  return mylist;  // Make sure to return the allocated list
}

// Frees memory used by the list and its nodes
void list_free(list_t *l) {
  if (l == NULL) {
    return;
  }

  node_t *current = l->head;
  node_t *next_node;

  while (current != NULL) {
    next_node = current->next;
    free(current);
    current = next_node;
  }

  free(l);  // Free the list itself after freeing all nodes
}

// Print all elements in the list
void list_print(list_t *l) {
  if (l == NULL) {
    printf("List is NULL\n");
    return;
  }

  node_t *current = l->head;

  if (current == NULL) {
    printf("List is empty\n");
    return;
  }

  while (current != NULL) {
    printf("%d -> ", current->value);
    current = current->next;
  }

  printf("NULL\n");
}

// Converts the list to a string representation
char *listToString(list_t *l) {
  char *buf = (char *) malloc(sizeof(char) * 1024);  // 1024 should be enough for most cases
  buf[0] = '\0';  // Start with an empty string
  char tbuf[20];

  node_t *curr = l->head;
  while (curr != NULL) {
    sprintf(tbuf, "%d->", curr->value);
    strcat(buf, tbuf);
    curr = curr->next;
  }
  strcat(buf, "NULL");
  return buf;
}

// Returns the length of the list
int list_length(list_t *l) {
  int count = 0;
  node_t *current = l->head;
  while (current != NULL) {
    count++;
    current = current->next;
  }
  return count;
}

// Add a new element to the back of the list
void list_add_to_back(list_t *l, elem value) {
  node_t *cur_node = getNode(value);

  if (l->head == NULL) {
    l->head = cur_node;
  } else {
    node_t *current = l->head;
    while (current->next != NULL) {
      current = current->next;
    }
    current->next = cur_node;
  }
}

// Add a new element to the front of the list
void list_add_to_front(list_t *l, elem value) {
  node_t *cur_node = getNode(value);
  cur_node->next = l->head;
  l->head = cur_node;
}

// Add a new element at a specific index
void list_add_at_index(list_t *l, elem value, int index) {
    if (index < 1 || index > list_length(l) + 1) {
        printf("Index %d out of bounds. Cannot add.\n", index);
        return;
    }

    if (index == 1) {  // Add at the front if index is 1
        list_add_to_front(l, value);
        return;
    }

    node_t *cur_node = getNode(value);
    node_t *current = l->head;
    int current_index = 1;  // Start index at 1

    while (current != NULL && current_index < index - 1) {
        current = current->next;
        current_index++;
    }

    if (current != NULL) {
        cur_node->next = current->next;
        current->next = cur_node;
    }
}

// Remove and return the last element from the list
elem list_remove_from_back(list_t *l) {
    if (l == NULL || l->head == NULL) {
        printf("List is empty. Cannot remove from back.\n");
        return -1;
    }

    if (l->head->next == NULL) {
        elem value = l->head->value;
        free(l->head);
        l->head = NULL;
        return value;
    }

    node_t *current = l->head;
    while (current->next->next != NULL) {
        current = current->next;
    }

    elem value = current->next->value;
    free(current->next);
    current->next = NULL;
    return value;
}

// Remove and return the first element from the list
elem list_remove_from_front(list_t *l) {
    if (l == NULL || l->head == NULL) {
        printf("List is empty. Cannot remove from front.\n");
        return -1;
    }

    node_t *node_to_remove = l->head;
    elem value = node_to_remove->value;
    l->head = node_to_remove->next;
    free(node_to_remove);

    return value;
}

// Remove and return an element at a specific index
elem list_remove_at_index(list_t *l, int index) {
    if (l == NULL || l->head == NULL || index < 1 || index > list_length(l)) {
        printf("Invalid index or no next node at index: %d\n", index);
        return -1;
    }

    if (index == 1) {  // If index is 1, remove from front
        return list_remove_from_front(l);
    }

    node_t *current = l->head;
    int current_index = 1;  // Start index at 1

    while (current != NULL && current_index < index - 1) {
        current = current->next;
        current_index++;
    }

    if (current == NULL || current->next == NULL) {
        printf("Invalid index or no next node at index: %d\n", index);
        return -1;
    }

    node_t *node_to_remove = current->next;
    elem value = node_to_remove->value;
    current->next = node_to_remove->next;
    free(node_to_remove);

    return value;
}
// Get the element at a specific index
elem list_get_elem_at(list_t *l, int index) {
    if (l == NULL || index < 1 || index > list_length(l)) {
        printf("Invalid index: %d\n", index);
        return -1;
    }

    node_t *current = l->head;
    int current_index = 1;  // Start index at 1

    while (current != NULL) {
        if (current_index == index) {
            return current->value;
        }
        current = current->next;
        current_index++;
    }

    printf("Index out of bounds: %d\n", index);
    return -1;
}
// Get the index of a specific value in the list
int list_get_index_of(list_t *l, elem value) {
    if (l == NULL) return -1;

    node_t *current = l->head;
    int current_index = 0;

    while (current != NULL) {
        if (current->value == value) {
            return current_index;
        }
        current = current->next;
        current_index++;
    }

    return -1;
}