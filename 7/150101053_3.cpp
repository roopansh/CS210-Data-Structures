/************************************************************************************************
ROOPANSH BANSAL
150101053
CS210
************************************************************************************************/

/************************************************************************************************
The off-line minimum problem
1) Create n sets initially

2) The input sequence is represented in the follwing form
		I1	E  I2  E  I3  E  I4  E  ....  I(m)  E I(m+1)
	NOTE :	E represents a SINGLE extract operation
			Ij represents a subsequence of insert operations.(It can also be empty).

3) For each subsequence Ij , place the corresponding nodes in the set K[j]
	NOTE :	Note that K[j] is NULL if Ij is empty subsequence

4) Then using the follwing algorithm
	for i = 1 to n
		determine j such that i belongs to K[j]
		if j != m+1
			ans[j] = i
			K[l] be the next set which exists
			Union K[l] with K[j] and DELETE K[j].
************************************************************************************************/

#include <bits/stdc++.h>

using namespace std;

struct Node
{
	int value;// stores the value of the node
	Node *Parent;// points to the parent of the node. If it points to itself , it means that it is the representatove of it's set
	int Number;// stores the index of K in which the node appears
};

//Make_Set() makes a set containing just one node in O(1) time
void Make_Set(int val , Node **Address)
{
	Node *Obj = new Node;
	Address[val] = Obj;// address stores a pointer to the node whose value is val
	Obj->value = val;// setting the value of the node to val
	Obj->Parent = Address[Obj->value];// is equal to the Obj itself
}

// Find_Set() finds the representative of the node 'x' and as well as reduce the path from the node x to it's representative. It's running time is O(Log n)
Node *Find_Set(Node *x)
{
	if (x->Parent != x)// x is not the representative then
	{
		x->Parent = Find_Set(x->Parent);// update the parent of x to equal to the representative
	}
	return x->Parent;
} 

// Union_Set() simply sets the parent of second node equal to the parent of first node passed as the arguments. It's runnig time is O(1). 
void Union_Set(Node *root , Node *node)
{
	node->Parent = root;
}// we have to make sure that we pass the representatives of the set as parameters to the Union_Set() function.

// it generates the result of the query using the above algorithm
int *Offline(int n , int m , Node ** Address , Node **K , bool *K_Exist)
{
	int *ans = new int[m+1];// for storing the final answer
	for (int i = 1; i <= n; ++i)
	{
		Node *temp = Find_Set(Address[i]);// find the representative of the node whose value is i
		int j = temp->Number;// find the index of the K in which it lies
		if (j != m+1)
		{
			ans[j] = i;

			// find the next l for which K[l] exists
			int l = j+1;
			while(l < m+2 && !K_Exist[l] )	l++;

			//union K[l] with K[j] and delte K[j]. for deleting K[j], an array K_Exist is maintained which stores whether K[j] set exists or not
			if(K[l] == NULL)
			{
				K[l] = new Node;
				K[l]->value = 0;
				K[l]->Parent = K[l];
				K[l]->Number = l;
			}
			Union_Set(K[l] , K[j]);
			K[j] = NULL;K_Exist[j] = false;
		}
	}
	return ans;
}

int main()
{
	// input the required values from the user
	int n,m;
	cout<<"Enter the number of insert operations:\t";
	cin>>n;
	cout<<"Enter the number of extract-min operations:\t";
	cin>>m;
	char input;
	int arr[n+m+1];
	Node *Address[n+1];
	cout<<"Enter the sequence of operations\nNOTE:PLEASE PUT A SPACE BETWEEN TWO DIFFERENT OPERATIONS\n";
	for (int i = 1; i < n+m+1; ++i)
	{
		cin>>input;
		if (input == 'E')	arr[i] = -1;
		else
		{
			arr[i] = input -48;//-48 because 0 is represented as 48 in ASCII.
			Make_Set(arr[i] , Address);// making the set of the values 
		}
	}

	// making the K array
	Node **K = new Node*[m+2];
	for (int i = 0; i < m+2; ++i)
	{
		K[i] == NULL;
	}
	int j = 1;

	// making the sets and storing in the respective K[j] 
	for (int i = 1; i < n+m+1; ++i)
	{
		if (arr[i] != -1)
		{
			K[j] = Address[arr[i]];
			K[j]->Number = j;
			while(i+1<n+m+1 && arr[i+1] != -1)
			{
				Union_Set( K[j] , Address[arr[i+1]]);
				i++;
			}
		}
		else	j++;
	}

	// generating whether set K[j] exists or not...initially all the sets exist
	bool K_Exist[j+1];
	for (int i = 1; i <= j; ++i)	K_Exist[i] = true;
	
	// finding and printing the required answer
	int *ans = 	Offline(n, m, Address , K , K_Exist);
	cout<<endl<<"The Required answer is :- "<<endl;
	for (int i = 1; i < m+1; ++i)
	{
		cout<<ans[i]<<"\t";
	}
	cout<<endl;
}
