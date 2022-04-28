/*
* Author: Julia Zeng 
*
* Code description: Testbench to verify serial bfs. 
*
*/

#include "param.h" 
#include "serial.h" 
#include "graph.h


int main() {
	// Idea: Initalize directed test
	// Input through the design under test
	// Use assertions to verify output
	// Print theoretical and experimental outputs
	
	int size = 4; 								// set number of vertices
	struct Graph *G = init_graph_rand(size); 	// initialize a graph randomly
	
	struct queue *serial_out = serial_bfs(G); 
	
	
	return 0; 
} 
