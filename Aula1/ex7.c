#include <stdio.h>
#include <stdlib.h>

void F1(void)
{
    puts("Exit function 1.");
}

void F2(void)
{
    puts("Exit function 2.");
}

void F3(void)
{
    puts("Exit function 3.");
}

int main(int argc, char *argv[])
{
    printf("Main done! ");
    atexit(F1);
    atexit(F2);
        exit(1);
    atexit(F3);
}