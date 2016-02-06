/*

Given a 2D board containing 'X' and 'O', capture all regions surrounded by 'X'.

A region is captured by flipping all 'O's into 'X's in that surrounded region.

For example,

    X X X X
    X O O X
    X X O X
    X O X X

After running your function, the board should be:

    X X X X
    X X X X
    X X X X
    X O X X

*/

#include <vector>
#include <queue>
using namespace std;

// 12ms, DFS
// without using queue, use recursion
class Solution3 {
public:
    void solve(vector<vector<char>>& board) {
        int m = board.size(), n = m ? board[0].size() : 0, i, j;

        for (i = 0; i < m; ++i)
        {
            markBorder(board, i, 0, m, n);
            if (n > 1)
                markBorder(board, i, n - 1, m, n);
        }
        for (j = 1; j < n - 1; ++j)
        {
            markBorder(board, 0, j, m, n);
            if (m > 1)
                markBorder(board, m - 1, j, m, n);
        }

        for (i = 0; i < m; ++i)
            for (j = 0; j < n; ++j)
                board[i][j] = board[i][j] == 'B' ? 'O' : 'X';
    }
private:
    void markBorder(vector<vector<char>>& board, int row, int col, int m, int n) {
        if (board[row][col] == 'O')  // it's slower to check this before calling, why? locality of reference?
        {
            board[row][col] = 'B';
            if (row > 1)  // don't need to consider border elements
                markBorder(board, row - 1, col, m, n);
            if (col > 1)
                markBorder(board, row, col - 1, m, n);
            if (row < m - 2)
                markBorder(board, row + 1, col, m, n);
            if (col < n - 2)
                markBorder(board, row, col + 1, m, n);
        }
    }
};

// 16m, BFS, using queue
// change the value before pushing into queue, otherwise a lot redundant work
class Solution2 {
public:
    void solve(vector<vector<char>>& board) {
        int m = board.size(), n = m ? board[0].size() : 0, i, j;

        for (j = 0; j < n; ++j)
        {
            if (board[0][j] == 'O')
                markBorder(board, 0, j, m, n);
            if (board[m - 1][j] == 'O')
                markBorder(board, m - 1, j, m, n);
        }
        for (i = 1; i < m - 1; ++i)
        {
            if (board[i][0] == 'O')
                markBorder(board, i, 0, m, n);
            if (board[i][n - 1] == 'O')
                markBorder(board, i, n - 1, m, n);
        }

        for (i = 0; i < m; ++i)
            for (j = 0; j < n; ++j)
                if (board[i][j] == 'B')
                    board[i][j] = 'O';
                else
                    board[i][j] = 'X';
    }
private:
    queue<pair<int, int>> q;

    void markBorder(vector<vector<char>>& board, int row, int col, int m, int n) {
        pair<int, int> elem;
        board[row][col] = 'B';
        q.push(make_pair(row, col));
        while (!q.empty())
        {
            elem = q.front();
            q.pop();
            row = elem.first;
            col = elem.second;
            if (row > 0 && board[row - 1][col] == 'O')
            {
                board[row - 1][col] = 'B';  // change it before pushing into queue, will eliminate unnecessary pushes
                q.push(make_pair(row - 1, col));
            }
            if (row < m - 1 && board[row + 1][col] == 'O')
            {
                board[row + 1][col] = 'B';
                q.push(make_pair(row + 1, col));
            }
            if (col > 0 && board[row][col - 1] == 'O')
            {
                board[row][col - 1] = 'B';
                q.push(make_pair(row, col - 1));
            }
            if (col < n - 1 && board[row][col + 1] == 'O')
            {
                board[row][col + 1] = 'B';
                q.push(make_pair(row, col + 1));
            }
        }
    }
};

// 32ms
// use Union-Find data structure
// if a region can't be captured, it is connected to the border
// So if we connect all the 'O' nodes on the border to a dummy node
// then connect each 'O' node to its neighbour 'O' nodes
// we can tell whether an 'O' node is captured by checking whether it is connected to the dummy node
class Solution4 {
public:
    void solve(vector<vector<char>>& board) {
        int m = board.size(), n = m ? board[0].size() : 0, i, j;
        UF uf = UF(m * n + 1);  // last one is the dummy node

        for (i = 0; i < m; ++i)
            for (j = 0; j < n; ++j)
            {
                if (board[i][j] == 'X')
                    continue;
                // if a 'O' node is on the border, connect it to the dummy node
                if (i == 0 || i == m - 1 || j == 0 || j == n - 1)
                    uf.connect(i * n + j, m * n);
                // connect an 'O' node to its neighbour 'O' nodes
                else
                {
                    if (board[i - 1][j] == 'O')
                        uf.connect(i * n + j, (i - 1) * n + j);
                    if (board[i + 1][j] == 'O')
                        uf.connect(i * n + j, (i + 1) * n + j);
                    if (board[i][j - 1] == 'O')
                        uf.connect(i * n + j, i * n + j - 1);
                    if (board[i][j + 1] == 'O')
                        uf.connect(i * n + j, i * n + j + 1);
                }
            }

        for (i = 1; i < m - 1; ++i)  // don't change the value of the border elements
            for (j = 1; j < n - 1; ++j)
                // if an 'O' node is not connected to the dummy node, it can be captured
                if (board[i][j] == 'O' && !uf.connected(i * n + j, m * n))
                    board[i][j] = 'X';
    }


    class UF
    {
    public:
        UF(int N) : id(N), rank(N, 0), count(N) {
            for (int i = 0; i < N; ++i)
                id[i] = i;
        }

        int getCount() {
            return count;
        }

        bool connected(int p, int q) {
            return find(p) == find(q);
        }

        void connect(int p, int q) {
            int i = find(p), j = find(q);
            if (i == j)
                return;
            if (rank[i] < rank[j])
                id[i] = j;
            else if (rank[i] > rank[j])
                id[j] = i;
            else
            {
                id[j] = i;
                ++rank[i];
            }
            --count;
        }

    private:
        vector<int> id;    // id[i] = parent of i
        vector<int> rank;  // rank[i] = rank of subtree rooted at i (cannot be more than 31)
        int count;         // number of components

        int find(int p) {
            while (p != id[p])
                p = id[p] = id[id[p]];    // path compression by halving
            return p;
        }
    };
};

class Solution5 {
private:
    struct Cell {
        Cell* group_;
        bool hasExit_;
        bool hasExit() {
            if (!hasExit_ && this != group_ && group_->hasExit())
                hasExit_ = true;  // speed optimization
            return hasExit_;
        }
        void hasExit(bool a) {
            hasExit_ = a;
        }
        Cell* getGroup() {
            if (group_ != this)
                group_ = group_->getGroup();  // speed optimization
            return group_;
        }
        void setGroup(Cell* cell) {
            group_ = cell;
        }
        void connectTo(Cell &cell) {
            Cell* p = cell.getGroup();
            Cell* q = getGroup();
            bool b = q->hasExit() || p->hasExit();
            p->hasExit(b);
            q->setGroup(p);
        }
        Cell() {}
    };
public:
    void solve(vector<vector<char>> &board) {
        if (board.empty() || board[0].empty())
            return;
        int m = board.size();
        int n = board[0].size();
        vector<vector<Cell>> cells(m, vector<Cell>(n, Cell()));
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j)
            {
                Cell &p = cells[i][j];
                p.setGroup(&p);
                p.hasExit(i == 0 || j == 0 || i == m - 1 || j == n - 1);
            }

        for (int i = 1; i < m; ++i)
            for (int j = 1; j < n; ++j)
            {
                if (board[i][j] != 'O')
                    continue;
                if (board[i - 1][j] == 'O')  // don't need to check the cell beneath and right
                    cells[i][j].connectTo(cells[i - 1][j]);  // it -> up
                if (board[i][j - 1] == 'O')
                    cells[i][j].connectTo(cells[i][j - 1]);  // it -> left
            }

        for (int i = 1; i < m - 1; ++i)  // didn't change the border elements
            for (int j = 1; j < n - 1; ++j)
                if (board[i][j] == 'O' && !cells[i][j].hasExit())
                    board[i][j] = 'X';
    }
};

// 28ms, BFS, using queue
class Solution {
public:
    void solve(vector<vector<char>>& board) {
        int m = board.size(), n = m ? board[0].size() : 0, i, j;

        for (i = 0; i < n; ++i)
        {
            if (board[0][i] == 'O')
                markBorder(board, 0, i, m, n);
            if (board[m - 1][i] == 'O')
                markBorder(board, m - 1, i, m, n);
        }
        for (i = 1; i < m - 1; ++i)
        {
            if (board[i][0] == 'O')
                markBorder(board, i, 0, m, n);
            if (board[i][n - 1] == 'O')
                markBorder(board, i, n - 1, m, n);
        }

        for (i = 0; i < m; ++i)
            for (j = 0; j < n; ++j)
                if (board[i][j] == 'O')
                    board[i][j] = 'X';
                else if (board[i][j] == 'B')
                    board[i][j] = 'O';
    }
private:
    // BFS
    void markBorder(vector<vector<char>>& board, int row, int col, int m, int n) {
        queue<pair<int, int>> q;
        q.push(make_pair(row, col));
        while (!q.empty())
        {
            pair<int, int> elem = q.front();
            q.pop();
            row = elem.first;
            col = elem.second;
            if (row >= 0 && row < m && col >= 0 && col < n && board[row][col] == 'O') {
                board[row][col] = 'B';
                q.push(make_pair(row - 1, col));
                q.push(make_pair(row + 1, col));
                q.push(make_pair(row, col - 1));
                q.push(make_pair(row, col + 1));
            }
        }
    }
};