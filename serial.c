/*
* Author: Julia Zeng 
*
* Code description: Implementation of serial version 
* of Breadth-First Search graph traversal algorithm.
*
*/ 


#include "serial.h"
#include "param.h"
#include "matrix.h"
#include "queue.h"
#include "graph.h"
#include <stdio.h>
#include <stdlib.h>


// TODO : serial code

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
* Define global data structures 
*/ 



/*
* Define helper functions 
*/ 



/* 
* Define the serial BFS algorithm
*/ 
struct queue *serial_bfs(struct Graph *G) {
	/* Initialize */ 
	int size = G->size; 	// get number of vertices
	struct queue *visited_list = new_queue(); 	// declare list that keeps track of already visited vertices
	struct node *current_v = malloc(sizeof(struct node)); 	// initialize a pointer to visited list
	
	/* Select a random starting vertex */ 
	int v = rand() % size;	// generate a random number between 0 and size-1
	push_queue(visited_list, v);	// add vertex to visited list
	current_v = visited_list->first_node;	// point current_v to front of visited list
	
	while (true) {
		/* Traverse the adjacency matrix for the first neighbor in the row */
		int col;
		for (col = 0; col < size; col++) {
			if (G->adjacency_mat->data[(current_v->value)*size + col] == 1) {
				if (!search_queue(visited_list, current_v->value)) {	// if vertex not in visited list, add vertex to visited list
					push_queue(visited_list, current_v->value);	
				}
			}
		}
		
		/* Find next vertex to perform algorithm on */
		current_v = current_v->next;	// look for next vertex in visited list
		
		/* Check if reached the end of the adjacency list, stop if so */
		if (current_v == NULL) {
			break; 
		}
	}
	
	return visited_list; 
}



















