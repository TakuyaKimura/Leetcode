/*

Given two sparse matrices A and B, return the result of AB.

You may assume that A's column number is equal to B's row number.

Example:

    A = [
            [ 1, 0, 0],
            [-1, 0, 3]
        ]

    B = [
            [ 7, 0, 0 ],
            [ 0, 0, 0 ],
            [ 0, 0, 1 ]
        ]


         |  1 0 0 |   | 7 0 0 |   |  7 0 0 |
    AB = | -1 0 3 | x | 0 0 0 | = | -7 0 3 |
                      | 0 0 1 |

*/

#include <vector>
#include <unordered_set>
using namespace std;

// using hash table to store the indexes
// like adjacency matrix vs adjacency list
class Solution {
public:
    vector<vector<int>> multiply(vector<vector<int>>& A, vector<vector<int>>& B) {
        int rows = A.size(), n = B.size(), cols = n ? B[0].size() : 0;
        vector<vector<int>> result(rows, vector<int>(cols, 0));
        vector<unordered_set<int>> hashA(rows), hashB(cols);
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < n; ++j)
                if (A[i][j])
                    hashA[i].insert(j);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < cols; ++j)
                if (B[i][j])
                    hashB[j].insert(i);
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                for (int idx : hashA[i])
                    if (hashB[j].find(idx) != hashB[j].end())
                        result[i][j] += A[i][idx] * B[idx][j];
        return result;
    }
};

// much faster than the naive way
class Solution2 {
public:
    vector<vector<int>> multiply(vector<vector<int>>& A, vector<vector<int>>& B) {
        int rows = A.size(), n = B.size(), cols = n ? B[0].size() : 0;
        vector<vector<int>> result(rows, vector<int>(cols, 0));
        for (int i = 0; i < rows; ++i)
            for (int k = 0; k < n; ++k)
                if (A[i][k])  // note how to speed up
                    for (int j = 0; j < cols; ++j)
                        result[i][j] += A[i][k] * B[k][j];  // without checking B[k][j] is a bit faster
        return result;
    }
};

// this is the naive way, extremely slow, barely pass OJ
// note the difference from the above one
class Solution3 {
public:
    vector<vector<int>> multiply(vector<vector<int>>& A, vector<vector<int>>& B) {
        int rows = A.size(), n = B.size(), cols = n ? B[0].size() : 0;
        vector<vector<int>> result(rows, vector<int>(cols, 0));
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                for (int k = 0; k < n; ++k)
                    if (A[i][k] && B[k][j])
                        result[i][j] += A[i][k] * B[k][j];
        return result;
    }
};