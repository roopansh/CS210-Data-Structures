#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

//Funciton Prototypes
void Arr_Initalise(int *arr , int n);
void random_gen(int *arr , int n);
void Algo_Implement(int *arr , int n);
void PART_A(int *arr , int n);
void PART_B(int *arr , int n);
void Print_Arr(int *arr , int n);
void Print_Span(int *X , int *S , int n);

//Main Funciton
int main()
{
	int n;
	cout<<"Enter the size of the array:\t";
	cin>>n;
	
	int X[n];
	
	//To initialise the array
	Arr_Initalise(X , n);

	//Function to call for PART - A and PART B of the question
	Algo_Implement(X , n);

	return 0;
}

//To select whether to generate array randomply or input from user
void Arr_Initalise(int *arr , int n)
{
	int choice;
	cout<<"Enter (0) to initialise the array randomly or press (1) to input the array:\t";
	cin>>choice;
	
	switch(choice)
	{
		//randomly generate the array 
		case 0:
		random_gen(arr , n);
		cout<<"Array generated is :-\n";
		Print_Arr(arr , n);
		break;

		//input the array from the user
		case 1:
		cout<<"Enter the Elements:\n";
		for(int i=0;i<n;i++)
		{
			cin>>arr[i];
		}
		break;

		default:
		cout<<"WRONG INPUT\tPLEASE TRY AGAIN"<<endl;
		Arr_Initalise(arr , n);
		break;
	}
	return ;
}


//Function to generate a array(size n) of random numbers from 0 to 1000
void random_gen(int *arr , int n)
{
	srand(time(0));
	for(int i=0;i<n;i++)
	{
		arr[i] = rand()%1001;
	}
	return ;
}

//To check with which implementation to run
// O(n^2) or O(n)
void Algo_Implement(int *arr , int n)
{
	int choice;
	cout<<endl<<"How to implement?"<<endl<<"PRESS (0) for O(n^2) ALGO OR (1) FOR O(N) ALGO"<<endl;
	cin>>choice;
	switch(choice)
	{
		case 0:
		//Calling function for part A. O(n^2) algorithm
		PART_A(arr , n);
		break;

		case 1:
		//Calling function for part B. O(n) algorithm
		PART_B(arr , n);
		break;

		default:
		cout<<"WRONG INPUT\tPLEASE TRY AGAIN"<<endl;
		Algo_Implement(arr , n);
		break;
	}
	return ;
}

//O(n^2) implementation 
void PART_A(int *arr , int n)
{
	//to store the span
	int S[n];
	for(int i=0;i<n;i++)
	{
		int j = i;
		S[i] = 1;
		{
			while(j>0 && arr[j] >= arr[i])
			{
				S[i]++;
				j--;
			}
		}
	}
	Print_Span(arr , S , n);
	return ;
}

//O(n) implementation 
void PART_B(int *arr , int n)
{
	//to store the span
	int S[n];


	/************************************************************************************************/

	Print_Span(arr , S , n);
	return ;
}

//Print the aray of size n
void Print_Arr(int *arr , int n)
{
	for(int i=0;i<n;i++)
	{
		cout<<arr[i]<<"\t";
	}
	cout<<endl;
	return ;
}

//print the span along with the array
void Print_Span(int *X , int *S , int n)
{
	for(int i=0;i<n;i++)
	{
		cout<<"SPAN OF\tX["<<i+1<<"] = "<<X[i]<<" is \t "<<S[i]<<endl;
	}
	cout<<endl;
	return ;
}