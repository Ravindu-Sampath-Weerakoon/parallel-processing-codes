#include <stdio.h>
#include <omp.h>
#define N 1000

int main() {
    int array[N];
    int sum = 0;
    int count = 0;

    // Initialize the array elements to 1
    for(int i = 0; i < N; ++i) {
        array[i] = 1;
    }

    // Spawn a parallel region sharing array, sum, and count among threads
    #pragma omp parallel shared(array, sum, count)
    {
        int local_sum = 0;
        int local_count = 0;

        // Distribute the loop iterations across the available threads
        #pragma omp for
        for(int i = 0; i < N; ++i) {
            local_sum += array[i];
            local_count++;
        }

        // --- THE PROBLEM BLOCK ---
        
        // #pragma omp atomic ONLY applies to the single, immediately following statement.
        #pragma omp atomic        // Problem: Only protects ONE statement
        sum += local_sum;         // This specific memory update is safe and atomic.

        // Because atomic doesn't accept curly braces or protect multiple lines,
        // this next line runs without protection! Multiple threads might write to 
        // 'count' simultaneously, causing a data race condition.
        count += local_count;     // This line is NOT protected!
    }

    // Print final results (Count may display an incorrect value due to the race condition)
    printf("Sum: %d, Count: %d\n", sum, count);
    return 0;
}