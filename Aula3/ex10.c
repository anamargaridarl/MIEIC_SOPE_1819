#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char *argv[], char *envp[])
{
    pid_t pid;
    int f1;
    if (argc != 2 && argc != 3)
    {
        printf("usage: %s dirname or %s dirname newfile \n", argv[0], argv[0]);
        exit(1);
    }
    pid = fork();
    if (pid > 0)
        printf("My child is going to execute command              \"ls -laR %s\"\n", argv[1]);
    else if (pid == 0)
    {

        if (argc == 3)
        {
            f1 = open(argv[2], O_WRONLY | O_CREAT, 0644);

            if (f1 == -1)
            {
                perror(argv[2]);
                return 2;
            }

            dup2(f1, STDOUT_FILENO);
        }

        execlp("ls", "ls", "-laR", NULL);
        printf("Command not executed !\n");
        exit(1);
    }
    exit(0);
}