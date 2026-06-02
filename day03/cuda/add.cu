#include <stdio.h>
#include <cuda_runtime.h>

// CUDA Kernel function to add elements of two arrays
__global__ void vectorAdd(const int *a, const int *b, int *c, int n) {
    // Calculate the unique global thread ID
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    
    // Boundary check to avoid accessing out-of-bounds memory
    if (i < n) {
        c[i] = a[i] + b[i];
    }
}

int main() {
    int n = 5;
    int size = n * sizeof(int);

    // 1. Host (CPU) Memory Initialization
    int h_a[5] = {1, 2, 3, 4, 5};
    int h_b[5] = {10, 20, 30, 40, 50};
    int h_c[5]; // Array to store the final result

    // 2. Device (GPU) Pointers
    int *d_a, *d_b, *d_c;

    // 3. Allocate memory on the GPU (Device)
    cudaMalloc((void**)&d_a, size);
    cudaMalloc((void**)&d_b, size);
    cudaMalloc((void**)&d_c, size);

    // 4. Copy data from Host (CPU) to Device (GPU)
    cudaMemcpy(d_a, h_a, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, h_b, size, cudaMemcpyHostToDevice);

    // 5. Define Execution Configuration (1 block with 'n' threads)
    int threadsPerBlock = n;
    int blocksPerGrid = 1;

    // 6. Launch the Kernel on the GPU
    vectorAdd<<<blocksPerGrid, threadsPerBlock>>>(d_a, d_b, d_c, n);

    // Wait for the GPU to finish before accessing results on the host
    cudaDeviceSynchronize();

    // 7. Copy the result back from Device (GPU) to Host (CPU)
    cudaMemcpy(h_c, d_c, size, cudaMemcpyDeviceToHost);

    // 8. Print the result
    printf("Result of addition:\n");
    for (int i = 0; i < n; i++) {
        printf("%d + %d = %d\n", h_a[i], h_b[i], h_c[i]);
    }

    // 9. Free allocated GPU memory
    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);

    return 0;
}