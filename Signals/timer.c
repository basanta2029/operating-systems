#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

// Global variables to track alarms and start time
volatile sig_atomic_t alarmsTriggered = 0;
time_t startTime;

// Signal handler function for SIGALRM
void alarm_handler(int signum) {
    alarmsTriggered++;
    alarm(1);  // Set another alarm after 1 second
}

// Signal handler function for SIGINT (CTRL-C)
void sigint_handler(int signum) {
    time_t endTime = time(NULL);
    printf("\nProgram ran for %ld seconds\n", endTime - startTime);
    printf("Alarms triggered: %d\n", alarmsTriggered);
    _exit(0);  // Exit the program
}

int main() {
    // Record the start time
    startTime = time(NULL);

    // Register signal handlers for SIGALRM and SIGINT
    signal(SIGALRM, alarm_handler);
    signal(SIGINT, sigint_handler);

    // Start the first alarm
    alarm(1);

    // Infinite loop, waiting for signals
    while (1) {
        pause();  // Wait for signals
    }

    return 0;
}
