#include <omp.h>
#include <stdio.h>

#define n 1000000L
double A[n];

int main()
{
	int i;
	volatile double sum, globsum;
	
	for (i = 0; i < n ; i++) { 
		A[i]=(double)i;
	}
	
	globsum=0.0;
	
	omp_set_num_threads(100);
	
	#pragma omp parallel private(sum)
	{
		sum=0.0;
		
		#pragma omp for
		for (i = 0; i < n ; i++) { 
			sum += A[i];
		}
		
		#pragma omp critical
		globsum+=sum;
	}

	printf("Global sum is: %f\n",  globsum);

	return 0;
}
