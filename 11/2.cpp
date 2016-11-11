#include <bits/stdc++.h>
using namespace std;

struct SibTreeNode
{
	int data;
	SibTreeNode *parent;
	SibTreeNode *firstChild;
	SibTreeNode *nextSibling;
};

struct SibTree
{
	SibTreeNode *root;
	int size;
};

void Print_Tree(SibTreeNode *Node , int k)
{
	// return if the node is NULL
	if (Node == NULL)
	{
		return;
	}

	// printing spaces to denote the level of the node
	for (int i = 0; i < k; ++i)
	{
		cout<<"\t";
	}
	// printig the node, then recursing into the children of the node.
	// doing the same for all the nodes in the sibling list of that node
	cout<<Node->data;
	cout<<endl;
	Print_Tree(Node->firstChild, k+1);
	cout<<endl;
	Print_Tree(Node->nextSibling, k);

}

SibTreeNode *Search_Tree(SibTreeNode *&Node, int k )
{	
	SibTreeNode *ptr = Node;

	// if node is null, just return null
	if (ptr == NULL)
	{
		return NULL;
	}

	do
	{
		if (ptr->data == k)
		{
			return ptr;
		}

		// find the node recursively in the subtree
		SibTreeNode *temp = Search_Tree(ptr->firstChild, k);
		
		if (temp != NULL)// if the node is found in the subtree rooted at Node
		{
			return temp;// return that node
		}

		ptr = ptr->nextSibling;
	}while(ptr != NULL);
	
}

void insertChild(SibTree *&Tree, int k1, int k2, int c)
{
	// make a node with data = k2
	SibTreeNode *temp = new SibTreeNode;
	temp->data = k2;
	temp->parent = NULL;
	temp->firstChild = NULL;
	temp->nextSibling = NULL;

	// if tree is null, directly insert the first node
	if (Tree->root == NULL)
	{
		Tree->root = temp;
		Tree->size++;
		return;
	}

	// search the pointer to the father node k1
	SibTreeNode *Father = Search_Tree(Tree->root , k1);
	
	if (Father == NULL)
	{
		cout<<k1<<" Not Found"<<endl;;
		return;
	}
	
	// insert the new node at the required position
	SibTreeNode *ptr1 = Father->firstChild;
	SibTreeNode *ptr2 = NULL;

	for (int i = 1; i < c && ptr1 != NULL; ++i)
	{
		ptr2 = ptr1;
		ptr1 = ptr1->nextSibling;
	}
	if (ptr2 == NULL)
	{
		Father->firstChild = temp;
		temp->parent = Father;
		temp->nextSibling = ptr1;
	}
	else
	{
		temp->parent = Father;
		temp->nextSibling = ptr1;
		ptr2->nextSibling = temp;
		Tree->size++;
	}
	return ;
}

void Remove_Node(SibTreeNode *&Node , int k)
{
	// search the poitner to the required node
	SibTreeNode *temp = Search_Tree(Node, k);

	if (temp->firstChild == NULL)
	{

		SibTreeNode *parent = temp->parent;
		// if the node is the first child of it's parent, update the firstchild pointer of the parent also
		if (parent->firstChild == temp)
		{
			parent->firstChild = temp->nextSibling;
		}
		// else traverse the children list of the father and remove the node
		else
		{
			SibTreeNode *ptr = parent->firstChild;
			while(ptr->nextSibling != temp)
			{
				ptr = ptr->nextSibling;
			}
			ptr->nextSibling = temp->nextSibling;
		}
		delete(temp);
	}
	return;
}

int main()
{
	// make a new tree
	SibTree *Tree = new SibTree;
	Tree->root = NULL;
	Tree->size = 0;

	// initial tree with 12 nodes
	insertChild(Tree, 0, 1, 0);
	insertChild(Tree, 1, 5, 1);
	insertChild(Tree, 1, 4, 1);
	insertChild(Tree, 1, 3, 1);
	insertChild(Tree, 1, 2, 1);
	insertChild(Tree, 2, 8, 1);
	insertChild(Tree, 2, 7, 1);
	insertChild(Tree, 2, 6, 1);
	insertChild(Tree, 4, 9, 1);
	insertChild(Tree, 5, 11, 1);
	insertChild(Tree, 5, 10, 1);
	insertChild(Tree, 9, 12, 1);

	Print_Tree(Tree->root , 0);
	cout<<endl<<"*******************************************************************"<<endl;

	Remove_Node(Tree->root, 7);
	Print_Tree(Tree->root , 0);
	cout<<endl<<"*******************************************************************"<<endl;

	Remove_Node(Tree->root, 3);
	Print_Tree(Tree->root , 0);
	cout<<endl<<"*******************************************************************"<<endl;

	insertChild(Tree, 2, 99, 2);
	Print_Tree(Tree->root , 0);
	cout<<endl<<"*******************************************************************"<<endl;

	insertChild(Tree, 9, 44, 2);
	Print_Tree(Tree->root , 0);
	cout<<endl<<"*******************************************************************"<<endl;

	insertChild(Tree, 5, 88, 1);
	Print_Tree(Tree->root , 0);
	cout<<endl<<"*******************************************************************"<<endl;

	insertChild(Tree, 7, 22, 1);
	Print_Tree(Tree->root , 0);
	cout<<endl<<"*******************************************************************"<<endl;

	Remove_Node(Tree->root, 4);
	Print_Tree(Tree->root , 0);
	cout<<endl<<"*******************************************************************"<<endl;

	insertChild(Tree, 9,100,5);
	Print_Tree(Tree->root , 0);
	cout<<endl<<"*******************************************************************"<<endl;
	
	cout<<endl;
}