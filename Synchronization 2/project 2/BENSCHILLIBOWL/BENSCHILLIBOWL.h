#ifndef BENSCHILLIBOWL_H
#define BENSCHILLIBOWL_H

#include <pthread.h>
#include <stdbool.h>

typedef struct Order {
    int customer_id;
    char* menu_item;
    struct Order* next;
} Order;

typedef const char* MenuItem;

typedef struct {
    Order* orders;
    int max_size;
    int current_size;
    int expected_num_orders;
    int orders_handled;

    pthread_mutex_t mutex;
    pthread_cond_t can_add_orders;
    pthread_cond_t can_get_orders;
} BENSCHILLIBOWL;

// Global menu
extern const MenuItem BENSCHILLIBOWLMenu[];
extern const int BENSCHILLIBOWLMenuLength;

// Function prototypes
MenuItem PickRandomMenuItem();
BENSCHILLIBOWL* OpenRestaurant(int max_size, int expected_num_orders);
void CloseRestaurant(BENSCHILLIBOWL* bcb);
int AddOrder(BENSCHILLIBOWL* bcb, Order* order);
Order* GetOrder(BENSCHILLIBOWL* bcb);
void AddOrderToBack(Order** orders, Order* order);

#endif