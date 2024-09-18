#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

int main() {
  list_t *mylist = list_alloc();
  list_add_to_front(mylist, 10);
  list_add_to_front(mylist, 20);
  list_add_to_front(mylist, 30);
  list_print(mylist);

  list_add_to_front(mylist, 40);
  list_add_to_front(mylist, 50);
  list_add_to_front(mylist, 60);
  list_add_to_front(mylist, 70);
  list_add_to_front(mylist, 80);
  list_add_to_front(mylist, 90);
  list_add_to_front(mylist, 100);
  list_print(mylist);

  // Test removing from the list
  printf("Before removing at index 3: %s\n", listToString(mylist));  // Debug statement
  list_remove_at_index(mylist, 3);
  list_print(mylist);  // Check list after removing

  printf("Before removing at index 6: %s\n", listToString(mylist));  // Debug statement
  list_remove_at_index(mylist, 6);
  list_print(mylist);  // Check list after removing

  // Continue with other test cases and print list after each operation
  printf("Before removing at index 0: %s\n", listToString(mylist));  // Debug statement
  list_remove_at_index(mylist, 0);
  list_print(mylist);

  return 0;
}