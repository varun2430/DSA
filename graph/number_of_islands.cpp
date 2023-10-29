// Given an m x n 2D binary grid grid which represents a map of '1's (land) and
// '0's (water), return the number of islands.
// An island is surrounded by water and is formed by connecting adjacent lands horizontally
// or vertically. You may assume all four edges of the grid are all surrounded by water.

// Example:
// Input:  grid = [ ["1","1","0","0","0"],
//                  ["1","1","0","0","0"],
//                  ["0","0","1","0","0"],
//                  ["0","0","0","1","1"]  ]
// Output: 3

#include <bits/stdc++.h>
using namespace std;

void bfs(int &i, int &j, int &n, int &m, vector<vector<char>> &grid, vector<vector<bool>> &visited)
{
    queue<pair<int, int>> q;
    q.push({i, j});
    visited[i][j] = true;

    while (!q.empty())
    {
        int row = q.front().first;
        int col = q.front().second;
        q.pop();

        int dr[4] = {-1, 0, 1, 0};
        int dc[4] = {0, 1, 0, -1};

        for (int k = 0; k < 4; k++)
        {
            int nrow = row + dr[k];
            int ncol = col + dc[k];

            if ((nrow >= 0) && (nrow < n) && (ncol >= 0) && (ncol < m) && (grid[nrow][ncol] == '1') && (visited[nrow][ncol] == false))
            {
                q.push({nrow, ncol});
                visited[nrow][ncol] = true;
            }
        }
    }
}

int numIslands(vector<vector<char>> &grid)
{
    int n = grid.size();
    int m = grid[0].size();

    vector<vector<bool>> visited(n, vector<bool>(m, false));

    int count = 0;
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < m; col++)
        {
            if ((grid[row][col] == '1') && (visited[row][col] == false))
            {
                bfs(row, col, n, m, grid, visited);
                count += 1;
            }
        }
    }

    return count;
}