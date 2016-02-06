/*

A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).

The robot can only move either down or right at any point in time. 
The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).

How many possible unique paths are there?

Note: m and n will be at most 100.

*/

#include <vector>
using namespace std;

// DP
class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<vector<int>> dp(m, vector<int>(n, 1));
        for (int i = 1; i < m; ++i)
            for (int j = 1; j < n; ++j)
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
        return dp[m - 1][n - 1];
    }
};

// instead of using O(m * n) space, we only need O(n) space
class Solution2 {
public:
    int uniquePaths(int m, int n) {
        vector<int> dp(n, 1);
        for (int i = 1; i < m; ++i)
            for (int j = 1; j < n; ++j)
                dp[j] += dp[j  - 1];
        return dp[n - 1];
    }
};

// use constant space
// The total step number should be m+n-2.
// This means that we have to move down for m-1 steps and move right n-1 steps to reach the destination.
// Then different choice number would be:
// UniqueStepNum = choose (m-1) from (m+n-2) = choose (n-1) from (m+n-2)
// = (m+n-2)! / [(m-1)! * (n-1)!]
// = ( (m+n-2) / (m-1) ) * ( (m+n-3) / (m-2) ) * ... * (n / 1)

// note that in each iteration, res will always be an integer, because it's the Binomial coefficient of C(i, n-1)
class Solution3 {
public:
    int uniquePaths(int m, int n) {
        long long res = 1;
        for (int i = n; i < m + n - 1; ++i)
            res = res * i / (i - n + 1);
        return res;
    }
};

class Solution4 {
public:
    int uniquePaths(int m, int n) {
        long long res = 1;
        for (int i = n, j = 1; i < m + n - 1; ++i, ++j)
            res = res * i / j;
        return res;
    }
};