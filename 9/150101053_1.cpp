#include <bits/stdc++.h>

#define MaxLists 50 

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

void DisplayChoice()
{
	cout<<"(0)\tQuit the program\n";
	cout<<"(1)\tInsert Element\n";
	cout<<"(2)\tCreate an Empty List\n";
	cout<<"(3)\tCreate Random List\n";
	cout<<"(4)\tConcat List\n";
	cout<<"(5)\tPrint List\n";
	cout<<"(6)\tNumber of Nodes\n";
	cout<<"(7)\tCreate Child\n";
	cout<<"(8)\tHeap Link\n";
	cout<<"\nEnter your choice : \n";
}

int main()
{
	srand(time(NULL));
	node *Heap[MaxLists];
	int ListCount = 0;
	DisplayChoice();
	int ch;
	while(cin>>ch)
	{
		switch(ch)
		{
			case 0:// exit
			{
				return 0;
			}
			case 1:// insert element
			{
				cout<<"Enter the element to insert:\t";
				int x;
				cin>>x;
				Insert_Node(Heap[ListCount-1] , x);
				break;
			}
			case 2:// create empty list 
			{
				Heap[ListCount++] = NULL;
				cout<<"Created an empty list at index = "<<ListCount-1<<endl;
				break;
			}
			case 3:// create a random list
			{
				cout<<"what is the size of the list that you want to create randomly:\t";
				int x;
				cin>>x;
				Heap[ListCount++] = Create_Random_list(x);
				cout<<"Created a random list at index = "<<ListCount-1<<endl; 
				break;
			}
			case 4:// concat list
			{
				cout<<"What are the lists that you want to concat.\n";
				cout<<"( Available index are = 0 to "<<ListCount-1<<" )"<<endl;
				int a ,b;
				cin>>a>>b;
				if (a>=0 && b>=0 && a<ListCount && b<ListCount)
				{
					Print_List(concat_list(Heap[a] , Heap[b]) , 0);
				}
				else
				{
					cout<<"Please enter valid index";
				}
				break;
			}
			case 5:// print list
			{
				Print_List(Heap[ListCount-1], 0);
				break;
			}
			case 6:// num of nodes
			{
				cout<<NumofNodes(Heap[ListCount-1])<<endl;
				break;
			}
			case 7:// create child
			{
				int a , b;
				cout<<"Enter list index : ";cin>>a;
				cout<<"Enter child-list index : ";cin>>b;
				if (a>=0 && b>=0 && a<ListCount && b<ListCount)
				{
					CreateCild(Heap[a] , Heap[b]);
				}
				else
				{
					cout<<"Please enter valid index";
				}
				break;
			}
			case 8:// heap link
			{
				int x,y;
				cout<<"Available nodes are : "<<endl;;
				Print_List(Heap[ListCount-1],0);
				cout<<"enter the key of x:\t"<<endl;cin>>x;
				cout<<"enter the key of y:\t"<<endl;cin>>y;
				if (x == y)
				{
					cout<<"Please enter distinct values"<<endl;
					continue; 
				}
				Heap_Link(Heap[ListCount-1] , x , y);
				cout<<"Link Success\n";
				Print_List(Heap[ListCount-1],0);
				break;
			}
			default:
			{
				cout<<"Enter a valid choice !"<<endl;
			}
		}
	}
}