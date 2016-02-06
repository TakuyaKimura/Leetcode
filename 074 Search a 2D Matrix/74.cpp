/*

Write an efficient algorithm that searches for a value in an m x n matrix.

This matrix has the following properties:

    Integers in each row are sorted from left to right.
    The first integer of each row is greater than the last integer of the previous row.

For example,

Consider the following matrix:

    [
        [1,   3,  5,  7],
        [10, 11, 16, 20],
        [23, 30, 34, 50]
    ]

Given target = 3, return true.

*/

#include <vector>
using namespace std;

// two solutions are of the same idea
// one use matrix[mid][n-1], one use matrix[mid+1][0]
class Solution2 {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();
        if (!m)
            return false;
        int n = matrix[0].size();
        if (!n)
            return false;
        int low = 0, high = m - 1, mid;
        while (low < high)
        {
            mid = (low + high) / 2;  // low + (high - low) / 2, to avoid overflow
            if (matrix[mid][n - 1] == target)
                return true;
            if (matrix[mid][n - 1] > target)
                high = mid;
            else
                low = mid + 1;
        }
        // low == high, binary search in this row
        int row = low;
        low = 0;
        high = n - 1;
        while (low <= high)
        {
            mid = (low + high) / 2;  // low + (high - low) / 2, to avoid overflow
            if (matrix[row][mid] == target)
                return true;
            if (matrix[row][mid] > target)
                high = mid - 1;
            else
                low = mid + 1;
        }
        return false;
    }
};

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();
        if (!m)
            return false;
        int n = matrix[0].size();
        if (!n)
            return false;
        int low = 0, high = m - 1, mid;
        while (low < high)
        {
            mid = (low + high) / 2 + 1;  // low + (high - low) / 2 + 1, to avoid overflow
            if (matrix[mid][0] == target)
                return true;
            if (matrix[mid][0] > target)
                high = mid - 1;
            else
                low = mid;
        }
        // low == high, binary search in this row
        int row = low;
        low = 0;
        high = n - 1;
        while (low <= high)
        {
            mid = (low + high) / 2;  // low + (high - low) / 2, to avoid overflow
            if (matrix[row][mid] == target)
                return true;
            if (matrix[row][mid] > target)
                high = mid - 1;
            else
                low = mid + 1;
        }
        return false;
    }
};