//shivam gupta
//150101068

#include <bits/stdc++.h>
using namespace std;

//defining structure for binomial heap
//key stores value in the node
//and rest vaiables as per name
struct node
{
	int degree;
	int key;
	node* parent;
	node* left_child;
	node* sibling;
};

//defining class bheap for binomial heap
class bheap
{
//root will be the pointer to the 1t node from which whole heap is accessed
private:
	node* root;

public:

    void make_bheap()
    {
        root=NULL;
	}
    

	void insert(int n)
	{
		//making a new node temp from given value n and then taking its union with root 
		node* temp=new node;
		temp->parent=NULL;
		temp->left_child=NULL;
		temp->sibling=NULL;
		temp->degree=0;
		temp->key=n;


		node* list1=root;
		node* list2=temp;
		
		uni(list1,list2);
	}

	//function for uniting 2 heaps.
	void uni(node* list1,node* list2)
	{
		node* x;
		if(list1==NULL)
		{
			list1=list2;
			x=list1;
			root=x;
			return;
		}
		if((list1->degree) < (list2->degree) )
		{
			x=list1;
			list1=list1->sibling;
		}
		else
		{
			x=list2;
			list2=list2->sibling;
		}
		
		node* final;
		final=x;

		//merging the two lists 
		while(list1!=NULL && list2!=NULL)
		{
			if((list1->degree) < (list2->degree))
			{
				final->sibling=list1;
				final=final->sibling;
				list1=list1->sibling;
			}
			else
			{
				final->sibling=list2;
				final=final->sibling;

				list2=list2->sibling;
			}
		}

		//copying the nodes of 1st and 2nd lists not covered in while loop
		if(list1!=NULL)
		{
			while(list1!=NULL)
			{
				final->sibling=list1;
				list1=list1->sibling;
				final=final->sibling;
			}
		}

        if(list2!=NULL)
		{
			while(list2!=NULL)
			{
				final->sibling=list2;
				list2=list2->sibling;
				final=final->sibling;
			}
		}

		root=x;
	
		//combine function is used to combine all binary trees of same degrees
		combine(x);
	}


	//function to extract min value 
	int extract_min()
	{
		
		node* x=root;
		if(root==NULL)
		{
			cout<<"tree is already empty "<<endl;
			return -1;
		}
		node *min_ptr,*min_child;
		min_ptr=NULL;
		int min=INT_MAX;
		node* prev1=NULL,*minprev;
		while(x!=NULL)
		{
			if(x->key < min)
			{
				min=x->key;
				min_ptr=x;
				minprev=prev1;
			}
			prev1 = x;
			x=x->sibling;
		}

		if(minprev==NULL)
		{
			root=min_ptr->sibling;
		}
		if(minprev!=NULL)
		{
			minprev->sibling=min_ptr->sibling;
		}

		
		min_child=min_ptr->left_child;

		node* q=min_child;

		//min_child stores all children of min_ptr
		//making their parent=NULL
		while(q!=NULL)
		{
			q->parent=NULL;
			q=q->sibling;
		}

		//to reverse the min_child
		node* prev   = NULL;
    	node* current = min_child;
    	node* next;
    	while (current != NULL)
    	{
    	    next  = current->sibling;  
    	    current->sibling = prev;   
    	    prev = current;
    	    current = next;
    	}


   		min_child = prev;
		node* y=min_child;
		
		//taking union with x if min_ptr has some children
		if(min_child!=NULL)
			uni(root,min_child);


	//	if(x==NULL && min_child==NULL)
	//		root=NULL;
		
		return min_ptr->key;

	}

//function to combine trees of same degree
	void combine(node* list)
	{
	    node *x,*prev_x,*next_x;
		x=list;
		prev_x=NULL;
		next_x=x->sibling;

		while(next_x!=NULL)
		{
			if(x->degree!=next_x->degree)
			{
				prev_x=x;
				x=next_x;
				next_x=next_x->sibling;
			}
			else if(next_x->sibling !=NULL && x->degree==next_x->degree && (next_x->sibling)->degree == x->degree)
			{
				prev_x=x;
				x=next_x;
				next_x=next_x->sibling;
			}
			else if(x->key <=next_x->key)
			{
				x->sibling=next_x->sibling;
				next_x->sibling=x->left_child;
				x->left_child=next_x;
				next_x->parent=x;
				next_x=x->sibling;
				x->degree=x->degree+1;
			}
			else if(x->key > next_x->key)
			{
				if(prev_x == NULL)
					root = next_x;
				else
				{
					prev_x->sibling = next_x;
				}
				x->sibling=next_x->left_child;
				next_x->left_child=x;
				x->parent=next_x;
				next_x->degree=next_x->degree+1;
				x=next_x;
				next_x=x->sibling;
			}

		}

	}	

	//sudo code for print funcion is given in assignment itself
	void print_recur(node* x,int depth)
	{
		if ( x != NULL )
		{
	    	if (x->sibling != NULL)
	        	print_recur( x->sibling, depth ) ; 
	    	
	    	if (x->parent == NULL)
	    		cout << endl ;    
	 
	    	if ( (x->left_child != NULL) || (x->parent == NULL) )
	    	{
	        	cout << setw(depth*6 + 4)<< x->key;
	        	if (x->left_child == NULL) 
	        		cout << "\n\n" ;
	    	}
	     	else
	     	{
	        	cout <<setw( 6 )<<x->key <<endl<<endl;  
	    	}
	    	if (x->left_child != NULL)
	        	print_recur( x->left_child, depth+1 ) ;  
	  	}

	}
	
	void print_format()
	{
		cout<<"Stucture of binomial heap (rotated 90 degrees ccwise):"<<endl;
		if(root == NULL)
		{
			cout<<"heap is already empty"<<endl;
			return;
		}
		else
			print_recur(root,0);

	}
};

int main()
{
	bheap heap;

	cout<<" c \t MAKE-BINOMIAL-HEAP"<<endl;
	cout<<" i \t BINOMIAL-HEAP-INSERT(i element_to_insert)\n"<<endl;
	cout<<" d \t BINOMIAL-HEAP-EXTRACT-MIN \n"<<endl;
	cout<<" s \t Display"<<endl;
	cout<<" + \t Turn off Print after extract min"<<endl;
	cout<<" - \t Turn on print after extract min "<<endl;
	cout<<" e \t EXIT"<<endl;

	int flag=0;
	cout<<"first call make binomial heap only so that operations like insert and extract min can be done"<<endl;
	while(1)
	{
		char c;
		cin>>c;
		switch(c)
		{

			case 'c':	
			{
				heap.make_bheap();
				break;
			}
			case 'i':
			{
				int n;
				cin>>n;
				heap.insert(n);
				break;
			}
			case 's':
			{
				heap.print_format();
				break;
			}
			case '-':
			{
				flag = 0;
				break;
			}
			case '+':
			{
				flag = 1;
				break;
			}

			case 'd':
			{
				int min_element = heap.extract_min();

				if(flag ==1)
				{
					if(min_element!=-1)
					cout<<"minimum element present in binomial heap is "<<min_element<<endl;
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
