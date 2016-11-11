/************************
ROOPANSH BANSAL
150101053
CS210
************************/

/************************
Generating 100 numbers and then inserting them to the Binary Search Tree(Initially empty).
then printing the level of smallest and largest level of the leaf node.
repeating this experiment for 50 times.
finally printing the number of trees generated such that the difference in levels is 1/2/3...so on.
************************/

#include <bits/stdc++.h>

using namespace std;

//structure of the node
struct node
{
	int info;
	node *left , *right , *parent;
};

// Binary Search Tree implementation using classes
class BST
{
private:
	node* Root;// root pointer points to the frist node of the tree

public:
	// Constructor
	BST();
	
	// basic functions:
	node * MakeNode(int x);// creating a node with value x
	bool isEmpty();// returning true of the tree is empty otherwise false
	node * root();// return the pointer to the tree

	// functions to modify tree :
	void InsertNode(int x);// inserts the node in the binary search tree in it's right position

	// Main Applications required in this question :
	int LargestLevel(node * Node ,int Level);// largest level of the leaf
	int SmallestLevel(node * Node ,int Level);// smallest level of the leaf
};

// Function Prototypes
void InitialseArray(int *arr , int size);// To initialise all the valuse of the array 'arr' of size 'size' to zero
void GenerateTree(BST * Tree , int NumOfNodes = 100);// Generates a random binary search tree with given number of nodes....default argument is 100

//Main Function
int main()
{
	// Seed the random fucntion
	srand(time(NULL));

	// array for storing the largest level of the leaves
	int LargestLevel[50];
	// array for storing the smallest level of leaves
	int SmallestLevel[50];
	// array for storing the difference of the largest level and the smallest level of the leaves
	int Difference[50];
	// DifferenceCount[i] stores the the number of trees whose level difference is 'i'.
	int DifferenceCount[101];
	// Note That the maximum Difference possible is 100 which is possible when all the elements are inserted in a linear form(wall the elements come in sorted manner)

	// Initialse all the different arrays to zero initially
	InitialseArray(LargestLevel , 50);
	InitialseArray(SmallestLevel , 50);
	InitialseArray(Difference , 50);
	InitialseArray(DifferenceCount , 101);

	// Running the experiment a total of 50 times
	for(int i=0;i<50;i++)
	{
		BST Tree;
		// Generating the binary search tree
		GenerateTree(&Tree);		

		// Finding The largest Level
		LargestLevel[i] = Tree.LargestLevel(Tree.root() , 0) ;
		// Finding The smallest Level
		SmallestLevel[i] = Tree.SmallestLevel(Tree.root() , 0) ;

		// Finding the difference of the levels
		Difference[i] = LargestLevel[i] - SmallestLevel[i];
		// Counting the trees where difference level is Difference[i]
		DifferenceCount[Difference[i]]++;
		
		// Printing the Test Case No. , Largest Level , Smallest Level , and the Difference between the levels
		cout<<"S.No.="<<i+1<<" \tLargest Level of Leafs="<<LargestLevel[i]<<"\tSmallest Level of Leafs="<<SmallestLevel[i]<<endl;
	}

	//Printing the Difference Count
	for(int i=0;i<101;i++)
	{
		// not printing the values for which there were no such tree generated such that the difference is i
		if(DifferenceCount[i] != 0)
			cout<<"Difference is\t"<<i<<"\tfor\t"<<DifferenceCount[i]<<"\ttrees."<<endl; 
	}

	return 0;
}

// Constructor of the BST
BST::BST()
{
	// set the root of the tree to null initially
	Root = NULL;
}

// creating a node with value x
node * BST::MakeNode(int x)
{
	// Allocating memory for the new node
	node * NewNode = new node;
	
	// Setting the value to store in that node to 'x'
	NewNode->info = x;
	
	// parent and children are set in the functino which calls this to function to create the node
	NewNode->left = NULL;
	NewNode->right = NULL;
	NewNode->parent = NULL;

	return NewNode;
}

// returning true of the tree is empty otherwise false
bool BST::isEmpty()
{
	if(Root == NULL)
		return true;
	else
		return false;
}

// return the pointer to the tree
node * BST::root()
{
	return Root;
}

// inserts the node in the binary search tree in it's right position
void BST::InsertNode(int x)
{
	// create a new node
	node * Node = MakeNode(x);
	
	// if the tree is empty then set the root to that node.
	if(isEmpty()) //Empty tree
	{
		Root = Node;
	}
	else //	non empty tree
	{
		// need two pointers to move along the tree and find the correct position
		node * p = Root;
		node *q = NULL;
		
		while(p != NULL)// when p is null , we have to insert the new node to that position
		{
			q = p;
			if(x >= p->info)
			{
				p = q->right;
			}
			else
			{
				p = q->left;
			}
		}
		
		// atleast one child of q is NULL , to which p points...and we need to insert to that node
		if(x >= q->info)
			q->right = Node;
		else
			q->left = Node;
		Node->parent = q;

		return ;
	}
}

// largest level of the leaf
int BST::LargestLevel(node * Node ,int Level)
{
	// It's a leaf if all the children are NULL
	if(Node->left == NULL && Node->right == NULL)
	{
		// return the level
		return Level;
	}
	// Recurse in the right sub tree if left child is NULL
	else if (Node->left == NULL)
	{
		return LargestLevel( Node->right , Level+1 );
	}
	// Recurse in the left sub tree if right child is NULL
	else if (Node->right == NULL)
	{
		return LargestLevel( Node->left , Level+1 );
	}
	// if both the children are present
	else
	{
		return max(LargestLevel( Node->right , Level+1 ) , LargestLevel( Node->left , Level+1 ));
	}
}
// smallest level of the leaf
int BST::SmallestLevel(node * Node ,int Level)
{
	// It's a leaf if all the children are NULL
	if(Node->left == NULL && Node->right == NULL)
	{
		return Level;
	}
	// Recurse in the right sub tree if left child is NULL
	else if (Node->left == NULL)
	{
		return SmallestLevel( Node->right , Level+1 );
	}
	// Recurse in the left sub tree if right child is NULL
	else if (Node->right == NULL)
	{
		return SmallestLevel( Node->left , Level+1 );
	}
	// if both the children are present
	else
	{
		return min(SmallestLevel( Node->right , Level+1 ) , SmallestLevel( Node->left , Level+1 ));
	}
}

// To initialise all the valuse of the array 'arr' of size 'size' to zero
void InitialseArray(int *arr , int size)
{
	for(int i=0;i<size;i++)
	{
		arr[i] = 0;
	}
}

// Generates a random binary search tree
void GenerateTree(BST * Tree , int NumOfNodes)
{
	//Generating 100 Numbers and Inserting in the binary tree
	for(int j=0;j<NumOfNodes;j++)
	{
		//random function to generate random integer to insert
		int ToInsert = rand()%5000 + 1;
		Tree->InsertNode(ToInsert);
	}
}
