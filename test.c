/*
* Author: Julia Zeng 
*
* Code description: Test Breadth-First Search graph traversal implementations.  
* 
* Note: Any code that was borrowed from the instructors of EC527 (High Performance 
* Computing) of the Boston University's ECE department are indicated as such with 
* comments. Please see README for more references to external resources used. 
* 
*/ 

/* Include libraries */ 
#include "param.h"
#include "benchmark.h"
#include "matrix.h"
#include "serial.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // printf("*********Test Serial BFS*********\n");

    /* 
    * Initialize data structures, time structures, and parameters.
    */
    int OPTION;
    struct timespec time_start, time_stop;
    double time_stamp[OPTIONS][NUM_TESTS];
    double wd;
    long int x, n;
    long int alloc_size;

    x = NUM_TESTS-1;
    alloc_size = A*x*x + B*x + C;

    /* 
    * Warm up processor and get out of power-saving mode
    */
    wd = wakeup_delay();


    /* 
    * Declare and initialize the matrix structures 
    */
    matrix_ptr a0 = new_matrix(alloc_size);
    init_matrix_rand(a0, alloc_size);
    matrix_ptr b0 = new_matrix(alloc_size);
    init_matrix_rand(b0, alloc_size);
    matrix_ptr c0 = new_matrix(alloc_size);
    zero_matrix(c0, alloc_size);
    matrix_ptr d0 = new_matrix(alloc_size);
    init_matrix_rand_grad(d0, alloc_size);


    /*
    * Begin benchmarking
    */ 
    OPTION = 0;
    printf("OPTION %d - serial_bfs()\n", OPTION);
    for (x=0; x<NUM_TESTS && (n = A*x*x + B*x + C, n<=alloc_size); x++) {
    init_matrix_rand(a0, n);
    set_matrix_rowlen(a0, n);
    set_matrix_rowlen(b0, n);
    set_matrix_rowlen(c0, n);
    clock_gettime(CLOCK_REALTIME, &time_start);
    // TODO: put serial BFS here
    clock_gettime(CLOCK_REALTIME, &time_stop);
    time_stamp[OPTION][x] = interval(time_start, time_stop);
    printf("iter %ld done\n", x);
    }

    printf("\n");
    printf("All measurements are in cycles (if CPNS is set correctly in the code)\n");
    printf("row length, 1 thread, 2 threads, 4 threads\n");
    {
    int i, j;
    for (i = 0; i < NUM_TESTS; i++) {
        printf("%d, ", A*i*i + B*i + C);
        for (j = 0; j < OPTIONS; j++) {
        if (j != 0) printf(", ");
        printf("%ld", (long int)((double)(CPNS) * 1.0e9 * time_stamp[j][i]));
        // printf("%f", 1.0e9 * time_stamp[j][i]);
        }
        printf("\n");
    }
    }

    printf("Wakeup delay calculated %f\n", wd);

    return 0;
} /* end main */
