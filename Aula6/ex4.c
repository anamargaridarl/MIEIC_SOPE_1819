#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 10

void *PrintTID(void *threadnum)
{
    pthread_t self;
    self = pthread_self();
    printf("Thread TID %lu \n", self);
    sleep(1);

    return threadnum;
}

int main()
{
    pthread_t threads[NUM_THREADS];
    int t;
    int *thrArg;
    for (t = 0; t < NUM_THREADS; t++)
    {
        void *count;
        thrArg = (int *)malloc(sizeof(t));
        *thrArg = t;
        pthread_create(&threads[t], NULL, PrintTID, thrArg);
        pthread_join(threads[t], &count);
        printf("N: %d\n", *(int *)count);
    }
    return 0;
}