// You are given an array/list ‘ARR’ of ‘N’ positive integers and an integer ‘K’. Your task
// is to check if there exists a subset in ‘ARR’ with a sum equal to ‘K’.
// Note: Return true if there exists a subset with sum equal to ‘K’. Otherwise, return false.

// Example:
// Input:  5 4
//         2 5 1 6 7
// Output: false

#include <bits/stdc++.h>
using namespace std;

bool solve_m(int index, int target, vector<int> &arr, vector<vector<int>> &dp)
{
    if (target == 0)
    {
        return true;
    }

    if (index == 0)
    {
        if (arr[index] == target)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    if (dp[index][target] != -1)
    {
        return dp[index][target];
    }

    bool take = false;
    if (arr[index] <= target)
    {
        take = solve_m(index - 1, target - arr[index], arr, dp);
    }

    bool notTake = solve_m(index - 1, target, arr, dp);

    dp[index][target] = (take || notTake);
    return dp[index][target];
}

bool solve_t(int &n, int &k, vector<int> &arr)
{
    vector<vector<bool>> dp(n, vector<bool>(k + 1, false));

    for (int i = 0; i < n; i++)
    {
        dp[i][0] = true;
    }

    if (arr[0] <= k)
    {
        dp[0][arr[0]] = true;
    }

    for (int index = 1; index < n; index++)
    {
        for (int target = 1; target <= k; target++)
        {
            bool take = false;
            if (arr[index] <= target)
            {
                take = dp[index - 1][target - arr[index]];
            }

            bool notTake = dp[index - 1][target];

            dp[index][target] = take || notTake;
        }
    }

    return dp[n - 1][k];
}

bool subsetSumToK(int n, int k, vector<int> &arr)
{
    // vector<vector<int>> dp(n, vector<int>(k+1, -1));

    return solve_t(n, k, arr);
}
