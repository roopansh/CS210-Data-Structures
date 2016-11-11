#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Function prototype

void InsertionSort(int arr[], int n ); // Arguments are Array , size of array
void InsertionSort2(int arr[], int n );	// arguments are array and size of the array
//BinarySearch returns the index(between left and right) of leftmost element greater than the key. 
int BinarySearch(int *arr , int left ,int right , int key ); //arguments are array , left index of the array, right index of the array , and the key to search for for


//Define the number of the test cases to run
int testCases = 100;

//Declaring the variable for storing the number of COMPARISONS
//Global because the number of COMPARISONS are added when the function is called
int NormalInsertion;
int BinaryInsertion;

int main()
{
	srand(time(0)); //seed the random function
	
	int n; //the number of elements of the array
	printf("Enter the number of elements:\t");
	printf("\n\n<<NOTE:: THE NUMBER OF ELEMENTS IN THE ARRAY REMAINS SAME FOR DIFFERENT CASES>>\n\n");
	scanf("%i" , &n); //input n
	
	int arr[n]; //Declaring intial array where rand function will store the elements
	
	int A[n],B[n]; //Declaring two different arrays. Different sorting will be run on these different arrays

	//Heading of the table for the Comparisons Tables
	printf("\n\n\t\t\tTHE NUMBER OF COMPARISONS IN\n \n");
	printf("S.No.\t\tNORMAL INSERTION\t---\tINSERTION USING BINARY SEARCH\n");	


	//Running the loop for the number of test cases to run
	// To take different cases for comparison between the two sorts
	for(int i=0;i<testCases;i++) 
	{
		//generating random elements
		for(int i=0;i<n;i++)
		{
			arr[i] = rand();
		}

		//Copying thios array into two arrays on which DIFFERENT SORTS would be run.
		for(int i=0;i<n;i++)
		{
			A[i] = arr[i];
			B[i] = arr[i];
		}


		//Declaring the number of COMPARISONS to zero initially
		NormalInsertion=0;
		BinaryInsertion=0;

		//Running Normal Insertion Sort on  ARRAY A
		InsertionSort(A , n );

		//Running Insertion Sort with Binary Search on  ARRAY B
		InsertionSort2(B , n );

		//printing the comparisons in tabular form
		printf("Test Case No. - %i\t\t%i\t-------------------\t%i\n" ,i+1, NormalInsertion, BinaryInsertion );
	}
}

//
//	Function Declarations FOLLOWS
//


// Normal Insertion Sort
void InsertionSort(int arr[], int n )
{
	for(int i=1;i<n;i++)
	{
		int temp = arr[i];
		int j = i-1;
		NormalInsertion++;//Adding one for the Comparison
		while( j>=0 && arr[j] >temp)
		{
			NormalInsertion++; //ADDING one for the COMPARISON 
			arr[j+1] = arr[j];
			j--;
		}
		arr[j+1] = temp;
	}
}



//Insertion Sort using binary search
void InsertionSort2(int arr[], int n)
{
	//
	//		NOTE: The number of comparisons are calculated only in the binary search
	//
	for(int i=1;i<n;i++)
	{
		int temp = arr[i];

		int position = BinarySearch(arr , 0 , i-1 , temp );//Binary search to return the index
	
		int j = i;

		// Shifting the elements one step to the right
		while (j>position)
		{
			arr[j] = arr[j-1];
			j--;
		}
	
		arr[position] = temp;
	}
}


// Binary Search to find the actual place of the key in the array between left and right
int BinarySearch(int *arr , int left ,int right , int key)
{
	//Initialising the mid of the array.
	int mid = (left+right)/2;

	//If there is only one element in the array , just compare it with the key
	if(left == right)
	{
		if(arr[left]>key)
			return left;
		else
			return left+1;
	}

	//for more than one Elements in the array
	while(left < right )
	{
		//updating the mid element
		mid = (left+right)/2;
		if(arr[mid] == key)
		{
			BinaryInsertion++;//Adding one for the Comparison
			return mid;
		}
		else if ( arr[mid] > key)
		{
			BinaryInsertion++;//Adding one for the Comparison
			right = mid-1;
		}
		else
		{
			BinaryInsertion++;//Adding one for the Comparison
			left = mid+1;
		}
		if(left > right)
			return left;
		if(left == right)
		{
			if(arr[left] > key)
				return left;
			else
				return left+1;
		}
	}
	return left;
}
