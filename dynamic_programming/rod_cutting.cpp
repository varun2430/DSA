// Given a rod of length N inches and an array of prices, price[]. price[i] denotes the value of a piece
// of length i. Determine the maximum value obtainable by cutting up the rod and selling the pieces.
// Note: Consider 1-based indexing.

// Example:
// Input:  N = 8
//         price = [1, 5, 8, 9, 10, 17, 17, 20]
// Output: 22

#include <bits/stdc++.h>
using namespace std;

int solve_m(int index, int length, int price[], vector<vector<int>> &dp)
{
    if (index == 0)
    {
        return (length * price[0]);
    }

    if (dp[index][length] != -1)
    {
        return dp[index][length];
    }

    // here index+1 is the curr rod length
    int take = INT_MIN;
    if (index + 1 <= length)
    {
        take = solve_m(index, length - (index + 1), price, dp) + price[index];
    }

    int notTake = solve_m(index - 1, length, price, dp);

    dp[index][length] = max(take, notTake);
    return dp[index][length];
}

int solve_t(int n, int price[])
{
    vector<vector<int>> dp(n, vector<int>(n + 1, 0));

    for (int length = 0; length <= n; length++)
    {
        dp[0][length] = length * price[0];
    }

    for (int index = 1; index < n; index++)
    {
        for (int length = 0; length <= n; length++)
        {
            int take = INT_MIN;
            if (index + 1 <= length)
            {
                take = price[index] + dp[index][length - (index + 1)];
            }

            int notTake = 0 + dp[index - 1][length];

            dp[index][length] = max(take, notTake);
        }
    }

    return dp[n - 1][n];
}

int solve_so(int n, int price[])
{
    vector<int> prev(n + 1, 0), curr(n + 1, 0);

    for (int length = 0; length <= n; length++)
    {
        prev[length] = length * price[0];
    }

    for (int index = 1; index < n; index++)
    {
        for (int length = 0; length <= n; length++)
        {
            int take = INT_MIN;
            if (index + 1 <= length)
            {
                take = price[index] + curr[length - (index + 1)];
            }

            int notTake = 0 + prev[length];

            curr[length] = max(take, notTake);
        }

        prev = curr;
    }

    return prev[n];
}

int cutRod(int price[], int n)
{
    // vector<vector<int>> dp(n, vector<int>(n+1, -1));
    // return solve_m(n-1, n, price, dp);

    return solve_so(n, price);
}
