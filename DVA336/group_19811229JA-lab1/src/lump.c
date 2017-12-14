#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>
#include "timer.h"

#define n 2048

long double A[n][n], B[n][n], L[n][n], U[n][n];


int main()
{
	int i,j,k,nthr,time;
	long double error;
	
	nthr = omp_get_max_threads();
	time = timer();
	
	/* Initialization */
	for (i=0; i<n; ++i)
	{
		for (j=0; j<n; ++j)
		{
			A[i][j] = 1.0 / (i+1+j+1);
			B[i][j] = 0.0;
		}
	}
	
	/* LU-factorization */
	for (k=0; k<n; ++k)
	{
		for (i=k+1; i<n; ++i)
		{
			A[i][k] = A[i][k] / A[k][k];
			for (j=k+1; j<n; ++j)
			{
				A[i][j] = A[i][j] - A[i][k] * A[k][j];
			}
		}
	}
	
	time = timer() - time;
	printf("n=%d,  threads=%d\n",n,nthr);
	print_time(time);
	
	
	/* Check correctness */
	for (i=0; i<n; ++i)
	{
		for (j=0; j<i; ++j)
		{
			L[i][j] = A[i][j];
			U[i][j] = 0.0;
		}
		
		L[i][i] = 1.0;
		U[i][i] = A[i][i];
		
		for (j=i+1; j<n; ++j)
		{
			L[i][j] = 0.0; 
			U[i][j] = A[i][j];
		}
	}

	for (i=0; i<n; ++i)
	{
		for (k=0; k<n; ++k)
		{
			for (j=0; j<n; ++j)
			{
				B[i][j] = B[i][j] + L[i][k] * U[k][j];
			}
		}
	}
	
	error = 0.0;
	
	for (i=0; i<n; ++i)
	{
		for (j=0; j<n; ++j)
		{
			error = error + fabsl( 1.0/(i+1+j+1) - B[i][j] );
		}
	}
	
	printf("Error is: %Le\n", error);
	
	return 0;
}
