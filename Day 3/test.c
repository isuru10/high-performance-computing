#include "omp.h"
#include "stdio.h"

void main()
{
    int count = 40;
    int tot = 0;

    #pragma omp parallel for reduction (+:tot)     

    for (int i = 0; i < count; i++)
    {        
        int id = omp_get_thread_num();
        tot += i;
        printf("thread id: %d tot: %d\n", id, tot);
    }                    
    
    printf("tot: %d\n", tot);
}

