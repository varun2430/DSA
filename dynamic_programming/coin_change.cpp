// You are given an integer array coins representing coins of different denominations and an
// integer amount representing a total amount of money.
// Return the fewest number of coins that you need to make up that amount. If that amount of
// money cannot be made up by any combination of the coins, return -1.
// You may assume that you have an infinite number of each kind of coin.

// Example:
// Input:  coins = [1,2,5], amount = 11
// Output: 3

#include <bits/stdc++.h>
using namespace std;

int solve_m(int index, int sum, vector<int> &coins, vector<vector<int>> &dp)
{
    if (index == 0)
    {
        if (sum % coins[0] == 0)
        {
            return sum / coins[0];
        }

        return (int)1e9;
    }

    if (dp[index][sum] != -1)
    {
        return dp[index][sum];
    }

    int take = (int)1e9;
    if (coins[index] <= sum)
    {
        take = solve_m(index, sum - coins[index], coins, dp) + 1;
    }

    int notTake = solve_m(index - 1, sum, coins, dp) + 0;

    dp[index][sum] = min(take, notTake);
    return dp[index][sum];
}

int solve_t(int &n, int &amount, vector<int> &coins)
{
    vector<vector<int>> dp(n, vector<int>(amount + 1, 0));

    for (int sum = 0; sum <= amount; sum++)
    {
        // we can use the 0th coin only if we can form the amount needed
        if (sum % coins[0] == 0)
        {
            dp[0][sum] = sum / coins[0];
        }
        else
        {
            dp[0][sum] = (int)1e9;
        }
    }

    for (int index = 1; index < n; index++)
    {
        for (int sum = 0; sum <= amount; sum++)
        {
            int take = (int)1e9;
            if (coins[index] <= sum)
            {
                take = 1 + dp[index][sum - coins[index]];
            }

            int notTake = dp[index - 1][sum];

            dp[index][sum] = min(take, notTake);
        }
    }

    return dp[n - 1][amount];
}

int solve_so(int &n, int &amount, vector<int> &coins)
{
    vector<int> prev(amount + 1, 0), curr(amount + 1, 0);

    for (int sum = 0; sum <= amount; sum++)
    {
        // we can use the 0th coin only if we can form the amount needed
        if (sum % coins[0] == 0)
        {
            prev[sum] = sum / coins[0];
        }
        else
        {
            prev[sum] = (int)1e9;
        }
    }

    for (int index = 1; index < n; index++)
    {
        for (int sum = 0; sum <= amount; sum++)
        {
            int take = (int)1e9;
            if (coins[index] <= sum)
            {
                take = 1 + curr[sum - coins[index]];
            }

            int notTake = prev[sum];

            curr[sum] = min(take, notTake);
        }

        prev = curr;
    }

    return prev[amount];
}

int coinChange(vector<int> &coins, int amount)
{
    int n = coins.size();

    // vector<vector<int>> dp(n, vector<int>(amount+1, -1));
    // int res = solve_m(n-1, amount, coins, dp);

    int res = solve_so(n, amount, coins);

    if (res == (int)1e9)
    {
        return -1;
    }

    return res;
}