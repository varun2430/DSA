// Ninja is planing this N days-long training schedule. Each day, he can perform any
// one of these three activities. (Running, Fighting Practice or Learning New Moves).
// Each activity has some merit points on each day. As Ninja has to improve all his
// skills, he can’t do the same activity in two consecutive days. Can you help Ninja
// find out the maximum merit points Ninja can earn?

// Example:
// Input:  3
//         10 40 70
//         20 50 80
//         30 60 90
// Output: 210

#include <bits/stdc++.h>
using namespace std;

// memoization top down
int solve_m(int day, int prevTask, vector<vector<int>> &points, vector<vector<int>> &dp)
{
    if (day == 0)
    {
        int maxPoints = INT_MIN;
        for (int task = 0; task < 3; task++)
        {
            if (task != prevTask)
            {
                maxPoints = max(maxPoints, points[day][task]);
            }
        }

        return maxPoints;
    }

    if (dp[day][prevTask] != -1)
    {
        return dp[day][prevTask];
    }

    int maxPoints = INT_MIN;
    for (int task = 0; task < 3; task++)
    {
        if (task != prevTask)
        {
            int currPoints = solve_m(day - 1, task, points, dp) + points[day][task];
            maxPoints = max(maxPoints, currPoints);
        }
    }

    dp[day][prevTask] = maxPoints;
    return dp[day][prevTask];
}

// tabulation bottom up
int solve_t(int n, vector<vector<int>> &points, vector<vector<int>> &dp)
{
    dp[0][0] = max(points[0][1], points[0][2]);
    dp[0][1] = max(points[0][0], points[0][2]);
    dp[0][2] = max(points[0][0], points[0][1]);
    dp[0][3] = max(points[0][0], max(points[0][1], points[0][2]));

    for (int day = 1; day <= n; day++)
    {
        for (int prevTask = 0; prevTask < 4; prevTask++)
        {
            int maxPoints = INT_MIN;
            for (int task = 0; task < 3; task++)
            {
                if (task != prevTask)
                {
                    int currPoints = dp[day - 1][task] + points[day][task];
                    maxPoints = max(maxPoints, currPoints);
                }
            }

            dp[day][prevTask] = maxPoints;
        }
    }

    return dp[n][3];
}

// space optimized
int solve_so(int n, vector<vector<int>> &points)
{
    vector<int> prev(4, -1);

    prev[0] = max(points[0][1], points[0][2]);
    prev[1] = max(points[0][0], points[0][2]);
    prev[2] = max(points[0][0], points[0][1]);
    prev[3] = max(points[0][0], max(points[0][1], points[0][2]));

    for (int day = 1; day <= n; day++)
    {
        vector<int> curr(4, 0);
        for (int prevTask = 0; prevTask < 4; prevTask++)
        {
            int maxPoints = INT_MIN;
            for (int task = 0; task < 3; task++)
            {
                if (task != prevTask)
                {
                    int currPoints = prev[task] + points[day][task];
                    maxPoints = max(maxPoints, currPoints);
                }
            }

            curr[prevTask] = maxPoints;
        }

        prev = curr;
    }

    return prev[3];
}

int ninjaTraining(int n, vector<vector<int>> &points)
{
    return solve_so(n - 1, points);
}
