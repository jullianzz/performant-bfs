/* 
* Borrowed from the instructors of EC527 (High Performance Computing) 
* of the Boston University's ECE department. 
*/ 

#ifndef _MATRIX_H
#define _MATRIX_H

#include "param.h"

/* Abstract data type for square adjacency matrix */
typedef struct {
    long int rowlen;
    data_t *data;
} matrix_rec, *matrix_ptr;  // define matrix and matrix pointer types

/* Matrix routines */ 
matrix_ptr new_matrix(long int row_len);
int set_matrix_rowlen(matrix_ptr m, long int index);
long int get_matrix_rowlen(matrix_ptr m);
int init_matrix_rand(matrix_ptr m, long int row_len);
int zero_matrix(matrix_ptr m, long int row_len);


#endif 
