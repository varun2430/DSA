// Given an integer array nums, return true if you can partition the array into two subsets
// such that the sum of the elements in both subsets is equal or false otherwise.

// Example:
// Input:  [1,5,11,5]
// Output: true

#include <bits/stdc++.h>
using namespace std;

bool solve_m(int index, int target, vector<int> &nums, vector<vector<int>> &dp)
{
    if (target == 0)
    {
        return true;
    }

    if (index == 0)
    {
        if (nums[0] == target)
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
    if (nums[index] <= target)
    {
        take = solve_m(index - 1, target - nums[index], nums, dp);
    }

    bool notTake = solve_m(index - 1, target, nums, dp);

    dp[index][target] = take || notTake;
    return dp[index][target];
}

bool solve_t(int &target, int &n, vector<int> &nums)
{
    vector<vector<bool>> dp(n, vector<bool>(target + 1, false));

    for (int i = 0; i < n; i++)
    {
        dp[i][0] = true;
    }

    if (nums[0] <= target)
    {
        dp[0][nums[0]] = true; // only one true condition for index 0
    }

    for (int index = 1; index < n; index++)
    {
        for (int k = 1; k <= target; k++)
        {
            bool take = false;
            if (nums[index] <= k)
            {
                take = dp[index - 1][k - nums[index]];
            }

            bool notTake = dp[index - 1][k];

            dp[index][k] = take || notTake;
        }
    }

    return dp[n - 1][target];
}

bool solve_so(int &target, int &n, vector<int> &nums)
{
    vector<bool> prev(target + 1, false);
    prev[0] = true;

    if (nums[0] <= target)
    {
        prev[nums[0]] = true; // only one true condition for index 0
    }

    for (int index = 1; index < n; index++)
    {
        vector<bool> curr(target + 1, false);
        curr[0] = true;

        for (int k = 1; k <= target; k++)
        {
            bool take = false;
            if (nums[index] <= k)
            {
                take = prev[k - nums[index]];
            }

            bool notTake = prev[k];

            curr[k] = take || notTake;
        }

        prev = curr;
    }

    return prev[target];
}

// we have to find if there exist a subset with sum = total_sum / 2
bool canPartition(vector<int> &nums)
{
    int n = nums.size();

    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += nums[i];
    }

    // sum cannot be divided evenly so not possible to find two subsets
    // with equal sum
    if (sum % 2 != 0)
    {
        return false;
    }

    int target = sum / 2;

    // vector<vector<int>> dp(n, vector<int>(target+1, -1));

    return solve_so(target, n, nums);
}