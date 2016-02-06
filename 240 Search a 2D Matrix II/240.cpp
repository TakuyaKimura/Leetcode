/*

Write an efficient algorithm that searches for a value in an m x n matrix. 

This matrix has the following properties:
    Integers in each row are sorted in ascending from left to right.
    Integers in each column are sorted in ascending from top to bottom.

For example,
Consider the following matrix:

    [
        [1,   4,  7, 11, 15],
        [2,   5,  8, 12, 19],
        [3,   6,  9, 16, 22],
        [10, 13, 14, 17, 24],
        [18, 21, 23, 26, 30]
    ]

Given target = 5, return true.

Given target = 20, return false.

*/

#include <vector>
using namespace std;

// http://articles.leetcode.com/2010/10/searching-2d-sorted-matrix-part-ii.html

// Step-wise Linear Search
// O(m + n), 180ms
// start with the upper right or the lower left corner element
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size(), n = m ? matrix[0].size() : 0, i = 0, j = n - 1, num;
        while (i < m && j >= 0)
        {
            num = matrix[i][j];
            if (num < target)
                ++i;
            else if (num > target)
                --j;
            else
                return true;
        }
        return false;
    }
};

// Diagonal-based binary partition, 224ms
// linear search the middle row/column/diagonal T(n) = 2T(n/2) + cn = O(n lg n)

// or use binary search to search the middle row/column/diagonal
// T(n) = 2T(n/2) + c lg n
//                       lg n
//      = 2 lg n T(1) + c ¡Æ(2 lg(n / 2k))
//                       k = 1
//      = O(n) + c(2n - lg n - 2)
//      = O(n)

// could also do row-wise or column-wise binary partition
class Solution2 {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        m = matrix.size();
        n = m ? matrix[0].size() : 0;
        return searchMatrix(matrix, target, 0, m - 1, 0, n - 1);
    }
private:
    int m, n;
    bool searchMatrix(vector<vector<int>>& matrix, int target, int upper, int lower, int left, int right) {
        if (upper > lower || left > right)
            return false;
        int mid_i = (upper + lower) / 2, mid_j = (left + right) / 2, mid = matrix[mid_i][mid_j];
        if (mid < target)
        {
            while (++mid_i <= lower && ++mid_j <= right && matrix[mid_i][mid_j] < target) {}
            if (mid_i > lower)
                return searchMatrix(matrix, target, upper, lower, ++mid_j, right);
            else if (mid_j > right)
                return searchMatrix(matrix, target, mid_i, lower, left, right);
            else if (matrix[mid_i][mid_j] > target)
                return searchMatrix(matrix, target, upper, mid_i - 1, mid_j, right) ||
                       searchMatrix(matrix, target, mid_i, lower, left, mid_j - 1);
            else
                return true;
        }
        else if (mid > target)
        {
            while (--mid_i >= upper && --mid_j >= left && matrix[mid_i][mid_j] > target) {}
            if (mid_i < upper)
                return searchMatrix(matrix, target, upper, lower, left, --mid_j);
            else if (mid_j < left)
                return searchMatrix(matrix, target, upper, mid_i, 0, right);
            else if (matrix[mid_i][mid_j] < target)
                return searchMatrix(matrix, target, upper, mid_i, mid_j + 1, right) ||
                       searchMatrix(matrix, target, mid_i + 1, lower, left, mid_j);
            else
                return true;
        }
        else
            return true;
    }
};

// row-wise binary partition, 276ms
class Solution3 {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        m = matrix.size();
        n = m ? matrix[0].size() : 0;
        return searchMatrix(matrix, target, 0, m - 1, 0, n - 1);
    }
private:
    int m, n;
    bool searchMatrix(vector<vector<int>>& matrix, int target, int upper, int lower, int left, int right) {
        if (upper > lower || left > right)
            return false;
        int mid_i = (upper + lower) / 2, mid_j = (left + right) / 2, mid = matrix[mid_i][mid_j];
        if (mid < target)
        {
            while (++mid_j <= right && matrix[mid_i][mid_j] < target) {}
            if (mid_j > right)
                return searchMatrix(matrix, target, mid_i + 1, lower, left, right);
            else if (matrix[mid_i][mid_j] > target)
                return searchMatrix(matrix, target, upper, mid_i, mid_j, right) ||
                       searchMatrix(matrix, target, mid_i + 1, lower, left, mid_j - 1);
            else
                return true;
        }
        else if (mid > target)
        {
            while (--mid_j >= left && matrix[mid_i][mid_j] > target) {}
            if (mid_j < left)
                return searchMatrix(matrix, target, upper, mid_i - 1, 0, right);
            else if (matrix[mid_i][mid_j] < target)
                return searchMatrix(matrix, target, upper, mid_i - 1, mid_j + 1, right) ||
                       searchMatrix(matrix, target, mid_i, lower, left, mid_j);
            else
                return true;
        }
        else
            return true;
    }
};