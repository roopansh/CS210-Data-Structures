#include <bits/stdc++.h>

using namespace std;

// defining the node of the structure
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

//Insert a node after the given node
void InsertAfter(int DataToInsert , int InsertAfter)
{
	// 	Check if the LIST IS EMPTY
	if(isEmpty())//(HEAD == NULL)
	{
		cout<<"ERROR : EMPTY LIST"<<endl;
		return;
	}

	node *p = HEAD;
	
	for(int i=1;i<InsertAfter;i++)
	{
		p = p->next;
		if(p == NULL)
		{
			cout<<"ERROR : THE INPUT POISTION IS OUT OF BOUNDS\n";
		}
	}
	
	node *q = CreateNode(DataToInsert);

	q->next = p->next;
	p->next = q;
	return ;
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

//Insert at the END
void InsertAtEnd(int x)
{
	node *q = CreateNode(x);
	q->next = NULL;

	if(isEmpty())//HEAD == NULL
	{
		HEAD = q;
	}
	else
	{
		node *p = HEAD;
		while(p->next != NULL)
		{
			p = p->next;
		}
		p->next = q;
	}
	return ;
}

//Delete a node after a given node in the list
void DeleteAfter(int x )
{
	if(isEmpty())
	{
		cout<<"ERROR : THE LIST IS EMPTY"<<endl;
		return;
	}
	else
	{
		node *p = HEAD;
		for(int i=1;i<x;i++)
		{
			p = p->next;
		}
		if(p->next == NULL)
		{
			cout<<"ERROR : NO ELEMENT TO DELETE"<<endl;
		}
		else
		{
			node *q = p->next;
			p->next = q->next;
			delete(q);
		}
	}
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

//Delete the last node of the list
void DeleteLastNode()
{
	if(isEmpty())
	{
		cout<<"ERROR : THE LIST IS EMPTY"<<endl;
		return;
	}
	else if(HEAD->next == NULL)
	{
		node *p = HEAD;
		HEAD = NULL;
		delete(p);
	}
	else
	{
		node *p = HEAD;
		node *q = p->next;
		while(q->next != NULL)
		{
			p = q;
			q = q->next;
		}
		p->next = NULL;
		delete(q);
	}
}

//Returns the top element of the list
int TopList()
{
	if(isEmpty())
	{
		cout<<"ERROR : THE LIST IS EMPTY"<<endl;
		return -1;
	}
	else
	{
		node *p = HEAD;
		while(p->next != NULL)
		{
			p = p->next;
		}
		return p->value;
	}
}

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
			cout<<"\t\t"<<p->value<<endl;
			p = p->next;
		}
		while(p != NULL);
	}
}

// Display the choices available for the user to input
void Display();

// Function for deciding which function to call based on the input by the user
void Choice(int n);


//MAIN FUNCTION 
int main()
{
	//initially the list is empty
	HEAD = NULL;

	//seeding the ranodom number generator
	srand(time(0));

	// temp for storing a random integer
	int temp = rand() % 1000 +1 ;
	InsertAtHead(temp);

	//Input the size of the list to initialise initially
	cout<<"What size of list to generate initially?\n\n<<--\tMINIMUM ONE ELEMENT IS REQUIRED\t-->>\n\n";
	int size;
	cin>>size;

	for(int i=1;i<size;i++)
	{
		temp = rand()%1000 +1 ;
		InsertAtEnd(temp);
	}



	//callint the function to print the initial array
	cout<<"THE INITIAL LIST IS : -"<<endl<<endl;
	PrintCompleteList();

	//Asking user what to do 
	int opt;
	Display();
	while(cin>>opt)
	{
		if(opt==0)
			break;
		Choice(opt);
		Display();
		//PrintCompleteList();
	}
	return 0;
}



void Display()
{
	cout<<endl;
	cout<<"ENTER 0 TO EXIT"<<endl;
	// cout<<"Enter integer for required funtion on the list"<<endl;
	cout<<"1\tInsert a new node after a given position in the list."<<endl; 
	cout<<"2\tInsert at the start of a list."<<endl;
	cout<<"3\tInsert a node at the end of a list."<<endl;
	cout<<"4\tDelete a node after a given position in the list."<<endl;
	cout<<"5\tDelete the first node of the list."<<endl;
	cout<<"6\tDelete the last node of the list."<<endl;
	cout<<"7\tPrint the entire list."<<endl;
	cout<<"8\tCheck if the list is empty."<<endl;
	cout<<endl;
}

void Choice(int n)
{
	int val;
	int after;
	switch(n)
	{
		case 1:
			cout<<"Input the Value to Insert :\t";
			cin>>val;
			cout<<"Insert after the value :\t";
			cin>>after;
			InsertAfter(val, after);
			break;
		case 2:
			cout<<"Input the Value to Insert :\t";
			cin>>val;
			InsertAtHead(val);
			break;
		case 3:
			cout<<"Input the Value to Insert :\t";
			cin>>val;
			InsertAtEnd(val);
			break;
		case 4:
			cout<<"Delete after the value :\t";
			cin>>after;
			DeleteAfter(after);
			break;
		case 5:
			DeleteFirst();
			break;
		case 6:
			DeleteLastNode();
			break;
		case 7:
			PrintCompleteList();
			break;
		case 8:
		if(isEmpty())
			cout<<"The list is empty\n";
		else
			cout<<"The list is NOT empty\n";
		break;
		default:
			cout<<"\nERROR : THE CHOICE ENETERED IS INVALID.\nPLEASE TRY AGAIN\n";
	}
}