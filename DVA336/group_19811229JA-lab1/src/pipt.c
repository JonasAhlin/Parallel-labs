#include <stdio.h>
#include "timer.h"

#define n 100000000L
long double pi = 0.0;


int main()
{
	int i, time;
	
	time = timer();
	/* Put your code here */	
	
	
	
	time = timer() - time;
	
	printf("The calculated value of PI is %.15llf\n", pi);
	printf("The   target   value of PI is 3.141592653589793\n");
	print_time(time);
	
	return 0;
}
