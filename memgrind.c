#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 
#include <math.h>
#include <sys/time.h>
#include "mymalloc.h"

double firstWorkload(){
	printf("WORKLOAD1\n");

	struct timeval start, end;
	gettimeofday(&start, NULL);

	int i;
	char * arr[150];
	//Each iteration, malloc and free
	for(i = 0; i < 150; ++i) {
		printf("\n%d\n", i);
		arr[i] =(char*)malloc(1);
		free(arr[i]); 
	}

	gettimeofday(&end, 0);
	double elapsed =(double) (end.tv_usec - start.tv_usec)/1000000 +(double) (end.tv_sec - start.tv_sec);
	return elapsed; 
}				

double secondWorkload(){
	printf("WORKLOAD2\n");

	struct timeval start, end; 
	gettimeofday(&start, 0);

	int i;
	int j;
	char * arr[150];
	for (i = 0; i < 150; ++i) {
		printf("\n%d\n", i);
		arr[i] = (char*)malloc(1);
		//Every 50, go back and free
		if (i % 50 == 49) {
			for (j = i-50+1; j < i+1; j++) {
				free(arr[j]);
			}
		}
	}

	gettimeofday(&end, 0);
	double elapsed = (double)(end.tv_usec - start.tv_usec)/1000000 +(double)(end.tv_sec - start.tv_sec);
	return elapsed; 

} 

void thirdWorkload(){}



int main()
{	
	double timeOne = 0;
	double timeTwo = 0;
	double timeThree = 0;

	int i;
	for (i=0; i<1; ++i){
		timeOne = timeOne + firstWorkload();
	}
	for (i=0; i<1; ++i) {
		timeTwo = timeTwo + secondWorkload();
	}
	printf("\nAverage time taken for workload 1 is: %f", timeOne/100);
	printf("\nAverage time taken for workload 2 is: %f", timeTwo/100);
	printf("\nAverage time taken for workload 3 is: %f", timeThree/100);
}


