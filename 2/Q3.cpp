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

/******************** QUEUE FUNCTIONS **************************/
// insert at the end
void INSERT(int val)
{
	InsertAtEnd(val);
}

// delete from the head
void DELETE()
{
	DeleteFirst();
}

// print the complete queue
void PRINTCOMPLETE()
{
	PrintCompleteList();
}

// print the first element
int PRINT_HEAD()
{
	if(isEmpty())
	{
		cout<<"ERROR\t:\tTHE QUEUE IS EMPTY"<<endl;
	}
	else
	{
		return HEAD->value;
	}
}

//display the options to the user
void Display()
{
	cout<<endl;
	cout<<"ENTER 0 TO EXIT OR"<<endl;
	// cout<<"Enter integer for required funtion on the list"<<endl;
	cout<<"1\tINSERT"<<endl; 
	cout<<"2\tDELETE"<<endl;
	cout<<"3\tPRINT COMPLETE."<<endl;
	cout<<"4\tPRINT HEAD"<<endl;
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
			INSERT(val);
			cout<<endl;
			break;
		case 2:
			DELETE();
			cout<<endl;
			break;
		case 3:
			PRINTCOMPLETE();
			cout<<endl;
			break;
		case 4:
			cout<<"The Top Element is\t"<<PRINT_HEAD()<<endl;
			cout<<endl;
			break;
		default:
			cout<<"\nERROR : THE CHOICE ENETERED IS INVALID.\nPLEASE TRY AGAIN\n";
	}
}


//main function
int main()
{
	//initially the queue is empty
	HEAD = NULL;

	//seeding the random number generator
	srand(time(0));

	// temp for storing a random integer
	int temp = rand() % 1000 +1 ;
	INSERT(temp);

	//Input the size of the list to initialise initially
	cout<<"What size of QUEUE to generate initially?\n\n<<--\tMINIMUM ONE ELEMENT IS REQUIRED\t-->>\n\n";
	int size;
	cin>>size;

	for(int i=1;i<size;i++)
	{
		temp = rand()%1000 +1 ;
		InsertAtEnd(temp);
	}



	//callint the function to print the initial array
	cout<<"THE INITIAL QUEUE IS : -"<<endl;
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