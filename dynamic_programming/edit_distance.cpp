// Given two strings word1 and word2, return the minimum number of operations required to
// convert word1 to word2.
// You have the following three operations permitted on a word:
//  Insert a character
//  Delete a character
//  Replace a character

// Example:
// Input:  word1 = "intention", word2 = "execution"
// Output: 5

#include <bits/stdc++.h>
using namespace std;

int solve_m(int i, int j, string &s1, string &s2, vector<vector<int>> &dp)
{
    // we exaust given string
    if (i < 0)
    {
        return (j + 1);
    }

    // we exaust required string
    if (j < 0)
    {
        return (i + 1);
    }

    if (dp[i][j] != -1)
    {
        return dp[i][j];
    }

    if (s1[i] == s2[j])
    {
        dp[i][j] = solve_m(i - 1, j - 1, s1, s2, dp) + 0;
        return dp[i][j];
    }

    int insert = solve_m(i, j - 1, s1, s2, dp) + 1;
    int deletion = solve_m(i - 1, j, s1, s2, dp) + 1;
    int replace = solve_m(i - 1, j - 1, s1, s2, dp) + 1;

    dp[i][j] = min(min(insert, deletion), replace);
    return dp[i][j];
}

// for tabulation we shift the index right by 1 to deal with -ve index
// i.e. 0 -> -1 && n -> n-1
int solve_t(int &n, int &m, string &s1, string &s2)
{
    vector<vector<int>> dp(n + 1, vector<int>(m + 1));

    for (int i = 0; i <= n; i++)
    {
        dp[i][0] = i;
    }

    for (int j = 0; j <= m; j++)
    {
        dp[0][j] = j;
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (s1[i - 1] == s2[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1] + 0;
            }
            else
            {
                int insert = dp[i][j - 1] + 1;
                int deletion = dp[i - 1][j] + 1;
                int replace = dp[i - 1][j - 1] + 1;

                dp[i][j] = min(min(insert, deletion), replace);
            }
        }
    }

    return dp[n][m];
}

int solve_so(int &n, int &m, string &s1, string &s2)
{
    vector<int> prev(m + 1), curr(m + 1);

    for (int j = 0; j <= m; j++)
    {
        prev[j] = j;
    }

    for (int i = 1; i <= n; i++)
    {
        curr[0] = i;
        for (int j = 1; j <= m; j++)
        {
            if (s1[i - 1] == s2[j - 1])
            {
                curr[j] = prev[j - 1] + 0;
            }
            else
            {
                int insert = curr[j - 1] + 1;
                int deletion = prev[j] + 1;
                int replace = prev[j - 1] + 1;

                curr[j] = min(min(insert, deletion), replace);
            }
        }

        prev = curr;
    }

    return prev[m];
}

int minDistance(string word1, string word2)
{
    int n = word1.length();
    int m = word2.length();

    // vector<vector<int>> dp(n, vector<int>(m, -1));
    // return solve_m(n-1, m-1, word1, word2, dp);

    return solve_so(n, m, word1, word2);
}
