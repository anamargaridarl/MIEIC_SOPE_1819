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

    if (argc != 2)
    {
        printf("Usage: %s <source> \n", argv[0]);
        return 1;
    }

    f1 = open(argv[1], O_RDONLY);
    if (f1 == -1)
    {
        perror(argv[1]);
        return 2;
    }

    while (nr = read(f1, buffer, BUFFER_SIZE) > 0)
    {
        if (nw = write(STDOUT_FILENO, buffer, nr) <= 0)
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