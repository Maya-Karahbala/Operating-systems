#include <stdio.h>
#include <stdlib.h>
int strtoint(char* charnums);
int main(int argc, char *argv[],char ** envp)
{
   // rakam  5 >>     5 >> beş
    
    int sayi=strtoint(argv[1]);
    if(sayi==-1) {
    	return 0;
    }
  switch (sayi)
   {
 case 9: printf("%d >> Dokuz \n",sayi); break;
 case 8: printf("%d >> Sekiz \n",sayi); break;
 case 7: printf("%d >> Yedi \n",sayi); break;
 case 6: printf("%d >> Altı \n",sayi); break;
 case 5: printf("%d >> Beş \n",sayi); break;
 case 4: printf("%d >> Dört \n",sayi); break;
 case 3: printf("%d >> Üç \n",sayi); break;
 case 2: printf("%d >> İki \n",sayi); break;
 case 1: printf("%d >> Bir \n",sayi); break;
 case 0: printf("%d >> sıfır \n",sayi); break;

 }
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
