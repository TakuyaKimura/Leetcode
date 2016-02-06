/*

Write a program to solve a Sudoku puzzle by filling the empty cells.

Empty cells are indicated by the character '.'.

You may assume that there will be only one unique solution.

*/

#include <vector>
#include <cstdint>  // for uint8_t, 8 bits
#include <bitset>
#include <array>
#include <cassert>  // for assert()
using namespace std;

// 4ms
class Solution6 {
public:
    void solveSudoku(vector<vector<char>>& board) {
        bool rows[9][9] = { false }, cols[9][9] = { false }, blks[9][9] = { false };
        for (int i = 0; i < 9; ++i)
            for (int j = 0; j < 9; ++j)
            {
                if (board[i][j] != '.')
                {
                    int idx = board[i][j] - '1';
                    rows[i][idx] = cols[j][idx] = blks[i / 3 * 3 + j / 3][idx] = true;
                }
            }
        dfs(board, rows, cols, blks, 0, 0);
    }
private:
    bool dfs(vector<vector<char>>& board, bool(&rows)[9][9], bool(&cols)[9][9], bool(&blks)[9][9], int i, int j) {
        i = i + j / 9;
        j = j % 9;
        if (i == 9)
            return true;
        if (board[i][j] == '.')
        {
            for (int idx = 0; idx < 9; ++idx)
                if (!rows[i][idx] && !cols[j][idx] && !blks[i / 3 * 3 + j / 3][idx])
                {
                    board[i][j] = '1' + idx;
                    rows[i][idx] = cols[j][idx] = blks[i / 3 * 3 + j / 3][idx] = true;
                    if (dfs(board, rows, cols, blks, i, j + 1))
                        return true;  // immediate return when one solution is found, don't need all solutions
                    rows[i][idx] = cols[j][idx] = blks[i / 3 * 3 + j / 3][idx] = false;
                }
            board[i][j] = '.';  // reset it, in case of unsuccessful approach, when we change the upper level, this needs to be '.'
            return false;       // unsuccessful, backtrack to upper level
        }
        else
            return dfs(board, rows, cols, blks, i, j + 1);
    }
};

// 40ms, O(9^4)
class Solution {
public:
    void solveSudoku(vector<vector<char>>& board) {
        vector<pair<int, int>> positions;
        for (int i = 0; i < 9; ++i)
            for (int j = 0; j < 9; ++j)
                if (board[i][j] == '.')
                    positions.push_back(make_pair(i, j));
        solve(board, positions, 0);
    }

private:
    bool solve(vector<vector<char>>&board, vector<pair<int, int>>& positions, int idx) {
        if (idx == positions.size())
            return true;

        int x = positions[idx].first, y = positions[idx].second;
        for (char c = '1'; c <= '9'; ++c)  // try each
        {
            board[x][y] = c;
            if (isValid(board, x, y, c) && solve(board, positions, idx + 1))
                return true;
            board[x][y] = '.';
        }
        return false;
    }

    bool isValid(vector<vector<char>>&board, int x, int y, char c) {
        for (int j = 0; j < 9; ++j)
            if (j != y && board[x][j] == c || j != x && board[j][y] == c)
                return false;

        int block_row = x / 3 * 3, block_col = y / 3 * 3;
        for (int row = block_row; row < block_row + 3; ++row)
            for (int col = block_col; col < block_col + 3; ++col)
                if (row != x && col != y && board[row][col] == c)
                    return false;

        return true;
    }
};

// same idea, 52ms
class Solution2 {
public:
    void solveSudoku(vector<vector<char>>& board) {
        solve(board, 0);
    }
private:
    bool solve(vector<vector<char>>& board, int ind) {
        if (ind == 81)
            return true;
        int i = ind / 9, j = ind % 9;
        if (board[i][j] != '.')
            return solve(board, ind + 1);
        else
        {
            for (char f = '1'; f <= '9'; ++f)
                if (isValidFill(board, i, j, f))
                {
                    board[i][j] = f;
                    if (solve(board, ind + 1))
                        return true;
                    board[i][j] = '.';
                }

            return false;
        }
    }
    bool isValidFill(vector<vector<char>>& board, int i, int j, char fill) {
        for (int k = 0; k < 9; ++k)
        {
            if (board[i][k] == fill)  // check the row
                return false;
            if (board[k][j] == fill)  // check the column
                return false;
            int r = i / 3 * 3 + j / 3;   //select the block
            if (board[r / 3 * 3 + k / 3][r % 3 * 3 + k % 3] == fill)  // check the block
                return false;
        }
        return true;
    }
};

// 4ms
class Solution3 {
public:
    void solveSudoku(vector<vector<char>>& board) {
        memset(row, 0, sizeof(row));
        memset(col, 0, sizeof(col));
        memset(grid, 0, sizeof(grid));
        for (int i = 0; i < 9; ++i)
            for (int j = 0; j < 9; ++j)
            {
                char c = board[i][j];
                if (c != '.')
                {
                    int k = c - '1';
                    row[i][k] = true;
                    col[j][k] = true;
                    grid[i / 3][j / 3][k] = true;
                }
            }
        solve(board, 0, 0);
    }

private:
    bool row[9][9];
    bool col[9][9];
    bool grid[3][3][9];

    bool solve(vector<vector<char>>& board, int i, int j) {
        if (i >= 9)
            return true;

        if (board[i][j] != '.')
            return solve(board, i + (j + 1) / 9, (j + 1) % 9);

        for (int k = 0; k < 9; ++k)
            if (!row[i][k] && !col[j][k] && !grid[i / 3][j / 3][k])
            {
                board[i][j] = '1' + k;
                row[i][k] = col[j][k] = grid[i / 3][j / 3][k] = true;
                if (solve(board, i + (j + 1) / 9, (j + 1) % 9))
                    return true;
                board[i][j] = '.';
                row[i][k] = col[j][k] = grid[i / 3][j / 3][k] = false;
            }

        return false;
    }
};

/**
    combines several techniques like reactive network update propagation and backtracking with very aggressive pruning.

    The algorithm is online - it starts with an empty board and as you add numbers to it, it starts solving the Sudoku.

    Unlike in other solutions where you have bitmasks of allowed/disallowed values per row/column/square, 
    this solution track bitmask for every(!) cell, forming a set of constraints for the allowed values for each particular cell. 
    Once a value is written into a cell, new constraints are immediately propagated to row, column and 3x3 square of the cell. 
    If during this process a value of other cell can be unambiguously deduced - then the value is set, 
    new constraints are propagated, so on.... You can think about this as an implicit reactive network of cells.

    If we're lucky (and we'll be lucky for 19 of 20 of Sudokus published in magazines) 
    then Sudoku is solved at the end (or even before!) processing of the input.

    Otherwise, there will be empty cells which have to be resolved. Algorithm uses backtracking for this purpose. 
    To optimize it, algorithm starts with the cell with the smallest ambiguity. 
    This could be improved even further by using priority queue (but it's not implemented here). 
    Backtracking is more or less standard, however, at each step we guess the number, 
    the reactive update propagation comes back into play 
    and it either quickly proves that the guess is unfeasible or significantly prunes the remaining search space.

    It's interesting to note, that in this case taking and restoring snapshots of the compact representation of the state 
    is faster than doing backtracking rollback by "undoing the moves".
*/

// 0ms
class Solution4 {
    struct cell // encapsulates a single cell on a Sudoku board
    {
        uint8_t value; // cell value 1..9 or 0 if unset
        // number of possible (unconstrained) values for the cell
        uint8_t numPossibilities;
        // if bitset[v] is 1 then value can't be v
        bitset<10> constraints;
        cell() : value(0), numPossibilities(9), constraints() {};
    };
    array<array<cell, 9>, 9> cells;

    // sets the value of the cell to [v]
    // the function also propagates constraints to other cells and deduce new values where possible
    bool set(int i, int j, int v)
    {
        // updating state of the cell
        cell& c = cells[i][j];
        if (c.value == v)
            return true;
        if (c.constraints[v])
            return false;
        c.constraints = bitset<10>(0x3FE); // all 1s
        c.constraints.reset(v);
        c.numPossibilities = 1;
        c.value = v;

        // propagating constraints
        for (int k = 0; k < 9; ++k)
        {
            // to the row: 
            if (i != k && !updateConstraints(k, j, v))
                return false;
            // to the column:
            if (j != k && !updateConstraints(i, k, v))
                return false;
            // to the 3x3 square:
            int ix = (i / 3) * 3 + k / 3;
            int jx = (j / 3) * 3 + k % 3;
            if (ix != i && jx != j && !updateConstraints(ix, jx, v))
                return false;
        }
        return true;
    }
    // update constraints of the cell i,j by excluding possibility of 'excludedValue'
    // once there's one possibility left the function recurses back into set()
    bool updateConstraints(int i, int j, int excludedValue)
    {
        cell& c = cells[i][j];
        if (c.constraints[excludedValue])
            return true;

        if (c.value == excludedValue)
            return false;

        c.constraints.set(excludedValue);
        if (--c.numPossibilities > 1)
            return true;
        for (int v = 1; v <= 9; ++v)
            if (!c.constraints[v])
                return set(i, j, v);

        assert(false);
    }

    // backtracking state - list of empty cells
    vector<pair<int, int>> bt;

    // find values for empty cells
    bool findValuesForEmptyCells()
    {
        // collecting all empty cells
        bt.clear();
        for (int i = 0; i < 9; ++i)
            for (int j = 0; j < 9; ++j)
                if (!cells[i][j].value)
                    bt.push_back(make_pair(i, j));

        // making backtracking efficient by pre-sorting empty cells by numPossibilities
        sort(bt.begin(), bt.end(), [this](const pair<int, int>&a, const pair<int, int>&b) {
            return cells[a.first][a.second].numPossibilities < cells[b.first][b.second].numPossibilities; });
            return backtrack(0);
    }

    // Finds value for all empty cells with index >=k
    bool backtrack(int k)
    {
        if (k >= bt.size())
            return true;
        int i = bt[k].first;
        int j = bt[k].second;
        // fast path - only 1 possibility
        if (cells[i][j].value)
            return backtrack(k + 1);
        auto constraints = cells[i][j].constraints;
        // slow path >1 possibility.
        // making snapshot of the state
        array<array<cell, 9>, 9> snapshot(cells);
        for (int v = 1; v <= 9; ++v)
            if (!constraints[v])
            {
                if (set(i, j, v))
                    if (backtrack(k + 1))
                        return true;
                // restoring from snapshot,
                // note: computationally this is cheaper
                // than alternative implementation with undoing the changes
                cells = snapshot;
            }
        return false;
    }

public:
    void solveSudoku(vector<vector<char>>& board) {
        cells = array<array<cell, 9>, 9>(); // clear array
        // Decoding input board into the internal cell matrix.
        // As we do it - constraints are propagated and even additional values are set as we go
        // (in the case if it is possible to unambiguously deduce them).
        for (int i = 0; i < 9; ++i)
            for (int j = 0; j < 9; ++j)
                if (board[i][j] != '.' && !set(i, j, board[i][j] - '0'))
                    return; // sudoku is either incorrect or unsolvable

        // if we're lucky we've already got a solution,
        // however, if we have empty cells we need to use backtracking to fill them
        if (!findValuesForEmptyCells())
            return; // sudoku is unsolvable

        // copying the solution back to the board
        for (int i = 0; i < 9; ++i)
            for (int j = 0; j < 9; ++j)
                if (cells[i][j].value)
                    board[i][j] = cells[i][j].value + '0';
    }
};

// Dancing Links X Algorithm, 0ms
class Solution5 {
public:
    static const int maxn = 15;

    int n;

    static const int maxCol = maxn * maxn * 4;
    static const int maxNode = maxCol + maxn * maxn * maxn * 4;

    int ID;
    int h, S[maxCol], N[maxCol];
    int U[maxNode], D[maxNode], L[maxNode], R[maxNode], C[maxNode], V[maxNode];

    char str[maxn * maxn];

    bool succ;
    void DL(int c, bool uncover = false)
    {
        if (!uncover)
        { 
            R[L[c]] = R[c];
            L[R[c]] = L[c];
        }
        else
            R[L[c]] = L[R[c]] = c;

        for (int i = D[c]; i != c; i = D[i])
            for (int j = R[i]; j != i; j = R[j])
                if (!uncover)
                { 
                    U[D[j]] = U[j];
                    D[U[j]] = D[j];
                    --S[C[j]];
                }
                else
                {
                    U[D[j]] = D[U[j]] = j;
                    ++S[C[j]];
                }
    }
    void dfs(int dep)
    {
        if (succ || R[h] == h)
        {
            succ = true;
            return;
        }
        int c = R[h];
        for (int i = R[h]; i != h; i = R[i])
        {
            if (!S[i])
                return;
            if (S[i] < S[c])
                c = i;
        }
        DL(c);
        for (int i = D[c]; i != c; i = D[i])
        {
            N[c] = V[i];
            for (int j = R[i]; j != i; j = R[j])
                DL(C[j]), N[C[j]] = V[j];

            dfs(dep + 1);
            if (succ)
                return;
            for (int j = L[i]; j != i; j = L[j])
                DL(C[j], true);
        }
        DL(c, true);
    }

    int add(int c, int v)
    {
        ++S[c];
        L[ID] = R[ID] = ID;
        U[ID] = U[c], D[ID] = c;
        D[U[ID]] = U[D[ID]] = ID;
        V[ID] = v;
        C[ID] = c;
        return ID++;
    }

# define INSR(x, y) do{ L[y]=x,R[y]=R[x];R[L[y]]=L[R[y]]=y; }while(0)

    void solveSudoku(std::vector<std::vector<char>> &board) {
        n = 9;

        char str[maxn * maxn];
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                str[i * 9 + j] = board[i][j];

        str[n*n] = 0;

        h = 4 * n*n;
        for (int c = 0; c <= h; ++c)
        {
            S[c] = 0;
            C[c] = D[c] = U[c] = c;
            L[c] = (c ? c - 1 : h);
            R[c] = (c == h ? 0 : c + 1);
        }
        ID = h + 1;
        for (int i = 0; str[i]; ++i)
        {
            int x = i / 9, y = i % 9;
            int lo = 1, hi = n;
            if ('1' <= str[i] && str[i] <= '0' + n)
            {
                lo = hi = str[i] - '0';
                V[i] = str[i] - '0';
            }
            for (int j = lo; j <= hi; ++j)
            {
                int a = add(i, j);
                int b = add(n*n + x * 9 + j - 1, j);
                int c = add(2 * n*n + y * 9 + j - 1, j);
                int d = add(3 * n*n + (x / 3 * 3 + y / 3) * 9 + j - 1, j);
                INSR(a, b);
                INSR(b, c);
                INSR(c, d);
            }
        }
        for (int i = R[h]; i != h; i = R[i])
        {
            if (S[i] == 0)
                return;
            if (S[i] == 1)
            {
                N[i] = V[i];
                DL(i);
                for (int j = D[i]; j != i; j = D[j])
                    for (int k = R[j]; k != j; k = R[k]) DL(C[k]), N[C[k]] = V[k];
            }
        }
        succ = false;
        dfs(0);
        if (succ)
            for (int i = 0; i < n * n; ++i)
                board[i / 9][i % 9] = N[i] + '0';
    }
};