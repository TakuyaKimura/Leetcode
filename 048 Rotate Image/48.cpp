/*

You are given an n x n 2D matrix representing an image.

Rotate the image by 90 degrees (clockwise).

Follow up:
Could you do this in-place?

*/

#include <vector>
using namespace std;

/*
* clockwise rotate
* first reverse up to down, then swap the symmetry  ||  or swap the symmetry, then reverse left to right
* 1 2 3     7 8 9     7 4 1
* 4 5 6  => 4 5 6  => 8 5 2
* 7 8 9     1 2 3     9 6 3
*/
void rotate(vector<vector<int>>& matrix) {
    int n = matrix.size();
    reverse(matrix.begin(), matrix.end());
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < i; ++j)
            swap(matrix[i][j], matrix[j][i]);
}

/*
* anticlockwise rotate
* first reverse left to right, then swap the symmetry ||  or swap the symmetry, then reverse up to down
* 1 2 3     3 2 1     3 6 9
* 4 5 6  => 6 5 4  => 2 5 8
* 7 8 9     9 8 7     1 4 7
*/
void anti_rotate(vector<vector<int>>& matrix) {
    int n = matrix.size();
    for (auto& vi : matrix)
        reverse(vi.begin(), vi.end());
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < i; ++j)
            swap(matrix[i][j], matrix[j][i]);
}

// rotate twice: diagonal(upper left - lower right), vertical
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();
        int temp;
        for (int i = 1; i < n; ++i)
            for (int j = 0; j < i; ++j)
            {
                temp = matrix[i][j];
                matrix[i][j] = matrix[j][i];
                matrix[j][i] = temp;
            }
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n / 2; ++j)
            {
                temp = matrix[i][j];
                matrix[i][j] = matrix[i][n - j - 1];
                matrix[i][n - j - 1] = temp;
            }
    }
};

class Solution2 {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size(), temp;

        // matrix[i][j] -> matrix[j][n-i-1] -> matrix[n-i-1][n-j-1] -> matrix[n-j-1][i] -> matrix[i][j]
        for (int i = 0; i < n / 2; ++i)         // tricky
            for (int j = i; j < n - i - 1; ++j) // draw picture to see
            {
                temp = matrix[i][j];
                matrix[i][j] = matrix[n - j - 1][i];
                matrix[n - j - 1][i] = matrix[n - i - 1][n - j - 1];
                matrix[n - i - 1][n - j - 1] = matrix[j][n - i - 1];
                matrix[j][n - i - 1] = temp;
            }
    }
};

// rotate twice: diagonal(upper right - lower left), horizontal
class Solution3 {
public:
    void rotate(vector<vector<int>>& matrix){
        int size = matrix.size();
        for (int i = 0; i < size - 1; ++i)
            for (int j = 0; j < size - 1 - i; ++j)
                swap(matrix[i][j], matrix[size - 1 - j][size - 1 - i]);
        reverse(matrix.begin(), matrix.end());
    }
};