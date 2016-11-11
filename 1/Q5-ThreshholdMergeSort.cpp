/************************
ROOPANSH BANSAL
150101053
CS210
************************/

/***********************************************

THE PROGRAMS FIRSTS INITIALISES AN ARRAY OF SIZE ArraySize(which increases from 1000 to n in steps of 50) USING RANDOM NUMBER GENERATOR.
THEN THE RUNNING TIMES OF MERGESORT (USING DIFFERENT THRESHHOLD VALUES) IS ADDED TO THE ARRAY MAINTAINED ( MergeThresh_Time[] ).
THE  " MergeThresh_Time[i] " is the sum of the running times of array of different size (1000 to 5000) for the threshhold value = i . 
THEN EACH ELEMENT OF THAT ARRAY IS DIVIDED BY TOTAL NUMBER OF CASES (PRECISELY 81)
THE AVERAGE RUNNING TIMES ARE PRINTED ON SCREEN AND THE LEAST RUNNING TIME IS THE ANSWER.

NOTE :::: IT IS OBSERVED THAT THE OPTIMUM THRESHHOLD VALUE IS AROUND 10-15.

***********************************************/


#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <limits.h>

using namespace std;

//Function Prototypes
void MergeSortThreshHold(int *arr , int left , int right , int MTH);//integer cargument MTH is the merge threshhold value
void Merge(int *arr , int left , int mid , int right );
void InsertionSort2(int *arr, int left , int right);
int BinarySearch(int *arr , int left ,int right , int key);
void PrintArr(int *arr ,int left , int right);

// Main Function
int main()
{
	//Maximum number of the elements in the array
	int n = 5000;

	// for calculating the time taken by different algorithms
	clock_t a ,b ;

	//MTH is the merge threshhold.
	// We'll calculate the running time for all values of threshhold from 1 to 100
	//According to the data provided , merge sort performs better than binary insert sort for input values of 55. So we'll check in that range only.
	int maximum_threshold = 60;

	// Variables to store the running times of the algorithms
	double MergeThresh_Time[maximum_threshold+1]  = {00.0};

	// for storing the value of the ans threshhold time and the threshold value
	int ANS_Threshhold ;
	double ANS_Threshhold_Time = 1000000.0;


	// WARNING MESSAGE PRINTED ON SCREEN FOR LOW SPECS COMPUTERS
	cout<<"\n\tPLEASE DON'T TERMINATE THE PROGRAM. IT IS RUNNING. IT MIGHT TAKE UPTO A FEW MINUTES ON SLOW PC'S\n\n";
	for(int ArraySize = 1000;ArraySize<n;ArraySize+=50)
	{
		//Seed the random number generator function
		srand(time(0));

		//Array declaration
		// This random array generated once remains same. Hence all the sorting for different threshhold values run on the same input array.
		int arr[ArraySize];

		for(int i=0;i<ArraySize;i++)
		{
			arr[i] = rand();
		}

		for(int MTH=1;MTH<=maximum_threshold;MTH++)	
		{
			//The array used where we'll copy the random array generated above before running any sorting algo on it.
			int UnSortedArr[ArraySize];

			//Initialise the Unsroted Array
			for(int x=0;x<ArraySize;x++)
			{
				UnSortedArr[x] = arr[x];
			}
	
			//Merge Sort using the threshhold value
			a = clock();
			MergeSortThreshHold(UnSortedArr , 0 , ArraySize-1 , MTH);
			b = clock();
			MergeThresh_Time[MTH] += (b-a)*1000000/CLOCKS_PER_SEC;
	
			//cout<<"For ThreshHold =\t"<<MTH<<"\tMerge Sort Takes Time=\t"<<MergeThresh_Time<<"MicroSeconds"<<endl;
		}
	}

	//The MergeThresh_Time[i] stores the total time taken to sort random arrays of size 1000,1050,1100,....4900,4950,5000 using threshhold value = i
	//hence the following loop converts it into the average time
	for(int i=1 ; i<maximum_threshold+1;i++)
	{
		MergeThresh_Time[i] /= 80;//Total of 80 cases are run
		cout<<"MERGE SORT TIME(AVERAGE) FOR THRESHOLD VALUE   ====   "<<i<<"   is   ====   "<<MergeThresh_Time[i]<<"MicroSeconds"<<endl<<endl;
		if(MergeThresh_Time[i] < ANS_Threshhold_Time)
		{
			ANS_Threshhold_Time = MergeThresh_Time[i];
			ANS_Threshhold = i;
		}
	}
	cout<<endl<<"<---\tTHE OPTIMUM THRESHOLD VALUE\t--->"<<endl<<"MERGE SORT TIME(AVERAGE) FOR THRESHOLD VALUE\t====\t"<<ANS_Threshhold<<"\tis\t====\t"<<ANS_Threshhold_Time<<"MicroSeconds"<<endl<<endl;
	return 0;
}

//Function Declaration of different functions

//Merge Sort with the threshold condition
void MergeSortThreshHold(int *arr , int left , int right , int MTH)//MTH is the merge threshhold value
{
	if(right - left + 1 < MTH) // Number of elements in the sub array is less than the Merge Threshhold
	{
		//sort using Binary Search Insertion
		//Question 2 of the assignment
		InsertionSort2(arr ,left , right );

	}
	else // Number of elements in the sub array are greater than the Merge Threshhold
	{
		//Normal merge Sort procedure
		//Question 4 of the assignment
		if(left < right )
		{
		//mid divides the array into two sub arrays
		int mid= (left+right)/2;

		//function recursion
		MergeSortThreshHold(arr , left , mid , MTH);
		MergeSortThreshHold(arr , mid+1 , right ,MTH);

		//finally merging the sub array into one array
		Merge(arr , left , mid , right );
		}
	}
}

// Funciton to merge two sorted sub-arrays
void Merge(int *arr , int left , int mid , int right )
{
	//n1 = the number of elements in the left subarray
	int n1 = mid - left + 1;

	//n2 = the number of the elements in the right subarray
	int n2 = right - mid;

	//CopyArr is declared to keep the subarrays
	int CopyArr[n1+n2];

	//copy the original arr into the CopyArr
	for(int i=0;i<n1+n2;i++)
	{
		CopyArr[i] = arr[left+i];
	}

	//Setting pointers to the left sub array(i) , right sub array(j) and the final answer array(k)
	//the sub arrays are stored together in the 'CopyArr'
	//The final sorted array will be stored in the 'arr' array
	int i = 0, j = n1 , k = left ;

	//compare the two elements in the subarrays.
	//insert the smallest of those two in the new arr
	while(i<n1 && j < n1+n2 )
	{
		if(CopyArr[i] <= CopyArr[j])
		{
			arr[k++] = CopyArr[i++];
		}
		else
		{
			arr[k++] = CopyArr[j++];
		}
	}
	//to insert the rest of the elements left to be inserted when the other subarray is exhausted
	while(i<n1)
		arr[k++] = CopyArr[i++];
	while(j<n1+n2)
		arr[k++] = CopyArr[j++];
}

// Insertion sort using Binary search
void InsertionSort2(int *arr, int left , int right)
{
	for(int i=left+1;i<=right;i++)
	{
		int temp = arr[i];
		int j = BinarySearch(arr , left , i-1 , temp);
		int k = i;
		while (k>j)
		{
			arr[k] = arr[k-1];
			k--;
		}
		arr[j] = temp;
	}
}

// Binary Search function for finding the right position of the key in insertion sort
int BinarySearch(int *arr , int left ,int right , int key)
{
	int mid = (left+right)/2;
	if(left == right)
	{
		if(arr[left]>key)
			return left;
		else
			return left+1;
	}
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
// Function to print the array to the screen
void PrintArr(int *arr ,int left , int right)
{
	cout<<"The Random Array Generated is : \n"<<endl;
	for(int i=left;i<=right;i++)
	{
		cout<<arr[i]<<"\t";
	}
	cout<<endl;
}
