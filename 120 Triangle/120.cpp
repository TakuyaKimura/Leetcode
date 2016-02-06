/*

Given a triangle, find the minimum path sum from top to bottom. 

Each step you may move to adjacent numbers on the row below.

For example, given the following triangle
    [
           [2],
          [3,4],
         [6,5,7],
        [4,1,8,3]
    ]

The minimum path sum from top to bottom is 11 (i.e., 2 + 3 + 5 + 1 = 11).

Note:
Bonus point if you are able to do this using only O(n) extra space, where n is the total number of rows in the triangle.

*/

#include <vector>
#include <algorithm>
using namespace std;

// bottom-up
class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int n = triangle.size(), i, j;
        if (n == 0)
            return 0;
        vector<int> dp(triangle.back());
        for (i = n - 2; i >= 0; --i)
            for (j = 0; j <= i; ++j)
                dp[j] = min(dp[j], dp[j + 1]) + triangle[i][j];
        return dp[0];
    }
};