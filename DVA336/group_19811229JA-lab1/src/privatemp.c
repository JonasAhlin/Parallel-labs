#include <stdio.h>
#include <omp.h>

int tmp = 1000;

int main()
{
	int i;
	int loop_limit = 10;
	
  	omp_set_num_threads(2);
	
	#pragma omp parallel for firstprivate(tmp) lastprivate(tmp)
	for (i=0; i<loop_limit; ++i)
	{
		printf("Thread %d got the sum %d\n", omp_get_thread_num(), omp_get_thread_num() + ++tmp + i);
	}
		
	printf("After the parallel region, tmp has the value %d\n", tmp);
	
	return 0;
}
