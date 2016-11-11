#include <bits/stdc++.h>
using namespace std;
class Graph
{
private:
	int NumOfVertices;
	std::vector<int> *Edges;
	int *DiscTime;
	int *FinTime;
	int *Colour;//0 is white , 1 is gray , 2 is black
public:
	Graph(int n)
	:NumOfVertices(n)
	{
		Edges = new vector<int>[NumOfVertices+1];
		DiscTime = new int[NumOfVertices];
		FinTime = new int[NumOfVertices];
		Colour = new int[NumOfVertices];
	}
	void InsertEdge(int u , int v)
	{
		Edges[u].push_back(v);
	}
	Graph* Transpose()
	{
		Graph *temp = new Graph(NumOfVertices);
		for (int i = 1; i <= NumOfVertices; ++i)
		{
			for (int j = 0; j < Edges[i].size(); ++j)
			{
				temp->InsertEdge(Edges[i].at(j) , i);
			}
		}
		return temp;
	}
	void initialise()
	{
		for (int i = 1; i <= NumOfVertices; ++i)
		{
			Colour[i] = 0;
			DiscTime[i] = 0;
			FinTime[i] = 0;
		}
	}
	void DFS(vector<int> &DFSTraver)
	{
		initialise();
		int time = 0;
		for (int i = 1; i <= NumOfVertices; ++i)
		{
			if (Colour[i] == 0)
			{
				Colour[i]++;
				DFSTraver.push_back(i);
				DFS_Visit(i , time , DFSTraver);
			}
		}
	}
	void DFS_Visit(int u , int &time , vector<int> &DFSTraver)
	{
		DiscTime[u] = ++time;
		for (int i = 0; i < Edges[u].size(); ++i)
		{
			int v = Edges[u].at(i);
			if (Colour[v] == 0)
			{
				Colour[v]++;
				DFSTraver.push_back(v);
				DFS_Visit(v , time , DFSTraver);
			}
		}
		Colour[u]++;
		FinTime[u] = ++time;
	}
	void Print_DFS()
	{
		std::vector<int> DFSTraver;
		DFS(DFSTraver);
		for (int i = 0; i < DFSTraver.size(); ++i)
		{
			cout<<DFSTraver.at(i)<<"\t";
		}
		cout<<endl;
	}
	void DFS2(vector<int> &TopoSort)
	{
		initialise();
		int time = 0;
		for (int i = 1; i <= NumOfVertices; ++i)
		{
			if (Colour[i] == 0)
			{
				Colour[i]++;
				DFS_Visit2(i , time , TopoSort);
			}
		}
	}
	void DFS_Visit2(int u , int &time , vector<int> &TopoSort)
	{
		DiscTime[u] = ++time;
		for (int i = 0; i < Edges[u].size(); ++i)
		{
			int v = Edges[u].at(i);
			if (Colour[v] == 0)
			{
				Colour[v]++;
				DFS_Visit2(v , time , TopoSort);
			}
		}
		Colour[u]++;
		FinTime[u] = ++time;
		TopoSort.push_back(u);
	}
	void DFS3(vector<int> TopoSort , vector<int> *SCC)
	{
		initialise();
		int time = 0;
		int SCC_Count = 0;
		// cout<<"SIZE OF TopoSort:"<<TopoSort.size()<<endl;;
		for (int i = TopoSort.size()-1; i >= 0 ; --i)
		{
			int u = TopoSort.at(i);
			if (Colour[u] == 0)
			{
				Colour[u]++;
				DFS_Visit3(u , time , SCC , SCC_Count++);
			}
		}
		cout<<"TOTAL NUMBER OF SCC's ARE:\t"<<SCC_Count<<endl;
	}
	void DFS_Visit3(int u , int &time , vector<int> *SCC , int SCC_Count)
	{
		SCC[SCC_Count].push_back(u);
		DiscTime[u] = ++time;
		for (int i = 0; i < Edges[u].size(); ++i)
		{
			int v = Edges[u].at(i);
			if (Colour[v] == 0)
			{
				Colour[v]++;
				DFS_Visit3(v , time , SCC , SCC_Count);
			}
		}
		Colour[u]++;
		FinTime[u] = ++time;
	}

	void SCC()
	{
		std::vector<int> TopoSort;
		DFS2(TopoSort);
		
		/*******DEBUGGING*******/
		// for (int i = 0; i < TopoSort.size(); ++i)
		// {
		// 	cout<<TopoSort.at(i)<<"  ";
		// }
		// cout<<endl;
		/*******DEBUGGING*******/

		Graph *Gt = Transpose();

		std::vector<int> SCC[NumOfVertices];
		Gt->DFS3(TopoSort , SCC);
		for (int i = 0; i < NumOfVertices; ++i)
		{
			for (int j = 0; j < SCC[i].size(); ++j)
			{
				cout<<SCC[i].at(j)<<"\t";
			}
			cout<<endl;
		}
	}
	void PrintList()
	{
		for (int i = 1; i <= NumOfVertices; ++i)
		{
			cout<<i<<"  --->  ";
			for (int j = 0; j < Edges[i].size(); ++j)
			{
				cout<<Edges[i].at(j)<<" , ";
			}
			cout<<endl;
		}
	}
};
int main(int argc, char const *argv[])
{
	int n,e;
	cout<<"Enter the number of vertices:\t";
	cin>>n;
	Graph G(n);
	cout<<"Enter the numebr of egdes:\t";
	cin>>e;
	int x, y;
	cout<<"Enter the edges:\n";
	while(e--)
	{
		cin>>x>>y;
		G.InsertEdge(x,y);
	}

	// G.PrintList();	


	cout<<"PART-A : TRANSPOSE"<<endl;
	Graph *GT = G.Transpose();
	GT->PrintList();

	cout<<endl<<endl<<"PART-B : DFS TRAVERSAL"<<endl;
	G.Print_DFS();
	
	cout<<endl<<endl<<"PART-C : SCC"<<endl;
	G.SCC();

	return 0;
}