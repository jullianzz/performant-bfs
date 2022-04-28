/* 
* Adapted from the instructors of EC527 (High Performance Computing) 
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

/* initialize matrix to random values in [0,1] */
int init_matrix_rand(matrix_ptr m, long int row_len)
{
    long int i, j;
    zero_matrix(m, row_len);	// initialize matrix to all zeros

    if (row_len > 0) {
		m->rowlen = row_len;
		for (i = 0; i < row_len; i++) {			// i = row
			for (j = i; j < row_len; j++) {		// j = col
				m->data[i*row_len+j] = (data_t) rand() % 2;	// generate random value [0,1]
				m->data[j*row_len+i] = m->data[i*row_len+j];// set mirror element to same value
			}
		}
    	return 1;
    }
    
    else return 0;
}

/* initialize matrix */
int zero_matrix(matrix_ptr m, long int row_len)
{
    long int i;

    if (row_len > 0) {
		m->rowlen = row_len;
		for (i = 0; i < row_len*row_len; i++)
		    m->data[i] = (data_t)(IDENT);
		return 1;
    }
    else return 0;
}



