/*

Given numRows, generate the first numRows of Pascal's triangle.

For example, given numRows = 5,
Return
    [
            [1],
           [1,1],
          [1,2,1],
         [1,3,3,1],
        [1,4,6,4,1]
    ]

*/

#include <vector>
using namespace std;

// note: ith row contains i+1 elements
class Solution2 {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> result(numRows);
        int i, j, mid;
        for (i = 0; i < numRows; ++i)
        {
            result[i] = vector<int>(i + 1);
            result[i][0] = result[i][i] = 1;
            mid = i / 2;
            for (j = 1; j <= mid; ++j)
                result[i][j] = result[i][i - j] = result[i - 1][j - 1] + result[i - 1][j];
        }
        return result;
    }
};

class Solution3 {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> pascal(numRows);
        if (numRows == 0)
            return pascal;
        pascal[0].push_back(1);
        for (int i = 1; i < numRows; ++i)
        {
            pascal[i] = pascal[i - 1];            // copy last row
            pascal[i].push_back(1);
            for (int j = i - 1; j > 0; --j)
                pascal[i][j] += pascal[i][j - 1]; // shift and add to itself
        }
        return pascal;
    }
};

class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> pascal;
        for (int i = 0; i < numRows; ++i)
        {
            vector<int> row(i + 1);
            row[0] = row[i] = 1;
            for (int j = 1; j <= i / 2; ++j)
                row[j] = row[i - j] = pascal[i - 1][j - 1] + pascal[i - 1][j];
            pascal.push_back(row);
        }
        return pascal;
    }
};