#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main()
{
    for (int i = 0; i < 2; i++) // loop will run n times (n=5)
    {
        if (i == 0)
        {
            if (fork() > 0)
            {
                write(STDOUT_FILENO, "Hello ", 6);
                return 0;
            }
            else
            {
                write(STDOUT_FILENO, "my ", 3);
            }
        }
        else
        {
            if (fork() == 0)
            {
                write(STDOUT_FILENO, "friends\n", 8);
            }
        }
    }

    for (int i = 0; i < 2; i++) // loop will run n times (n=5)
    {
        wait(NULL);
    }

    return 0;
}
