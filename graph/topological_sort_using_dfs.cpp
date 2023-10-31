// Given a Directed Acyclic Graph (DAG) with V vertices and E edges, Find any Topological
// Sorting of that Graph.

#include <bits/stdc++.h>
using namespace std;

void dfs(int node, vector<int> adj[], vector<bool> &visited, stack<int> &st)
{
    visited[node] = true;

    for (int &adjNode : adj[node])
    {
        if (!visited[adjNode])
        {
            dfs(adjNode, adj, visited, st);
        }
    }

    st.push(node);
}

vector<int> topoSort(int V, vector<int> adj[])
{
    stack<int> st;
    vector<bool> visited(V, false);

    for (int i = 0; i < V; i++)
    {
        if (!visited[i])
        {
            dfs(i, adj, visited, st);
        }
    }

    vector<int> res;
    while (!st.empty())
    {
        res.push_back(st.top());
        st.pop();
    }

    return res;
}
