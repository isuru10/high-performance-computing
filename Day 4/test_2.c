#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

#define NUM_THREADS 5
#define TCOUNT 10
#define COUNT_LIMIT 12

int count = 0;
pthread_mutex_t count_mutex;
pthread_cond_t count_threshold_cv;

void *incCount(void *t)
{
    long tid = (long) t;
    int i;
    for(i = 0; i < TCOUNT; i++)
    {
        pthread_mutex_lock(&count_mutex);
        count++;

        if(count == COUNT_LIMIT)
        {
            printf("Count: %d reached at thread: %ld\n", count, tid);
            pthread_cond_signal(&count_threshold_cv);
            printf("Sent signal\n");
        }
        printf("incCount(): thread: %ld count: %d unlocking mutex\n", tid, count);
        pthread_mutex_unlock(&count_mutex);
        sleep(1);
    }
    pthread_exit(NULL);
}

void *watchCount(void *t)
{
    long tid = (long) t;

    printf("Starting wachCount() at thread: %ld\n", tid);

    pthread_mutex_lock(&count_mutex);

    while(count < COUNT_LIMIT)
    {
        printf("watchCount() thread: %ld count: %d going into wait\n", tid, count);
        pthread_cond_wait(&count_threshold_cv, &count_mutex);
        printf("Conditional signal recieved. thread: %ld count: %d\n", tid, count);
    }

    count += 125;
    printf("thread: %ld count now: %d\n", tid, count);
    printf("Unlocking mutex");
    pthread_mutex_unlock(&count_mutex);
    pthread_exit(NULL);
}

int main(int argc, char* argv[])
{
    pthread_t threads[NUM_THREADS];
    pthread_attr_t attr;
    long t1 = 1, t2 = 2, t3 = 3;
    int i;

    pthread_mutex_init(&count_mutex, NULL);
    pthread_cond_init(&count_threshold_cv, NULL);

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    pthread_create(&threads[0], &attr, watchCount, (void *)t1);
    pthread_create(&threads[1], &attr, incCount, (void *)t2);
    pthread_create(&threads[2], &attr, incCount, (void *)t3);

    for(i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }
    printf ("Main(): Waited and joined with %d threads. Final value of count = %d. Done.\n", 
          NUM_THREADS, count);

    pthread_attr_destroy(&attr);
    pthread_mutex_destroy(&count_mutex);
    pthread_cond_destroy(&count_threshold_cv);
    pthread_exit (NULL);
}