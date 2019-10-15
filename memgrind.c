#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 
#include <math.h>
#include <sys/time.h>
#include "mymalloc.h"


double firstWorkload(){

	struct timeval start, end;

	gettimeofday(&start, NULL);

	int i;
	char * arr[4096];
	
		for(i = 0; i<150; i++)
		{
			arr[i] =(char*)malloc(1);
			free(arr[i]); 
		}


		gettimeofday(&end, 0);

	double elapsed =(double) (end.tv_usec - start.tv_usec)/1000000 +(double) (end.tv_sec - start.tv_sec);

	return elapsed; 
		}				

double secondWorkload(){

	struct timeval start, end; 

	gettimeofday(&start, 0);

	//implement second workload












	gettimeofday(&end, 0);

double elapsed = (double)(end.tv_usec - start.tv_usec)/1000000 +(double)(end.tv_sec - start.tv_sec);

return elapsed; 

} 

void thirdWorkload(){}



int main() {
	
	double timeOne = 0;
	double timeTwo = 0;
	double timeThree = 0;

	int i;
	for (i=0; i<100; i++){
		timeOne = timeOne + firstWorkload();
		
		}
	printf("\nAverage time taken for workload 1 is: %f", timeOne/100);
	printf("\nAverage time taken for workload 2 is: %f", timeTwo/100);

}


