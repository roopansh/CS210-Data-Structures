#include <bits/stdc++.h>
using namespace std;

void foo(int *arr , int *brr, int n)
{
	// initialising the variables
	int i1 = 0, i2 = i1, j=i1, min = arr[i1];
	while(i1<n)
	{
		// first finding the indexes whose elements will be swapped
		j = i1;
		i2 = j;
		min = arr[j];

		while(j < n)
		{
			if(arr[j] <= min)
			{
				i2 = j;
				min = arr[j];
			}
			j++;
		}

		//swap the elements
		if (i2 > i1 && brr[i2] != brr[i1])
		{
			//swap brr[i] and brr[j]
			int temp = brr[i1];
			brr[i1] = brr[i2];
			brr[i2] = temp;
		}

		// DEBUGGING PURPOSE
		// for (int i = 0; i < n; ++i)
		// {
		// 	cout<<brr[i]<<" ";
		// }
		// cout<<endl;

		// printing the pattern
		int k = 0;
		if(i1 != i2 && brr[i2] != brr[i1])
		{
			while(k<i1)
			{
				cout<<"\t";
				k++;
			}
			cout<<brr[i1]<<"\t";k++;
			while(k<i2)
			{
				cout<<"\t";
				k++;
			}
			cout<<brr[i2];k++;
			cout<<endl;

			//copy brr to arr
			for (int i = 0; i < n; ++i)
			{
				arr[i] = brr[i];
			}
		}
		i1++;
	}
}

int main()
{
	int n;
	cout<<"Enter the numebr of elements:\t";
	cin>>n;
	int arr[n], brr[n];
	cout<<"Enter the elements:\n";
	for (int i = 0; i < n; ++i)
	{
		cin>>arr[i];
		brr[i] = arr[i];
	}

	// print the orginal array
	cout<<endl<<endl;
	for (int i = 0; i < n; ++i)
	{
		cout<<arr[i]<<"\t";
	}
	cout<<endl;
	
	foo(arr, brr, n);
	
}