/*

Determine if a Sudoku is valid, according to: http://sudoku.com.au/TheRules.aspx.

The Sudoku board could be partially filled, where empty cells are filled with the character '.'.

Note:
A valid Sudoku board (partially filled) is not necessarily solvable. Only the filled cells need to be validated.

*/

#include <vector>
#include <unordered_set>
#include <array>  // usage: array<bool, 9> used; used.fill(false);
#include <iostream>
using namespace std;

// 12ms, using int array is faster than bool array in OJ
class Solution3 {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        int row[9][9] = { 0 };
        int col[9][9] = { 0 };
        int blk[9][9] = { 0 };
        int i, j, num, block;
        for (i = 0; i < 9; ++i)
            for (j = 0; j < 9; ++j)
            {
                if (board[i][j] == '.')
                    continue;
                num = board[i][j] - '1';
                block = i / 3 * 3 + j / 3;
                if (row[i][num] || col[j][num] || blk[block][num])
                    return false;
                row[i][num] = col[j][num] = blk[block][num] = 1;
            }
        return true;
    }
};

class Solution {
public:
    bool isValidSudoku(vector<vector<char>> &board) {
        unordered_set<char> row[9];
        unordered_set<char> col[9];
        unordered_set<char> blk[9];
        char c;
        int block;
        for (int i = 0; i < 9; ++i)
            for (int j = 0; j < 9; ++j)
            {
                c = board[i][j];
                if (c != '.')
                {
                    if (c > '9' || c < '1')
                        return false;
                    if (row[i].find(c) == row[i].end())
                        row[i].insert(c);
                    else
                        return false;
                    if (col[j].find(c) == col[j].end())
                        col[j].insert(c);
                    else
                        return false;
                    block = i / 3 * 3 + j / 3;
                    if (blk[block].find(c) == blk[block].end())
                        blk[block].insert(c);
                    else
                        return false;
                }
            }
        return true;
    }
};

class Solution2 {
public:
    bool isValidSudoku(vector<vector<char>> &board) {
        array<bool, 9> used;
        int num;
        char c;
        for (int i = 0; i < 9; ++i)
        {
            used.fill(false);
            for (int j = 0; j < 9; ++j)
                if (board[i][j] != '.')
                {
                    num = board[i][j] - '1';
                    if (num > 9 || num < 0 || used[num])
                        return false;
                    used[num] = true;
                }
        }
        for (int j = 0; j < 9; ++j)
        {
            used.fill(false);
            for (int i = 0; i < 9; ++i)
                if (board[i][j] != '.')
                {
                    num = board[i][j] - '1';
                    if (used[num])
                        return false;
                    used[num] = true;
                }
        }
        for (int row = 0; row < 3; ++row)
            for (int col = 0; col < 3; ++col)
            {
                used.fill(false);
                for (int i = 0; i < 3; ++i)
                    for (int j = 0; j < 3; ++j)
                    {
                        c = board[row * 3 + i][col * 3 + j];
                        if (c != '.')
                        {
                            num = c - '1';
                            if (used[num])
                                return false;
                            used[num] = true;
                        }
                    }
            }
        return true;
    }
};

int main()
{
    Solution2 s;
    vector<vector<char>> board(9, vector<char>(9, '.'));
    for (int i = 1; i < 9; ++i)
    {
        board[0][i] = '0' + 9 - i;
        board[i][0] = '0' + i + 1;
    }
    cout << s.isValidSudoku(board);

}