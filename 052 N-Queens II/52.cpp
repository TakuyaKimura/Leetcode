/*

Follow up for N-Queens problem.

Now, instead outputting board configurations, return the total number of distinct solutions.

*/

#include <vector>
using namespace std;

class Solution {
public:
    int totalNQueens(int n) {
        int count = 0;
        vector<int> hasQueenAtColumn(n, 0);
        vector<int> hasQueenAtMainDiag(2 * n - 1, 0);
        vector<int> hasQueenAtAntiDiag(2 * n - 1, 0);
        dfs(0, n, count, hasQueenAtColumn, hasQueenAtMainDiag, hasQueenAtAntiDiag);
        return count;
    }
private:
    void dfs(int row, int n, int& count, vector<int>& hasQueenAtColumn, vector<int>& hasQueenAtMainDiag, vector<int>& hasQueenAtAntiDiag) {
        if (row == n)  // we've got a solution
        {
            ++count;
            return;
        }
        for (int col = 0; col < n; ++col)  // try each column
            // 2n-1 main diagnal, use row - col + n - 1 to index
            // 2n-1 antidiagnal, use row + col to index
            if (!hasQueenAtColumn[col] && !hasQueenAtMainDiag[row - col + n - 1] && !hasQueenAtAntiDiag[row + col])
            {
                hasQueenAtColumn[col] = hasQueenAtMainDiag[row - col + n - 1] = hasQueenAtAntiDiag[row + col] = 1;
                dfs(row + 1, n, count, hasQueenAtColumn, hasQueenAtMainDiag, hasQueenAtAntiDiag);
                hasQueenAtColumn[col] = hasQueenAtMainDiag[row - col + n - 1] = hasQueenAtAntiDiag[row + col] = 0;
            }
    }
};