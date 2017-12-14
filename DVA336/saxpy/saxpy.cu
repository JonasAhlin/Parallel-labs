#include "cuda_runtime.h"
//#include "device_launch_parameters.h"


__global__ void krnl_SAXPY(float a, float * x, int n, float * y) {
    int id = threadIdx.x + blockIdx.x * blockDim.x;
	int st = blockDim.x * gridDim.x;

    while (id < n) {
        y[id] = a * x[id] + y[id];
        id += st;
    }    
}

void computeSAXPY_CUDA(float a, float * x, int n, float * y) {
	float * dev_x;
    float * dev_y;
	
	// Allocate device memory
	cudaMalloc((void **)&dev_x, n * sizeof(float));
	cudaMalloc((void **)&dev_y, n * sizeof(float));
	
	// Initialize device buffers
	cudaMemcpy(dev_x, x, n * sizeof(float), cudaMemcpyHostToDevice);
	cudaMemcpy(dev_y, y, n * sizeof(float), cudaMemcpyHostToDevice);
		    
	// Launch kernel
	krnl_SAXPY<<<128, 256>>>(a, dev_x, n, dev_y);

	// Read back the computed result from the device
	cudaMemcpy(y, dev_y, n * sizeof(float), cudaMemcpyDeviceToHost);
	
	// Clean up
    cudaFree(dev_x);
	cudaFree(dev_y);
}
