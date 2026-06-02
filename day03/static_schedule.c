#include <omp.h>
#include <stdio.h>

int main() {
    // 16 total iterations to be divided
    const int size = 16;

    // schedule(static, 2) splits the loop into "chunks" of size 2.
    // These chunks are distributed among available threads in a round-robin, 
    // deterministic fashion before the loop even begins executing.
    #pragma omp parallel for schedule(static, 2)
    for(int i = 0; i < size; i++) {
        printf("Thread %d processes iteration %d\n", omp_get_thread_num(), i);
    }
    
    return 0;
}