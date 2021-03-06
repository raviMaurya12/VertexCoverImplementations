#include<bits/stdc++.h>
using namespace std;
#define NIL 0
#define INF INT_MAX

class BipGraph
{
	int m, n;

	list<int> *adj;

	int *pairU, *pairV, *dist;

public:
	BipGraph(int m, int n); // Constructor
	void addEdge(int u, int v); // To add edge

	// Returns true if there is an augmenting path
	bool bfs();

	// Adds augmenting path if there is one beginning with u
	bool dfs(int u);

	// Returns size of maximum matcing
	int hopcroftKarp();
};

int BipGraph::hopcroftKarp()
{
	pairU = new int[m+1];

	pairV = new int[n+1];

	dist = new int[m+1];

	for (int u=0; u<m; u++)
		pairU[u] = NIL;
	for (int v=0; v<n; v++)
		pairV[v] = NIL;

	// Initialize result
	int result = 0;

	while (bfs())
	{
		for (int u=1; u<=m; u++)

			if (pairU[u]==NIL && dfs(u))
				result++;
	}
	return result;
}

bool BipGraph::bfs()
{
	queue<int> Q;

	for (int u=1; u<=m; u++)
	{
		if (pairU[u]==NIL)
		{
			dist[u] = 0;
			Q.push(u);
		}
		else dist[u] = INF;
	}

	dist[NIL] = INF;

	while (!Q.empty())
	{
		int u = Q.front();
		Q.pop();

		if (dist[u] < dist[NIL])
		{
			list<int>::iterator i;
			for (i=adj[u].begin(); i!=adj[u].end(); ++i)
			{
				int v = *i;
				if (dist[pairV[v]] == INF)
				{
					dist[pairV[v]] = dist[u] + 1;
					Q.push(pairV[v]);
				}
			}
		}
	}

	return (dist[NIL] != INF);
}

bool BipGraph::dfs(int u)
{
	if (u != NIL)
	{
		list<int>::iterator i;
		for (i=adj[u].begin(); i!=adj[u].end(); ++i)
		{

			int v = *i;

			if (dist[pairV[v]] == dist[u]+1)
			{
				if (dfs(pairV[v]) == true)
				{
					pairV[v] = u;
					pairU[u] = v;
					return true;
				}
			}
		}

		dist[u] = INF;
		return false;
	}
	return true;
}

// Constructor
BipGraph::BipGraph(int m, int n)
{
	this->m = m;
	this->n = n;
	adj = new list<int>[m+1];
}

void BipGraph::addEdge(int u, int v)
{
	adj[u].push_back(v);
}

// Driver Program
int main()
{
	cout<<"Enter number of vertices on left and right "<<endl;
	int a,b;
	cin>>a>>b;
	BipGraph g(a,b);
	cout<<"Enter the number of edges "<<endl;
	int edge;
	cin>>edge;
	cout<<"Enter all edges "<<endl;
	for(int i=0;i<edge;i++){
		int x,y;
		cin>>x>>y;
		g.addEdge(x,y);
	}

	cout << "Size of maximum matching is " << g.hopcroftKarp()<<endl;

	return 0;
}
