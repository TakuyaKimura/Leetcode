/*

You are given a m x n 2D grid initialized with these three possible values.

   -1 - A wall or an obstacle.
    0 - A gate.
  INF - Infinity means an empty room. We use the value 2^31 - 1 = 2147483647 to represent INF 
        as you may assume that the distance to a gate is less than 2147483647.

Fill each empty room with the distance to its nearest gate. 

If it is impossible to reach a gate, it should be filled with INF.

For example, given the 2D grid:

        INF  -1  0  INF
        INF INF INF  -1
        INF  -1 INF  -1
        0  -1 INF INF

After running your function, the 2D grid should be:

        3  -1   0   1
        2   2   1  -1
        1  -1   2  -1
        0  -1   3   4

*/

#include <vector>
#include <queue>
using namespace std;

// BFS, O(mn), each room is updated at most once
class Solution {
public:
    void wallsAndGates(vector<vector<int>>& rooms) {
        int m = rooms.size(), n = m ? rooms[0].size() : 0, dist = 0;
        queue<pair<int, int>> q;
        int dxy[4][2] { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } };
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j)
                if (rooms[i][j] == 0)
                    q.push(make_pair(i, j));

        while (!q.empty())
        {
            int size = q.size();
            ++dist;
            while (size--)
            {
                int row = q.front().first, col = q.front().second, x, y;
                q.pop();
                for (int i = 0; i < 4; ++i)
                {
                    x = row + dxy[i][0];
                    y = col + dxy[i][1];
                    if (x >= 0 && x < m && y >= 0 && y < n && rooms[x][y] == INT_MAX)  // if not INF, then visited
                    {
                        rooms[x][y] = dist;
                        q.push(make_pair(x, y));
                    }
                }
            }
        }
    }
};

// DFS, each room could be updated multiple O(mn) times, so overall O((mn)^2)
class Solution2 {
public:
    void wallsAndGates(vector<vector<int>>& rooms) {
        m = rooms.size();
        n = m ? rooms[0].size() : 0;

        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j)
                if (rooms[i][j] == 0)
                    dfs(rooms, i, j);
    }
private:
    int m, n;
    int dxy[4][2] { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } };

    // int (&dxy)[4][2] if pass as argument
    void dfs(vector<vector<int>>& rooms, int row, int col) {
        int dist = rooms[row][col] + 1;
        for (int i = 0; i < 4; ++i)
        {
            int x = row + dxy[i][0], y = col + dxy[i][1];
            if (x >= 0 && x < m && y >= 0 && y < n && rooms[x][y] > dist)
            {
                rooms[x][y] = dist;
                dfs(rooms, x, y);
            }
        }
    }
};