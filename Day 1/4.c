#include "omp.h"
#include "stdio.h"

void main()
{    
    #pragma omp parallel num_threads(4)
    {
        int id = omp_get_thread_num();

        printf("%d\n", id);
    }
}