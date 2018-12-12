#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
int main()
{
srand(time(NULL));   // Initialization, should only be called once.

// the first digit detrmine row or column if row  0 if column  1
// second digit  index of selected row or column
int arr[6] = {00, 01,02,10, 11,12 };

int  r = rand() %6; // random index from arr
// writing random value to named pipe
write(4, &arr[r], sizeof(int));
 return 0;
} 