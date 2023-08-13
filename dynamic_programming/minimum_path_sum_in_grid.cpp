// Ninjaland is a country in the shape of a 2-Dimensional grid 'GRID', with 'N' rows and
// 'M' columns.
// Each point in the grid has some cost associated with it.Find a path from top left
// i.e. (0, 0) to the bottom right i.e. ('N' - 1, 'M' - 1) which minimizes the sum of the
// cost of all the numbers along the path.
// You need to tell the minimum sum of that path.You can only move down or right at any
// point in time.

// Example:
// Input:  2 3
//         5 9 6
//         11 5 2
// Output: 21

#include <bits/stdc++.h>
using namespace std;

int solve_m(int row, int col, vector<vector<int>> &grid, vector<vector<int>> &dp)
{
    if ((row < 0) || (col < 0))
    {
        return 1e9;
    }

    if ((row == 0) && (col == 0))
    {
        return grid[0][0];
    }

    if (dp[row][col] != -1)
    {
        return dp[row][col];
    }

    int up = solve_m(row - 1, col, grid, dp) + grid[row][col];
    int left = solve_m(row, col - 1, grid, dp) + grid[row][col];

    dp[row][col] = min(up, left);
    return dp[row][col];
}

int solve_t(int n, int m, vector<vector<int>> &grid, vector<vector<int>> &dp)
{
    for (int row = 0; row <= n; row++)
    {
        for (int col = 0; col <= m; col++)
        {
            if ((row == 0) && (col == 0))
            {
                dp[row][col] = grid[0][0];
            }
            else
            {
                int right = grid[row][col];
                if (col > 0)
                {
                    right += dp[row][col - 1];
                }
                else
                {
                    right += 1e9;
                }

                int down = grid[row][col];
                if (row > 0)
                {
                    down += dp[row - 1][col];
                }
                else
                {
                    down += 1e9;
                }

                dp[row][col] = min(right, down);
            }
        }
    }

    return dp[n][m];
}

int solve_so(int n, int m, vector<vector<int>> &grid)
{
    vector<int> prev;

    for (int row = 0; row < n; row++)
    {
        vector<int> curr(m);

        for (int col = 0; col < m; col++)
        {
            if ((row == 0) && (col == 0))
            {
                curr[col] = grid[0][0];
            }
            else
            {
                int right = grid[row][col];
                if (col > 0)
                {
                    right += curr[col - 1];
                }
                else
                {
                    right += 1e9;
                }

                int down = grid[row][col];
                if (row > 0)
                {
                    down += prev[col];
                }
                else
                {
                    down += 1e9;
                }

                curr[col] = min(right, down);
            }
        }

        prev = curr;
    }

    return prev[m - 1];
}

int minSumPath(vector<vector<int>> &grid)
{
    int n = grid.size();
    int m = grid[0].size();

    // vector<vector<int>> dp(n, vector<int>(m, -1));

    return solve_so(n, m, grid);
}
