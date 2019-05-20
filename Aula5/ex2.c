#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

#define READ 0
#define WRITE 1


int main(void)
{
    int fd1[2];
    int fd2[2];
    pid_t pid;

    pipe(fd1);
    pipe(fd2);
    pid = fork();
    if (pid > 0) //pai
    {
        close(fd2[WRITE]);
        close(fd1[READ]);

        int a[2];
        printf("PARENT:\n");
        printf("x y ? ");
        scanf("%d %d", &a[0], &a[1]);

        write(fd1[WRITE], a, 2 * sizeof(int));

        int resRead[4];
        read(fd2[READ], resRead, 4 * sizeof(int));

        printf("Soma: %d \n", resRead[0]);
        printf("Diferenca: %d \n", resRead[1]);
        printf("Divisao: %d \n", resRead[2]);
        printf("Multiplicacao: %d \n", resRead[3]);

        close(fd1[WRITE]);
        close(fd2[READ]);
    }
    else //filho
    {
        close(fd1[WRITE]);
        close(fd2[READ]);

        int b[2];
        read(fd1[READ], b, 2 * sizeof(int));
        printf("SON:\n"); //WHY HERE AND NOT ABOVE ...?!

        int resWrite[4] = {b[0] + b[1], b[0] - b[1], 0, b[0] * b[1]};

        if (b[1] != 0)
        {
            resWrite[3] = b[0] / b[1];
        }

        write(fd2[WRITE], resWrite, 4 * sizeof(int));

        close(fd1[READ]);
        close(fd2[WRITE]);
    }
    return 0;
}