#ifndef MY_BARRIER_H
#define MY_BARRIER_H

#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>


typedef struct my_barrier_t
{
    int total_threads;    //number of threads
    int count_threads_waiting;   //counts threads in the barrier
    bool flag;     //signals the change of state of the barrier between cycles
    pthread_mutex_t barrier_mutex;   //mutex lock for counter
    pthread_cond_t barrier_cond;    //condition variable for synchronization
}my_barrier_t;

void my_barrier_init(my_barrier_t *b, int count);
void my_barrier_destroy(my_barrier_t *b);
void my_barrier_wait(my_barrier_t *b);

#endif