#include <stdio.h>
#include <stdlib.h>
#include <time.h>  

int main(int argc, char *argv[])
{
    int n, i;
    i = 0;
    srand(time(NULL));
    do
    {
        n = rand()% atoi(argv[1]);
        printf("N %d :  %d \n", i,n);
        i++;
    }
    while( n != atoi(argv[2]) );
}