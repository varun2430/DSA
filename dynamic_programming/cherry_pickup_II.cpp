// You are given a rows x cols matrix grid representing a field of cherries where grid[i][j]
// represents the number of cherries that you can collect from the (i, j) cell.

// You have two robots that can collect cherries for you:
// Robot #1 is located at the top-left corner (0, 0), and
// Robot #2 is located at the top-right corner (0, cols - 1).
// Return the maximum number of cherries collection using both robots by following the rules
// below:

// From a cell (i, j), robots can move to cell (i + 1, j - 1), (i + 1, j), or (i + 1, j + 1).
// When any robot passes through a cell, It picks up all cherries, and the cell becomes an
// empty cell.
// When both robots stay in the same cell, only one takes the cherries.
// Both robots cannot move outside of the grid at any moment.
// Both robots should reach the bottom row in grid.

// Example:
// Input:  grid = [ [3,1,1] ,
//                  [2,5,1] ,
//                  [1,5,5] ,
//                  [2,1,1] ]
// Output: 24

#include <bits/stdc++.h>
using namespace std;

// memoization top down
int solve_m(int row, int col_1, int col_2, int &n, int &m, vector<vector<int>> &grid, vector<vector<vector<int>>> &dp)
{
    if ((col_1 >= m) || (col_1 < 0) || (col_2 >= m) || (col_2 < 0))
    {
        return -1e9;
    }

    if (dp[row][col_1][col_2] != -1)
    {
        return dp[row][col_1][col_2];
    }

    if (row == n - 1)
    {
        if (col_1 == col_2)
        {
            return grid[row][col_1];
        }
        else
        {
            return (grid[row][col_1] + grid[row][col_2]);
        }
    }

    int maxCherry = -1e9;
    for (int d1 = -1; d1 <= 1; d1++)
    {
        for (int d2 = -1; d2 <= 1; d2++)
        {
            int ncol_1 = col_1 + d1;
            int ncol_2 = col_2 + d2;

            int cherryPicked = 0;
            if (col_1 == col_2)
            {
                cherryPicked = grid[row][col_1];
            }
            else
            {
                cherryPicked = grid[row][col_1] + grid[row][col_2];
            }
            cherryPicked += solve_m(row + 1, ncol_1, ncol_2, n, m, grid, dp);

            maxCherry = max(maxCherry, cherryPicked);
        }
    }

    dp[row][col_1][col_2] = maxCherry;
    return dp[row][col_1][col_2];
}

// tabulation bottom up
int solve_t(int &n, int &m, vector<vector<int>> &grid, vector<vector<vector<int>>> &dp)
{
    for (int col_1 = 0; col_1 < m; col_1++)
    {
        for (int col_2 = 0; col_2 < m; col_2++)
        {
            if (col_1 == col_2)
            {
                dp[n - 1][col_1][col_2] = grid[n - 1][col_1];
            }
            else
            {
                dp[n - 1][col_1][col_2] = grid[n - 1][col_1] + grid[n - 1][col_2];
            }
        }
    }

    for (int row = n - 2; row >= 0; row--)
    {
        for (int col_1 = 0; col_1 < m; col_1++)
        {
            for (int col_2 = 0; col_2 < m; col_2++)
            {
                int maxCherry = INT_MIN;
                for (int d1 = -1; d1 <= 1; d1++)
                {
                    for (int d2 = -1; d2 <= 1; d2++)
                    {
                        int ncol_1 = col_1 + d1;
                        int ncol_2 = col_2 + d2;

                        int cherryPicked = 0;
                        if (col_1 == col_2)
                        {
                            cherryPicked = grid[row][col_1];
                        }
                        else
                        {
                            cherryPicked = grid[row][col_1] + grid[row][col_2];
                        }

                        if ((ncol_1 >= 0) && (ncol_1 < m) && (ncol_2 >= 0) && (ncol_2 < m))
                        {
                            cherryPicked += dp[row + 1][ncol_1][ncol_2];
                        }

                        maxCherry = max(maxCherry, cherryPicked);
                    }
                }

                dp[row][col_1][col_2] = maxCherry;
            }
        }
    }

    return dp[0][0][m - 1];
}

// space optimized bottom up
int solve_so(int &n, int &m, vector<vector<int>> &grid)
{
    vector<vector<int>> prev(m, vector<int>(m, 0));

    for (int col_1 = 0; col_1 < m; col_1++)
    {
        for (int col_2 = 0; col_2 < m; col_2++)
        {
            if (col_1 == col_2)
            {
                prev[col_1][col_2] = grid[n - 1][col_1];
            }
            else
            {
                prev[col_1][col_2] = grid[n - 1][col_1] + grid[n - 1][col_2];
            }
        }
    }

    for (int row = n - 2; row >= 0; row--)
    {
        vector<vector<int>> curr(m, vector<int>(m, 0));

        for (int col_1 = 0; col_1 < m; col_1++)
        {
            for (int col_2 = 0; col_2 < m; col_2++)
            {
                int maxCherry = INT_MIN;
                for (int d1 = -1; d1 <= 1; d1++)
                {
                    for (int d2 = -1; d2 <= 1; d2++)
                    {
                        int ncol_1 = col_1 + d1;
                        int ncol_2 = col_2 + d2;

                        int cherryPicked = 0;
                        if (col_1 == col_2)
                        {
                            cherryPicked = grid[row][col_1];
                        }
                        else
                        {
                            cherryPicked = grid[row][col_1] + grid[row][col_2];
                        }

                        if ((ncol_1 >= 0) && (ncol_1 < m) && (ncol_2 >= 0) && (ncol_2 < m))
                        {
                            cherryPicked += prev[ncol_1][ncol_2];
                        }

                        maxCherry = max(maxCherry, cherryPicked);
                    }
                }

                curr[col_1][col_2] = maxCherry;
            }
        }

        prev = curr;
    }

    return prev[0][m - 1];
}

int cherryPickup(vector<vector<int>> &grid)
{
    int n = grid.size();
    int m = grid[0].size();

    // vector<vector<vector<int>>> dp(n, vector<vector<int>>(m, vector<int>(m, -1)));
    // return solve_m(0, 0, m-1, n, m, grid, dp);

    // return solve_t(n, m, grid, dp);

    return solve_so(n, m, grid);
}