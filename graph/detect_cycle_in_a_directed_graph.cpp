// Given a Directed Graph with V vertices (Numbered from 0 to V-1) and E edges, check
// whether it contains any cycle or not.

#include <bits/stdc++.h>
using namespace std;

// bfs approach:
// perform topological sort using kahn's algorithm
// if the sequence produced has V elements then there is no cycle
// if the sequence produced has less than V elements then there is a cycle

bool dfs(int vertex, vector<int> adj[], vector<bool> &visited, vector<bool> &pathVisited)
{
    visited[vertex] = true;
    pathVisited[vertex] = true;

    for (auto adjVer : adj[vertex])
    {
        if (!visited[adjVer])
        {
            if (dfs(adjVer, adj, visited, pathVisited) == true)
            {
                return true;
            }
        }
        else if (pathVisited[adjVer] == true)
        {
            return true;
        }
    }

    pathVisited[vertex] = false;
    return false;
}

bool isCyclic(int V, vector<int> adj[])
{
    vector<bool> visited(V, false);
    vector<bool> pathVisited(V, false);

    for (int i = 0; i < V; i++)
    {
        if (!visited[i])
        {
            if (dfs(i, adj, visited, pathVisited) == true)
            {
                return true;
            }
        }
    }

    return false;
}