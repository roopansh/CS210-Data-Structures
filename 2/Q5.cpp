#include <bits/stdc++.h>

using namespace std;

const int TimeQuantum = 100;

struct node
{
	int Process;
	int ExecutionTime;
	int ArrivalTime;
	node *next ;
	node *prev;
};

node * CreateNode(int P , int Exec , int Arr )
{
	node * temp = new node;
	temp->Process = P;
	temp->ExecutionTime = Exec;
	temp->ArrivalTime = Arr;
	temp->next = NULL;
	temp->prev = NULL;

	return temp;
}

class Queue
{
private:
	node * HEAD ;//Head points to the process currently being processed
public:
	Queue()
	:HEAD(NULL)
	{
		//Initially the Queue is empty
	}

	bool isEmpty()
	{
		if(HEAD==NULL)
			return true;
		else
			return false;
	}


	void InsertNode(node * ProcessToInsert)
	{
		if(isEmpty())
		{
			HEAD = ProcessToInsert;
			ProcessToInsert->prev = NULL;
			ProcessToInsert->next = NULL;
			//TAIL = ProcessToInsert;
			return ;
		}
		else if (HEAD->next == NULL)
		{
			HEAD->next = ProcessToInsert;
			HEAD->prev = ProcessToInsert;
			ProcessToInsert->next = HEAD;
			ProcessToInsert->prev = HEAD;
		}
		else
		{
			node * ptr = HEAD->prev;
			ProcessToInsert->next = HEAD;
			ProcessToInsert->prev = ptr;
			ptr->next = ProcessToInsert;
			HEAD->prev = ProcessToInsert;
		}
	}

	void DeleteNode()
	{
		if(isEmpty())
		{
			cout<<"No Process To Delete"<<endl;
			return ;
		}
		if(HEAD->next == NULL)
		{
			cout<<"No Process is being processed currently"<<endl;
			free(HEAD);
			return;
		}
		node * ptr = HEAD;
		HEAD = HEAD->next;
		HEAD->prev = ptr->prev;
		(ptr->prev)->next = HEAD;
		free(ptr);
		return;
	}

	void NextProcess()
	{
		HEAD = HEAD->next;
	}

	node * CurProcess()
	{
		if(isEmpty())
		{
			cout<<"No Process is being processed currently"<<endl;
			return NULL;
		}
		return HEAD;
	}
};

int main()
{

	cout<<"Enter the number of processes:\t";
	int TotalProcess;
	cin>>TotalProcess;

	node * Process[TotalProcess];

	// int Arrival[TotalProcess];
	// int Execute[TotalProcess];

	cout<<endl<<endl<<"**************************************"<<endl<<endl<<"INPUT PROCESSES SORTED ON BASIS OF ARRIVAL TIME ONLY"<<endl<<endl<<"**************************************"<<endl<<endl;

	for(int i=0;i<TotalProcess;i++)
	{
		int Arrival, Execute;
		cout<<"Enter the Arrival time and Execution time of the Process : "<<i+1<<endl;
		cout<<"Arrival : ";
		cin>>Arrival;
		cout<<"Execution : ";
		cin>>Execute;
		Process[i] = CreateNode(i+1 , Execute , Arrival);
	}

	int CurrentTime = 0;

	Queue ProcessQueue;
	
	ProcessQueue.InsertNode(Process[0]);
	
	int PreviousTime = 0;
	int NextTime;
	int NextQuatumTime = TimeQuantum ;
	int P=1;
	//Till the process are arriving
	while(true)
	{
		NextTime = min( NextQuatumTime , Process[P]->ArrivalTime );
		NextTime = min( NextTime , (ProcessQueue.CurProcess())->ExecutionTime  );

		if (NextTime == NextQuatumTime)
		//The Head would move to the next process
		{
			(ProcessQueue.CurProcess())->ExecutionTime -= NextTime - CurrentTime;
			ProcessQueue.NextProcess();
			NextQuatumTime += TimeQuantum;
		}
		else if (NextTime == Process[P]->ArrivalTime)
		//A new process is arriving
		{
			ProcessQueue.InsertNode(Process[P]);
			P++;
			(ProcessQueue.CurProcess())->ExecutionTime -= NextTime - CurrentTime;
			if (P == TotalProcess)
			{
				break;
			}
		}
		else if(NextTime == Process[P-1]->ExecutionTime)
		//The process has completed and is now to be deleted
		{
			ProcessQueue.DeleteNode();
		}

		PreviousTime = CurrentTime;
		CurrentTime = NextTime;
	}

	return 0;
}