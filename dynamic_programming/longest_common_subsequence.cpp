// Given two strings text1 and text2, return the length of their longest common subsequence. If there
// is no common subsequence, return 0.
// A subsequence of a string is a new string generated from the original string with some characters
// (can be none) deleted without changing the relative order of the remaining characters.
// For example, "ace" is a subsequence of "abcde".
// A common subsequence of two strings is a subsequence that is common to both strings.

// Example:
// Input:  text1 = "abc", text2 = "abc"
// Output: 3

#include <bits/stdc++.h>
using namespace std;

int solve_m(int i, int j, string &text1, string &text2, vector<vector<int>> &dp)
{
    if ((i < 0) || (j < 0))
    {
        return 0;
    }

    if (dp[i][j] != -1)
    {
        return dp[i][j];
    }

    if (text1[i] == text2[j])
    {
        dp[i][j] = solve_m(i - 1, j - 1, text1, text2, dp) + 1;
        return dp[i][j];
    }

    dp[i][j] = max(solve_m(i, j - 1, text1, text2, dp), solve_m(i - 1, j, text1, text2, dp));
    return dp[i][j];
}

// for tabulation we shift the index right by 1 to deal with -ve index
// i.e. 0 -> -1 && n -> n-1
int solve_t(int &t1_len, int &t2_len, string &text1, string &text2)
{
    vector<vector<int>> dp(t1_len + 1, vector<int>(t2_len + 1, 0));
    for (int i = 0; i <= t1_len; i++)
    {
        dp[i][0] = 0;
    }

    for (int i = 0; i <= t2_len; i++)
    {
        dp[0][i] = 0;
    }

    for (int i = 1; i <= t1_len; i++)
    {
        for (int j = 1; j <= t2_len; j++)
        {
            if (text1[i - 1] == text2[j - 1])
            {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            }
            else
            {
                dp[i][j] = max(dp[i][j - 1], dp[i - 1][j]);
            }
        }
    }

    // printing the lcs using dp table
    string lcs = "";
    int i = t1_len, j = t2_len;
    while ((i > 0) && (j > 0))
    {
        if (text1[i - 1] == text2[j - 1])
        {
            lcs = text1[i - 1] + lcs;
            i -= 1;
            j -= 1;
        }
        else if (dp[i][j - 1] > dp[i - 1][j])
        {
            j -= 1;
        }
        else
        {
            i -= 1;
        }
    }

    cout << lcs << endl;

    return dp[t1_len][t2_len];
}

int solve_so(int &t1_len, int &t2_len, string &text1, string &text2)
{
    vector<int> prev(t2_len + 1, 0), curr(t2_len + 1, 0);
    for (int i = 0; i <= t2_len; i++)
    {
        prev[i] = 0;
    }
    curr[0] = 0;

    for (int i = 1; i <= t1_len; i++)
    {
        for (int j = 1; j <= t2_len; j++)
        {
            if (text1[i - 1] == text2[j - 1])
            {
                curr[j] = 1 + prev[j - 1];
            }
            else
            {
                curr[j] = max(curr[j - 1], prev[j]);
            }
        }

        prev = curr;
    }

    return prev[t2_len];
}

int longestCommonSubsequence(string text1, string text2)
{
    int t1_len = text1.length();
    int t2_len = text2.length();

    // vector<vector<int>> dp(t1_len, vector<int>(t2_len, -1));
    // return solve_m(t1_len-1, t2_len-1, text1, text2, dp);

    return solve_t(t1_len, t2_len, text1, text2);
}
