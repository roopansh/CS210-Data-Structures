/*
Shubham Singhal
150101072
Union By rank and path compressoin
Time complexity of m makeset and union opoerations : O(m)
amortized time complexity of any operation : O(1)
*/

#include <bits/stdc++.h>

using namespace std;
//Making structure of a node
struct node
{
	int data;
	node *parent;		//pointer to parent
	int rank;			//Rank of node
};
//Make a new empty node
node* create(int ele)
{
	node *ptr = new node;
	ptr->data = ele;
	ptr->parent = ptr;
	ptr->rank = 0;
	return ptr;
}

//Makeser function : make a tree with just one node
//O(1) coplexity
void makeset(int ele , node **adr)
{
	node * newptr = create(ele);
	adr[ele] = newptr;
}

//Findset function : return the representative element
node* findset(node* x)
{
	if(x!=x->parent)
	{
		x->parent = findset(x->parent);				//Path compression heuristics.
	}												//As u go up change parent of each node to representative element
	return x->parent;
}

//unionset function
void unionset(int x , int y , node **adr , int ar[] , int k)
{
	int rep1 = findset(adr[x])->data;
	int rep2 = findset(adr[y])->data;
	if(rep1!=rep2)
	{
		if(adr[rep1]->rank == adr[rep2]->rank)			//if rank is equal increment rank by 1
		{
			adr[rep1]->parent = adr[rep2];
			adr[rep2]->rank += 1;
		}
		else if(adr[rep1]->rank < adr[rep2]->rank)		//if rank unequal change pointer of tree with less rank
		{
			adr[rep1]->parent = adr[rep2];
		}
		else
		{
			adr[rep2]->parent = adr[rep1];
		}	
	}	
	else
	{
		cout<<"elements belong to same set already\n";
	}

	//PRinting all the sets of all disjoints sets
	cout<<"elements of set after being unioned\n";
	vector<int> *v;
	v = new vector<int>[100000];
	for (int i = 0; i < k; ++i)
	{
		int repele = findset(adr[ar[i]])->data; 
		v[repele].push_back(ar[i]);
		
	}
	for (int i = 0; i < 100000; ++i)
	{
		if(v[i].size()!=0)
		{
			for (int j = 0; j < v[i].size(); ++j)
			{
				cout<<v[i].at(j)<<" ";
			}
			cout<<endl;
		}

	}

}

int main(int argc, char const *argv[])
{
	int k;
	cout<<"Enter the no. of total elements\n";
	cin>>k;
	int ar[k];
	node **adr;										//Making an address array to store addresses of nodes
	adr = new node*[100000];						//Maximum value of node is assumed to be 100000
	cout<<"Enter elements now\n";
	for (int i = 0; i < k; ++i)
	{
		cin>>ar[i];
		makeset(ar[i] , adr);						//calling makeset function
	}
	//menu based output
	while(true)
	{
		int option;
		cout<<"1. Find_Set\n2. Union\n3. Exit\n";
		cin>>option;
		switch(option)
		{
			case 1:
			{
				int x;
				cout<<"Enter the element\n";
				cin>>x;
				cout<<"representative element : "<<findset(adr[x])->data<<endl;
				break;
			}
			case 2:
			{
				int x , y;
				cout<<"Enter the two element whose set is to be Union\n";
				cin>>x>>y;
				unionset(x , y , adr , ar , k);
				break;
			}
			case 3:
			{
				return 0;
				break;
			}
			default:
			{
				cout<<"Wrong option\n";
				continue;
			}
		}

	}
	return 0;
}