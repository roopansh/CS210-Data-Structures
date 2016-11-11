/************************
ROOPANSH BANSAL
150101053
CS210
************************/

/************************
Generating 100 numbers and then inserting them to the Binary Tree(Initially empty).
Then printing the number of leaves for all the trees.
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
	// Constructor :
	BST();

	// basic functions :
	bool isEmpty();// returning true of the tree is empty otherwise false
	node * root();// return the pointer to the tree
	node * MakeNode(int x);// creating a node with value x

	// functions to modify tree:
	void InsertNode(int x);// inserts the node in the binary search tree in it's right position

	// Speacial Applications :
	void Leaves(node* Node , int & Count);// counts the number of the leaves in the tree
};

// Funciton Prototype
void GenerateTree(BST * Tree , int NumOfNodes = 100);// Generates a random binary search tree with the given number of nodes..default number of nodes is 100

//Main Function
int main()
{
	// Seed the random fucntion
	srand(time(NULL));

	for(int i=0;i<50;i++)
	{
		//Declare a Binary search tree
		BST Tree;
		// generating random integers and inputing in the tree
		GenerateTree(&Tree );

		// initialise no of leaves to zero
		int LeavesCount = 0;

		// calculate the leaves by calling the function at the root of the tree and then recursively counting
		Tree.Leaves(Tree.root(),LeavesCount);

		cout<<"The number of the leaves in the\t"<<i+1<<" tree are : \t"<<LeavesCount<<endl;
	}
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

// Count the number of leaves in the tree
void BST::Leaves(node* Node , int & Count)
{
	// node having no children is a leave
	if (Node->left == NULL && Node->right == NULL)
	{
		Count++;
	}

	// if there is a left child , recurse in the left subtree
	if(Node->left != NULL)
		Leaves(Node->left , Count);

	// if there is a right child , recurse in the right subtree
	if(Node->right != NULL)
		Leaves(Node->right , Count);

	return ;//return nothing because i've passed a reference to the variable storing the number of leaves as an argument to the function. 
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