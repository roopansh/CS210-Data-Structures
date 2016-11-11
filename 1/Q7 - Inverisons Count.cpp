/************************
ROOPANSH BANSAL
150101053
CS210
************************/
/***********************
The Function sorts the array using merge sort and calculates the inversion simultaneously.
Running time of the following pragram is O(nLogn)

Main Property used:
During merging of the left and right arrays(SORTED).
If right[b] > left[a] implies that all the elements left in the left subarray to merge are less than the right[b]
and hence all of them contribute to the inversion count. 
***********************/
#include <iostream>

using namespace std;

//Function Prototypes
int MergeInvCount(int *arr , int left , int right);
int MergeSplitInv(int *arr , int left , int mid , int right);


int main()
{
	int n;
	cout<<"\n Enter the number of elements:\t";
	cin>>n;

	int arr[n];
	cout<<"Enter the elements in the array:\n";
	for(int i=0;i<n;i++)
	{
		cin>>arr[i];
	}

	// During Merge Sort , we would count the number of the inversions.
	int No_of_inversions = MergeInvCount( arr , 0 , n-1 );
	cout<<"The number of inversions are : "<<No_of_inversions<<endl;
	return 0;
}


int MergeInvCount(int *arr , int left , int right)
{
	// if left >= right , the number of elements in the array is at most 1 and hence the number of inversions is zero. 
	if(left < right)
	{
		// the number of the inversions are inversions in left sub array + inversions in the right sub array + the Split-Inversions
		int mid = (left + right)/2;
		int Left_inv = MergeInvCount(arr ,left , mid);
		int right_inv = MergeInvCount(arr, mid+1 , right);  
		int Split_inv = MergeSplitInv(arr , left , mid , right);
		return Left_inv + right_inv + Split_inv;
	}
	else
	{
		return 0;
	}
}


//	The arrays are sorted also because when we call the function recursively
//	in such a manner , we assume that the left and right sub arrays are sorted.
int MergeSplitInv(int *arr , int left , int mid , int right)
{
	// Initialise the number of the inversions of the array to 0
	int ans = 0;

	//n1 = the number of elements in the left subarray
	int n1 = mid - left + 1;

	//n2 = the number of the elements in the right subarray
	int n2 = right - mid;

	//Left and right subarrays
	int Left_SubArr[n1];
	int Right_SubArr[n2];

	//copy the original arr into the Left and the right subarrays
	for(int i=0;i<n1;i++)
	{
		Left_SubArr[i] = arr[left+i];
	}
	for(int i=0;i<n2;i++)
	{
		Right_SubArr[i] = arr[mid+1+i];
	}

	//Setting pointers to the left sub array(i) , right sub array(j) and the final answer array(k)
	//The final sorted array will be stored in the 'arr' array
	int i = 0, j = 0 , k = left ;

	//compare the two elements in the subarrays.
	//insert the smallest of those two in the new arr
	while( i<n1 && j<n2 )
	{
		if(Left_SubArr[i] <= Right_SubArr[j])
		{
			arr[k++] = Left_SubArr[i++];
		}
		else//	Left_SubArr[i] > Right_SubArray[j] which means that their is inversions
		{
			//all the elements left in the left subarray are the inversion for the j element in the right subarray
			ans += n1 - i; 
			arr[k++] = Right_SubArr[j++];
		}
	}
	//to insert the rest of the elements left to be inserted when the other subarray is exhausted
	while(i<n1)
		arr[k++] = Left_SubArr[i++];
	while(j<n2)
		arr[k++] = Right_SubArr[j++];

	return ans;
}
