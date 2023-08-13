// You are given an array prices where prices[i] is the price of a given stock on the ith
// day.
// Find the maximum profit you can achieve. You may complete at most two transactions.
// Note: You may not engage in multiple transactions simultaneously (i.e., you must sell
// the stock before you buy again).

// Example:
// Input:  prices = [1,2,3,4,5]
// Output: 4

#include <bits/stdc++.h>
using namespace std;

int solve_m(int index, int buy, int count, int &n, vector<int> &prices, vector<vector<vector<int>>> &dp)
{
    // count is used to track the no. of buy-sell transactions that have occured
    if ((index == n) || (count == 0))
    {
        return 0;
    }

    if (dp[index][buy][count] != -1)
    {
        return dp[index][buy][count];
    }

    int profit = 0;

    // buy == 1 means we dont currently hold a stock and can buy or skip
    // buy == 0 means we currently hold a stock and can sell or skip
    if (buy == 1)
    {
        int buyStock = -prices[index] + solve_m(index + 1, 0, count, n, prices, dp);
        int skip = 0 + solve_m(index + 1, 1, count, n, prices, dp);

        profit = max(buyStock, skip);
    }
    else
    {
        int sellStock = prices[index] + solve_m(index + 1, 1, count - 1, n, prices, dp);
        int skip = 0 + solve_m(index + 1, 0, count, n, prices, dp);

        dp[index][buy][count] = max(sellStock, skip);
        return dp[index][buy][count];
    }

    return profit;
}

int solve_t(int &transactions, int &n, vector<int> &prices)
{
    vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(2, vector<int>(transactions + 1)));

    for (int index = 0; index <= n; index++)
    {
        for (int buy = 0; buy <= 1; buy++)
        {
            dp[index][buy][0] = 0;
        }
    }

    for (int buy = 0; buy <= 1; buy++)
    {
        for (int count = 1; count <= transactions; count++)
        {
            dp[n][buy][count] = 0;
        }
    }

    for (int index = n - 1; index >= 0; index--)
    {
        for (int buy = 0; buy <= 1; buy++)
        {
            for (int count = 1; count <= transactions; count++)
            {
                int profit = 0;

                if (buy == 1)
                {
                    int buyStock = -prices[index] + dp[index + 1][0][count];
                    int skip = 0 + dp[index + 1][1][count];

                    profit = max(buyStock, skip);
                }
                else
                {
                    int sellStock = prices[index] + dp[index + 1][1][count - 1];
                    int skip = 0 + dp[index + 1][0][count];

                    profit = max(sellStock, skip);
                }

                dp[index][buy][count] = profit;
            }
        }
    }

    return dp[0][1][transactions];
}

int solve_so(int &transactions, int &n, vector<int> &prices)
{
    vector<vector<int>> prev(2, vector<int>(transactions + 1)), curr(2, vector<int>(transactions + 1));

    for (int buy = 0; buy <= 1; buy++)
    {
        prev[buy][0] = 0;
        curr[buy][0] = 0;
    }

    for (int buy = 0; buy <= 1; buy++)
    {
        for (int count = 1; count <= transactions; count++)
        {
            prev[buy][count] = 0;
        }
    }

    for (int index = n - 1; index >= 0; index--)
    {
        for (int buy = 0; buy <= 1; buy++)
        {
            for (int count = 1; count <= transactions; count++)
            {
                int profit = 0;

                if (buy == 1)
                {
                    int buyStock = -prices[index] + prev[0][count];
                    int skip = 0 + prev[1][count];

                    profit = max(buyStock, skip);
                }
                else
                {
                    int sellStock = prices[index] + prev[1][count - 1];
                    int skip = 0 + prev[0][count];

                    profit = max(sellStock, skip);
                }

                curr[buy][count] = profit;
            }

            prev = curr;
        }
    }

    return prev[1][transactions];
}

int maxProfit(vector<int> &prices)
{
    int n = prices.size();
    int transactions = 2;

    // vector<vector<vector<int>>> dp(n+1, vector<vector<int>>(2, vector<int>(transactions+1, -1)));
    // return solve_m(0, 1, transactions, n, prices, dp);

    return solve_so(transactions, n, prices);
}
