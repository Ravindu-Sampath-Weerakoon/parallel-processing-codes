#include <omp.h>
#include <stdio.h>

// initialize private copies with the original value 

int main(){
    int i = 5; // original value of i, but it will be private to each thread and not shared

    #pragma omp parallel firstprivate(i) // each thread has its own private copy of i
    {
        printf("Thread %d: initial value of i = %d\n", omp_get_thread_num(), i); // each thread prints its own initial value of i
         
        i += omp_get_thread_num(); // each thread assigns its own thread number to i
        printf("Thread %d: end with i = %d\n", omp_get_thread_num(), i); // each thread prints its own value of i after modification

    }

    printf("Original after parallel region, i = %d\n", i); // after the parallel region, i will still have its original value of 5

    return 0;
}