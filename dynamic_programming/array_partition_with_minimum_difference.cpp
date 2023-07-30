// You are given an array 'arr' containing non-negative integers.
// Your task is to partition this array into two subsets such that the absolute difference
// between subset sums is minimum.
// You just need to find the minimum absolute difference considering any valid division of
// the array elements.

// Example:
// Input:  1 2 3 4
// Output: 0

#include <bits/stdc++.h>
using namespace std;

// tabulation bottom up
int solve_t(int &sum, int &n, vector<int> &arr)
{
    vector<vector<bool>> dp(n, vector<bool>(sum + 1, false));
    for (int i = 0; i < n; i++)
    {
        dp[i][0] = true;
    }

    if (arr[0] <= sum)
    {
        dp[0][arr[0]] = true;
    }

    for (int index = 1; index < n; index++)
    {
        for (int target = 1; target <= sum; target++)
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

    int minDiff = INT_MAX;
    for (int target = 1; target <= sum; target++)
    {
        if (dp[n - 1][target] == true)
        {
            int s1 = target;
            int s2 = sum - target;

            minDiff = min(minDiff, abs(s1 - s2));
        }
    }

    return minDiff;
}

// space optimized bottom up
int solve_so(int &sum, int &n, vector<int> &arr)
{
    vector<bool> prev(sum + 1, false);
    prev[0] = true;

    if (arr[0] <= sum)
    {
        prev[arr[0]] = true;
    }

    for (int index = 1; index < n; index++)
    {
        vector<bool> curr(sum + 1, false);
        curr[0] = true;

        for (int target = 1; target <= sum; target++)
        {
            bool take = false;
            if (arr[index] <= target)
            {
                take = prev[target - arr[index]];
            }

            bool notTake = prev[target];

            curr[target] = take || notTake;
        }

        prev = curr;
    }

    int minDiff = INT_MAX;
    for (int target = 1; target <= sum / 2; target++)
    {
        if (prev[target] == true)
        {
            int s1 = target;
            int s2 = sum - target;

            minDiff = min(minDiff, abs(s1 - s2));
        }
    }

    return minDiff;
}

int minSubsetSumDifference(vector<int> &arr, int n)
{
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += arr[i];
    }

    return solve_so(sum, n, arr);
}
