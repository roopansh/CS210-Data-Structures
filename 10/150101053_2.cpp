/************************************************************************************************
ROOPANSH BANSAL
150101053
CS210
************************************************************************************************/

/************************************************************************************************
Multiplying two polynomials of size m and n respectively.
************************************************************************************************/

#include <iostream>

using namespace std;

// structure of a term of the polynomial
struct PolyTerm
{
	int Coeffecient;// coeffecient of the term
	int Exponent;// power of the term
	PolyTerm *Next = NULL;// pointer to the next term of the polynomial
};

// class for storing the two polynomials as a singly linked list
class Polynomial
{
private:
	PolyTerm *Head;// pointer to the head of the polynomial

public:
	Polynomial(int n = 0)// constructor which will ask user to insert 'n' terms in the polynomial
	{
		Head = NULL;

		PolyTerm *temp;
		for (int i = 0; i < n; ++i)
		{
			temp = new PolyTerm;
			cout<<"Coeffecient: ";
			cin>>temp->Coeffecient;
			cout<<"Exponent: ";
			cin>>temp->Exponent;
			
			Insert(temp);
			temp = NULL;
		}
	}

	// insert the term to the polynomial
	void Insert(PolyTerm *Term)
	{
		Term->Next = Head;
		Head = Term;
	}

	PolyTerm *HeadTerm()
	{
		return Head;
	}
};

int main()
{
	int n,m;
	cout<<"Enter the Number of terms in FIRST polynomial:\t";
	cin>>n;
	cout<<"Enter the "<<n<<" terms of First Polynomial :\n";
	Polynomial Polynomial1(n);
	cout<<endl;
	cout<<"Enter the Number of terms in SECOND polynomial:\t";
	cin>>m;
	cout<<"Enter the "<<m<<" terms of Second Polynomial :\n";
	Polynomial Polynomial2(m);
	
	// we'll store the resulant polynomial in a Hash table of size m*n
	// collisions will be handeled by using linear probing
	
	int HashTableSize = m*n;
	PolyTerm ResultPolynomial[HashTableSize + 1];

	// initialising the has table
	// exponent = -1 means that that location is Empty
	for (int i = 0; i <= HashTableSize; ++i)
	{
		ResultPolynomial[i].Exponent = -1;
		ResultPolynomial[i].Coeffecient = 0;	
	}

	// term1 is for traversing polynomial1 and term2 for polynomial2
	PolyTerm *term1, *term2;
	int coeff, power, indexToInsert;

	term1 = Polynomial1.HeadTerm();
	while(term1 != NULL)
	{
		term2 = Polynomial2.HeadTerm();
		while(term2 != NULL)
		{
			power = term1->Exponent + term2->Exponent;
			coeff = term1->Coeffecient * term2->Coeffecient;
			indexToInsert = power % (HashTableSize+1);

			// isnerting the new term in it's right postion in the resultant polynomial
			while(ResultPolynomial[indexToInsert].Exponent != -1 && ResultPolynomial[indexToInsert].Exponent != power)
			{
				indexToInsert = (indexToInsert + 1) % (HashTableSize+1);
			}

			ResultPolynomial[indexToInsert].Coeffecient += coeff;
			ResultPolynomial[indexToInsert].Exponent = power;

			term2 = term2->Next;
		}
		term1 = term1->Next;
	}

	// printing the output
	cout<<"The Resultant Polynomial is : ";
	for (int i = 0; i < (HashTableSize+1); ++i)
	{
		if (ResultPolynomial[i].Exponent == -1)
		{
			continue;
		}
		cout<<ResultPolynomial[i].Coeffecient<<" X^"<<ResultPolynomial[i].Exponent<<" + ";
	}
	cout<<"0"<<endl;
	return 0;
}