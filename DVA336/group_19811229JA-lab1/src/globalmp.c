#include <stdio.h>
#include "timer.h"
#include <omp.h>


/* Number of array elements */
#define N 100000000

int array[N];


void check_array()
{
	int i;
	for (i=0; i<N; ++i)
		if (array[i] != i)
	{
		printf("Not "); 
		break;
	}
	printf("Correct\n");
}

int main()
{
	int i, time;
	int nthreads, tid;
	
	time = timer();
	
	#pragma omp parallel for
		for (i=0; i<N; ++i) {
			array[i] = i;
		}	
	time = timer() - time;
	print_time(time);
	check_array();
	
	
	return 0;
}
