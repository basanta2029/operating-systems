#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <search_term>\n", argv[0]);
        exit(1);
    }

    int pipe1[2], pipe2[2];
    
    // Create pipes
    if (pipe(pipe1) == -1) {
        perror("pipe1 failed");
        exit(1);
    }
    
    if (pipe(pipe2) == -1) {
        perror("pipe2 failed");
        exit(1);
    }

    // Fork first child to execute 'cat scores'
    pid_t p1 = fork();
    if (p1 == 0) {
        // In child P1 (cat process)
        dup2(pipe1[1], STDOUT_FILENO); // Redirect stdout to write end of pipe1
        close(pipe1[0]); // Close read end of pipe1
        close(pipe1[1]);
        close(pipe2[0]); // Close pipe2
        close(pipe2[1]);
        execlp("cat", "cat", "scores", NULL);
        perror("execlp failed");
        exit(1);
    }

    // Fork second child to execute 'grep'
    pid_t p2 = fork();
    if (p2 == 0) {
        // In child P2 (grep process)
        dup2(pipe1[0], STDIN_FILENO);  // Read from read end of pipe1
        dup2(pipe2[1], STDOUT_FILENO); // Write to write end of pipe2
        close(pipe1[1]); // Close write end of pipe1
        close(pipe1[0]);
        close(pipe2[0]); // Close read end of pipe2
        close(pipe2[1]);
        execlp("grep", "grep", argv[1], NULL);
        perror("execlp failed");
        exit(1);
    }

    // Fork third child to execute 'sort'
    pid_t p3 = fork();
    if (p3 == 0) {
        // In child P3 (sort process)
        dup2(pipe2[0], STDIN_FILENO); // Read from read end of pipe2
        close(pipe1[0]); // Close all pipe1 ends
        close(pipe1[1]);
        close(pipe2[1]); // Close write end of pipe2
        close(pipe2[0]);
        execlp("sort", "sort", NULL);
        perror("execlp failed");
        exit(1);
    }

    // Close all pipes in parent
    close(pipe1[0]);
    close(pipe1[1]);
    close(pipe2[0]);
    close(pipe2[1]);

    // Wait for children to finish
    wait(NULL);
    wait(NULL);
    wait(NULL);

    return 0;
}