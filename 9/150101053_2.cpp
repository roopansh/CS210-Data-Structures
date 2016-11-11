/****************************
Roopansh Bansal
150101053
****************************/

#include <bits/stdc++.h>

#define MaxLists 10

using namespace std;

struct node
{
	int key , degree ;
	node *parent, *child, *left, *right;
	bool mark;
};

void Print_List(node *list , int depth )
{
	if (list != NULL)
	{
		node *ptr = list;
		for(int i = 0;i<4*depth;i++)	cout<<" ";
		cout<<"< "<<ptr->key<<", "<<ptr->degree<<", "<<ptr->mark<<" >\n";
		if (ptr->child != NULL)
		{
			Print_List(ptr->child , depth+1);
		}
		ptr = ptr->right;
		while(ptr != list && ptr != NULL)
		{
			for(int i =0; i<4*depth;i++)	cout<<" ";
			cout<<"< "<<ptr->key<<", "<<ptr->degree<<", "<<ptr->mark<<" >\n";
			if (ptr->child != NULL)
			{
				Print_List(ptr->child , depth+1);
			}
			ptr = ptr->right;
		}
	}
	else
	{
		cout<<"Empty List"<<endl;
	}
	return ;
}

node *Make_Node(int x)
{
	node *temp = new node;
	temp->key = x;
	temp->degree = 0;
	temp->parent = NULL;
	temp->child = NULL;
	temp->left = NULL;
	temp->right = NULL;
}

void Insert_Node(node *& list, int x)
{
	node *Toinsert = Make_Node(x);
	if (list == NULL)
	{
		list = Toinsert;
		list->right = list;
		list->left = list;
		return;
	}

	Toinsert->right = list->right;
	Toinsert->left = list;
	list->right->left = Toinsert;
	list->right = Toinsert;
	if (list->key > x)
	{
		list = Toinsert;
	}
	return;
}

node *Create_Random_list(int size = 0)
{
	int x;
	if (size > 0)
	{
		x = rand() % 1000 +1;
		node *List = Make_Node(x);
		List->right = List;
		List->left = List;
		for (int i = 1; i < size; ++i)
		{
			x = rand() % 1000 +1;
			Insert_Node(List , x);
		}
		Print_List(List, 0);
		return List;
	}
	else
	{
		cout<<"Please enter a valid size of the list you want to reandomly generate"<<endl;
	}
}

node *concat_list(node *& list1 , node *& list2)
{
	if (list1 == NULL && list2 == NULL)
	{
		return NULL;
	}
	else if (list1 == NULL)
	{
		return list2;
	}
	else if(list2 == NULL)
	{
		return list1;
	}
	else
	{
		node *MinList = list1;
		if (list2->key < list1->key)
		{
			MinList = list2;
		}

		node *list1_back = list1->left;
		node *list2_back = list2->left;

		list1_back->right = list2;
		list2->left = list1_back;
		list1->left = list2_back;
		list2_back->right = list1;
		
		list1 = MinList;
		list2 = MinList;
		return MinList;		
	}

}

void DisplayChoice()
{
	cout<<"(Q)\tQuit the program\n";
	cout<<"(I)\tInsert Element\n";
	cout<<"(C)\tCreate an Empty Heap\n";
	cout<<"(E)\tExtract Minimum\n";
	cout<<"(U)\tUnion Heap\n";
	cout<<"(S)\tPrint Heap\n";
	cout<<"\nEnter your choice : \n";
}


int NumofNodes(node * list)
{
	if (list == NULL)
	{
		return 0;
	}
	else
	{
		int ans = 0;
		node *ptr = list;
		ptr = ptr->right; ans++;
		while(ptr != list)
		{
			ptr = ptr->right; ans++;
		}
		return ans;
	}
}


void CreateCild(node *& list , node *& child)
{
	if (list == NULL)
	{
		cout<<"Please give a non Empty list";
		return;
	}
	else if (child == NULL)
	{
		return;
	}
	else 
	{
		if(list->child == NULL)
		{
			list->child = child;
		}
		else
		{
			list->child = concat_list(list->child , child);
		}
		list->degree += NumofNodes(child);
		node *ptr = child;
		ptr->parent = list;
		ptr = ptr->right;
		while(ptr != child)
		{
			ptr->parent = list;
			ptr = ptr->right;
		}
		child = list;
	}
}


void Heap_Link(node *List , int x , int y)
{
	node *ptr = List;
	node *X =NULL, *Y=NULL;
	if (ptr->key == x)	X = ptr;
	else if(ptr->key == y)	Y = ptr;
	ptr = ptr->right;
	while(ptr != List)
	{
		if (ptr->key == x)	X = ptr;
		else if(ptr->key == y)	Y = ptr;
		ptr = ptr->right;
	}
	if (X == NULL || Y == NULL)
	{
		cout<<endl<<"ERROR:\tElements not found in the list"<<endl;
		return;
	}
	Y->right->left = Y->left;
	Y->left->right = Y->right;
	Y->left = Y; Y->right = Y;
	CreateCild(X , Y);
}


void ExtractMin_util(node *&Root)
{
	int D = 1000;
	node* AuxArr[D+1];
	for(int i=0;i<D+1;i++)
	{
		AuxArr[i]=NULL;
	}
	node* x = Root;
	node* pt = x;
	node* y;
	int d;

	//Join two nodes untill all degree are one
	do
	{
		pt = pt->right;
		d = x->degree;
		while(AuxArr[d]!=NULL)
		{
			y = AuxArr[d];
			if(x->key > y->key)
			{
				node* temp = x;
				x = y;
				y = temp;
			}
			if(y == Root)
				Root = x;
			Heap_Link(Root , y->key , x->key);
			if(x->right == x)
				Root = x;
			AuxArr[d] = NULL;
			d = d+1;
		}
		AuxArr[d] = x;
		x = x->right;
	}while(x!=Root);

	node* min1 = NULL;
	for (int j = 0; j < D+2; ++j)
	{
		if(AuxArr[j]!=NULL)
		{
			AuxArr[j]->left = AuxArr[j]; 
			AuxArr[j]->right = AuxArr[j]; 
			if(min1!=NULL)
			{
				(min1->left)->right = AuxArr[j];
				AuxArr[j]->right = min1;
				AuxArr[j]->left = min1->left;
				min1->left = AuxArr[j];
				if(AuxArr[j]->key < min1->key)
					min1 = AuxArr[j];
			}
			else
			{
				min1 = AuxArr[j];
			}
			if(min1==NULL)
	    			 min1=AuxArr[j];
	   			 else if(AuxArr[j]->key < min1->key)
	   				  min1=AuxArr[j];
		}
	}
	Root = min1;
}

node *ExtractMin(node *& Root)
{
	if (Root == NULL)
	{
		return Root;
	}

	node *ans = Root;

	node *ptr1 = Root->right;
	node *NewMin = ptr1;

	while(ptr1 != Root)
	{
		if (ptr1->key < NewMin->key)
		{
			NewMin = ptr1;
		}
		ptr1 = ptr1->right;
	}

	node *ptr2 = ans->child;
	node *NewHeap = ptr2;
	if (ptr2 != NULL)
	{
		ptr2->parent = NULL;
		while(ptr2->right != ans->child)
		{
			ptr2->parent = NULL;
			if (ptr2->key < NewHeap->key)
			{
				NewHeap = ptr2;
			}
			ptr2 = ptr2->right;
		}		
	}
	else if (ans == ans->right)
	{
		NewMin = NULL;
	}

	Root->left->right = Root->right;
	Root->right->left = Root->left;
	Root = NewMin;

	if (NewHeap != NULL)
	{
		Root = concat_list(Root , NewHeap);
	}

	// now consolidate
	// ExtractMin_util(Root);

	return ans;
}

int main()
{
	srand(time(NULL));
	node *Heap[MaxLists];
	int ListCount = 0;
	DisplayChoice();
	char ch;
	while(cin>>ch)
	{
		switch(ch)
		{
			case 'Q':// exit
			case 'q':
			{
				return 0;
			}
			case 'I':// insert element
			case 'i':
			{
				cout<<"Enter the element to insert:\t";
				int x;
				cin>>x;
				Insert_Node(Heap[ListCount-1] , x);
				break;
			}
			case 'c':
			case 'C':// create empty heap
			{
				Heap[ListCount++] = NULL;
				cout<<"Created an empty list at index = "<<ListCount-1<<endl;
				break;
			}
			case 'e':
			case 'E':// Extract min
			{
				node *Min = ExtractMin(Heap[ListCount-1]);
				if (Min == NULL)
				{
					cout<<"Empty Heap"<<endl;
					continue;
				}
				cout<<"The Minimum is : "<<Min->key;
				break;
			}
			case 'u':
			case 'U':// Union heap
			{
				if (ListCount > 1)
				{
					Print_List(concat_list(Heap[ListCount-2] , Heap[ListCount-1]) , 0);
				}
				break;
			}
			case 's':
			case 'S':// print Heap
			{
				Print_List(Heap[ListCount-1], 0);
				break;
			}
			default:
			{
				cout<<"Enter a valid choice !"<<endl;
			}
		}
	}
}