// You have been given an N*M matrix filled with integer numbers, find the maximum sum that
// can be obtained from a path starting from any cell in the first row to any cell in the
// last row. From a cell in a row, you can move to another cell directly below that row,
// or diagonally below left or right. So from a particular cell (row, col), we can move in
// three directions

// Example:
// Input:  4 4
//         1 2 10 4
//         100 3 2 1
//         1 1 20 2
//         1 2 2 1
// Output: 105

#include <bits/stdc++.h>
using namespace std;

int solve_m(int row, int col, vector<vector<int>> &matrix, vector<vector<int>> &dp)
{
    if ((col < 0) || (col >= matrix[0].size()))
    {
        return -1e9;
    }

    if (row == 0)
    {
        return matrix[row][col];
    }

    if (dp[row][col] != -1)
    {
        return dp[row][col];
    }

    int up = matrix[row][col] + solve_m(row - 1, col, matrix, dp);
    int dl = matrix[row][col] + solve_m(row - 1, col - 1, matrix, dp);
    int dr = matrix[row][col] + solve_m(row - 1, col + 1, matrix, dp);

    dp[row][col] = max(up, max(dl, dr));
    return dp[row][col];
}

int solve_t(int n, int m, vector<vector<int>> &matrix, vector<vector<int>> &dp)
{
    for (int col = 0; col < m; col++)
    {
        dp[0][col] = matrix[0][col];
    }

    for (int row = 1; row < n; row++)
    {
        for (int col = 0; col < m; col++)
        {
            int up = matrix[row][col] + dp[row - 1][col];

            int dl = matrix[row][col];
            if (col - 1 >= 0)
            {
                dl += dp[row - 1][col - 1];
            }
            else
            {
                dl = -1e9;
            }

            int dr = matrix[row][col];
            if (col + 1 < m)
            {
                dr += dp[row - 1][col + 1];
            }
            else
            {
                dr = -1e9;
            }

            dp[row][col] = max(up, max(dl, dr));
        }
    }

    int maxSum = INT_MIN;
    for (int col = 0; col < m; col++)
    {
        maxSum = max(maxSum, dp[n - 1][col]);
    }

    return maxSum;
}

int solve_so(int n, int m, vector<vector<int>> &matrix)
{
    vector<int> prev(m);
    for (int col = 0; col < m; col++)
    {
        prev[col] = matrix[0][col];
    }

    for (int row = 1; row < n; row++)
    {
        vector<int> curr(m);
        for (int col = 0; col < m; col++)
        {
            int up = matrix[row][col] + prev[col];

            int dl = matrix[row][col];
            if (col - 1 >= 0)
            {
                dl += prev[col - 1];
            }
            else
            {
                dl = -1e9;
            }

            int dr = matrix[row][col];
            if (col + 1 < m)
            {
                dr += prev[col + 1];
            }
            else
            {
                dr = -1e9;
            }

            curr[col] = max(up, max(dl, dr));
        }

        prev = curr;
    }

    int maxSum = INT_MIN;
    for (int col = 0; col < m; col++)
    {
        maxSum = max(maxSum, prev[col]);
    }

    return maxSum;
}

int getMaxPathSum(vector<vector<int>> &matrix)
{
    int n = matrix.size();
    int m = matrix[0].size();

    // vector<vector<int>> dp(n, vector<int>(m, -1));

    // int maxSum = INT_MIN;
    // for(int col=0 ; col < m ; col++)
    // {
    //     maxSum = max(maxSum, solve_m(n-1, col, matrix, dp));
    // }

    return solve_so(n, m, matrix);
}
