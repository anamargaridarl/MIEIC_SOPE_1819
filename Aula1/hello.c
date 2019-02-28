#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[], char *envp[])
{
	int i = 0;
	char *name = "USER=";

	while (envp[i] != NULL)
	{
		if(strncmp (envp[i], name, 5) == 0)
		{
			printf("Hello %s !\n", envp[i]+5);
		}
		i++;
	}
	return 0;
}
