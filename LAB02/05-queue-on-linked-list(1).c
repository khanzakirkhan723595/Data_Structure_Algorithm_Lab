/*
	Course:		CS2130 DSA Lab 
	Semester:	2026 Jan-Apr
	Lab No:		2
	File: 		5
	Aim: 		Implement the queue ADT using a singly linked list.
	Instructions:
		Complete the set of tasks listed here. Search for "Task".
*/
#include <stdio.h>
#include <stdlib.h>
struct pnode;
struct pnode {
	int data;
	struct pnode *next;
};
typedef struct pnode node;

typedef struct {
	node *front;
	node *back;
} queue;

void init(queue *q)
{
	/*Initializes an empty queue q.*/

	q->front = NULL;
	q->back = NULL;
}
int isempty(queue *q)
{
	/*Task 1: This function should return 1 if the queue is empty and 0 otherwise.*/
	if(q->back==NULL)
	{
		return 1;
	}

	return 0;
}
void destroy(queue *q)
{
	/*Frees the space allocated for the queue.*/

	while(!isempty(q))
	{
		node *temp = q->front;
		q->front = q->front->next;
		free(temp);
	}
}
int enqueue(queue *q, int val)
{
	/*Task 3: This function adds the value val to the queue. It returns 0 if it successfully adds val
	to the queue and -1 if the queue is full.*/
	node * newNode = (node*)malloc(sizeof(node));
	if(newNode==NULL)
	{
		return -1;
	}
	newNode->data = val;
    newNode->next = NULL;
	if (q->back == NULL) { 
        
        q->front = q->back = newNode;
    } else {
        
        q->back->next = newNode;
        q->back = newNode;
    }
    return 0;

	return 0;
}
int dequeue(queue *q)
{
	/*Task 4: This function removes a value from the queue and returns it. It returns -1 if the queue
	is empty.*/
	if (q->front == NULL) { 
        return -1;
    }
    node *temp = q->front;
    int value = temp->data;
    
    q->front = q->front->next;

    
    if (q->front == NULL) {
        q->back = NULL;
    }
    return value;
}
void printqueue(queue *q)
{
	/*Task 5: This function prints the contents of the queue.*/
	node *temp = q->front;
    if (temp == NULL) {
        
        return;
    }
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
	
}
int main()
{
	queue *q;
	int i;
	q = (queue *) malloc(sizeof(queue));
	init(q);
	printf("Positive numbers go into the queue, 0 dequeues an element, and any negative number terminates the program.\n");
	do
	{
		scanf("%d",&i);
		if(i > 0)
		{
			if(enqueue(q,i) == -1)
			{
				printf("\nCan't insert %d, queue full.",i);
			}
			printf("\nQ: ");
			printqueue(q);
			printf("\n");
		}
		else if(i == 0)
		{
			printf("\n-> %d\nQ: ",dequeue(q));
			printqueue(q);		
			printf("\n");	
		}
	}
	while(i >= 0);

	printf("\nDequeuing the elements of the queue:");
	while(!isempty(q))
	{
		printf("\n-> %d\nQ: ",dequeue(q));
		printqueue(q);
	}
	printf("\n");
	destroy(q);
	free(q);
	return 0;
}
