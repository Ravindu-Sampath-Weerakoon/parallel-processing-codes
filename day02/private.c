#include <omp.h>
#include <stdio.h>

int main(){
    int i = 100; //orginal value of i, but it will be private to each thread and not shared

    //

    #pragma omp parallel private(i) // each thread has its own private copy of i
    {
        i = omp_get_thread_num(); // each thread assigns its own thread number to i
        printf("Thread %d: i = %d\n", omp_get_thread_num(), i); // each thread prints its own value of i

    }

    printf("after parallel region, i = %d\n", i); // after the parallel region, i will still have its original value of 100

    return 0;
}

//Each thread will print its own value of i, which is the thread number, and after the parallel region, the original value of i will still be 100. This demonstrates that i is private to each thread and not shared among them.

//orginal value of i, but it will be private to each thread and not shared there fore each thread will have its own copy of i and will not affect the value of i in other threads.