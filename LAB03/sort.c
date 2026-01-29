#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define L 75

int *temparr; // Temporary array used by the merge function.

void merge(int a[], int p, int q, int r)
{
	/* Task 1. Write a function which, when p < q < r and both the subarrays
	 [p]..a[q-1] and a[q]..a[r-1] of the array a are sorted
	in non-descending order, modifies the array a so that the subarray
	a[p]..a[r-1] is sorted in non-descending order.*/
	
	int n1=q-p;
	int n2=r-q;
	int Larr[n1];
	int Rarr[n2];
	for(int i=0;i<n1;i++)
	{
		Larr[i]=a[p+i];
	}
	
	for(int j=0;j<n2;j++)
	{
		Rarr[j]=a[q+j];
	}
	

	int i=0;
	int j=0;
	int k=p;
	while(i<n1 && j<n2)
	{
		if(Larr[i]<Rarr[j])
		{
			a[k++]=Larr[i++];
		}
		else{
			a[k++]=Rarr[j++];
		}
	}
	while(i<n1)
	{
		a[k++]=Larr[i++];
	}
	while(j<n2)
	{
		a[k++]=Rarr[j++];
	}

	
	

	

	



}

void merge_sort(int a[], int p, int q)
{
	/* Task 2. Write a function which sorts the subarray a[p]..a[q-1] of the array a in
	non-descending order using merge sort.*/
	if(p+1>=q)
	{
		return;
	}
	int mid=(p+q)/2;
	merge_sort(a,p,mid);
	merge_sort(a,mid,q);
	merge(a,p,mid,q);

}

void swap(int *a,int *b)
{
	int temp=*a;
	*a=*b;
	*b=temp;
}

void insertion_sort(int a[], int p, int q)
{
	/* Task 3. Write a function which sorts the subarray a[p]..a[q-1] of a in non-descending order
	using insertion sort.*/
	int n=q-p;
	for(int i=1;i<n;i++)
	{
		int j=i-1;
		int key=a[i];
		while(j>=0 && key<a[j])
		{
			swap(&a[j+1],&a[j]);
			j--;
		}
		a[j+1]=key;


	}


}

void ins_merge_sort(int a[], int p, int q)
{
	/* Task 4. Write a modified merge sort function which uses insertion sort to sort subarrays
	which are smaller than length L. Experiment with various values for L. */
	if(q-p<=L)
	{
		insertion_sort(a,p,q);
	}
	if(p+1>=q)
	{
		return;
	}
	int mid=(p+q)/2;
	merge_sort(a,p,mid);
	merge_sort(a,mid,q);
	merge(a,p,mid,q);

}

void k_way_merge(int src[], int indx[], int k)
{
	/* Task 5. Merge k sorted arrays: Here, indx is an array of length k
	containing k-1 indices into the array src and the length of the array src
	(as indx[k-1]). Write a function which, given that each of the subarrays
		src[0]..src[indx[0]-1], 
		src[indx[0]]..src[indx[1]-1],
		src[indx[1]]..src[indx[2]-1], ..., 
		src[indx[k-2]]..src[indx[k-1]-1]
	are sorted, merges all of them so that the array src becomes sorted. The
	function has to run in time O(n log k), where n is the length of the array
	src. */

	int p=indx[0];
	int q=indx[1]-1;
	int r;
	for(int i=1;i<k;i++)
	{
		r=indx[i+1]-1;

		merge(src,p,q,r);
		q=r;

	}
	
}

int main()
{
	int *a, *x, *indx, len, numblocks, i, j, prev;
	clock_t begin, end;
	clock_t mergetime, instime, insmergtime;

	printf("Enter length of array: ");
	scanf("%d", &len);

	a = (int *) malloc(sizeof(int)*len);
	x = (int *) malloc(sizeof(int)*len);	
	temparr = (int *) malloc(sizeof(int)*len);	

	if(a == NULL || x == NULL || temparr == NULL)
	{
		printf("Memory allocation error.\n");
		return 1;
	}

	srand(time(NULL)); // Initializing random number generator 

	for (i = 0; i < len; i++) // Populates the array a with random values in the range 0 .. 4*len-1
	{
		a[i] = rand() % (4 * len);
	}

	for (i = 0; i < len; i++) // Copies the array a to x
	{
		x[i] = a[i];
	}

	printf("\nThe unsorted array:\n");
	for(i = 0; i < len; i++)
	{
		printf("%d ", x[i]);
	}
	printf("\n");

	begin = clock(); // Store clock value just before merge_sort() is called
	merge_sort(x, 0, len);
	end = clock(); // Store clock value just after the call to merge_sort() returns
	mergetime = end - begin; // Find time elapsed during execution of merge_sort()

	printf("\nArray sorted using Merge Sort:\n");
	for(i = 0; i < len; i++)
	{
		printf("%d ", x[i]);
	}
	printf("\n");

	for (i = 0; i < len; i++)
	{
		x[i] = a[i];
	}

	begin = clock();
	insertion_sort(x, 0, len);
	end = clock();
	instime = end - begin; // Find time elapsed during execution of insertion_sort()

	printf("\nArray sorted using Insertion Sort:\n");
	for(i = 0; i < len; i++)
	{
		printf("%d ", x[i]);
	}
	printf("\n");

	for (i = 0; i < len; i++)
	{
		x[i] = a[i];
	}

	begin = clock();
	ins_merge_sort(x, 0, len);
	end = clock();
	insmergtime = end - begin;

	printf("\nArray sorted using Insertion-Merge Sort:\n");
	for(i = 0; i < len; i++)
	{
		printf("%d ", x[i]);
	}
	printf("\n");


	printf("\n           %20s|%20s|%20s\n-----------------------------------------------------------------------\n","     Merge Sort     ","   Insertion Sort   ","   Ins-Merge Sort   ");
	printf("Clock ticks%12lu        |%12lu        |%12lu\n\n",mergetime, instime, insmergtime);

	printf("\nEnter number of blocks k: ");
	scanf("%d", &numblocks);
	srand(time(NULL));

	indx = (int *) malloc(sizeof(int) * numblocks + 2);
	for(i = 0; i < numblocks - 1; i++)
	{
		indx[i] = rand() % len;
	}
	indx[numblocks - 1] = len;
	insertion_sort(indx, 0, numblocks);

	prev = 0;
	for(i = 0; i < numblocks; i++)
	{
		insertion_sort(a, prev, indx[i]);
		prev = indx[i];
	}

	printf("\nBlock-wise sorted array:\n");

	j = 0;
	for(i = 0; i < len; i++)
	{
		while(i == indx[j])
		{
			printf("| ");
			j++;
		}
		printf("%d ", a[i]);
	}
	printf("\n");

	k_way_merge(a, indx, numblocks);

	printf("\nArray after k-way merge:\n");
	for(i = 0; i < len; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");

}
