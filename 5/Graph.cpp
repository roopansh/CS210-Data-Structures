#include <bits/stdc++.h>

using namespace std;

class Graph
{
private:
	int NumOfVertex;
	vector<int> *Vertex;
	int *Parent;// -1 represents NULL Parent
	int *Color;// 0 represents white , 1 represents gray and 2 represents black
	int *Distance;
	int Timer;
	int *Timer1;
	int *Timer2;
	vector<int> *Connections;
	vector<int> *Cycles;
	struct EdgeType
	{
		int u , v;
		int Type;
		/*	1 = Tree Edge
			2 = Forward Edge
			3 = Back Edge
			4 = Cross Edge 		*/
	};
	vector<EdgeType> TypeOfEdge;
	int **PathMatrix;
public:
	int Connect;
	int Cycle;
	Graph(int V);
	void InitialiseForSearch();
	void InsertEdgeUndirected(int u , int v);
	void InsertEdgeDirected(int u , int v);
	void DFS();
	void DFS_Visit(int v);
	void BFS();
	bool CheckCycle();
	bool CheckCycle_Visit(int v);
	void Print_Path(int u , int v);
	bool PathCheck(int u , int v);
	void Print_Conenctions();
	void Print_Cycles();
	void Print_PathMatrix();
	EdgeType * CreateEdgeType(int u , int v , int x);
	void PrintEdgeType();
	void BuildPathMatrix();
};

int main()
{}

Graph::Graph(int V)
:NumOfVertex(V)
{
	Vertex = new vector<int>[NumOfVertex+1];
	InitialiseForSearch();
	PathMatrix = new int*[NumOfVertex+1];
	for(int i=1;i<=NumOfVertex;i++)
	{
		PathMatrix[i] = new int[NumOfVertex+1];
	}
}

void Graph::InitialiseForSearch()
{
	Color = new int[NumOfVertex+1];
	Parent = new int[NumOfVertex+1];
	Timer1 = new int [NumOfVertex+1];
	Timer2 = new int[NumOfVertex+1];
	Distance = new int[NumOfVertex];
	Connections = new vector<int>[NumOfVertex+1];
	Cycles = new vector<int>[NumOfVertex+1];
	Connect = 0;
	Cycle = 0;
	Timer =0;
	for(int v =1 ; v<= NumOfVertex ; v++)
	{
		Color[v] = 0;
		Parent[v] = -1;
		Timer1[v] = -1;
		Timer2[v] = -1;
		Distance[v] = 0;
	}

}

void Graph::InsertEdgeUndirected(int u , int v)
{
	Vertex[u].push_back(v);
	Vertex[v].push_back(u);
}

void Graph::InsertEdgeDirected(int u , int v)
{
	Vertex[u].push_back(v);
}

void Graph::DFS()
{
	InitialiseForSearch();
	for (int v = 1; v <= NumOfVertex; ++v)
	{
		if (Color[v] == 0)
		{
			Connect++;
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
		if (Color[v] == 0)
		{
			cout<<"\t"<<v;
			Parent[v] = u;
			DFS_Visit(v);
		}
	}
	Color[u] = 2;// represents black color
	Timer++;
	Timer2[u] = Timer;
}

void Graph::BFS()
{
	queue <int> BFS_Queue;
	InitialiseForSearch();
	BFS_Queue.push(1);
	Color[1] = 1;
	cout<<"1";
	while(!BFS_Queue.empty())
	{
		int node1 = BFS_Queue.front();
		for(int i = 0; i < Vertex[node1].size() ; i++)
		{
			int node2 = Vertex[node1].at(i);
			if(Color[node2] == 0)
			{
				Parent[node2] = node1;
				Distance[node2] = Distance[node1] +1;
				Color[node2] = 1;
				BFS_Queue.push(node2);
				cout<<"\t"<<node2;
			}
		}
		Color[node1] = 2;
		BFS_Queue.pop();
	}
	cout<<endl;
}

bool Graph::CheckCycle()
{
	//dfs and first occurrence of any back edge , it means that there is a cycle
	InitialiseForSearch();
	for(int i=1; i<= NumOfVertex ;i++)
	{
		if (Color[i] == 0)
		{
			if(CheckCycle_Visit(i))
				return true;
		}
	}
	return false;
}

bool Graph::CheckCycle_Visit(int v)
{
	Color[v]++;
	for (int i = 0; i <	Vertex[v].size(); ++i)
	{
		int node = Vertex[v].at(i);
		if(Color[node] == 0)
		{
			Parent[node] = v;
			if( CheckCycle_Visit(node))
				return true;
		}
		else if (Color[node] == 1)
		{
			if (Parent[node] != v && Parent[v] != node)//for undirected graph
			{
				return true;
			}
		}
	}
	Color[v]++;
	return false;
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
		}
	}
	return;
}

void Graph::Print_Cycles()
{
	if(!CheckCycle())
	{
		cout<<"No Cycle Found"<<endl;
		return ;
	}
	int count = 1;
	for(int u = 1 ; u <= NumOfVertex ; u++ )
	{
		for(int i = 0 ; i < Cycles[u].size() ; i++)
		{
			int v = Cycles[u].at(i);
			cout<<"Cycle #"<<count++<<" :";
			Print_Path(u , v);
			cout<<"\t"<<u;
			cout<<endl;
		}
	}
	return ;
}

void Graph::BuildPathMatrix()
{
	for (int i = 1; i <= NumOfVertex; ++i)
	{
		for (int j = 1; i <= NumOfVertex; ++i)
		{
			if (i == j)
			{
				PathMatrix[i][j] = 1;
				continue;
			}
			if(PathCheck(i , j))
				PathMatrix[i][j] = 1;
			else
				PathMatrix[i][j] = 0;
		}
	}
}

void Graph::Print_PathMatrix()
{
	BuildPathMatrix();

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
}

bool Graph::PathCheck(int u , int v)
{
	InitialiseForSearch();
	queue<int> Q;
	Q.push(u);
	while(!Q.empty())
	{
		int Node = Q.front();
		Q.pop();
		if(Node == v)
			return true;
		Color[Node] = 1;
		for(int i=0;i< Vertex[Node].size();i++)
		{
			int temp = Vertex[Node].at(i);
			if(Color[temp] == 0)
			{
				Q.push(temp);
				Color[temp] = 1;
				if(temp == v)
					return true;
			}
		}
		Color[Node] = 2;
	}
	return false;
}

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
}

void Graph::PrintEdgeType()
{
	for(int i = 0 ; i < TypeOfEdge.size() ;i++)
	{
		EdgeType *Edge = &TypeOfEdge.at(i);
		cout<<Edge->u<<"--->"<<Edge->v<<" is a\t"<<Edge->Type<<"."<<endl;
	}
}