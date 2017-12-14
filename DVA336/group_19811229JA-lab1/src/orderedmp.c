#include <stdio.h>
#include <omp.h>


int main()
{
	int i;
	int loop_limit = 16;
	
	omp_set_num_threads(4);
	
	#pragma omp parallel
	{
		#pragma omp for
		for (i=0; i<loop_limit; ++i)
		{
			printf("Thread %d: The value of i is %d\n", omp_get_thread_num(), i);
		}
	}
	return 0;
}
