/* signal.c */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handler(int signum)
{
  printf("Hello World!\n");
  alarm(5); // Schedule the next alarm in 5 seconds
}

int main(int argc, char * argv[])
{
  signal(SIGALRM, handler); // Register the signal handler for SIGALRM
  alarm(5); // Schedule the first alarm

  while(1) 
  {
    pause(); // Wait for signal
    printf("Turing was right!\n");
  }

  return 0;
}