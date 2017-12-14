#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

#define READERS 8
#define WRITERS 6
#define BUFFER_SIZE 3


/* Circular buffer */
int buffer[BUFFER_SIZE];
int buffer_count = 0;
int put_index=0;
int get_index=0;



void * reader_body(void * args)
{
	int i;
	int tmp; /* Store the read value from the buffer in this variable */
	
	for (i=0; i<WRITERS; ++i)
	{
		/* Put your code here */
		
		
		sleep(2);
	}
	
	/* Return the last value read */
	return (void *) tmp;
}

void * writer_body(void * args)
{
	int i;
	int tmp;
	
	/* Seed the random number generator */
	srand(time(NULL));
	
	for (i=0; i<READERS; ++i)
	{
		tmp = random(); /* Number to be written to the buffer */
		
		/* Put your code here */
		
		
		sleep(1);
	}
	
	/* Return the last value written */
	return (void *) tmp;
}


int main()
{
	int i;
	pthread_t readers[READERS];
	pthread_t writers[WRITERS];
	
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	void * status;
	
	
	for (i=0; i<READERS; ++i)
	{
		pthread_create(&readers[i], &attr, reader_body, NULL);
	}
	
	for (i=0; i<WRITERS; ++i)
	{
		pthread_create(&writers[i], &attr, writer_body, NULL);
	}
	
	for (i=0; i<WRITERS; ++i)
	{
		pthread_join(writers[i], &status);
		printf("Writer value returned: %10d\n", (int) status);
	}
	
	for (i=0; i<READERS; ++i)
	{
		pthread_join(readers[i], &status);
		printf("Reader value returned: %10d\n", (int) status);
	}
	
	pthread_attr_destroy(&attr);
	
	
	return 0;
}
