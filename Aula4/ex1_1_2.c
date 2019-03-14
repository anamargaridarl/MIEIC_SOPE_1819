// PROGRAMA p01a.c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void sigint_handler(int signo)
{
    printf("In SIGUSR1 handler ...\n");
}

int main(void)
{
    if (signal(SIGUSR1, sigint_handler) < 0)
    {
        fprintf(stderr, "Unable to install SIGINT handler\n");
        exit(1);
    }
    printf("Sleeping for 30 seconds ...\n");
    kill(getpid(),SIGUSR1);
    sleep(30);
    printf("Waking up ...\n");
    exit(0);
}