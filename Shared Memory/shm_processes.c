#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <time.h>
#include <stdint.h>
#include <sys/types.h>  // Include this for pid_t

void DearOldDad(int *BankAccount, int *Turn) {
    int account;
    for (int i = 0; i < 25; i++) {
        sleep(rand() % 6); // Random sleep between 0-5 seconds

        while (*Turn != 0); // Wait for Turn = 0

        account = *BankAccount; // Copy the BankAccount value locally

        if (account <= 100) {
            int deposit = rand() % 101; // Random deposit between 0-100
            if (deposit % 2 == 0) {
                account += deposit;
                printf("Dear old Dad: Deposits $%d / Balance = $%d\n", deposit, account);
            } else {
                printf("Dear old Dad: Doesn't have any money to give\n");
            }
        } else {
            printf("Dear old Dad: Thinks Student has enough Cash ($%d)\n", account);
        }

        *BankAccount = account; // Update shared BankAccount
        *Turn = 1; // Set Turn to 1 (Student's turn)
    }
}

void PoorStudent(int *BankAccount, int *Turn) {
    int account;
    for (int i = 0; i < 25; i++) {
        sleep(rand() % 6); // Random sleep between 0-5 seconds

        while (*Turn != 1); // Wait for Turn = 1

        account = *BankAccount; // Copy the BankAccount value locally

        int withdraw = rand() % 51; // Random withdraw between 0-50
        printf("Poor Student needs $%d\n", withdraw);

        if (withdraw <= account) {
            account -= withdraw;
            printf("Poor Student: Withdraws $%d / Balance = $%d\n", withdraw, account);
        } else {
            printf("Poor Student: Not Enough Cash ($%d)\n", account);
        }

        *BankAccount = account; // Update shared BankAccount
        *Turn = 0; // Set Turn to 0 (Dad's turn)
    }
}

int main() {
    srand(time(NULL));

    int ShmID;
    int *ShmPTR;
    int shmSize = 2 * sizeof(int); // We need space for BankAccount and Turn

    ShmID = shmget(IPC_PRIVATE, shmSize, IPC_CREAT | 0666);
    if (ShmID < 0) {
        printf("*** shmget error (server) ***\n");
        exit(1);
    }

    ShmPTR = (int *) shmat(ShmID, NULL, 0);
    if ((intptr_t) ShmPTR == -1) {
        printf("*** shmat error (server) ***\n");
        exit(1);
    }

    ShmPTR[0] = 0; // BankAccount
    ShmPTR[1] = 0; // Turn

    pid_t pid = fork();
    if (pid < 0) {
        printf("Fork failed.\n");
        exit(1);
    } else if (pid == 0) { // Child process
        PoorStudent(&ShmPTR[0], &ShmPTR[1]);
        exit(0);
    } else { // Parent process
        DearOldDad(&ShmPTR[0], &ShmPTR[1]);
    }

    wait(NULL); // Wait for child to finish

    printf("Server has detected the completion of its child.\n");

    shmdt((void *) ShmPTR); // Detach from shared memory
    shmctl(ShmID, IPC_RMID, NULL); // Remove shared memory

    return 0;
}