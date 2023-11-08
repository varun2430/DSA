// Given a Directed Acyclic Graph of N vertices from 0 to N-1 and a 2D Integer
// array(or vector) edges[ ][ ] of length M, where there is a directed edge from edge[i][0]
// to edge[i][1] with a distance of edge[i][2] for all i.

// Find the shortest path from src(0) vertex to all the vertices and if it is impossible to
// reach any vertex, then return -1 for that vertex.

// Example:
// Input:  N = 4, M = 2
//         edge = [[0,1,2],[0,2,1]
// Output: 0 2 1 -1

#include <bits/stdc++.h>
using namespace std;

void topoDfs(int node, vector<pair<int, int>> adj[], vector<bool> &visited, stack<int> &st)
{
    visited[node] = true;

    for (auto it : adj[node])
    {
        int v = it.first;
        if (!visited[v])
        {
            topoDfs(v, adj, visited, st);
        }
    }

    st.push(node);
}

vector<int> shortestPath(int N, int M, vector<vector<int>> &edges)
{
    vector<pair<int, int>> adj[N];
    for (int i = 0; i < M; i++)
    {
        adj[edges[i][0]].push_back({edges[i][1], edges[i][2]});
    }

    vector<bool> visited(N, false);
    stack<int> st;
    for (int i = 0; i < N; i++)
    {
        if (!visited[i])
        {
            topoDfs(i, adj, visited, st);
        }
    }

    vector<int> dist(N, 1e9);
    dist[0] = 0;

    // we first perform toposort then go according to that sequence i.e. rechability
    // to calculate the distance
    while (!st.empty())
    {
        int u = st.top();
        st.pop();

        for (auto it : adj[u])
        {
            int v = it.first;
            int wt = it.second;

            if ((dist[u] + wt) < dist[v])
            {
                dist[v] = dist[u] + wt;
            }
        }
    }

    // the distance of the rechable nodes gets updated and those who remain 1e9 are
    // unrechable
    for (int i = 0; i < N; i++)
    {
        if (dist[i] == 1e9)
        {
            dist[i] = -1;
        }
    }

    return dist;
}
