/************************
ROOPANSH BANSAL
150101053
CS210
************************/

/************************
Normal implementation of the insertion sort.
************************/
#include <stdio.h>

//Function Prototypes
void InsertionSort(int arr[], int n);


//Main Function
int main()
{
	//n is the number of the elements
	int n ;
	printf("Enter the number of elements:\t");
	scanf("%i" , &n);
	
	//declaring the array of size n
	int arr[n];

	//taking the numbers as inputs
	printf("Enter the elements:\n");

	int i;
	for( i=0 ; i<n ; i++)
	{
		scanf("%d" , &arr[i]);
	}
	
	InsertionSort(arr , n);
	
	for(i=0;i<n;i++)
	{
		printf("%i\t" , arr[i]);
	}
	
	printf("\n");

	return 0;
}

//Normal insertion sort function
void InsertionSort(int arr[], int n)
{
	for(int i=1;i<n;i++)
	{
		//Storing the arr[i] in a temp variable
		int temp = arr[i];

		// Finding the right postition for the arr[i] to be inserted
		int j = i-1;
		while( j>=0 && arr[j] >temp)
		{
			arr[j+1] = arr[j];
			j--;
		}

		//inserting arr[i] in the right position
		arr[j+1] = temp;
	}
}
