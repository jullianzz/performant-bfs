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
#include "benchmark.h"
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

//struct timespec time_start, time_stop;
/*
* Define globals. 
*/
pthread_t *Threads;			// array of |V| worker threads. Can try to make this an array instead if dynamic allocation is too slow
int *Traversal;				// global traversal list
bool *Visited_Map;
int barrier_count; 			// barrier is a counter that is initialize by each vertex and decremented by each of its neighbors
int Back;					// Back tracks the index of the last element of the Traversal list
int current_layer;			// current layer (first layer is layer 0)



/* 
* Define global synchonization objects. 
*/
pthread_mutex_t *mutexes; 				// mutexes is an array of |V| mutexes where each mutex is associated with a vertex
pthread_mutex_t Critical_Section_lock;	// Traversal_lock protects the Traversal global
pthread_mutex_t Visited_Map_lock;
pthread_barrier_t *Barriers;			// each layer gets a barrier  



/*
* Define pthread worker function.
*/ 
/* look_for_neighbors */
void *look_for_neighbors(void *argv) {

	/* Parse arg */
	int cv = current_layer;						// record value of current layer
	int v = ((args_ptr) argv)->v;
	struct Graph *G = ((args_ptr) argv)->G; 
    /* Get Graph metadata */
	int size = G->size; 
    /* Initialize neighbor list */
    int *neighbors = malloc(size * sizeof(int));

    int i, num_neighbors; 
    /* Find your neighbors */
    for (i = 0, num_neighbors = 0; i < size; i++)
        if (G->adjacency_mat->data[v * size + i] == 1) 
            neighbors[num_neighbors++] = i; 

	
	/* Block until node mutex is released */
	pthread_mutex_lock(&mutexes[v]);

    /* Each node of the layer adds itself to the global Traversal list */
	pthread_mutex_lock(&Critical_Section_lock);		// lock C.S.
	Traversal[Back++] = v; 
	pthread_mutex_unlock(&Critical_Section_lock);	// unlock C.S.
	
 	/* For loop to set next barrier initialization */
 	for (i = 0; i < num_neighbors; i++) {
        pthread_mutex_lock(&Visited_Map_lock);	// unlock neighbor mutex
        if (Visited_Map[neighbors[i]] == false) {
            Visited_Map[i] = true; 
            barrier_count++; 
        }
        pthread_mutex_unlock(&Visited_Map_lock);	// unlock neighbor mutex
 	}

 	/* Wait for all nodes of current layer to arrive at barrier */
 	int barrier_ret = pthread_barrier_wait(&Barriers[cv]);	
 	
 	
 	/* Set the barrier for the next layer. Note: Only one node per layer needs to do this */		
 	if (barrier_ret == PTHREAD_BARRIER_SERIAL_THREAD) {	
        if (current_layer > size-1) {
            pthread_barrier_init(&Barriers[++current_layer], NULL, barrier_count);	// set barrier1
            barrier_count = 0; 	
        }	
 	}


 	/* For loop to release neighboring mutexes */
    for (i = 0; i < num_neighbors; i++)
        pthread_mutex_unlock(&mutexes[neighbors[i]]);			// unlock neighbor mutex

    free(neighbors);
 	
 	
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
	mutexes = malloc(size * sizeof(pthread_mutex_t));	// initialize mutex array
	for (i = 0; i < size; i++) {
		pthread_mutex_init(&mutexes[i], NULL); 			// initialize node mutex
		pthread_mutex_lock(&mutexes[i]);				// lock node mutex
	}
	Barriers = malloc(size * sizeof(pthread_barrier_t));// initialize barrier array
	Traversal = malloc(size * sizeof(int));				// initialize barrier array
	Visited_Map = malloc(size * sizeof(bool));			// initialize barrier array
	pthread_barrier_init(&Barriers[0], NULL, 1);		// initialize layer 0 Barrier to 1 (no previous layers to wait for)
	pthread_mutex_init(&Critical_Section_lock, NULL); 	// initialize Traversal lock 
	pthread_mutex_init(&Visited_Map_lock, NULL); 		// initialize Visited_Map_lock


	/* Initialize other globals */
	barrier_count = 0; 
	Back = 0;
	current_layer = 0;

	args_ptr argv = malloc(size * sizeof(args)); 		// initialize arguments list pointer
	/* Initialize the pthreads */
	Threads = malloc(size * sizeof(pthread_t));
	for (i = 0; i < size; i++) {
		argv[i].v = i;
		argv[i].G = G; 
		pthread_create(Threads+i, NULL, &look_for_neighbors, argv+i); 
	} 
	
	//clock_gettime(CLOCK_REALTIME, &time_start);
	/* Release vertex 0 to begin traversal */
	pthread_mutex_unlock(&mutexes[0]);			// unlock mutex 0


	/* Main thread waits for worker threads to finish */
	for (i = 0; i < size; i++) 
		pthread_join(Threads[i], NULL); 

	//clock_gettime(CLOCK_REALTIME, &time_stop);
	//printf("size %d time: %f\n", size, interval(time_start, time_stop));
	/* Free memory */
	free(argv);
	free(Visited_Map);
	// free(Traversal); 
	free(Threads);
	free(mutexes);
	
	return Traversal;  // return Traversal
	// return NULL;
}





