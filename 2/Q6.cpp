#include <bits/stdc++.h>

using namespace std;

// creating the structure of node
// it contains the info to be stored and the pointer to next node
struct node
{
	int info;
	node *next ;
};

// Implementing Single Linked List using classes
class Link_List
{
private:
	
	node *HEAD;// Points to the first node of the list
	int size;// stores the number of nodes in the list 

public:

	//Constructor of the class
	Link_List()
	:size(0) // initialises the size of the list to 0
	{
		HEAD = NULL ; // the list is empty. so head points to NULL
	}

	//check if the list has any element
	bool isEmpty()
	{
		//list is empty if there is no element in the list
		// so the head points to NULL
		if (HEAD == NULL)
			return true;
		else
			return false;
	}

	// Create a new node
	node * CreateNode(int x)
	{
		//allocate memory for the new node
		node * Node = new node;

		//store the info the new node
		Node->info = x;

		// set the next pointer to null initially
		Node->next = NULL;

		//return the pointer to this new node
		return Node;
	}

	//Always inserting at the head
	void InsertNode(int x)
	{
		// create a new node having info = x
		node * NodeToInsert = CreateNode(x) ;

		//if the list is empty, simply make the head point to this new ndoe
		if(isEmpty())
		{
			HEAD = NodeToInsert;
			size++;
			return;
		}

		//if the list is not empty , make the new incoming node point to the present first node and update the head pointer to point to the new node 
		NodeToInsert->next = HEAD;
		HEAD = NodeToInsert;

		//Increase the size of the linked list by one for the new element tha thas been inserted
		size++;

		return;
	}

	// always delete the node at the head of the list
	void DeleteNode(int pos)
	{
		//display error message if the list is already empty
		if(isEmpty())
		{
			cout<<"ERROR\t:\tList is Already Empty"<<endl;
			return ;
		}

		//if the list is not empty , first make the HEAD point to the present second node.Hence the second node is now the first node and so on.
		node * NodeToDelete = HEAD;
		HEAD = NodeToDelete->next;
		
		// free the memory of the node removed from the list
		free(NodeToDelete);

		//decreas the size of the linked list by one because one node is deleted
		size--;
		
		return ;
	}


	// I'll simply set the last element to point to a random element in the list
	void CreateLoop(int x)
	{
		//if the list is empty , no loop can be created
		if(isEmpty())
		{
			cout<<"EMPTY LIST : PLease insert nodes in the list"<<endl;
			return;
		}

		//choice inserted by the user is '0' for NO and '1' for YES"
		
		if(x == 0)//No Loop
		{
			// Nothing to do , simply return the function
			return ;
		}
		else//there has to be a loop
		{
			//if there is only one element
			if(size == 1)
			{
				// Loop of one element , that element will point to itself
				HEAD->next = HEAD;
				return ;
			}

			// For more than one elements

			//seed the random function
			srand(time(0));

			// generate a random position in the list , where the loop will be created , that is the last node will point to this node.
			// we have choices from Node-1 , Node-2 , ......Node-(Size-1);
			int RandomNodePosition = random() % (size-1) + 1;
			
			//Node pointer pointing to the first node
			node * ptr = HEAD;
			
			//Traverse the node where the loop will be created
			for(int i=1;i<RandomNodePosition;i++)
			{
				ptr = ptr->next;
			}
			
			// Declare a node to point to the last node
			node * LastNode = HEAD;
			
			//traverse to the last node in the list
			while(LastNode->next != NULL)
			{
				LastNode = LastNode->next;
			}
			
			// make the last node point to that node
			LastNode->next = ptr;
			
			return ;
		}
	}


	// Check if there is a loop in the linked list.
	// Using the tortoise and hare algorithm to check if their is loop in the linked list
	// Move one pointer by one element and the other by two elements.
	// if they ever meet , then their is a loop
	// if any one of them points to null before meeting , then there is no loop
	bool CheckLoop()
	{
		// there is no loop is the list is empty
		if(isEmpty())
		{
			cout<<"The list is Empty"<<endl;
			return false;
		}

		//node pointer A moves two steps at a time
		// node B moves one step at a time
		// initially both point to the first element of the list.
		node *A , *B ;
		A = HEAD;B=HEAD;

		// Move one pointer by one element and the other by two elements.
		// if they ever meet , then their is a loop
		// if any one of them points to null before meeting , then there is no loop
	
		// Note That A will always be ahead of B
		// So need to check if B points to NULL. While A is not NULL , B will not be NULL
		while(true)
		{
			if( A == NULL) // pointer A has reached the end of the list
				return false;
			
			A = A->next;

			if(A == NULL) // pointer A has reached the end of the list
				return false;
			
			A = A->next;
			B = B->next;

			if( A == B) // if both point to the same node , there has to be a loop
				return true;
		}
	}

	// //set next of the nodeA to nodeB
	// void Set_Next(node* NodeA , node * NodeB)
	// {
	// 	NodeA->next = NodeB;
	// 	return ;
	// }

	void PrintList()
	{
		if (isEmpty())
		{
			cout<<"The list is empty.\tThere is nothing to print.\t PLease insert some elements before calling this fucntion "<<endl;
			return ;
		}
		else if(CheckLoop())
		{
			cout<<"ERROR\t:\tTHERE IS A LOOP IN THE LIST\nPLEASE CHECK IT AND CALL THIS FUNCTION";
			return;
		}
		else
		{
			node *ptr = HEAD;
			while(ptr->next != NULL)
			{
				cout<<ptr->info<<" ---> ";
			}
			cout<<endl;
		}
	}
	
};


//The main fucntion
int main()
{
	//Declaring an empty Singly Linked List
	Link_List LL;
	
	//inputing the number of nodes the user wants to input
	int n;
	cout<<"How many elements to enter in the list:\t";
	cin>>n;

	//Input the elements in the linked list
	for(int i=0;i<n;i++)
	{
		cout<<"Enter the "<<i+1<<" element of the linked list:\t";
		int element;
		cin>>element;

		// insert the element in the list
		LL.InsertNode(element);
	}


/*************************************************************************
NOTE :-

	I am asking for the user if he wants a loop in the list
	if he wants , i am simply connecting the last node to a random node in the list
	then i am checking for the loop by traversing the loop using two pointers(one moves 1 node at a time and the other moves 2 nodes at a time)


*************************************************************************/
	//ask user if he wants to create a loop in the linked list
	cout<<"\n\nDo you want a LOOP in the LINKED LIST?\n\nEnter '0' for NO and '1' for YES\t";
	int choice;
	cin>>choice;
	LL.CreateLoop(choice);

	cout<<endl<<"...\nCHECKING THE LIST FOR LOOPS\n...\n"<<endl;
	
	// calling the function to check if there is a loop in the linked list.
	
	if (LL.CheckLoop())
	{
		cout<<"YES\tTHERE IS A LOOP"<<endl;
	}
	else
	{
		cout<<"NO\tTHERE IS NO LOOP"<<endl;
	}
	return 0;
}