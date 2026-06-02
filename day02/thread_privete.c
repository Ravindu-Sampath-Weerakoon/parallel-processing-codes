#include <omp.h>
#include <stdio.h>

// Global variables private to each thread

int thread_private_var;

#pragma omp threadprivate(thread_private_var)
// This declares outside the main function that thread_private_var is private to each thread
// This global variable now behaves as if each thread has its own separate instance of thread_private_var
// This pragma applies for the entire program, so any access to thread_private_var will refer to the thread's private instance

int main() {
    
    #pragma omp prallel 
    {
        thread_private_var = omp_get_thread_num(); // Each thread assigns its own thread number to its private variable
        printf("Fist parallel region: Thread %d, thread_private_var = %d\n", omp_get_thread_num(), thread_private_var);


    }

    #pragma omp parallel 
    {
        printf("Second parallel region: Thread %d, thread_private_var = %d\n", omp_get_thread_num(), thread_private_var);
        // In the second parallel region, each thread will still see its own value of thread_private_var
    }

    return 0;
}