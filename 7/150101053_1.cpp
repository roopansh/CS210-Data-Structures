/************************************************************************************************
ROOPANSH BANSAL
150101053
CS210
************************************************************************************************/

/************************************************************************************************
Implement MAKE_SET, FIND_SET, UNION operations using linked list representation
of disjoint sets and the weighted union heuristic.
************************************************************************************************/

#include <bits/stdc++.h>

using namespace std ;

struct Node
{
	int value;// store the value of the node
	Node *Next;// pointer to the next Node of the list
	Node *Representative;// pointer to the representative of the diskoint set
};

// Make_Set() makes a new set in O(1) time
void Make_Set(int val , Node **Address , Node **Head , Node **Tail , int *size)
{
	Node *Obj = new Node;
	Address[val] = Obj;// address stores the address of the node which has value = val
	Obj->value = val;// setting the value of the node
	Obj->Representative = Address[Obj->value];// pointer to the representative. for make set, only one node is added in the list, so that will be the representative of the list
	Obj->Next = NULL;// there is only one node, so the next pointer is NULL
	Head[Obj->value] = Obj;// head points to the head node.
	Tail[Obj->value] = Obj;// tail points to the tail node.
	size[Obj->value] = 1;// size of the set is one.
}

// Find_Set() finds the representative of the node of value x in O(1) time because the representative of different elements is stored in an array 
Node *Find_Set(int x , Node **Address)
{
	if (Address[x] == NULL)	return NULL;
	return Address[x]->Representative;// returns a pointer to the representative node of the list
}

// Union_Set() takes O(n) time
void Union_Set(int x , int y , Node **Head , Node **Tail , Node **Address , int *size)
{
	// I first find the smaller and the larger of the two sets. 
	Node *SmallRep = Find_Set(x , Address);
	Node *LargeRep = Find_Set(y , Address);

	if (SmallRep == LargeRep)// if the representative node of both the nodes x and y are same , it means that they already belong to the same set
	{
		cout<<"Both the elements are already in the same set"<<endl;
		return ;
	}

	// checking the smaller and the larger of the two sets.
	int smallSize = size[SmallRep->value] , largeSize = size[LargeRep->value];
	if (largeSize < smallSize)
	{
		int temp;
		temp = smallSize;
		smallSize = largeSize;
		largeSize = temp;

		Node *tempNode;
		tempNode = SmallRep;
		SmallRep = LargeRep;
		LargeRep = tempNode;
	}

	// size[x] stores the size of the set whose representative is x. So updating the new size = size of smaller set + size of the larger set
	size[LargeRep->value] += size[SmallRep->value];
	size[SmallRep->value] = size[LargeRep->value];

	// updating the representative node of each of the nodes in the smaller set 
	Node *temp = Head[SmallRep->value];
	while(temp != NULL)
	{
		temp->Representative = LargeRep;
		temp = temp->Next;
	}

	// updating the tail pointer and the head pointers for the new list
	Tail[LargeRep->value]->Next = Head[SmallRep->value];
	Tail[LargeRep->value] = Tail[SmallRep->value];
	Head[LargeRep->value] = Head[LargeRep->value];
}

// printing all the sets
void Print_Sets(int k , int *val , Node **Address)
{
	// color array for storing whether the node has been printed or not
	bool Color[100000];
	for (int i = 0; i < k; ++i)
	{
		Color[val[i]] = false;
	}

	int count = 1;// stores the number of sets 
	for (int i = 0; i < k; ++i)
	{
		int x = val[i];
		if (Color[x] == true)// the node has already been printed
		{
			continue;
		}
		cout<<"SET #"<<count++<<":";

		// printing all the nodes present in the set in which x is also present
		Node *rep = Find_Set(x , Address);
		Node *temp = rep;
		while(temp != NULL)
		{
			cout<<"\t"<<temp->value;
			Color[temp->value] = true;
			temp = temp->Next;
		}
		cout<<endl;
	}

}

// function for displaying the choices to the user
void ChoiceDisplay()
{
	cout<<endl;
	cout<<"Please select one of the follwing options:\n";
	cout<<"(1)\tFIND_SET\n(2)\tUNION_SET\n(3)\tEXIT\n";
	cout<<"Enter Choice:\t";
}

int main(int argc, char const *argv[])
{
	Node **Head , **Tail , **Address;// these are arrays of Node Pointers to the Head, Tail, and the Node Itself. Adress[i] points to the node which has value = i
	int *size = new int[100000];// Array where size[i] stores the size of the disjoint set containing the value 'i' 
	Head = new Node*[100000];
	Tail = new Node*[100000];
	Address = new Node*[100000];

	// initialising all the arrays accordingly
	for (int i = 0; i < 100000; ++i)
	{
		Head[i] = NULL;
		Tail[i] = NULL;
		Address[i] = NULL;
		size[i] = 0;
	}

	// taking the elements as input from the user
	int k;
	cout<<"How many Distinct Elements:\t";
	cin>>k;
	int val[k];// stores the values
	cout<<"Enter the "<<k<<" Elements:\n";
	for (int i = 0; i < k; ++i)
	{
		cin>>val[i];
		Make_Set(val[i] , Address , Head , Tail , size);// making a set of the inputed values
	}

	int temp;// for inputing the choice from the user
	while(true)
	{
		ChoiceDisplay();// display the list of choices availabe to the user
		cin>>temp;
		switch(temp)
		{
			case 1://find set
			{
				cout<<"Enter the value whose Representative you want to find:\t";
				int a;
				cin>>a;
				Node *RepOf_a = Find_Set(a,Address);// representative node of the set containing the node a
				if ( RepOf_a == NULL)	cout<<a<<" Not found in any of the Disjoint Data Sets."<<endl;
				else 	cout<<"The value of the representative element of "<<a<<" is "<<RepOf_a->value<<endl;
				break;
			}
			case 2://union set
			{
				cout<<"Enter two values whose sets you want to union\n";
				int x, y;
				cin>>x>>y;
				Union_Set(x , y , Head , Tail , Address , size);
				Print_Sets(k ,val, Address);// printing all the set after the union
				break;
			}
			case 3://exit
			{
				return 0;// will exit the program
			}
			default:
			{
				cout<<endl<<"WRONG INPUT";
				break;
			}
		}
	}
}