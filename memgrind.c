#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 
#include <math.h>
#include "mymalloc.h"

void firstWorkload(){

int i;
void* arr[4096];
for(i = 0; i<150; i++)
	{
	arr[i] = malloc(1);
	free(arr[i]); 
	}

}

void secondWorkload(){

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



} 

void thirdWorkload(){}




int main() {
//perform all workloads

//A 

firstWorkload();


secondWorkload();
}





