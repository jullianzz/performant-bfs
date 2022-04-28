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
	matrix_ptr adjacency_mat;	// adjacency matrix
	int size;					// number of vertices in graph   
	int *traversal;				// output of BFS traversal
	bool *visited_map;			// boolean array to map the visit metadata of each vertex
}; 


struct Graph *init_graph(int size);
void display_graph(struct Graph *G);
int find_unvisited(struct Graph *G); 
void display_traversal(struct Graph *G);


#endif
