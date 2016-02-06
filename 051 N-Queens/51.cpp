/*

The n-queens puzzle is the problem of placing n queens on an n¡Án chessboard such that no two queens attack each other.

Given an integer n, return all distinct solutions to the n-queens puzzle.

Each solution contains a distinct board configuration of the n-queens' placement, 
where 'Q' and '.' both indicate a queen and an empty space respectively.

For example,
There exist two distinct solutions to the 4-queens puzzle:

    [
    [".Q..",  // Solution 1
    "...Q",
    "Q...",
    "..Q."],

    ["..Q.",  // Solution 2
    "Q...",
    "...Q",
    ".Q.."]
    ]

*/

#include <vector>
using namespace std;

// DFS + Backtracking, 4ms
// note: use int as flag (4ms) is acctually faster than bool (12ms)
class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> result;
        vector<string> solution(n, string(n, '.'));
        vector<int> hasQueenAtColumn(n, 0);
        vector<int> hasQueenAtMainDiag(2 * n - 1, 0);
        vector<int> hasQueenAtAntiDiag(2 * n - 1, 0);
        dfs(0, n, result, solution, hasQueenAtColumn, hasQueenAtMainDiag, hasQueenAtAntiDiag);
        return result;
    }
private:
    void dfs(int row, int n, vector<vector<string>>& result, vector<string>& solution, 
            vector<int>& hasQueenAtColumn, vector<int>& hasQueenAtMainDiag, vector<int>& hasQueenAtAntiDiag) {
        if (row == n)  // we've got a solution
        {
            result.push_back(solution);
            return;
        }
        for (int col = 0; col < n; ++col)  // try each column
            // 2n-1 main diagnal, use row - col + n - 1 to index
            // 2n-1 antidiagnal, use row + col to index
            if (!hasQueenAtColumn[col] && !hasQueenAtMainDiag[row - col + n - 1] && !hasQueenAtAntiDiag[row + col])
            {
                solution[row][col] = 'Q';
                hasQueenAtColumn[col] = hasQueenAtMainDiag[row - col + n - 1] = hasQueenAtAntiDiag[row + col] = 1;
                dfs(row + 1, n, result, solution, hasQueenAtColumn, hasQueenAtMainDiag, hasQueenAtAntiDiag);
                solution[row][col] = '.';
                hasQueenAtColumn[col] = hasQueenAtMainDiag[row - col + n - 1] = hasQueenAtAntiDiag[row + col] = 0;
            }
    }
};