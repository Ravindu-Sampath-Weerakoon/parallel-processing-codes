#include <omp.h>
#include <stdio.h>

//only the master thread will execute this section 

int main() {
    #pragma omp parallel num_threads(4)
    {
        //all threads will execute this section
        printf("Hello from thread %d\n", omp_get_thread_num());

        #pragma omp master
        {
            //only the master thread will execute this section
            printf("This is the master thread, thread %d\n", omp_get_thread_num());
        }

        //no implicit barrier here, threads can continue without waiting for the master thread to finish
        printf("Thread %d is continuing after the master section\n", omp_get_thread_num());
    }
    return 0;
}