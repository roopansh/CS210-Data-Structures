/************************************************************************************************
ROOPANSH BANSAL
150101053
CS210
************************************************************************************************/

/************************************************************************************************
Making a Database of the books using Binary Search Tree(Based on the ISBN number of the books).
************************************************************************************************/

#include <iostream>

using namespace std;

// Structure of a book to store all the required details
struct Book
{
	string title;
	string author;
	int year_of_publication;
	float cost;
	int number_of_copies_sold;
	unsigned long long ISBN;

	// the following pointers are used for Database
	Book *left = NULL;
	Book *right = NULL;
	Book *parent = NULL;
};

// Database of the books using the database Binary Search Tree
class BST
{
private:
	Book *Root;// root of the database
	long long int BookCount;// number of books in the database

public:
	BST()// constructor function
	{
		Root = NULL;
		BookCount = 0;
		Book *temp;
	}

	void InsertFirst5()// insert the first 5 harry potter book details in the database 
	{
		Book *temp;

		// Book # 1
		temp = NULL;
		temp = new Book;
		temp->title = "Harry Potter & The Philosopher's Stone";
		temp->author = "J. K. Rowling";
		temp->year_of_publication = 1997;
		temp->cost = 5001;
		temp->number_of_copies_sold = 10001;
		temp->ISBN = 9780439708180;
		InsertBook(temp);
		
		// Book # 2
		temp = NULL;
		temp = new Book;
		temp->title = "Harry Potter & The Chamber of Secrets";
		temp->author = "J. K. Rowling";
		temp->year_of_publication = 2000;
		temp->cost = 5002;
		temp->number_of_copies_sold = 10002;
		temp->ISBN = 9780439064873;
		InsertBook(temp);

		// Book # 3
		temp = NULL;
		temp = new Book;
		temp->title = "Harry Potter & The Prisoner of Azkaban";
		temp->author = "J. K. Rowling";
		temp->year_of_publication = 2001;
		temp->cost = 5003;
		temp->number_of_copies_sold = 10003;
		temp->ISBN = 9780439136365;
		InsertBook(temp);

		// Book # 4
		temp = NULL;
		temp = new Book;
		temp->title = "Harry Potter & The Goblet of Fire";
		temp->author = "J. K. Rowling";
		temp->year_of_publication = 2002;
		temp->cost = 5004;
		temp->number_of_copies_sold = 10004;
		temp->ISBN = 9780439139601;
		InsertBook(temp);

		// Book # 5
		temp = NULL;
		temp = new Book;
		temp->title = "Harry Potter & The Order of the Phoenix";
		temp->author = "J. K. Rowling";
		temp->year_of_publication = 2004;
		temp->cost = 5005;
		temp->number_of_copies_sold = 10005;
		temp->ISBN = 9780439358071;
		InsertBook(temp);

		temp = NULL;
	}

	Book *RootofClass()// return a pointer to the root of the database
	{
		return Root;
	}

	void InsertBook(Book *book)// insert a new book to the database
	{
		BookCount++;// increase the number of books in the database by one 

		if (Root == NULL)// database is empty yet
		{
			Root = book;
			return;
		}

		// find the appropriate position for storing the book in the database
		Book *ptr1 , *ptr2;
		ptr1 = Root;
		while(ptr1 != NULL)
		{
			ptr2 = ptr1;

			if (ptr1->ISBN < book->ISBN)
			{
				ptr1 = ptr1->right;
			}
			else
			{
				ptr1 = ptr1->left;
			}
		}

		// insert the book to that position
		if (ptr2->ISBN < book->ISBN)
		{
			ptr2->right = book;
		}
		else
		{
			ptr2->left = book;
		}
		book->parent = ptr2;

		return;

	}

	void Increase10(BST *& NewBookDB)// create a new database with the same books such that price of the books is increased by 10%
	{
		NewBookDB = new BST;// allocate memory to the new database
		NewBookDB->InsertBook10(Root);
	}

	void InsertBook10(Book * book)
	{
		// create a new book with the same details and price increased by 10%
		Book *temp = new Book;
		temp->title = book->title;
		temp->author = book->author;
		temp->year_of_publication = book->year_of_publication;
		temp->cost = (book->cost)*1.10;// price is multiplied by 1.10
		temp->number_of_copies_sold = book->number_of_copies_sold;
		temp->ISBN = book->ISBN;

		// insert the book to the database
		InsertBook(temp);
		// recursively add the books in the left subtree and then right subtree
		if (book->left != NULL)		InsertBook10(book->left);
		if (book->right != NULL)	InsertBook10(book->right);
	}

	void PrintBookDB(Book *book)// print the book database
	{
		if (book == NULL)
		{
			return;
		}
		// print the book title, ISBN, cost of the book
		cout<<"<"<<book->title<<",  "<<book->ISBN<<",  Rs. "<<book->cost<<">"<<endl;
		// recursively print the books details in the left and right subtrees
		PrintBookDB(book->left);
		PrintBookDB(book->right);
	}

	Book *FindCopiesSold()// returns a pointer to the book whose ISBN is given
	{
		// take the ISBN as the input
		cout<<endl<<"Please enter the ISBN of the book you want to find: ";
		unsigned long long int Book_ISBN;
		cin>>Book_ISBN;

		Book *bookPtr = Root;

		// find the book
		while(bookPtr != NULL)
		{
			// if the book is found, return the pointer to that book
			if (bookPtr->ISBN == Book_ISBN)
			{
				return bookPtr;
			}
			else if (bookPtr->ISBN < Book_ISBN)
			{
				bookPtr = bookPtr->right;
			}
			else
			{
				bookPtr = bookPtr->left;
			}
		}

		// if the book is not found, return a NULL pointer
		return NULL;
	}
};

void DisplayChoice()// display the choices available to the user
{
	cout<<"\n(1)Exit\n(2)Increase the Price of each book by 10%\n(3)Find the number of Copies Sold\n(4)Insert a New Book\n(5)Print the Books Database\n\n";
	return;
}

int main()// main function 
{
	BST *Book_DB = NULL;

	int choice;

	// first create a database with 5 books... proceed only if the database is created
	while(Book_DB == NULL)
	{
		cout<<"First Enter (1) to create a Book Database with 5 books initially.\n";
		cin>>choice;
		if (choice == 1)
		{
			Book_DB = new BST;// allocate memory for the new Books database
			Book_DB->InsertFirst5();// add the first 5 books to the database
			cout<<"Database initialised.\n\n";
		}
	}

	DisplayChoice();
	while(true)
	{
		cout<<"\n Now Enter choice: ";
		cin>>choice;	
		switch(choice)
		{
			case 1:// exit
			{
				return 0;
			}
			case 2:// increase the prices by 10%
			{
				BST *Book_DB_New = NULL;// create a pointer to the new database
				Book_DB->Increase10(Book_DB_New);
				// after the above fucntion returns, the Book_DB_New contains all the books with prices increased by 10%
				delete(Book_DB);// dlete the original database
				Book_DB = Book_DB_New;// replace the original databse by the new database 
				cout<<"Price of each Book Increased by 10%";
				break;
			}
			case 3:// copies sold
			{
				Book *book = Book_DB->FindCopiesSold();// pointer to the require book
				cout<<endl;
				if (book != NULL)
				{
					cout<<"Number of copies Sold of  '"<<book->title<<"'  are  '"<<book->number_of_copies_sold<<"'."<<endl;
				}
				else
				{
					cout<<"Book not found in the Database"<<endl;
				}
				break;
			}
			case 4:// Insert a new Book
			{
				// input the details of the book from the user
				cout<<"Enter the Book Details"<<endl;
				cout<<"Title:\t";
				string title;
				cin.ignore();
				getline(cin,title);
				cout<<"Author:\t";
				string author;
				cin.ignore();
				getline(cin,author);
				cout<<"Year of Publication:\t";
				int year_of_publication;
				cin>>year_of_publication;
				cout<<"Cost:\t";
				float cost;
				cin>>cost;
				cout<<"Number of Copies Sold:\t";
				int number_of_copies_sold;
				cin>>number_of_copies_sold;
				cout<<"ISBN:\t";
				unsigned long long ISBN;
				cin>>ISBN;

				// create a new book structure with the given details
				Book *NewBookToInsert = new Book;
				NewBookToInsert->title = title;
				NewBookToInsert->author=author;
				NewBookToInsert->year_of_publication=year_of_publication;
				NewBookToInsert->cost=cost;
				NewBookToInsert->number_of_copies_sold=number_of_copies_sold;
				NewBookToInsert->ISBN=ISBN;

				// insert the book to the database
				Book_DB->InsertBook(NewBookToInsert);
				break;
			}
			case 5:// print the entire books database
			{
				Book_DB->PrintBookDB(Book_DB->RootofClass());
				break;
			}
			default:
			{
				cout<<"Please enter a valid choice.\n\n";
				break;
			}

		}
	}
}