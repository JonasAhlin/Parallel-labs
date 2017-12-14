#include <stdio.h>
#include <omp.h>


void func1()
{
	printf("Thread %d is handling func1\n", omp_get_thread_num());
}

void func2()
{
	printf("Thread %d is handling func2\n", omp_get_thread_num());
}

void func3()
{
#pragma omp parallel
	printf("Thread %d is handling func3\n", omp_get_thread_num());
}

void func4()
{
	printf("Thread %d is handling func4\n", omp_get_thread_num());
}


int main()
{
	omp_set_num_threads(4);
	omp_set_nested(1);
	
	#pragma omp sections
	{
		#pragma omp section
		func1();
		#pragma omp section	
		func2();
		#pragma omp section
		func3();
		#pragma omp section
		func4();
	}
	return 0;
}
