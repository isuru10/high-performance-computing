#include "omp.h"
#include "stdio.h"
#include "math.h"

double A(int x);
double subA(int id);


void main()
{
    int area[4];
    double E = 1;

    #pragma omp parallel num_threads(4)
    {
       
        #pragma omp critical
        {
            int id = omp_get_thread_num();
            area[id] = subA(id);
        }
    }

    E = (area[0] * area[1]) + (area[2] * area[3]);

    printf("E: %f\n", E);
}

double A(int r)
{
    return 3.14 * r * r;
}

double subA(int id)
{    
    return A(pow(2, id) * 10);
}

