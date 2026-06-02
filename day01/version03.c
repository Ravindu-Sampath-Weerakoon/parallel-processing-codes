#include <stdio.h>
#include <omp.h>

int main() {
    // Record the starting time of the execution
    double start_time = omp_get_wtime();

    double sum = 0.0;

    // Parallelize the loop safely using the reduction clause
    #pragma omp parallel for reduction(+:sum)
    for (int i = 1; i <= 1000; i++) {
        sum += i;
    }

    // Record the ending time of the execution
    double end_time = omp_get_wtime();

    // Print the benchmark and total result
    printf("Time taken = %f seconds\n", end_time - start_time);
    printf("Sum = %f\n", sum);

    return 0;
}