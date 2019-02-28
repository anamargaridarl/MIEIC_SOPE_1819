#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/times.h>
#include <stdlib.h>

#define BUFFER_SIZE 256

int main(int argc, char *argv[])
{
    FILE *f1;
    FILE *f2;

    int nr, nw;
    unsigned char buffer[BUFFER_SIZE];

    struct tms *t;
    clock_t init, final;

    t = (struct tms *)malloc(sizeof(struct tms));

    init = times(t);

    if (argc != 3)
    {
        printf("Usage: %s <source> <destination>\n", argv[0]);
        return 1;
    }

    f1 = fopen(argv[1], "r");
    if (f1 == NULL)
    {
        perror(argv[1]);
        return 2;
    }

    f2 = fopen(argv[2], "w");
    if (f2 == NULL)
    {
        perror(argv[2]);
        fclose(f1);
        return 3;
    }

    while ((nr = fread(buffer, sizeof(unsigned char), BUFFER_SIZE, f1)) > 0)
    {
        if ((nw = fwrite(buffer, sizeof(unsigned char), nr, f2)) <= 0)
        {
            perror(argv[2]);
            fclose(f1);
            fclose(f2);
            return 4;
        }
    }

    final = times(t);

    clock_t dif = final - init;
    dif /= sysconf(_SC_CLK_TCK);

    printf("%d \n", (int)dif);

    free(t);

    fclose(f1);
    fclose(f2);
    return 0;
}