/*
* Author: Julia Zeng 
*
* Code description: Implementation of graph structure and functionality.  
*
*/

#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "matrix.h"
#include <stdbool.h>


/* Graph data structure which is represented by an adjacency matrix */ 
struct Graph {
	int size;					// number of vertices in graph   
	int *traversal;				// output of BFS traversal
	bool *visited_map;			// boolean array to map the visit metadata of each vertex
	matrix_ptr adjacency_mat;	// adjacency matrix
}; 


struct Graph *init_graph(int size);
void display_graph(struct Graph *G);
int find_unvisited(struct Graph *G); 
void display_traversal(struct Graph *G);
void set_graph_size(struct Graph *G, long int size); 
void free_graph(struct Graph *G);
void find_unvisited_pthread(struct Graph *G); 

#endif
