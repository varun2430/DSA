// Given a wooden stick of length n units. The stick is labelled from 0 to n. For example,
// a stick of length 6 is labelled as follows:

// Given an integer array cuts where cuts[i] denotes a position you should perform a cut at.

// You should perform the cuts in order, you can change the order of the cuts as you wish.

// The cost of one cut is the length of the stick to be cut, the total cost is the sum of
// costs of all cuts. When you cut a stick, it will be split into two smaller sticks (i.e.
// the sum of their lengths is the length of the stick before the cut). Please refer to the
// first example for a better explanation.

// Return the minimum total cost of the cuts.

// Example:
// Input:  n = 7, cuts = [1,3,4,5]
// Output: 16

#include <bits/stdc++.h>
using namespace std;

int solve_m(int i, int j, vector<int> &cuts, vector<vector<int>> &dp)
{
    if (i > j)
    {
        return 0;
    }

    if (dp[i][j] != -1)
    {
        return dp[i][j];
    }

    int min_cost = INT_MAX;

    for (int index = i; index <= j; index++)
    {
        int cost = cuts[j + 1] - cuts[i - 1] +
                   solve_m(i, index - 1, cuts, dp) +
                   solve_m(index + 1, j, cuts, dp);

        min_cost = min(min_cost, cost);
    }

    dp[i][j] = min_cost;
    return dp[i][j];
}

int solve_t(vector<int> &cuts)
{
    int c = cuts.size();

    // base case for all dp[i][j] where i > j set 0
    vector<vector<int>> dp(c, vector<int>(c, 0));

    for (int i = c - 2; i >= 1; i--)
    {
        for (int j = i; j <= c - 2; j++)
        {
            int min_cost = INT_MAX;
            for (int index = i; index <= j; index++)
            {
                int cost = cuts[j + 1] - cuts[i - 1] +
                           dp[i][index - 1] +
                           dp[index + 1][j];

                min_cost = min(min_cost, cost);
            }

            dp[i][j] = min_cost;
        }
    }

    return dp[1][c - 2];
}

int minCost(int n, vector<int> &cuts)
{
    int c = cuts.size();

    // add 0 and n to cuts and sort to help find length of current stick segment at each step
    cuts.insert(cuts.begin(), 0);
    cuts.push_back(n);
    sort(cuts.begin(), cuts.end());

    // vector<vector<int>> dp(c+1, vector<int>(c+1, -1));
    // return solve_m(1, c, cuts, dp);

    return solve_t(cuts);
}
