#include "omp.h"
#include "stdio.h"
#include "math.h"

void main()
{
    #pragma omp parallel num_threads(4)
    {
       
        #pragma omp critical
        {
            int id = omp_get_thread_num();
            printf("%d\n", id);
        }
    }
}
