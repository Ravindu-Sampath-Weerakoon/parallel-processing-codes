#include <stdio.h>
#include <cuda_runtime.h>

// The GPU kernel definition
__global__ void mykernel(void) {
    printf("Hello world\n");
}

int main() {
    // Launch the kernel with 1 block containing 10 threads
    mykernel<<<1, 10>>>();
    
    // Wait for the GPU to finish before the CPU exits
    cudaDeviceSynchronize();
    
    return 0;
}