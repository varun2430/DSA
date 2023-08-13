// Given a positive integer n, find the nth fibonacci number. Since the answer can be very
// large return the answer modulo 1000000007.

// Example:
// Input: n = 5
// Output: 5

#include <bits/stdc++.h>
using namespace std;

// memoization top down
long long int solve_m(long long int n, vector<long long int> &dp)
{
    if (n <= 1)
    {
        return n;
    }

    if (dp[n] != -1)
    {
        return dp[n];
    }

    dp[n] = (solve_m(n - 1, dp) + solve_m(n - 2, dp)) % 1000000007;
    return dp[n];
}

// tabulation bottom up
long long int solve_t(long long int n, vector<long long int> &dp)
{
    if (n < 2)
    {
        return n;
    }

    dp[0] = 0;
    dp[1] = 1;

    for (int i = 2; i <= n; i++)
    {
        dp[i] = (dp[i - 1] + dp[i - 2]) % 1000000007;
    }

    return dp[n];
}

// space optimized
long long int solve_so(long long int n)
{
    if (n < 2)
    {
        return n;
    }

    long long int curr;
    long long int prev1 = 0;
    long long int prev2 = 1;

    for (int i = 2; i <= n; i++)
    {
        curr = (prev1 + prev2) % 1000000007;

        prev1 = prev2;
        prev2 = curr;
    }

    return curr;
}

long long int nthFibonacci(long long int n)
{
    // vector<long long int> dp(n+1, -1);
    return solve_so(n);
}
