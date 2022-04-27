/* 
* Borrowed from the instructors of EC527 (High Performance Computing) 
* of the Boston University's ECE department. 
*/ 

#ifndef _BENCHMARK_H
#define _BENCHMARK_H

#include <time.h>

double interval(struct timespec start, struct timespec end); 

double wakeup_delay(); 



#endif