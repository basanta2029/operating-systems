#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <time.h>

// Shared variables
int *BankAccount;
sem_t *mutex;

// Function declarations for process roles (defined in shm_processes.c)
void DearOldDad();
void PoorStudent();
void LovableMom();

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <num_parents> <num_children>\n", argv[0]);
        exit(1);
    }

    int num_parents = atoi(argv[1]);
    int num_children = atoi(argv[2]);

    srand(time(NULL));

    // Create shared memory for BankAccount
    BankAccount = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    *BankAccount = 0;

    // Create semaphore
    mutex = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    sem_init(mutex, 1, 1); // Shared between processes, initial value = 1

    pid_t pid;
    int i; // Declare 'i' outside of loops to avoid redefinition errors

    // Create parent processes
    for (i = 0; i < num_parents; i++) {
        if ((pid = fork()) == 0) {
            if (i == 0) {
                DearOldDad(); // First parent
            } else {
                LovableMom(); // Second parent or more
            }
            exit(0);
        }
    }

    // Create child processes
    for (i = 0; i < num_children; i++) {
        if ((pid = fork()) == 0) {
            PoorStudent(); // Child process
            exit(0);
        }
    }

    // Wait for all processes to complete
    while (wait(NULL) > 0);

    // Clean up
    sem_destroy(mutex);
    munmap(BankAccount, sizeof(int));
    munmap(mutex, sizeof(sem_t));

    return 0;
}