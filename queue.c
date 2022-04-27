/* 
* Author: Julia Zeng
*
* Code description: Implementation of an unbounded queue data structure. 
*
*/


#include "queue.h"
#include <stdio.h>
#include <stdlib.h>


/* new_node creates a new node with value 'value' */ 
struct node *new_node(int value) {
	struct node *n = malloc(sizeof(struct node));
	n->value = value;
	n->next = NULL;
	return n;
}

/* new_queue creates a new queue structure and returns a pointer to it */ 
struct queue *new_queue() {
	struct queue *q = malloc(sizeof(struct queue));
	q->first_node = NULL;
	q->last_node = NULL; 
	return q;
}


/* push_queue creates a new node with value 'value' and pushes it to the back of the queue 'q' */ 
void push_queue(struct queue *q, int value) {
	/* Create a new node with value 'value' */ 
	struct node *n = new_node(value); 
	
	/* Check to see if the first_node and last_node are both NULL */
	if (q->first_node == NULL && q->last_node == NULL) {	// both are NULL
		q->first_node = n;	// point first_node and last_node to new node
		q->last_node = n; 	// set next of new node to NULL
		n->next = NULL; 
	} else {	// both are not NULL (shouldn't be possible that only one is NULL) 
		struct node *temp = q->last_node; 	// make a temp node pointer to point to current last node
		temp->next = n;		// set temp->next to new node
		n->next = NULL; 	// set new node->next to NULL
		q->last_node = n; 	// point last_node to new node
	}
}

/* pop_queue removes and returns the first item of the queue ... I think I don't need to impl. this*/ 
//int pop_queue(struct queue *q) {
	// empty for now
//}

/* get_queue_size returns the size of the queue */
int get_queue_size(struct queue *q) {
	return q->size; 
}

/* print_queue prints the values of the queue in order */ 
void print_queue(struct queue *q) {
  	int s = get_queue_size(q);
  	struct node *n = q->first_node;		// initialize a node pointer to iterate through queue
	printf("Queue is: ");
	for (int i = 0; i < s; i++) {
		printf("%d ", n->value); 
		n = n->next; 
	}
	printf("\n"); 
	printf("Size of queue is %d\n", s); 
}


