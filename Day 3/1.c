#include "omp.h"
#include "stdio.h"

int do_lots_of_work(int id);

void main()
{
    int tmp, id;
    omp_lock_t lck;
    omp_init_lock(&lck);
    #pragma omp parallel private (tmp, id)
    {
        id = omp_get_thread_num();
        
        omp_set_lock(&lck);
        tmp = do_lots_of_work(id);
        printf("%d %d\n", id, tmp);
        omp_unset_lock(&lck);
    } 
    omp_destroy_lock(&lck); 
}

int do_lots_of_work(int id)
{
    int i,tot = 0;
    for(i = 0; i < 800/(id + 1); i++){
        tot += i;
    }
    return tot;
}