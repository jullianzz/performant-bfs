/*
* Author: Julia Zeng 
*
* Code description: Testbench to verify serial bfs. 
*
*/

#include "param.h" 
#include "bfs_serial.h" 
#include "graph.h"
#include "matrix.h"
#include <stdio.h>


int main() {
	// Idea: Initalize directed test
	// Input through the design under test
	// Use assertions to verify output
	// Print theoretical and experimental outputs
	
	printf("********** Serial BFS Testbench **********\n"); 
	
	int size = 10; 								// initialize number of vertices
	struct Graph *inputG = init_graph(size); 	// initialize directed test
	display_graph(inputG); 		// display the graph 

	serial_bfs(inputG); 	// pass through serial bfs design
	display_traversal(inputG); 	// display the serial bfs output

	
	
	return 0; 
} 
