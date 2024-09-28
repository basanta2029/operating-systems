#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>  // Required for pid_t
#include <time.h>       // Required for time()

int main() {
    pid_t pid1, pid2;
    int status;

    // Seed the random number generator
    srand(time(NULL));

    // Create first child process
    pid1 = fork();

    if (pid1 == 0) {  // Child 1 process
        int iterations = rand() % 30;  // Random iterations, max 30
        int i;  // Declare i outside the loop
        for (i = 0; i < iterations; i++) {
            printf("Child 1 Pid: %d is going to sleep!\n", getpid());
            sleep(rand() % 10);  // Sleep for random time (max 10 seconds)
            printf("Child 1 Pid: %d is awake!\n", getpid());
            printf("Where is my Parent: %d?\n", getppid());
        }
        exit(0);
    }

    // Create second child process
    pid2 = fork();

    if (pid2 == 0) {  // Child 2 process
        int iterations = rand() % 30;  // Random iterations, max 30
        int i;  // Declare i outside the loop
        for (i = 0; i < iterations; i++) {
            printf("Child 2 Pid: %d is going to sleep!\n", getpid());
            sleep(rand() % 10);  // Sleep for random time (max 10 seconds)
            printf("Child 2 Pid: %d is awake!\n", getpid());
            printf("Where is my Parent: %d?\n", getppid());
        }
        exit(0);
    }

    // Parent process waits for both child processes to terminate
    waitpid(pid1, &status, 0);  // Wait for Child 1
    printf("Child Pid: %d has completed\n", pid1);

    waitpid(pid2, &status, 0);  // Wait for Child 2
    printf("Child Pid: %d has completed\n", pid2);

    return 0;
}