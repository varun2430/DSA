// You are given an array arr of size n containing positive integers and a target sum k.
// Find the number of ways of selecting the elements from the array such that the sum of
// chosen elements is equal to the target 'k'.
// Find the number of ways of selecting the elements from the array such that the sum of
// chosen elements is equal to the target 'k'.

// Example:
// Input:  k=5, arr=[1 4 4 5]
// Output: 3

#include <bits/stdc++.h>
using namespace std;

#define MOD 1000000007

int solve_m(int index, int sum, vector<int> &arr, vector<vector<int>> &dp)
{
    if (index == 0)
    {
        // makes sure the 0 is also counted i.e. we can form a subset with and
        // without this 0 so return 2
        if ((sum == 0) && (arr[0] == 0))
        {
            return 2;
        }

        if ((sum == 0) || (arr[0] == sum))
        {
            return 1;
        }

        return 0;
    }

    if (dp[index][sum] != -1)
    {
        return dp[index][sum];
    }

    int take = 0;
    if (arr[index] <= sum)
    {
        take = solve_m(index - 1, sum - arr[index], arr, dp);
    }

    int notTake = solve_m(index - 1, sum, arr, dp);

    dp[index][sum] = take + notTake;
    dp[index][sum] %= MOD;

    return dp[index][sum];
}

int solve_t(int &n, int &k, vector<int> &arr)
{
    vector<vector<int>> dp(n, vector<int>(k + 1, 0));

    for (int i = 0; i < n; i++)
    {
        dp[i][0] = 1;

        if ((arr[0] == 0) && (i == 0))
        {
            dp[i][0] = 2;
        }
    }

    if ((arr[0] != 0) && (arr[0] <= k))
    {
        dp[0][arr[0]] = 1;
    }

    for (int index = 1; index < n; index++)
    {
        for (int sum = 0; sum <= k; sum++)
        {
            int take = 0;
            if (arr[index] <= sum)
            {
                take = dp[index - 1][sum - arr[index]];
            }

            int notTake = dp[index - 1][sum];

            dp[index][sum] = take + notTake;
            dp[index][sum] %= MOD;
        }
    }

    return dp[n - 1][k];
}

int solve_so(int &n, int &k, vector<int> &arr)
{
    vector<int> prev(k + 1, 0);

    if (arr[0] == 0)
    {
        prev[0] = 2;
    }
    else
    {
        prev[0] = 1;
    }

    if ((arr[0] != 0) && (arr[0] <= k))
    {
        prev[arr[0]] = 1;
    }

    for (int index = 1; index < n; index++)
    {
        vector<int> curr(k + 1, 0);
        curr[0] = 1;

        for (int sum = 0; sum <= k; sum++)
        {
            int take = 0;
            if (arr[index] <= sum)
            {
                take = prev[sum - arr[index]];
            }

            int notTake = prev[sum];

            curr[sum] = take + notTake;
            curr[sum] %= MOD;
        }

        prev = curr;
    }

    return prev[k];
}

int findWays(vector<int> &arr, int k)
{
    int n = arr.size();

    // vector<vector<int>> dp(n, vector<int>(k+1, -1));
    // return solve_m(n-1, k, arr, dp);

    return solve_so(n, k, arr);
}
