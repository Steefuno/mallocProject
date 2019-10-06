#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 
#include <math.h>
#include <sys/time.h>
#include "mymalloc.h"

long firstWorkload(){

struct timeval start, end;

gettimeofday(&start, 0);

int i;
void* arr[4096];
for(i = 0; i<150; i++)
	{
	arr[i] = malloc(1);
	free(arr[i]); 
	}
gettimeofday(&end, 0);

long elapsed = (end.tv_sec - start.tv_sec)*1000000 + end.tv_usec - start.tv_usec;

return elapsed; 
}

long secondWorkload(){

struct timeval start, end; 

gettimeofday(&start, 0);

int i;
int j= 0;
void* arr[4096];
for(i = 0; i<150; i++){

	
	arr[j] = malloc(1);
	if (j == 50)
	{
	//if 50 is reached, then start to free
	j = -1;
	int x;
	for (x = 0; x < 50; x++){
	free(arr[i]);}
	
	}

	j++;
} 

gettimeofday(&end, 0);

long elapsed = (end.tv_sec - start.tv_sec)*1000000 + end.tv_usec - start.tv_usec;

return elapsed; 

} 

void thirdWorkload(){}




int main() {
//perform all workloads

//have to run all workloads 100 times and find the average times 

firstWorkload();


secondWorkload();
}





