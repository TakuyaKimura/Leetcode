/*

Given a 2d grid map of '1's (land) and '0's (water), count the number of islands. 

An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. 

You may assume all four edges of the grid are all surrounded by water.

Example 1:

    11110
    11010
    11000
    00000

    Answer: 1

Example 2:

    11000
    11000
    00100
    00011

    Answer: 3

*/

#include <vector>
#include <queue>
using namespace std;

// DFS 
// need to change the value of the cell before calling next function
// otherwise will push duplicates
class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int m = grid.size(), n = m ? grid[0].size() : 0, i, j, count = 0;
        for (i = 0; i < m; ++i)
            for (j = 0; j < n; ++j)
                if (grid[i][j] == '1')
                {
                    dfs(grid, i, j, m, n);
                    ++count;
                }
        return count;
    }
private:
    void dfs(vector<vector<char>>& grid, int i, int j, int m, int n) {
        grid[i][j] = 'x';
        if (i > 0 && grid[i - 1][j] == '1')
            dfs(grid, i - 1, j, m, n);
        if (i < m - 1 && grid[i + 1][j] == '1')
            dfs(grid, i + 1, j, m, n);
        if (j > 0 && grid[i][j - 1] == '1')
            dfs(grid, i, j - 1, m, n);
        if (j < n - 1 && grid[i][j + 1] == '1')
            dfs(grid, i, j + 1, m, n);
    }
};

// same idea
class Solution2 {
public:
    int numIslands(vector<vector<char>>& grid) {
        int m = grid.size(), n = m ? grid[0].size() : 0, i, j, count = 0;
        for (i = 0; i < m; ++i)
            for (j = 0; j < n; ++j)
                if (grid[i][j] == '1')
                {
                    dfs(grid, i, j, m, n);
                    ++count;
                }
        return count;
    }
private:
    void dfs(vector<vector<char>>& grid, int i, int j, int m, int n) {
        if (i == -1 || i == m || j == -1 || j == n || grid[i][j] != '1')
            return;
        grid[i][j] = 'x';
        dfs(grid, i - 1, j, m, n);
        dfs(grid, i + 1, j, m, n);
        dfs(grid, i, j - 1, m, n);
        dfs(grid, i, j + 1, m, n);
    }
};

// BFS using a queue - need to change the value of the cell before pushing into queue
class Solution3 {
public:
    int numIslands(vector<vector<char>>& grid) {
        int m = grid.size(), n = m ? grid[0].size() : 0, i, j, count = 0;
        for (i = 0; i < m; ++i)
            for (j = 0; j < n; ++j)
                if (grid[i][j] == '1')
                {
                    bfs(grid, i, j, m, n);
                    ++count;
                }
        return count;
    }
private:
    void bfs(vector<vector<char>>& grid, int i, int j, int m, int n) {
        queue<pair<int, int>> q;
        q.push(make_pair(i, j));
        grid[i][j] = 'x';
        while (!q.empty())
        {
            i = q.front().first;
            j = q.front().second;
            q.pop();
            if (i > 0 && grid[i - 1][j] == '1')
            {
                q.push(make_pair(i - 1, j));
                grid[i - 1][j] = 'x';
            }
            if (i < m - 1 && grid[i + 1][j] == '1')
            {
                q.push(make_pair(i + 1, j));
                grid[i + 1][j] = 'x';
            }
            if (j > 0 && grid[i][j - 1] == '1')
            {
                q.push(make_pair(i, j - 1));
                grid[i][j - 1] = 'x';
            }
            if (j < n - 1 && grid[i][j + 1] == '1')
            {
                q.push(make_pair(i, j + 1));
                grid[i][j + 1] = 'x';
            }
        }
    }
};

// using Union Find with a dummy point
// It's obvious to connect adjacent 1s. Then how to handle 0s?
// if we connect all 0s to the dummy point, then the count of UF is equal to the number of islands plus 1
class UF {
public:
    UF(int N) : count(N), id(N), weight(N, 0) {
        for (int i = 0; i < N; ++i) 
            id[i] = i;
    }

    void unionP(int p, int q) {
        int i = root(p), j = root(q);
        if (i == j)
            return;
        if (weight[i] < weight[j])
            id[i] = j;
        else if (weight[i] > weight[j])
            id[j] = i;
        else 
        {
            id[i] = j;
            ++weight[j];
        }
        --count;
    }

    bool connected(int p, int q) {
        return root(p) == root(q);
    }

    int getCount() {
        return count;
    }

private:
    vector<int> id;
    vector<int> weight;  // height?
    int count;

    int root(int i) {
        while (i != id[i])
            i = id[i] = id[id[i]];
        return i;
    }
};

class Solution4 {
public:
    // Runtime: 8 ms
    int numIslands(vector<vector<char>>& grid) {
        if (grid.empty() || grid[0].empty())
            return 0;

        int ROW = grid.size(), COL = grid[0].size();
        UF uf(ROW * COL + 1);
        int dummyPoint = ROW * COL;  // We assume it as 0 and it connects all 0s.
        for (int i = 0; i < ROW; ++i)
            for (int j = 0; j < COL; ++j)
                if (grid[i][j] == '1')
                {
                    if (j != COL - 1 && grid[i][j + 1] == '1')
                        uf.unionP(i * COL + j, i * COL + j + 1);
                    if (i != ROW - 1 && grid[i + 1][j] == '1')
                        uf.unionP(i * COL + j, (i + 1) * COL + j);
                }
                else
                    uf.unionP(i * COL + j, dummyPoint);  // connect all 0s to the dummy point

        return uf.getCount() - 1;
    }
};