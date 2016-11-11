#include <bits/stdc++.h>

using namespace std;

class Graph
{
private:
	int NumOfVertex;
	vector<int> *Vertex;
	int *Color;// 0 represents white , 1 represents gray and 2 represents black
	int *Parent;// -1 represents NULL Parent
	int Timer;
	int *Timer1;
	int *Timer2;
	vector<int> *Connections;
public:
	int Connect;
	int Cycle;
	Graph(int V);
	void InsertEdge(int u , int v);
	void DFS();
	void DFS_Visit(int v, int Connect);
	void Print_Path(int u , int v);
	void Print_Conenctions();
};

int main()
{
	int n , e;
	// cout<<"Enter thenumber of Vertices:\t";
	cin>>n;
	Graph Lab5(n);
	// cout<<"Enter the number of edges:\t";
	cin>>e;
	// cout<<"Enter the Edges:"<<endl;
	for (int i = 0; i < e; ++i)
	{
		int u ; int v;
		// cout<<"Edge #"<<i+1<<":\t";
		cin>>u>>v;
		Lab5.InsertEdge(u , v);
	}

	Lab5.DFS();

	if(Lab5.Cycle == 0)	cout<<"NO CYCLES"<<endl;
	else	cout<<"Total number of cycles present are :\t"<<Lab5.Cycle<<endl;
	cout<<"********************************************************************"<<endl;
	cout<<"Total number of Connected Components present are :\t"<<Lab5.Connect<<endl;
	Lab5.Print_Conenctions();
}

Graph::Graph(int V)
:NumOfVertex(V)
{
	Vertex = new vector<int>[NumOfVertex+1];
	Color = new int[NumOfVertex+1];
	Parent = new int[NumOfVertex+1];
	Timer1 = new int [NumOfVertex+1];
	Timer2 = new int[NumOfVertex+1];
	Connections = new vector<int>[NumOfVertex+1];
	Connect = 0;
	Cycle = 0;
	for(int v =1 ; v<= NumOfVertex ; v++)
	{
		Color[v] = 0;
		Parent[v] = -1;
	}
}

void Graph::InsertEdge(int u , int v)
{
	Vertex[u].push_back(v);
	Vertex[v].push_back(u);
}

void Graph::DFS()
{
	Timer =0;
	for (int v = 1; v <= NumOfVertex; ++v)
	{
		if (Color[v] == 0)
		{
			Connect++;
			DFS_Visit(v , Connect);
		}
	}
}

void Graph::DFS_Visit(int u , int Connect)
{
	Color[u] = 1;// represents gray color
	Timer++;
	Timer1[u] = Timer;
	Connections[Connect].push_back(u);
	for (int i = 0; i < Vertex[u].size(); ++i)
	{
		int v = Vertex[u].at(i);
		if (Color[v] == 0)
		{
			Parent[v] = u;
			DFS_Visit(v , Connect);
		}
		else if(Color[v] == 1)//Gray(i.e. Back Edge ==> Cycle)
		{
			if (Parent[u] == v || Parent[v] == u)
			{
				continue;
			}
			else
			{
				Cycle++;
				cout<<"Cycle Found #"<<Cycle<<":\t";
				Print_Path(v , u);
				cout<<"\t"<<v;
				cout<<endl;
			}
		}
	}
	Color[u] = 2;// represents black color
	Timer++;
	Timer2[u] = Timer;
}

void Graph::Print_Path(int u , int v)
{
	if (u == v)
	{
		cout<<"\t"<<u;
	}
	else if (Parent[v] == -1)
	{
		cout<<"NO PATH EXIST"<<endl;
	}
	else
	{
		Print_Path(u, Parent[v]);
		cout<<"\t"<<v;
	}
}

void Graph::Print_Conenctions()
{
	int count = 1;
	for (int i = 1; i <= NumOfVertex; ++i)
	{
		if (Connections[i].size() != 0)
		{
			cout<<"Connected Component #"<<count++<<":\t";
		}

		for (int v = 0; v < Connections[i].size(); ++v)
		{
			cout<<"\t"<<Connections[i].at(v);
		}
		if (Connections[i].size() != 0)
		{
			cout<<endl;
			/* code */
		}
	}
}