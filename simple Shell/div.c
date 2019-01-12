#include <stdio.h>
#include <stdlib.h>
int strtoint(char* charnums);
int main(int argc, char *argv[],char ** envp)
{

    int k, sonuc=1; // dev a  b >>  a/b=sonuc
    int a=strtoint(argv[1]);
    int b=strtoint(argv[2]);
    if(a==-1 || b==-1|| b==0) return 0;// 0 a bölme varsa çıkma kotrolu
    sonuc=a/b;
    // yazdırma kısmı
     
    printf("%d / %d = %d \n",a,b, sonuc); 
//
    return 0;
}

int strtoint(char* charnums)
{
 int number=0;
 int index=0;
 while(charnums[index])
 {
    if(('0'<=charnums[index]) && (charnums[index]<='9'))
    {

    if(!number)
        number= ( (int) charnums[index]) - 48;
    else
    {
        number = (number *= 10) + ((int) charnums[index] - 48);
    }
    index++;
         }
         else
         {
            number=-1;
            printf("\nGecersiz islem");
            break;
         }
 }
 return number;
}
