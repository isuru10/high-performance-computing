#include "omp.h"
#include "stdio.h"

void main()
{
    int a = 0;
    #pragma omp parallel
    {
        a += 10;
    }
    printf("a = (%d)\n",a);
}