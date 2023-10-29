// Given an undirected graph with V vertices. We say two vertices u and v belong to a single
// component if there is a path from u to v or v to u. Your task is to find the
// number of component.

// Example:
// Input:  [
//             [1, 0, 1],
//             [0, 1, 0],
//             [1, 0, 1]  ]
// Output: 2

#include <bits/stdc++.h>
using namespace std;

void dfs(int node, vector<int> adj[], vector<bool> &visited)
{
    visited[node] = true;

    for (int &adjNode : adj[node])
    {
        if (visited[adjNode] == false)
        {
            dfs(adjNode, adj, visited);
        }
    }
}

int numProvinces(vector<vector<int>> adjM, int V)
{
    vector<int> adj[V];

    // convert the given adjacency matrix to adjacency list
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            if ((adjM[i][j] == 1) && (i != j))
            {
                adj[i].push_back(j);
            }
        }
    }

    vector<bool> visited(V, false);

    int count = 0;
    for (int node = 0; node < V; node++)
    {
        if (visited[node] == false)
        {
            dfs(node, adj, visited);
            count += 1;
        }
    }

    return count;
}