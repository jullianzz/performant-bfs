/*
* Author: Julia Zeng 
*
* Code description: Testbench to verify pthreaded bfs. 
*
*/

#include "param.h" 
#include "bfs_pthread.h" 
#include "graph.h"
#include "matrix.h"
#include <stdio.h>


int main() {
	// Idea: Initalize directed test
	// Input through the design under test
	// Use assertions to verify output
	// Print theoretical and experimental outputs
	
	printf("********** Pthreaded BFS Testbench **********\n"); 
	
	int size = 5; 								// initialize number of vertices
	struct Graph *inputG = init_graph(size); 	// initialize directed test
	display_graph(inputG); 						// display the graph 

	int *Traversal = bfs_pthread(inputG); 		// pass through serial bfs design
	display_traversal(TRAV, NULL, Traversal, size); 				// display traversal

	
	
	return 0; 
} 
