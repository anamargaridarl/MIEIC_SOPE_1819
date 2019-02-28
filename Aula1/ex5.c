#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[], char *envp[])
{
	int i = 0;
	char *name;
    name = getenv("USER");
	printf("Hello %s !\n", name);
	
	return 0;
}