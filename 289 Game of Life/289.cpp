/*

According to the Wikipedia's article: 
"The Game of Life, also known simply as Life, is a cellular automaton 
devised by the British mathematician John Horton Conway in 1970."

Given a board with m by n cells, each cell has an initial state live (1) or dead (0). 
Each cell interacts with its eight neighbors (horizontal, vertical, diagonal) 
using the following four rules (taken from the above Wikipedia article):

    Any live cell with fewer than two live neighbors dies, as if caused by under-population.
    Any live cell with two or three live neighbors lives on to the next generation.
    Any live cell with more than three live neighbors dies, as if by over-population..
    Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.

Write a function to compute the next state (after one update) of the board given its current state.

Follow up:
1. Could you solve it in-place? Remember that the board needs to be updated at the same time: 
   You cannot update some cells first and then use their updated values to update other cells.

2. In this question, we represent the board using a 2D array. 
   In principle, the board is infinite, which would cause problems 
   when the active area encroaches the border of the array. How would you address these problems?

*/

#include <vector>
#include <algorithm>
using namespace std;

// in-place
// Since the board has ints, but only 1 bit is used, use the second bit to store the new state.
// At the end, replace the old state with the new state by shifting all values one bit to the right.
class Solution {
public:
    void gameOfLife(vector<vector<int>>& board) {
        int m = board.size(), n = m ? board[0].size() : 0, i, j, I, J, count;
        for (i = 0; i < m; ++i)
            for (j = 0; j < n; ++j)
            {
                count = 0;  // count = -board[i][j], if don't want to include itself
                // count neighbors including itself
                for (I = max(i - 1, 0); I < min(i + 2, m); ++I)
                    for (J = max(j - 1, 0); J < min(j + 2, n); ++J)
                        count += board[I][J] & 1;  // get the last bit
                if (count == 3 || count - board[i][j] == 3)
                    board[i][j] |= 2;  // set the second to last bit
            }

        for (i = 0; i < m; ++i)
            for (j = 0; j < n; ++j)
                board[i][j] >>= 1;
    }
};