#include <stdio.h>
#include <pthread.h>

/* The function executed by each thread */
void * body(void * args)
{
	/* Dummy work */
	int i;
	volatile int a;
	for (i=0; i<10000000; ++i)
		a=i;
	/* Dummy work done */

	int id = (int)args;
	printf("Hello World! %i, 20\n", id);
	return NULL;
}

int main()
{
	const int num_threads = 20;
	pthread_t thread[num_threads];
	pthread_attr_t attr;
	int ID;
	int i;
	
	/* Initiate the thread attributes */
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	
	/* Create and run the threads */
	for (i=0; i<num_threads; i++)
	{
		ID = pthread_create(&thread[i], &attr, body, (void *)i);
	}
	
	/* Join the threads - barrier*/
	for (i=0; i<num_threads; i++)
	{
		pthread_join(thread[i], NULL);
	}
	
	printf("Goodbye World...\n");
	
	//pthread_exit(NULL);
	return 0;
}
