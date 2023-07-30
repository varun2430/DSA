// Given two strings. The task is to find the length of the longest common substring.

// Example:
// Input:  text1 = "ABCDGH", text2 = "ACDGHR"
// Output: 4

#include <bits/stdc++.h>
using namespace std;

int solve_m(int i, int j, int count, string &s1, string &s2)
{
    if ((i == -1) || (j == -1))
    {
        return count;
    }

    if (s1[i] == s2[j])
    {
        count = solve_m(i - 1, j - 1, count + 1, s1, s2);
    }

    count = max(count, max(solve_m(i, j - 1, 0, s1, s2), solve_m(i - 1, j, 0, s1, s2)));
    return count;
}

// here we shift the index right by 1 to deal with -ve index
// i.e. 0 -> -1 && n -> n-1
int solve_t(int &s1_len, int &s2_len, string &s1, string &s2)
{
    vector<vector<int>> dp(s1_len + 1, vector<int>(s2_len + 1, 0));

    for (int i = 0; i <= s1_len; i++)
    {
        dp[i][0] = 0;
    }

    for (int i = 0; i <= s2_len; i++)
    {
        dp[0][i] = 0;
    }

    int maxLen = 0;
    for (int i = 1; i <= s1_len; i++)
    {
        for (int j = 1; j <= s2_len; j++)
        {
            if (s1[i - 1] == s2[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                maxLen = max(maxLen, dp[i][j]);
            }
            else
            {
                dp[i][j] = 0;
            }
        }
    }

    return maxLen;
}

int solve_so(int &s1_len, int &s2_len, string &s1, string &s2)
{
    vector<int> prev(s2_len + 1, 0), curr(s2_len + 1, 0);

    for (int i = 0; i <= s2_len; i++)
    {
        prev[i] = 0;
    }

    curr[0] = 0;

    int maxLen = 0;
    for (int i = 1; i <= s1_len; i++)
    {
        for (int j = 1; j <= s2_len; j++)
        {
            if (s1[i - 1] == s2[j - 1])
            {
                curr[j] = prev[j - 1] + 1;
                maxLen = max(maxLen, curr[j]);
            }
            else
            {
                curr[j] = 0;
            }
        }

        prev = curr;
    }

    return maxLen;
}

int longestCommonSubstr(string S1, string S2, int n, int m)
{
    int s1_len = S1.length();
    int s2_len = S2.length();

    return solve_so(s1_len, s2_len, S1, S2);
}
