/************************
  ROOPANSH BANSAL
  150101053
  CS210
 ************************/

/************************
  To find the Diameter of the tree.
  Running Time - O(n)
Explaination :-
Every node is visited once while recursing.
THe height of the subtrees is updated while recursing only.(No extra function is called for calculating the dia at each node.)
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
		BST();

		//basic functions:
		node * MakeNode(int x);// creating a node with value x
		bool isEmpty();// returning true of the tree is empty otherwise false
		node * root();// return the pointer to the tree

		//functions to modify tree :
		void InsertNode(int x);// inserts the node in the binary search tree in it's right position

		//traversals
		void PreOrderTraversal(node * Node);// Preorder Traversals - Prints the info of the current node followed by the Preorder traversal of the left subtree and right subtree respectively

		//Speacial Applications
		int Diameter(node * Node ,int *Height);// Calculate the diameter of the tree in O(n) running time.
};

// Function Prototypes
void GenerateTree(BST * Tree , int NumOfNodes = 100);// Generates a random binary search tree with given number of nodes....default argument is 100

//Main Function
int main()
{
	// Seed the random fucntion
	srand(time(NULL));

	for(int i=0;i<50;i++)// to calculate the diameter of 50 randomly generated trees
	{
		// Generating the binary search tree
		BST Tree;
		GenerateTree(&Tree);

		/*
								//	FOR DEBUGGING PURPOSE ONLY	//
		int n,val;
		cout<<"How many nodes do you want in the tree :\t";
		cin>>n;
		while(n--)
		{
			cin>>val;
			Tree.InsertNode(val);
		}

		// Print the preorder traversal of the tree
		cout<<"Nodes available are (Printed in Preorder Format) : ";
		Tree.PreOrderTraversal(Tree.root());
		cout<<endl<<endl<<"************************\t************************\t************************\t************************\t************************"<<endl<<endl;
		
		*/

		//temp variable is for the optimisation of the diameter function to run in O(n)
		int temp = 0;

		// store the diameter of the tree 
		int Diameter = Tree.Diameter(Tree.root() , &temp );

		//print the diameter
		cout<<"The Diameter of the Random Tree "<<i+1<<" is \t"<<Diameter<<endl;
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

	// parent and children are set in the function which calls this to function to create the node
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

		// atleast one child of q is NULL , to which p points...and we need to insert the incoming node at that position
		if(x >= q->info)
			q->right = Node;
		else
			q->left = Node;
		Node->parent = q;

		return ;
	}
}

void BST::PreOrderTraversal(node * Node)
{
	// if the node is null then return
	if(Node == NULL)
		return ;
	//Print the current node followed by the function recursion in the left subtree and right subtree respectively
	cout<<"\t"<<Node->info;
	PreOrderTraversal(Node->left);
	PreOrderTraversal(Node->right);

}

int BST::Diameter(node * Node , int *Height)
{
	// If the node is null , then the dia will be zero around that node
	if(Node == NULL)
	{
		*Height = 0;
		return 0;
	}

	// To store the diameter of left subtree and right subtree
	int LeftDia = 0 , RightDia = 0;

	//to store the heights of the left and right subtree while recursing
	int LeftHeight = 0 , RightHeight = 0;

	//	Recursion updates the left and right heights of the left and right subtrees of the node and returns the diameter of left and right subtree 
	LeftDia = Diameter(Node->left , &LeftHeight);
	RightDia = Diameter(Node->right , &RightHeight);

	// Height is the max of height of the left and right subtree
	*Height = max(LeftHeight , RightHeight) +1;

	// Diameter is the max of the diameter of left subtree , right subtree and the diameter which passes through the current node(i.e. left height + right height + 1 )
	return max(LeftHeight+RightHeight+1 , max(LeftDia , RightDia));
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
