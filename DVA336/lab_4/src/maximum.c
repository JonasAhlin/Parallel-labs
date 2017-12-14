#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <mpi.h>

#define PROBLEM_SIZE 100000000

int main (argc, argv)
     int argc;
     char *argv[];
{
	int rank, size;
	int i;
	int * problem;
	int * my_problem;
	int actual_max = INT_MIN;
	int my_max = INT_MIN;
	int all_max = INT_MIN;
	int tmp;
	int time;

	MPI_Init (&argc, &argv);	/* starts MPI */
	MPI_Comm_rank (MPI_COMM_WORLD, &rank);	/* get current process id */
	MPI_Comm_size (MPI_COMM_WORLD, &size);	/* get number of processes */
	
	
	
	/* The master process initiates the problem... */
	/* The wrong way! */
// 	if (rank == 0)
// 	{
// 		problem = (int *) malloc (PROBLEM_SIZE* sizeof(int));
// 		for (i=0; i<PROBLEM_SIZE; ++i)
// 		{
// 			tmp = i+1;
// 			problem[i] = tmp;
	// 			/* ... and keeps track of the actual maximum */
// 			if (actual_max < tmp)
// 			{
// 				actual_max = tmp;
// 			}
// 		}
// 	}
	
	
	
	/* The master process initiates the problem... */
	/* The correct way! */
	if (rank == 0)
	{
		// Allocate more elements than needed in order make MPI_Scatter safe
		problem = (int *) malloc ((PROBLEM_SIZE + size - PROBLEM_SIZE % size)* sizeof(int));
// 		srand(time(NULL));
		for (i=0; i<PROBLEM_SIZE; ++i)
		{
			tmp = i+1;
// 			tmp = random();
			problem[i] = tmp;
			/* ... and keeps track of the actual maximum */
			if (actual_max < tmp)
			{
				actual_max = tmp;
			}
		}
		
		// Do not take the extra elements into account
		for (; i<PROBLEM_SIZE + size - PROBLEM_SIZE % size; ++i)
		{
			problem[i] = INT_MIN;
		}
	}
	
	
	
	/* All processes allocate space for their subproblem. */
	my_problem = (int *) malloc ((PROBLEM_SIZE/size+1)*sizeof(int));
	for (i=0; i<PROBLEM_SIZE/size+1; ++i)
	{
		my_problem[i] = INT_MIN;
	}
	
	
	if (rank == 0)
		time = timer();
	
	/* Your job is to distribute the problem among the processes and to 
	* derive the maximum value in the array.
	* Store the found maximum in all_max and use my_max as a local 
	* maximum for each process. 
	* Put your code here:                                              */
	
	
	
	
	
	
	/* Let the master thread print the found maximum value */
	if (rank == 0)
	{
		time = timer() - time;
		printf("The found maximum is  %11d\nThe actual maximum is %11d\n", all_max, actual_max);
		printf("Total runtime: %f seconds\n", time/1000000.0);
	}
	
	MPI_Finalize();
	return 0;
}
