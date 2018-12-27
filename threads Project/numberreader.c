#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <ctype.h> 
char *trim(char *str);
int main(void)
{
	// read file one time and hide line values in numbers array
	int size=100;  // number of lines in the file
	char *numbers [size]; //  line values  
    // variables needed for reading  numbers file 
	FILE * fp;
	char * line = NULL;
	size_t len = 0;
	ssize_t read1;
	int i=1;
	fp = fopen("numbers.txt", "r");
	if (fp == NULL)
		exit(EXIT_FAILURE);

	while ((read1 = getline(&line, &len, fp)) != -1) {
		numbers[i] = malloc(10 * sizeof(char));
		strcpy(numbers[i], trim(line));
		i++;
	}
	fclose(fp);
	if (line)
		free(line);
   // named pipe initilaization
	int npipefd;
    //path of named pipe 
	char * myfifo = "/tmp/myfifo";
	mkfifo(myfifo, 0666);

	char *lineNo=(char*)calloc(10, sizeof(char));
	int counter=1;
    //work as a servise for xyz totalizer program
	while (1)
	{
        //read selected row value from pipe and assign it to lineNo variable 
        // lineNo contains 2 part 1.line number 2.name of the variable (x,y,z)
		npipefd = open(myfifo,O_RDONLY);
		read(npipefd, lineNo, 10);
		close(npipefd);
        //convert lineNo from string to int to use it as index
		int i= atoi(lineNo);
		while(isdigit(lineNo[counter])){
            counter++; 
		}
		printf("%c = %s \n",lineNo[counter], numbers[i]);
		
        //write result to pipe
		npipefd = open(myfifo,O_WRONLY);
		write(npipefd, numbers[i], 10);
		close(npipefd);
		sleep(1);
	}
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


