/************************
ROOPANSH BANSAL
150101053
CS210
************************/

/************************
Normal merge sort implementation
************************/

#include <iostream>

using namespace std;

//Funtion Prototypes
void MergeSort(int *arr , int left , int right);
void Merge(int *arr , int left , int mid , int right );

int main()
{
	cout<<"Enter the number of elements in the array:\t";
	// n=the number of elements in the array
	int n;
	cin>>n;

	int arr[n];
	
	// take the array as input from the user
	cout<<"Enter the elements : \n";
	for(int i=0;i<n;i++)
	{
		cin>>arr[i];
	}

	//Calling the Merge Sort function
	MergeSort(arr , 0 , n-1 );

	//printing the sorted array
	for(int i=0;i<n;i++)
	{
		cout<<arr[i]<<"\t";
	}
	cout<<endl;
	return 0;
}

void MergeSort(int *arr , int left , int right)
{
	//if left == right the array contains only one element that is by default sorted( the exit condition for the recursion)
	if(left < right )
	{
		//mid divides the array into two sub arrays
		int mid= (left+right)/2;

		//function recursion
		MergeSort(arr , left , mid);
		MergeSort(arr , mid+1 , right);

		//finally merging the sub array into one array
		Merge(arr , left , mid , right );
	}
}

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
