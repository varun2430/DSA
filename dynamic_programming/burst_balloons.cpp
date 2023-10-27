// You are given n balloons, indexed from 0 to n - 1. Each balloon is painted with a number
// on it represented by an array nums. You are asked to burst all the balloons.

// If you burst the ith balloon, you will get nums[i - 1] * nums[i] * nums[i + 1] coins.
// If i - 1 or i + 1 goes out of bounds of the array, then treat it as if there is a balloon
// with a 1 painted on it.

// Return the maximum coins you can collect by bursting the balloons wisely.

// Example:
// Input:  nums = [3,1,5,8]
// Output: 167

#include <bits/stdc++.h>
using namespace std;

// as all selections are dependent on the adjacent selections, here we select balloons
// from last to first
int solve_m(int i, int j, vector<int> &nums, vector<vector<int>> &dp)
{
    if (i > j)
    {
        return 0;
    }

    if (dp[i][j] != -1)
    {
        return dp[i][j];
    }

    int max_coins = INT_MIN;
    for (int index = i; index <= j; index++)
    {
        int coins = nums[i - 1] * nums[index] * nums[j + 1] +
                    solve_m(i, index - 1, nums, dp) +
                    solve_m(index + 1, j, nums, dp);

        max_coins = max(max_coins, coins);
    }

    dp[i][j] = max_coins;
    return dp[i][j];
}

int solve_t(int &n, vector<int> &nums)
{
    // base case for all dp[i][j] where i > j set 0
    vector<vector<int>> dp(n, vector<int>(n, 0));

    for (int i = n - 2; i >= 1; i--)
    {
        for (int j = i; j <= n - 2; j++)
        {
            int max_coins = INT_MIN;
            for (int index = i; index <= j; index++)
            {
                int coins = nums[i - 1] * nums[index] * nums[j + 1] +
                            dp[i][index - 1] +
                            dp[index + 1][j];

                max_coins = max(max_coins, coins);
            }

            dp[i][j] = max_coins;
        }
    }

    return dp[1][n - 2];
}

int maxCoins(vector<int> &nums)
{
    nums.insert(nums.begin(), 1);
    nums.push_back(1);

    int n = nums.size();

    // vector<vector<int>> dp(n-1, vector<int>(n-1, -1));
    // return solve_m(1, n-2, nums, dp);

    return solve_t(n, nums);
}
