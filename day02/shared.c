#include <stdio.h>
#include <omp.h>

int main() {
    int shared_counter = 0;
    shared_counter++; 

    #pragma omp parallel shared(shared_counter)
        {
            #pragma  omp atomic // only one thread at a time can update the shared counter
            shared_counter++;
            
            #pragma omp barrier // wait for all threads to finish updating the shared counter before proceeding

            if (omp_get_thread_num() == 0) {
                printf("Shared Counter: %d\n", shared_counter);
            }

            
            

    }
        
    
        



    return 0;
}