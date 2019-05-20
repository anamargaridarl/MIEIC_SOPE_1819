// PROGRAMA p01.c
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include<stdlib.h>

#define STDERR 2
#define NUMITER 10000

int numb = 50;

void *thrfunc(void *arg)
{
    int i;
    void *count;
    fprintf(stderr, "Starting thread %s\n", (char *)arg);

    for (i = 1; i <= NUMITER && numb > 1; i++)
    {
        write(STDERR, arg, 1);
        numb--;
    }

    count = malloc(sizeof(int));
    *(int *)count = i -1;
    return count;
}
int main()
{
    void *count;
    pthread_t ta, tb;
    pthread_create(&ta, NULL, thrfunc, "1");
    pthread_create(&tb, NULL, thrfunc, "2");
    pthread_join(ta, &count);
    printf("Main thread: %d\n", *(int *)count);
    pthread_join(tb, &count);
    printf("Main thread: %d\n", *(int *)count);
    free(count);
    return 0;
}