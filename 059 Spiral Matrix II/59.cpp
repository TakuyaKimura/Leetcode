/*

Given an integer n, generate a square matrix filled with elements from 1 to n2 in spiral order.

For example,
Given n = 3,

You should return the following matrix:
    [
    [ 1, 2, 3 ],
    [ 8, 9, 4 ],
    [ 7, 6, 5 ]
    ]

*/

#include <vector>
using namespace std;

class Solution2 {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> matrix(n, vector<int>(n, 0));
        int i = 0, j = 0, di = 0, dj = 1, temp, size = n * n;
        for (int num = 1; num <= size; ++num)
        {
            matrix[i][j] = num;
            // Make a right turn when the cell ahead is already non-zero
            //if (i + di == n || i + di == -1 || j + dj == n || j + dj == -1 || matrix[i + di][j + dj])
            if (matrix[(i + di + n) % n][(j + dj + n) % n])
            {
                temp = di;
                di = dj;
                dj = -temp;
            }
            i += di;
            j += dj;
        }
        return matrix;
    }
};

class Solution3 {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> res(n, vector<int>(n));
        int colL = 0, rowL = 0, colH = n - 1, rowH = n - 1, k = 1;
        while (colL <= colH && rowL <= rowH)
        {
            for (int i = colL; i <= colH; ++i)
                res[rowL][i] = k++;
            ++rowL;
            for (int i = rowL; i <= rowH; ++i)
                res[i][colH] = k++;
            --colH;
            for (int i = colH; i >= colL; --i)
                res[rowH][i] = k++;
            --rowH;
            for (int i = rowH; i >= rowL; --i)
                res[i][colL] = k++;
            ++colL;
        }
        return res;
    }
};

class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> matrix(n, vector<int>(n));
        int ele = 1;
        for (int i = 0; i < n / 2; ++i)
        {
            for (int j = i; j < n - i - 1; ++j)
            {
                matrix[i][j] = ele;
                matrix[j][n - i - 1] = ele + (n - 2 * i - 1);
                matrix[n - i - 1][n - j - 1] = ele + 2 * (n - 2 * i - 1);
                matrix[n - j - 1][i] = ele + 3 * (n - 2 * i - 1);
                ++ele;
            }
            ele += 3 * (n - 2 * i - 1);
        }
        if (n % 2 == 1)
            matrix[n / 2][n / 2] = n * n;
        return matrix;
    }
};

// Build it inside-out
// Start with the empty matrix, add the numbers in reverse order until we added the number 1
// Always rotate the matrix clockwise and add a top row:
//     | | => | 9 | => | 8 |    | 6 7 |    | 4 5 |    | 1 2 3 |
//                     | 9 | => | 9 8 | => | 9 6 | => | 8 9 4 |
//                                         | 8 7 |    | 7 6 5 |