#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main() {
    int pipe1[2], pipe2[2];
    pid_t p;
    char input_str[100], output_str[100];

    // Create two pipes: pipe1 for P1 -> P2, pipe2 for P2 -> P1
    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        fprintf(stderr, "Pipe Failed");
        return 1;
    }

    p = fork();

    if (p < 0) {
        fprintf(stderr, "Fork Failed");
        return 1;
    }

    // Parent Process (P1)
    if (p > 0) {
        close(pipe1[0]);  // Close reading end of pipe1
        close(pipe2[1]);  // Close writing end of pipe2

        printf("Input: ");
        fgets(input_str, 100, stdin);
        input_str[strcspn(input_str, "\n")] = 0;  // Remove newline

        // Write the input string to pipe1
        write(pipe1[1], input_str, strlen(input_str) + 1);
        close(pipe1[1]);

        // Read from pipe2
        read(pipe2[0], output_str, 100);
        printf("Output: %s\n", output_str);
        close(pipe2[0]);
    }

    // Child Process (P2)
    else {
        close(pipe1[1]);  // Close writing end of pipe1
        close(pipe2[0]);  // Close reading end of pipe2

        // Read from pipe1
        read(pipe1[0], output_str, 100);
        close(pipe1[0]);

        // Append "howard.edu"
        strcat(output_str, "howard.edu");
        printf("Output: %s\n", output_str);

        // Get another input from P2
        printf("Input for P1: ");
        fgets(input_str, 100, stdin);
        input_str[strcspn(input_str, "\n")] = 0;  // Remove newline

        // Append "gobison.org"
        strcat(output_str, input_str);
        strcat(output_str, "gobison.org");

        // Write the final string to pipe2
        write(pipe2[1], output_str, strlen(output_str) + 1);
        close(pipe2[1]);
    }

    return 0;
}