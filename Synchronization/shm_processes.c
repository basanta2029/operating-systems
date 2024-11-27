#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <time.h>

// Shared variables from example.c
extern int *BankAccount;
extern sem_t *mutex;

// Function for Dear Old Dad
void DearOldDad() {
    while (1) {
        sleep(rand() % 6); // Sleep 0-5 seconds
        printf("Dear Old Dad: Attempting to Check Balance\n");

        sem_wait(mutex); // Enter critical section
        int localBalance = *BankAccount;

        if (rand() % 2 == 0) { // Random number is even
            if (localBalance < 100) {
                int amount = rand() % 101; // Random amount 0-100
                if (rand() % 2 == 0) { // Random number is even
                    localBalance += amount;
                    printf("Dear Old Dad: Deposits $%d / Balance = $%d\n", amount, localBalance);
                    *BankAccount = localBalance;
                } else {
                    printf("Dear Old Dad: Doesn't have any money to give\n");
                }
            } else {
                printf("Dear Old Dad: Thinks Student has enough Cash ($%d)\n", localBalance);
            }
        } else {
            printf("Dear Old Dad: Last Checking Balance = $%d\n", localBalance);
        }
        sem_post(mutex); // Exit critical section
    }
}

// Function for Poor Student
void PoorStudent() {
    while (1) {
        sleep(rand() % 6); // Sleep 0-5 seconds
        printf("Poor Student: Attempting to Check Balance\n");

        sem_wait(mutex); // Enter critical section
        int localBalance = *BankAccount;

        if (rand() % 2 == 0) { // Random number is even
            int need = rand() % 51; // Random amount 0-50
            printf("Poor Student needs $%d\n", need);
            if (need <= localBalance) {
                localBalance -= need;
                printf("Poor Student: Withdraws $%d / Balance = $%d\n", need, localBalance);
                *BankAccount = localBalance;
            } else {
                printf("Poor Student: Not Enough Cash ($%d)\n", localBalance);
            }
        } else {
            printf("Poor Student: Last Checking Balance = $%d\n", localBalance);
        }
        sem_post(mutex); // Exit critical section
    }
}

// Function for Lovable Mom
void LovableMom() {
    while (1) {
        sleep(rand() % 11); // Sleep 0-10 seconds
        printf("Lovable Mom: Attempting to Check Balance\n");

        sem_wait(mutex); // Enter critical section
        int localBalance = *BankAccount;

        if (localBalance <= 100) {
            int amount = rand() % 126; // Random amount 0-125
            localBalance += amount;
            printf("Lovable Mom: Deposits $%d / Balance = $%d\n", amount, localBalance);
            *BankAccount = localBalance;
        }
        sem_post(mutex); // Exit critical section
    }
}