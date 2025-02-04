#include "my_barrier.h"

/*Function for initialization*/
void my_barrier_init(my_barrier_t *b, int total_threads)
{
    b->total_threads = total_threads;
    b->count_threads_waiting = 0;
    b->flag = false;
    pthread_mutex_init(&b->barrier_mutex, NULL);
    pthread_cond_init(&b->barrier_cond, NULL);
}

/*Function for correct synchronization between threads, where the last thread must broadcast to all others.*/
void my_barrier_wait(my_barrier_t *b)
{
    pthread_mutex_lock(&b->barrier_mutex);
    b->count_threads_waiting++;

    // Check if the current thread is not the last to reach the barrier
    if(b->count_threads_waiting < b->total_threads)
    {
        bool flag = b->flag;

        // Check the current flag state
        while (b->flag == flag)
        {
            pthread_cond_wait(&b->barrier_cond, &b->barrier_mutex);  // waits until the last thread arrives
        }
    }
    // If the current thread is the last: reset the count, toggle the flag and broadcast to all waiting threads
    else
    {
        b->flag = !b->flag;    //toggle the flag to indicate a new cycle
        b->count_threads_waiting = 0;
        pthread_cond_broadcast(&b->barrier_cond);
    }

    pthread_mutex_unlock(&b->barrier_mutex);
}


/*Function for clean up*/
void my_barrier_destroy(my_barrier_t *b)
{
    pthread_mutex_destroy(&b->barrier_mutex);
    pthread_cond_destroy(&b->barrier_cond);
}