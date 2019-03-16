#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int pid, status;
pid_t pid_chld = 0;

void sigalarm_handler(int signo)
{
    printf("Alarm handler \n");
    printf("Prog was aborted \n");
    kill(pid_chld, SIGKILL);
}

void sigchld_handler(int signo)
{
    pid = wait(&status);
    if (pid != -1)
    {
        printf("Program finished normally");
        exit(0);
    }
}

int main(int argc, char *argv[])
{

    struct sigaction alrm;
    alrm.sa_handler = sigalarm_handler;
    sigemptyset(&alrm.sa_mask);
    alrm.sa_flags = 0;

    struct sigaction chld;
    chld.sa_handler = sigchld_handler;
    sigemptyset(&chld.sa_mask);
    chld.sa_flags = 0;

    // Implement handlers for signals
    if (sigaction(SIGALRM, &alrm, NULL) < 0)
    {
        fprintf(stderr, "Unable to install SIGALRM handler\n");
        exit(1);
    }

    if (sigaction(SIGCHLD, &chld, NULL) < 0)
    {
        fprintf(stderr, "Unable to install SIGCHILD handler\n");
        exit(1);
    }

    if (argc != 3)
    {
        printf("Error calling program \n");
        return 1;
    }

    alarm(atoi(argv[1]));

    pid = fork();

    if (pid == 0)
    {
        if(execvp(argv[0],argv) == -1)
        printf("error");
        
        pid_chld = getpid();

        for (int i = 1; i <= 2; i++)
        {
            printf(" %s \n", argv[2]);
            sleep(5);
        }

        exit(0);
    }
    else
    {
        sleep(atoi(argv[1]));
    }

    return 0;
}