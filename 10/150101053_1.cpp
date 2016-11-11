#include <iostream>
#include <stdlib.h>

using namespace std;

// -1 represents empty and -2 represents deleted in hash tables
void Initialise(int m, int LinearProbing[], int QuadraticProbing[], int DoubleHashing[])
{
	for (int i = 0; i < m; ++i)
	{
		LinearProbing[i] = -1;
		QuadraticProbing[i] = -1;
		DoubleHashing[i] = -1;
	}
}

void Delete(int x, int m, int LinearProbing[], int QuadraticProbing[], int DoubleHashing[])
{
	int hash = (x%m);

	// Linear Hashing - Insert
	int i = hash;
	while(LinearProbing[i] != -1 && LinearProbing[i] != x)
	{
		i++;
		i %= m;
	}
	if (i < m)
	{
		LinearProbing[i] = -2;
		cout<<"In Linear Probing, the value "<<x<<" is deleted from the index "<<i<<" of the table.\n";
	}
	else
	{
		cout<<x<<" not found in the table.\n";
	}

	// Quadratic Hashing - Insert
	int j = 0;
	int hashQuad = (hash + 1*j + 3*j*j)%m;
	while(QuadraticProbing[hashQuad] != -1 && QuadraticProbing[hashQuad] != x && j < m)
	{
		j++;
		hashQuad = (hash + 1*j + 3*j*j)%m;
	}
	if (j < m)
	{
		QuadraticProbing[hashQuad] = -2;
		cout<<"In Quadratic Probing, the value "<<x<<" is deleted from the index "<<hashQuad<<" of the table.\n";
	}
	else
	{
		cout<<x<<" not found in the table.\n";
	}

	// Double Hashing - Insert
	int hash2 = 1 + (x%(m-1)); // 1 + (k mod (m - 1))
	int k = 0;
	int hashDouble = (hash + k*hash2)%m;
	while(DoubleHashing[hashDouble] != -1 && DoubleHashing[hashDouble] != x && k<m)
	{
		k++;
		hashDouble = (hash + k*hash2)%m;
	}
	if (k < m)
	{
		DoubleHashing[hashDouble] = -2;
		cout<<"In Double Hashing, the value "<<x<<" is deleted from the index "<<hashDouble<<" of the table.\n";
	}
	else
	{
		cout<<x<<" not found in the table.\n";
	}

	return;
	
}

void Insert(int x, int m, int LinearProbing[], int QuadraticProbing[], int DoubleHashing[], int &LinCol, int &QuadCol, int &DoubCol)
{
	int hash = (x%m);

	// Linear Hashing - Insert
	int i = hash;
	while(LinearProbing[i] != -1 && LinearProbing[i] != -2)
	{
		i++;
		i %= m;
		LinCol++;
	}
	if (i < m)
	{
		LinearProbing[i] = x;
		cout<<"In Linear Probing, the value "<<x<<" is stored in the index "<<i<<" of the table.\n";
	}
	else
	{
		cout<<"All the possible positions for the Linear Probing are full. Can't Insert "<<x<<" into the table.\n";
	}

	// Quadratic Hashing - Insert
	int j = 0;
	int hashQuad = (hash + 1*j + 3*j*j)%m;
	while(QuadraticProbing[hashQuad] != -1 && QuadraticProbing[hashQuad] != -2 && j < m)
	{
		j++;
		QuadCol++;
		hashQuad = (hash + 1*j + 3*j*j)%m;
	}
	if (j < m)
	{
		QuadraticProbing[hashQuad] = x;
		cout<<"In Quadratic Probing, the value "<<x<<" is stored in the index "<<hashQuad<<" of the table.\n";
	}
	else
	{
		cout<<"All the possible positions for the Quadratic Probing are full. Can't Insert "<<x<<" into the table.\n";
	}

	// Double Hashing - Insert
	int hash2 = 1 + (x%(m-1)); // 1 + (k mod (m - 1))
	int k = 0;
	int hashDouble = (hash + k*hash2)%m;
	while(DoubleHashing[hashDouble] != -1 && DoubleHashing[hashDouble] != -2 && k<m)
	{
		k++;
		DoubCol++;
		hashDouble = (hash + k*hash2)%m;
	}
	if (k < m)
	{
		DoubleHashing[hashDouble] = x;
		cout<<"In Double Hashing, the value "<<x<<" is stored in the index "<<hashDouble<<" of the table.\n";
	}
	else
	{
		cout<<"All the possible positions for the Double Hashing are full. Can't Insert "<<x<<" into the table.\n";
	}

	return;
}

int main()
{
	srand(time(NULL));
	int m;
	cout<<"Enter the value of m : ";
	cin>>m;
	int LinearProbing[m], QuadraticProbing[m], DoubleHashing[m];
	Initialise(m, LinearProbing, QuadraticProbing, DoubleHashing);
	int size = 0, LinCol = 0, QuadCol = 0, DoubCol = 0;
	cout<<"(0)\tPRINT COLLISSIONS\n(1)\tINSERT\n(2)\tDELETE\n(3)\tINSERT 'n' RANDOM ELEMENTS\n(4)\tPRINT THE TABLES\n(5)\tEXIT\n";
	int ch;
	while(true)
	{
		cout<<endl;
		cin>>ch;
		switch(ch)
		{
			case 0:// PRINT COLLISIONS
			{
				cout<<"Total Number Of Collisions in various Hash tables were : \nLinear Hashing\t\t"<<LinCol<<"\nQuadratic Hashing\t"<<QuadCol<<"\nDouble Hashing\t\t"<<DoubCol<<"\n";
				break;
			}
			case 1:// insert
			{
				if(size == m)
				{
					cout<<"ERROR : Can't Insert. All hash tables are full.\n";
					continue;
				}
				int x;
				cout<<"Enter element to insert: ";
				cin>>x;
				Insert(x, m, LinearProbing, QuadraticProbing, DoubleHashing, LinCol, QuadCol, DoubCol);
				size++;
				break;
			}
			case 2:// delete
			{
				if (size == 0)
				{
					cout<<"ERROR : The Hash tables are already empty\n";
					continue;
				}
				int x;
				cout<<"Enter element to Delete : ";
				cin>>x;
				Delete(x, m, LinearProbing, QuadraticProbing, DoubleHashing);
				size--;
				break;
			}
			case 3:// insert random elements
			{
				int n;
				cout<<"How many random elements to insert: ";
				cin>>n;
				int count = 0;
				int x;
				while (count < n)
				{
					if(size == m)
					{
						cout<<"ERROR : Can't Insert Any more. All hash tables are full.\n";
						break;
					}
					x = rand() % 1000;
					Insert(x, m, LinearProbing, QuadraticProbing, DoubleHashing, LinCol, QuadCol, DoubCol);
					cout<<endl;
					size++;
					count++;
				}
				break;
			}
			case 4:// print the tables
			{
				cout<<endl<<"  ::  Linear Probing Hash Table  ::"<<endl<<"\t";
				for(int i=0; i<m; i++)
				{
					cout<<LinearProbing[i]<<"  ";
				}
				cout<<endl<<endl<<"  ::  Quadratic Probing Hash Table  ::"<<endl<<"\t";
				for(int i=0; i<m; i++)
				{
					cout<<QuadraticProbing[i]<<"  ";
				}
				cout<<endl<<endl<<"  ::  Double Hashing Hash Table  ::"<<endl<<"\t";
				for(int i=0; i<m; i++)
				{
					cout<<DoubleHashing[i]<<"  ";
				}
				break;
			}
			case 5:// exit
			{
				return 0;
			}
			default :
			{
				cout<<"Please Enter a Valid Choice."<<endl;
				break;
			}
		}
	}

}