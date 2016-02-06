/*

Follow up for "Unique Paths":

Now consider if some obstacles are added to the grids. How many unique paths would there be?

An obstacle and empty space is marked as 1 and 0 respectively in the grid.

For example,
There is one obstacle in the middle of a 3x3 grid as illustrated below.
    [
        [0,0,0],
        [0,1,0],
        [0,0,0]
    ]

The total number of unique paths is 2.

Note: m and n will be at most 100.

*/

#include <vector>
using namespace std;

class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size();
        if (m == 0)
            return 0;
        int n = obstacleGrid[0].size(), i, j;
        if (n == 0)
            return 0;
        vector<int> dp(n + 1, 0);
        if (obstacleGrid[0][0] == 0)
            dp[1] = 1;
        for (i = 0; i < m; ++i)
            for (j = 1; j <= n; ++j)
                dp[j] = obstacleGrid[i][j - 1] ? 0 : dp[j] + dp[j - 1];
        return dp[n];
    }
};