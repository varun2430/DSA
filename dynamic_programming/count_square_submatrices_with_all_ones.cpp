// Given a m * n matrix of ones and zeros, return how many square submatrices have all ones.

// Example:
// Input:  matrix = [   [1,0,1],
//                     [1,1,0],
//                     [1,1,0] ]
// Output: 7

#include <bits/stdc++.h>
using namespace std;

int solve_t(vector<vector<int>> &matrix)
{
    int n = matrix.size();
    int m = matrix[0].size();

    vector<vector<int>> dp(n, vector<int>(m));

    int count = 0;

    // base case set first row & col same as input matrix
    // also count 1's encountered
    for (int i = 0; i < m; i++)
    {
        dp[0][i] = matrix[0][i];

        if (matrix[0][i] == 1)
        {
            count += 1;
        }
    }

    for (int i = 1; i < n; i++)
    {
        dp[i][0] = matrix[i][0];

        if (matrix[i][0] == 1)
        {
            count += 1;
        }
    }

    for (int i = 1; i < n; i++)
    {
        for (int j = 1; j < m; j++)
        {
            if (matrix[i][j] == 0)
            {
                dp[i][j] = 0;
            }
            else
            {
                dp[i][j] = min(dp[i - 1][j - 1], min(dp[i - 1][j], dp[i][j - 1])) + 1;
            }

            count += dp[i][j];
        }
    }

    return count;
}

int countSquares(vector<vector<int>> &matrix)
{
    return solve_t(matrix);
}