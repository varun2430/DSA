// Given a Directed Acyclic Graph (DAG) with V vertices and E edges, Find any Topological
// Sorting of that Graph.

#include <bits/stdc++.h>
using namespace std;

vector<int> topoSort(int V, vector<int> adj[])
{
    int inDegree[V] = {0};
    for (int i = 0; i < V; i++)
    {
        for (int &adjNode : adj[i])
        {
            inDegree[adjNode]++;
        }
    }

    queue<int> q;
    for (int i = 0; i < V; i++)
    {
        if (inDegree[i] == 0)
        {
            q.push(i);
        }
    }

    vector<int> res;
    while (!q.empty())
    {
        int node = q.front();
        q.pop();

        res.push_back(node);

        for (int &adjNode : adj[node])
        {
            inDegree[adjNode]--;

            if (inDegree[adjNode] == 0)
            {
                q.push(adjNode);
            }
        }
    }

    return res;
}
