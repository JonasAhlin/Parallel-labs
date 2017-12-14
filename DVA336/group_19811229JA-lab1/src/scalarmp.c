#include <omp.h>
#include <stdio.h>
#include "timer.h"

#define n 1000000L
#define NUM_THREADS	4

unsigned long long result, sum = 0;
int A[n], B[n];

void dotProd() {
	int start, end, tid;
	tid = omp_get_thread_num();
	start = tid * n/NUM_THREADS;
	end = start + n/NUM_THREADS;
	printf("Start of thread %i = %i\n", tid, start);
	printf("End of thread %i = %i\n", tid, end);

	#pragma omp for
	for (int i=start; i<end; i++)
	{
		sum += A[i]*B[i];
	}
	#pragma omp critical
	result += sum;
}

int main()
{
	int i, time;
	
	/* Vector initialization */
	for (i=0; i<n; ++i)
	{
		A[i] = i % 100;
		B[i] = (i+23) % 10;
	}
	
	time = timer();
	/* Insert your code here */
	omp_set_num_threads(NUM_THREADS);
	
	#pragma omp parallel private(sum) reduction(+:result)
	{	
		/*tid = omp_get_thread_num();
		start = tid * n/NUM_THREADS;
		end = start + n/NUM_THREADS;
		printf("Start of thread %i = %i\n", tid, start);
		printf("End of thread %i = %i\n", tid, end);

		#pragma omp for ordered
		for (i=start; i<end; i++)
		{
			sum += A[i]*B[i];
		}
		*/
		dotProd();
	
	}

	time = timer() - time;
	
	printf("The scalar product A dot B is %lld\n", result);
	print_time(time);
	
	return 0;
}
