/*

Given a 2D board and a word, find if the word exists in the grid.

The word can be constructed from letters of sequentially adjacent cell, 
where "adjacent" cells are those horizontally or vertically neighboring. 
The same letter cell may not be used more than once.

For example,
Given board =
    [
        ['A','B','C','E'],
        ['S','F','C','S'],
        ['A','D','E','E']
    ]

word = "ABCCED", -> returns true,
word = "SEE", -> returns true,
word = "ABCB", -> returns false.

*/

#include <vector>
#include <string>
using namespace std;

// DFS
// running time: O(m *n * 4^w), where w is length of word
// w = O(m * n)

class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        int m = board.size(), n = m ? board[0].size() : 0, len = word.length();
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j)
                if (dfs(board, word, 0, i, j, m, n, len))
                    return true;
        return false;
    }
private:
    bool dfs(vector<vector<char>>& board, string const& word, int idx, int i, int j, int m, int n, int len) {
        if (idx == len)
            return true;
        if (i == -1 || i == m || j == -1 || j == n || board[i][j] != word[idx])
            return false;
        char c = board[i][j];
        board[i][j] = '\0';  // mark as visited
        bool found = dfs(board, word, idx + 1, i + 1, j, m, n, len)
                  || dfs(board, word, idx + 1, i - 1, j, m, n, len)
                  || dfs(board, word, idx + 1, i, j + 1, m, n, len)
                  || dfs(board, word, idx + 1, i, j - 1, m, n, len);
        board[i][j] = c;
        return found;
    }
};