#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 5

void *printHello(void *thread_id)
{
    long tid = (long) thread_id;
    printf("Hello world! It's thread %ld\n", tid);
    pthread_exit(NULL);
}

int main(int argc, void* argv[])
{
    pthread_t threads[NUM_THREADS];

    int rc;
    long t;

    for(t = 0; t < NUM_THREADS; t++)
    {
        printf("In main: creating thread %ld\n", t);

        rc = pthread_create(&threads[t], NULL, printHello, (void *)t);

        printf("rc: %d\n", rc);

        if(rc)
        {
            printf("ERROR rc: %d", rc);
            exit(-1);
        }        
    }
    
    pthread_exit(NULL);
}