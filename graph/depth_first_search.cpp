// You are given a connected undirected graph. Perform a Depth First Traversal of the graph.

// Example:
// Input:  V = 5, adj = [[2,3,1] , [0], [0,4], [0], [2]]
// Output: 0 2 4 3 1

#include <bits/stdc++.h>
using namespace std;

void dfs(int node, vector<bool> &visited, vector<int> adj[], vector<int> &res)
{
    visited[node] = true;
    res.push_back(node);

    for (int adjNode : adj[node])
    {
        if (visited[adjNode] == false)
        {
            dfs(adjNode, visited, adj, res);
        }
    }
}

vector<int> dfsOfGraph(int V, vector<int> adj[])
{
    vector<int> res;
    vector<bool> visited(V, false);

    dfs(0, visited, adj, res);

    return res;
}
