#include "my_barrier.h"
#include "jones_family.h"


/*Array for the 5 days of the week*/
const char *days[] = {"Monday", "Thuesday", "Wednesday", "Thursday", "Friday"};
FILE *output;

/*Barrier variables for activities synchronization*/
my_barrier_t barrier_breakfast;
my_barrier_t barrier_math;
my_barrier_t barrier_football;
my_barrier_t barrier_dinner;


/*Function for having breakfast together*/
void eating_breakfast(const char *name, const char *day)
{
    fprintf(output, "%s wakes up on %s. %s is ready to eat breakfast with family.\n", name, day, name);
    my_barrier_wait(&barrier_breakfast);   //Wait for all family members for breakfast
    fprintf(output, "%s eats breakfast with family on %s morning.\n", name, day);
}


/*Function for parents going to work*/
void going_to_work(const char *name, const char *day)
{
    // Check if is the parents
    if(!strcmp(name, "Mama") || !(strcmp(name, "Papa")))
    {
        fprintf(output, "%s goes to work on %s.\n", name, day);
        sleep(8);    //Simulate time spent at work
        fprintf(output, "%s finishes work on %s and goes home.\n", name, day);
    }
}


/*Function for children going to school*/
void going_to_school(const char *name, const char *day)
{
    //Check if is one of the children
    if(!strcmp(name, "Alice") || !strcmp(name, "Bob") || !strcmp(name, "Chris") || !strcmp(name, "Dave"))
    {
        fprintf(output, "%s goes to school on %s.\n", name, day);
        sleep(6);   //Simulate time spent at school
        fprintf(output, "%s finishes school on %s and goes home.\n", name, day);
    }
}


/*Function for studying math*/
void studying_math(const char *name)
{
    //Check if the children is Alice
    if(!strcmp(name, "Alice"))
    {
        fprintf(output, "Alice is ready to learn math with Bob.\n");
        my_barrier_wait(&barrier_math);   //Wait for Bob to be ready
        fprintf(output, "Alice learns math with Bob.\n");
        sleep(2);
    }
    //Check if the children is Bob
    else if(!strcmp(name, "Bob"))
    {
        fprintf(output, "Bob is ready to learn math with Alice.\n");
        my_barrier_wait(&barrier_math);   //Wait for Alice to be ready
        fprintf(output, "Bob learns math with Alice.\n");
        sleep(2);
    }
}


/*Function for playing football*/
void playing_football(const char *name)
{
    //Check if the children is Chris
    if(!strcmp(name, "Chris"))
    {
        fprintf(output, "Chris is ready to play football with Dave.\n");
        my_barrier_wait(&barrier_football);   //Wait for Dave to be ready
        fprintf(output, "Chris plays football with Dave.\n");
        sleep(2);
    }
    //Check if the children is Dave
    else if(!strcmp(name, "Dave"))
    {
        fprintf(output, "Dave is ready to play football with Chris.\n");
        my_barrier_wait(&barrier_football);   //Wait for Chris to be ready
        fprintf(output, "Dave plays football with Chris.\n");
        sleep(2);
    }
}


/*Function for having dinner together*/
void eating_dinner(const char *name, const char *day)
{
    fprintf(output, "%s is ready to eat dinner with family.\n", name);
    my_barrier_wait(&barrier_dinner);  //Wait for all family members for dinner
    fprintf(output, "%s eats dinner with family on %s evening.\n", name, day);
    sleep(1);  // Simulate time for eating dinner
}

void going_to_sleep(const char *name, const char *day)
{
    fprintf(output, "%s goes to bed on %s night.\n", name, day);  //Show the end of the day for each member of the family
    sleep(7);   // Simulate time for a night's sleep
}


/*Function for simulating the daily life of family members*/
void *daily_life(void *var) 
{
    const char *name = (char *)var;   //Get the name of the family member

    for (int i = 0; i < DAYS; i++) 
    {
        const char *day = days[i];   //Get the current day

        //Function calls for daily activities
        eating_breakfast(name, day);
        going_to_work(name, day);
        going_to_school(name, day);
        studying_math(name);
        playing_football(name);
        eating_dinner(name, day);
        going_to_sleep(name, day);
    }

    return NULL;
}