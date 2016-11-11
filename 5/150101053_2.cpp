/************************************************************************************************
ROOPANSH BANSAL
150101053
CS210
************************************************************************************************/

/************************************************************************************************
Print the matrix which shows if there is a path from node u to node v.
Graph is stored in the form of adjacency list.
************************************************************************************************/

#include <bits/stdc++.h>

using namespace std;

// Directed graph class
class Graph
{
private:
	int NumOfVertex;// stores the number of vertices in the graph
	vector<int> *Vertex;// storing the vertices in the form of adjacency list by using the vectors of c++
	int *Color;// 0 represents white , 1 represents gray and 2 represents black
	int **PathMatrix;// is the 2D array which stores if there is a path from node u to node v
public:
	Graph(int V);// constructor
	void InitialiseForSearch();// setting the colour of all the nodes to white
	void InsertEdgeDirected(int u , int v);// insert an directed edge
	void BuildPathMatrix();// generating the path matrix 
	void Print_PathMatrix();// printing the path matrix generated in the above function
	bool PathCheck(int u , int v);// check if there is a path from node u to node v (uses BFS)
};

int main(int argc, char const *argv[])
{
	// take the number of vertices as input from user
	cout<<"Enter The number of the Vertices:\t";
	int n;
	cin>>n;

	//initalise an object of class graph 
	Graph DirGraph(n);

	// take the edges as input from the user
	cout<<"Enter the Number of Edges:\t";
	int e;
	cin>>e;
	cout<<"Enter the Edges.\t(NODES NUMBERING STARTS FROM 1):\n";
	while(e--)
	{
		int u , v;
		cin>>u>>v;
		DirGraph.InsertEdgeDirected(u,v);
	}

	// print the math matrix representing the path between two vertices
	DirGraph.Print_PathMatrix();
	return 0;
}

// constructor of graph
Graph::Graph(int V)
:NumOfVertex(V)
{
	Vertex = new vector<int>[NumOfVertex+1];
	PathMatrix = new int*[NumOfVertex+1];
	for(int i=1;i<=NumOfVertex;i++)
	{
		PathMatrix[i] = new int[NumOfVertex+1];
	}
	InitialiseForSearch();
}

// setting the colour of all the nodes to white
void Graph::InitialiseForSearch()
{
	// allocating memory for the colour array of the graph and setting all of them to white
	Color = new int[NumOfVertex+1];
	for(int v =1 ; v<= NumOfVertex ; v++)
	{
		Color[v] = 0;
	}
}

// insert an directed edge
void Graph::InsertEdgeDirected(int u , int v)
{
	Vertex[u].push_back(v);
}

// generating the path matrix
void Graph::BuildPathMatrix()
{
	// find if there is a path from i to j for every entry of the matrix
	for (int i = 1; i <= NumOfVertex; ++i)
	{
		for (int j = 1; j <= NumOfVertex; ++j)
		{
			// if there is a path from vertex i to vertex j then represent it as a 1 in the Path-Matrix otherwise as 0.
			if(PathCheck(i , j))
				PathMatrix[i][j] = 1;
			else
				PathMatrix[i][j] = 0;
		}
	}
}

// printing the path matrix generated in the above function
void Graph::Print_PathMatrix()
{
	// first build the matrix
	BuildPathMatrix();


	// then print the matrix in a readable manner
	cout<<"VERTEX\t";
	for (int i = 1; i <= NumOfVertex; ++i)
	{
		cout<<" | "<<i;
	}
	cout<<endl;
	for(int i=1;i<=NumOfVertex;i++)
	{
		cout<<"  "<<i<<"\t";
		for(int j=1;j<=NumOfVertex;j++)
		{
			cout<<" | "<<PathMatrix[i][j];
		}
		cout<<endl;
	}

	cout<<endl<<endl<<"NOTE\t:\t1 REPRESENTS THAT THERE IS A PATH FROM LEFT VERTEX TO ABOVE VERTEX AND 0 REPRESENTS THAT THERE IS NO PATH."<<endl<<endl;
}

// check if there is a path from node u to node v (uses BFS)
bool Graph::PathCheck(int u , int v)
{
	// set the colour of all the vertices to white initially
	InitialiseForSearch();
	// initialise an empty queue
	queue<int> Q;
	// apply bfs with the node 'u' as the root
	Q.push(u);
	Color[u] = 1;
	while(!Q.empty())
	{
		int Node = Q.front();
		Q.pop();
		// if we find the node v then there exists a path from node u to node v
		for(int i=0;i< Vertex[Node].size();i++)
		{
			int temp = Vertex[Node].at(i);
			if(temp == v)// there exists a path from node u to node v
			{
				delete(Color);// free the memory used by the colour array 
				return true;
			}
			if(Color[temp] == 0)
			{
				Q.push(temp);
				Color[temp] = 1;
			}
		}
	}
	delete(Color);// free the memory used by the colour array
	return false;
}