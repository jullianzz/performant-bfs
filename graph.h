/*
* Author: Julia Zeng 
*
* Code description: Implementation of graph structure and functionality.  
*
*/

#ifndef _GRAPH_H_
#define _GRAPH_H_


/* Graph data structure which is represented by an adjacency matrix */ 
struct Graph {
	matrix_ptr adjacency_mat;	// adjacency matrix
	int size;					// number of vertices in graph   
}; 


/* init_graph to initialize graph and populates adjacency matrix randomly */ 
struct Graph *init_graph_rand(int size) {
	struct Graph *G = malloc(sizeof(struct Graph));	// allocate memory to graph 
	int ret_val = init_matrix_rand(G->adjacency_mat, size);	// randomly initialize adjacency matrix
	G->size = vertices;		// set Graph size
	return G; 
};



#endif
