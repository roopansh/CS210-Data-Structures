/************************
ROOPANSH BANSAL
150101053
CS210
************************/

// This header file includes all the header files required
#include <bits/stdc++.h>

using namespace std;

//Function Prototypes
int CalulateTreeSize(int InputSize);//	Calculates the tree size to form for a given input of array size
void InputTreeElements(int *Tree , int size , int Input);//	Inputs the tree elements in the required position and puts dummy nodes wherever required 
void buildTournamentTree(int *Tree , int size);//	Builds a winner tournament tree
void PrintTree(int *Tree , int size);//	Print the tree

int main()
{
	// Input the number of elements 
	cout<<"Enter the number of inputs :\t";
	int n;
	cin>>n;

	// Calculate the size of the tree to build
	int size = CalulateTreeSize(n) ;
	
	// declare winner tree as an array
	int WinnerTree[size+1];

	// input the numebr of elements in the required poistions 
	InputTreeElements(WinnerTree , size , n);
	
	// Build the Tournament tree
	buildTournamentTree(WinnerTree , size);
	
	// Print the tree
	PrintTree(WinnerTree , size);
	
	return 0;
}

//	Calculates the tree size to form for a given input of array size
int CalulateTreeSize(int InputSize)
{
	// first calulates the number of levels in required in the tree.
	//	from that calulate the number of nodes required in the tree 
	//
	return pow( 2 , ceil(log2(InputSize)) + 1 )  -1 ;
}

//	Inputs the tree elements in the required position and puts dummy nodes wherever required 
bool InputTreeElements(int *Tree , int size , int Input)
{
	int i;
	cout<<"Enter the elements \n";

	// We'll input the number of elements to the last level of the tree
	for(i=size/2 +1 ; i<size/2 +1 + Input ; i++)
	{
		int val;
		cin>>val;
		if(val < 0)
		{
			cout<<"WRONG INPUT"<<endl;
			return ;
		}
		// storing the values to the tree simultaneously
		Tree[i] = val;
	}

	// for the rest of the nodes left in the last level of the tree , we'll store INT_MIN as a dummy ndoe
	for(i ; i<=size ; i++)
	{
		Tree[i] = INT_MIN;
	}
	return ;
}

//	Builds a winner tournament tree
void buildTournamentTree(int *Tree , int size)
{
	// from the second last level to the first level , 
	// keep on calculating the value of node as the maximum of the two children values
	for(int i = size/2 ; i>0 ; i--)
	{
		int left = 2*i;// left child of the current node
		int right = 2*i+1;//	Right child ofthe current node
		Tree[i] = max(Tree[left] , Tree[right]);
	}
	return ;
}

//	Print the tree
void PrintTree(int *Tree , int size)
{
	//	Print tree print 'XX' where dummy node is stored
	int i=1;
	cout<<endl<<"THE TREE GENERATED IS:\n";
	cout<<Tree[i++];
	bool flag = false;
	while(i <= size)
	{
		// if the Tree[i] contains the dummy node , just print a XX in it's place and continue 
		if(Tree[i] == INT_MIN)
		{
			i++;
			cout<<"\tXX";
			flag = true;
			continue;
		}
		cout<<"\t"<<Tree[i++];
	}
	cout<<endl;
	if(flag)
	{	cout<<"***********************************************************"<<endl;
		cout<<"NOTE :: 'XX' DENOTES THE DUMMY NODE"<<endl;
		cout<<endl<<"***********************************************************"<<endl;
	}
}