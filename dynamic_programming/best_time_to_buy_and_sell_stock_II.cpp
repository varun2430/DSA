// You are given an integer array prices where prices[i] is the price of a given stock on
// the ith day.
// On each day, you may decide to buy and/or sell the stock. You can only hold at most one
// share of the stock at any time. However, you can buy it then immediately sell it on the
// same day.
// Find and return the maximum profit you can achieve.

// Example:
// Input:  prices = [1,2,3,4,5]
// Output: 4

#include <bits/stdc++.h>
using namespace std;

int solve_m(int index, int buy, int &n, vector<int> &prices, vector<vector<int>> &dp)
{
    if (index == n)
    {
        return 0;
    }

    if (dp[index][buy] != -1)
    {
        return dp[index][buy];
    }

    int profit = 0;

    // buy == 1 means we dont currently hold a stock and can buy or skip
    // buy == 0 means we currently hold a stock and can sell or skip
    if (buy == 1)
    {
        int buyStock = -prices[index] + solve_m(index + 1, 0, n, prices, dp);
        int skip = 0 + solve_m(index + 1, 1, n, prices, dp);

        profit = max(buyStock, skip);
    }
    else
    {
        int sellStock = prices[index] + solve_m(index + 1, 1, n, prices, dp);
        int skip = 0 + solve_m(index + 1, 0, n, prices, dp);

        profit = max(sellStock, skip);
    }

    dp[index][buy] = profit;
    return dp[index][buy];
}

int solve_t(int &n, vector<int> &prices)
{
    vector<vector<int>> dp(n + 1, vector<int>(2));

    dp[n][0] = 0;
    dp[n][1] = 0;

    for (int index = n - 1; index >= 0; index--)
    {
        for (int buy = 0; buy <= 1; buy++)
        {
            int profit = 0;

            if (buy == 1)
            {
                int buyStock = -prices[index] + dp[index + 1][0];
                int skip = 0 + dp[index + 1][1];

                profit = max(buyStock, skip);
            }
            else
            {
                int sellStock = prices[index] + dp[index + 1][1];
                int skip = 0 + dp[index + 1][0];

                profit = max(sellStock, skip);
            }

            dp[index][buy] = profit;
        }
    }

    return dp[0][1];
}

int solve_so(int &n, vector<int> &prices)
{
    vector<int> prev(2), curr(2);

    prev[0] = 0;
    prev[1] = 0;

    for (int index = n - 1; index >= 0; index--)
    {
        for (int buy = 0; buy <= 1; buy++)
        {
            int profit = 0;

            if (buy == 1)
            {
                int buyStock = -prices[index] + prev[0];
                int skip = 0 + prev[1];

                profit = max(buyStock, skip);
            }
            else
            {
                int sellStock = prices[index] + prev[1];
                int skip = 0 + prev[0];

                profit = max(sellStock, skip);
            }

            curr[buy] = profit;
        }

        prev = curr;
    }

    return prev[1];
}

int maxProfit(vector<int> &prices)
{
    int n = prices.size();

    // vector<vector<int>> dp(n+1, vector<int>(2, -1));
    // return solve_m(0, 1, n, prices, dp);

    return solve_so(n, prices);
}
