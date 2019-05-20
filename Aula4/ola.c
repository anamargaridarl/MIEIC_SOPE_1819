#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
    char *a = NULL; 
    int i = (a == NULL ? 0:1);
    printf("i: %d \n", i );

    // i = 0
    printf( "true: %d\n", i == 0);
    printf("false: %d\n", i ==1);

    return 0;
}