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
//#include <pthread.h>

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
// threads and sets a global variable (return value) .


/* 
* Define the pthread BFS algorithm
*/ 
void bfs_pthread(struct Graph *G) {
	
}





