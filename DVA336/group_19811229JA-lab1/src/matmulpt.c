#include <stdio.h>
#include "timer.h"


#define n 2000

double A[n][n];
double B[n][n];
double C[n][n];


int main()
{
	int i,j,k;
	int time;
	
	/* Init */
	for (i=0; i<n; ++i)
		for (j=0; j<n; ++j)
		{
			A[i][j] = (i%1000)/1000.0;
			B[i][j] = (j%1000)/1000.0;
			C[i][j] = 0.0;
		}
	
	time = timer();
	
	/* Matrix multiplication */
	for (i=0; i<n; ++i)
	{
		for (j=0; j<n; ++j)
		{
			for (k=0; k<n; ++k)
			{
				C[i][j] += A[i][k] * B[k][j];
			}
		}
	}
	
	time = timer() - time;
	print_time(time);
	
	return 0;
}
