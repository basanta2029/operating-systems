// process.h
#ifndef PROCESS_H
#define PROCESS_H

typedef struct {
    int pid;
    int arrival_time;
    int priority;
} Process;

extern int P_SIZE; // To track the number of processes read

void print_processes(Process *processes, int count); // Print function

#endif // PROCESS_H