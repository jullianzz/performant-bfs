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
	
	int size = 8; 								// initialize number of vertices
	struct Graph *inputG = init_graph((long int) size); 	// initialize directed test
	struct queue *serial_out = serial_bfs(inputG); 	// pass through serial bfs design
	print_queue(serial_out); 	// display the serial bfs output
	display_graph(inputG); 		// display the graph 
	
	
	return 0; 
} 
