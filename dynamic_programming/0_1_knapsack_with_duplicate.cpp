// Given a set of N items, each with a weight and a value, represented by the array w[]
// and val[] respectively. Also, a knapsack with weight limit W.
// The task is to fill the knapsack in such a way that we can get the maximum profit.
// Return the maximum profit.
// Note: Each item can be taken any number of times.

// Example:
// Input: wMax = 8
//        w = [1, 3, 4, 5]
//        v = [1, 4, 5, 7]
// Output: 11

#include <bits/stdc++.h>
using namespace std;

int solve_m(int index, int maxWeight, int val[], int wt[], vector<vector<int>> &dp)
{
    // for the last remaining item return the value of maximum number of items that can be
    // returned
    if (index == 0)
    {
        return (maxWeight / wt[0]) * val[0];
    }

    if (dp[index][maxWeight] != -1)
    {
        return dp[index][maxWeight];
    }

    int take = INT_MIN;
    if (wt[index] <= maxWeight)
    {
        take = solve_m(index, maxWeight - wt[index], val, wt, dp) + val[index];
    }

    int notTake = solve_m(index - 1, maxWeight, val, wt, dp) + 0;

    dp[index][maxWeight] = max(take, notTake);
    return dp[index][maxWeight];
}

int solve_t(int &N, int &W, int val[], int wt[])
{
    vector<vector<int>> dp(N, vector<int>(W + 1, 0));

    for (int maxWeight = wt[0]; maxWeight <= W; maxWeight++)
    {
        dp[0][maxWeight] = (maxWeight / wt[0]) * val[0];
    }

    for (int index = 1; index < N; index++)
    {
        for (int maxWeight = 0; maxWeight <= W; maxWeight++)
        {
            int take = INT_MIN;
            if (wt[index] <= maxWeight)
            {
                take = val[index] + dp[index][maxWeight - wt[index]];
            }

            int notTake = 0 + dp[index - 1][maxWeight];

            dp[index][maxWeight] = max(take, notTake);
        }
    }

    return dp[N - 1][W];
}

int solve_so(int &N, int &W, int val[], int wt[])
{
    vector<int> prev(W + 1, 0), curr(W + 1, 0);

    for (int maxWeight = wt[0]; maxWeight <= W; maxWeight++)
    {
        prev[maxWeight] = (maxWeight / wt[0]) * val[0];
    }

    for (int index = 1; index < N; index++)
    {
        for (int maxWeight = 0; maxWeight <= W; maxWeight++)
        {
            int take = INT_MIN;
            if (wt[index] <= maxWeight)
            {
                take = val[index] + curr[maxWeight - wt[index]];
            }

            int notTake = 0 + prev[maxWeight];

            curr[maxWeight] = max(take, notTake);
        }

        prev = curr;
    }

    return prev[W];
}

int knapSack(int N, int W, int val[], int wt[])
{
    // vector<vector<int>> dp(N, vector<int>(W+1, -1));
    // return solve_m(N-1, W, val, wt, dp);

    return solve_so(N, W, val, wt);
}
