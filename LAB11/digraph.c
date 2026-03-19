#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

struct node;
struct node {	
	int value;
	struct node *next;
};
typedef struct node Node;

typedef struct {
	Node *head;
} List;

typedef struct
{
    int n;
    List **adj;
} Graph;

void init_LL(List *l)
{
	/*Initializes an empty list.*/

	l->head = NULL;
}

void add_LL(List *l, int val)
{
	/*Adds a node with value "val" to the head of the list l.*/

	Node *n = (Node *) malloc(sizeof(Node));
	n->value = val;
	n->next = l->head;
	l->head = n;
}

Node *search_LL(List *l, int searchkey)
{
    Node *n;
    n = l->head;
    while(n != NULL && n->value != searchkey)
        n = n->next;
    return n;
}

void destroy_LL(List *l)
{
	/*Frees the space allocated for the list.*/

	Node *temp;
	temp = l->head;
	while(temp != NULL)
	{
		l->head = l->head->next;
		free(temp);
		temp = l->head;
	}
}

int length_LL(List *l)
{
    int ret;
    Node *t;
    ret = 0;
    t = l->head;
    while(t != NULL)
    {
        ret++;
        t = t->next;
    }
    return ret;
}

void init_Graph(Graph *G, int numvertices)
{
    int i;
    G->n = numvertices;
    G->adj = (List **) malloc(sizeof(List *) * G->n);
    for(i = 0; i < G->n; i++)
    {
        G->adj[i] = (List *) malloc(sizeof(List));
        init_LL(G->adj[i]);
    }
}

void destroy_Graph(Graph *G)
{
    int i;
    for(i = 0; i < G->n; i++)
        destroy_LL(G->adj[i]);
    free(G->adj);
}

void addEdge(Graph *G, int u, int v)
{
	/* Task 7a. This function should add a directed edge in G from u to v if u
	 * and v are distinct valid vertices of G and this edge is not already
	 * present in G.  */
    Node *nn=malloc(sizeof(Node));
    nn->value=v;
    nn->next=G->adj[u]->head;
    G->adj[u]->head=nn;
	
}

int isEdge(Graph *G, int u, int v)
{
	/* Task 7b. This function should return 1 if (u,v) is a directed  edge in G
	 * and 0 otherwise */
     Node *temp=G->adj[u]->head;
     while(temp!=NULL && temp->value!=v)
     {
        temp=temp->next;
     }
     if(temp==NULL)
     {
        return 0;
     }
     else{
        return 1;
     }
}

int outdegree(Graph *G, int u)
{
	/* Task 8a. Return the out-degree of the vertex u in G */
    Node *temp=G->adj[u]->head;
    int cnt=0;
    while(temp!=NULL)
    {
        cnt++;
        temp=temp->next;
    }

    return cnt;
}

int indegree(Graph *G, int u)
{
	/* Task 8b. Return the in-degree of the vertex u in G */
    int cnt=0;
    for(int i=0;i<G->n;i++)
    {
        Node *temp=G->adj[i]->head;
        while(temp!=NULL)
        {
            if(temp->value==u)
            {
                cnt++;
                break;
            }
            temp=temp->next;
        }
    }

    return cnt;
}

void printOutNeighbours(Graph *G, int u)
{
	/* Task 9a. Print all the out-neighbours of vertex u in G */
    Node *temp=G->adj[u]->head;
    while(temp!=NULL)
    {
        printf("%d ",temp->value);
        temp=temp->next;
    }

}

void printInNeighbours(Graph *G, int u)
{
	/* Task 9b. Print all the in-neighbours of vertex u in G */
    for(int i=0;i<G->n;i++)
    {
        Node *temp=G->adj[i]->head;
        while(temp!=NULL)
        {
            if(temp->value==u)
            {
                printf("%d ",i);
                break;
            }
            else{
                temp=temp->next;
            }
        }
    }

}

void remove_LL(List *l, int removekey)
{
    Node *t, *prev;
    prev = NULL;
    t = l->head;
    while(t != NULL && t->value != removekey)
    {
        prev = t;
        t = t->next;
    }
    if(t != NULL)
    {
        if(prev != NULL)
            prev->next = t->next;
        else
            l->head = t->next;
        free(t);
    }
}

void removeEdge(Graph *G, int u, int v)
{
	/* Task 10. Remove the directed edge (u,v) from G */

    Node *temp=G->adj[u]->head;
    Node *prev=NULL;
    while(temp!=NULL)
    {

        if(temp->value==v)
        {
            if(prev==NULL)
            {
                G->adj[u]->head=temp->next;
            }
            else{
                prev->next=temp->next;
            }
            
            

        }
        prev=temp;
        temp=temp->next;

    }
}

int showGraph(Graph *G)
{
    int i;
    FILE *fp;
    fp = fopen("graph.txt", "w");
    if(fp == NULL)
        return -1;
    if(G != NULL)
    {   
        for(i = 0; i < G->n; i++)
        {
            Node *t;
            fprintf(fp, "%d :", i);
            t = G->adj[i]->head;
            while(t != NULL)
            {
                if(t != G->adj[i]->head)
                    fprintf(fp, ",");
                fprintf(fp, " %d", t->value);
                t = t->next;
            }
            fprintf(fp, "\n");
        }
    }
    fclose(fp);
    return 0;
}

int** adjacencyMatrix(Graph *G)
{
	/* Task 11. Create an adjacency matrix of the given graph G and store
	it in the two-dimensional array adjMat initialied below and return the
	same */

    int i, j;
	int n;

	n = G->n;
	int **adjMat = malloc(n * sizeof(int *));
	if (adjMat == NULL) {
    	printf("Error: malloc Failed\n");
		return NULL;
	}

	for (int i = 0; i < n; i++) {
    	adjMat[i] = malloc(n * sizeof(int));
    	if (adjMat[i] == NULL) {
    		printf("Error: malloc Failed\n");
			return NULL;
    	}
	}
	
    for(i = 0; i < n; i++)
		for(j = 0; j < n; j++)
			adjMat[i][j] = 0;

	/* Enter your code here */
    for(int i=0;i<n;i++)
    {
        Node *temp=G->adj[i]->head;
        while(temp!=NULL)
        {
            int v=temp->value;
            adjMat[i][v]=1;
            temp=temp->next;
        }
    }

	return adjMat;
}

void printMatrix(int** mat, int n)
{
    int i, j;
    for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
			printf(" %d", mat[i][j]);
		printf("\n");
	}
	return;
}

void freeadjacencyMatrix(int** mat, int n)
{
	int i;
	for (i = 0; i < n; i++) 
	{
    	free(mat[i]);   // free each row
	}

	free(mat);   
	return;
}

void reverseGraph(Graph *G)
{
	/* Task 12. Modify the graph G by reversing all the edges in G */
    Adj=G->adj;
    int n=G->n;
    for(int i=0;i<n;i++)
    {
        Node *temp=G->adj[i]->head;
        
    }

}

int main()
{
    int i, j;
	char c;
    Graph G;
	int **adjMat;
    pid_t guiproc;
    showGraph(NULL); //clears the graph.txt file

    guiproc = fork();
    if(guiproc < 0)
        return -1;
    else if(guiproc == 0)
    {
        execlp("python3", "python3", "showdigraph.py", (char *) NULL);
    }
    printf("Enter the number of vertices: ");
    scanf("%d", &i);
    if(i < 0)
        return 0;
    init_Graph(&G, i);
    printf("Vertices numbered 0 to %d\n", G.n - 1);
    printf("Enter the edges (terminate by -1): ");
    while(1)
    {
        scanf("%d", &i);
        if(i < 0)
            break;
        scanf("%d", &j);
        if(j < 0)
            break;
        if(i < G.n && j < G.n)
        {
            if(isEdge(&G, i, j) == 1)
            {
                printf("Edge already exists.\n");
            }
            else
            {
                addEdge(&G, i, j);
                if(showGraph(&G) == -1)
                {
                    printf("Error writing to file.\n");
                    break;
                }
            }
        }
        else
            printf("Invalid edge (%d, %d).\n", i, j);
    }
    for(i = 0; i < G.n; i++)
    {
        printf("\nVertex %2d\n---------\n", i);
        printf("Out-degree: %d\nIn-degree: %d\n", outdegree(&G, i), indegree(&G, i));
        printf("Out-neighbours:");
        printOutNeighbours(&G, i);
        printf("\nIn-neighbours:");
        printInNeighbours(&G, i);
        printf("\n");
    }
    printf("\nadjacency Matrix:\n-----------------\n");
	adjMat = adjacencyMatrix(&G);
	printMatrix(adjMat, G.n);
	freeadjacencyMatrix(adjMat, G.n);
    showGraph(&G);
    while(1)
    {
        printf("\nadjacency Matrix:\n-----------------\n");
		adjMat = adjacencyMatrix(&G);
		printMatrix(adjMat, G.n);
		freeadjacencyMatrix(adjMat, G.n);
        printf("\nEdge to remove: ");
        scanf("%d", &i);
        if(i < 0)
            break;
        scanf("%d", &j);
        if(j < 0)
            break;
        if(i < G.n && j < G.n)
        {
            if(isEdge(&G, i,j) == 0)
                printf("(%d, %d) is not an edge.\n", i, j);
            else
            {
                removeEdge(&G, i, j);
                showGraph(&G);
            }
        }
    }
    printf("\n\nReversing Graph...\n");
    reverseGraph(&G);
    showGraph(&G);
    printf("\n\nEnter q to exit the program...\n");
	scanf("%c\n", &c);
	destroy_Graph(&G);
    kill(guiproc, SIGTERM);
    return 0;
}
