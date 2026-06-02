#include <stdio.h>
#include <omp.h>

#define N 1000

int main(){
    int array[N];
    int sum = 0;

    for (int i = 0; i < N; i++) {
        array[i] = i + 1; // Initialize the array with values from 1 to N
    }

    #pragma omp parallel for shared(array) reduction(+:sum)
    for (int i = 0; i < N; i++) {
        sum += array[i]; // Each thread contributes to the reduction
    }

    printf("The sum of the array is: %d\n", sum);

    return 0;
}