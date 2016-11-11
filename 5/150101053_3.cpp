/************************************************************************************************
ROOPANSH BANSAL
150101053
CS210
************************************************************************************************/

/************************************************************************************************
find the type of the edge in the directed graph given.
graph is stored in the form of adjacence list.
************************************************************************************************/

#include <bits/stdc++.h>

using namespace std;

// Directed graph class
class Graph
{
private:
	int NumOfVertex;// stores the number of vertices in the graph
	vector<int> *Vertex;// storing the vertices in the form of adjacency list by using the vectors of c++
	int *Parent;// -1 represents NULL Parent
	int *Color;// 0 represents white , 1 represents gray and 2 represents black
	int Timer;
	int *Timer1;// discovery time
	int *Timer2;// finishing time
	struct EdgeType
	{
		int u , v;
		int Type;
		// 1 = Tree Edge
		// 2 = Forward Edge
		// 3 = Back Edge
		// 4 = Cross Edge 
	};
	vector<EdgeType> TypeOfEdge;// vector for storing all the edge types
public:
	Graph(int V);// constructor
	void InitialiseForSearch();// setting the colour of all the nodes to white and the timers to nil...basically preparing the arays for the DFS
	void InsertEdgeDirected(int u , int v);// insert an directed edge
	void DFS();
	void DFS_Visit(int v);
	EdgeType * CreateEdgeType(int u , int v , int x);// creating a structure for storing the edge type
	void PrintEdgeType();
};

int main(int argc, char const *argv[])
{
	int n ,e ;
	cout<<"Enter the number of the Vertices:\t";
	cin>>n;
	Graph dirGraph(n);
	cout<<"Enter the number of edges(Directed):\t";
	cin>>e;
	cout<<"Enter the edges\t(NODES NUMBERING STARTS FROM 1):\n";
	while(e--)
	{
		int u , v;
		cin>>u>>v;
		dirGraph.InsertEdgeDirected( u , v );
	}

	// perform dfs....during dfs, different types of the edges are stored accordingly
	dirGraph.DFS();

	// print those edge types
	dirGraph.PrintEdgeType();

	return 0;
}

// constructor
Graph::Graph(int V)
:NumOfVertex(V)
{
	Vertex = new vector<int>[NumOfVertex+1];
	InitialiseForSearch();
}

// setting the colour of all the nodes to white and the timers to nil...basically preparing the arays for the DFS
void Graph::InitialiseForSearch()
{
	Color = new int[NumOfVertex+1];
	Parent = new int[NumOfVertex+1];
	Timer1 = new int [NumOfVertex+1];
	Timer2 = new int[NumOfVertex+1];
	Timer =0;
	for(int v =1 ; v<= NumOfVertex ; v++)
	{
		Color[v] = 0;
		Parent[v] = -1;
		Timer1[v] = -1;
		Timer2[v] = -1;
	}

}

// insert an directed edge
void Graph::InsertEdgeDirected(int u , int v)
{
	Vertex[u].push_back(v);
}

void Graph::DFS()
{
	InitialiseForSearch();
	cout<<endl<<"\t\tNOTE:\tROOT OF DFS = NODE 1"<<endl<<endl;
	for (int v = 1; v <= NumOfVertex; ++v)
	{
		if (Color[v] == 0)
		{
			DFS_Visit(v);
		}
	}
}

void Graph::DFS_Visit(int u)
{
	Color[u] = 1;// represents gray color
	Timer++;
	Timer1[u] = Timer;
	for (int i = 0; i < Vertex[u].size(); ++i)
	{
		int v = Vertex[u].at(i);
		if (Color[v] == 0) //tree edge
		{
			Parent[v] = u;
			DFS_Visit(v);
			TypeOfEdge.push_back(*CreateEdgeType(u , v , 1));// store this tree edge found from u to v
		}
		else if (Color[v] == 1)//back edge
		{
			TypeOfEdge.push_back(*CreateEdgeType(u , v , 3));// store this back edge found from u to v
		}
		else if (Color[v] == 2)
		{
			//check whether it is a forward edge or a cross edge
			if (Timer1[v] > Timer1[u])// Forward Edge
			{
				TypeOfEdge.push_back(*CreateEdgeType(u , v , 2));// store this forward edge found from u to v
			}
			else
			{
				TypeOfEdge.push_back(*CreateEdgeType(u , v , 4 ));// store this cross edge found from u to v
			}
		}
	}
	Color[u] = 2;// represents black color
	Timer++;
	Timer2[u] = Timer;
}

// creating a structure for storing the edge type
Graph::EdgeType * Graph::CreateEdgeType(int u , int v , int x)
{
	EdgeType * temp = new EdgeType;
	temp->u=u;
	temp->v=v;
	temp->Type=x;
	// 1 = Tree Edge
	// 2 = Forward Edge
	// 3 = Back Edge
	// 4 = Cross Edge
	return temp;
}

void Graph::PrintEdgeType()
{
	for(int i = 0 ; i < TypeOfEdge.size() ;i++)
	{
		EdgeType *Edge = &TypeOfEdge.at(i);
		cout<<Edge->u<<"--->"<<Edge->v<<" is a\t";
		switch(Edge->Type)
		{
		case 1:
			cout<<"Tree Edge";
			break;
		case 2:
			cout<<"Forward Edge";
			break;
		case 3:
			cout<<"Back Edge";
			break;
		case 4:
			cout<<"Cross Edge";
			break;
		}
		cout<<"."<<endl;
	}
}