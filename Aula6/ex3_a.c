#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS 10

void *PrintHello(void *threadnum)
{
    printf("Hello from thread no. %d!\n", *(int *)threadnum);
    pthread_exit(NULL);
}
int main()
{
    pthread_t threads[NUM_THREADS];
    int t;
    int *thrArg;
    for (t = 0; t < NUM_THREADS; t++)
    {
        printf("Creating thread %d\n", t);
        thrArg = (int *)malloc(sizeof(t));
        *thrArg = t;
        pthread_create(&threads[t], NULL, PrintHello, thrArg);
        pthread_join(threads[t], NULL);
    }
    pthread_exit(0);
}