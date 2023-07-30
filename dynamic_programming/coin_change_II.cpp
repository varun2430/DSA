// You are given an integer array coins representing coins of different denominations and an
// integer amount representing a total amount of money.
// Return the number of combinations that make up that amount. If that amount of money cannot
// be made up by any combination of the coins, return 0.
// You may assume that you have an infinite number of each kind of coin.
// The answer is guaranteed to fit into a signed 32-bit integer.

// Example:
// Input:  amount = 5, coins = [1,2,5]
// Output: 4

#include <bits/stdc++.h>
using namespace std;

int solve_m(int index, int amount, vector<int> &coins, vector<vector<int>> &dp)
{
    if (index == 0)
    {
        if (amount % coins[0] == 0)
        {
            return 1;
        }

        return 0;
    }

    if (dp[index][amount] != -1)
    {
        return dp[index][amount];
    }

    int take = 0;
    if (coins[index] <= amount)
    {
        take = solve_m(index, amount - coins[index], coins, dp);
    }

    int notTake = solve_m(index - 1, amount, coins, dp);

    dp[index][amount] = take + notTake;
    return dp[index][amount];
}

int solve_t(int &n, int &amount, vector<int> &coins)
{
    vector<vector<int>> dp(n, vector<int>(amount + 1, 0));

    for (int sum = 0; sum <= amount; sum++)
    {
        if (sum % coins[0] == 0)
        {
            dp[0][sum] = 1;
        }
        else
        {
            dp[0][sum] = 0;
        }
    }

    for (int index = 1; index < n; index++)
    {
        for (int sum = 0; sum <= amount; sum++)
        {
            int take = 0;
            if (coins[index] <= sum)
            {
                take = dp[index][sum - coins[index]];
            }

            int notTake = dp[index - 1][sum];

            dp[index][sum] = take + notTake;
        }
    }

    return dp[n - 1][amount];
}

int solve_so(int &n, int &amount, vector<int> &coins)
{
    vector<int> prev(amount + 1, 0), curr(amount + 1, 0);

    for (int sum = 0; sum <= amount; sum++)
    {
        if (sum % coins[0] == 0)
        {
            prev[sum] = 1;
        }
        else
        {
            prev[sum] = 0;
        }
    }

    for (int index = 1; index < n; index++)
    {
        for (int sum = 0; sum <= amount; sum++)
        {
            int take = 0;
            if (coins[index] <= sum)
            {
                take = curr[sum - coins[index]];
            }

            int notTake = prev[sum];

            curr[sum] = take + notTake;
        }

        prev = curr;
    }

    return prev[amount];
}

int change(int amount, vector<int> &coins)
{
    int n = coins.size();

    // vector<vector<int>> dp(n, vector<int>(amount+1, -1));
    // return solve_m(n-1, amount, coins, dp);

    return solve_so(n, amount, coins);
}
