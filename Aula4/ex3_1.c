#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

int flag = 0;


void sigusr1_handler(int signo)
{
    flag = 0;
}


void sigusr2_handler(int signo)
{
    flag =1;
}


int main(void)
{
    struct sigaction usr1;
    usr1.sa_handler = sigusr1_handler;
    sigemptyset(&usr1.sa_mask);
    usr1.sa_flags = 0;

    struct sigaction usr2;
    usr2.sa_handler = sigusr2_handler;
    sigemptyset(&usr2.sa_mask);
    usr2.sa_flags = 0;

    if (sigaction(SIGUSR1, &usr1, NULL) < 0)
    {
        fprintf(stderr, "Unable to install SIGUSR1 handler\n");
        exit(1);
    }

     if (sigaction(SIGUSR2, &usr2, NULL) < 0)
    {
        fprintf(stderr, "Unable to install SIGUSR2 handler\n");
        exit(2);
    }


    int i = 0;

    while(1)
    {
    printf("%d \n", i);
    sleep(1);
    if(!flag)
    i++;
    else
    i--;    
    }
}