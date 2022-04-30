/*
* Author: Julia Zeng 
*
* Code description: Implementation of pthread multi-threaded version 
* of Breadth-First Search graph traversal algorithm.
*
*/ 


#include "bfs_pthread.h"
#include "param.h"
#include "matrix.h"
#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

// plan for pthread bfs implementation
// I need to figure out what can be parallelized from the serial bfs code
// from first glance, it doesn't seem to parallelize each vertex (i.e. 
// assign a thread to each vertex and offload the work). However, ther
// are two places that can be parallelized and that is the body of the 
// for-loop and the calls to find_unvisited(...). 


// algorithm
// data structures: adjacency matrix (row=vertex col=neighbor), visited node list,
//		    traversal list that keeps track of the bfs traversal 
// idea for for-loop: have V threads and each threads, each thread gets passed a
// value 'col' and indexes into visited_map to see if it is a neighbor or not. 
// If not, exit the thread. If so, continue enter the critical section of appending 
// neighbor to the visited_map (if not already there). Need two mutexes, on traversal
// list and 'back' variable. 

// idea for find_unvisited(...): Again, have V threads each indexing into G. 
// Each worker thread indexes into visited_map, the first thread to find an
// unvisited vertex enters the critical section, terminates all other worker
// threads and sets a global variable (return value).



// ok .... no this isn't going to work
// new idea: think of the tree graphs to help visualize the following. I will need to 
// use a count "barrier", an ARRAY of mutexes, and a global traversal list. The job of
// each vertex is to wake its neighbor by unlocking its mutex. <<-- this is some really good stuff


/*
* Define globals. 
*/
pthread_t *threads;	// array of |V| worker threads. Can try to make this an array instead if dynamic allocation is too slow
pthread_mutex_t qvm_mutex; 	// qvm_mutex="query_visited_map mutex"
int next_vertex; 	// next_vertex is set by query_visited_map and read by bfs_pthread(...) 



/* query_visited_map is a thread worker function that indexes into G->visited_map 
   to see if the thread was visited or not */
void query_visited_map(struct Graph *G, int i) {
	// no locking needed for G since read-only
	if (G->visited_map[i] == false) {
		// acquire mutex
		// 
	} else {
		// exit thread
		pthread_exit(); 
	}
} 



/* find_unvisited_pthread is a multi-threaded version of the serial find_unvisited(...)
   find_unvisited_pthread prototype is located in graph.h */
void find_unvisited_pthread(struct Graph *G) {
	// G->visited_map
	// initialize V threads
	
} 


/* 
* Define the pthread BFS algorithm
*/ 
void bfs_pthread(struct Graph *G) {
	/* Initialize */
	pthread_mutex_init(&qvm_mutex, NULL); 	// initialize mutex
	int size = G->size; 	// get number of vertices
	int cidx = -1;			// initialize current index into G->traversal list
	
	// initialize |V| worker threads
	threads = malloc(size * sizeof(pthread_t);	// need to free this at the end of bfs_pthread
	for (int i = 0; i < size; i++) {
		pthread_create(&threads[i], NULL, query_visited_map, 
	}
	
	
	
	
	
	
	

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





