/* 
* Adapted from the instructors of EC527 (High Performance Computing) 
* of the Boston University's ECE department. 
*/ 

#ifndef _PARAM_H_
#define _PARAM_H_

#define CPNS 3.0 /* Machine clock speed in cycles per nanosecond (GHz) 
                //-- Adjust to your computer */
   
/* Matrix size is determined quadratically n = Ax^2 + Bx + C */
#define A   0   /* coefficient of x^2 */
#define B   1   /* coefficient of x */
#define C   18  /* constant term */

#define NUM_TESTS 10

#define OPTIONS 3     
#define IDENT 0

#define INIT_LOW -10.0
#define INIT_HIGH 10.0


typedef double data_t;  /* Adjust data type here */

int NUM_THREADS = 4;


#endif