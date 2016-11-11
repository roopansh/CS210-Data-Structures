/************************
ROOPANSH BANSAL
150101053
CS210
************************/

/************************
Implementing the insertion sort using binary search for finding the right position of the element to be inserted
************************/
#include <stdio.h>

//Function prototypes 
void InsertionSort(int arr[], int n);
int BinarySearch(int *arr, int left,int right , int key);//BinarySearch returns the index(between left and right) of leftmost element greater than the key. 

//Main Function 
int main()
{
	//n is the number of elements in the array
	int n  ,i;
	printf("Enter the number of elements:\t");
	scanf("%i" , &n);

	//Declaring the array of size n
	int arr[n];

	//Inputing the n elements from user
	printf("Enter the elements:\n");
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

//insertion sort using binary search
void InsertionSort(int arr[], int n)
{
	for(int i=1;i<n;i++)
	{
		//Storing value of arr[i] in the temp variable
		int temp = arr[i];

		//Binary search returns the correct position to insert the temp
		int j = BinarySearch(arr , 0 , i-1 , temp);

		//Shifting the numbers to the right of j by one unit to the right
		int k = i;
		while (k>j)
		{
			arr[k] = arr[k-1];
			k--;
		}

		// Inserting the key value(i.e. stored temp variable) in the rightful poition
		arr[j] = temp;
	}
}

//Binary search returns the index where the key should be inserted
int BinarySearch(int *arr , int left ,int right , int key)
{
	//note that the array from left to right is sorted already


	int mid = (left+right)/2;
	
	//If there is only one element , then either the value to be inserted is at that position or to the position to right of that 
	if(left == right)
	{
		if(arr[left]>key)
			return left;
		else
			return left+1;
	}

	// If the number of elements are greater than 1
	// we'll have to use the normal binary search procedure
	while(left < right )
	{
		mid = (left+right)/2;
		if(arr[mid] == key)
		{
			return mid;
		}
		else if ( arr[mid] > key)
		{
			right = mid-1;
		}
		else
		{
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