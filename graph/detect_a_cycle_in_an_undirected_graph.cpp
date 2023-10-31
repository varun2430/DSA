// Given an undirected graph with V vertices and E edges, check whether it contains any
// cycle or not. Graph is in the form of adjacency list where adj[i] contains all the nodes
// ith node is having edge with.

// Example:
// Input:  V = 5, E = 5, adj = {{1}, {0, 2, 4}, {1, 3}, {2, 4}, {1, 3}}
// Output: 1

#include <bits/stdc++.h>
using namespace std;

bool dcycle_bfs(int src, vector<int> adj[], bool visited[])
{
    queue<pair<int, int>> q;
    q.push({src, -1});
    visited[src] = true;

    while (!q.empty())
    {
        int node = q.front().first;
        int parent = q.front().second;
        q.pop();

        for (int &adjNode : adj[node])
        {
            if (visited[adjNode] == false)
            {
                q.push({adjNode, node});
                visited[adjNode] = true;
            }
            else if (parent != adjNode)
            {
                return true;
            }
        }
    }

    return false;
}

bool dcycle_dfs(int node, int parent, vector<int> adj[], bool visited[])
{
    visited[node] = 1;

    for (int &adjNode : adj[node])
    {
        if (!visited[adjNode])
        {
            if (dcycle_dfs(adjNode, node, adj, visited) == true)
            {
                return true;
            }
        }
        else if (parent != adjNode)
        {
            return true;
        }
    }

    return false;
}

bool isCycle(int V, vector<int> adj[])
{
    bool visited[V] = {0};

    for (int node = 0; node < V; node++)
    {
        if (!visited[node])
        {
            if (dcycle_bfs(node, adj, visited))
            {
                return true;
            }
        }

        // if (!visited[node])
        // {
        //     if (dcycle_dfs(node, -1, adj, visited) == true)
        //     {
        //         return true;
        //     }
        // }
    }

    return false;
}