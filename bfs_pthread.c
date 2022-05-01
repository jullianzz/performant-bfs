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
// idea: think of the tree graphs to help visualize the following. I will need to 
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
int barrier_count; 			// barrier is a counter that is initialize by each vertex and decremented by each of its neighbors
int Back;					// Back tracks the index of the last element of the Traversal list



/* 
* Define global synchonization objects. 
*/
pthread_mutex_t *mutexes; 		// mutexes is an array of |V| mutexes where each mutex is associated with a vertex
pthread_mutex_t Traversal_lock;	// Traversal_lock protects the Traversal global
pthread_mutex_t Back_lock; 
pthread_mutex_t Visited_Map_lock; 
pthread_mutex_t barrier_count_lock;
pthread_barrier_t Barrier; 


/*
* Define pthread worker function.
*/ 
/* look_for_neighbors */
void *look_for_neighbors(void *argv) {

	/* Parse arg */
	int v = ((args_ptr) argv)->v;
	struct Graph *G = ((args_ptr) argv)->G; 
	
	/* Block until node mutex is released */
	pthread_mutex_lock(&mutexes[v]);
	
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
 		 		/* Acquire locks */
 		 		pthread_mutex_lock(&Traversal_lock);	// lock Traversal list because RD and WR
 		 		pthread_mutex_lock(&Back_lock);			// lock Back_lock because RD and WR
 		 		pthread_mutex_lock(&barrier_count_lock);// lock barrier_count because RD and WR
 		 		
 		 		/* Update metadata */ 
 		 		barrier_count++; 
		 		Traversal[Back] = v; 
		 		Back++;  
		 		Visited_Map[v] = true; 					// update Visited_Map
		 		
		 		/* Release locks */
		 		pthread_mutex_unlock(&Traversal_lock);	// unlock Traversal lock
 		 		pthread_mutex_unlock(&Back_lock);		// lock Back_lock because RD and WR
  		 		pthread_mutex_unlock(&barrier_count_lock);	// lock barrier_count because RD and WR
		 	}
		 	pthread_mutex_unlock(&Visited_Map_lock);	// unlock Visited_Map_lock
		} 
 	}
 	
 	/* Wait for all nodes of current layer to finish by using a barrier */
 	int barrier_ret = pthread_barrier_wait(&Barrier);	
 	
 	/* Set the barrier for the next layer. Note: Only one node per layer needs to do this */		
 	if (barrier_ret == PTHREAD_BARRIER_SERIAL_THREAD) {	
	 	pthread_barrier_init(&Barrier, NULL, barrier_count); 
	 	barrier_count = 0; 							
 	}

 	/* For loop to release neighboring mutexes */
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
	
	/* Error checking */
	if (size == 0) {
		perror("ERROR:\tGraph is empty");
		return NULL; 
	}
		
	int i = 0; 
	
	
	/* Initialize all synchronization objects */ 
	mutexes = malloc(size * sizeof(pthread_mutex_t));	// initialize mutex array, TODO: need to free this at the end of bfs_pthread
	for (i = 0; i < size; i++) {
		pthread_mutex_init(&mutexes[i], NULL); 			// initialize node mutex
		pthread_mutex_lock(&mutexes[i]);				// lock node mutex
	}
	pthread_mutex_init(&Traversal_lock, NULL); 			// initialize Traversal lock 
	pthread_mutex_init(&Back_lock, NULL); 				// initialize Back_lock
	pthread_mutex_init(&Visited_Map_lock, NULL); 		// initialize Visited_Map_lock
	pthread_mutex_init(&barrier_count_lock, NULL); 		// initialize barrier_lock
	pthread_barrier_init(&Barrier, NULL, 0);			// initialize Barrier to 0 (no previous layers to wait for)
	
	
	/* Initialize Traversal list */ 
	Traversal = malloc(size * sizeof(int));
	for (i = 0; i < size; i++) {	
		Traversal[i] = -1; 
	}

	/* Initialize Visited_Map */
	Visited_Map = malloc(size * sizeof(bool));
	for (i = 0; i < size; i++) {
		Visited_Map[i] = false; 
	}
	
	/* Initialize barrier_count and Back */
	barrier_count = 0; 
	Back = 0;

	args_ptr argv = malloc(size * sizeof(args)); // initialize arguments list pointer
	/* Initialize the pthreads */
	Threads = malloc(size * sizeof(pthread_t));
	for (i = 0; i < size; i++) {
		argv[i].v = i;
		argv[i].G = G; 
		pthread_create(Threads+i, NULL, &look_for_neighbors, argv+i); 
	} 
	
	/* Release vertex 0 to begin traversal */
	pthread_mutex_unlock(&mutexes[0]);			// unlock mutex 0


	/* Main thread waits for worker threads to finish */
	for (i = 0; i < size; i++) {
		pthread_join(Threads[i], NULL); 
	}
	
	/* Free memory */
	free(argv);
	free(Visited_Map);
	//free(Traversal); 
	free(Threads);
	
	return Traversal; 
}





