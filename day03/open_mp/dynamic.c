#include <stdio.h>
#include <omp.h>
#include <unistd.h> // for sleep function

int main(){
    #pragma omp parallel for schedule(dynamic, 2)
    for(int i = 0; i < 16; i++){
        sleep(i % 3); // Simulate work by sleeping for 1 or 2 seconds
        printf("Thread %d processes iteration %d\n", omp_get_thread_num(), i);
    }

    return 0;
}