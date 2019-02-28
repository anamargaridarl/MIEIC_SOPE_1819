#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/times.h>

#define BUFFER_SIZE 20

int main(int argc, char *argv[])
{
    struct tms *t;
    clock_t init, final;

    t = (struct tms *)malloc(sizeof(struct tms));

    init = times(t);

    int f1, f2, nr, nw;
    unsigned char buffer[BUFFER_SIZE];

    if (argc != 3)
    {
        printf("Usage: %s <source> <destination>\n", argv[0]);
        return 1;
    }

    f1 = open(argv[1], O_RDONLY);
    if (f1 == -1)
    {
        perror(argv[1]);
        return 2;
    }

    f2 = open(argv[2], O_CREAT | O_WRONLY | O_EXCL, 0644);
    if (f2 == -1)
    {
        perror(argv[2]);
        close(f1);
        return 3;
    }

    while (nr = read(f1, buffer, BUFFER_SIZE) > 0)
    {
        if (nw = write(f2, buffer, nr) <= 0)
        {
            perror(argv[2]);
            close(f1);
            close(f2);
            return 4;
        }
    }

    final = times(t);

    clock_t dif = final - init;
    dif /= sysconf(_SC_CLK_TCK);

    printf("%d \n", (int)dif);

    free(t);

    close(f1);
    close(f2);
    return 0;
}