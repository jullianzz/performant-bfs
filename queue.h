/* 
* Author: Julia Zeng
*
* Code description: Implementation of an unbounded queue data structure. 
*
*/


#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <stdbool.h> 

/* Define abstract data structure for nodes in queue */ 
struct node {
	int value;
	struct node *next;
};

/* Define node constructor prototype */
struct node *new_node(int value);


/* Define abstract data structure for queue */ 
struct queue {
	struct node *first_node;
	struct node *last_node;
	int size; 
};

/* Define prototypes for queue functionality */
struct queue *new_queue();
void push_queue(struct queue *q, int value);
// int pop_queue(struct queue *q);
void print_queue(struct queue *q);
int get_queue_size(struct queue *q); 
bool search_queue(struct queue *q, int v); 



#endif
