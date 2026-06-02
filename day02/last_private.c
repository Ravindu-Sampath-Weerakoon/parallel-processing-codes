#include <omp.h>
#include <stdio.h>

//final value is copied back to orginal varibale

int main() {
    int i ,x;

    #pragma omp parallel for lastprivate(x)
    for(i=0; i<5; i++) {
        x = i*2;
        printf("Thread %d: x = %d\n", omp_get_thread_num(), x);
    }
    printf("Final value of x: %d\n", x); // This will print the value of x from the last thread

    return 0;
}