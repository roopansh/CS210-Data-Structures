/************************************************************************************************
ROOPANSH BANSAL
150101053
CS210
************************************************************************************************/

/************************************************************************************************
(1.)For finding the path , i am visiting the neighbouring nodes(not the parent node) and marking them as visited by updating their value 
in the Visited array by 1.
(2.)If i reach the exit point , then i increase the number of paths by one.
(3.)If by anyother path i reach the exit node again , i again increase the number of paths by one.
(4.)To avoid any loops in the path , i am not visiting any node more than twice.
(5.)Hence , if i visit any node (which is in the path from entry to exit) more than once , there is definetly not a unique path.
(6.) If there are less than or more than 2 entry and exit points , it's a bad luck.
************************************************************************************************/

#include <bits/stdc++.h>

using namespace std;

//function prototypes
//Funciton to evaluate the path and check how many paths can exist
void Path(char **Jungle , int **Visited ,  int i , int j , int iPrev , int jPrev , int iEnter , int jEnter , int iExit , int jExit , int row , int col , int & NumOfPaths);

//note that this function is mainly for Debugging purpose
void MsgToDisplay(int x);// message to display on the screen based on 'x'

//Main Funciton
int main()
{
    int row,col,exit_points;
    while(true)
    {
		// input the number of rows , columns in the jungle 
        cout<<"Enter the number of Rows:\t";
        cin>>row;
        cout<<"Enter the number of Columns:\t";
        cin>>col;
        
        //exit condition
        if( row ==0 && col ==0) return 0;

        // jungle refers to the jungle inputted by the user
        char **Jungle ;
        // visited denotes the number of times we visit one node(land) of the jungle
        int **Visited;

        //allocating memory for the jungle and visited arrays
        // Jungle[1...row][1...col]
        // Visited[1...row][1...col]
        Jungle = new char*[row+1];
        Visited = new int*[row+1];
        for (int i = 1; i <= row; ++i)
        {
        	Jungle[i] = new char[col+1];
        	Visited[i] = new int[col+1];
        }

        //exit points refer to the number of 'lands' on the boundary of the jungle
        exit_points = 0;

        // these are the coordinates of the entry and exit points repectively
        int iEnter , jEnter , iExit , jExit;

        // input the jungle from the user
        cout<<"Enter the map.\t(Without spaces in between them)."<<endl;
        for(int i = 1; i <= row; i++)
        {
        	for (int j = 1; j <= col; ++j)
        	{
        		cin>>Jungle[i][j];
        		Visited[i][j] == 0;//initially every node is unvisited.

        		// for checking the boundary points
        		if (i == 1 || i == row || j == 1 || j == col)
        		{
        			if (Jungle[i][j]=='L')
        			{
        				exit_points++;
        				if (exit_points == 1)// Entry point
        				{
        					iEnter = i;jEnter = j;
        				}
        				if (exit_points == 2) // Exit POint
        				{
        					iExit = i;jExit = j;
        				}
        			}
        		}
        	}
        }

        // Exit points are not exactly two then it's bad luck 
        if (exit_points != 2)
        {
        	cout<<"Bad Luck!\t"<<endl;
       		// MsgToDisplay(1);// Display that there are not exactly two points
        	
        	// Continue to the next text case
        	continue;
        }

        //For Debugging Purpose
        // cout<<iEnter<<jEnter<<iExit<<jExit<<endl;

        // Initally Number Of Paths = 0
    	int NumOfPaths = 0;
    	// Calculate the number of paths from entry point to the exit point
    	Path(Jungle , Visited , iEnter , jEnter , 0 , 0 , iEnter , jEnter , iExit , jExit , row , col , NumOfPaths);


    	if(NumOfPaths > 1)
    	{
    		cout<<"Bad Luck!\t"<<endl;
       		// MsgToDisplay(2); // Unique path doesn't exist
        	continue;
    	}
    	else if (NumOfPaths < 1)
    	{
    		cout<<"Bad Luck!\t"<<endl;
       		// MsgToDisplay(3);// No path exist
        	continue;
    	}
    	else
    	{
    		cout<<"Submitted!\t"<<endl;
    		// MsgToDisplay(4);// Assignment can be submitted and unique path exists
    		continue;
    	}
    }
}

//Calculate the number of paths from entery point to the exit point
void Path(char **Jungle , int **Visited , int i , int j , int iPrev , int jPrev , int iEnter , int jEnter , int iExit , int jExit , int row , int col , int &NumOfPaths)
{
	// the number of times exit coordinate is reached , increase the number of paths by one
	if(i == iExit && j == jExit)
	{
		NumOfPaths++;
		// cout<<NumOfPaths<<endl;
		return ;
	}

	// Increase the number of times the current node is reached by one
	Visited[i][j]++ ;
	
	// if left point is in the domain of jungle 
	if (i-1 > 0)
	{
		if (i-1 == iPrev && j == jPrev) // the parent node
		{
			// return;
		}
		else if (Jungle[i-1][j] == 'T') // it's a dead end(i.e. it is a tree)
		{
			// return;
		}
		else if (Visited[i-1][j] == 2) // Don't visit any node more than 2 times.
		{
			 // return;
		}
		// if the left node is not the parent node of the current node AND it's not a tree AND it's not visited more than once , visit that node
		else
		{
			Path(Jungle , Visited , i-1 , j , i , j , iEnter , jEnter , iExit , jExit , row , col , NumOfPaths);
		}
	}

	// if right point is in the domain of jungle 
	if (i+1 <= row)
	{
		if (i+1 == iPrev && j == jPrev)// the parent node
		{
			// return;
		}
		else if (Jungle[i+1][j] == 'T')// it's a dead end(i.e. it is a tree)
		{
			// return;
		}
		else if (Visited[i+1][j] == 2)// Don't visit any node more than 2 times.
		{
			 // return;
		}
		// if the right node is not the parent node of the current node AND it's not a tree AND it's not visited more than once , visit that node
		else
		{
			Path(Jungle , Visited , i+1 , j , i , j , iEnter , jEnter , iExit , jExit , row , col , NumOfPaths);
		}
	}

	// if below point is in the domain of jungle 
	if (j-1 > 0)
	{
		if (i == iPrev && j-1 == jPrev)// the parent node
		{
			// return;
		}
		else if (Jungle[i][j-1] == 'T')// it's a dead end(i.e. it is a tree)
		{
			// return;
		}
		else if (Visited[i][j-1] == 2)// Don't visit any node more than 2 times.
		{
			 // return;
		}
		// if the below node is not the parent node of the current node AND it's not a tree AND it's not visited more than once , visit that node
		else
		{
			Path(Jungle , Visited , i , j-1 , i , j , iEnter , jEnter , iExit , jExit , row , col , NumOfPaths);
		}
	}

	// if above point is in the domain of jungle 
	if (j+1 <= col)
	{
		if (i == iPrev && j+1 == jPrev)// the parent node
		{
			// return;
		}
		else if (Jungle[i][j+1] == 'T')// it's a dead end(i.e. it is a tree)
		{
			// return;
		}
		else if (Visited[i][j+1] == 2)// Don't visit any node more than 2 times.
		{
			 // return;
		}
		// if the above node is not the parent node of the current node AND it's not a tree AND it's not visited more than once , visit that node
		else
		{
			Path(Jungle , Visited , i , j+1 , i , j , iEnter , jEnter , iExit , jExit , row , col , NumOfPaths);
		}
	}

	// cout<<NumOfPaths<<endl;
	
	return;
}

//MAINLY FOR DEBUGGING PURPOSE
// Messages to display on the screen
void MsgToDisplay(int x)
{
	cout<<"(";
	switch(x)
	{
		case 1:
			cout<<"Entry point + Exit point not exactly 2";
			break;
		case 2:
			cout<<"Entry point + Exit point exactly 2 BUT More than one path exists. No unique path";
			break;
		case 3:
			cout<<"Entry point + Exit point exactly 2 BUT No path exists";
			break;
		case 4:
			cout<<"Entry point + Exit point exactly 2 AND unique path exists";
			break;
		default:
			cout<<"Default Message"<<endl;
	}
	cout<<")."<<endl<<endl;
	return ;
}
