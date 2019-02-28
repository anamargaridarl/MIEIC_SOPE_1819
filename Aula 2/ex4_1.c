#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 50

int main(void)
{
    int grade,n,f;
    printf("How many students?");
    scanf("%d", &n);
    char name[MAX_LEN];

    f = open("class", O_CREAT | O_WRONLY | O_EXCL, 0644);
    if (f == -1)
    {
        perror("class");
        close(f);
        return 3;
    }

    for(int i =n; i >0; i--)
    {
    printf("Name of Student: ");
    scanf("%s", name);
    printf("Grade: ");
    scanf("%d", &grade);
    write(f,name,strlen(name));
    write(f,to_string(grade),strlen(to_string(grade)));
    }

    close(f);

}