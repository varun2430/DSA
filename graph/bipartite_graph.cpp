// Given an adjacency list of a graph adj  of V no. of vertices having 0 based index. Check
// whether the graph is bipartite or not.

// Bipartite graph: a graph that can be coloured using two colours such that no adjacent
//                  nodes have the same colour.
// Note: if there are even no. of nodes in a cycle than graph is bipartite
//       if there are odd no. of nodes in a cycle than graph is not bipartite
//       all linear graphs are bipartite

#include <bits/stdc++.h>
using namespace std;

bool check(int src, vector<int> adj[], vector<int> &color)
{
    queue<int> q;
    q.push(src);
    color[src] = 0;

    while (!q.empty())
    {
        int node = q.front();
        q.pop();

        for (int adjNode : adj[node])
        {
            if (color[adjNode] == -1)
            {
                color[adjNode] = !color[node];
                q.push(adjNode);
            }
            else if (color[node] == color[adjNode])
            {
                return false;
            }
        }
    }

    return true;
}

bool isBipartite(int V, vector<int> adj[])
{
    vector<int> color(V, -1);
    for (int i = 0; i < V; i++)
    {
        if (color[i] == -1)
        {
            if (check(i, adj, color) == false)
            {
                return false;
            }
        }
    }

    return true;
}