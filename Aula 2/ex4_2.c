#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 50

struct Student
{
    char *name;
    int grade;
} student;

int main(void)
{
    FILE *f;
    int grade, n;
    char name[MAX_LEN];
    struct Student input;
    struct Student a;

    printf("How many students?");
    scanf("%d", &n);

    f = fopen("class", "w");
    if (f == NULL)
    {
        perror("class");
        fclose(f);
        return 1;
    }

    for (int i = n; i > 0; i--)
    {
        printf("Name of Student: \n");
        scanf("%s", name);
        printf("Grade: \n");
        scanf("%d", &grade);

        a.name=(char*)malloc(MAX_LEN*sizeof(char));
        a.name = name;
        
        a.grade =grade;

        fwrite(&a, sizeof(struct Student), 1, f);
    }

    fclose(f);


    f = fopen("class", "r");
    if (f == NULL)
    {
        perror("class");
        fclose(f);
        return 1;
    }

    while (fread(&input, sizeof(struct Student), 1, f))
        printf("name = %s , grade = %d \n", input.name,
               input.grade);
    
    fclose(f);
}