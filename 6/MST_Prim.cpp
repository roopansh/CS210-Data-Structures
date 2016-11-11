#include <bits/stdc++.h>

using namespace std;

class Priority_Queue
{
	int NumNode;// storing the number of nodes in the heap
	int *Node;// heap in array form
	int *Location;// storing the index of nodes
public:
	Priority_Queue(int n)
	:NumNode(n)
	{
		Node = new int[NumNode+1];
		Location = new int[NumNode+1];
		for (int i = 1; i <= NumNode; ++i)
		{
			Node[i] = INT_MAX;
			Location[i]=i;
		}
		Node[1] = 0;
		Location[1] = 1;// index of node 1 is 1
	}
	bool Empty()// returns true if the queue is empty
	{
		if (NumNode == 0)	return true;
		else	return false
	}
	void Heapify(int index)
	{
		int left = index << 1 ;// left child = 2*index
		int right = left +1;
		int largest = index;
		if (left < NumNode & Node[index] < Node[left])	largest = left;
		if (right < NumNode & Node[largest] < Node[right])	largest = right;
		if (largest != index)
		{
			
			Heapify(largest);
		}
	}
	int Extract_Min()
	{

	}
	void Decrease_key(int Vertex , int NewKey)
	{

	}

};

class Graph
{
	int NumOfVertices; 
	std::vector<int> *Edges;
	int **Weight;
public:
	Graph(int n)
	:NumOfVertices(n)
	{
		Edges = new vector<int>[NumOfVertices+1];
		Weight = new *int[NumNode+1];
		for (int i = 0; i <= NumNode; ++i)
		{
			Weight[i] = new int[NumNode+1];
		}
	}
	void InsertEdges(int u , int v , int w)// insert edge from vertex u to vertex v of wight w in the graph
	{
		Edges[u].push_back(v);
		Weight[u][v] = w;
	}
	void MST_Prim()
	{
		int Key[NumNode+1] /*, Parent[NumNode+1]*/ , Color[NumNode+1];
		for (int i = 0; i <= NumNode; ++i)
		{
			Key[i] = INT_MAX;
			// Parent[i] = 0;// 0 represents nill parent
			Color[i] = 0;// 0 represents that the vertex is not in the Subset of the MST yet.//1 represents that the vertex has been included in the subset of MST
		}
		// taking node 1 as the root
		Key[1] = 0;
		Priority_Queue Q(NumNode);// for storing the keys of the nodes of the graph
		cout<<"Nodes Visited in the MST_Prim are in order:"
		while (!Q.Empty())
		{
			int u = Q.Extract_Min();
			Color[u] = 1;// bcz the vertex is now included in the MST.
			cout<<"\t"<<u;
			for (int i = 0; i < Edges[u].size(); ++i)
			{
				int v= Edges[u].at(i);
				if (Color[v] == 0 && Weight[u][v] < Key[v])
				{
					// Parent[v] = u;
					Key[v] = Weight[u][v];
					Q.Decrease_key(v , Weight[u][v]);
				}
			}
		}
	}			
};

int main(int argc, char const *argv[])
{
	int n , e;//for storing the number of nodes and edges
	cout<<"Enter the number of the vertices:\t";
	cin>>n;
	Graph G(n);// for the original graph
	cout<<"Enter the number of the edges:\t";
	cin>>e;
	int u , v;//for inputing the edges
	while(e--)
	{
		cin>>u>>v;
		G.InsertEdges(u,v);
	}
	G.MST_Prim();
	return 0;
}