#include <stdio.h>
#include <cuda_runtime.h>

// CUDA Kernel for parallel reduction using shared memory
__global__ void sumReduction(const int *d_input, int *d_output, int n) {
    // Allocate shared memory for the threads in this block
    __shared__ void* shared_mem; // Dummy declaration if needed, or explicit size:
    extern __shared__ int sdata[];

    unsigned int tid = threadIdx.x;
    unsigned int i = blockIdx.x * blockDim.x + threadIdx.x;

    // Load elements from global memory into shared memory
    sdata[tid] = (i < n) ? d_input[i] : 0;
    __syncthreads(); // Make sure all data is loaded before starting reduction

    // Do reduction in shared memory (Tree-based approach)
    for (unsigned int s = blockDim.x / 2; s > 0; s >>= 1) {
        if (tid < s) {
            sdata[tid] += sdata[tid + s];
        }
        __syncthreads(); // Synchronize threads after each step of the tree
    }

    // Thread 0 writes the result of this block's reduction to global memory safely
    if (tid == 0) {
        atomicAdd(d_output, sdata[0]);
    }
}

int main() {
    const int n = 1000;
    const int size = n * sizeof(int);

    // Host (CPU) memory allocation
    int h_input[n];
    int h_sum = 0;

    // Initialize array with values 1 to 1000
    for (int i = 0; i < n; i++) {
        h_input[i] = i + 1;
    }

    // Device (GPU) memory pointers
    int *d_input, *d_output;
    cudaMalloc((void**)&d_input, size);
    cudaMalloc((void**)&d_output, sizeof(int));

    // Copy input data from Host to Device, and initialize output to 0
    cudaMemcpy(d_input, h_input, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_output, &h_sum, sizeof(int), cudaMemcpyHostToDevice);

    // Timing events
    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    // Define execution configuration
    int threadsPerBlock = 256;
    int blocksPerGrid = (n + threadsPerBlock - 1) / threadsPerBlock;

    cudaEventRecord(start);

    // Launch the kernel. We pass threadsPerBlock * sizeof(int) for dynamically allocated shared memory
    sumReduction<<<blocksPerGrid, threadsPerBlock, threadsPerBlock * sizeof(int)>>>(d_input, d_output, n);

    cudaEventRecord(stop);
    cudaEventSynchronize(stop);

    // Calculate elapsed time
    float milliseconds = 0;
    cudaEventElapsedTime(&milliseconds, start, stop);

    // Copy the final result back to the Host
    cudaMemcpy(&h_sum, d_output, sizeof(int), cudaMemcpyDeviceToHost);

    // Print benchmarks and results
    printf("Time taken = %f seconds\n", milliseconds / 1000.0);
    printf("Sum = %d\n", h_sum);

    // Free GPU memory
    cudaFree(d_input);
    cudaFree(d_output);

    return 0;
}