/*
* Author: Julia Zeng 
*
* Code description: Implementation of serial version 
* of Breadth-First Search graph traversal algorithm.
*
*/ 


#include "bfs_serial.h"
#include "param.h"
#include "matrix.h"
#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// plan for bfs serial implementation
// graphs are represented by matrices
// I need to write a bfs algorithm that works on adjacency matrices


// algorithm
// data structures: adjacency matrix (row=vertex col=neighbor), visited node list,
//		    pointer to current vertex of interest in visited list, 
// idea: pick a vertex at random from the neighbor list
// traverse the adjacency matrix for the first neighbor in the row 
// add look-up the neighbor in the visited list: if found, move on to next neighbor, if not,
// add to visited list
// keep iterating through the neighbors until all are found for the vertex
// move on to next vertex by consulting the visited list pointer
// do this until reach the end of the visited list


/* 
* Define the serial BFS algorithm
*/ 
void serial_bfs(struct Graph *G) {
	/* Initialize */ 
	int size = G->size; 	// get number of vertices
	int cidx = -1;			// initialize current index into G->traversal list

	int v, back;  // 'back' is the index of the last element in traversal list 
	back = 0; 
	
	while (true) {
		/* If size of visited list is equal to the number of vertices, break out of loop */
		if (++cidx == size)	break; 
			
		/* Find vertex to perform algorithm on */
		if (G->traversal[cidx] == -1) {
			v = find_unvisited(G); 				// find an unvisited vertex
			G->traversal[back++] = v; 			// add vertex to traversal list
			G->visited_map[v] = true; 			// update graph visited map
		} 

		/* Traverse the adjacency matrix for the first neighbor in the row */
		int col;	// col="column"
		for (col = 0; col < size; col++) {
			if (G->adjacency_mat->data[G->traversal[cidx]*size + col] == 1) {
				if (G->visited_map[col] == false) {		// if vertex has not been visited
					G->traversal[back++] = col; 			// add vertex to visited list
					G->visited_map[col] = true; 		// update visited map
				}
			}
		}
	}
	
}



















