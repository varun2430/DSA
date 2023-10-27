// Given an integer array nums, return the length of the longest strictly increasing
// subsequence.

// Example:
// Input:  nums = [10,9,2,5,3,7,101,18]
// Output: 4

#include <bits/stdc++.h>
using namespace std;

// here we shift the prev right by 1 to deal with -ve index
// by adding 1 to dp's column index
// i.e. 0 -> -1 && n -> n-1
int solve_m(int index, int prev, int &n, vector<int> &nums, vector<vector<int>> &dp)
{
    if (index == n)
    {
        return 0;
    }

    if (dp[index][prev + 1] != -1)
    {
        return dp[index][prev + 1];
    }

    int notTake = 0 + solve_m(index + 1, prev, n, nums, dp);

    int take = 0;
    if ((prev == -1) || (nums[index] > nums[prev]))
    {
        take = 1 + solve_m(index + 1, index, n, nums, dp);
    }

    dp[index][prev + 1] = max(notTake, take);
    return dp[index][prev + 1];
}

// here we shift the prev right by 1 to deal with -ve index
// by adding 1 to dp's column index
// i.e. 0 -> -1 && n -> n-1
int solve_t(int &n, vector<int> &nums)
{
    vector<vector<int>> dp(n + 1, vector<int>(n + 1));

    for (int prev = -1; prev < n; prev++)
    {
        dp[n][prev + 1] = 0;
    }

    for (int index = n - 1; index >= 0; index--)
    {
        for (int prev = index - 1; prev >= -1; prev--)
        {
            int notTake = 0 + dp[index + 1][prev + 1];

            int take = 0;
            if ((prev == -1) || (nums[index] > nums[prev]))
            {
                take = 1 + dp[index + 1][index + 1];
            }

            dp[index][prev + 1] = max(notTake, take);
        }
    }

    return dp[0][-1 + 1];
}

int solve_so(int &n, vector<int> &nums)
{
    vector<int> next(n + 1), curr(n + 1);

    for (int prev = -1; prev < n; prev++)
    {
        next[prev + 1] = 0;
    }

    for (int index = n - 1; index >= 0; index--)
    {
        for (int prev = index - 1; prev >= -1; prev--)
        {
            int notTake = 0 + next[prev + 1];

            int take = 0;
            if ((prev == -1) || (nums[index] > nums[prev]))
            {
                take = 1 + next[index + 1];
            }

            curr[prev + 1] = max(notTake, take);
        }

        next = curr;
    }

    return next[-1 + 1];
}

int solve_t2(int &n, vector<int> &nums)
{
    // here dp[i] is the length of the lis that is formed from 0 to ith element
    vector<int> dp(n, 1);

    // we use m to back track and print the lis
    vector<int> m(n);

    int maxLen = INT_MIN;
    int lastIndex = 0;
    for (int index = 0; index < n; index++)
    {
        m[index] = index;

        for (int prev = 0; prev < index; prev++)
        {
            if ((nums[prev] < nums[index]) && (dp[prev] + 1 > dp[index]))
            {
                dp[index] = dp[prev] + 1;
                m[index] = prev;
            }
        }

        if (dp[index] > maxLen)
        {
            maxLen = dp[index];
            lastIndex = index;
        }
    }

    int index = lastIndex;
    vector<int> lis;
    lis.push_back(nums[index]);

    while (m[index] != index)
    {
        index = m[index];
        lis.push_back(nums[index]);
    }

    reverse(lis.begin(), lis.end());
    for (int &num : lis)
    {
        cout << num << " ";
    }
    cout << endl;

    return maxLen;
}

int solve_bs(int &n, vector<int> &nums)
{
    vector<int> tmp;
    tmp.push_back(nums[0]);

    int len = 1;
    for (int i = 1; i < n; i++)
    {
        if (nums[i] > tmp.back())
        {
            tmp.push_back(nums[i]);
            len += 1;
        }
        else
        {
            int index = lower_bound(tmp.begin(), tmp.end(), nums[i]) - tmp.begin();
            tmp[index] = nums[i];
        }
    }

    return len;
}

int lengthOfLIS(vector<int> &nums)
{
    int n = nums.size();

    // vector<vector<int>> dp(n, vector<int>(n+1, -1));
    // return solve_m(0, -1, n, nums, dp);

    // return solve_t2(n, nums);

    return solve_bs(n, nums);
}
