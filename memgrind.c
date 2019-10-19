#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 
#include <math.h>
#include <sys/time.h>
#include "mymalloc.h"

double firstWorkload()
{
	struct timeval start, end;
	gettimeofday(&start, NULL);

	int i;
	char * arr[150];
	//Each iteration, malloc and free
	for(i = 0; i < 150; ++i) {
		arr[i] =(char*)malloc(1);
		free(arr[i]); 
	}

	gettimeofday(&end, 0);
	double elapsed = (double)(end.tv_usec - start.tv_usec)/1000000 + (double)(end.tv_sec - start.tv_sec);
	return elapsed; 
}				

double secondWorkload()
{
	struct timeval start, end; 
	gettimeofday(&start, 0);

	int i;
	int j;
	char * arr[150];
	for (i = 0; i < 150; ++i) {
		arr[i] = (char*)malloc(1);
		//Every 50, go back and free
		if (i % 50 == 49) {
			for (j = i-50+1; j < i+1; j++) {
				free(arr[j]);
			}
		}
	}

	gettimeofday(&end, 0);
	double elapsed = (double)(end.tv_usec - start.tv_usec)/1000000 + (double)(end.tv_sec - start.tv_sec);
	return elapsed; 

} 

double thirdWorkload()
{
	struct timeval start, end;
	gettimeofday(&start, 0);

	int i = 0;
	char* data[50];
	int option;
	int nMalloc = 0;
	while (nMalloc < 50) { //repeat until malloc 50 times
		option = rand() % 2;
		if (option) {
			data[i] = (char*)malloc(1);
			++i;
			++nMalloc;
		} else if (i > 0) { //Only free if allocated
			free(data[i-1]);
			--i;
		}
	}

	//Free all remaining data
	while (i > 0) {
		free(data[i-1]);
		--i;
	}

	gettimeofday(&end, 0);
	double elapsed = (double)(end.tv_usec - start.tv_usec)/1000000 + (double)(end.tv_sec - start.tv_sec);
	return elapsed;
}

double fourthWorkload()
{
	struct timeval start, end;
	gettimeofday(&start, 0);

	int i = 0;
	char* data[50];
	int usage[50];
	int option;
	int nMalloc = 0;
	int space = 4096;

	while (nMalloc < 50) {
		option = rand() % 2;
		if (option) {
			int size = (rand() % 63) + 1;
			if (space - size - 4 >= 0) { //NOTE: 4 is sizeof(metadata)
				data[i] = (char*)malloc(size);
				space = space - size - 4; //
				usage[i] = size;
				++i;
				++nMalloc;
			}
		} else if (i > 0) {
			space = space + usage[i-1] + 4; //
			free(data[i-1]);
			--i;
		}
	}

	while (i > 0) {
		free(data[i-1]);
		--i;
	}

	gettimeofday(&end, 0);
	double elapsed = (double)(end.tv_usec - start.tv_usec)/1000000 + (double)(end.tv_sec - start.tv_sec);
	return elapsed;
}

double fifthWorkload()
{
	struct timeval start, end;
	gettimeofday(&start, 0);

	int i;
	char * data[150];
	for (i=0; i < 150; i++) {
		data[i] = (char*)malloc(1);
	}
	for (i=0; i < 150; i = i + 4) { //Free normally
		free(data[i]);
	}
	for (i=1; i < 150; i = i + 4) { //Test merging down
		free(data[i]);
	}
	for (i=3; i < 150; i = i + 4) { //Test merging up
		free(data[i]);
	}
	for (i=2; i < 150; i = i + 4) { //Test merging up and down at the same time
		free(data[i]);
	}

	gettimeofday(&end, 0);
	double elapsed = (double)(end.tv_usec - start.tv_usec)/1000000 + (double)(end.tv_sec - start.tv_sec);
	return elapsed;
}

double sixthWorkload()
{
	struct timeval start, end;
	gettimeofday(&start, 0);

	int i;
	char* data[150];
	for (i=0; i < 150; i = i + 1) {
		data[i] = (char*)malloc(1);
	}
	for (i=148; i >= 0; i = i - 1) { //tests merging node3 into node2
		free(data[i]);
	}
	free(data[149]); //tests freeing in bulk

	gettimeofday(&end, 0);
	double elapsed = (double)(end.tv_usec - start.tv_usec)/1000000 + (double)(end.tv_sec - start.tv_sec);
	return elapsed;
}


int main()
{	
	double timeOne = 0;
	double timeTwo = 0;
	double timeThree = 0;
	double timeFour = 0;
	double timeFive = 0;
	double timeSix = 0;

	int i;
	for (i=0; i<100; ++i) {
		timeOne = timeOne + firstWorkload();
	}
	for (i=0; i<100; ++i) {
		timeTwo = timeTwo + secondWorkload();
	}
	for (i=0; i<100; ++i) {
		timeThree = timeThree + thirdWorkload();
	}
	for (i=0; i<100; ++i) {
		timeFour = timeFour + fourthWorkload();
	}
	for (i=0; i<100; ++i) {
		timeFive = timeFive + fifthWorkload();
	}
	for (i=0; i<100; ++i) {
		timeSix = timeSix + sixthWorkload();
	}
	printf("\nAverage time taken for workload 1 is: %f", timeOne/100);
	printf("\nAverage time taken for workload 2 is: %f", timeTwo/100);
	printf("\nAverage time taken for workload 3 is: %f", timeThree/100);
        printf("\nAverage time taken for workload 4 is: %f", timeFour/100);
        printf("\nAverage time taken for workload 5 is: %f", timeFive/100);
        printf("\nAverage time taken for workload 6 is: %f", timeSix/100);
}


