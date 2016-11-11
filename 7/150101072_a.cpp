#include <iostream>

using namespace std;
//Making structure of a node
struct node
{
	int data;
	node * rep;			//pointer to representative element
	node * next;		//pointer to next element
};
	
//Make a new empty node
node * create(int n)
{
	node *newptr = new node;
	newptr->rep = NULL;
	newptr->next = NULL;
	newptr->data = n;
	return newptr;
}

//Makenode function: Initialises a list of only one node
//O(1) Comlplexity
void makenode(int ele , node **adr , node **head , node **tail ,int *size)
{
	node *temp = create(ele);		//Create empty node
	temp->rep = temp;				//representative element is itself
	temp->next = NULL;				//next pointrt is null
	adr[ele] = temp;				//stores the adress of element node
	head[ele] = temp;				//maintaining head tail and size pointes
	tail[ele] = temp;
	size[ele] = 1;
}

//Findset : Return representative element
//O(1) Comlplexity
int findset(int ele , node **adr)
{
	node * temp = adr[ele];			//Getting  address of node of that element
	return (temp->rep)->data;		//Going to representatove element and returning the data
}

//unionset : 
//O(N) complexity
void unionset(int x , int y , node** adr , node **head , node **tail , int *size)
{
	int rep1 = findset(x , adr);
	int rep2 = findset(y , adr);
	int siz1 = size[rep1];
	int siz2 = size[rep2];
	//cout<<rep1<<" "<<rep2<<" "<<siz1<<" "<<siz2<<endl;
	cout<<"elements of set after being unioned\n";
	
	if(rep1 != rep2)
	{
		if(siz1<siz2)			//list 1 is small
		{
			node * tem = head[rep2];
			for (int i = 1; i <= siz2; ++i)
			{
				cout<<tem->data<<" ";
				tem = tem->next;
			}
			node * temp = head[rep1];
			tail[rep2]->next = head[rep1];
			for (int i = 1; i < siz1; ++i)		//traversing the smaller list and updating representaticve pointer of each element
			{
				temp->rep = adr[rep2];
				cout<<temp->data<<" ";
				temp = temp->next;
			}
			tail[rep2] = temp;
			cout<<temp->data<<endl;
			temp->rep = adr[rep2];
			size[rep2] = siz1+ siz2;
		}
		else					//list 2 is small
		{
			node * tem = head[rep1];
			for (int i = 1; i <= siz1; ++i)
			{
				cout<<tem->data<<" ";
				tem = tem->next;
			}
			node * temp = head[rep2];
			tail[rep1]->next = head[rep2];
			for (int i =1; i < siz2; ++i)		//traversing the smaller list and updating representaticve pointer of each element
			{
				temp->rep = adr[rep1];
				cout<<temp->data<<" ";
				temp = temp->next;

			}
			tail[rep1] = temp;
			cout<<temp->data<<endl;
			temp->rep = adr[rep1];
			size[rep1] = siz1 + siz2;
		}
	}
	else
		cout<<"BOth elements are in same set!!.\n";
}
int main()
{
	node **head , **tail ;
	int *size;
	int k;
	cout<<"Enter the no. of total elements\n";
	cin>>k;
	node **adr;
	head = new node*[100000];					//declaring and initialising all the pointers
	tail = new node*[100000];
	size = new int[100000];
	adr = new node*[100000];
	int ar[k];
	cout<<"Enter elements now\n";
	for (int i = 0; i < k; ++i)
	{
		cin>>ar[i];
		makenode(ar[i] , adr , head , tail , size);	//calling makenode function for each element
	}
	while(true)				//menu based Output
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
				cout<<"representative element : "<<findset(x , adr)<<endl	;
				break;
			}
			case 2:
			{
				int x , y;
				cout<<"Enter the two element whose set is to be Union\n";
				cin>>x>>y;
				unionset(x , y , adr , head , tail , size);
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