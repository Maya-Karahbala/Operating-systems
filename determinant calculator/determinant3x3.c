#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

void fillArray(int row ,int column, int matrix[3][3],char *newargv[4]) ;
void printArray1d(char *newargv[4],int length);
void printArray1dInt(int newargv[3],int length);
void printArray3x3(int matrix[3][3]);
void getArray3x3(int matrix[3][3]);
char *itoa_simple(char *dest, int i);
static char *itoa_simple_helper(char *dest, int i);
int main(int argc, char *argv[],char ** envp)
{
       int matrix[3][3];
       int results[3]; //result comming from kofakHesap
       char *newargv[4];// array will passed tp kofakHesap
      
      //pipe
     int pipefd[2];
      //pipe olustur
      if (pipe(pipefd) < 0) {
        perror("pipe");
        exit(1);
      }
    // random row or column has been chooced
      int result;//value will come from satSutSec
      int secilen =result%10 ;
      char answer;
      int pid,c,i;// for each element call kofakHesap program
      // get value of the matrix from user
      do{
       getArray3x3(matrix);
     
       printArray3x3(matrix);
      pid=fork();
      if (pid == 0) {// child process
          c = execve("SatSutSec", argv,envp);
          perror("");
          }
     else{//parent process
         wait(&c);
         read(pipefd[0], &result, sizeof(int));
         secilen=result%10;
         if(result>=10)// if first digit = 0 row has been choosed
           printf(" %d  row  is selected\n",secilen+1);
           else // if first digit = 1 column has been choosed
            printf("%d column  is selected\n",secilen+1); 
         }
       
      //invoking kofakHesap
      
      for (i = 0; i < 3; ++i)
      {
        
        pid=fork();
        if(pid==0){
           if(result>=10)// if first digit = 0 row has been choosed
           fillArray(secilen,i,matrix,newargv);
           else // if first digit = 1 column has been choosed
            fillArray(i,secilen,matrix,newargv);
           c=execve("KofakHesap2x2", newargv,NULL);
           printf("hata\n");
           close(pipefd[1]);
        }
        else{
          wait(&c);
          int value;
        read(pipefd[0], &value, sizeof(int));
         if(result>=10)// if first digit = 0 row has been choosed
            results[i]=matrix[secilen][i]*value;
           else // if first digit = 1 column has been choosed
            results[i]=matrix[i][secilen]*value;
        }
        
      }
      int totalResult=(results[0]-results[1]+results[2]);
      printf("total result = %d\n",totalResult);
      printf("yeni işlem yapmak istiyor musunuz y/n \n");
      scanf(" %c", &answer);
      if (answer=='n')
              exit(1); 
      }while(answer=='y');              
              // }

    

    return 0;
}

void fillArray(int row ,int column, int matrix[3][3],char *newargv[4]) {
  int i,j,k=0;
  for(i=0;i<3;i++)
  {
      for(j=0;j<3;j++)
      {
        if(i!=row && j!=column)
        {  
           newargv[k]=(char*) malloc(50*sizeof(char));
            itoa_simple(newargv[k],matrix[i][j]);
           k++;
        }
      }
  }
    newargv[k]=(char*) malloc(50*sizeof(char));
    newargv[k]=NULL;
   
}


void printArray1d(char *newargv[4],int length){
      for(int j=0;j<length;j++)
          {
          printf("%s  ",newargv[j]);
          
          }
          printf("\n");
}
void printArray1dInt(int newargv[3],int length){
      for(int j=0;j<length;j++)
          {
          printf("%d  ",newargv[j]);
          
          }
          printf("\n");
}
void printArray3x3(int matrix[3][3]){
       for(int i=0;i<3;i++)
        {
            for(int j=0;j<3;j++)
            {
            printf("%d ",matrix[i][j]);
            }
            printf("\n");
        }
}
void getArray3x3(int matrix[3][3]){
  printf("ENTER THE ELEMENTS OF  3X3 THE MATRIX:\n");
  int n,cont=0;;
  for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        { printf("matrix[%d][%d] :",i,j);
          n=scanf("%d",&matrix[i][j]);
          /*n=1;
          matrix[i][j]=cont++;*/
            if (n != 1) {// if the input is not a number
                  printf("invalid input" );
                  exit (1);
              }
        }
    }
}




static char *itoa_simple_helper(char *dest, int i) {
  if (i <= -10) {
    dest = itoa_simple_helper(dest, i/10);
  }
  *dest++ = '0' - i%10;
  return dest;
}

char *itoa_simple(char *dest, int i) {
  char *s = dest;
  if (i < 0) {
    *s++ = '-';
  } else {
    i = -i;
  }
  *itoa_simple_helper(s, i) = '\0';
  return dest;
}