/************************
ROOPANSH BANSAL
150101053
CS210
************************/
/**************************
//		SORTING 		============================	O( n Logn )
//		Finding the elements in sorted array 	====	O( n )
//
//		Total Running Time 		====================	O( n Logn )
//
**************************/

#include <iostream>

using namespace std;

//Function Prototypes
void Merge(int *arr , int left , int mid , int right );
void MergeSort(int *arr , int left , int right);

int main()
{
	int n , m;
	cout<<"\nEnter the number of elements in the array: \t";
	cin>>n;
	int A[n] , B[n] ;
	cout<<"Enter m (The sum of two elements):\t";
	cin>>m;
	cout<<"Enter ARRAY 1 \t:\n";
	for (int i=0;i<n;i++)
	{
		cin>>A[i];
	}
	cout<<endl;
	cout<<"Enter ARRAY 2 \t:\n";
	for (int i=0;i<n;i++)
	{
		cin>>B[i];
	}

	//Sort the two arrays
	//SORTING IS DONE IN :- 
	// 
	//	O(nlgn)
	// 
	MergeSort(A , 0 , n-1);
	MergeSort(B, 0 , n-1);

	//The following code runs in :-
	//
	//	O(2n) = O(n)
	//
	// i is the index pointer for array 1 and j is the pointer index of array 2
	//sum is the sum of A[i] and B[j]
	int i=0,j=n-1,sum;
	while( i<n && j>=0 )
	{
		sum = A[i] + B[j] ;
		if(sum == m)
		{
			cout<<"The two elements are \" "<<A[i]<<" \" at index="<<i<<" of array-1 & \" "<<B[j]<<" \" at index "<<j<<" of array-2."<<endl;
			break;
		}
		else if(sum < m)
		{
			i++;
		}
		else
		{
			j--;
		}
	}
	if(i>=n || j<0)
	{
		cout<<"There Exists no i , j such that\n\n\tA[i]\t+\tB[j]\t=\tM\n\n";
	}
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
