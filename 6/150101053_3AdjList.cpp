/************************************************************************************************
ROOPANSH BANSAL
150101053
CS210
************************************************************************************************/

/************************************************************************************************
Finding the minumu spannign tree of the given graph using prim's algorithm in O(V^2)
Note:  the graph is stored in the adjacency list form
************************************************************************************************/

#include <bits/stdc++.h>

using namespace std;

class Graph // Undirected Graph implemeted using adjacency list
{
private:
	int NumOfVertices; // for storing the number of the vertices
	std::vector<int> *Edges; // for storing the edges in adjacency list form
	int **Weight; // Weight[u][v] stores the weight of the edge between u and v

public:
	Graph(int n) // constructor
	:NumOfVertices(n)
	{
		Edges = new vector<int>[NumOfVertices+1];
		Weight = new int*[NumOfVertices+1];
		for (int i = 0; i <= NumOfVertices; ++i)
		{
			Weight[i] = new int[NumOfVertices+1];
		}
	}

	void InsertEdges(int u , int v , int w)// insert edge between vertex u and vertex v of wight w in the graph
	{
		Edges[u].push_back(v);
		Edges[v].push_back(u);
		Weight[u][v] = w;
		Weight[v][u] = w;
		// v appears in the adjacency list of the vertex u and vice versa
	}

	void MST_Prim() // for finding the minimum spannign tree using prim's algo
	{
		struct edge
		{
			int Vertex , Weight; // connected to vertex u with a weight of w
		};

		edge Key[NumOfVertices+1];
		
		int  Color[NumOfVertices+1], Count=0; 
		// Count stores the number of nodes added to the MST
		// Key[v] stores the minimum weight of the edge from the vertex 'v' to the MST.

		for (int i = 0; i <= NumOfVertices; ++i)
		{
			Key[i].Weight = INT_MAX; // initialising all the keys to infinity
			Color[i] = 0; // for color array :-
			// 0 represents that the vertex is not  added in the MST yet.
			//1 represents that the vertex has been included in the subset of MST
		}
		// taking node 1 as the root
		Key[1].Weight = 0;
		Key[1].Vertex = 0;

		cout<<endl<<"EDGES added to the MST_PRIM are in the following order :-"<<endl;
		while (Count < NumOfVertices)
		{
			// finding the minimum key by using simple linear search O(V)
			int u , v;
			int min = INT_MAX;
			for (int i = 1; i <=NumOfVertices; ++i)
			{
				// if the vertex is not yet added to the MST and the key is less than the current minimum found key
				if (Color[i] == 0 && Key[i].Weight < min)
				{
					min = Key[i].Weight; // update the minimum
					u = i;v=Key[i].Vertex; // store the vertex
				}
			}

			Color[u] = 1;// bcz the vertex is now included in the MST.
			cout<<Key[u].Vertex<<"  --->  "<<u<<endl;
			Count++;

			// traversing the edge list of the vertex u and updating the keys of those vertices
			for (int i = 0; i < Edges[u].size(); ++i)
			{
				int v= Edges[u].at(i);
				if (Color[v] == 0 && Weight[u][v] < Key[v].Weight)
				{
					Key[v].Weight = Weight[u][v];
					Key[v].Vertex = u;
				}
			}
		}
		cout<<endl<<endl;
	}			
};

int main(int argc, char const *argv[])
{
	int n , e;//for storing the number of nodes and edges
	cout<<"Enter the number of the vertices:\t";
	cin>>n;

	Graph G(n);// for the undirected graph
	
	cout<<"Enter the number of the edges:\t";
	cin>>e;

	int u , v , w;//for inputing the edges
	
	cout<<"Enter all the Edges"<<endl<<endl;
	cout<<"Should be in the format <FROM> <TO> <WIEGHT>"<<endl;
	cout<<"NOTE : The numbering of the vertices start from 1"<<endl;
	while(e--)
	{
		cin>>u>>v>>w;
		G.InsertEdges(u,v,w);
	}

	// Minimum spanning tree using the Prim's algo 
	G.MST_Prim();
	
	return 0;
}