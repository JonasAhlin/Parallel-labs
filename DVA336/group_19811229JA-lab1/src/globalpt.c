#include <stdio.h>
#include "timer.h"
#include <pthread.h>

/* Number of threads */
#define P 4
/* Number of array elements */
#define N 100000003

int array[N];
int put_index = 0;


pthread_mutex_t mutexput;

/* The function executed by each thread */
void * body(void * args)
{
	int id = (int)args;

	//pthread_mutex_lock(&mutexput);
	while (1)
	{
		if (put_index + id >= N)
		{
			break;
		}
		array[put_index + id] = put_index + id;
		++put_index;
	}
	//pthread_mutex_unlock(&mutexput);

	return NULL;
}

void check_array()
{
	int i;
	for (i=0; i<N; ++i)
		if (array[i] != i)
		{
			printf("Not "); 
			break;
		}
	printf("Correct\n");
}

int main()
{
	pthread_t thread[P];
	pthread_attr_t attr;
	int i, time;
		
	//initiate mutex
	pthread_mutex_init(&mutexput, NULL);

	/* Initiate the thread attributes */
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	
	time = timer();
	/* Create and run the threads */
	for (i=0; i<P; i++)
	{
		pthread_create(&thread[i], &attr, body, (void*)i);
	}
	
	/* Join the threads - barrier*/
	for (i=0; i<P; i++)
	{
		pthread_join(thread[i], NULL);
	}
	
	time = timer() - time;
	print_time(time);
	check_array();
	
	pthread_mutex_destroy(&mutexput);
	pthread_exit(NULL);
	return 0;
}
