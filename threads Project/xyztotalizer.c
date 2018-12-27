#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
int strint( char* charnums);
char *intstr(int number);
int readnumber(char *character, int line);

pthread_mutex_t lockx;
pthread_mutex_t locky;
pthread_mutex_t lockz;
pthread_mutex_t lockSum;
int readcount,linenum=1,counter=0;

int x,y,z;
void *setX()
{    
	while(counter<readcount)
	{  // lock xthread to prevent x from working one more time befor y,z and some working
		pthread_mutex_lock(&lockx);
		x=readnumber("x", linenum);
		printf("x = %d\n" ,x);
		linenum++; // increase line for next thread
		counter++; // increase number of line read from numbers file
		// unlock y to keep progress 
		pthread_mutex_unlock(&locky);
	}
}

void *setY()//
{
	while(counter<readcount)
	{
		pthread_mutex_lock(&locky);
		y=readnumber("y", linenum);
		printf("y = %d\n",y );
		linenum++;
		counter++;
		pthread_mutex_unlock(&lockz);
	}
}

void *setZ() 
{
	while(counter<readcount)
	{
		pthread_mutex_lock(&lockz);
		z=readnumber("z", linenum);
		printf("z = %d\n",z );
		linenum++;
		counter++;
		pthread_mutex_unlock(&lockSum);
	}
}
void *sum() 
{
	
	while(counter<readcount)
	{	
		pthread_mutex_lock(&lockSum);
		printf("x + y + z = %d  \n",(x+y+z));
		pthread_mutex_unlock(&lockx);
	}
	
}

int main(int argc, char *argv[],char ** envp){
	// readcount will be passed as a paramter to main and converted to int
	readcount=strint(argv[1]);	
	readcount=readcount-2;
	// initilization all mutexs
	pthread_mutex_init(&lockx, NULL);
	pthread_mutex_init(&lockz, NULL);
	pthread_mutex_init(&locky, NULL);
	pthread_mutex_init(&lockSum, NULL);
	// lock all threads except x to start
	pthread_mutex_lock(&locky); 
	pthread_mutex_lock(&lockz); 
	pthread_mutex_lock(&lockSum);
	// initilization all threads
	pthread_t xthread;
	pthread_t ythread;
	pthread_t zthread;
	pthread_t sumthread;
    // create all threads
	void* status;
	pthread_create(&xthread,NULL,setX,NULL);
	pthread_create(&ythread,NULL,setY,NULL);
	pthread_create(&zthread,NULL,setZ,NULL);
	pthread_create(&sumthread,NULL,sum,NULL);
	pthread_join(xthread,&status);
	pthread_join(ythread,&status);
	pthread_join(zthread,&status);
	pthread_join(sumthread,&status);
	// destroy mutexs before terminating
	pthread_mutex_destroy(&lockx);
	pthread_mutex_destroy(&lockz); 
	pthread_mutex_destroy(&locky); 
	pthread_mutex_destroy(&lockSum);
	return 0;
}

int readnumber(char *character, int line){
	int npipefd;
    //path of named pipe 
	char * myfifo = "/tmp/myfifo";
	mkfifo(myfifo, 0666);
	char *lineNo=(char*)calloc(20, sizeof(char));
    // open pipe only for writing
	npipefd = open(myfifo, O_WRONLY);
	// assign line value given as a parameter to lineNo 
	lineNo=intstr(line);
	// concat character value (x,y,x)
	strcat(lineNo, character);
	write(npipefd, lineNo, sizeof(lineNo));
	close(npipefd);
	char *lineValue=(char*)calloc(10, sizeof(char));
    //read line value from pipe
	npipefd = open(myfifo, O_RDONLY);
	read(npipefd, lineValue, sizeof(lineValue));
	close(npipefd);
	int lineValueInt=strint(lineValue);
	return lineValueInt;
}
//int str cevrim

char *intstr(int number)
{
	int count=0;
	int numbertmp=number;
	while(numbertmp>0)
	{
		int digit= numbertmp%10;
		numbertmp/=10;
		count++;
	}
	char * value= (char * ) calloc (count,sizeof(unsigned char)  );
	numbertmp=number;
	count--;
	while(numbertmp>0)
	{
		int digit= numbertmp%10;
		numbertmp/=10;
		char x=(char) 48+digit;
		*(value+count)=x;
		count--;
	}

	return value;
}
//str int cevrim
int strint( char* charnums)
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
			exit(0);
			printf("\nGecersiz islem");
			break;
		}
	}
	return number;
}

