/*

Given a m x n grid filled with non-negative numbers, 
find a path from top left to bottom right which minimizes the sum of all numbers along its path.

Note: You can only move either down or right at any point in time.

*/

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size();
        if (!m)
            return 0;
        int n = grid[0].size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, INT_MAX));
        dp[0][1] = 0;
        for (int i = 1; i <= m; ++i)
            for (int j = 1; j <= n; ++j)
                dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + grid[i - 1][j - 1];
        return dp[m][n];
    }
};

// only need O(n) space, one vector
class Solution2 {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size();
        if (!m)
            return 0;
        int n = grid[0].size();
        vector<int> dp(n + 1, INT_MAX);
        dp[1] = 0;
        for (int i = 0; i < m; ++i)
            for (int j = 1; j <= n; ++j)
                dp[j] = min(dp[j], dp[j - 1]) + grid[i][j - 1];
        return dp[n];
    }
};