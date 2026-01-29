/*
	Course:		CS2130 DSA Lab 
	Semester:	2026 Jan-Apr
	Lab No:		2
	File: 		2
	Aim: 		Implement the queue ADT using an array.
	Instructions:
		Complete the set of tasks listed here. Search for "Task".
*/
#include <stdio.h>
#include <stdlib.h>
typedef struct {
	int *data;
	int front;
	int back;
	int size;
} queue;
void init(queue *q, int sz)
{
	/*Initializes a queue having size sz.*/

	q->data = (int *) malloc(sizeof(int)*sz);
	q->front = 0;
	q->back = 0;
	q->size = sz;
}
void destroy(queue *q)
{
	/*Frees the space allocated for the queue.*/

	free(q->data);
}
int isempty(queue *q)
{
	/*Task 1: This function should return 1 if the queue is empty and 0 otherwise.*/
	if((q->front)>=(q->back))
		return 1;
	return 0;
}
int isfull(queue *q)
{
	/*Task 2: This function should return 1 if the queue is full and 0 otherwise.*/

	if((q->back)==(q->size-1))
		return 1;
	return 0;
}
int enqueue(queue *q, int val)
{
	/*Task 3: This function adds the value val to the queue. It returns 0 if it successfully adds val
	to the queue and -1 if the queue is full.*/
	if(isfull(q))
	{
		return -1;
	}
	q->data[q->back]=val;
	q->back++;

	return 0;
}
int dequeue(queue *q)
{
	/*Task 4: This function removes a value from the queue and returns it. It returns -1 if the queue
	is empty.*/
	if(isempty(q))
	{
		return -1;
	}
	int popped=q->data[q->front];
	q->front++;

	return popped;
}
void printqueue(queue *q)
{
	/*Task 5: This function prints the contents of the array q->data, with the special condition that
	it prints a * for each position of the array that currently does not contain an element of the
	queue.*/
	
	for(int i=0;i<q->size;i++)
	{
		if(i>=q->front && i<q->back)
		{	printf("%d ",q->data[i]);
		}
		else{
			printf("* ");
		}
		
	}
	
	printf("\n");
	
}
int main()
{
	queue *q;
	int i;
	q = (queue *) malloc(sizeof(queue));
	init(q,10);
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
