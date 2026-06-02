#include <omp.h>
#include <stdio.h>

int main() {
    // Spawn a team of threads to handle work in parallel
    #pragma omp parallel
    {
        // #pragma omp sections defines a container enclosing non-loop parallel tasks
        #pragma omp sections
        {
            // Each individual '#pragma omp section' defines an independent task.
            // OpenMP assigns exactly ONE thread to handle each section.
            
            #pragma omp section
            {
                printf("Section 1 executed by thread %d\n", omp_get_thread_num());
            }

            #pragma omp section
            {
                printf("Section 2 executed by thread %d\n", omp_get_thread_num());
            }

            #pragma omp section
            {
                printf("Section 3 executed by thread %d\n", omp_get_thread_num());
            }
        } // Implicit synchronization point: Threads wait here until all sections are finished
    }

    return 0;
}