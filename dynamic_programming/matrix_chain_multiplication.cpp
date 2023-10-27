// Given a sequence of matrices, find the most efficient way to multiply these matrices
// together. The efficient way is the one that involves the least number of multiplications.

// The dimensions of the matrices are given in an array arr[] of size N (such that N =
// number of matrices + 1) where the ith matrix has the dimensions (arr[i-1] x arr[i]).

// Example:
// Input:  N = 5  arr = {40, 20, 30, 10, 30}
// Output: 26000

#include <bits/stdc++.h>
using namespace std;

int solve_m(int i, int j, int arr[], vector<vector<int>> &dp)
{
    if (i == j)
    {
        return 0;
    }

    if (dp[i][j] != -1)
    {
        return dp[i][j];
    }

    int min_steps = INT_MAX;

    // explore all possible combination of dividing matrixes in i and j into two groups
    for (int k = i; k < j; k++)
    {
        int steps = (arr[i - 1] * arr[k] * arr[j]) + solve_m(i, k, arr, dp) + solve_m(k + 1, j, arr, dp);
        min_steps = min(min_steps, steps);
    }

    dp[i][j] = min_steps;
    return dp[i][j];
}

int solve_t(int &N, int arr[])
{
    vector<vector<int>> dp(N, vector<int>(N));

    // base case
    for (int i = 1; i < N; i++)
    {
        dp[i][i] = 0;
    }

    for (int i = N - 1; i >= 1; i--)
    {
        for (int j = i + 1; j < N; j++)
        {
            int min_steps = INT_MAX;

            for (int k = i; k < j; k++)
            {
                int steps = (arr[i - 1] * arr[k] * arr[j]) + dp[i][k] + dp[k + 1][j];
                min_steps = min(min_steps, steps);
            }

            dp[i][j] = min_steps;
        }
    }

    return dp[1][N - 1];
}

int matrixMultiplication(int N, int arr[])
{
    // vector<vector<int>> dp(N, vector<int>(N, -1));
    // return solve_m(1, N-1, arr, dp);

    return solve_t(N, arr);
}
