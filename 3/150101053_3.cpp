/************************
ROOPANSH BANSAL
150101053
CS210
************************/

/************************
To find the lowest common ancestor.
Running Time - O(n) where n is the number of nodes in the tree
EXPLAINATION:-
For calculating the path for any node , we'll be visiting every node exactly once to check if it is in the path from the node to the root
Hence , for calculating the paths for the two different nodes , we'll require 'O(n)' time for each.
The path would contain at most 'n' elements (i.e. equal to the height of the tree when the binary tree is created for a sorted input).
Hence while calulating the LCA , there can be atmost n Comparisons.
So running time = O( n + n + n ) = O(n)
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
	
	//basic functions:
	node * MakeNode(int x);// creating a node with value x
	bool isEmpty();// returning true of the tree is empty otherwise false
	node * root();// return the pointer to the tree
	
	//functions to modify tree :
	void InsertNode(int x);// inserts the node in the binary search tree in it's right position
	
	//traversals
	void PreOrderTraversal(node * Node);// Preorder Traversals - Prints the info of the current node followed by the Preorder traversal of the left subtree and right subtree respectively

	//Speacial Applications
	int LCA(int v , int w);// calulates the Lowest Common Ancestor of the two nodes v and w
	bool PathToNode(node * Node ,int x , vector<int> & v);// Stores the info of the nodes in the vector 'v' starting from the node to the root of the tree
};

// Funciton Prototype
void GenerateTree(BST * Tree , int NumOfNodes = 100);// Generates a random binary search tree with the given number of nodes..default number of nodes is 100

//Main Function
int main()
{
	// Seed the random fucntion
	srand(time(NULL));

	// Generating the binary search tree
	BST Tree;
	GenerateTree(&Tree);		

/*
			//	FOR DEBUGGING PURPOSE ONLY // 
	int n,temp;
	cin>>n;
	while(n--)
	{
		cin>>temp;
		Tree.InsertNode(temp);
	}
*/
	// Print the preorder traversal of the tree
	cout<<"Nodes available are (Printed in Preorder Format) : ";
	Tree.PreOrderTraversal(Tree.root());
	cout<<endl<<endl<<"************************\t****************\t************************\t************************\t************************"<<endl<<endl;

	// asking user to input two values from the available node values which are printed above
	int  v , w;
	cout<<endl<<endl<<"ENTER ANY TWO VALUES FROM THE NODES AVAILABLE ABOVE"<<endl<<endl;
	cout<<"FIRST:\t";cin>>v;
	cout<<"SECOND:\t";cin>>w;

	//Computing the Lowest Common Ancestor and storing the key value of the node in the variable LCA
	int LCA = Tree.LCA( v , w );

	// Printing LCA on the screen
	cout<<"Least Common Ancestor is\t"<<LCA<<endl;

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

// Printing LCA on the screen
int BST::LCA(int v , int w)
{
	// define two vectors for storing the paths from the node v and w to the root
	vector<int> v_Path; 
	vector<int> w_Path;

	if( !PathToNode(Root , v , v_Path) ) // if there is no path from the root to the node 'v'
	{
		cout<<v<<" Not Found in the Tree."<<endl<<"Please Try Again"<<endl;
		return 0;
	}
	if( !PathToNode(Root , w , w_Path) ) // if there is no path from the root to the node 'w'
	{
		cout<<w<<" Not Found in the Tree."<<endl<<"Please Try Again"<<endl;
		return 0;
	}

	// NOTE :- path is stored from starting from the node to the root
	// we'll reverse that path so that the vectors now store the path from the root to the required node
	reverse(v_Path.begin() , v_Path.end());
	reverse(w_Path.begin() , w_Path.end());

	// Define vector iterators for these vector(paths)
	vector<int>::iterator v_it = v_Path.begin(), w_it = w_Path.begin();
	
	// FOR DEBUGGING PURPOSE ONLY
	/*
	for(v_it;v_it!=v.end();v_it++)
		cout<<" "<<*v_it;
	for(w_it;w_it!=w.end();w_it++)
		cout<<" "<<*w_it;
	v_it = v.begin();
	w_it = w.begin();
	*/

	// LCA is the last common node in the two paths from root to 'v' and from root to 'w'

	// while both the vectors contain the same node , we can move to the next node
	while(*v_it == *w_it)
	{
		v_it++;
		w_it++;
	}

	//return the last node which is common
	return *(--v_it);
}

// calulates the Lowest Common Ancestor of the two nodes v and w
bool BST::PathToNode(node * Node , int x , vector<int> & v)
{
	// if the node is found then push the node in the vector
	// NOTE THAT TILL NOW VECTOR WOULD BE EMPTY AND WOULD NOT CONTAIN ANY NODES
	if(Node->info == x)
	{
		v.push_back(Node->info);
		return true; //	Returns true to denote that the required node was found
	}

	// If node has left child
	if(Node->left != NULL)
	{
		if( PathToNode( Node->left , x , v ) ) // Check if the subtree on the left has the node x RECURSIVELY
		{
			// if left subtree has the node x , insert the node into the vector
			v.push_back( Node->info );
			return true; //	Returns true to denote that the required node was found
		}
	}

	// If node has right child
	if(Node->right != NULL)
	{
		if( PathToNode( Node->right , x , v ) ) // Check if the subtree on the right has the node x RECURSIVELY
		{
			// if right subtree has the node x , insert the node into the vector
			v.push_back( Node->info );
			return true; //	Returns true to denote that the required node was found
		}
	}

	// If the node would have been found , then the compiler would have exited this function in any one of the above return True statements // Else the required node woudn't be found and we'll have to return false
	return false; 
}

// Generates a random binary search tree
void GenerateTree(BST * Tree , int NumOfNodes)
{
	//Generating 100 Numbers and Inserting in the binary tree
	for(int j=0;j<NumOfNodes;j++)
	{
		//random function to generate random integer to insert
		int ToInsert = rand()%5000 + 1 ;
		Tree->InsertNode(ToInsert);
	}
}