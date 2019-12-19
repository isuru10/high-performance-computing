#include "omp.h"
#include "stdio.h"

void main()
{
    printf("num_procs: %d\n", omp_get_num_procs());
    omp_set_dynamic(0);
    printf("num_procs: %d\n", omp_get_num_procs());
    #pragma omp parallel
    {
        printf("num_threads: %d\n", omp_get_num_threads());
    }
}