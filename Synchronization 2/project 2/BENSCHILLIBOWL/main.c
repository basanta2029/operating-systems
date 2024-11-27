#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#include "BENSCHILLIBOWL.h"

#define BENSCHILLIBOWL_SIZE 100
#define NUM_CUSTOMERS 90
#define NUM_COOKS 10
#define ORDERS_PER_CUSTOMER 3
#define EXPECTED_NUM_ORDERS (NUM_CUSTOMERS * ORDERS_PER_CUSTOMER)

// Global variable for the restaurant
BENSCHILLIBOWL *bcb;

// Customer thread function
void* BENSCHILLIBOWLCustomer(void* tid) {
    int customer_id = (int)(long)tid;

    int i; // Declare loop variable outside the loop
    for (i = 0; i < ORDERS_PER_CUSTOMER; i++) {
        // Allocate space for an order
        Order* order = (Order*)malloc(sizeof(Order));
        if (!order) {
            fprintf(stderr, "Failed to allocate memory for order\n");
            pthread_exit(NULL);
        }

        // Select a menu item and populate the order
        order->menu_item = (char*)PickRandomMenuItem(); // Cast to remove 'const' warning
        order->customer_id = customer_id;

        // Add the order to the restaurant
        printf("Customer #%d placing order: %s\n", customer_id, order->menu_item);
        AddOrder(bcb, order);
    }

    pthread_exit(NULL);
}

// Cook thread function
void* BENSCHILLIBOWLCook(void* tid) {
    int cook_id = (int)(long)tid;
    int orders_fulfilled = 0;

    while (1) {
        // Get an order from the restaurant
        Order* order = GetOrder(bcb);

        // If no order is received, exit
        if (!order) {
            break;
        }

        // Fulfill the order and free its memory
        printf("Cook #%d fulfilling order: %s for customer #%d\n",
               cook_id, order->menu_item, order->customer_id);
        free(order);
        orders_fulfilled++;
    }

    printf("Cook #%d fulfilled %d orders\n", cook_id, orders_fulfilled);
    pthread_exit(NULL);
}

// Main function
int main() {
    // Open the restaurant
    bcb = OpenRestaurant(BENSCHILLIBOWL_SIZE, EXPECTED_NUM_ORDERS);

    // Create threads for customers and cooks
    pthread_t customers[NUM_CUSTOMERS];
    pthread_t cooks[NUM_COOKS];

    int i; // Declare loop variable outside the loops

    for (i = 0; i < NUM_COOKS; i++) {
        pthread_create(&cooks[i], NULL, BENSCHILLIBOWLCook, (void*)(long)(i + 1));
    }

    for (i = 0; i < NUM_CUSTOMERS; i++) {
        pthread_create(&customers[i], NULL, BENSCHILLIBOWLCustomer, (void*)(long)(i + 1));
    }

    // Wait for all threads to finish
    for (i = 0; i < NUM_CUSTOMERS; i++) {
        pthread_join(customers[i], NULL);
    }

    for (i = 0; i < NUM_COOKS; i++) {
        pthread_join(cooks[i], NULL);
    }

    // Close the restaurant
    CloseRestaurant(bcb);

    return 0;
}