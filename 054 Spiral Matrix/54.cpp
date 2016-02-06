/*

Given a matrix of m x n elements (m rows, n columns), return all elements of the matrix in spiral order.

For example,
Given the following matrix:
    [
    [ 1, 2, 3 ],
    [ 4, 5, 6 ],
    [ 7, 8, 9 ]
    ]

You should return [1,2,3,6,9,8,7,4,5].

*/

#include <vector>
using namespace std;

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = m ? matrix[0].size() : 0, size = m * n;
        vector<int> result(size);
        int rowStart = 0, rowEnd = m - 1, colStart = 0, colEnd = n - 1;
        int index = 0, i, j;
        while (index < size)
        {
            // traverse right
            for (j = colStart; j <= colEnd; ++j)
                result[index++] = matrix[rowStart][j];
            ++rowStart;

            // traverse down
            for (i = rowStart; i <= rowEnd; ++i)
                result[index++] = matrix[i][colEnd];
            --colEnd;

            // traverse left
            if (rowStart <= rowEnd)
                for (j = colEnd; j >= colStart; --j)
                    result[index++] = matrix[rowEnd][j];
            --rowEnd;

            // traverse up
            if (colStart <= colEnd)
                for (i = rowEnd; i >= rowStart; --i)
                    result[index++] = matrix[i][colStart];
            ++colStart;
        }
        return result;
    }
};