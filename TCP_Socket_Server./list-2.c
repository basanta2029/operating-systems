#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

list_t* list_alloc() {
    list_t* list = (list_t*)malloc(sizeof(list_t));
    list->head = NULL;
    return list;
}

void list_free(list_t* list) {
    node_t* current = list->head;
    node_t* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    free(list);
}

void list_add_to_back(list_t* list, int value) {
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    new_node->data = value;
    new_node->next = NULL;

    if (list->head == NULL) {
        list->head = new_node;
    } else {
        node_t* current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

void list_add_to_front(list_t* list, int value) {
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    new_node->data = value;
    new_node->next = list->head;
    list->head = new_node;
}

void list_add_at_index(list_t* list, int index, int value) {
    if (index == 0) {
        list_add_to_front(list, value);
        return;
    }

    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    new_node->data = value;

    node_t* current = list->head;
    for (int i = 0; i < index - 1 && current != NULL; i++) {
        current = current->next;
    }

    if (current == NULL) {
        free(new_node);
        return;
    }

    new_node->next = current->next;
    current->next = new_node;
}

int list_remove_from_back(list_t* list) {
    if (list->head == NULL) return -1;

    node_t* current = list->head;
    if (current->next == NULL) {
        int val = current->data;
        free(current);
        list->head = NULL;
        return val;
    }

    while (current->next->next != NULL) {
        current = current->next;
    }

    int val = current->next->data;
    free(current->next);
    current->next = NULL;
    return val;
}

int list_remove_from_front(list_t* list) {
    if (list->head == NULL) return -1;

    node_t* temp = list->head;
    int val = temp->data;
    list->head = list->head->next;
    free(temp);
    return val;
}

int list_remove_at_index(list_t* list, int index) {
    if (index == 0) return list_remove_from_front(list);

    node_t* current = list->head;
    for (int i = 0; i < index - 1 && current != NULL; i++) {
        current = current->next;
    }

    if (current == NULL || current->next == NULL) {
        return -1;
    }

    node_t* temp = current->next;
    int val = temp->data;
    current->next = temp->next;
    free(temp);
    return val;
}

int list_get_elem_at(list_t* list, int index) {
    node_t* current = list->head;
    for (int i = 0; i < index && current != NULL; i++) {
        current = current->next;
    }
    if (current == NULL) return -1;
    return current->data;
}

int list_length(list_t* list) {
    int count = 0;
    node_t* current = list->head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

char* listToString(list_t* list) {
    static char str[1024];
    str[0] = '\0';
    node_t* current = list->head;
    while (current != NULL) {
        char buffer[32];
        sprintf(buffer, "%d -> ", current->data);
        strcat(str, buffer);
        current = current->next;
    }
    strcat(str, "NULL");
    return str;
}