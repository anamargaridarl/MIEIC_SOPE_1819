// PROGRAMA p6a.c
#include <stdio.h>
#include <stdlib.h>

#define BUF_LENGTH 256
#define MAX 10

int main(int argc, char *argv[])
{
    FILE *src, *dst;
    char buf[BUF_LENGTH];

    if(argc < 3)
    {
    printf("Usage: \n");
    exit(3);
    }

    if ((src = fopen(argv[1], "r")) == NULL)
    {
        perror("file to read didnt open");
        exit(1);
    }
    if ((dst = fopen(argv[2], "w")) == NULL)
    {
        perror("file to write didnt open");
        exit(2);
    }
    while ((fgets(buf, MAX, src)) != NULL)
    {
        fputs(buf, dst);
    }
    fclose(src);
    fclose(dst);
    exit(0); // zero é geralmente indicativo de "sucesso"
}