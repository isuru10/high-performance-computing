#include "omp.h"
#include "stdio.h"

double A(int x);

void main()
{
    
    double E = 0;

    #pragma omp parallel
    {
        int id = omp_get_thread_num();

        #pragma omp critical
        E += A(id);
    }

    printf("E: %f\n", E);
}

double A(int id)
{
    return 3.14 * (id + 1) * 10 * (id + 1) * 10;
}

