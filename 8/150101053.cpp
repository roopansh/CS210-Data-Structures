/************************************************************************************************
ROOPANSH BANSAL
150101053
CS210
************************************************************************************************/

/************************************************************************************************
Implementation of Binomial Heap
************************************************************************************************/

#include <iostream>
#include <iomanip>
// for union function , i have created an array (of size MAX_HEAPS_COUNT ) of pointers to heaps 
#define MAX_HEAPS_COUNT 50

using namespace std;

// Node structure of elements in the heap
struct Node
{
    int key;// store the key/value of the node
    int Degree;// store the degree, that is the number of children of that node
    Node *LeftChild;// pointer to the left most child of the node
    Node *Parent;// pointer to the parent of the node
    Node *Next;// pointer to the next sibling of the node
};

void Make_Heap(Node *Heap[] , int &HeapsCount)
{
	Heap[HeapsCount++] = NULL;
}


// Merge function is used to merge two heaps and create another heap which has the Binomial trees in the non increasing order and there can be two trees with same degree present in the heap
Node *Merge(Node *& Heap1, Node *& Heap2)
{
	// check if any of the heap is null
	if (Heap1 == NULL && Heap2 != NULL)
	{
		return Heap2;
	}
	else if (Heap2 == NULL && Heap1 != NULL)
	{
		return Heap1;
	}
	else if (Heap1 == NULL && Heap2 == NULL)
	{
		return NULL;
	}

	Node *z;// points to the new head of the merged heap
	Node *x = Heap1, *y = Heap2, *temp;// node x and y are the pointers which traverse the Heap1 and Heap2 respectively

	// finding the Head which points to the node with less degree
	if (x->Degree < y->Degree)
	{
		temp = x;
		x = x->Next;
	}
	else
	{
		temp = y;
		y = y->Next;
	}
	z = temp;
	
	// while there are nodes in the root list of both the heaps to be traversed
	// check which one is having lesser degree and join that to the merged list
	while(x != NULL && y != NULL)
	{
		if (x->Degree < y->Degree)
		{
			temp->Next = x;
			x = x->Next;
		}
		else
		{
			temp->Next = y;
			y = y->Next;
		}
		temp = temp->Next;
	}

	// if there are some nodes still left to be linked in any of the heaps
	if (temp->Next == NULL)
	{
		if (x != NULL)
		{
			temp->Next = x;
		}
		if (y != NULL)
		{
			temp->Next = y;
		}
	}
	return z;
}

// Link makes the Node y leftmost child of the Node x
// the calling function takes care that both the nodes x and y have the same degree
void Link(Node *& x , Node *& y)
{
	y->Next = x->LeftChild;
	y->Parent = x;
	x->LeftChild = y;
	x->Degree = x->Degree+1;
}

// Union_Heap merges Heap1 and Heap2 and forms a Heap which satisfies the properties of the Binomial Heap
void Union_Heap(Node *& Heap1 , Node *& Heap2)
{
	//Merged Heap1 & Heap2, and stored in Heap1 only. AFter merging, ther will be Trees in the heap which have the same degree
	Heap1 = Merge(Heap1 , Heap2);

	// if after merging, the heap is still empty, return 
	if (Heap1 == NULL)
	{
		return;
	}

	// Now, we'll combine the nodes having the same degree, for that we'll maintain 3 pointers, current pointer called 'x', pointer to the previous node (Prev_x) and pointer to the next node(Next_x)
	Node *Prev_x = NULL , *x = Heap1, *Next_x = x->Next;
	while(Next_x != NULL)
	{
		if ((x->Degree != Next_x->Degree) || (Next_x->Next != NULL && Next_x->Next->Degree == x->Degree))// when degree of x and next_x is not same or  Degree of x , Next_x and Next of Next_x are same, simply move the pointers by one node each
		{
			Prev_x = x;
			x = Next_x;
			Next_x = Next_x->Next;
		}
		//else exactly two trees whose degrees are same, so we need to combine them
		else if(x->key <= Next_x->key)// key of current node is less than the next node 
		{
			x->Next = Next_x->Next;
			Link(x, Next_x);
			Next_x = x->Next;
		}
		else // key of current node is more than the next node
		{
			if(Prev_x == NULL)
			{
				Heap1 = Next_x;
			}
			else
			{
				Prev_x->Next = Next_x;
			}
			Link(Next_x, x);
			x = Next_x;
			Next_x = Next_x->Next;
		}

	}

	return ;
}

// insert heap makes a new heap with only one node of key=x and merges it with the required Heap
void Insert_Heap(Node *& Heap, int x)
{
	// make a heap with single node of key x
	Node *temp = new Node;
	temp->key = x;
	temp->Parent = NULL;
	temp->LeftChild = NULL;
	temp->Next = NULL;
	temp->Degree = 0;
	
	// Merge the two heaps
	if (Heap == NULL)
	{
		Heap = temp;
		return;
	}

	Union_Heap(Heap , temp);
}

// Show_Heap is used for printing the heap on screen
void Show_Heap(Node * node , int Depth)
{
	if (node->Next != NULL)
	{
		Show_Heap(node->Next , Depth);
	}
	if (node->Parent == NULL)
	{
		cout<<endl;
	}
	if ( node->LeftChild != NULL || node->Parent == NULL )
	{
		cout<<setw(Depth*6 + 4)<<node->key;
		if (node->LeftChild == NULL)
		{
			cout<<endl<<endl;
		}
	}
	else
	{
		cout<<setw(6)<<node->key<<endl;
	}
	if (node->LeftChild != NULL)
	{
		Show_Heap(node->LeftChild , Depth+1);
	}
}

// Print_Heap is used to check if the heap is empty or not before printing
void Print_Heap(Node *Heap)
{
	cout<<"Structure of the binomial Heap (rotated 90 degrees clockwise) is :\n\n ";
	if (Heap == NULL){
		cout<<"Empty Heap"<<endl;
	}
	else 
	{
		cout<<endl;
		Show_Heap(Heap , 0);
	}
}

// Extract_Min finds the minimum of the heap and deletes it from the heap
Node *Extract_Min(Node *& Heap)
{
	// if heap is empty, we can't delete anything
	if (Heap == NULL)
	{
		cout<<"ERROR : Empty Heap."<<endl;
		return NULL;
	}

	// RootPtr is used to traverse the rootlist of the heap and MinPtr points to the minimum of the nodes present among the trees
	Node *RootPtr = Heap;
	Node *MinPtr = Heap;

	// Find the minimum
	while(RootPtr != NULL)
	{
		if (RootPtr->key < MinPtr->key)	MinPtr = RootPtr;
		RootPtr = RootPtr->Next;
	}

	// remove that Root from the heap
	if (Heap == MinPtr)
	{
		Heap = MinPtr->Next;
	}
	else
	{
		RootPtr = Heap;
		while(RootPtr->Next != MinPtr)	RootPtr = RootPtr->Next;
		RootPtr->Next = MinPtr->Next;
	}

	// Create a new heap with the Minimum Root's children as the trees in that heap
	// For creating the new heap, we'll have to reverse the list of the Children of the extracted node.
	Node *NewHeap, *prev, *curr, *next;// used to point to the new heap and reverse the list
	prev = MinPtr->LeftChild;
	if(prev != NULL && prev->Next != NULL)
	{
		curr = prev->Next;
		prev->Next = NULL;
		if (curr->Next != NULL)
		{
			next = curr->Next;
			while(next != NULL)
			{
				curr->Next = prev;
				prev = curr; curr = next; next = next->Next;
			}
			curr->Next = prev;
			NewHeap = curr;
		}
		else
		{
			NewHeap = curr;
			curr->Next = prev;
		}
	}
	else if(prev == NULL)
	{
		return MinPtr;
	}
	else
	{
		NewHeap = prev;
	}

	// making the parent of each node in the new heap to NULL
	Node *TempNode = NewHeap;
	while( TempNode != NULL)
	{
		TempNode->Parent = NULL;
		TempNode = TempNode->Next;
	}

	// Join these two heaps
	Union_Heap(Heap , NewHeap);

	return MinPtr; 
}

// display a list of choice to the user
void Choice()
{
    cout<<endl<<"Choose one of the following options:\n";
    cout<<"(C)\tMAKE-BINOMIAL-HEAP\n";
    cout<<"(U)\tBINOMIAL-HEAP-UNION\n";
    cout<<"(I)\tBINOMIAL-HEAP-INSERT\n";
    cout<<"(D)\tBINOMIAL-HEAP-EXTRACT-MIN\n";
    cout<<"(S)\tPRINT THE BINOMIAL HEAP\n";

    cout<<"(+)\tTurn on print after extract min\n";
    cout<<"(-)\tTurn off print after extract min\n";

    cout<<"(Q)\tEXIT THE PROGRAM\n";
    cout<<endl<<"Enter Choice :\n";
}

// chech if the number of the Heaps created is 0 or not
bool CheckCount(int x)
{
	if (x == 0)	return true;
	else	return false;
}

int main()
{
	// An array of pointers to the first nodes of the Heaps.... Basically, it's an array of pointers to the Heaps
    Node *Heap[MAX_HEAPS_COUNT];
	int HeapsCount = 0;// mainting the count of the heaps

    bool PrintFlag = false;// printflag is used to check we have to do a silent Extract_Min or not. It's controlled by the inputs '+' and '-'

    Choice();// display a choice of options to the user

    char x;// for taking the user choice input

    while(true)
    {
        cin>>x;

        switch(x)
        {
	        // Create a new heap
	        case 'C':
	        case 'c':
	        {
	        	Make_Heap(Heap , HeapsCount);
	            cout<<"Created a new Empty Heap. INDEX OF THIS HEAP IS "<<HeapsCount-1<<endl;
	            break;
	        }

	        // Union of two heaps
	        case 'U':
	        case 'u':
	        {
	        	// check if a heap has been created or not... need to create a new heap before applying this operation
	        	if (CheckCount(HeapsCount))
	        	{
	        		cout<<"Create a heap First\n";
	        		continue;
	        	}

	            cout<<"Enter the indexes of the two binomial heaps you want to merge.\nThe available choices are from 0 to "<<HeapsCount-1<<endl;
	            int a , b;
	            cin>>a>>b;
	            if (a >= HeapsCount || b >= HeapsCount || a < 0 || b < 0)
	            {
	            	cout<<"ERROR : No Heap Found at that INDEX"<<endl;
	            	continue;
	            }
	            else if (a == b)
	            {
	            	cout<<"ERROR : Cannot Merge the heap with itself. Please Enter distinct values .\n";
	            	continue;
	            }

	            Union_Heap(Heap[a] , Heap[b]);
	            cout<<"After the UNION , the new heap is stored in the index : "<<a<<endl;
	            break;
	        }

	        // Inserting a new element to the heap
	        case 'I':
	        case 'i':
	        {
	        	// check if a heap has been created or not... need to create a new heap before applying this operation
	        	if (CheckCount(HeapsCount))
	        	{
	        		cout<<"Create a heap First\n";
	        		continue;
	        	}
	        	int x;
	        	cin>>x;
	        	Insert_Heap(Heap[HeapsCount-1], x);
	        	break;
	        }

	        // Extract Min
	        case 'D':
	        case 'd':
	        {
	        	// check if a heap has been created or not... need to create a new heap before applying this operation
	        	if (CheckCount(HeapsCount))
	        	{
	        		cout<<"Create a heap First\n";
	        		continue;
	        	}

	        	Node *Min = Extract_Min(Heap[HeapsCount-1]);
	            if (PrintFlag && Min != NULL)// no silent extract min
            	{
            		cout<<"Minimum Extracted : "<<Min->key<<endl;
            	}	
	        	break;
	        }

	        // display the heap
	        case 'S':
	        case 's':
	        {
	        	// check if a heap has been created or not... need to create a new heap before applying this operation
	        	if (CheckCount(HeapsCount))
	        	{
	        		cout<<"Create a heap First\n";
	        		continue;
	        	}
	        	if (HeapsCount > 1)
	        	{
	        		cout<<"Which Heap do you want to print? Please enter the index of that heap(Available Heaps are from 0 to "<<HeapsCount-1<<") :\t";
	        		int x;
	        		cin>>x;
	        		if (x < 0 || x >= HeapsCount)
	        		{
	        			cout<<"Please Enter A valid HEAP INDEX"<<endl;
	        			continue;
	        		}
	        		Print_Heap(Heap[x]);
	        	}
	        	else
	        	{
	        		Print_Heap(Heap[HeapsCount-1]);
	        	}
	        	break;
	        }

	        // turn the PrintFlag 'on'
	        case '+':
	        	PrintFlag = true;
	        	cout<<"PrintFlag turned 'ON'"<<endl;
	        	break;

	        // turn the PrintFlag 'off'
	        case '-':
	        	PrintFlag = false;
	        	cout<<"PrintFlag turned 'OFF'"<<endl;
	        	break;

	        // Exit the program
	        case 'q':
	        case 'Q':
	            return 0;
	            break;
	        default:
	            cout<<"Please Enter a valid choice.\n";
	            break;
        }
    }
}
