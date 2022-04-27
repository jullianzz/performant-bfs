/*
* Author: Julia Zeng 
*
* Code description: Implementation of serial verion 
* of Breadth-First Search graph traversal algorithm.
*/ 


#include "serial.h"
#include "param.h"
#include "matrix.h"
#include "queue.h"
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

