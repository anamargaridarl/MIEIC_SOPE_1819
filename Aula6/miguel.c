#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main()
{


    char *a = "2010-12-20";
    char p[10];
    strncpy(p,a, sizeof(p));
    char *token = strtok(p,"-");

      printf( " %s\n", token );  
      token = strtok(NULL, "-");
      printf( " %s\n", token );  
      token = strtok(NULL, "-");
      printf( " %s\n", token );  


    struct tm t;
    t.tm_year = 2010;
    t.tm_mday = 20;
    t.tm_mon = 5;

     struct tm f;
    f.tm_year = 2010;
    f.tm_mday = 25;
    f.tm_mon = 5;

  

}