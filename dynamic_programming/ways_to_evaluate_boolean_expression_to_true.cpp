// You are given an expression exp  in the form of a string where operands will be : (TRUE
// or FALSE), and operators will be :  (AND, OR or XOR).
// Now you have to find the number of ways we can parenthesize the expression such that it
// will evaluate to TRUE.
// As the answer can be very large, return the output modulo 1000000007.

// Example:
// Input:  F|T^F
// Output: 2

#include <bits/stdc++.h>
using namespace std;

int MOD = 1000000007;

long long solve_m(int i, int j, int want_true, string &exp, vector<vector<vector<long long>>> &dp)
{
    if (i > j)
    {
        return 0;
    }

    if (i == j)
    {
        if (want_true == 1)
        {
            return (exp[i] == 'T') ? 1 : 0;
        }
        else
        {
            return (exp[i] == 'F') ? 1 : 0;
        }
    }

    if (dp[i][j][want_true] != -1)
    {
        return dp[i][j][want_true];
    }

    long long ways = 0;

    for (int index = i + 1; index <= j - 1; index += 2)
    {
        long long left_true = solve_m(i, index - 1, 1, exp, dp);
        long long left_false = solve_m(i, index - 1, 0, exp, dp);
        long long right_true = solve_m(index + 1, j, 1, exp, dp);
        long long right_false = solve_m(index + 1, j, 0, exp, dp);

        if (exp[index] == '&')
        {
            if (want_true == 1)
            {
                ways = (ways + (left_true * right_true) % MOD) % MOD;
            }
            else
            {
                ways = (ways + (left_true * right_false) % MOD + (left_false * right_false) % MOD + (left_false * right_true) % MOD) % MOD;
            }
        }
        else if (exp[index] == '|')
        {
            if (want_true == 1)
            {
                ways = (ways + (left_true * right_false) % MOD + (left_true * right_true) % MOD + (left_false * right_true) % MOD) % MOD;
            }
            else
            {
                ways = (ways + (left_false * right_false) % MOD) % MOD;
            }
        }
        else
        {
            if (want_true == 1)
            {
                ways = (ways + (left_true * right_false) % MOD + (left_false * right_true) % MOD) % MOD;
            }
            else
            {
                ways = (ways + (left_true * right_true) % MOD + (left_false * right_false) % MOD) % MOD;
            }
        }
    }

    dp[i][j][want_true] = ways;
    return dp[i][j][want_true];
}

long long solve_t(int &n, string &exp)
{
    // base case 1 is taken care of by setting all to 0
    vector<vector<vector<long long>>> dp(n, vector<vector<long long>>(n, vector<long long>(2, 0)));

    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = i; j <= n - 1; j++)
        {
            for (int want_true = 0; want_true <= 1; want_true++)
            {
                // base case 2
                if (i == j)
                {
                    if (want_true == 1)
                    {
                        dp[i][j][want_true] = (exp[i] == 'T') ? 1 : 0;
                    }
                    else
                    {
                        dp[i][j][want_true] = (exp[i] == 'F') ? 1 : 0;
                    }

                    continue;
                }

                long long ways = 0;

                for (int index = i + 1; index <= j - 1; index += 2)
                {
                    long long left_true = solve_m(i, index - 1, 1, exp, dp);
                    long long left_false = solve_m(i, index - 1, 0, exp, dp);
                    long long right_true = solve_m(index + 1, j, 1, exp, dp);
                    long long right_false = solve_m(index + 1, j, 0, exp, dp);

                    if (exp[index] == '&')
                    {
                        if (want_true == 1)
                        {
                            ways = (ways + (left_true * right_true) % MOD) % MOD;
                        }
                        else
                        {
                            ways = (ways + (left_true * right_false) % MOD + (left_false * right_false) % MOD + (left_false * right_true) % MOD) % MOD;
                        }
                    }
                    else if (exp[index] == '|')
                    {
                        if (want_true == 1)
                        {
                            ways = (ways + (left_true * right_false) % MOD + (left_true * right_true) % MOD + (left_false * right_true) % MOD) % MOD;
                        }
                        else
                        {
                            ways = (ways + (left_false * right_false) % MOD) % MOD;
                        }
                    }
                    else
                    {
                        if (want_true == 1)
                        {
                            ways = (ways + (left_true * right_false) % MOD + (left_false * right_true) % MOD) % MOD;
                        }
                        else
                        {
                            ways = (ways + (left_true * right_true) % MOD + (left_false * right_false) % MOD) % MOD;
                        }
                    }
                }

                dp[i][j][want_true] = ways;
            }
        }
    }

    return dp[0][n - 1][1];
}

int evaluateExp(string &exp)
{
    int n = exp.length();

    // vector<vector<vector<long long>>> dp(n, vector<vector<long long>>(n, vector<long long>(2, -1)));
    // return solve_m(0, n-1, 1, exp, dp);

    return solve_t(n, exp);
}
