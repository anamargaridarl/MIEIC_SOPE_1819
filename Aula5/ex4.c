#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

#define BUFFER 512
#define READ    0
#define WRITE   1

int main(int argc, char * argv[]){
    int fd1[2], n;
    int fd2[2];
    char buffer[BUFFER];
    
    pipe(fd1);

    if(fork() > 0)
    {
        close(fd1[WRITE]);
        pipe(fd2);
        if(fork() > 0)
        {
            close(fd1[READ]);
            close(fd2[WRITE]);
            dup2(fd2[READ], STDIN_FILENO);
            execlp("sort","sort", NULL);
            printf("Error in sort!\n");
            exit(3);
        }
        else
        {
            close(fd2[READ]);
            dup2(fd1[READ], STDIN_FILENO);
            dup2(fd2[WRITE],STDOUT_FILENO);
            execlp("grep", "grep", argv[2], NULL);
            printf("Error grep!\n");
            exit(2);
        }
        
    }
    else
    {
        close(fd1[READ]);
        dup2(fd1[WRITE],STDOUT_FILENO);
        execlp("ls", "ls", argv[1], "-laR", NULL);
        printf("Error ls!\n");
        exit(1);
    }

    
    return 0;
}