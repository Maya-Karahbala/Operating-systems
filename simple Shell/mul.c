#include <stdio.h>
#include <stdlib.h>
int strtoint(char* charnums);

int main(int argc, char *argv[],char ** envp)
{
	// mul a b  >> a x b -= sonuc
    int k, sonuc=1,temp=0;// argcontrol arguman varsa 1 
      for(k=1; k<3 ;k++){
    	temp=strtoint((argv[k]));
    	if(temp == -1 ){
    		return (0);
    	}
    	 sonuc=sonuc* temp;
          }
    if (argv[1]!= NULL) printf(" %s x %s = %d\n",argv[1],argv[2],sonuc); 
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
            printf("Gecersiz islem \n");
            break;
         }
 }
 return number;
}
