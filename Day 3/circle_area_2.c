#include "omp.h"
#include "stdio.h"

double A(int x);
double subA(int id);


void main()
{
    
    double E = 1;

    #pragma omp parallel num_threads(2)
    {
        int id = omp_get_thread_num();

        #pragma omp critical
        {
            E *= subA(id);
        }
    }

    printf("E: %f\n", E);
}

double A(int r)
{
    return 3.14 * r * r;
}

double subA(int id)
{
    return A((id + 1) * (id + 1) * 10) + A((id + 1) * (id + 1) * 20);
}

