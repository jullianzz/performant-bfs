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
	q->size = 0; 
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
	
	/* Increment queue size */
	q->size ++; 
}

/* pop_queue removes and returns the first item of the queue ... unfinished*/ 
/*
int pop_queue(struct queue *q) {
	q->size--; 
	struct node *n = q->first_node; 
	q->first_node = q->first_node->next; 
	free(n); 
	return q->first_node; 	// popped item is NULL if queue empty
}
*/

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

/* search_queue traverses through the queue to see if a node with value 'v' exists
   Currently, at O(n) time, which is bad. Leave for now, refactor using hash-table 
   implementation later */
bool search_queue(struct queue *q, int v) {
	struct node *n = q->first_node; 
	for (int i = 0; i < get_queue_size(q); i++) {
		if (n->value == v) {
			return true; 
		}
		n = n->next;
	}
	return false;
}


/* compare two queues item by item to check if equal */
bool compare(struct queue *q1, struct queue *q2) {
	int s1 = q1->size; 
	int s2 = q2->size;
	if (s1 != s2) {
		return false;
	} else {
		struct node *n1 = q1->first_node;
		struct node *n2 = q2->first_node; 
		for (int i = 0; i < s1; i++) {
			if (n1->value != n2->value) {
				return false; 
			}
			n1 = n1->next;
			n2 = n2->next; 
		}
	}
	return true; 
}






