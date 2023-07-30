// There are N stones, numbered 1,2,…,N. For each i (1≤i≤N), the height of Stone i is hi.
// There is a frog who is initially on Stone 1. He will repeat the following action some
// number of times to reach Stone N:If the frog is currently on Stone i, jump to one of
// the following: Stone i+1,i+2,…,i+K. Here, a cost of abs(hi - hj) is incurred,
// where j is the stone to land on. Find the minimum possible total cost incurred before
// the frog reaches Stone N.

// Example:
// Input:   5 3
//          10 30 40 50 20
// Output: 30

#include <bits/stdc++.h>
using namespace std;

// memoization top down
int solve_m(int step, int &k, vector<int> &heights, vector<int> &dp)
{
    if (step == 0)
    {
        return 0;
    }

    if (dp[step] != -1)
    {
        return dp[step];
    }

    int minCost = INT_MAX;
    for (int i = 1; i <= k; i++)
    {
        if (step - i >= 0)
        {
            int currCost = solve_m(step - i, k, heights, dp) + abs(heights[step] - heights[step - i]);
            minCost = min(minCost, currCost);
        }
    }

    dp[step] = minCost;
    return dp[step];
}

// tabulation bottom up
int solve_t(int step, int &k, vector<int> &heights, vector<int> &dp)
{
    dp[0] = 0;

    for (int i = 1; i <= step; i++)
    {
        int minCost = INT_MAX;
        for (int j = 1; j <= k; j++)
        {
            if (i - j >= 0)
            {
                int currCost = dp[i - j] + abs(heights[i] - heights[i - j]);
                minCost = min(minCost, currCost);
            }
        }

        dp[i] = minCost;
    }

    return dp[step];
}

// space optimized
int solve_so(int step, int &k, vector<int> &heights)
{
    vector<int> prev(k, INT_MAX); // store best option for prev k steps
    prev[0] = 0;

    for (int i = 1; i <= step; i++)
    {
        int minCost = INT_MAX;
        for (int j = 1; j <= k; j++)
        {
            if (i - j >= 0)
            {
                int currCost = prev[(i - j) % k] + abs(heights[i] - heights[i - j]);
                minCost = min(minCost, currCost);
            }
        }

        prev[i % k] = minCost;
    }

    return prev[step % k];
}
