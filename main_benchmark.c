#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "my_barrier.h"


#define N 100000  //number of iterations in the `do_work` function

int REPEATS;

pthread_barrier_t pthread_barrier;
my_barrier_t my_barrier;


/* Function that simulates some work by summing up N float values*/
void do_work(int thread_id)
{
    float sum = 0;

    for(int i = 0; i < N; i++)
    {
        sum += (float)i;
    }
}


/* Function for threads using pthread barrier*/
void *pthread_barrier_function(void *arg)
{
    int thread_id = *(int *)arg;

    for(int i = 0; i < REPEATS; i++)
    {
        do_work(thread_id);
        pthread_barrier_wait(&pthread_barrier);
    }

    return NULL;
}


/* Function for threads using my barrier*/
void *my_barrier_function(void *arg)
{
    int thread_id = *(int *)arg;

    for(int i = 0; i < REPEATS; i++)
    {
        do_work(thread_id);
        my_barrier_wait(&my_barrier);
    }

    return NULL;
}


int main(int argc, char **argv)
{
    //check if the correct number of arguments is provided
    if(argc != 3)
    {
        fprintf(stderr, "Usage: %s <number_of_threads> <number_of_repeats>\n", argv[0]);
        exit(EXIT_FAILURE);
    }


    //convert to int
    int NUMTHREADS = atoi(argv[1]);   
    REPEATS = atoi(argv[2]);

    pthread_t threads[NUMTHREADS];
    int thread_id[NUMTHREADS];

    struct timespec start, finish;
    double elapsed_pthread_barrier, elapsed_my_barrier;

    
    //Measuring the time for pthread barrier
    printf("Pthread barrier: ");
    clock_gettime(CLOCK_MONOTONIC, &start);

    pthread_barrier_init(&pthread_barrier, NULL, NUMTHREADS);   //initialize the pthread barrier

    //Create threads that will use the pthread barrier
    for(int i = 0; i < NUMTHREADS; i++)
    {
        thread_id[i] = i;
        pthread_create(&threads[i], NULL, pthread_barrier_function, (void *)&thread_id[i]);
    }

    //Wait for all threads to finish
    for(int i = 0; i < NUMTHREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    pthread_barrier_destroy(&pthread_barrier);   //destroy the pthread barrier

    clock_gettime(CLOCK_MONOTONIC, &finish);

    elapsed_pthread_barrier = (finish.tv_sec - start.tv_sec);
    elapsed_pthread_barrier += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

    printf("time = %lf \n", elapsed_pthread_barrier);



    //Measuring the time for my barrier
    printf("My barrier: ");
    clock_gettime(CLOCK_MONOTONIC, &start);

    my_barrier_init(&my_barrier, NUMTHREADS);   //initialize my barrier

    //Create threads that will use my barrier
    for(int i = 0; i < NUMTHREADS; i++)
    {
        thread_id[i] = i;
        pthread_create(&threads[i], NULL, my_barrier_function, (void *)&thread_id[i]);
    }

    //Wait for all threads to finish
    for(int i = 0; i < NUMTHREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    my_barrier_destroy(&my_barrier);   //destroy my barrier

    clock_gettime(CLOCK_MONOTONIC, &finish);

    elapsed_my_barrier = (finish.tv_sec - start.tv_sec);
    elapsed_my_barrier += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

    printf("time = %lf \n", elapsed_my_barrier);

    return 0;
}