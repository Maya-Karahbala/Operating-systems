#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define clear() printf("\033[H\033[J")

// methods signatures 
int dtmsplit(char *str, const char *delim, char ***array, int *length );
char *trim(char *str);

int main(int argc, char *argv[],char ** envp)
{

  int k,i,fv,perid,komutSayisi=1;
  char **arr = NULL;
  char str[80];
  int c = 0, count =0;
    int baslangic= 0;// birden fazla komut varsa kopyalama başlangıc adresi
    int yapilanKomutSayisi;

    char *girilenStr=(char*) malloc(50*sizeof(char));
    while(1){
      baslangic=0;
      komutSayisi=1;
      yapilanKomutSayisi=0;
      printf("myshell>> ");
      fgets (girilenStr, 300, stdin);
      c = 0;
      count =0;
      c = dtmsplit(girilenStr, " ", &arr, &count);
    //komut sayisini bulma
      for (int i = 0; i < count; ++i)
      {
       if (strcmp((trim(arr[i])), "&") == 0){
        komutSayisi=komutSayisi+1;
      }
    }

    //arr kopyalama
    char *newargv[count];
    while(yapilanKomutSayisi< komutSayisi){

      yapilanKomutSayisi=yapilanKomutSayisi+1;
      i=0;
      for(k=baslangic;k<count;k++){
        newargv[i]=(char*) malloc(50*sizeof(char));
        if (strcmp((trim(arr[k])), "&") == 0){
          newargv[k]=(char*) malloc(50*sizeof(char));
          newargv[k]=NULL;
          baslangic=k+1;
          break;
        }
        strcpy(newargv[i], trim(arr[k]));
        i++;

      }

      newargv[count]=(char*) malloc(50*sizeof(char));
      newargv[count]=NULL;

    // ilk argümana göre
      if (strcmp(newargv[0], "exit") == 0) {
          return 0;
        }

      else if (strcmp(newargv[0], "clear") == 0) {
          clear();
        }
      else if (strcmp(newargv[0], "cat") == 0) {
          printf("cat :  " );
          for(k=1 ;k<count;k++){
            if (strcmp(newargv[k], "&") == 0){
              printf("girdi\n");
             break;
           }
           printf("%s ",newargv[k] );
         }
         printf("\n" );
       }
       
      else if (strcmp(newargv[0], "mul") == 0) {
           fv=fork();
             if(fv==0){
                i = execve("mul", newargv, envp);
                }
             else{// parent
                wait(NULL);
                 }
       }

      else if (strcmp(newargv[0], "rakam") == 0) {
        fv=fork();
        if(fv==0){
         i = execve("rakam", newargv, envp);
         }

       }
       else if (strcmp(newargv[0], "div") == 0) {
            fv=fork();
            if(fv==0){
               i = execve("div", newargv, envp);
               }
            else{// parent
               wait(NULL);
                }

            }

       else{
        printf("yanlis bir komut girdiniz\n");
        }

      }//while(komut sayısı)
      
    }//while(1)
    return(0);
  }
  int dtmsplit(char *str, const char *delim, char ***array, int *length ) {
    int i=0;
    char *token;
    char **res = (char **) malloc(0 * sizeof(char *));

  /* get the first token */
    token = strtok(str, delim);
    while( token != NULL ) 
    {
      res = (char **) realloc(res, (i + 1) * sizeof(char *));
      res[i] = token;
      i++;
      token = strtok(NULL, delim);
    }
    *array = res;
    *length = i;
    return 1;
  }
  char *trim(char *str)
  {
    size_t len = 0;
    char *frontp = str;
    char *endp = NULL;
    if( str == NULL ) { return NULL; }
    if( str[0] == '\0' ) { return str; }
    len = strlen(str);
    endp = str + len;
    while( isspace((unsigned char) *frontp) ) { ++frontp; }
    if( endp != frontp )
    {
      while( isspace((unsigned char) *(--endp)) && endp != frontp ) {}
    }

  if( str + len - 1 != endp )
    *(endp + 1) = '\0';
  else if( frontp != str &&  endp == frontp )
    *str = '\0';
  endp = str;
  if( frontp != str )
  {
    while( *frontp ) { *endp++ = *frontp++; }
    *endp = '\0';
  }


  return str;
}
