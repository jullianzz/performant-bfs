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
* Define data structures.
*/
typedef struct {
	struct Graph *G;
	int v;
} args, *args_ptr;


/*
* Define globals. 
*/
pthread_t *Threads;			// array of |V| worker threads. Can try to make this an array instead if dynamic allocation is too slow
int *Traversal;				// global traversal list
bool *Visited_Map;			// global visited map
int next_vertex; 			// next_vertex is set by query_visited_map and read by bfs_pthread(...) 
int barrier; 				// barrier is a counter that is initialize by each vertex and decremented by each of its neighbors
int Back;					// Back tracks the index of the last element of the Traversal list
// TODO: add global array for nodes that have run look_for_neighbors to completion
// TODO: each node gets a pthread_barrier_t instead ? to block before release neighbor mutexes



/* 
* Define global synchonization locks. 
*/
pthread_mutex_t *mutexes; 		// mutexes is an array of |V| mutexes where each mutex is associated with a vertex
pthread_mutex_t Traversal_lock;	// Traversal_lock protects the Traversal global
pthread_mutex_t Back_lock; 
pthread_mutex_t Visited_Map_lock; 
pthread_mutex_t barrier_lock;



/*
* Define pthread worker function.
*/ 
/* look_for_neighbors looks for the  */
void *look_for_neighbors(void *argv) {
	/* Cast void* to args_ptr */
	args_ptr arg = (args_ptr) argv;
	
	/* Parse arg */
	int v = arg->v;
	struct Graph *G = arg->G; 
	
	// busy waiting check if barrier = 0 ??? 
	/* Block until mutex is released */
	pthread_mutex_unlock(&mutexes[v]);
	
	/* Get Graph metadata */
	int size = G->size; 
	
	/* Look for your neighbors */  
 	int num_neighbors = 0; 								// initialize neighbors counter
 	int i; 
 	/* Iterate through row v of Graph G. Note: no lock needed on G because read-only */ 
 	for (i = 0; i < size; i++) {
 		if (G->adjacency_mat->data[v * size + i] == 1) {
 			num_neighbors++;							// increment num_neighbors
		 	pthread_mutex_lock(&Visited_Map_lock);		// lock Visited_Map because RD and WR
 		 	if (Visited_Map[v] == false) {				// query the Visited_Map 
 		 		pthread_mutex_lock(&Traversal_lock);	// lock Traversal list because RD and WR
 		 		pthread_mutex_lock(&Back_lock);			// lock Back_lock because RD and WR
		 		Traversal[Back] = v; 
		 		pthread_mutex_unlock(&Traversal_lock);	// unlock Traversal lock
		 		Back++;  
		 		Visited_Map[v] = true; 					// update Visited_Map
		 	}
		 	pthread_mutex_unlock(&Visited_Map_lock);	// unlock Visited_Map_lock
		} 
 	}
 	
 	/* Set barrier */
 	pthread_mutex_lock(&barrier_lock);		// lock barrier
 	barrier = num_neighbors;					// set barrier
 	pthread_mutex_unlock(&barrier_lock);	// unlock barrier
 	// hmm this may not work, what if another node changes barrier 
 	
 	
 	/* TODO: would put pthread_barrier_t here */
 	
 	
 	
 	/* For loop to release neighboring mutexes */
 	// TODO: refactor to not use for-loop
 	for (i = 0; i < size; i++) {
 		if (G->adjacency_mat->data[v * size + i] == 1) {
 			pthread_mutex_unlock(&mutexes[i]);			// unlock neighbor mutex
 		}
 	} 
 	
 	/* Exit thread ? */
 	
 	return NULL;
}
	
	

/* 
* Define the pthread BFS algorithm
*/ 
int *bfs_pthread(struct Graph *G) {
	/* Get Graph metadata */ 
	int size = G->size; 	// get number of vertices
	//int cidx = -1;			// initialize current index into G->traversal list
	
	/* Error checking */
	if (size == 0) {
		perror("ERROR:\tGraph is empty"); 
	}
		
	/* Initialize */
	/* Initialize mutex array */ 
	mutexes = malloc(size * sizeof(pthread_mutex_t));	// need to free this at the end of bfs_pthread
	int i = 0; 
	for (i = 0; i < size; i++) {
		pthread_mutex_init(&mutexes[i], NULL); 	// invoke mutex initializer
	}
	/* Initialize global traversal list */ 
	for (i = 0; i < size; i++) {	
		Traversal[i] = -1; 
	}
	pthread_mutex_init(&Traversal_lock, NULL); // initialize Traversal lock 
	pthread_mutex_unlock(&Traversal_lock);		// unlock Traversal mutex
	/* Initialize global visited map */
	for (i = 0; i < size; i++) {
		Visited_Map[i] = false; 
	}
	/* Initialize next_vertex and barrier */
	next_vertex = 0; 	// sets the starting vertex as vertex 0
	barrier = 0; 

	
	args_ptr argv; 
	argv = malloc(size * sizeof(args)); 
	/* Initialize the pthreads */
	for (i = 0; i < size; i++) {
		argv[i].v = i;
		argv[i].G = G; 
		// TODO: refactor with a macro to create inline struct pointer to pass cleanly to pthread_create
		pthread_create(Threads+i, NULL, &look_for_neighbors, argv+i); 
	} 
	
	/* Release vertex 0 to begin traversal */
	pthread_mutex_unlock(&mutexes[0]);		// unlock mutex 0
	
	/* Free argv */
	free(argv);
	
	/* Main thread waits for worker threads to finish */
	for (i = 0; i < size; i++) {
		pthread_join(Threads[i], NULL); 
	}
	
	return Traversal; 
}





