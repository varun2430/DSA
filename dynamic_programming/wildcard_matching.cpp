// Given an input string (s) and a pattern (p), implement wildcard pattern matching with
// support for '?' and '*' where:
//  '?' Matches any single character.
//  '*' Matches any sequence of characters (including the empty sequence).
// The matching should cover the entire input string (not partial).

// Example:
// Input:  s = "cb", p = "?a"
// Output: false

#include <bits/stdc++.h>
using namespace std;

bool solve_m(int i, int j, string &p, string &s, vector<vector<int>> &dp)
{
    // we exaust both pattern and req string
    if ((i < 0) && (j < 0))
    {
        return true;
    }

    // we exaust pattern before req string
    if ((i < 0) && (j >= 0))
    {
        return false;
    }

    // we exaust req string before pattern
    if ((i >= 0) && (j < 0))
    {
        for (int k = 0; k <= i; k++)
        {
            if (p[k] != '*')
            {
                return false;
            }
        }

        return true;
    }

    if (dp[i][j] != -1)
    {
        return dp[i][j];
    }

    if ((p[i] == s[j]) || (p[i] == '?'))
    {
        dp[i][j] = solve_m(i - 1, j - 1, p, s, dp);
        return dp[i][j];
    }

    if (p[i] == '*')
    {
        bool empty_seq = solve_m(i - 1, j, p, s, dp);
        bool any_seq = solve_m(i, j - 1, p, s, dp);

        dp[i][j] = empty_seq || any_seq;
        return dp[i][j];
    }

    return false;
}

// for tabulation we shift the index right by 1 to deal with -ve index
// i.e. 0 -> -1 && n -> n-1
bool solve_t(int &p_len, int &s_len, string &p, string &s)
{
    vector<vector<bool>> dp(p_len + 1, vector<bool>(s_len + 1));

    dp[0][0] = true;

    for (int j = 1; j <= s_len; j++)
    {
        dp[0][j] = false;
    }

    for (int i = 1; i <= p_len; i++)
    {
        bool flag = true;
        for (int k = 1; k <= i; k++)
        {
            if (p[k - 1] != '*')
            {
                flag = false;
                break;
            }
        }

        dp[i][0] = flag;
    }

    for (int i = 1; i <= p_len; i++)
    {
        for (int j = 1; j <= s_len; j++)
        {
            if ((p[i - 1] == s[j - 1]) || (p[i - 1] == '?'))
            {
                dp[i][j] = dp[i - 1][j - 1];
            }
            else if (p[i - 1] == '*')
            {
                bool empty_seq = dp[i - 1][j];
                bool any_seq = dp[i][j - 1];

                dp[i][j] = empty_seq || any_seq;
            }
            else
            {
                dp[i][j] = false;
            }
        }
    }

    return dp[p_len][s_len];
}

bool solve_so(int &p_len, int &s_len, string &p, string &s)
{
    vector<bool> prev(s_len + 1), curr(s_len + 1);

    prev[0] = true;

    for (int j = 1; j <= s_len; j++)
    {
        prev[j] = false;
    }

    for (int i = 1; i <= p_len; i++)
    {
        bool flag = true;
        for (int k = 1; k <= i; k++)
        {
            if (p[k - 1] != '*')
            {
                flag = false;
                break;
            }
        }

        curr[0] = flag;

        for (int j = 1; j <= s_len; j++)
        {
            if ((p[i - 1] == s[j - 1]) || (p[i - 1] == '?'))
            {
                curr[j] = prev[j - 1];
            }
            else if (p[i - 1] == '*')
            {
                bool empty_seq = prev[j];
                bool any_seq = curr[j - 1];

                curr[j] = empty_seq || any_seq;
            }
            else
            {
                curr[j] = false;
            }
        }

        prev = curr;
    }

    return prev[s_len];
}

bool isMatch(string s, string p)
{
    int p_len = p.length();
    int s_len = s.length();

    // vector<vector<int>> dp(p_len, vector<int>(s_len, -1));
    // return solve_m(p_len-1, s_len-1, p, s, dp);

    return solve_so(p_len, s_len, p, s);
}
