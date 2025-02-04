#ifndef JONES_FAMILY_H
#define JONES_FAMILY_H

#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

#define DAYS 5

extern my_barrier_t barrier_breakfast;
extern my_barrier_t barrier_math;
extern my_barrier_t barrier_football;
extern my_barrier_t barrier_dinner;

extern FILE *output;


void eating_breakfast(const char *name, const char *day);
void going_to_work(const char *name, const char *day);
void going_to_school(const char *name, const char *day);
void studying_math(const char *name);
void playing_football(const char *name);
void eating_dinner(const char *name, const char *day);
void going_to_sleep(const char *name, const char *day);
void *daily_life(void *var);

#endif