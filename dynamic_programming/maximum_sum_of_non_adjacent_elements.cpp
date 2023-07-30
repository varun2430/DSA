// You are given an array/list of N integers. You are supposed to return
// the maximum sum of the subsequence with the constraint that no two
// elements are adjacent in the given array/list.

// Example:
// Input:  9
//         1 2 3 1 3 5 8 1 9
// Output: 24

#include <bits/stdc++.h>
using namespace std;

// memoization top down
int solve_m(int index, vector<int> &nums, vector<int> &dp)
{
    if (index < 0)
    {
        return 0;
    }

    if (dp[index] != -1)
    {
        return dp[index];
    }

    int pick = nums[index] + solve_m(index - 2, nums, dp);
    int notPick = 0 + solve_m(index - 1, nums, dp);

    dp[index] = max(pick, notPick);
    return dp[index];
}

// tabulation bottom up
int solve_t(int index, vector<int> &nums, vector<int> &dp)
{
    // for index 0 we always pick nums[0]
    dp[0] = nums[0];

    for (int i = 1; i <= index; i++)
    {
        int pick = nums[i] + ((i > 1) ? dp[i - 2] : 0);
        int notPick = 0 + dp[i - 1];

        // store the best sum for range 0...i in dp[i]
        dp[i] = max(pick, notPick);
    }

    return dp[index];
}

// space optimized
int solve_so(int index, vector<int> &nums)
{
    int prev1 = nums[0]; // store the best sum for range 0...i-1
    int prev2 = 0;       // store the best sum for range 0...i-2

    for (int i = 1; i <= index; i++)
    {
        int pick = nums[i] + ((i > 1) ? prev2 : 0);
        int notPick = 0 + prev1;

        prev2 = prev1;
        prev1 = max(pick, notPick);
    }

    return prev1;
}

int maximumNonAdjacentSum(vector<int> &nums)
{
    int n = nums.size();

    // vector<int> dp(n, -1);

    return solve_so(n - 1, nums);
}
