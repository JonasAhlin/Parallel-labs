#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define PHILOSOPHERS 5

char forks[PHILOSOPHERS];

void pick_up_fork(int i)
{
	while (forks[i]);
	forks[i] = 1;
}

void put_down_fork(int i)
{
	forks[i] = 0;
}

void eat()
{
	sleep(1);
}

void think()
{
	sleep(1);
}

void * philosopher_body(void * args)
{
	int id = (int) args;
	
	while(1)
	{
		printf("Philosopher %2d will now start to eat.\n", id);
		pick_up_fork(id); /* Left fork */
		sleep(1);
		pick_up_fork((id+1)%PHILOSOPHERS); /* Right fork */
		eat();
		put_down_fork(id);
		put_down_fork((id+1)%PHILOSOPHERS);
		printf("Philosopher %2d has finished eating for now.\n", id);
		think();
	}
	
	return NULL;
}


int main()
{
	int i;
	pthread_t philosopher[PHILOSOPHERS];
	pthread_attr_t attr;
	void * status;
	
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	
	for (i=0; i<PHILOSOPHERS; ++i)
	{
		forks[i] = 0;
	}
	
	for (i=0; i<PHILOSOPHERS; ++i)
	{
		pthread_create(&philosopher[i], &attr,
			       philosopher_body, (void *) i);
	}
	
	for (i=0; i<PHILOSOPHERS; ++i)
	{
		pthread_join(philosopher[i], &status);
	}
	
	pthread_attr_destroy(&attr);
	
	return 0;
}
