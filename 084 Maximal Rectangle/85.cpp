/*

Given a 2D binary matrix filled with 0's and 1's, find the largest rectangle containing all ones and return its area.

*/

#include <vector>
#include <algorithm>
using namespace std;

// height counts the number of successive '1's above (plus the current one)
// left & right are the boundaries of the rectangle which contains the current point with a height of value height
// loops can be combined to speed up, but it may not actually be faster because of locality of reference

// DP, at every matrix[i][j], calculate the square with matrix[i][j] on the bottom, and max height at matrix[i][j]
// cur_left is the leftmost consecutive 1s to the left of matrix[i][j]
// cur_right is the rightmost consecutive 1s to the right of matrix[i][j]
class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        int m = matrix.size(), n = m ? matrix[0].size() : 0, maxA = 0;
        vector<int> left(n, 0), right(n, n), height(n, 0);

        for (int i = 0; i < m; ++i)
        {
            int cur_left = 0, cur_right = n;
            // compute height (can do this from either side)
            for (int j = 0; j < n; ++j)
                if (matrix[i][j] == '1')
                    ++height[j];
                else
                    height[j] = 0;

            // compute left (from left to right)
            for (int j = 0; j < n; ++j)
                if (matrix[i][j] == '1')
                    left[j] = max(left[j], cur_left);
                else
                {
                    left[j] = 0; 
                    cur_left = j + 1;  // right edge of the bar
                }

            // compute right (from right to left)
            for (int j = n - 1; j >= 0; --j)
                if (matrix[i][j] == '1') 
                    right[j] = min(right[j], cur_right);
                else
                { 
                    right[j] = n; 
                    cur_right = j;  // left edge of the bar
                }

            // compute the area of rectangle (can do this from either side)
            for (int j = 0; j < n; ++j)
                maxA = max(maxA, (right[j] - left[j]) * height[j]);

        }
        return maxA;
    }
};

class Solution2 {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        int m = matrix.size(), n = m ? matrix[0].size() : 0, maxArea = 0, curLeft, curRight;
        vector<int> height(n, 0), left(n, 0), right(n, n);
        for (int i = 0; i < m; ++i)
        {
            curLeft = 0;
            curRight = n;
            for (int j = 0; j < n; ++j)
                if (matrix[i][j] == '0')
                {
                    height[j] = 0;
                    curLeft = j + 1;
                    left[j] = 0;
                }
                else
                {
                    ++height[j];
                    left[j] = max(left[j], curLeft);
                }


            for (int j = n - 1; j >= 0; --j)
            {
                if (matrix[i][j] == '0')
                {
                    curRight = j;
                    right[j] = n;
                }
                else
                    right[j] = min(right[j], curRight);

                maxArea = max(maxArea, height[j] * (right[j] - left[j]));
            }
        }
        return maxArea;
    }
};