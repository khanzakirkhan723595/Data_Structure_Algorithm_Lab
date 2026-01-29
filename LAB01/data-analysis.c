/*
	Course:		CS2130 DSA Lab 
	Semester:	2026 Jan-Apr
	Lab No:		1
	Aim: 		Simple data analysis on a list of integers in the range 1-100. 
	Instructions:
		1.	Read a list of numbers from the terminal and store it in an array.
		2.	You can also read the list by redirecting a file data.txt to the input 
		3.	Complete a set of data analytic tasks on these numbers. Search
			for "Task".
*/

#include <stdio.h>
#include <math.h>
#include<limits.h>
#define N 100		// The maximum amount of data the program will handle

void printarray(const int a[], int len)
{
	/*Prints the elements of the array a.*/

	int i;
	for(i = 0; i < len; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
}

void sort(const int src[], int lensrc, int dest[])
{
	/*Copies the elements of the array src to the array dest and then
	sorts the elements of dest in non-decreasing order. It is assumed that
	enough memory has already been allocated for the array dest.*/

	int i, j;
	for(i = 0; i < lensrc; i++)
	{
		dest[i] = src[i];
	}
	for(i = 0; i < lensrc - 1; i++)
	{
		int temp;
		temp = dest[i+1];
		for(j = i; j >= 0 && dest[j] > temp; j--)
		{
			dest[j+1] = dest[j];
		}
		dest[j+1] = temp;
	}
}
void swap(int *a,int *b)
{
	int temp=*a;
	*a=*b;
	*b=temp;
}

void reversearray(int a[], int len)//Task 1
{
	/*Reverses the order of the elements in the array a.*/
	int l=0;
	int r=len-1;
	while(r>l)
	{
		swap(&a[l],&a[r]);
		l++;
		r--;
	}


}

float average(const int a[], int len)//Task 2
{
	/*Returns the average of the elements in the array a.*/
	float sum=0;
	for(int i=0;i<len;i++)
	{
		sum+=a[i];
	}
	float avg=sum/len;

	return avg;
}

float sd(const int a[], int len)//Task 3
{
	/*Returns the standard deviation of the elements in the array a.*/
	float mean=average(a,len);
	float xsqr=0;
	for(int i=0;i<len;i++)
	{
		xsqr+=(a[i]-mean)*(a[i]-mean);
	};
	float sd=sqrt(xsqr/len);

	return sd;
}

int min(const int a[], int len)//Task 4
{
	/*Returns a position in the array a containing the minimum value in a.*/
	int mini=INT_MAX;
	int idx=0;
	for(int i=0;i<len;i++)
	{
		if(a[i]<mini)
		{
			mini=a[i];
			idx=i;
		}
	}

	return idx;
}

int max(const int a[], int len)//Task 5
{
	/*Returns a position in the array a containing the maximum value in a.*/
	int maxi=INT_MIN;
	int idx=0;
	for(int i=0;i<len;i++)
	{
		if(a[i]>maxi)
		{
			maxi=a[i];
			idx=i;
		}
	}

	return idx;

	
}

int mode(const int a[], int len)//Task 6
{
	/*Returns the value that appears the maximum number of times in a.*/
	int sorted[len];
	sort(a,len,sorted);
	int count=1;
	int maxicnt=0;
	int idx=0;
	int ele=sorted[0];
	for(int i=1;i<len;i++)
	{
		if(sorted[i]==ele)
		{
			count++;
		}
		else{
			if(count>maxicnt)
			{
				maxicnt=count;
				idx=i-1;
			}
			ele=sorted[i];
			count=1;
		}
	}


	return sorted[idx];
}

void printhistogram(const int a[], int len)//Task 7
{
/* Generates a histogram of the data in the following form
		01 - 10 : ####
		11 - 20 : ########
		...
		91 - 100 : ##
		
		Here the number of #'s after i-j denote the number of numbers in the
		list which are between i and j (i and j included).
	*/
	int count[11]={0};
	//int ec=0;
	for(int i=0;i<len;i++)
	{
		if(a[i]<=10 && a[i]>=1)
		{
			count[1]++;
		}
		if(a[i]<=20 && a[i]>=11)
		{
			count[2]++;
		}
		if(a[i]<=30 && a[i]>=21)
		{
			count[3]++;
		}
		if(a[i]<=40 && a[i]>=31)
		{
			count[4]++;
		}
		if(a[i]<=50 && a[i]>=41)
		{
			count[5]++;
		}
		if(a[i]<=60 && a[i]>=51)
		{
			count[6]++;
		}
		if(a[i]<=70 && a[i]>=61)
		{
			count[7]++;
		}
		if(a[i]<=80 && a[i]>=71)
		{
			count[8]++;
		}
		if(a[i]<=90 && a[i]>=81)
		{
			count[9]++;
		}
		if(a[i]<=100 && a[i]>=91)
		{
			count[10]++;
		}
		
	}
	for(int i=1;i<=10;i++)
	{
		printf("%d - %d : ",((i)*10-9),(i)*10);
		int n=count[i];
		while(n--)
		{
			printf("#");
		}
		printf("\n");
	}

	

}

int linearsearch(const int a[], int len, int key)//Task 8
{
	/*Returns a position of the array a that contains the value key. Returns -1
	if key is not present in the array.*/
	
	int ele=-1;
	for(int i=0;i<len;i++)
	{
		if(a[i]==key)
		{
			ele=i;
			break;
		}
	}

	return ele;
}

int binarysearch(const int a[], int len, int key)//Task 9
{
	/*Assuming that the array a is sorted in non-decreasing order,
	returns a position of the array containing the value key by performing a
	binary search. Returns -1 if value key is not present in the array a.*/
	int l=0;
	int r=len-1;
	while(r>=l)
	{
		int mid= (l+r)/2;
		if(a[mid]==key)
			return mid;
		else if(a[mid]>key)
		{
			r=mid-1;
		}
		else{
			l=mid+1;
		}
	}

	return -1;
}

int removedup(const int src[], int lensrc, int dest[])//Task 10
{
	/*Copies the values in the array src to the array dest so that
	every value in src appears exactly once in dest, i.e. dest contains 
	all the values in src, but without any repetition. The order of the
	elements in the array dest can be arbitrary. The function returns
	the number of values copied to the array dest. It is assumed that
	enough memory has already been allocated for the array dest.*/
	int sorted[lensrc];
	sort(src,lensrc,sorted);
	int j=0;
	int unq=1;
	for(int i=1;i<lensrc;i++)
	{
		if(sorted[i-1]==sorted[i])
		{
			continue;
		}
		else{
			dest[j++]=sorted[i-1];
			unq++;
		}
	}

	return unq;
}

int main()
{
	int a[N], b[N];
	int i, len, temp, z;

	// To read the input array
	for(i = 0; i < N; i++)
	{
		scanf("%d", &temp);
		if(temp == 0)
		{
			len = i;
			break;
		}
		else
		{
			a[i] = temp;
		}
	}

	// Testing Code (Do not change)
	printf("The array:\n");
	printarray(a,len);

	printf("\nThe array in reverse order:\n");
	reversearray(a,len);
	printarray(a,len);
	reversearray(a,len);/*Restores array to original form*/

	printf("\nAverage: %f\nStandard Deviation: %f\nMinimum value: %d\nMaximum value: %d",
		average(a,len),sd(a,len),a[min(a,len)],a[max(a,len)]);

	printf("\nThe value %d is a mode of the array.",mode(a,len));

	printf("\n\nHistogram\n---------\n");
	printhistogram(a,len);

	printf("\n\nEnter a value to search for: ");
	scanf("%d",&z);
	temp = linearsearch(a,len,z);
	if(temp == -1)
	{
		printf("Value %d not present in array.\n", z);
	}
	else
	{
		printf("Value %d found at position %d.\n", z, temp);
	}

	printf("\n\nEnter a value to search for: ");
	scanf("%d",&z);
	temp = linearsearch(a,len,z);
	if(temp == -1)
	{
		printf("Value %d not present in array.\n", z);
	}
	else
	{
		printf("Value %d found at position %d.\n",z, temp);
	}

	sort(a,len,b);
	printf("\nThe array in sorted order:\n");
	printarray(b,len);

	printf("\nEnter value to search in sorted array: ");
	scanf("%d",&z);
	temp = binarysearch(b,len,z);
	if(temp == -1)
	{
		printf("Value %d not present in array.\n", z);
	}
	else
	{
		printf("Value %d found at position %d in sorted array.\n", z, temp);
	}

	printf("\nEnter value to search in sorted array: ");
	scanf("%d",&z);
	temp = binarysearch(b,len,z);
	if(temp == -1)
	{
		printf("Value %d not present in array.\n", z);
	}
	else
	{
		printf("Value %d found at position %d in sorted array.\n", z, temp);
	}

	printf("\nThe elements of the array without repetition:\n");
	temp = removedup(a,len,b);
	printarray(b,temp);

	return 0;
}

