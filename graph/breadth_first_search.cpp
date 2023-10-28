// Given a directed graph. The task is to do Breadth First Traversal of this graph starting
// from 0.

// Example:
// Input:  V = 5, E = 4 adj = {{1,2,3},{},{4},{},{}}
// Output: 0 1 2 3 4

#include <bits/stdc++.h>
using namespace std;

vector<int> bfsOfGraph(int V, vector<int> adj[])
{
    vector<bool> visited(V, false);

    queue<int> q;
    q.push(0);
    visited[0] = true;

    vector<int> bfs;

    while (!q.empty())
    {
        int node = q.front();
        q.pop();

        bfs.push_back(node);

        for (int &adjNode : adj[node])
        {
            if (visited[adjNode] == false)
            {
                q.push(adjNode);
                visited[adjNode] = true;
            }
        }
    }

    return bfs;
}
