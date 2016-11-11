#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

//Funciton Prototypes
void Arr_Initalise(int *arr , int n);
void random_gen(int *arr , int n);
void Algo_Implement(int *arr , int n);
void PART_A(int *arr , int n);
void PART_B(int *arr , int n);
void Print_Arr(int *arr , int n);
void Print_Span(int *X , int *S , int n);


//Stack implementation
// for part- B of the question
class Stack
{
private:
	int *arr;//array to store the integers
	int top;//top is the index of the top element of the stack
	int Size;// size of the stack
public:
	Stack(int n=100)
	:Size(n)	// initialise size to n
	{
		arr = new int[Size];//allocate memory for th earray
		top = -1;// initialise top to -1
	}

	//check if the stack is empty
	bool isEmpty()
	{
		if(top == -1)
			return true;
		else
			return false;
	}

	//push in the stack
	void Push(int x)
	{
		if(top == Size-1)
		{
			//Overflow error message
			//Error_Display(1);
			return ;
		}
		// increase top by one and input the element
		arr[++top] = x;
	}

	//pop the top element
	void Pop()
	{
		if(isEmpty())
		{
			//Underflow Error message
			//Error_Display(0);
			return ;
		}
		// simply decrease top by one
		top--;
	}

	//return the top element
	int Top()
	{
		if(isEmpty())
		{
			//Underflow Error message
			//Error_Display(0);
			// top = -1 means the stack is empty
			return -1;
		}
		// return the top element of the stack
		return arr[top];
	}

	//To display errors on the console
	//Display error message
	// err = 0 ==> Underflow
	// err = 1 ==> Overflow
	void Error_Display(int err)
	{
		cout<<endl<<"ERROR\t:\t";
		switch(err)
		{
			case 0://Underflow
			cout<<"UNDERFLOW"<<endl;
			break;

			case 1://Overflow
			cout<<"OVERFLOW"<<endl;
			break;
			
			default:
			cout<<endl;
			break;
		}
	}
};


//Main Funciton
int main()
{
	int n;
	cout<<"Enter the size of the array:\t";
	cin>>n;
	
	//Declare the array to store the input
	int X[n];
	
	//To initialise the array
	Arr_Initalise(X , n);

	//Function to call for PART - A and PART B of the question
	Algo_Implement(X , n);

	return 0;
}

//To select whether to generate array randomply or input from user
void Arr_Initalise(int *arr , int n)
{
	int choice;
	cout<<"Enter (0) to initialise the array randomly or press (1) to input the array:\t";
	cin>>choice;
	
	switch(choice)
	{
		//randomly generate the array 
		case 0:
		random_gen(arr , n);
		cout<<"Array generated is :-\n";
		Print_Arr(arr , n);
		break;

		//input the array from the user
		case 1:
		cout<<"Enter the Elements:\n";
		for(int i=0;i<n;i++)
		{
			cin>>arr[i];
		}
		break;

		default:
		cout<<"WRONG INPUT\tPLEASE TRY AGAIN"<<endl;
		Arr_Initalise(arr , n);
		break;
	}
	return ;
}


//Function to generate a array(size n) of random numbers in range of 0 to 1000
void random_gen(int *arr , int n)
{
	//Seed the random Fucntion 
	srand(time(0));

	// generate array of random integers
	for(int i=0;i<n;i++)
	{
		arr[i] = rand()%1001;
	}

	return ;
}


//To check with which implementation to run
// Either O(n^2) or O(n)
void Algo_Implement(int *arr , int n)
{
	int choice;
	cout<<endl<<"How to implement?"<<endl<<"PRESS (0) for O(n^2) ALGO OR (1) FOR O(N) ALGO"<<endl;
	cin>>choice;
	switch(choice)
	{
		case 0:
		//Calling function for part A. O(n^2) algorithm
		PART_A(arr , n);
		break;

		case 1:
		//Calling function for part B. O(n) algorithm
		PART_B(arr , n);
		break;

		default:
		cout<<"WRONG INPUT\tPLEASE TRY AGAIN"<<endl;
		Algo_Implement(arr , n);
		break;
	}
	return ;
}

//O(n^2) implementation 
void PART_A(int *arr , int n)
{
	//to store the span
	int S[n];

	// Traverse the array in backward direction starting from i and compare the elements to calculate the span of the i-th element
	for(int i=0;i<n;i++)
	{
		int j = i;
		S[i] = 0;
		while(j>=0 && arr[j] <= arr[i])
		{
			S[i]++;
			j--;
		}
	}

	//Print the span of the array 
	Print_Span(arr , S , n);
	return ;
}

//O(n) implementation 
// It's O(n) because every element will be pushed into and poped out of the stack only one.
// Push and pop takes O(1) time
// Hence for n elements of the array , the maintainence of stack takes O(2n) = O(n) time
void PART_B(int *arr , int n)
{
	//to store the span
	int Span[n];

	// to implement using stack
	Stack X(n);

	// for each element in the array
	for(int i=0;i<n;i++)
	{
		// if stack is empty , simply push the element
		// span of hat element is i+1
		if(X.isEmpty())
		{
			Span[i] = i + 1;
			X.Push(i);
		}
		else
		{
			//pop the stack while the stack's top element is less than the e
			while(!X.isEmpty() && arr[X.Top()] <= arr[i])
			{
				X.Pop();
			}

			Span[i] = i - X.Top();
			// cout<<"Span[i] = \t"<<Span[i]<<endl;
			X.Push(i);
		}
	}
	Print_Span(arr , Span , n);
	return ;
}

//Print the aray of size n
void Print_Arr(int *arr , int n)
{
	for(int i=0;i<n;i++)
	{
		cout<<arr[i]<<"\t";
	}
	cout<<endl;
	return ;
}

//print the span along with the array
void Print_Span(int *X , int *S , int n)
{
	for(int i=0;i<n;i++)
	{
		cout<<"SPAN OF\tX["<<i+1<<"] = "<<X[i]<<" is \t "<<S[i]<<endl;
	}
	cout<<endl;
	return ;
}
