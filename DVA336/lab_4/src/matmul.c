#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define DIM 1000

/* 
* Statically allocate the matrices to make the rows 
* sequentially placed in memory. (This eases the task
* of distributing the problem among the slaves.)
* Make the matrices global to allow for larger 
* dimensions. 
*/
int A[DIM][DIM];
int B[DIM][DIM];
int C[DIM][DIM];
int D[DIM][DIM];

int correct_result(int A[DIM][DIM], int B[DIM][DIM])
{
	int i,j;
	for (i=0; i<DIM; ++i)
		for (j=0; j<DIM; ++j)
			if (A[i][j] != B[i][j])
				return 0;
	return 1;
}


int main (argc, argv)
int argc;
char *argv[];
{
	int rank=0, size;
	int i, j, k;
	int time1;
	volatile int tmp;
	
	srand(time(NULL));
	for(i=0; i<DIM; ++i)
	{
		for (j=0; j<DIM; ++j)
		{
			A[i][j] = random() % 100 - 50;
			B[i][j] = random() % 100 - 50;
		}
	}
	
	/* Calculate the true answer */
	for (i=0; i<DIM; ++i)
		for (k=0; k<DIM; ++k)
			for (j=0; j<DIM; ++j)
				D[i][j] += A[i][k] * B[k][j];
	
	
	time1 = timer();
	
	
	/* Put your code here: */
	
	

	
	
	/* Error checking */
	time1 = timer() - time1;
	printf ("Your calculation is %scorrect.\n", correct_result(C,D) ? "" : "not ");
	printf ("Total runtime: %f seconds\n", time1/1000000.0);
	
	return 0;
}
