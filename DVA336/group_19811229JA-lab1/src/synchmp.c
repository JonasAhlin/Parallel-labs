#include <stdio.h>
#include <omp.h>


#define P 3
long interval[P];

int power(int base, int exp)
{
	int i,tmp=1;
	for (i=0; i<exp; ++i)
	{
		tmp *= base;
	}
	return tmp;
}

int main()
{
	int i;

	for (i=0; i<P; ++i)
	{
		interval[i] = 1000*power(10,i);
	}

	omp_set_num_threads(P);

	#pragma omp parallel private(i)
	{
		for (i=1; i<=interval[omp_get_thread_num()]*5; ++i)
		{
			if (i % interval[omp_get_thread_num()] == 0)
			{
				#pragma omp barrier
				printf("Thread with interval %ld is at %d\n", interval[omp_get_thread_num()], i);
			}
		}

		printf("Done\n");
	}
}
