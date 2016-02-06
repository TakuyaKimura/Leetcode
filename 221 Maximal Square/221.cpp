/*

Given a 2D binary matrix filled with 0's and 1's, find the largest square containing all 1's and return its area.

For example, given the following matrix:

        1 0 1 0 0
        1 0 1 1 1
        1 1 1 1 1
        1 0 0 1 0

Return 4.

*/

#include <vector>
#include <algorithm>
using namespace std;

// dp[i][j] represents length of the max square whose lower right corner is matrix[i][j]
// if matrix[i][j] == 0, dp[i][j] = 0
// if matrix[i][j] == 1, dp[i][j] = min(dp[i-1][j], dp[i][j-1], dp[i-1][j-1]) + 1
// instead of using m*n space, we could use two vectors

// furthermore, we could use only one vector: dp[j] as dp[i-1][j]
// dp[i-1] as dp[i-1][j], above_left as dp[i-1][j-1]

// the following code pad an additional row / column

class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        int m = matrix.size(), n = m ? matrix[0].size() : 0, maxsize = 0, above_left = 0, temp, size;
        vector<int> dp(n + 1, 0);
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j)
            {
                temp = dp[j + 1];

                if (matrix[i][j] == '1')
                {
                    size = min(min(dp[j + 1], dp[j]), above_left) + 1;
                    dp[j + 1] = size;
                    if (size > maxsize)
                        maxsize = size;
                }
                else
                    dp[j + 1] = 0;

                above_left = temp;
            }

        return maxsize * maxsize;
    }
};