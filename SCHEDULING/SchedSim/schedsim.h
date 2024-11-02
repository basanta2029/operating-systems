#ifndef SCHEDSIM_H
#define SCHEDSIM_H

#include "process.h"

// Function prototypes
void findWaitingTime(ProcessType plist[], int n);
void findTurnAroundTime(ProcessType plist[], int n);
int my_comparer(const void *a, const void *b);
void findWaitingTimeRR(ProcessType plist[], int n, int quantum);
void findWaitingTimeSJF(ProcessType plist[], int n);
void findWaitingTimePriority(ProcessType plist[], int n);
void findavgTimeFCFS(ProcessType plist[], int n);
void findavgTimeSJF(ProcessType plist[], int n);
void findavgTimeRR(ProcessType plist[], int n, int quantum);
void findavgTimePriority(ProcessType plist[], int n);
void printMetrics(ProcessType plist[], int n);
ProcessType *initProc(char *filename, int *n);

#endif