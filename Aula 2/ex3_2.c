#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/times.h>
#include <stdlib.h>

#define BUFFER_SIZE 256


int main(int argc, char *argv[])
{
    int f1, f2, nr, nw;
    unsigned char buffer[BUFFER_SIZE];

    if (argc != 3 && argc !=2)
    {
        printf("Usage: %s <source> or <source> <destination> \n", argv[0]);
        return 1;
    }

    f1 = open(argv[1], O_RDONLY);
    if (f1 == -1)
    {
        perror(argv[1]);
        return 2;
    }

    if(argc ==3)
    {
    f2 = open(argv[2],O_CREAT | O_WRONLY | O_EXCL, 0644);
    if (f2 == -1)
    {
        perror(argv[2]);
        return 2;
    }

    dup2(f2,STDOUT_FILENO);
    }

    while (nr = read(f1, buffer, BUFFER_SIZE) > 0)
    {
        if (( write(STDOUT_FILENO, buffer, nr) <= 0 )&& (write(f2, buffer, nr) <= 0))
        {
            perror(argv[2]);
            close(f1);
            close(f2);
            return 4;
        }
    }

    close(f1);
    close(f2);
    return 0;
}