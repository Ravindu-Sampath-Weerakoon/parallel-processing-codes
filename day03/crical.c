#include <omp.h>
#include <stdio.h>

int main() {
    int sum = 0;

    // 1. Open the parallel block with curly braces
    #pragma omp parallel num_threads(4) 
    {
        int local_sum = 0;
        for(int i = 0; i < 1000; i++) {
            local_sum++;
        }

        // 2. Critical section protects the shared variable update
        #pragma omp critical
        {
            sum += local_sum;
            printf("Thread %d added its local sum\n", omp_get_thread_num());
        } 
    } // 3. Close the parallel block here

    // 4. Print final result and return AFTER all threads are finished
    printf("Final sum: %d\n", sum);
    return 0;
}