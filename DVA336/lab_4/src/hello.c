#include <stdio.h>
#include <mpi.h>


int main (argc, argv)
     int argc;
     char *argv[];
{
	int rank, size;
	int i;
	int time;
	volatile int a;

	MPI_Init (&argc, &argv);	/* starts MPI */
	MPI_Comm_rank (MPI_COMM_WORLD, &rank);	/* get current process id */
	MPI_Comm_size (MPI_COMM_WORLD, &size);	/* get number of processes */
	
	if (rank == 0)
		time = timer();
	
	
	
	/* You should change this piece of code: */
	/*---------------------------------------------*/
	printf( "Hello world from process %d of %d\n", rank, size );
	/* Do some work before saying goodbye */
	for (i=0; i<10000000; ++i)
		a=1;
	printf( "Goodbye world from process %d of %d\n", rank, size );
	/*---------------------------------------------*/
	
	
	
	if (rank == 0)
	{
		time = timer() - time;
		printf("Total runtime: %f seconds\n", time/1000000.0);
	}
	
	MPI_Finalize();
	return 0;
}
