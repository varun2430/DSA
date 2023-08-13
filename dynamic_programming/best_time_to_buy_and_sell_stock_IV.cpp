// You are given an integer array prices where prices[i] is the price of a given stock on
// the ith day, and an integer k.
// Find the maximum profit you can achieve. You may complete at most k transactions: i.e.
// you may buy at most k times and sell at most k times.
// Note: You may not engage in multiple transactions simultaneously (i.e., you must sell
// the stock before you buy again).

// Example:
// Input:  k = 2, prices = [3,2,6,5,0,3]
// Output: 7

#include <bits/stdc++.h>
using namespace std;

int solve_m(int index, int transaction, int &k, int &n, vector<int> &prices, vector<vector<int>> &dp)
{
    // we multiply by 2 as in one transaction we buy and sell
    if ((index == n) || (transaction == 2 * k))
    {
        return 0;
    }

    if (dp[index][transaction] != -1)
    {
        return dp[index][transaction];
    }

    int profit = 0;

    // 0  1  2  3  4
    // B  S  B  S  B
    // we buy when transaction is even and sell when odd
    if (transaction % 2 == 0)
    {
        int buyStock = -prices[index] + solve_m(index + 1, transaction + 1, k, n, prices, dp);
        int skip = 0 + solve_m(index + 1, transaction, k, n, prices, dp);

        profit = max(buyStock, skip);
    }
    else
    {
        int sellStock = prices[index] + solve_m(index + 1, transaction + 1, k, n, prices, dp);
        int skip = 0 + solve_m(index + 1, transaction, k, n, prices, dp);

        profit = max(sellStock, skip);
    }

    dp[index][transaction] = profit;
    return dp[index][transaction];
}

int solve_t(int &k, int &n, vector<int> &prices)
{
    vector<vector<int>> dp(n + 1, vector<int>((2 * k) + 1));

    for (int transaction = 0; transaction <= 2 * k; transaction++)
    {
        dp[n][transaction] = 0;
    }

    for (int index = 0; index <= n; index++)
    {
        dp[index][2 * k] = 0;
    }

    for (int index = n - 1; index >= 0; index--)
    {
        for (int transaction = 0; transaction < 2 * k; transaction++)
        {
            int profit = 0;

            if (transaction % 2 == 0)
            {
                int buyStock = -prices[index] + dp[index + 1][transaction + 1];
                int skip = 0 + dp[index + 1][transaction];

                profit = max(buyStock, skip);
            }
            else
            {
                int sellStock = prices[index] + dp[index + 1][transaction + 1];
                int skip = 0 + dp[index + 1][transaction];

                profit = max(sellStock, skip);
            }

            dp[index][transaction] = profit;
        }
    }

    return dp[0][0];
}

int solve_so(int &k, int &n, vector<int> &prices)
{
    vector<int> prev((2 * k) + 1), curr((2 * k) + 1);

    for (int transaction = 0; transaction <= 2 * k; transaction++)
    {
        prev[transaction] = 0;
    }

    prev[2 * k] = 0;
    curr[2 * k] = 0;

    for (int index = n - 1; index >= 0; index--)
    {
        for (int transaction = 0; transaction < 2 * k; transaction++)
        {
            int profit = 0;

            if (transaction % 2 == 0)
            {
                int buyStock = -prices[index] + prev[transaction + 1];
                int skip = 0 + prev[transaction];

                profit = max(buyStock, skip);
            }
            else
            {
                int sellStock = prices[index] + prev[transaction + 1];
                int skip = 0 + prev[transaction];

                profit = max(sellStock, skip);
            }

            curr[transaction] = profit;
        }

        prev = curr;
    }

    return prev[0];
}

int maxProfit(int k, vector<int> &prices)
{
    int n = prices.size();

    // vector<vector<int>> dp(n+1, vector<int>((2*k)+1, -1));
    // return solve_m(0, 0, k, n, prices, dp);

    return solve_so(k, n, prices);
}
