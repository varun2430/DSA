// You are present at point ‘A’ which is the top-left cell of an M X N matrix, your
// destination is point ‘B’, which is the bottom-right cell of the same matrix. Your
// task is to find the total number of unique paths from point ‘A’ to point ‘B’.In
// other words, you will be given the dimensions of the matrix as integers ‘M’ and ‘N’,
// your task is to find the total number of unique paths from the cell MATRIX[0][0]
// to MATRIX['M' - 1]['N' - 1].

// Example:
// Input:  2 2
// Output: 2

#include <bits/stdc++.h>
using namespace std;

// memoization top down
int solve_m(int row, int col, int &m, int &n, vector<vector<int>> &dp)
{
    if ((row == 0) && (col == 0))
    {
        return 1;
    }

    if ((row < 0) || (col < 0))
    {
        return 0;
    }

    if (dp[row][col] != -1)
    {
        return dp[row][col];
    }

    int up = solve_m(row - 1, col, m, n, dp);
    int left = solve_m(row, col - 1, m, n, dp);

    dp[row][col] = (up + left);
    return dp[row][col];
}

// tabulation bottom up
int solve_t(int &m, int &n, vector<vector<int>> &dp)
{
    dp[0][0] = 1;

    for (int row = 0; row < m; row++)
    {
        for (int col = 0; col < n; col++)
        {
            if ((row == 0) && (col == 0))
            {
                continue;
            }

            // no. of ways the above cell reaches the target
            int up = 0;
            if (row > 0)
            {
                up = dp[row - 1][col];
            }

            // no. of ways the left cell reaches the target
            int left = 0;
            if (col > 0)
            {
                left = dp[row][col - 1];
            }

            dp[row][col] = up + left;
        }
    }

    return dp[m - 1][n - 1];
}

// space optimized
int solve_so(int &m, int &n)
{
    vector<int> prev(n, 0);

    for (int row = 0; row < m; row++)
    {
        vector<int> curr(n, 0);
        for (int col = 0; col < n; col++)
        {
            if ((row == 0) && (col == 0))
            {
                curr[col] = 1;
                continue;
            }

            int up = prev[col];

            int left = 0;
            if (col > 0)
            {
                left = curr[col - 1];
            }

            curr[col] = up + left;
        }

        prev = curr;
    }

    return prev[n - 1];
}

int uniquePaths(int m, int n)
{
    // vector<vector<int>> dp(m, vector<int>(n, 0));

    return solve_so(m, n);
}
