// PROGRAMA p01a.c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
    void (*old_handler) (int);

    old_handler = signal(SIGINT, SIG_IGN);

    if(old_handler < 0)
    {
        fprintf(stderr, "Unable to install SIGUSR1 handler\n");
        exit(1);
    }
    printf("Sleeping for 30 seconds ...\n");
    sleep(30);
    printf("Waking up ...\n");

    if(signal(SIGUSR1, old_handler)< 0)
    {
        fprintf(stderr, "Vulnerable again\n");
        exit(1);
    }
    exit(0);
}