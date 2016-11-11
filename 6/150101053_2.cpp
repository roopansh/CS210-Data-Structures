/************************************************************************************************
ROOPANSH BANSAL
150101053
CS210
************************************************************************************************/

/************************************************************************************************
Finding the SCC Graph in O(V+E)
1) DFS of the original graph in O(V+E)
2) Finding the Transpose of the graph again in O(V+E)
3) DFS of the transpose of the graph in O(V+E)... during this step, i am storing the Component to which the vertex belongs.
4) Traversing the adjacency list of the original graph and and forming the SCC Graph based on the Component to which that vertex belongs. (Not adding the Self loops during this step)
5) Finding the Parallel Edges in O(V+E) by using O(V) extra space.// check the implementation of the RemoveParallelEdge function of the Graph class.
************************************************************************************************/

#include <bits/stdc++.h>

using namespace std;

class Graph // Directed Graph implemeted using adjacency list
{
private:
	int NumOfVertices; // store the total number of vertices
	std::vector<int> *Edges; // dtore the edges in form of adjacency list
	int *DiscTime; // discovery time of the vertices for DFS
	int *FinTime; // finshing time of the vertices for DFS
	int *Colour;// 0 is white , 1 is gray , 2 is black
	stack <int> TopoSort; // storing the vertices in topological sorted manner
	int *SCC_ID; // SCC_ID[i] stores the strongly connected component in which the vertex i would appear

public:
	Graph(int n) // constructor 
	:NumOfVertices(n)
	{
		Edges = new vector<int>[NumOfVertices+1];
	}

	void InsertEdge(int u , int v) // insert edge from Vertex 'u' to vertex 'v'
	{
		Edges[u].push_back(v);
	}

	void initialise() // initialising the discovery time , finishing time , colour arrays before beginning with DFS
	{
		Colour = new int[NumOfVertices+1];
		DiscTime = new int[NumOfVertices+1];
		FinTime = new int[NumOfVertices+1];
		
		for (int i = 1; i <= NumOfVertices; ++i)
		{
			Colour[i] = 0;
			DiscTime[i] = 0;
			FinTime[i] = 0;
		}

		SCC_ID = new int[NumOfVertices+1];
	}

	Graph* Transpose() // return the transpose of the graph
	{
		Graph *temp = new Graph(NumOfVertices);
		
		// traverse through the complete adjacency list of the graph and store the opossite direction of the edge in the new graph
		for (int i = 1; i <= NumOfVertices; ++i)
		{
			for (int j = 0; j < Edges[i].size(); ++j)
			{
				temp->InsertEdge(Edges[i].at(j) , i);
			}
		}
		return temp;
	}

	void DFS()
	{
		initialise(); // initialising the discovery time , finishing time , colour arrays before beginning with DFS

		int time = 0;
		
		for (int i = 1; i <= NumOfVertices; ++i)
		{
			if (Colour[i] == 0) // the vertex is not visited yet
			{
				Colour[i] = 1;
				DFS_Visit(i , time );
			}
		}
	}

	void DFS_Visit(int u , int &time , int SCC_CompNo = 0)
	{
		Colour[u] = 1;

		if(SCC_CompNo > 0)	cout<<u<<" "; // output the vertex only when finding the SCC_ID's of the vertex and displaying on the screen
		
		DiscTime[u] = ++time;
		
		SCC_ID[u] = SCC_CompNo; // the vertex 'u' belongs to the strongly connected component-'SCC_CompNo'
		
		for (int i = 0; i < Edges[u].size(); ++i)
		{
			int v = Edges[u].at(i);
			if (Colour[v] == 0)
			{
				Colour[v]++;
				DFS_Visit(v , time , SCC_CompNo);
			}
		}

		Colour[u] = 2;
		FinTime[u] = ++time;
		TopoSort.push(u); // for storing the vertices in the topological sorted manner

	}

	Graph *SCC() // return the Strongly connected component graph
	{
		//DFS of original graph
		DFS();

		// find the transpose of the graph
		Graph *GT = Transpose();

		//DFS of the transpose in the order of decreasing finishing time of nodes(DFS of original graph)
		GT->initialise(); // initialise for the Transpose
		int time = 0;
		int SCC_Comp_Count = 0; // for storing the number of SCC Components found

		while(!TopoSort.empty())
		{
			int u = TopoSort.top();

			if(GT->Colour[u] == 0)
			{
				cout<<"Component #"<<SCC_Comp_Count+1<<" contains the following vertices of the original Graph:\t";
				GT->DFS_Visit(u , time , ++SCC_Comp_Count);
				cout<<endl;
			}
			TopoSort.pop();
		}

		// now we know which node of the GT graph is in which strongly connected component so build the SCC graph avoiding self loops and parallel edges
		Graph *SCC_Graph = new Graph(SCC_Comp_Count);

		for (int i = 1; i <= NumOfVertices; ++i)
		{
			for (int j = 0; j < Edges[i].size(); ++j)
			{
				int u = GT->SCC_ID[i]; // strongly connected component of the vertex 'i'
				int v = GT->SCC_ID[Edges[i].at(j)]; // strongly connected component of the vertex at position j in the adjacency list of the vertex 'i'
				if (u == v)//self loops in the SCC Graph are avoided
				{
					continue;
				}
				SCC_Graph->InsertEdge( u , v);
			}
		}

		//Note that the SCC still contains Parallel Edges
		SCC_Graph->RemoveParallelEdge();
		
		delete(GT);// we no longer require the Transpose of the graph...so free the memory

		return SCC_Graph;// return the strongly connected component graph
	}

	// Removing parallel edges in O(V+E) time using extra space of O(V)
	void RemoveParallelEdge()
	{
		// NOTE : if edgeMemo[u] = v , this means that there is an edge from the node v to node u
		int edgeMemo[NumOfVertices+1]={0};

		for (int u = 1; u < NumOfVertices; ++u)
		{
			for (vector<int>::iterator it = Edges[u].begin(); it != Edges[u].end(); ++it)
			{
				int v = *it;

				// if edgeMemo[v] == u , this means that we have alreasy found an edge from node u to node v....so the node v appears mutiple times in the adjacency list of u
				if (edgeMemo[v]==u)// duplicate edge found
				{
					Edges[u].erase(it--);
				}
				else
				{
					edgeMemo[v]=u; // updating the edgeMemo of node v to contain u..... once the adjacency list of node u is completed , it would still contain u.....so during the traversal of adjacency list of vertex u+1 , if there is a node from u+1 to v , edgeMemo[v] will become u+1 when the vertex v appears for the first time in the adjacency list of the vertex u+1....and so on for the other nodes after u+1.
				}
			}
		}

		// NOTE: the running time is the time requires to traverse the adjacency list of the graph , which is O(V+E)
	}

	void PrintAdjList()// print the adjacency list of the graph
	{
		for (int i = 1; i <= NumOfVertices; ++i)
		{
			cout<<i<<"  --->  ";
			for (int j = 0; j < Edges[i].size(); ++j)
			{
				int v = Edges[i].at(j);
				cout<<v<<"  ";
			}
			cout<<endl;
		}
	}
};

int main(int argc, char const *argv[])
{
	int n,e;// store the number of vertices and the edges
	cout<<"Enter the number of vertices:\t";
	cin>>n;
	Graph G(n);// declare a graph with n vertices
	cout<<"Enter the numebr of egdes:\t";
	cin>>e;
	int x, y;// to input the edges from the user
	cout<<"Enter the edges:\n";
	cout<<"NOTE : THE VERTEX NUMBERING STARTS FROM 1"<<endl;
	while(e--)
	{
		cin>>x>>y;
		G.InsertEdge(x,y);// insert the edge to the graph(adjacency list representation)
	}
	cout<<endl;

	// to find the Strongly connected graph of the Graph
	Graph *SCC_Graph = G.SCC();

	cout<<endl;
	
	// print the SCC Graph
	cout<<"Adjacency List of the STRNGLY CONNECTED COMPONENT GRAPH is :\n";
	SCC_Graph->PrintAdjList();

}