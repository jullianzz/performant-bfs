/*
* Author: Julia Zeng 
*
* Code description: Testbench to verify serial bfs. 
*
*/

#include "param.h" 
#include "serial.h" 
#include "graph.h"
#include "matrix.h"


int main() {
	// Idea: Initalize directed test
	// Input through the design under test
	// Use assertions to verify output
	// Print theoretical and experimental outputs
	
	int size = 5; 								// initialize number of vertices
	struct Graph *inputG = init_graph(size); 	// initialize directed test
	display_graph(inputG); 		// display the graph 

	serial_bfs(inputG); 	// pass through serial bfs design
	display_traversal(inputG); 	// display the serial bfs output

	
	
	return 0; 
} 
