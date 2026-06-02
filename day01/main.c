#include<omp.h>
#include<stdio.h>
#include<stdlib.h>

void main()
{
    int a[8] = {1,2,5,10,3,7,2,-1};
    int b[8] = {2,3,4,9,0,3,2,-1};

    int c[8];

    int tid;

    #pragma omp parallel sections num_threads(8)

    {
        tid = omp_get_thread_num();
        c[tid] = a[tid] + b[tid];
        printf("c[%d] = %d\n", tid, c[tid]);
    }

}
