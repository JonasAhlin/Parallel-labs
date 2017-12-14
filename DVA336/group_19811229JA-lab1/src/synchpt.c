#include <stdio.h>
#include <pthread.h>

#define P 3

pthread_barrier_t barrier;

/* The function executed by each thread */
void * body(void * args)
{
	int interval = * (int*) args;
	int i;

	for (i=1; i<=interval*5; ++i)
	{
		if (i % interval == 0)
		{
			pthread_barrier_wait(&barrier);
			printf("Thread with interval %d is at %d\n", interval, i);
		}
	}

	printf("Done\n");

	return NULL;
}



int main()
{
	pthread_t thread[P];
	pthread_attr_t attr;
	int i, barr;
	int interval=100;

	/* Initiate the thread attributes */
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	//initiate barrier
	barr = pthread_barrier_init(&barrier, NULL, P);

	/* Create and run the threads */
	for (i=0; i<P; ++i)
	{
		interval *= 10;
		pthread_create(&thread[i], &attr, body, (void*) &interval);
	}

	/* Join the threads - barrier*/
	for (i=0; i<P; ++i)
	{
		pthread_join(thread[i], NULL);
	}

	pthread_barrier_destroy(&barrier);
	pthread_exit(NULL);
	return 0;
}
