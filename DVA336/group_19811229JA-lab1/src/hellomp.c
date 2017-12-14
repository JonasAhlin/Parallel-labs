#include <stdio.h>
#include <omp.h>


int main()
{
	int i;
	volatile int a;
	int nthreads, tid;

	omp_set_dynamic(0);
	#pragma omp parallel private(nthreads,tid) num_threads(4)
	{
		tid = omp_get_thread_num();
		nthreads = omp_get_num_threads();
		/* Dummy work */
		for (i=0; i<10000000; ++i)
			a=i;
		printf("Hello World! %i, %i\n", tid, nthreads);
		
		#pragma omp single nowait
		{
			printf("Only one thread says this.\n");
		}
		
		printf("Goodbye World...%i, %i\n", tid, nthreads);
	}
	
	return 0;
}
