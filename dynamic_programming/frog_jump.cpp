// There is a frog on the '1st' step of an 'N' stairs long staircase. The frog wants
// to reach the 'Nth' stair. 'HEIGHT[i]' is the height of the '(i+1)th' stair.
// If Frog jumps from 'ith' to 'jth' stair, the energy lost in the jump is given by
// absolute value of ( HEIGHT[i-1] - HEIGHT[j-1] ). If the Frog is on 'ith' staircase,
// he can jump either to '(i+1)th' stair or to '(i+2)th' stair. Your task is to find
// the minimum total energy used by the frog to reach from '1st' stair to 'Nth' stair.

// Example:
// Input: n=5, heights=[10, 20, 30, 10]
// Output: 20

#include <bits/stdc++.h>
using namespace std;

// memoization top down
int solve_m(int step, vector<int> &heights, vector<int> &dp)
{
    if (step == 0)
    {
        return 0;
    }

    if (dp[step] != -1)
    {
        return dp[step];
    }

    int oneStep = solve_m(step - 1, heights, dp) + abs(heights[step] - heights[step - 1]);

    int twoStep = INT_MAX;
    if (step > 1)
    {
        twoStep = solve_m(step - 2, heights, dp) + abs(heights[step] - heights[step - 2]);
    }

    dp[step] = min(oneStep, twoStep);
    return dp[step];
}

// tabulation bottom up
int solve_t(int step, vector<int> &heights, vector<int> &dp)
{
    dp[0] = 0;

    for (int i = 1; i <= step; i++)
    {
        int oneStep = dp[i - 1] + abs(heights[i - 1] - heights[i]);

        int twoStep = INT_MAX;
        if (i > 1)
        {
            twoStep = dp[i - 2] + abs(heights[i - 2] - heights[i]);
        }

        dp[i] = min(oneStep, twoStep);
    }

    return dp[step];
}

// space optimized
int solve_so(int step, vector<int> &heights)
{
    int prev1 = 0; // best option one step back
    int prev2 = 0; // best option two step back

    for (int i = 1; i <= step; i++)
    {
        int oneStep = prev1 + abs(heights[i - 1] - heights[i]);

        int twoStep = INT_MAX;
        if (i > 1)
        {
            twoStep = prev2 + abs(heights[i - 2] - heights[i]);
        }

        prev2 = prev1;
        prev1 = min(oneStep, twoStep);
    }

    return prev1;
}

int frogJump(int n, vector<int> &heights)
{
    // vector<int> dp(n, -1);

    return solve_so(n - 1, heights);
}
