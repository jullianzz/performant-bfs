/* 
* Author: Julia Zeng 
*
* Code description: Graph header
*/ 

#include "graph.h"
#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>



/* init_graph to initialize and malloc graph fields and populates adjacency matrix randomly */ 
struct Graph *init_graph(int size) {
	/* Malloc */ 
	struct Graph *G = malloc(sizeof(struct Graph));	// allocate memory to graph 
	G->traversal = malloc(size * sizeof(int)); 		// allocate an int array with 'size' elements
	G->visited_map = malloc(size * sizeof(bool));	// allocate a boolean array with 'size' elements
	int i;
	for (i = 0; i < size; i++) {	// initialize  traversal
		G->traversal[i] = -1; 
	}
	for (i = 0; i < size; i++) {	// initialize  traversal
		G->visited_map[i] = false; 
	}
	
	/* Initialize adjacency matrix */ 
	G->adjacency_mat = new_matrix(size); 		// initialize adjacency matrix
	init_matrix_rand(G->adjacency_mat, size);	// randomly initialize adjacency matrix
	
	/* Set Graph size */
	G->size = size;	
	return G; 
}


/* display graph prints the adjacency matrix in graph G in 2D-format */
void display_graph(struct Graph *G) {
	int size = G->size; 
	int i;
	printf("Graph is: \n");
	for (i = 0; i < size*size; i++) {
		printf("%d ", G->adjacency_mat->data[i]);
		if ((i+1) % size == 0) {
			printf("\n");
		}		
	}
}


/* display_traversal prints the bfs traversal of the graph G or Traversal */
void display_traversal(enum dtype d, struct Graph *G, int *Traversal, int size) {
	printf("Traversal is: ");
	if (d == GRAP) {
		size = G->size; 
		int i;
		for (i = 0; i < size; i++) {
			printf("%d ", G->traversal[i]);	
		}
		printf("\n");
	} else if (d == TRAV) {
		int i;
		for (i = 0; i < size; i++) {
			printf("%d ", Traversal[i]);	
		}
		printf("\n");
	} 
} 


/* find_unvisited finds an unvisited vertex in graph G*/
int find_unvisited(struct Graph *G) {
	int i;
	for (i = 0; i < G->size; i++) {
		if (G->visited_map[i] == false) {
			return i;
		}
	}
	return -1; 	// return -1 if no unvisited node is found
} 


/* set_graph_size sets the size of the Graph and adjacency matrix structures */
void set_graph_size(struct Graph *G, long int size) {
	//G->size = size; 
	set_matrix_rowlen(G->adjacency_mat, size);
}


/* free_graph frees the malloc'd fields of the Graph structure */
void free_graph(struct Graph *G) {
	free(G->adjacency_mat->data);	// free data vector in matrix 
	free(G->adjacency_mat);			// free adjacency matrix
	free(G->visited_map);			// free visited map
	free(G->traversal); 			// free traversal pointer
	free(G);						// free Graph
}


