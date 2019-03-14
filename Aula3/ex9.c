#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char *argv[], char *envp[])
{
    int status;
    pid_t pid;
    if (argc != 2)
    {
        printf("usage: %s dirname\n", argv[0]);
        exit(1);
    }
    pid = fork();
    if (pid > 0)
    {
        waitpid(-1, &status,0);
        printf("My child is going to execute command              \"ls -laR %s\"\n", argv[1]);
        printf("My son exited with EXIT CODE = %d\n ", WEXITSTATUS(status));
        if(WIFEXITED(status) == 1)
        printf("Normal termination \n");
    }
    else if (pid == 0)
    {
        execlp("ls", "ls", "-laR", NULL);
        printf("Command not executed !\n");
        exit(1);
    }
    exit(0);
}