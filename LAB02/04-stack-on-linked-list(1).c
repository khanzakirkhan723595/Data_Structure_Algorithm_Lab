/*
	Course:		CS2130 DSA Lab 
	Semester:	2026 Jan-Apr
	Lab No:		2
	File: 		4
	Aim: 		Implement the stack ADT using a singly linked list.
	Instructions:
		Complete the set of tasks listed here. Search for "Task".
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct pnode;
struct pnode {
	int data;
	struct pnode *next;
};
typedef struct pnode node;

typedef struct {
	node *top;
} stack;

void init(stack *s)
{
	/*Initializes a stack.*/

	s->top = NULL;
}
void destroy(stack *s)
{
	/*Frees the space allocated for the stack.*/

	node *temp;
	temp = s->top;
	while(temp != NULL)
	{
		s->top = s->top->next;
		free(temp);
		temp = s->top;
	}
}
int isempty(const stack *s)
{
	/*Task 1: This function should return 1 if the stack is empty and 0 otherwise*/
	return s->top==NULL;

}
int push(stack *s, int val)
{
	/*Task 3: This function pushes the value val into the stack. If this can't be done because the stack is
	full, then the function returns -1, otherwise it returns 0.*/
	
	node * newNode=(node*)malloc(sizeof(node));
	if(newNode==NULL)
	{
		return -1;
	}
	newNode->data=val;
	newNode->next=s->top;
	s->top=newNode;


	return 0;
}
int pop(stack *s)
{
	/*Task 4: This function pops a value from the stack and returns it. It returns -1 if the stack
	is empty.*/
	if(isempty(s))
	{
		return -1;
	}
	node *temp;
	temp=s->top;
	int val=temp->data;
	s->top=s->top->next;
	return val;



	return 0;
}
void printstack(stack *s)
{
	/*Task 5: This function prints the contents of the stack.*/
	node *temp=s->top;
	while(temp!=NULL)
	{
		printf("%d ",temp->data);
		temp=temp->next;
	}
	printf("\n");

}
int checkparantheses(const char *str, int len)
{
	/*Task 6: Function should return 1 if str is made up of the characters '(', ')', {', '}', '['
	and ']' only, and these parantheses are balanced, i.e. they should be correctly nested.
	Otherwise the function should return 0. The string str contains len characters.*/
	stack s;
	init(&s);
	for(int i=0;str[i]!='\0';i++)
	{
		char c=str[i];
		
		if(c=='(' || c=='{' || c=='[')
		{
			push(&s,c);
		}
		else if(c==')' || c=='}'  || c==']')
		{
			if(isempty(&s))
			{
				return 0;
			}
			char stop=pop(&s);
			
			if((c==')' && stop!='(') || (c=='}' && stop!='{') || (c==']' && stop!='['))
			{
				return 0;
			}
		}
		else{
			return 0;
		}
			
	}
	
	return isempty(&s);
	
	
}

int main()
{
	stack *s;
	int i;
	char str[100];
	s = (stack *) malloc(sizeof(stack));
	init(s);
	printf("Positive numbers go into the stack, 0 pops the stack, and any negative number terminates the program.\n");
	scanf("%d", &i);
	while(i >= 0)
	{
		if(i != 0)
		{
			if(push(s,i) == -1)
			{
				printf("\nCan't push %d, stack full.\n", i);
			}			
			printf("\nS: ");
			printstack(s);
		}
		else
		{
			int temp;
			temp = pop(s);
			if(temp != -1)
			{
				printf("\n-> %d\n", temp);
			}
			else
			{
				printf("\nStack empty.\n");
			}
		}
		scanf("%d",&i);
	}

	/*Repeatedly pops elements from the stack until it is empty.*/
	while(!isempty(s))
	{
		printf("\n-> %d",pop(s));
	}

	printf("\n");
	destroy(s);
	free(s);

	for(i = 0; i < 2; i++)
	{
		printf("Enter a string of parantheses: ");
		scanf("%s",str);
		if(checkparantheses(str,strlen(str)) == 1)
		{
			printf("It is a string of balanced parantheses.\n");
		}
		else
		{
			printf("It is not a string of balanced parantheses.\n");
		}
	}

	return 0;
}
