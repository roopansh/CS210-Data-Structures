/*
Shubham Singhal
150101072

Binomial Heaps
*/


#include <bits/stdc++.h>

using namespace std;


//Structure of one node
struct heap
{
	int value;						//Storing value
	int degree;						//Degree
	heap* leftmost;					//pointer to leftmost child
	heap* sibling;					//pointer to next node at same level
	heap* parent;					//pointer to parent
};


//Making binommail heap class
class BH
{
	heap* rootlist;					//making poinrter of rootlist as private
public:
	void Make()
	{
		rootlist = NULL;			//initilising by making rootlist null
	}

	void Insert(int ele)
	{
		
		//Make a new node
		heap* temp = new heap;
		temp->value = ele;
		temp->degree = 0;
		temp->leftmost = NULL;
		temp->sibling = NULL;
		temp->parent = NULL;
		heap* newrootlist = temp;

		//Union new node with existing binomial heap
		Union(rootlist , newrootlist);
	}
	
	void Union(heap* originallist , heap* newlist)
	{
		heap* templist = NULL;
		heap* templist2;
		
		//Normal merging of two list to be union(in order of increasing degrees)

		while(originallist!=NULL && newlist!=NULL)
		{
			if(originallist->degree <= newlist->degree)
			{
				// cout<<"1\n";
				if(templist == NULL)
				{
					templist = originallist;
					templist2 = templist;
				}
				else
				{
					templist->sibling = originallist;
					templist = templist->sibling;
				}
				originallist = originallist->sibling;
			}
			else if(originallist->degree > newlist->degree)
			{
				// cout<<"2sure\n";
				if(templist == NULL)
				{	
					templist = newlist;
					templist2 = templist;
				}
				else
				{
					templist->sibling = newlist;
					templist = templist->sibling;
				}
				newlist = newlist->sibling;
			}
		}
		if(originallist == NULL)
		{
			// cout<<"3\n";
			while(newlist!=NULL)
			{
				if(templist == NULL)
				{
					templist = newlist;
					templist2 = templist;
				}
				else
				{
					templist->sibling = newlist;
					templist = templist->sibling;
				}
				newlist = newlist->sibling;
			}
		}
		if(newlist == NULL)
		{
			// cout<<"4\n";
			while(originallist!=NULL)
			{
				if(templist == NULL)
				{
					templist = originallist;
					templist2 = templist;
				}
				else
				{
					templist->sibling = originallist;
					templist = templist->sibling;
				}
				originallist = originallist->sibling;
			}
		}

		//after mergng is complete , make new merged list equal to rootlist 

		rootlist = templist2;


		//Making the main union function (keep track of 3 pointers)

		heap* prevx = NULL;
		heap* x = rootlist;
		heap* nextx = x->sibling;

		//going until whole merged list is traversed
		while(nextx != NULL)
		{
			//case 1 : if degrees not equal , move pointers one step ahead
			
			if(x->degree != nextx->degree)
			{
				prevx = x;
				x = nextx;
				nextx = nextx->sibling;
			}

			//case 2 : if three BH have same degrees , move pointers one step ahead
			else if(nextx->sibling!=NULL && x->degree == nextx->degree && nextx->degree == (nextx->sibling)->degree)
			{
				// cout<<"case 2\n";
				prevx = x;
				x = nextx;
				nextx = nextx->sibling;
			}	

			//case 3 : if two BH have same degrees , combine one with higher degree as child of other
			else if(x->value <= nextx->value)
			{
				// cout<<"case 3\n";
				x->sibling = nextx->sibling;
				nextx->parent = x;
				nextx->sibling = x->leftmost;
				x->leftmost = nextx;
				x->degree = x->degree+1;

				nextx = x->sibling;

			}

			//case 4 : if two BH have same degrees , combine one with higher degree as child of other
			else if(x->value > nextx->value)
			{
				// cout<<"case 4\n";
				if(prevx == NULL)
					rootlist = nextx;
				else
				{
					prevx->sibling = nextx;
				}
				x->parent = nextx;
				x->sibling = nextx->leftmost;
				nextx->leftmost = x;
				nextx->degree = nextx->degree+1;

				x = nextx;
				nextx = x->sibling;
								
			}
		}
	}

	//Making extractmin function

	int ExtractMin()
	{
		int minvalue;
		if(rootlist == NULL)
		{
			return -1;
		}
		heap* traverse = rootlist;
		heap* traversehelp = rootlist;
		heap* minkey = new heap;
		minkey->value = INT_MAX;
		
		//traversing the whole list to find min node
		while(traversehelp!=NULL)
		{
			if(traversehelp->value < minkey->value)
			{	
				minkey = traversehelp;
				// minkey->value = traversehelp->value;
				minvalue = minkey->value;
			}
			traversehelp = traversehelp->sibling;
		}

		//making a list containing only children of heap having min node 

		heap* revchildlist = minkey->leftmost;
		heap* childlist;

		//reversing the ist since we want it to be in increasing order of degree
		if(revchildlist!=NULL)
		{
			if(revchildlist->sibling == NULL)
			{
				childlist = revchildlist;
			}
			else
			{
				heap* prev = NULL;
				heap* curr = revchildlist;
				heap* next;
				while(curr!=NULL)
				{
					next = curr->sibling;
					curr->sibling = prev;
					prev = curr;
					curr = next;
				}
				childlist = prev;
			}	
		}
		else
		{
			childlist = NULL;
		}
		
		//Make seond list with the heap removed which was storing min element

		traversehelp = traverse;
		heap * ptr1;
		if(traversehelp==NULL)
		{
			ptr1 = NULL;
		}
		else
		{
			ptr1 = traversehelp->sibling;
		}
		if(ptr1 == NULL)
		{
			traverse = NULL;
			if(childlist!=NULL)
				Union(traverse , childlist);		//Unioning the two list formed
			else
				rootlist = NULL;
		}
		else
		{
			while(ptr1 != NULL)
			{
				if(traversehelp == minkey)
				{
					traverse = ptr1;
					break;
				}
				else if(ptr1 == minkey)
				{
					traversehelp->sibling = ptr1->sibling;
					break;
				}
				traversehelp = ptr1;
				ptr1 = ptr1->sibling;
			}	
			Union(traverse , childlist);			////Unioning the two list formed
		}
		return minvalue;
	}

	//show binomial heap function
	void showBinomialHeap()
	{
		cout<<"Stucture of binomial heap (rotated 90 degrees clockwise):\n";
		if (rootlist == NULL ) 
			cout<<"Heap is Empty\n";
		else
			ShowHeap(rootlist,0);
	}

	//recursive showheap function
	void ShowHeap(heap* x,int depth) 
	{
		if ( x != NULL )
		{
	    	//recursively show all its sibling first
	    	if (x->sibling != NULL)
	        	ShowHeap ( x->sibling, depth ) ; 
	    	
	    	if (x->parent == NULL)
	    		cout << endl ;    
	 
	    	if ( (x->leftmost != NULL) || (x->parent == NULL) )
	    	{
	        	cout << setw(depth*6 + 4)<< x->value ;
	        	if (x->leftmost == NULL) 
	        		cout << "\n\n" ;   //node with degree 0
	    	}
	     	else
	     	{
	        	cout <<setw( 6 )<< x->value << "\n\n" ;  
	    	}
	    	// take care of children of that heap
	    	if (x->leftmost != NULL)
	        	ShowHeap ( x->leftmost, depth+1 ) ;  
	  	}
	}
};

int main(int argc, char const *argv[])
{
	BH obj;
	cout<<" c \tMAKE-BINOMIAL-HEAP\n"<<" i \tBINOMIAL-HEAP-INSERT(i element_to_insert)\n"<<" d \tBINOMIAL-HEAP-EXTRACT-MIN\n"<<" s \tDisplay\n"<<" + \tTurn off Print after extract min\n"<<" - \tTurn on print after extract min\n"<<" e \tEXIT\n";
	char flag = '-';
	cout<<"\n"<<" First call MAKE-BINOMIAL-HEAP (enter c) to initilise binomial heap\n After entering i enter a integer also"<<endl;
	while(true)
	{
		char s;
		cin>>s;
		switch(s)
		{
			case 'c':	
			{
				obj.Make();
				break;
			}
			case 'i':
			{
				int ele;
				cin>>ele;
				obj.Insert(ele);
				break;
			}
			case 's':
			{
				obj.showBinomialHeap();
				break;
			}
			case '-':
			{
				flag = '-';
				break;
			}
			case '+':
			{
				flag = '+';
				break;
			}
			case 'd':
			{
				int toprint = obj.ExtractMin();
				if(toprint == -1)
						cout<<"Empty HEap\n";
				if(flag == '-')
				{
					if(toprint!=-1)
					cout<<"The minimum element extracted is "<<toprint<<endl;
				}
				break;
			}
			case 'e':
			{
				return 0;
			}
			default:
			{
				cout<<"Wrong option chosen\n";
			}
		}	
	}
	return 0;
}