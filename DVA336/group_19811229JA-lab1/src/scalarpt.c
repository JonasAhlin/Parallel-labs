#include <pthread.h>
#include <stdio.h>
#include "timer.h"

#define n 1000000L

#define NUM_THREADS	4
pthread_mutex_t mutexsum;

unsigned long long result = 0;
int A[n], B[n];

void *dotProduct(void * args) {
	int offset = (int)args;
	int sum = 0;
	int start = offset * n/NUM_THREADS;
	int end = start + n/NUM_THREADS;
	for (int i = start; i < end; i++) {
		sum += A[i]*B[i];
	}
	pthread_mutex_lock(&mutexsum);
	result += sum;
	pthread_mutex_unlock(&mutexsum);
}

int main()
{
	int i, time;
	
	/* Vector initialization */
	for (i=0; i<n; ++i)
	{
		A[i] = i % 100;
		B[i] = (i+23) % 10;
	}
	
	time = timer();
	/* Insert your code here */
	
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

	int rc;
	pthread_t threads[NUM_THREADS];
	for (i = 0; i<NUM_THREADS; i++) {
		rc = pthread_create(&threads[i], NULL, dotProduct, (void*)i);
	}
	result = result + result;
	if (rc) {
		printf("ERROR; return code from pthread_create() is %d\n", rc);
	}
	for (i=0; i<NUM_THREADS; i++) {
		pthread_join(threads[i], NULL);
	}

	
	time = timer() - time;
	
	printf("The scalar product A dot B is %lld\n", result);
	print_time(time);
	
	pthread_exit(NULL);
	return 0;
}
