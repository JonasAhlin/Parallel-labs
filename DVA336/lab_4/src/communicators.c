#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <mpi.h>

int main (argc, argv)
     int argc;
     char *argv[];
{
	// MPI_COMM_WORLD info
	int world_rank = -1, world_size = -1;
	MPI_Group world_group;
	
	// first level ranks, group and comm, based on MPI_COMM_WORLD
	int * ranks11;
	int * ranks12;
	int * ranks13;
	int size11;
	int size12;
	int size13;
	MPI_Comm comm1;
	MPI_Group group1;
	
	// Uncomment and use these variables in case you want to do the voluntary exercise
	// second level ranks, group and comm
// 	int myrank11 = -1;
// 	int * ranks21;
// 	int * ranks22;
// 	int size21;
// 	int size22;
// 	MPI_Comm comm2;
// 	MPI_Group group2;
	
	// group local rank
	int local_rank = -1;
	
	// loop iterator and variable
	long long i;
	volatile int k;
	
	MPI_Init (&argc, &argv);	/* starts MPI */
	MPI_Comm_rank (MPI_COMM_WORLD, &world_rank);	/* get current process id */
	MPI_Comm_size (MPI_COMM_WORLD, &world_size);	/* get number of processes */
	
	// Put your code here
	
	
	
	
	
	
	
	
	// Uncomment this code in case you want to do the voluntary exercise
	// Determine local rank
// 	if (world_rank%3 == 0)
// 		MPI_Group_rank(group2, &local_rank);
// 	else
		MPI_Group_rank(group1, &local_rank);
	
	printf("Process with world rank %2d, local rank %2d, starts.\n", world_rank, local_rank);
	
	for (i=0; i<((1+world_rank%3)*100000000L); ++i)
		k = i*i*i;
	
	// Uncomment this code in case you want to do the voluntary exercise
// 	if (world_rank%3 == 0)
// 		MPI_Barrier(comm2);
// 	else
		MPI_Barrier(comm1);
	
	printf("Process with world rank %2d, local rank %2d, ends.\n", world_rank, local_rank);
	
	MPI_Finalize();
	return 0;
}
