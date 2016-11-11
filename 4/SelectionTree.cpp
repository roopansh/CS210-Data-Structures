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
int ExtractMax(int * Tree);// Extracts the maximum of the current tree
int nextMax(int * Tree , int size);// removes the maximum and makes the winner tree in O(Log(n))

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
	
	//	Extract the first winner out of the tree
	// cout<<"First Winner of the Tournament is :- "<<ExtractMax<<endl;

	cout<<endl<<"************************************************************"<<endl;

	// Extract the second winner out of the tree by removing the first one and then rebuilding the tree by tracing along the path
	int SecondMax = nextMax(WinnerTree , size);

	//	again printing the tree
	PrintTree(WinnerTree , size);

	// printitng the second tree
	cout<<endl<<"New Winner of the tournament is :\t"<<SecondMax<<endl;

	return 0;
}

int CalulateTreeSize(int InputSize)
{
	// first calulates the number of levels in required in the tree.
	//	from that calulate the number of nodes required in the tree 
	return pow( 2 , ceil(log2(InputSize)) + 1 )  -1 ;
}


void InputTreeElements(int *Tree , int size , int Input)
{
	int i;
	cout<<"Enter the elements \n";

	// We'll input the number of elements to the last level of the tree
	for(i=size/2 +1 ; i<size/2 +1 + Input ; i++)
	{
		int temp;
		cin>>temp;
		Tree[i] = temp;
	}

	// for the rest of the nodes left in the last elvel of the tree , we'll store INT_MIN as a dummy ndoe
	for(i ; i<=size ; i++)
	{
		Tree[i] = INT_MIN;
	}
	return ;
}

void buildTournamentTree(int *Tree , int size)
{
	// from the second last level to the first level , 
	// keep on calculating the value of node as the maximum of the two children values
	for(int i = size/2 ; i>0 ; i--)
	{
		int left = 2*i;
		int right = 2*i+1;
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
	if(flag)
	{	cout<<endl<<"***********************************************************"<<endl;
		cout<<"NOTE :: 'XX' DENOTES THE DUMMY NODE"<<endl;
		cout<<endl<<"***********************************************************"<<endl;
	}
}

int ExtractMax(int * Tree)
{
	// we are making sure that the tree passed is already built as a winner tournament tree
	return Tree[1];
}

int nextMax(int * Tree , int size)
{
	// first start from the top and then go to the bottom tracing the value of the tree and putting zero in it's path
	int i=1;
	while(i<=size/2)
	{
		if(Tree[i] == Tree[2*i]) // Left child
		{
			// Tree[i] = 0;
			i = 2*i;
		}
		else // Right child
		{
			// Tree[i] = 0;
			i = 2*i +1;
		}
	}
	
	// finally putting 0 in the node from where the winner comes
	Tree[i] = 0;

	// going to the parent of the tree
	i = i/2;

	// again making the winner tree along the path from where it comes.
	// simply go along it's parent which are currently storing zeroes.
	while(i>0)
	{
		Tree[i] = max(Tree[2*i] , Tree[2*i +1]);//	check whose value will be stored in the node by comparing the values of it's children nodes 
		i = i/2;
	}

	return Tree[1]; // return the new maximum of the tree
}