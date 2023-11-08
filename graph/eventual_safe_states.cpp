// A directed graph of V vertices and E edges is given in the form of an adjacency list adj.
// Each node of the graph is labelled with a distinct integer in the range 0 to V - 1.
// A node is a terminal node if there are no outgoing edges. A node is a safe node if every
// possible path starting from that node leads to a terminal node.
// You have to return an array containing all the safe nodes of the graph. The answer should
// be sorted in ascending order.

#include <bits/stdc++.h>
using namespace std;

// bfs approach:
// reverse the edges in the graph
// perform kahn's algorithm on the resultant graph
// the sequence we get are the safe nodes

bool dfs(int node, vector<int> adj[], vector<bool> &visited, vector<bool> &pathVis, vector<bool> &safe)
{
    visited[node] = true;
    pathVis[node] = true;
    safe[node] = false;

    for (auto adjNode : adj[node])
    {
        if (!visited[adjNode])
        {
            if (dfs(adjNode, adj, visited, pathVis, safe) == true)
            {
                return true;
            }
        }
        else if (pathVis[adjNode] == true)
        {
            return true;
        }
    }

    safe[node] = true;
    pathVis[node] = false;
    return false;
}

vector<int> eventualSafeNodes(int V, vector<int> adj[])
{
    vector<bool> visited(V, false);
    vector<bool> pathVis(V, false);
    vector<bool> safe(V, false);

    for (int i = 0; i < V; i++)
    {
        if (!visited[i])
        {
            dfs(i, adj, visited, pathVis, safe);
        }
    }

    vector<int> res;
    for (int i = 0; i < V; i++)
    {
        if (safe[i] == true)
        {
            res.push_back(i);
        }
    }

    return res;
}
