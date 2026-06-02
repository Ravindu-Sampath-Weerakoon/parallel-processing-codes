#include <omp.h>
#include <stdio.h>
#include <unistd.h> // Required for the sleep() function

// Makes threads wait until all threads reach the barrier point
int main() {
    // Spawn a parallel region with 4 threads
    #pragma omp parallel num_threads(4)
    {
        // Phase 1: Every thread starts this immediately
        printf("Thread %d starting phase 1\n", omp_get_thread_num());
        
        // Simulate different workloads: 
        // Thread 0 sleeps 0s, Thread 1 sleeps 1s, Thread 2 sleeps 2s, etc.
        sleep(omp_get_thread_num()); 

        // BARRIER: Synchronization point. 
        // Fast threads (like Thread 0) will pause here and wait until 
        // the slowest thread (Thread 3) finishes its sleep and catches up.
        #pragma omp barrier

        // Phase 2: No thread can execute this line until ALL 4 threads 
        // have successfully crossed the barrier above.
        printf("Thread %d starting phase 2\n", omp_get_thread_num());
    }
    
    return 0;
}