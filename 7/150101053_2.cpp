/************************************************************************************************
ROOPANSH BANSAL
150101053
CS210
************************************************************************************************/

/************************************************************************************************
Implement MAKE_SET, FIND_SET, UNION operations using Disjoint-set forests and union
by rank and path compression heuristics.
************************************************************************************************/

#include <bits/stdc++.h>

using namespace std ;

struct Node
{
	int value;// stores the value of the node
	Node *Parent;// points to the parent of the node. If it points to itself , it means that it is the representatove of it's set
	int rank;// stores the rank of the set
};

//Make_Set() makes a set containing just one node in O(1) time
void Make_Set(int val , Node **Address)
{
	Node *Obj = new Node;
	Address[val] = Obj;// address stores a pointer to the node whose value is val
	Obj->value = val;// setting the value of the node to val
	Obj->Parent = Address[Obj->value];// is equal to the Obj itself
	Obj->rank = 0;// initially the rank is 0
}

// Find_Set() finds the representative of the node whose value is 'x' and as well as reduce the path from the node x to it's representative
Node *Find_Set(int x , Node **Address)
{
	if (Address[x] == NULL)	return NULL;
	if (Address[x]->Parent != Address[x])
	{
		Address[x]->Parent = Find_Set(Address[x]->Parent->value , Address);
	}
	return Address[x]->Parent;
} 

// Union_Set() joints two distinct sets
void Union_Set(int x , int y , Node **Address)
{
	Node *Rep1 = Find_Set(x , Address);// representaive of the first set
	Node *Rep2 = Find_Set(y , Address);// representative of the second set

	if (Rep1 == Rep2)// both x and y belongs to the same set
	{
		cout<<"Both the elements are already in the same set\n";
		return;
	}

	if (Rep1->rank == Rep2->rank)// if both have the same rank, then it doesn't matter which set is joined to which. the rank increases by one
	{
		Rep1->Parent = Rep2;
		Rep2->rank += 1;// rep2 is the new representative of the new set formed from the union of two sets
	} 
	else if (Rep1->rank < Rep2->rank)// rank of set 1 is less than rank of set 2, so join set 1 to set 2
	{
		Rep1->Parent = Rep2;
	}
	else // rank of set 2 is less than rank of set 1, so join set 2 to set 1
	{
		Rep2->Parent = Rep1;
	}
}

// print_set first finds which node belongs to which set and then prints all the set
void Print_Sets(int k , int *val , Node **Address)
{
	bool Color[100000];// to check if the node is alreasy included in some set or not
	for (int i = 0; i < k; ++i)
	{
		Color[val[i]] = false;
	}
	std::vector<int> v[100000];
	for (int i = 0; i < k; ++i)
	{
		int x = val[i];
		if (Color[x] == true)// this node is already included in some set
		{
			continue;
		}
		v[Find_Set(x,Address)->value].push_back(x);// push the node to the vector list of the representative of that set
		Color[x] = true;
	}

	int count = 0;// stores the number of sets
	for (int i = 0; i < 100000; ++i)
	{
		if (v[i].size() == 0)	continue;// there are no nodes in that vector list
		
		// print the vector list
		count++;
		cout<<"SET #"<<count<<":";
		for (int j = 0; j < v[i].size(); ++j)
		{
			cout<<"\t"<<v[i].at(j);
		}
		cout<<endl;
	}

}

// display a choice of options available to the user
void ChoiceDisplay()
{
	cout<<endl<<endl;
	cout<<"Please select one of the follwing options:\n";
	cout<<"(1)\tFIND_SET\n(2)\tUNION_SET\n(3)\tEXIT\n";
	cout<<"Enter Choice:\t";
}

int main(int argc, char const *argv[])
{
	Node **Address;// array of Node Pointers pointing to Itself. Adress[i] points to the node which has value = i
	Address = new Node*[100000];

	for (int i = 0; i < 100000; ++i)	Address[i] = NULL;
	
	// taking all the nodes as input from the user
	int k;
	cout<<"How many Distinct Elements:\t";
	cin>>k;
	int val[k];// stores the values
	cout<<"Enter the "<<k<<" Elements:\n";

	for (int i = 0; i < k; ++i)
	{
		cin>>val[i];
		Make_Set(val[i] , Address);// making set of one nodes initially
	}

	int temp;// for inputing the choice of the user
	while(true)
	{
		ChoiceDisplay();// display the options available to the user
		cin>>temp;
		switch(temp)
		{
			case 1://find set
			{
				cout<<"Enter the value whose Representative you want to find:\t";
				int a;
				cin>>a;
				Node *RepOf_a = Find_Set(a,Address);// returns the representative of the set containing the node a
				cout<<endl;
				if ( RepOf_a == NULL)	cout<<a<<" not found in any of the Disjoint Data Sets."<<endl;
				else 	cout<<"The value of the representative element of "<<a<<" is "<<RepOf_a->value<<endl;
				break;
			}
			case 2://union set
			{
				cout<<"Enter two values whose sets you want to union\n";
				int x, y;
				cin>>x>>y;
				Union_Set(x , y , Address );// combines the two sets
				cout<<endl;
				Print_Sets(k ,val, Address);// printout the sets
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