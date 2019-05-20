#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 4

typedef struct
{
    int a;
    int b;
} Operands;

void *addThread(void *threadnum)
{
    void *count;
    Operands *o = threadnum;

    count = malloc(sizeof(int));
    *(int *)count = o->a + o->b;

    sleep(1);
    return count;
}

void *subThread(void *threadnum)
{

    void *count;
    Operands *o = threadnum;

    count = malloc(sizeof(int));
    *(int *)count = o->a - o->b;

    sleep(1);
    return count;
}

void *multThread(void *threadnum)
{

    void *count;
    Operands *o = threadnum;

    count = malloc(sizeof(int));
    *(int *)count = o->a * o->b;

    sleep(1);
    return count;
}

void *divThread(void *threadnum)
{

    void *count;
    Operands *o = threadnum;

    if (!(o->b == 0))
        count = malloc(sizeof(int));
    *(int *)count = o->a / o->b;

    sleep(1);
    return count;
}

int main(int argc, char *argv[])
{
    if (!(argc == 3))
    {
        printf("wrong usage");
        return 0;
    }
 
    pthread_t threads[NUM_THREADS];
    int t;
    int *thrArg;
    Operands *o = malloc(sizeof(Operands));


    char *a = argv[1];
    char *b = argv[2];


    o->a =  (*a - (int)48);
    o->b =  (*b - (int)48);


    void *count;

    thrArg = (int *)malloc(sizeof(t));
    *thrArg = t;
    pthread_create(&threads[t], NULL, addThread, o);
    pthread_join(threads[t], &count);
    printf("ADD: %d\n", *(int *)count);
    pthread_create(&threads[t], NULL, subThread, o);
    pthread_join(threads[t], &count);
    printf("SUB: %d\n", *(int *)count);
    pthread_create(&threads[t], NULL, multThread, o);
    pthread_join(threads[t], &count);
    printf("MULT: %d\n", *(int *)count);
    pthread_create(&threads[t], NULL, divThread, o);
    pthread_join(threads[t], &count);
    printf("DIVIDE: %d\n", *(int *)count);

    return 0;
}