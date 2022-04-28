/* 
* Author: Julia Zeng 
*
* Code description: Graph header
*/ 

#include "graph.h"
#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>



/* init_graph to initialize graph and populates adjacency matrix randomly */ 
struct Graph *init_graph(int size) {
	struct Graph *G = malloc(sizeof(struct Graph));	// allocate memory to graph 
	matrix_ptr new_matrix(long int row_len);
	G->adjacency_mat = new_matrix((long int) size); 			// initialize adjacency matrix
	init_matrix_rand(G->adjacency_mat, (long int) size);		// randomly initialize adjacency matrix
	G->size = size;		// set Graph size
	return G; 
}


/* display graph prints the adjacency matrix in graph G in 2D-format */
void display_graph(struct Graph *G) {
	int size = G->size; 
	int i;
	for (i = 0; i < size*size; i++) {
		printf("%d ", G->adjacency_mat->data[i]);
		if ((i+1) % size == 0) {
			printf("\n");
		}		
	}
}


