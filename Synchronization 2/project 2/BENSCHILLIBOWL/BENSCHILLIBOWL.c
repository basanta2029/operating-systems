#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "BENSCHILLIBOWL.h"

// Define the menu items
const MenuItem BENSCHILLIBOWLMenu[] = {
    "Chili Half-Smoke",
    "Chili Cheese Fries",
    "Bowl of Chili",
    "Shake",
    "Hot Dog",
    "Burger"
};

// Define the length of the menu
const int BENSCHILLIBOWLMenuLength = sizeof(BENSCHILLIBOWLMenu) / sizeof(MenuItem);

// Select a random menu item
MenuItem PickRandomMenuItem() {
    return BENSCHILLIBOWLMenu[rand() % BENSCHILLIBOWLMenuLength];
}

// Open the restaurant
BENSCHILLIBOWL* OpenRestaurant(int max_size, int expected_num_orders) {
    BENSCHILLIBOWL* bcb = (BENSCHILLIBOWL*)malloc(sizeof(BENSCHILLIBOWL));
    if (!bcb) {
        fprintf(stderr, "Failed to allocate memory for the restaurant\n");
        return NULL;
    }

    bcb->orders = NULL;
    bcb->max_size = max_size;
    bcb->expected_num_orders = expected_num_orders;
    bcb->current_size = 0;
    bcb->orders_handled = 0;

    pthread_mutex_init(&bcb->mutex, NULL);
    pthread_cond_init(&bcb->can_add_orders, NULL);
    pthread_cond_init(&bcb->can_get_orders, NULL);

    return bcb;
}

// Close the restaurant
void CloseRestaurant(BENSCHILLIBOWL* bcb) {
    pthread_mutex_lock(&bcb->mutex);

    if (bcb->orders_handled != bcb->expected_num_orders) {
        fprintf(stderr, "Error: Not all orders handled!\n");
    }

    pthread_mutex_unlock(&bcb->mutex);

    pthread_mutex_destroy(&bcb->mutex);
    pthread_cond_destroy(&bcb->can_add_orders);
    pthread_cond_destroy(&bcb->can_get_orders);

    free(bcb);
}

// Add an order to the restaurant
int AddOrder(BENSCHILLIBOWL* bcb, Order* order) {
    pthread_mutex_lock(&bcb->mutex);

    while (bcb->current_size >= bcb->max_size) {
        pthread_cond_wait(&bcb->can_add_orders, &bcb->mutex);
    }

    AddOrderToBack(&bcb->orders, order);
    bcb->current_size++;

    pthread_cond_signal(&bcb->can_get_orders);
    pthread_mutex_unlock(&bcb->mutex);

    return 0;
}

// Get an order from the restaurant
Order* GetOrder(BENSCHILLIBOWL* bcb) {
    pthread_mutex_lock(&bcb->mutex);

    while (bcb->current_size == 0 && bcb->orders_handled < bcb->expected_num_orders) {
        pthread_cond_wait(&bcb->can_get_orders, &bcb->mutex);
    }

    if (bcb->current_size == 0 && bcb->orders_handled >= bcb->expected_num_orders) {
        pthread_mutex_unlock(&bcb->mutex);
        return NULL;
    }

    Order* order = bcb->orders;
    bcb->orders = bcb->orders->next;
    bcb->current_size--;
    bcb->orders_handled++;

    pthread_cond_signal(&bcb->can_add_orders);
    pthread_mutex_unlock(&bcb->mutex);

    return order;
}

// Add an order to the back of the queue
void AddOrderToBack(Order** orders, Order* order) {
    if (*orders == NULL) {
        *orders = order;
        order->next = NULL;
    } else {
        Order* temp = *orders;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = order;
        order->next = NULL;
    }
}