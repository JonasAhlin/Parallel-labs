#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "saxpy.h"

const int N = 1000 * 1000 * 10;

void copyArr(float * arr, int n, float * b) { 
	for (int i=0; i<n; i++) { 
		b[i] = arr[i]; 
	}
}

void randArr(float * arr, int n) {
	for (int i=0; i<n; i++) { 
		arr[i] = 10.0f * (float)rand() / (float)RAND_MAX;
	}
}

void compareArrays(float * a, float * b, int n, float & maxDiff, int & diffCnt) {
	float eps = 0.00001f;
	diffCnt = 0;
	maxDiff = 0.f;

	for (int i=0; i<n; i++) {
		float diff = fabs(a[i] - b[i]);
		if (diff > eps) diffCnt++;
		if (diff > maxDiff) maxDiff = diff;
	}
}

void main() {	
	// Allocate host data
	float a = 2.5f;
	float * x = (float *) malloc(N * sizeof(float));
	float * y = (float *) malloc(N * sizeof(float));
	float * y_in = (float *) malloc(N * sizeof(float));	
	float * y_ref = (float *) malloc(N * sizeof(float));
	
	// Generate input data
	randArr(x, N);
	randArr(y_in, N);
	
	// Run GPU computation
	copyArr(y_in, N, y);
	computeSAXPY_CUDA(a, x, N, y); 

	// Run reference cpu computation 
	copyArr(y_in, N, y_ref);
	computeSAXPY_Ref(a, x, N, y_ref); 

	// Measure execution times and report results here ...
	printf("Problem size n == %d\n\n", N);
	
		
	// Verify correctness of computation
	float maxDiff;
	int diffCnt;
	compareArrays(y, y_ref, N, maxDiff, diffCnt);
	printf("Number of elementwise differences: %d\n", diffCnt);
	printf("Maximum elementwise difference: %f\n", maxDiff);
	printf("\n");
	
	// Clean up
    free(x);
	free(y);
	free(y_in);	
	free(y_ref);	
}