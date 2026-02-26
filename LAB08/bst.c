#include <stdio.h>
#include <stdlib.h>

#define MAXNODES 4000

struct node;
typedef struct node
{
	int data;
	struct node *left;
	struct node *right;
	struct node *p;
} Node;

typedef struct
{
	Node *root;
} BSTree;

void init(BSTree *T)
{
	T->root = NULL;
}

int height(Node *x)
{
	int max, hl, hr;
	if(x == NULL)
		return -1;
	hl = height(x->left);
	hr = height(x->right);
	max = (hl <= hr) ? hr : hl;
	return max + 1;
}

void printTree(BSTree *T)
{
	Node *a[MAXNODES], *b[MAXNODES];
	int len, arrempty, fieldsize;
	fieldsize = 1 << (height(T->root) + 2);
	a[0] = T->root;
	arrempty = 0;
	len = 1;
	while(!arrempty)
	{
		int i, j;
		arrempty = 1;
		printf("\n\n");
		j = 0;
		for(i = 0; i < len; i++)
		{
			int k;
			for(k = 0; k < (fieldsize >> 1) - 1; k++)
			{
				printf(" ");
			}
			if(a[i] != NULL)
			{
				arrempty = 0;
				
				// if(a[i]->left!=NULL)
				// {
				// 	printf(" left is: %d",a[i]->left->data);

				// }
				// // if(a[i]!=NULL)
				// // {
				// // 	printf("parent of root is: %d",a[i]->p->data);
				// // }
				// printf(" root is: %d",a[i]->data);

				// if(a[i]->right!=NULL)
				// {
				// 	printf(" right is: %d",a[i]->right->data);
				// }
				printf("%2d", a[i]->data);
				b[j++] = a[i]->left;
				b[j++] = a[i]->right;
			}
			else
			{
				printf("  ");
				b[j++] = NULL;
				b[j++] = NULL;
			}
			for(k = 0; k < (fieldsize >> 1) - 1; k++)
			{
				printf(" ");
			}
		}
		len = len << 1;
		fieldsize = fieldsize >> 1;
		for(i = 0; i < len; i++)
		{
			a[i] = b[i];
		}
	}
	printf("\n");
}

void destroyNode(Node *x)
{
	if(x == NULL)
		return;
	destroyNode(x->left);
	destroyNode(x->right);
	free(x);
}

void destroy(BSTree *T)
{
	destroyNode(T->root);
	T->root = NULL;
}

void inorder(Node *x)
{
	/*Task 1: This function should print the data fields of the nodes of the subtree rooted at node x in the order in
	which the nodes will be visited by an inorder traversal of the subtree rooted at x.*/
	if(x==NULL)
	{
		return;
	}
	inorder(x->left);
	printf("%d",x->data);
	inorder(x->right);

}

Node *minimum(Node *x)
{
	/*Task 2: This function should return a pointer to the node that will be visited first by an inorder
	traversal of the subtree rooted at x. You can assume that x is not NULL.*/
	// while(x->left!=NULL)
	// {
	// 	x=x->left;
	// }
	// return x;
	if(x->left==NULL)
	{
		return x;
	}
	minimum(x->left);
	return NULL;
}

Node *maximum(Node *x)
{
	/*Task 3: This function should return a pointer to the node that will be visited last by an inorder
	traversal of the subtree rooted at x. You can assume that x is not NULL.*/
	// while(x->right!=NULL)
	// {
	// 	x=x->right;
	// }
	// return x;
	if(x->right==NULL)
	{
		return x;
	}
	minimum(x->right);
	return NULL;
}

Node *successor(Node *x)
{
	/*Task 4: This function should return a pointer to the node that will be visited just after node x by an inorder
	traversal of the subtree rooted at x. You can assume that x is not NULL. The function should return NULL if x is the
	vertex that is visited last by the inorder traversal.*/
	if(x->right!=NULL)
	{
		return minimum(x->right);
	}
	Node *par=x->p;
	while (par!=NULL && x==par->right)
	{
		x=par;
		par=par->p;
	}


	return par;
}

Node *predecessor(Node *x)
{
	/*Task 5: This function should return a pointer to the node that will be visited just before node x by an inorder
	traversal of the subtree rooted at x. You can assume that x is not NULL. The function should return NULL if the vertex
	x is the vertex that is visited first by the inorder traversal.*/
	if(x->left!=NULL)
	{
		return maximum(x->left);
	}
	Node *par=x->p;
	while (par!=NULL && x==par->left)
	{
		x=par;
		par=par->p;
	}


	return par;
}

Node *search(Node *x, int key)
{
	/* Task 6: If there exists a node having the value key in its data field in the subtree rooted at the node x, then this
	function should return the pointer to such a node. If no such node exists, the function should return NULL.*/
	/*Node *curr=x;
	while(curr!=NULL)
	{
		if(key==curr->data)
		{
			return curr;
		}
		else if(key<curr->data)
		{
			curr=curr->left;
		}
		else{
			curr=curr->right;
		}
	}*/

	if(x==NULL || x->data==key)
	{
		return x;
	}
	
	if(key<x->data)
	{
		return search(x->left,key);
	}
	else{
		return search(x->right,key);
	}
	return NULL;
}

void insert(BSTree *T, Node *x)
{
	/* Task 7: This function inserts the node x in the correct position in the binary search tree T (based
	on the value in x->data). You can assume that x->left and x->right are both equal to NULL.*/
	//Node *newNode = (Node*)malloc(sizeof(Node));
	//newNode=x;
	Node *parent=NULL;
	Node *curr=T->root;
	while(curr!=NULL)
	{
		parent=curr;
		if(x->data<curr->data)
		{
			curr=curr->left;
		}
		else{
			curr=curr->right;
		}
	}
	x->p=parent;
	if(parent==NULL)
	{
		T->root=x;
		//return;
	}
	else if(x->data<parent->data)
	{
		parent->left=x;
		//x->p=curr;
	}
	else{
		parent->right=x;
		//x->p=curr;
	}

}


void transplant(BSTree *T, Node *u, Node *v)
{
	/* This is a placeholder for the transplant function taught in class. You could implement this as a subroutine that
	can be used for Task 8, if needed. */

}

void delete(BSTree *T, Node *x)// x should be non-null
{
	/* Task 8: This function should delete the node x from the binary search tree T. You can assume that x is not equal
	to NULL. Do not call free(x). */


}

int main()
{
	BSTree T;
	Node *n;
	int i;
	init(&T);
	printf("\nBinary search tree (for integers in the range 1-99).\n\n");
	while(1)
	{
		printf("Enter key value to insert or delete (+x inserts x, -x removes x, zero terminates): ");
		scanf("%d", &i);
		if(i == 0)
			break;
		if(i < 0)
		{
			i = -i;
			n = search(T.root, i);
			if(n == NULL)
			{
				printf("Key %d not found in tree.\n", i);
				continue;
			}
			else
			{
				printf("\nRemoving node with key value %d...", i);
				delete(&T, n);
				free(n);
			}
		}
		else
		{
			Node *n;
			n = (Node *) malloc(sizeof(Node));
			n->left = NULL;
			n->right = NULL;
			n->data = i;
			printf("\nInserting node with key value %d...", i);
			insert(&T, n);
		}
		printTree(&T);
	}
	printf("\nInorder traversal: ");
	inorder(T.root);
	printf("\n");

	while(1)
	{
		printf("\nEnter key value to locate (zero to terminate): ");
		scanf("%d", &i);
		if(i <= 0)
			break;
		else
		{
			int j;
			Node *m;
			n = search(T.root, i);
			if(n == NULL)
			{
				printf("Key %d not found in tree.\n", i);
				continue;
			}
			j = 0;
			m = n;
			while(1)
			{
				if(m == n)
				{
					printf("At node with key value: %d\n", n->data);
					printf("Minimum of subtree: %d\n", minimum(n)->data);
					printf("Maximum of subtree: %d\n", maximum(n)->data);
					printTree(&T);
				}
				printf("\nStep (positive steps forward, negative steps backward, zero terminates): ");
				scanf("%d", &j);
				if(j == 0)
					break;
				if(j > 0)
				{
					printf("Stepping forward...\n");
					m = successor(n);
					if(m == NULL)
						printf("No successor.\n");
				}
				else
				{
					printf("Stepping backward...\n");
					m = predecessor(n);
					if(m == NULL)
						printf("No predecessor.\n");
				}
				if(m != NULL)
					n = m;
			}
		}
	}
	destroy(&T);
	return 0;
}
