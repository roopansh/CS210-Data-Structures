// perform dfs
// have a topological sort
// DFS - transpose of the graph in decreasing topological sort 

#include <bits/stdc++.h>
using namespace std;
class Graph
{
	int numOfVertexes;
	std::vector<int> *Edge;
	int *colour;//white = 0;gray = 1;black = 2;
	std::vector<int> *SCC;
	int SCCcount;
public:
	Graph(int n)
	:numOfVertexes(n)
	{
		Edge = new vector<int>[numOfVertexes+1];
		colour = new int[numOfVertexes+1];
		SCC = new vector<int>[numOfVertexes+1];
	}
	void insertEdge(int u , int v)
	{
		Edge[u].push_back(v);
	}
	void initialise()
	{
		for (int i = 0; i <= numOfVertexes; ++i)
		{
			colour[i] = 0; 
		}
	}
	void topologicalSort(int *arr)
	{
		initialise();
		for (int i = 1; i <= numOfVertexes; ++i)
		{
			if (colour[i] == 0)
			{
				colour[i]++;
				DFS_Visit(i, arr);
			}
		}
	}
	void DFS_Visit(int u ,int *arr)
	{
		static int key = numOfVertexes;
		for (int i = 0; i < Edge[u].size(); ++i)
		{
			int v = Edge[u].at(i);
			if (colour[v] == 0)
			{
				colour[v]++;
				DFS_Visit(v,arr);
			}
		}
		colour[u]++;
		arr[--key] = u;
	}
	void customDFS(int *order)
	{
		initialise();
		int u;
		SCCcount = 0;
		for (int i = 0; i < numOfVertexes; ++i)
		{
			u = order[i];
			if (colour[u] == 0)
			{
				colour[u]++;
				DFS_Visit(u , SCCcount++);
			}
		}
	}
	void DFS_Visit(int u , int count)
	{
		SCC[count].push_back(u);
		for (int i = 0; i < Edge[u].size(); ++i)
		{
			int v = Edge[u].at(i);
			if (colour[v] == 0)
			{
				colour[v]++;
				DFS_Visit(v, count);
			}
		}
		colour[u]++;
	}
	void printSCC()
	{
		for (int i = 0; i < SCCcount; ++i)
		{
			// cout<<SCC[i];
			for (int j = 0; j < SCC[i].size(); ++j)
			{
				cout<<SCC[i].at(j)<<" ";
			}
			cout<<endl;
		}
	}
};
int main(int argc, char const *argv[])
{
	int n ,e;
	cout<<"No of Vertices:";
	cin>>n;
	Graph G1(n), G2(n);
	cout<<"No of edges:";
	cin>>e;
	cout<<"Enter the edges:\n";
	int u , v;
	while(e--)
	{
		cin>>u>>v;
		G1.insertEdge(u,v);
		G2.insertEdge(v,u);
	}
	int TopSort[n];
	G1.topologicalSort(TopSort);
	G2.customDFS(TopSort);
	G2.printSCC();
	return 0;
}