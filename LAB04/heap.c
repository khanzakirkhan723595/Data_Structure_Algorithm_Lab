/*
	Course:		CS2130 DSA Lab 
	Semester:	2026 Jan-Apr
	Lab No:		4
	Aim: 		Implement a min-heap and some operations on it.
	Instructions:
		1.	Read a list of numbers from the terminal, store it in a min-heap, and perform operations
			on the heap.
		2.	You can also read the list by redirecting a file data.txt to the input .
		3.  For ease of formatting, you can assume that all input numbers are in the range 10 -- 99.
		4.	Complete a set of given tasks. Search for "Task".
*/

#include <stdio.h>
#include <stdlib.h>

#define MAXLEN 1000

typedef struct {
	int data[MAXLEN];
	int size;
} heap;

int log_2(int val)
{
	/* Helper Function for printheap() */

	int ret = -1;
	while(val != 0)
	{
		val >>= 1;
		ret++;
	}
	return ret;
}

int isfull(heap *h)
{
	return (MAXLEN == h->size);
}

int isempty(heap *h)
{
	return (h->size == 0);
}

int parent(int i)
{
	return (i-1)/2;
}

int left(int i)
{
	return 2*i+1;
}

int right(int i)
{
	return 2*i+2;
}

int valueat(heap *h, int pos)
{
	/* Returns the value at position pos of the array h->data, or -1 if pos is beyond the length
	   of the array h->data. */

	if(pos < h->size)
	{
		return h->data[pos];
	}
	return -1;
}

void printheap(heap *h)
{
	/* Helper function which prints a heap formatted as a tree */

	int level, i, j, fieldsize, height;
	height = log_2(h->size);
	fieldsize = 4;
	for(i = 0; i < height; i++)
	{
		fieldsize *= 2;
	}

	level = 1;
	i = 0;
	printf("\n");
	while(i < h->size)
	{
		if(i == level)
		{
			fieldsize /= 2;
			printf("\n");
			level = (level + 1) * 2 - 1;
		}
		for(j = 0; j < (fieldsize - 2)/2; j++)
		{
			printf(" ");
		}
		printf("%2d", h->data[i]);
		for(j = 0; j < (fieldsize - 2)/2; j++)
		{
			printf(" ");
		}
		i++;
	}
	printf("\n");
}

void swap(int a[],int i,int j,heap *h)
{
	// if(i<0 || i>=h->size || j<0 || j>=h->size)
	// {
	// 	return;
	// }
	int temp=a[i];
	a[i]=a[j];
	a[j]=temp;
	return;
}

void heapify(heap *h, int indx)
{
	/* Task 1: Implement the Heapify procedurei 
	(Check the pseudocode given for the details). */
	int l=left(indx);
	int r=right(indx);
	int Smallest=indx;
	if(l<h->size && valueat(h,l)<valueat(h,Smallest))
		Smallest=l;
	if(r<h->size && valueat(h,r)<valueat(h,Smallest))
		Smallest=r;

	if(Smallest!=indx)
	{
		swap(h->data,indx,Smallest,h);
		heapify(h,Smallest);
	}
	
	

}

void buildheap(heap *h, const int *arr, int len)
{
	/* Task 2 : Implement the Build-Heap procedure which takes all the 
	elements from arr and then builds a heap h. Do not change the contents
	of arr. */
	for(int i=0;i<len;i++)
	{
		h->data[i]=arr[i];
	}
	h->size=len;
	int n=h->size;
	for(int i=(n/2)-1;i>=0;i--)
	{
		heapify(h,i);
	}
	

}

void floatup(heap *h, int i)
{
	/* Task 3 : Implement the "float-up" procedure. 
	(Check the pseudocode given for the details). */
	/* It floats up the value at index i until it reaches a node whose parent
	node contains a value lesser than or equal to it, or until it reaches
	the root node. */
	if(i==0 || valueat(h,parent(i))<=valueat(h,i))
		return;
	swap(h->data,parent(i),i,h);
	floatup(h,parent(i));

}

void changevalue(heap *h, int indx, int newval)
{
	/* Task 4 : This procedure changes the value at h->data[indx] to newval and
	updates the array h->data so that it still satisfies the min-heap property. */
	int initialval=valueat(h,indx);
	if(initialval<newval)
	{
		heapify(h,indx);
	}
	else{
		floatup(h,indx);
	}


}

int insert(heap *h, int val)
{
	/* Task  5: Implement the Insert procedure. 
		Return -1 if the heap is full and 0 otherwise */
	if(isfull(h))
	{
		return -1;
	}
	
	h->size++;
	int n=h->size;
	h->data[n-1]=val;
	floatup(h,h->size-1);
	return 0;

}

int extractmin(heap *h)
{
	/* Task 6: Implement the Extract-Min operation. 
		Return -1 if the heap is empty and the extracted value otherwise.
		Make sure that the modified array is heapified */
	if(isempty(h))
	{
		return -1;
	}
	int mini=h->data[0];
	int n=h->size;
	h->data[0]=h->data[n-1];
	h->size--;
	heapify(h,0);


	return mini;
}

void heap_sort(int *arr, int length)
{
	/* Task 7 : Implement Heap Sort procedure. This procedure sorts an input
	array by converting it into a heap and then repeatedly extracting the
	minimum element. Assume that length <= MAXLEN. */

	heap h;
	int i;
	for (i = 0; i < length; i++)
	{
		h.data[i] = arr[i];
	}
	h.size = length;
	buildheap(&h, arr, length);
	for(i = 0; i < length; i++)
	{
		arr[i] = extractmin(&h);
	}
}

int main()
{
	heap h;
	int i, j, len;
	int a[MAXLEN];
	j = 0;
	printf("Enter a list of at most %d numbers, terminated by 0.\n", MAXLEN);
	scanf("%d",&i);
	while(i != 0)
	{
		a[j] = i;
		j++;
		scanf("%d",&i);
	}

	printf("\nThe unsorted array:\n");
	for(i = 0; i < j; i++)
	{
		printf("%d ", a[i]);
	}
	len = j;

	printf("\nBuilding Heap...\n");
	buildheap(&h, a, len);
	printheap(&h);
	printf("\nEnter numbers. Positive numbers are inserted into the heap. 0 extracts the min element from the heap. Any negative number terminates this stage.\n");
	scanf("%d",&i);
	while(i >= 0)
	{
		if(i > 0)
		{
			if(isfull(&h))
			{
				printf("Heap is full.\n");
			}
			else
			{
				printf("Inserting %d ...\n", i);
				insert(&h, i);
				printheap(&h);
			}
		}
		else
		{
			j = extractmin(&h);
			if(j == -1)
			{
				printf("Heap is empty.\n");
			}
			else
			{
				printf("-> %d\n", j);
				printheap(&h);
			}
		}
		scanf("%d",&i);
	}

	printf("\nChanging values inside the heap\nEnter a negative number to terminate.\n");
	do
	{
		printf("\nIndex to change value at: ");
		scanf("%d", &i);
		if(i >= 0)
		{
			j = valueat(&h, i);
			if(j != -1)
			{
				printf("Current value at position %d: %d\n", i, j);
				printf("Enter new value: ");
				scanf("%d",&j);
				changevalue(&h, i, j);
				printheap(&h);
			}
			else
			{
				printf("\nNo such position.\n");
			}
		}
	}
	while(i >= 0);

	printf("\nEmptying heap completely using extractmin ...\n");
	while(!isempty(&h))
	{
		printf(" %d, ",extractmin(&h));
		// printheap(&h);
	}

	printf("\n\nInitial array sorted using heapsort:\n");
	heap_sort(a, len);
	for(i = 0; i < len; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
}
