#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "my_barrier.h"
#include "jones_family.h"


int main() 
{
    //Open the output file for writing results
    output = fopen("results_jones_family.txt", "w");

    if(output == NULL)
    {
        fprintf(stderr, "Failed to open the file");
        exit(EXIT_FAILURE);
    }

    //Initialize barriers for different parts of the day
    my_barrier_init(&barrier_breakfast, 6);
    my_barrier_init(&barrier_math, 2);
    my_barrier_init(&barrier_football, 2);
    my_barrier_init(&barrier_dinner, 6);

    char *family_members[] = {"Mama", "Papa", "Alice", "Bob", "Chris", "Dave"};
    pthread_t thread[6];

    //Create threads for each family member
    for(int i = 0; i < 6; i++)
    {
        pthread_create(&thread[i], NULL, daily_life, (void *)(family_members[i]));
    }

    //Wait for all threads to finish
    for(int i = 0; i < 6; i++)
    {
        pthread_join(thread[i], NULL);
    }

    //Destroy the barriers after all threads finished
    my_barrier_destroy(&barrier_breakfast);
    my_barrier_destroy(&barrier_math);
    my_barrier_destroy(&barrier_football);
    my_barrier_destroy(&barrier_dinner);

    //Close the output file
    if(fclose(output))
    {
        fprintf(stderr, "Failed to close the file");
        exit(EXIT_FAILURE);   
    }
    return 0;
}