#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#define READ 0
#define WRITE 1

typedef struct{
    int a;
    int b;
}Numbers;

int main(void)
{
    int fd[2];
    pid_t pid;
    pipe(fd);
    pid = fork();
    if (pid > 0) //pai
    {
        int a[2];
        printf("PARENT:\n");
        printf("x y ? ");
        scanf("%d %d", &a[0], &a[1]);
        close(fd[READ]);
        Numbers nb;
        nb.a = a[0];
        nb.b = a[1];

        write(fd[WRITE], &nb, sizeof(Numbers));
        close(fd[WRITE]);
    }
    else //filho
    {
        Numbers n;
        int b[2];
        //printf("SON:\n");
        close(fd[WRITE]);
        read(fd[READ],&n ,  sizeof(Numbers));
        printf("SON:\n"); //WHY HERE AND NOT ABOVE ...?!
        printf("x + y = %d\n", n.a + n.b);
        printf("x - y = %d\n", n.a - n.b);
        if(n.b != 0)
        {
        float x = n.a / n.b;
        printf("x / y = %f \n", x);
        }

        printf("x * y = %d\n", n.a * n.b);
        close(fd[READ]);
    }
    return 0;
}