/* 
* Borrowed from the instructors of EC527 (High Performance Computing) 
* of the Boston University's ECE department. 
*/ 

#include "matrix.h"
#include "param.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/* Random number generator */ 
double fRand(double fMin, double fMax)
{
    double f = (double)random() / (double)(RAND_MAX);
    return fMin + f * (fMax - fMin);
}

/* Create matrix of specified row length */
matrix_ptr new_matrix(long int row_len)
{
    // long int i;

    /* Allocate and declare header structure */
    matrix_ptr result = (matrix_ptr) malloc(sizeof(matrix_rec));
    if (!result) {
    return NULL;  /* Couldn't allocate storage */
    }
    result->rowlen = row_len;

    /* Allocate and declare array */
    if (row_len > 0) {
    data_t *data = (data_t *) calloc(row_len*row_len, sizeof(data_t));
    if (!data) {
        free((void *) result);
        printf("COULDN'T ALLOCATE %ld bytes STORAGE \n",
                                            row_len*row_len*sizeof(data_t));
        return NULL;  /* Couldn't allocate storage */
    }
    result->data = data;
    }
    else result->data = NULL;

    return result;
}

/* Set row length of matrix */
int set_matrix_rowlen(matrix_ptr m, long int row_len)
{
    m->rowlen = row_len;
    return 1;
}

/* Return row length of matrix */
long int get_matrix_rowlen(matrix_ptr m)
{
    return m->rowlen;
}

/* initialize matrix to consecutive numbers starting with 0 */
int init_matrix(matrix_ptr m, long int row_len)
{
    long int i;

    if (row_len > 0) {
    m->rowlen = row_len;
    for (i = 0; i < row_len*row_len; i++)
        m->data[i] = (data_t)(i);
    return 1;
    }
    else return 0;
}

/* initialize matrix to random values in [INIT_LOW, INIT_HIGH] */
int init_matrix_rand(matrix_ptr m, long int row_len)
{
    long int i;
    double fRand(double fMin, double fMax);

    if (row_len > 0) {
    m->rowlen = row_len;
    for (i = 0; i < row_len*row_len; i++)
        m->data[i] = (data_t)(fRand((double)(INIT_LOW),(double)(INIT_HIGH)));
    return 1;
    }
    else return 0;
}

/* initialize matrix to random values bounded by a "gradient" envelope */
int init_matrix_rand_grad(matrix_ptr m, long int row_len)
{
    long int i;
    double fRand(double fMin, double fMax);

    if (row_len > 0) {
    m->rowlen = row_len;
    for (i = 0; i < row_len*row_len; i++)
        m->data[i] = (data_t)(fRand((double)(0.0),(double)(i)));
    return 1;
    }
    else return 0;
}

/* initialize matrix */
int zero_matrix(matrix_ptr m, long int row_len)
{
    // long int i,j;
    long int i;

    if (row_len > 0) {
    m->rowlen = row_len;
    for (i = 0; i < row_len*row_len; i++)
        m->data[i] = (data_t)(IDENT);
    return 1;
    }
    else return 0;
}

data_t *get_matrix_start(matrix_ptr m)
{
    return m->data;
}

/* print matrix */
void print_matrix(matrix_ptr v)
{
    long int i, j, row_len;

    row_len = v->rowlen;
    for (i = 0; i < row_len; i++) {
    printf("\n");
    for (j = 0; j < row_len; j++)
        printf("%.4f ", (data_t)(v->data[i*row_len+j]));
    }
}