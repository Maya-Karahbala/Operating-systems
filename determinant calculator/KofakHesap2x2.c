#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, char *argv[],char ** envp)
{   /*argv = a,b,c,d
      a b
      c d
      result= a*d + b*c
    */ 
    int a=atoi(argv[0]);
    int b=atoi(argv[1]);
    int c=atoi(argv[2]);
    int d=atoi(argv[3]); 
    
    int result= a*d - b*c;
     
    write(4, &result, sizeof(int));

//
    return 0;
}

