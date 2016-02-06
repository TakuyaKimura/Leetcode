/*

Given a m x n matrix, if an element is 0, set its entire row and column to 0. Do it in place.

Follow up:
    Did you use extra space?
    A straight forward solution using O(mn) space is probably a bad idea.
    A simple improvement uses O(m + n) space, but still not the best solution.
    Could you devise a constant space solution?

*/

#include <vector>
#include <iostream>
using namespace std;

class Solution2 {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = m ? matrix[0].size() : 0;
        int col0 = 1, i, j;  // use matrix[0][0] to represent row0
        for (i = 0; i < m; ++i)
        {
            if (matrix[i][0] == 0)
                col0 = 0;
            for (j = 1; j < n; ++j)
                if (matrix[i][j] == 0)
                    matrix[0][j] = matrix[i][0] = 0;
        }
        for (i = m - 1; i >= 0; --i)
        {
            for (j = n - 1; j > 0; --j)  // leave the first column out
                if (matrix[i][0] == 0 || matrix[0][j] == 0)
                    matrix[i][j] = 0;
            if (col0 == 0)
                matrix[i][0] = 0;
        }
    }
};

class Solution3 {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int m = matrix.size();
        if (!m)
            return;
        int n = matrix[0].size(), i, j;
        bool firstRow = false;
        for (j = 0; j < n; ++j)
            if (matrix[0][j] == 0)
            {
                firstRow = true;
                break;
            }

        for (i = 1; i < m; ++i)
            for (j = 0; j < n; ++j)
                if (matrix[i][j] == 0)
                    matrix[0][j] = matrix[i][0] = 0;

        for (i = 1; i < m; ++i)
            if (matrix[i][0] == 0)
                for (j = 1; j < n; ++j)
                    matrix[i][j] = 0;

        for (j = 0; j < n; ++j)
            if (matrix[0][j] == 0)
                for (i = 1; i < m; ++i)
                    matrix[i][j] = 0;

        if (firstRow)
            for (j = 0; j < n; ++j)
                matrix[0][j] = 0;
    }
};

class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = m ? matrix[0].size() : 0;
        int i, j;
        bool firstRowHasZero = false, firstColHasZero = false;

        for (j = 0; j < n; ++j)
            if (matrix[0][j] == 0)
            {
                firstRowHasZero = true;
                break;
            }
        for (i = 0; i < m; ++i)
            if (matrix[i][0] == 0)
            {
                firstColHasZero = true;
                break;
            }

        // don't modify the matrix just yet
        // mark them in the first row and first column
        for (i = 1; i < m; ++i)
            for (j = 1; j < n; ++j)
            {
                if (matrix[i][j] == 0)
                {
                    matrix[0][j] = 0;
                    matrix[i][0] = 0;
                }
            }
        // set 0 for each row   
        for (i = 1; i < m; ++i)
            for (j = 1; j < n; ++j)
                if (matrix[i][0] == 0)
                    matrix[i][j] = 0;
        // set 0 for each column         
        for (j = 1; j < n; ++j)
            for (i = 1; i < m; ++i)
                if (matrix[0][j] == 0)
                    matrix[i][j] = 0;

        // finally do the first row and first column
        if (firstRowHasZero)
            for (j = 0; j < n; ++j)
                matrix[0][j] = 0;

        if (firstColHasZero)
            for (i = 0; i < m; ++i)
                matrix[i][0] = 0;
    }
};