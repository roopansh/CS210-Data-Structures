#include <bits/stdc++.h>

using namespace std;

/*****************
USING THE FUNCTIONS FROM QUESTION 1 AS IT IS
******************/

struct node
{
	int value;
	node *next;
} *HEAD ;

//Check if the list is empty
bool isEmpty()
{
	if(HEAD == NULL)
		return true;
	else
		return false;
}

// Create a new node
node * CreateNode( int x)
{
	node *NodePtr;
	NodePtr = new node;
	NodePtr->value = x;
	NodePtr->next = NULL;
	return NodePtr;
}

//Insert node at the starting of the list
void InsertAtHead(int x)
{
	node * p = CreateNode(x);
	if(isEmpty())
	{
		HEAD = p;
	}
	else
	{
		p->next = HEAD;
		HEAD = p;
	}
	return ;
}

//Delete the first node of the list
void DeleteFirst()
{
	if(isEmpty())
	{
		cout<<"ERROR : THE LIST IS EMPTY"<<endl;
	}
	else
	{
		node *p = HEAD;
		node *q = p->next;
		HEAD = q;
		delete(p);
	}
}

// for priniting the complete list
void PrintCompleteList()
{
	if(isEmpty())
	{
		cout<<"ERROR : THE LIST IS EMPTY"<<endl;
		return ;
	}
	else
	{
		node *p = HEAD;
		do
		{
			cout<<p->value<<endl;
			p = p->next;
		}
		while(p != NULL);
	}
}
/**************************STACK FUNCTIONS************************************/
// for inserting the value in the stack
void PUSH(int val)
{
	InsertAtHead(val);
}

//for deleteing the top element of the stack
void POP()
{
	DeleteFirst();
}

// returning the top element of the stack
int TOP()
{
	if(isEmpty())
	{
		cout<<"ERROR\t:\tTHE LIST IS EMPTY\n";
		return -1;
	}
	else
	{
		return HEAD->value;
	}
}

// to print the complete stack
void PRINT()
{
	PrintCompleteList();
}

//display the options to the user
void Display()
{
	cout<<endl;
	cout<<"ENTER 0 TO EXIT OR"<<endl;
	// cout<<"Enter integer for required funtion on the list"<<endl;
	cout<<"1\tPUSH"<<endl; 
	cout<<"2\tPOP"<<endl;
	cout<<"3\tPRINT."<<endl;
	cout<<"4\tTOP"<<endl;
	cout<<endl;
}

//input choice and call the required function
void Choice(int n)
{
	cout<<endl;
	int val;
	switch(n)
	{
		case 1:
			cout<<"Input the Value to Insert :\t";
			cin>>val;
			PUSH(val);
			cout<<endl;
			break;
		case 2:
			POP();
			cout<<endl;
			break;
		case 3:
			PRINT();
			cout<<endl;
			break;
		case 4:
			cout<<"The Top Element is\t"<<TOP()<<endl;
			cout<<endl;
			break;
		default:
			cout<<"\nERROR : THE CHOICE ENETERED IS INVALID.\nPLEASE TRY AGAIN\n";
	}
}

// MAIN FUCNTION
int main()
{
	//initially the stack is empty
	HEAD = NULL;

	//seeding the ranodom number generator
	srand(time(0));

	// temp for storing a random integer
	int temp = rand() % 1000 +1 ;
	InsertAtHead(temp);

	//Input the size of the list to initialise initially
	cout<<"What size of STACK to generate initially?\n\n<<--\tMINIMUM ONE ELEMENT IS REQUIRED\t-->>\n\n";
	int size;
	cin>>size;

	for(int i=1;i<size;i++)
	{
		temp = rand()%1000 +1 ;
		PUSH(temp);
	}

	//callint the function to print the initial array
	cout<<"THE INITIAL STACK IS : -"<<endl;
	PrintCompleteList();

	//Asking user what to do 
	int opt;
	Display();
	while(cin>>opt)
	{
		if(opt==0)
			break;
		Choice(opt);
		cout<<endl;
		Display();
		cout<<endl;
		//PrintCompleteList();
	}

	return 0;
}