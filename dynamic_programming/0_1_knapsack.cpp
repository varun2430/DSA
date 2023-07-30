// A thief is robbing a store and can carry a maximal weight of W into his knapsack. There
// are N items and the ith item weighs wi and is of value vi. Considering the constraints
// of the maximum weight that a knapsack can carry, you have to find and return the maximum
// value that a thief can generate by stealing items.

// Example:
// Input: wMax = 5
//        w = [1 2 4 5]
//        v = [5 4 8 6]
// Output: 20

#include <bits/stdc++.h>
using namespace std;

int solve_m(int index, int maxWeight, vector<int> &value, vector<int> &weight, vector<vector<int>> &dp)
{
    if (index == 0)
    {
        if (weight[0] <= maxWeight)
        {
            return value[0];
        }

        return 0;
    }

    if (dp[index][maxWeight] != -1)
    {
        return dp[index][maxWeight];
    }

    int take = INT_MIN;
    if (weight[index] <= maxWeight)
    {
        take = solve_m(index - 1, maxWeight - weight[index], value, weight, dp) + value[index];
    }

    int notTake = 0 + solve_m(index - 1, maxWeight, value, weight, dp);

    dp[index][maxWeight] = max(take, notTake);
    return dp[index][maxWeight];
}

int solve_t(int &n, int &maxWeight, vector<int> &value, vector<int> &weight)
{
    vector<vector<int>> dp(n, vector<int>(maxWeight + 1, 0));

    // we can only pick the 0th item when the maxWeight allowd is >= weitht of the item
    for (int w = weight[0]; w <= maxWeight; w++)
    {
        dp[0][w] = value[0];
    }

    for (int index = 1; index < n; index++)
    {
        for (int w = 0; w <= maxWeight; w++)
        {
            int take = INT_MIN;
            if (weight[index] <= w)
            {
                take = dp[index - 1][w - weight[index]] + value[index];
            }

            int notTake = dp[index - 1][w] + 0;

            dp[index][w] = max(take, notTake);
        }
    }

    return dp[n - 1][maxWeight];
}

int solve_so(int &n, int &maxWeight, vector<int> &value, vector<int> &weight)
{
    vector<int> prev(maxWeight + 1, 0), curr(maxWeight + 1, 0);

    // we can only pick the 0th item when the maxWeight allowd is >= weitht of the item
    for (int w = weight[0]; w <= maxWeight; w++)
    {
        prev[w] = value[0];
    }

    for (int index = 1; index < n; index++)
    {
        // we can further reduce time complexity by filling in reverse order for the same row
        for (int w = 0; w <= maxWeight; w++)
        {
            int take = INT_MIN;
            if (weight[index] <= w)
            {
                take = prev[w - weight[index]] + value[index];
            }

            int notTake = prev[w] + 0;

            curr[w] = max(take, notTake);
        }

        prev = curr;
    }

    return prev[maxWeight];
}

int knapsack(vector<int> weight, vector<int> value, int n, int maxWeight)
{
    // vector<vector<int>> dp(n, vector<int>(maxWeight+1, -1));
    // return solve_m(n-1, maxWeight, value, weight, dp);

    return solve_so(n, maxWeight, value, weight);
}