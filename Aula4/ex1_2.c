// PROGRAMA p01a.c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void (*old_handler) (int);

int main(void)
{
    old_handler = signal(SIGUSR1, SIG_IGN);

    if(old_handler < 0)
    {
        fprintf(stderr, "Unable to install SIGUSR1 handler\n");
        exit(1);
    }
    printf("Sleeping for 30 seconds ...\n");
    kill(getpid(),SIGUSR1);
    sleep(30);
    printf("Waking up ...\n");

    if(signal(SIGUSR1, old_handler)< 0)
    {
        fprintf(stderr, "Unable to install old SIGUSR1 handler\n");
        exit(1);
    }
    exit(0);
}