#include <stdio.h>

int arr[100];
int len;
int count;

void printarray()
{
	/* Prints the current contents of the global array arr */

    int i;
    for(i = 0; i < len; i++)
    {
        printf("%d ", arr[i]);
    }
	printf("\n");
    count++;
}

void swap(int *a,int *b)
{
    int temp=*a;
    *a=*b;
    *b=temp;
}

void allperm(int arr[],int idx,int len)
{
    if(idx==len)
    {
        count++;
        for(int i=0;i<len;i++)
        {
            printf("%d ",arr[i]);
        }
        printf("\n");
        return;

    }
    for(int i=idx;i<len;i++)
    {
        swap(&arr[idx],&arr[i]);
        allperm(arr,idx+1,len);
        swap(&arr[idx],&arr[i]);

    }
}

void printallperm(int p, int q)
{
	/* Task 3: Print all arrays that can obtained from the array arr by
	 * permuting the values in arr[p] .. arr[q-1] in all possible ways.
	 * Note that arr is a global array of length len. You can assume that
	 * the array contains all distinct values */
    allperm(arr,p,q-p);

}

int main()
{
    int i;
    printf("Enter number of elements: ");
    scanf("%d", &len);
    count = 0;
    for(i = 0; i < len; i++)
    {
        arr[i] = i;
    }
    printf("\n");
    printallperm(0, len);
    printf("\n");
    printf("Total number of permutations generated: %d\n", count);
}
